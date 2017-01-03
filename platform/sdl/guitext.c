#include "debug.h"
#include "draw.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <stdint.h>

/* vertexTextShader is the vertex shader used for text rendering. */
static GLchar const *textVertexShader[] = {"#version 150\n"
                                           "in vec4 pos;\n"
                                           "in vec2 texco;\n"
                                           "out vec2 out_texco;\n"
                                           "uniform mat4 mvp;\n"
                                           "void main( void ) {"
                                           "    out_texco = texco;\n"
                                           "    gl_Position = mvp * pos;\n"
                                           "}\n"};

/* fragmentTextShader is the fragment shader used for text rendering. */
static GLchar const *textFragmentShader[] = {
    "#version 150\n"
    "in vec2 out_texco;\n"
    "out vec4 out_color;\n"
    "uniform sampler2D tex0;\n"
    "void main()\n"
    "{\n"
    "  out_color = texture(tex0, out_texco);\n"
    "}\n"};

/* textMesh is the mesh used for drawing glyphs. */
struct TextMesh {
	struct Mesh *mesh;
	GLuint vao;
	struct {
		GLuint pos, texco;
	} buffs;
	struct {
		GLuint pos, texco;
	} attrs;
} textMesh;

static GLuint textProgram;   /* the shader program */
static struct Mat4x4 guiMat; /* the mvp mat used for rendering the GUI */
static GLint mvp;            /* the modelview matrix uniform handle */
static GLuint font;          /* the font texture handle */
static GLuint fontUniform;   /* the font texture handle */

/* initShader compiles the shader used for GUI rendering in this engine. */
static bool initShader() {
	GLint compiled, linked;
	GLuint fs, vs, gs;

	fs = 0;
	vs = 0;
	gs = 0;

	/* create shader program (if not already built) */
	if (textProgram == 0) {
		GLint len;
		/* vertex shader */
		vs = glCreateShader(GL_VERTEX_SHADER);
		len = strlen(textVertexShader[0]);
		glShaderSource(vs, 1, textVertexShader, &len);
		glCompileShader(vs);
		glGetShaderiv(vs, GL_COMPILE_STATUS, &compiled);
		if (compiled == GL_FALSE) {
			GLint logSz;
			GLchar *log;

			glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &logSz);
			log = malloc(logSz * sizeof(GLchar));
			glGetShaderInfoLog(vs, logSz, &logSz, log);
			debug_puts("error: vertex shader compilation failed");
			debug_puts(log);
			free(log);
			return false;
		}

		/* fragment shader */
		fs = glCreateShader(GL_FRAGMENT_SHADER);
		len = strlen(textFragmentShader[0]);
		glShaderSource(fs, 1, textFragmentShader, &len);
		glCompileShader(fs);
		glGetShaderiv(fs, GL_COMPILE_STATUS, &compiled);
		if (compiled == GL_FALSE) {
			GLint logSz;
			GLchar *log;

			glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &logSz);
			log = malloc(logSz * sizeof(GLchar));
			glGetShaderInfoLog(fs, logSz, &logSz, log);
			debug_puts("error: fragment shader compilation failed");
			debug_puts(log);
			free(log);
			return false;
		}

		/* link shaders */
		textProgram = glCreateProgram();
		glAttachShader(textProgram, vs);
		glAttachShader(textProgram, fs);
		glLinkProgram(textProgram);
		glGetProgramiv(textProgram, GL_LINK_STATUS, &linked);
		if (linked == GL_FALSE) {
			GLint logSz;
			GLchar *log;

			glGetProgramiv(textProgram, GL_INFO_LOG_LENGTH, &logSz);
			log = malloc(logSz * sizeof(GLchar));
			glGetProgramInfoLog(textProgram, logSz, &logSz, log);
			debug_puts("error: shader program failed to link");
			debug_puts(log);
			free(log);
			return false;
		}

		/* get the modelview-projection matrix uniform */
		mvp = glGetUniformLocation(textProgram, "mvp");
		if (mvp == -1) {
			debug_puts("error: no \"mvp\" uniform found in shader "
			           "program");
			return false;
		}
	}
	return true;
}

/* bitmap to texture loads file and returns a handle an OpenGL texture of it */
static GLuint bitmapToTexture(const char *file) {
	GLuint tex;
	SDL_Surface *surf;

	surf = NULL;
	tex = 0;
	if ((surf = SDL_LoadBMP(file))) {
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0,
		             GL_RGB, GL_UNSIGNED_BYTE, surf->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		                GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		                GL_NEAREST);
		SDL_FreeSurface(surf);
		glBindTexture(GL_TEXTURE_2D, 0);
	} else {
		printf("error: failed to load texture %s\n", file);
	}
	printf("%d\n", tex);
	return tex;
}

/* initGUI initializes the OpenGL and SDL state used for GUI rendering */
void initGUI() {
	mat4x4_orthographic(&guiMat, 0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);

	if (!initShader()) {
		debug_puts("error: shader");
	}
	font = bitmapToTexture("font.bmp");
	fontUniform = glGetUniformLocation(textProgram, "texture");
}

/* tv_GuiRect draws a w x h rectangle @ (x,y). */
void tv_GuiRect(unsigned x, unsigned y, unsigned w, unsigned h, uint32_t rgba) {
	GLint program;
	static GLuint vao;
	static struct { GLuint col, pos; } buffs;
	static struct { GLint col, pos; } attrs;
	uint8_t r = (rgba & 0xff000000) >> 24;
	uint8_t g = (rgba & 0x00ff0000) >> 16;
	uint8_t b = (rgba & 0x0000ff00) >> 8;
	uint8_t a = (rgba & 0x000000ff);
	uint8_t c[] = {
	    r, g, b, a, r, g, b, a, r, g, b, a,
	    r, g, b, a, r, g, b, a, r, g, b, a,
	};
	uint16_t v[] = {x, y, 1, 1, x + w, y,     1, 1, x + w, y + h, 1, 1,
	                x, y, 1, 1, x + w, y + h, 1, 1, x,     y + h, 1, 1};

	glGetIntegerv(GL_CURRENT_PROGRAM, &program);
	if (vao == 0) {
		glGenBuffers(1, &buffs.pos);
		glGenBuffers(1, &buffs.col);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		attrs.pos = glGetAttribLocation(program, "pos");
		if (attrs.pos == -1)
			debug_puts("error: could not find attribute \"pos\" in "
			           "shader program.");
		attrs.col = glGetAttribLocation(program, "col");
		if (attrs.col == -1)
			debug_puts("error: could not find attribute \"col\" in "
			           "shader program.");
	}
	glBindVertexArray(vao);
	glUniformMatrix4fv(mvp, 1, GL_FALSE, mat4x4_to_array(&guiMat));
	glBindBuffer(GL_ARRAY_BUFFER, buffs.pos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffs.col);
	glBufferData(GL_ARRAY_BUFFER, sizeof(c), c, GL_STATIC_DRAW);

	glEnableVertexAttribArray(attrs.pos);
	glBindBuffer(GL_ARRAY_BUFFER, buffs.pos);
	glVertexAttribPointer(attrs.pos, 4, GL_UNSIGNED_SHORT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(attrs.col);
	glBindBuffer(GL_ARRAY_BUFFER, buffs.col);
	glVertexAttribPointer(attrs.col, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

static void drawChar(char c, unsigned x, unsigned y, unsigned sz) {
	const unsigned ustep = 0xffff / 16;
	const unsigned vstep = 0xffff / 16;
	static GLuint vao;
	static struct { GLuint pos, texco; } buffs;
	static struct { GLint pos, texco; } attrs;
	unsigned u, v, w, h;

	w = sz;
	h = sz;
	u = 0xffff * ((c % 16) / 16.0f);
	v = 0xffff * ((c / 16) / 16.0f);

	uint16_t vd[] = {x, y, 1, 1, x + w, y,     1, 1, x + w, y + h, 1, 1,
	                 x, y, 1, 1, x + w, y + h, 1, 1, x,     y + h, 1, 1};
	uint16_t td[] = {u, v, u + ustep, v,         u + ustep, v + vstep,
	                 u, v, u + ustep, v + vstep, u,         v + vstep};

	if (vao == 0) {
		glGenBuffers(1, &buffs.pos);
		glGenBuffers(1, &buffs.texco);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		attrs.pos = glGetAttribLocation(textProgram, "pos");
		if (attrs.pos == -1)
			debug_puts("error: could not find attribute \"pos\" in "
			           "shader program.");
		attrs.texco = glGetAttribLocation(textProgram, "texco");
		if (attrs.texco == -1)
			debug_puts(
			    "error: could not find attribute \"texco\" in "
			    "shader program.");
	}

	glBindVertexArray(vao);

	glUniformMatrix4fv(mvp, 1, GL_FALSE, mat4x4_to_array(&guiMat));
	glBindBuffer(GL_ARRAY_BUFFER, buffs.pos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vd), vd, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffs.texco);
	glBufferData(GL_ARRAY_BUFFER, sizeof(td), td, GL_STATIC_DRAW);

	glEnableVertexAttribArray(attrs.pos);
	glBindBuffer(GL_ARRAY_BUFFER, buffs.pos);
	glVertexAttribPointer(attrs.pos, 4, GL_UNSIGNED_SHORT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(attrs.texco);
	glBindBuffer(GL_ARRAY_BUFFER, buffs.texco);
	glVertexAttribPointer(attrs.texco, 2, GL_UNSIGNED_SHORT, GL_TRUE, 0, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, font);
	glUniform1i(fontUniform, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

/* tv_GuiText displays text @ (x,y) wrapping as necessary. */
void tv_GuiText(unsigned x, unsigned y, const char *text, unsigned sz) {
	char c;
	GLint id;

	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	if (textProgram == 0) {
		return;
	}

	glUseProgram(textProgram);

	if (sz == 0 || sz > 128)
		sz = 32;

	for (c = *text; c != '\0'; c = *++text) {
		drawChar(c, x, y, sz);
		x += sz;
	}

	glUseProgram(id);
}

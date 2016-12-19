#include <stdbool.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "debug.h"
#include "draw.h"
#include "input.h"
#include "matrix.h"

#include "components/enum.h"

enum{
	MAX_MESHES = 10000
};

static SDL_Window *win; /* SDL window to render to. */
static SDL_GLContext *glCtx; /* OpenGL context. */

static struct Mat4x4 projMat; /* the projection matrix. */
static struct Mat4x4 mvMat;   /* the modelview matrix. */
static struct Mat4x4 mvpMat;  /* the main modelview-projection matrix. */
static struct Mat4x4 guiMat;  /* the mvp mat used for rendering the GUI. */

/* vertexShader is the vertex shader used for all rendering. */
GLchar const *vertexShader[] = {
	"#version 150\n"
		"in vec4 pos;\n"
		"in vec4 col;\n"
		"out vec4 out_col;\n"
		"uniform sampler2D tex;\n"
		"uniform mat4 mvp;\n"
		"void main()\n"
		"{\n"
		"  out_col = col;\n"
		"  gl_Position = mvp * pos;\n"
		"}\n"
};

/* fragmentShader is the fragment shader used for all rendering. */
GLchar const *fragmentShader[] = {
	"#version 150\n"
		"in vec4 out_col;\n"
		"out vec4 out_color;\n"
		"uniform sampler2D tex;\n"
		"void main()\n"
		"{\n"
		"  out_color = out_col;\n"
		"}\n"
};

/* loadedMeshes is a table of GL-state associated with all loaded meshes. */
/* XXX: should really be hash table, but until it's an issue... */
struct BufferedMesh{
	struct Mesh *mesh;
	GLuint vao;
	struct{
		GLuint pos, col;
	}buffs;
	struct{
		GLuint pos, col;
	}attrs;
}loadedMeshes[MAX_MESHES];

static GLuint program;  /* the shader program. */
static GLuint mvp;      /* the modelview matrix uniform handle. */

/* initShader compiles the shader used for all rendering in this engine. */
static bool initShader()
{
	GLint compiled, linked;
	GLuint fs, vs, gs;

	fs = 0;
	vs = 0;
	gs = 0;

	/* create shader program (if not already built) */
	if(program == 0){
		GLint len;
		/* vertex shader */
		vs = glCreateShader(GL_VERTEX_SHADER);
		len = strlen(vertexShader[0]);
		glShaderSource(vs, 1, vertexShader, &len);
		glCompileShader(vs);
		glGetShaderiv(vs, GL_COMPILE_STATUS, &compiled);
		if(compiled == GL_FALSE){
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
		len = strlen(fragmentShader[0]);
		glShaderSource(fs, 1, fragmentShader, &len);
		glCompileShader(fs);
		glGetShaderiv(fs, GL_COMPILE_STATUS, &compiled);
		if(compiled == GL_FALSE){
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
		program = glCreateProgram();
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if(linked == GL_FALSE){
			GLint logSz;
			GLchar *log;

			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSz);
			log = malloc(logSz * sizeof(GLchar));
			glGetProgramInfoLog(program, logSz, &logSz, log);
			debug_puts("error: shader program failed to link");
			debug_puts(log);
			free(log);
			return false;
		}
		/* get the modelview-projection matrix uniform */
		mvp = glGetUniformLocation(program, "mvp");
		if(mvp == -1){
			debug_puts("error: no \"mvp\" uniform found in shader program");
			return false;
		}
	}
	glUseProgram(program);
	return true;
}

/* tv_DrawInit initializes the rendering system. */
int tv_DrawInit()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		debug_printf("failed to initailize SDL. SDL_Error: %s\n", SDL_GetError());
		return -1;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	win = SDL_CreateWindow("evo2", SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, 640, 480,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if(win == NULL ){
		debug_printf("failed to create window. SDL_Error: %s\n", SDL_GetError());
		return -2;
	}
	glCtx = SDL_GL_CreateContext(win);
	if(glCtx == NULL){
		debug_puts("error: failed to create GL context");
		return -3;
	}
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK){
		debug_puts("error: failed to initialize GLEW");
		return -4;
	}
	if(!initShader()){
		debug_puts("error: shader");
		return -5;
	}
	glViewport(0,0,640,480);

	mat4x4_perspective(&projMat, 45.0f, 640.0f/480.0f, 0.01f, 100.0f);
	mat4x4_load_identity(&mvMat);
	mat4x4_translate(&mvMat, 0.0f, 0.0f, -6.0f);

	mat4x4_orthographic(&guiMat, 0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	return 0;
}

/* tv_DrawQuit deinitializes/frees resources used by the rendering system. */
void tv_DrawQuit()
{
	SDL_Quit();
}

/* tv_DrawStartFrame prepares for rendering a new frame. */
void tv_DrawStartFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*  tv_DrawEndFrame is called when all rendering for the current frame is done. */
void tv_DrawEndFrame()
{
	SDL_GL_SwapWindow(win);
}

/* bufferMesh creates and buffers the mesh data into VBO's. */
static struct BufferedMesh * bufferMesh(struct Mesh *mesh)
{
	int i;
	struct BufferedMesh *m;
	uint8_t *vb, *cb;

	for(i = 0; i < MAX_MESHES; ++i){
		if(loadedMeshes[i].mesh == NULL){
			m = loadedMeshes + i;
			break;
		}
	}
	if(i >= MAX_MESHES)
		return NULL;

	vb = mesh->buffers;
	cb = vb + sizeof(struct MeshAttr) * mesh->numVerts;

	glGenBuffers(1, &m->buffs.pos);
	glGenBuffers(1, &m->buffs.col);
	glBindBuffer(GL_ARRAY_BUFFER, m->buffs.pos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(struct MeshAttr) * mesh->numVerts,
			vb, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m->buffs.col);
	glBufferData(GL_ARRAY_BUFFER, sizeof(struct MeshAttr) * mesh->numVerts,
			cb, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m->vao);
	glBindVertexArray(m->vao);

	m->attrs.pos = glGetAttribLocation(program, "pos");
	if(m->attrs.pos == -1)
		debug_puts("error: could not find attribute \"pos\" in shader program.");
	m->attrs.col = glGetAttribLocation(program, "col");
	if(m->attrs.col == -1)
		debug_puts("error: could not find attribute \"col\" in shader program.");

	glBindVertexArray(0);
	m->mesh = mesh;
	return m;
}

/* getMesh retrieves mesh from the table of loaded meshes (if it exists). */
static struct BufferedMesh * getMesh(struct Mesh *mesh)
{
	int i;
	for(i = 0; i < MAX_MESHES; ++i){
		if(loadedMeshes[i].mesh == mesh)
			return loadedMeshes + i;
	}
	return NULL;
}

/* tv_Draw draws the given mesh with the given material. */
void tv_Draw(struct Mesh *mesh, struct Material *mat)
{
	struct BufferedMesh *m;

	m = getMesh(mesh);
	if(m == NULL)
		m = bufferMesh(mesh);
	if(m == NULL)
		return;

	mvpMat = mat4x4_multiply(projMat, mvMat);
	glUniformMatrix4fv(mvp, 1, GL_FALSE, mat4x4_to_array(&mvpMat));

	glBindVertexArray(m->vao);

	glEnableVertexAttribArray(m->attrs.pos);
	glBindBuffer(GL_ARRAY_BUFFER, m->buffs.pos);
	glVertexAttribPointer(m->attrs.pos, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);

	glEnableVertexAttribArray(m->attrs.col);
	glBindBuffer(GL_ARRAY_BUFFER, m->buffs.col);
	glVertexAttribPointer(m->attrs.col, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, m->mesh->numVerts);
	glBindVertexArray(0);
}

/* tv_DrawModelview sets the modelview matrix to render with. */
void tv_DrawModelview(struct Mat4x4* mv)
{
	mvMat = *mv;
}

/* tv_InputInit initializes the engine for receiving/dispatching user input. */
void tv_InputInit()
{
	SDL_SetRelativeMouseMode(true);
}

/* tv_InputUpdate polls input device(s) and emits input events. */
void tv_InputUpdate()
{
	SDL_Event evt;
	int xrel, yrel;

	while(SDL_PollEvent(&evt)){
		switch(evt.type){
			case SDL_QUIT:
				EMIT(Kill)
				break;
			case SDL_KEYDOWN:
				if(evt.key.keysym.sym == SDLK_ESCAPE)
					EMIT(Kill)
				else
					EMIT(ButtonDown, evt.key.keysym.scancode)
				break;
			case SDL_KEYUP:
				EMIT(ButtonUp, evt.key.keysym.scancode)
				break;
			default:
				break;
		}
		SDL_GetRelativeMouseState(&xrel, &yrel);
		if(xrel != 0)
			EMIT(AxisMoved, TV_INPUT_AXIS0, xrel)
			if(yrel != 0)
				EMIT(AxisMoved, TV_INPUT_AXIS1, yrel)
	}
}

/* tv_GuiRect draws a w x h rectangle @ (x,y). */
void tv_GuiRect(unsigned x, unsigned y, unsigned w, unsigned h, uint32_t rgba)
{
	static GLuint vao;
	static struct {
		GLuint col, pos;
	}buffs;
	static struct {
		GLuint col, pos;
	}attrs;
	uint8_t r = (rgba & 0xff000000) >> 24;
	uint8_t g = (rgba & 0x00ff0000) >> 16;
	uint8_t b = (rgba & 0x0000ff00) >> 8;
	uint8_t a = (rgba & 0x000000ff);
	uint8_t c[] = {
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
	};
	uint16_t v[] = {
		x,y,1,1,
		x+w,y,1,1,
		x+w,y+h,1,1,
		x,y,1,1,
		x+w,y+h,1,1,
		x,y+h,1,1
	};

	if(vao == 0){
		glGenBuffers(1, &buffs.pos);
		glGenBuffers(1, &buffs.col);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		attrs.pos = glGetAttribLocation(program, "pos");
		if(attrs.pos == -1)
			debug_puts("error: could not find attribute \"pos\" in shader program.");
		attrs.col = glGetAttribLocation(program, "col");
		if(attrs.col == -1)
			debug_puts("error: could not find attribute \"col\" in shader program.");
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

/* tv_GuiText displays text @ (x,y) wrapping as necessary. */
void tv_GuiText(unsigned x, unsigned y, const char *text)
{
	static struct tv_Entity *glyph;
	static struct Mesh *mesh;
	static struct Material *material;
	struct MeshTexco *texcos;
	unsigned i;

#if 0
	if(glyph == NULL){
		struct Mesh m;
		m = MeshNewQuad();
		glyph = tv_EntityNew(1,
			COMPONENT_MESH, &mesh);
		glyph->start(glyph);
		mesh = (struct Mesh*)tv_EntityGetComponent(glyph,
				COMPONENT_MESH);
		material = (struct Material*)tv_EntityGetComponent(glyph,
				COMPONENT_MATERIAL);
	}
#endif
	texcos = (struct MeshTexco*)MeshGetBuffer(mesh, 1);
	for(i = 0; i < strlen(text); ++i){
		texcos->u = 0;
		texcos->v = 0;
		texcos->u = 0xffff;
		texcos->v = 0;
		texcos->u = 0xffff;
		texcos->v = 0xffff;

		texcos->u = 0;
		texcos->v = 0;
		texcos->u = 0xffff;
		texcos->v = 0xffff;
		texcos->u = 0;
		texcos->v = 0xffff;
	}
	tv_Draw(mesh, material);
}

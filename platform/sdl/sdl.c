#include <stdbool.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "debug.h"
#include "draw.h"
#include "matrix.h"

static SDL_Window *win; /* SDL window to render to. */
static SDL_GLContext *glCtx; /* OpenGL context. */
static struct Mat4x4 mvpMat; /* the main modelview-projection matrix to render with. */

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

  mat4x4_perspective(&mvpMat, 45.0f, 640.0f/480.0f, 0.01f, 100.0f);
  mat4x4_translate(&mvpMat, 0.0f, 0.0f, -6.0f);
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
  glClear(GL_COLOR_BUFFER_BIT);
}

/*  tv_DrawEndFrame is called when all rendering for the current frame is done. */
void tv_DrawEndFrame()
{
  SDL_GL_SwapWindow(win);
}

/* tv_Draw draws the given mesh with the given material. */
void tv_Draw(struct Mesh *mesh, struct Material *mat)
{
  struct{
    GLuint pos, col;
  }buffs;
  struct{
    GLuint pos, col;
  }attrs;
  uint8_t *vb, *cb;
  GLuint vao;

  vb = mesh->buffers;
  cb = vb + sizeof(struct MeshAttr) * mesh->numVerts;
 
  //XXX: store vbo's in table (don't rebuffer each frame)
  glGenBuffers(1, &buffs.pos);
  glGenBuffers(1, &buffs.col);
  glBindBuffer(GL_ARRAY_BUFFER, buffs.pos);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct MeshAttr) * mesh->numVerts,
      vb, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, buffs.col);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct MeshAttr) * mesh->numVerts,
      cb, GL_STATIC_DRAW);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  //XXX: same with attributes
  attrs.pos = glGetAttribLocation(program, "pos");
  if(attrs.pos == -1)
    debug_puts("error: could not find attribute \"pos\" in shader program.");
  attrs.col = glGetAttribLocation(program, "col");
  if(attrs.col == -1)
    debug_puts("error: could not find attribute \"col\" in shader program.");

  glUniformMatrix4fv(mvp, 1, GL_FALSE, mat4x4_to_array(&mvpMat));
  glEnableVertexAttribArray(attrs.pos);
  glBindBuffer(GL_ARRAY_BUFFER, buffs.pos);
  glVertexAttribPointer(attrs.pos, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);

  glEnableVertexAttribArray(attrs.col);
  glBindBuffer(GL_ARRAY_BUFFER, buffs.col);
  glVertexAttribPointer(attrs.col, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);

  glDrawArrays(GL_TRIANGLES, 0, mesh->numVerts);
  glBindVertexArray(0);

  glDeleteBuffers(1, &buffs.pos);
  glDeleteBuffers(1, &buffs.col);
  glDeleteVertexArrays(1, &vao);
}

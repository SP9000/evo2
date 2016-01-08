#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "debug.h"
#include "draw.h"

static SDL_Window *win;
static SDL_GLContext *glCtx;

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

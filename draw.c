#include "draw.h"

static SDL_Window *win;
static SDL_Renderer *renderer;

int tv_DrawInit()
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("failed to initailize SDL. SDL_Error: %s\n", SDL_GetError());
    return -1;
  }
  win = SDL_CreateWindow("evo2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );
  if(win == NULL )
  {
    printf("failed to create window. SDL_Error: %s\n", SDL_GetError());
    return -2;
  }
  renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
  if(renderer == NULL )
  {
    printf("failed to create renderer. SDL_Error: %s\n", SDL_GetError());
    return -3;
  }
  return 0;
}

void tv_DrawQuit()
{
  SDL_Quit();
}

void tv_DrawStartFrame()
{
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
  SDL_RenderClear(renderer);
}

void tv_DrawEndFrame()
{
  SDL_RenderPresent(renderer);
}

SDL_Renderer * tv_DrawGetRenderer()
{
  return renderer;
}

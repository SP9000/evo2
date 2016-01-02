#include <SDL2/SDL.h>
#include "draw.h"
#include "engine.h"
#include "entity.h"

static bool run = true;

int tv_EngineInit()
{
  tv_DrawInit();
  return 0;
}

void tv_EngineTick()
{
  SDL_Event e;

  if(run == false) 
  {
    return;
  }

  tv_DrawStartFrame();
  while(SDL_PollEvent(&e)) 
  {
    switch(e.type)
    {
    case SDL_QUIT:
      run = false;
    }
  }
  /* TODO: update systems */
  tv_DrawEndFrame();
}

void tv_EngineRun()
{
  run = true;
  while(run)
  {
    tv_EngineTick();
  }
}

bool tv_EngineRunning()
{
  return run;
}

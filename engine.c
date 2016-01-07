#include <SDL2/SDL.h>
#include "draw.h"
#include "engine.h"
#include "entity.h"

static bool run;

/* tv_EngineInit initializes the engine.  Call before running the engine. */
int tv_EngineInit()
{
  tv_DrawInit();
  return 0;
}

/* tv_EngineTick runs one "tick" of the engine by updating all the engine's
 * systems and updating all entities.
 */
void tv_EngineTick()
{
  SDL_Event e;

  if(run == false) {
    return;
  }
  tv_DrawStartFrame();
  while(SDL_PollEvent(&e)){
    switch(e.type){
    case SDL_QUIT:
      run = false;
    }
  }
  /* TODO: update systems */
  tv_DrawEndFrame();
}

/* tv_EngineRun runs the engine until it is terminated. */
void tv_EngineRun()
{
  run = true;
  while(run){
    tv_EngineTick();
  }
}

/* tv_EngineRunning returns true if the engine is currently running. */
bool tv_EngineRunning()
{
  return run;
}

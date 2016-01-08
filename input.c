#include <SDL2/SDL.h>
#include "sigslot.h"
#include "input.h"

SIGDEF(ButtonDown)
SIGDEF(ButtonUp)
SIGDEF(MouseMove)
SIGDEF(Kill)

/* Update polls for input and stores the input state for the current frame */
void tv_InputUpdate()
{
  SDL_Event evt;
  while(SDL_PollEvent(&evt)){
    switch(evt.type){
    case SDL_QUIT:
      EMIT(Kill)
      break;
    case SDL_KEYDOWN:
      EMIT(ButtonDown, evt.key.keysym.scancode);
      break;
    case SDL_KEYUP:
      EMIT(ButtonUp, evt.key.keysym.scancode);
      break;
    case SDL_MOUSEMOTION:
      EMIT(MouseMove, evt.motion.x, evt.motion.y);
      break;
    default:
      break;
    }
  }
}

/* tv_InputInit initializes the engine for receiving/dispatching user input. */
void tv_InputInit()
{
}


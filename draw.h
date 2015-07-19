#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>

/**
 * tv_DrawInit initializes the rendering system. 
 */
int tv_DrawInit();

/**
 * tv_DrawQuit deinitializes/frees resources used by the rendering system.
 */
void tv_DrawQuit();

/**
 * tv_DrawStartFrame prepares for rendering a new frame.
 */
void tv_DrawStartFrame();

/**
 * tv_DrawEndFrame is called when all rendering for the current frame is done.
 */
void tv_DrawEndFrame();

/**
 * tv_DrawGetRenderer returns the renderer that is associated with the engine's
 * window.
 */
SDL_Renderer * tv_DrawGetRenderer();

#endif

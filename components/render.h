#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "../entity.h"
#include "transform.h"

struct Spritesheet 
{
  int  xStep, yStep; /* the spacing between each tile. */
  int  w, h;         /* the width/height of the spritesheet */
  char name[31] ;    /* the name the spritesheet is loaded from */
  SDL_Texture *tex;
};

/**
 * Render is a component used to draw anything.
 * 
 */
struct Render 
{
  struct tv_Component co;
  struct Spritesheet *sheet;
  struct Transform *transform;
  int    tileID; 
};

/**
 * RenderNew creates a new Render component that clips sprites from the file
 * spritesheet.
 */
struct Render * NewRender();

#endif

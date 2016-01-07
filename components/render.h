#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <OpenGL/gl.h>
#include "../entity.h"
#include "transform.h"

/* tv_Material contains OpenGL handles for the shader program to render with. */
struct tv_Material
{
  GLuint fs, vs, gs;
  GLuint vbo;
  GLuint mvp;
};

/* Render is a component used to draw anything. */
struct Render 
{
  struct tv_Component co;
  struct Transform *transform;
  int    tileID; 
};

/* NewRender creates a new Render component. */
struct Render * NewRender();


#endif

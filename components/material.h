#ifndef MATERIAL_H
#define MATERIAL_H

#include "entity.h"
#include "vector.h"

/* Texture is a structure that holds info about a material's texture. */
struct Texture{
  uint32_t handle;  /* handle assigned to loaded textures. */
};

/* Material is a component that contains OpenGL handles for rendering. */
struct Material{
  TV_COMPONENT
  uint32_t ambient;
  uint32_t diffuse;
  uint32_t specularity;
  uint32_t shininess;
  struct Texture tex;
};

struct Material NewMaterial(uint32_t, uint32_t, uint32_t, uint32_t);

#endif

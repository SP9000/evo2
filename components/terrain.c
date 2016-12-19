#include "terrain.h"

struct Terrain NewTerrain(int w, int h)
{
  struct Terrain t = {
    .C = {
      .size = sizeof(struct Terrain)
    },
    .w = w,
    .h = h
  };
  return t;
}


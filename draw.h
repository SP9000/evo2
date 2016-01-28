#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>
#include "components/material.h"
#include "components/mesh.h"
#include "matrix.h"

int tv_DrawInit();
void tv_DrawQuit();
void tv_DrawStartFrame();
void tv_DrawEndFrame();
void tv_Draw(struct Mesh*, struct Material*);
void tv_DrawModelview(struct Mat4x4*);

#endif

#ifndef DRAW_H
#define DRAW_H

#include "components/cam.h"
#include "components/material.h"
#include "components/mesh.h"
#include "components/transform.h"
#include "matrix.h"
#include <SDL2/SDL.h>

int tv_DrawInit();
void tv_DrawQuit();
void tv_DrawStartFrame();
void tv_DrawEndFrame();
void tv_Draw(struct Cam *, struct Mesh *, struct Material *);
void tv_DrawModelview(struct Mat4x4 *);

#endif

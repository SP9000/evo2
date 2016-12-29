#ifndef SCENE_H
#define SCENE_H

#include "entity.h"
#include "vector.h"

enum { SCENE_MAX_RAYCAST_HITS = 32,
};

void tv_SceneAdd(struct tv_Entity *);
void tv_SceneRemove(struct tv_Entity *);
bool tv_SceneRaycast(tv_Vector3, tv_Vector3, struct tv_Entity **);

#ifdef DEBUG_H
void tv_ScenePrint();
#endif

#endif

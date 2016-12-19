#ifndef SCENE_H
#define SCENE_H

#include "entity.h"

void tv_SceneAdd(struct tv_Entity*);
void tv_SceneRemove(struct tv_Entity*);

#ifdef DEBUG_H
void tv_ScenePrint();
#endif

#endif

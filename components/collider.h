#ifndef COLLIDER_H
#define COLLIDER_H

#include "entity.h"
#include <stdbool.h>
#include <stdint.h>

/* Collider is a component that is used to check collision. */
struct Collider {
	uint16_t radius;
};

bool ColliderOverlaps(struct tv_Entity *, struct tv_Entity *);
bool ColliderContains(struct tv_Entity *, struct tv_Entity *);

#endif

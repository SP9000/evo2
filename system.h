#ifndef SYSTEM_H
#define SYSTEM_H

#define TV_MAX_SYSTEMS 1024

#include <stdbool.h>
#include "entity.h"

/**
 * tv_System is a struct containing the information of a "system".
 * A system iterates through each entity, operating on each entity that 
 * contains a particular component.
 */
struct tv_System{
  bool enabled;
  void (*Update)(struct tv_Entity*);     /* updates an entity per-frame. */
  bool (*Implements)(struct tv_Entity*); /* true- entity implements system */
};

void tv_RegisterSystem(struct tv_System *sys);
void tv_UpdateSystems();

#endif

#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>
#include <stdlib.h>

/* tv_Component is a container for data used by systems */
struct tv_Component
{
  unsigned id;                          /* id is a unique ID used to refer to this component. */
  struct tv_Entity *entity;             /* entity is the entity the component is attached to. */
  size_t (*Size)();                     /* Size returns the size (in bytes) of the component. */
  void (*Start)(struct tv_Component*);  /* Start initializes a component (run before update). */
};

/* tv_Entity is the basic container of all entities in the engine. */
struct tv_Entity 
{
  unsigned _numComponents;  

  char name[31];  /** a unique name used to refer to this entity */
  struct tv_Component *components[];  /** the components that make up this entity. */
};

struct tv_Entity * tv_EntityNew(const char*);
void tv_EntityDestroy(struct tv_Entity*);
struct tv_Entity * tv_EntityCopy(struct tv_Entity*);
void tv_EntityAdd(struct tv_Entity**, struct tv_Component*);
void tv_EntityRemove(struct tv_Entity**, struct tv_Component*);
void tv_EntityStart(struct tv_Entity*);
void tv_EntityUpdateAll(bool (*test)(struct tv_Entity*),
    void (*update)(struct tv_Entity*));
unsigned tv_EntityNumComponents(struct tv_Entity*);
struct tv_Component * tv_EntityGetComponent(struct tv_Entity*, unsigned id);

#endif

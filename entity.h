#ifndef ENTITY_H
#define ENTITY_H

#include <stdlib.h>

/**
 * tv_Component is the basic unit of all "components"- the building blocks of 
 * every entity.
 */
struct tv_Component
{
  unsigned id;                          /* id is a unique ID used to refer to this component. */
  struct tv_Entity *entity;             /* entity is the entity the component is attached to. */
  size_t (*Size)();                     /* Size returns the size (in bytes) of the component. */
  void (*Start)(struct tv_Component*);  /* Start initializes a component (run before update). */
  void (*Update)(struct tv_Component*); /* Update runs a per-frame update on the component. */
};

/** 
 * tv_Entity is the basic container of all entities in the engine. 
 */
struct tv_Entity 
{
  unsigned _numComponents;  

  char name[31];  /** a unique name used to refer to this entity */
  struct tv_Component *components[];  /** the components that make up this entity. */
};

/**
 * tv_EntityNew creates a new entity named name.
 */
struct tv_Entity * tv_EntityNew(const char *name);

/**
 * tv_EntityDestroy destroys an entity and all its components.
 */
void tv_EntityDestroy(struct tv_Entity *e);

/**
 * tv_EntityCopy performs a deep copy of e and returns a pointer to the copy.
 */
struct tv_Entity * tv_EntityCopy(struct tv_Entity* e);

/**
 * tv_EntityAdd attaches the component c to e.
 */
void tv_EntityAdd(struct tv_Entity **e, struct tv_Component *c);

/**
 * tv_EntityRemove removes the component c from e.
 */
void tv_EntityRemove(struct tv_Entity **e, struct tv_Component *c);

/**
 * tv_EntityStart initializes an entity by "Start"ing all the components
 * attached to e.
 */
void tv_EntityStart(struct tv_Entity *e);

/**
 * tv_EntityUpdate updates an entity by "Update"ing all the components
 * attached to e.
 */
void tv_EntityUpdate(struct tv_Entity *e);

/**
 * tv_EntityUpdateAll updates all entities that have been created with 
 * tv_EntityNew.
 */
void tv_EntityUpdateAll();

/**
 * tv_EntityGetComponent searches e for a component of the type id.
 */
struct tv_Component * tv_EntityGetComponent(struct tv_Entity *e, unsigned id);

#endif

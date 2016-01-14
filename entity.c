#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "components/enum.h"
#include "entity.h"
#include "system.h"

#define MAX_ENTITIES 10000

static struct tv_Entity *entities[MAX_ENTITIES];
static int numentities;

/* entitysize returns the size of e in bytes. */
static int entitysize(struct tv_Entity *e)
{
  int i, size;
  for(i = 0, size = 0; i < TV_ENTITY_MAX_COMPONENTS; ++i){
    if(e->components[i] == COMPONENT_END)
      break;
    size += ((struct tv_Component*)(e->data + size))->size;
  }
  return size + sizeof(struct tv_Entity);
}

/* tv_EntityNew copies e into the engine. */
struct tv_Entity * tv_EntityNew(struct tv_Entity *e)
{
  int size;
  struct tv_Entity *ret;

  size = entitysize(e);
  ret = malloc(size);
  memcpy(ret, e, size);
  entities[numentities] = ret;
  numentities++;
  return ret;
}

/* tv_EntityDestroy destroys an entity and all its components. */
void tv_EntityDestroy(struct tv_Entity *e)
{
  int i;
  for(i = numentities-1; i >= 0; --i){
    if(entities[i] == e){
      entities[i] = NULL;
      numentities--;
      free(e);
      break;
    }
  }
}

/* tv_EntityAdd attaches the component c to e and initializes c. */
struct tv_Entity * tv_EntityAdd(struct tv_Entity *e, uint16_t id,
    struct tv_Component *c)
{
  int i;

  for(i = 0; i < TV_ENTITY_MAX_COMPONENTS; ++i){
    if(e->components[i] == COMPONENT_END){
      uint16_t newsize;
      newsize = entitysize(e) + c->size;

      e->components[i] = id;
      e = realloc(e, newsize);
      memcpy(e->data + newsize, c, c->size);
      c->init(e->data + newsize);
      break;
    }
  }
  return e;
}

/* tv_EntityRemove removes the component of type id from e. */
struct tv_Entity * tv_EntityRemove(struct tv_Entity *e, uint16_t id)
{
  unsigned i;
  bool found;
  for(i = 0, found = false; i < TV_ENTITY_MAX_COMPONENTS; ++i){
    if(found && i < TV_ENTITY_MAX_COMPONENTS-1)
      e->components[i] = e->components[i+1];
    else if(found)
      e->components[i] = COMPONENT_END;
    else if(e->components[i] == id)
      found = true;
  }
  if(i < TV_ENTITY_MAX_COMPONENTS){
    uint16_t newsize;
    newsize = entitysize(e);
    e = realloc(e, newsize);
  }
  return e;
}

/* tv_EntityStartAll runs start on all entities for which test is true. */
void tv_EntityStartAll(bool (*test)(struct tv_Entity*), 
    void (*start)(struct tv_Entity *))
{
  unsigned i;
  for(i = 0; i < numentities; ++i){
    if(test(entities[i]))
      start(entities[i]);
  }
}

/* tv_EntityUpdateAll runs update on all entities for which test is true. */
void tv_EntityUpdateAll(bool (*test)(struct tv_Entity*), 
    void (*update)(struct tv_Entity *), struct tv_Entity **cache)
{
  unsigned i, updated;

  for(i = 0; i < TV_SYSTEM_CACHE_SIZE; ++i){
    if(cache[i] == NULL)
      break;
    update(cache[i]);
  }

  for(i = 0, updated = 0; i < numentities; ++i){
    if(test(entities[i])){
      update(entities[i]);
      if(updated < TV_SYSTEM_CACHE_SIZE)
        cache[updated++] = entities[i];
    }
  }
  if(updated < TV_SYSTEM_CACHE_SIZE)
    cache[updated] = NULL;
}

/* tv_EntityGetComponent returns e's component of type id - NULL if none. */
struct tv_Component * tv_EntityGetComponent(struct tv_Entity *e, uint16_t id)
{
  unsigned i, offset;
  for(i = 0, offset = 0; i < TV_ENTITY_MAX_COMPONENTS; ++i)
  {
    if(e->components[i] == id)
      return (struct tv_Component*)(e->data + offset);
    offset += ((struct tv_Component*)(e->data + offset))->size;
  }
  return NULL;
}

/* tv_EntityNumComponents returns the number of components attached to e. */
unsigned tv_EntityNumComponents(struct tv_Entity *e)
{
  unsigned i;
  for(i = 0; i < TV_ENTITY_MAX_COMPONENTS; ++i){
    if(e->components[i] == TV_ENTITY_MAX_COMPONENTS)
      return i;
  }
  return TV_ENTITY_MAX_COMPONENTS;
}

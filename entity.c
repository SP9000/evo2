#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "components/enum.h"
#include "entity.h"
#include "system.h"

#define MAX_ENTITIES 10000

static struct tv_Entity *entities[MAX_ENTITIES];
static int numentities;

/* tv_EntityNew copies e into the engine. */
struct tv_Entity * tv_EntityNew(int count, ...)
{
  struct tv_Entity *e;
  int i, numComponents, size;
  va_list ap;

  uint16_t ids[TV_ENTITY_MAX_COMPONENTS] = {};
  struct tv_Component *components[TV_ENTITY_MAX_COMPONENTS];

  /* get components and total entity size */
  va_start(ap, count);
  for (i = 0, size = 0; i < count; ++i){
    ids[i] = (uint16_t)va_arg(ap, int);
    components[i] = va_arg(ap, struct tv_Component*);
    size += components[i]->size;
  }
  va_end(ap);
  numComponents = i;

  /* allocate entity and copy/init component data */
  e = malloc(size + sizeof(struct tv_Entity));
  memcpy(e->components, ids, sizeof(ids));
  for(i = 0, size = 0; i < numComponents; ++i){
    struct tv_Component *c;
    c = (struct tv_Component*)(e->data + size);
    memcpy(c, components[i], components[i]->size);
    if(c->init != NULL)
      c->init(c);
    size += components[i]->size;
  }
  entities[numentities] = e;
  numentities++;
  return e;
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

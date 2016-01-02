#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "entity.h"

#define MAX_ENTITIES 10000

static struct tv_Entity *entities[MAX_ENTITIES];
static int numEntities;

struct tv_Entity * tv_EntityNew(const char *name)
{
  struct tv_Entity *e = (struct tv_Entity*)malloc(sizeof(struct tv_Entity));
  strncpy(e->name, name, 31);
  e->_numComponents = 0;

  entities[numEntities] = e;
  numEntities++;

  return e;
}

void tv_EntityDestroy(struct tv_Entity *e)
{
  int i;
  for(i = numEntities-1; i >= 0; --i)
  {
    if(entities[i] == e)
    {
      entities[i] = NULL;
      numEntities--;
    }
  }
}

void tv_EntityAdd(struct tv_Entity **e, struct tv_Component *c)
{
  (*e) = realloc(*e, sizeof(struct tv_Entity) + sizeof(struct tv_Component*) * ((*e)->_numComponents + 1));
  (*e)->components[(*e)->_numComponents] = c;
  (*e)->_numComponents++;
}

void tv_EntityRemove(struct tv_Entity **e, struct tv_Component *c)
{
  unsigned i, end;
  bool found;

  end = (*e)->_numComponents;
  for(i = 0, found = false; i < end; ++i) 
  {
    if(found || (*e)->components[i] == c) 
    {
      found = true;
      if(i < end) 
      {
        (*e)->components[i] = (*e)->components[i+1];
      }
    }
  }
  if(found)
  {
    *e = realloc(*e, sizeof(struct tv_Entity) + sizeof(struct tv_Component) * ((*e)->_numComponents - 1));
    (*e)->_numComponents--;
  }
}

void tv_EntityStart(struct tv_Entity *e)
{
  unsigned i;

  for(i = 0; i < e->_numComponents; ++i) 
  {
    struct tv_Component *c = e->components[i];

    c->entity = e;
    if(c->Start)
    {
      c->Start(c);
    }
  }
}

void tv_EntityUpdateAll(bool (*test)(struct tv_Entity*), 
    void (*update)(struct tv_Entity *))
{
  unsigned i;

  for(i = 0; i < numEntities; ++i)
  {
    if(test(entities[i]))
    {
      update(entities[i]);
    }
  }
}

struct tv_Entity * tv_EntityCopy(struct tv_Entity *e)
{
  unsigned i;
  struct tv_Entity* ret;

  ret = malloc(sizeof(struct tv_Entity));
  for(i = 0; i < e->_numComponents; ++i) 
  {
    ret->components[i] = malloc(e->components[i]->Size());
  }
  return ret;
}

struct tv_Component * tv_EntityGetComponent(struct tv_Entity *e, unsigned id)
{
  unsigned i;
  for(i = 0; i < e->_numComponents; ++i)
  {
    if(e->components[i]->id == id)
    {
      return e->components[i];
    }
  }
  return NULL;
}


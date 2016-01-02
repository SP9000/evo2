#include <stdbool.h>
#include "test.h"
#include "../entity.h"
#include "../systems/sys_render.h"

enum
{
  COMPONENT_COMPONENTA = 1,
  COMPONENT_COMPONENTB
};


struct SystemA
{
  struct tv_System sys;
};
static bool ImplementsA(struct tv_Entity *e)
{
  return tv_EntityGetComponent(e, COMPONENT_COMPONENTA) != NULL;
}
static void UpdateA(struct tv_Entity *e)
{
  puts(" updating A");
}
struct SystemA * NewSysA()
{
  struct tv_System *sys;
  sys = malloc(sizeof(struct SystemA));
  sys->Implements = ImplementsA;
  sys->Update = UpdateA;
  return sys;
}

static void StartA(struct tv_Component *c)
{
  puts(" starting A");
}
struct ComponentA
{
  struct tv_Component c;
  int val;
};
static size_t SizeA()
{
  return sizeof(struct ComponentA);
}
struct ComponentA * NewA() 
{
  struct ComponentA * a;
  struct tv_Component * c;

  a = malloc(sizeof(struct ComponentA));
  c = (struct tv_Component*)a;

  c->id = COMPONENT_COMPONENTA;
  c->Start = StartA;
  c->Size = SizeA;
  return a;
}

/* b is a simple component for testing. */
struct ComponentB
{
  struct tv_Component c;
  int val;
};
static void StartB(struct tv_Component *c)
{
  puts(" starting B");
}
static size_t SizeB()
{
  return sizeof(struct ComponentB);
}
struct ComponentB * NewB() 
{
  struct ComponentB * b;
  struct tv_Component * c;

  b = malloc(sizeof(struct ComponentB));
  c = (struct tv_Component*)b;

  c->id = COMPONENT_COMPONENTB;
  c->Start = StartB;
  c->Size = SizeB;
  return b;
}

/* TestEntity tests the creation of an entity as well as the attachment, 
 * removal, and usage of components to it.
 */
bool TestEntity() 
{
  struct tv_Entity *e;
  struct ComponentA *a;
  struct ComponentB *b;

  puts("creating components...");
  a = NewA();
  b = NewB();

  puts("creating systems...");
  tv_RegisterSystem(NewSysA());

  puts("creating entity...");
  e = tv_EntityNew("dog");

  puts("");

  puts("adding components...");
  tv_EntityAdd(&e, (struct tv_Component*)a);
  tv_EntityAdd(&e, (struct tv_Component*)b);
  puts("starting...");
  tv_EntityStart(e);
  puts("updating...");
  tv_UpdateSystems();
  puts("");

  puts("removing components...");
  tv_EntityRemove(&e, (struct tv_Component*)a);
  tv_EntityRemove(&e, (struct tv_Component*)b);
  puts("starting...");
  tv_EntityStart(e);
  puts("updating...");
  tv_UpdateSystems();
  puts("");

  puts("done");
  return true;
}

#include <stdbool.h>
#include "test.h"
#include "../entity.h"

static void UpdateA(struct tv_Component *c)
{
  printf(" updating A (id: %d)\n", c->id);
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
  static unsigned id = 0;
  struct ComponentA * a;
  struct tv_Component * c;

  tv_ComponentGenerateID(&id);
  a = malloc(sizeof(struct ComponentA));
  c = (struct tv_Component*)a;
  c->id = id;
  c->Start = StartA;
  c->Update = UpdateA;
  c->Size = SizeA;
  return a;
}

/* b is a simple component for testing. */
struct ComponentB
{
  struct tv_Component c;
  int val;
};
static void UpdateB(struct tv_Component *c)
{
  printf(" updating B (id: %d)\n", c->id);
}
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
  static unsigned id = 0;
  struct ComponentB * b;
  struct tv_Component * c;

  b = malloc(sizeof(struct ComponentB));
  c = (struct tv_Component*)b;

  tv_ComponentGenerateID(&id);
  c->id = id;
  c->Start = StartB;
  c->Update = UpdateB;
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

  puts("creating entity...");
  e = tv_EntityNew("dog");

  puts("");

  puts("adding components...");
  tv_EntityAdd(&e, (struct tv_Component*)a);
  tv_EntityAdd(&e, (struct tv_Component*)b);
  puts("starting...");
  tv_EntityStart(e);
  puts("updating...");
  tv_EntityUpdate(e);
  puts("");

  puts("removing components...");
  tv_EntityRemove(&e, (struct tv_Component*)a);
  tv_EntityRemove(&e, (struct tv_Component*)b);
  puts("starting...");
  tv_EntityStart(e);
  puts("updating...");
  tv_EntityUpdate(e);

  puts("");

  puts("done");
  return true;
}

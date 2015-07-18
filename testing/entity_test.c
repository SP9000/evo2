#include <stdbool.h>
#include "test.h"
#include "../entity.h"

/* a is a simple component for testing. */
static void UpdateA()
{
  puts(" updating A");
}
static void StartA()
{
  puts(" starting A");
}
struct ComponentA
{
  struct tv_Component c;
  int val;
} a;

/* b is a simple component for testing. */
struct ComponentB
{
  struct tv_Component c;
  int val;
} b;
static void UpdateB()
{
  puts(" updating B");
}
static void StartB()
{
  puts(" starting B");
}

/* TestEntity tests the creation of an entity as well as the attachment, 
 * removal, and usage of components to it.
 */
bool TestEntity() 
{
  struct tv_Entity *e;
  a.c.Start = StartA;
  a.c.Update = UpdateA;
  b.c.Start = StartB;
  b.c.Update = UpdateB;

  puts("creating entity...");
  e = tv_EntityNew("dog");

  puts("");

  puts("adding components...");
  tv_EntityAdd(&e, (struct tv_Component*)&a);
  tv_EntityAdd(&e, (struct tv_Component*)&b);
  puts("starting...");
  tv_EntityStart(e);
  puts("updating...");
  tv_EntityUpdate(e);
  puts("");

  puts("removing components...");
  tv_EntityRemove(&e, (struct tv_Component*)&a);
  tv_EntityRemove(&e, (struct tv_Component*)&b);
  puts("starting...");
  tv_EntityStart(e);
  puts("updating...");
  tv_EntityUpdate(e);

  puts("");

  puts("done");
  return true;
}

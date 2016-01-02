#include <stdio.h>
#include "../components/transform.h"
#include "../components/render.h"
#include "../draw.h"

void Setup()
{
  tv_DrawInit();
}

/**
 * TestComponents tests various components by adding them to an entity and
 * simulating their usage.
 */
void TestComponents()
{
  struct tv_Entity *e;
  struct Transform *transform;
  struct Render *render;

  e = tv_EntityNew("test");
  transform = NewTransform();
  render = NewRender();

  tv_EntityAdd(&e, (struct tv_Component*)transform);
  tv_EntityAdd(&e, (struct tv_Component*)render);

  /* simulate one game-tick */
  tv_EntityStart(e);

  tv_DrawStartFrame();
  tv_DrawEndFrame();

  puts("\ndone");
}



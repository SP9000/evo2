#include <assert.h>
#include <string.h>
#include "enum.h"
#include "render.h"
#include "../draw.h"

static size_t Size()
{
  return sizeof(struct Render);
}

struct Render * NewRender()
{
  struct Render *r;
  struct tv_Component *c;

  r = malloc(sizeof(struct Render));
  c = (struct tv_Component*)r;

  c->id     = COMPONENT_RENDER;
  c->Size   = Size;
  return r;
}


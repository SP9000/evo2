#include "../components/enum.h"
#include "../components/render.h"
#include "../components/transform.h"
#include "sys_render.h"

static bool Implements(struct tv_Entity *e)
{
  return tv_EntityGetComponent(e, COMPONENT_RENDER) != NULL &&
    tv_EntityGetComponent(e, COMPONENT_TRANSFORM) != NULL;
}

/* TODO: actually do what this should do*/
static void Update(struct tv_Entity *e)
{
  struct Render *r;
  SDL_Rect renderQuad;
  r = (struct Render*)tv_EntityGetComponent(e, COMPONENT_RENDER);
}

struct sys_Render * NewRenderSystem()
{
  struct tv_System *sys;
  sys = malloc(sizeof(struct sys_Render));
  sys->Implements = Implements;
  sys->Update = Update;
  return sys;
}


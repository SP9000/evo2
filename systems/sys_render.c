#include "../components/enum.h"
#include "../components/render.h"
#include "../components/transform.h"
#include "sys_render.h"

static bool Implements(struct tv_Entity *e)
{
  return tv_EntityGetComponent(e, COMPONENT_RENDER) != NULL &&
    tv_EntityGetComponent(e, COMPONENT_TRANSFORM) != NULL;
}

/* TODO: for now, Update just renders a rectangle. */
static void Update(struct tv_Entity *e)
{
  struct Render *r;
  SDL_Rect renderQuad;
  
  r = (struct Render*)tv_EntityGetComponent(e, COMPONENT_RENDER);

  renderQuad.x = 0;
  renderQuad.y = 0;
  renderQuad.w = r->transform->scale.x * 32;
  renderQuad.h = r->transform->scale.y * 32;
  
  SDL_SetRenderDrawColor(tv_DrawGetRenderer(), 255, 255, 0, 255);
  SDL_RenderFillRect(tv_DrawGetRenderer(), &renderQuad);
}

static size_t Size()
{
  return sizeof(struct Render);
}

struct sys_Render * NewRenderSystem()
{
  struct tv_System *sys;
  sys = malloc(sizeof(struct sys_Render));
  sys->Implements = Implements;
  sys->Update = Update;
  return sys;
}


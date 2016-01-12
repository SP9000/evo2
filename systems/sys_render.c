#include "components/enum.h"
#include "components/transform.h"
#include "components/material.h"
#include "components/mesh.h"
#include "sys_render.h"

static bool Implements(struct tv_Entity *e)
{
  return tv_EntityGetComponent(e, COMPONENT_MATERIAL) != NULL &&
    tv_EntityGetComponent(e, COMPONENT_MESH) != NULL;
}

/* TODO: */
static void Update(struct tv_Entity *e)
{
  struct Mesh *mesh;
  struct Material *mat;

  mesh = tv_EntityGetComponent(e, COMPONENT_MESH);
  mat = tv_EntityGetComponent(e, COMPONENT_MATERIAL);
}

struct sys_Render * NewRenderSystem()
{
  struct tv_System *sys;
  sys = malloc(sizeof(struct sys_Render));
  sys->Implements = Implements;
  sys->Update = Update;
  return sys;
}


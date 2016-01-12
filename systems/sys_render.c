#include "components/enum.h"
#include "components/transform.h"
#include "components/material.h"
#include "components/mesh.h"
#include "system.h"
#include "sys_render.h"

static bool implements(struct tv_Entity *e)
{
  return tv_EntityGetComponent(e, COMPONENT_MATERIAL) != NULL &&
    tv_EntityGetComponent(e, COMPONENT_MESH) != NULL;
}

/* TODO: */
static void update(struct tv_Entity *e)
{
  struct Mesh *mesh;
  struct Material *mat;

  mesh = (struct Mesh*)tv_EntityGetComponent(e, COMPONENT_MESH);
  mat = (struct Material*)tv_EntityGetComponent(e, COMPONENT_MATERIAL);
}

void InitRenderSystem()
{
  struct tv_System sys = {
    .enabled = true,
    .Start = NULL,
    .Update = update,
    .Implements = implements,
    .GlobalUpdate = NULL,
  };
  tv_RegisterSystem(&sys);
}


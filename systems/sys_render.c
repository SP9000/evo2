#include "components/cam.h"
#include "components/enum.h"
#include "components/material.h"
#include "components/mesh.h"
#include "components/transform.h"
#include "debug.h"
#include "draw.h"
#include "system.h"
#include "sys_render.h"

#define SYSTEM_RENDER_MAX_MESHES 2048

static struct Transform *cam; /* the camera to render with */

//XXX: proper scenegraph
static struct {
  struct Mesh *mesh;
  struct Material *mat;
}meshes[SYSTEM_RENDER_MAX_MESHES];

/* start adds renderable geometry to the render system's scenegraph. */
static void start(struct tv_Entity *e)
{
  int i;
  struct Transform *c;
  struct Mesh *mesh;
  struct Material *mat;

  if(tv_EntityGetComponent(e, COMPONENT_CAM) != NULL){
    c = (struct Transform*)tv_EntityGetComponent(e, COMPONENT_TRANSFORM);
    if(c != NULL){
      cam = c;
    }
  }

  mat = (struct Material*)tv_EntityGetComponent(e, COMPONENT_MATERIAL);
  mesh = (struct Mesh*)tv_EntityGetComponent(e, COMPONENT_MESH);
  if(mesh != NULL){
    for(i = 0; i < SYSTEM_RENDER_MAX_MESHES; ++i){
      if(meshes[i].mesh == NULL){
        meshes[i].mesh = mesh;
        meshes[i].mat = mat;
      }
    }
    //XXX: insert into scenegraph
    for(i = 0; i < SYSTEM_RENDER_MAX_MESHES; ++i){
      if(meshes[i].mesh == NULL){
        meshes[i].mesh = mesh;
        meshes[i].mat = mat;
      }
    }
  }
}

/* update does nothing. */
static void update(struct tv_Entity *e)
{
}

/* render renders the scene as seen by cam. */
static void render()
{
  int i;
  struct Mat4x4 mv = Mat4x4Identity;

  if(cam != NULL){
    //mat4x4_rotate(&mv, cam->rot.x, 1.0f, 0.0f, 0.0f);
    //mat4x4_rotate(&mv, cam->rot.y, 0.0f, 1.0f, 0.0f);
    mat4x4_rotate_y(&mv, cam->rot.y);
    mat4x4_translate(&mv, -cam->pos.x, -cam->pos.y, -cam->pos.z - 6.0f);
  }
  tv_DrawModelview(&mv);

  //XXX: render from scenegraph
  for(i = 0; i < SYSTEM_RENDER_MAX_MESHES; ++i){
    if(meshes[i].mesh != NULL)
      tv_Draw(meshes[i].mesh, meshes[i].mat);
  }
}

/* InitRenderSystem initializes the rendering system. */
void InitRenderSystem()
{
  struct tv_System sys = {
    .enabled = true,
    .Start = start,
    .Update = update,
    .Implements = NULL,
    .GlobalUpdate = render
  };
  tv_RegisterSystem(&sys);
}

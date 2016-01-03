#include <assert.h>
#include <string.h>
#include "enum.h"
#include "render.h"
#include "../draw.h"

static void Start(struct tv_Component *c)
{
  assert(tv_EntityGetComponent(c->entity, COMPONENT_TRANSFORM));
}

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
  c->Start  = Start;
  return r;
}

unsigned tv_EntityNumComponents(struct tv_Entity *e)
{
  return e->_numComponents;
}


struct tv_Mesh * tv_NewMesh(int format, int n)
{
  int i, sz;
  struct tv_Mesh *m;

  /* calculate the vertex size */
  for(i=1, sz=0; i < TV_VERTEX_ATTR_END; i<<=1)
  {
    if(format&i == 0)
    {
      continue;
    }
    switch(i)
    {
      case TV_VERTEX_ATTR_POS:
        sz += sizeof(struct tv_AttrPos);
        break;
      case TV_VERTEX_ATTR_COL:
        sz += sizeof(struct tv_AttrCol);
        break;
      case TV_VERTEX_ATTR_UV:
        sz += sizeof(struct tv_AttrTexco);
        break;
      default:
        break;
    }
  }
  m = malloc(sizeof(struct tv_Mesh) + (sz*n));
  return m;
}

void tv_MeshAppend(struct tv_Mesh *mesh, void *vtx)
{
  int i, sz;
  void *v;
  
  if(mesh->numVertices == mesh->allocSize)
  {
    mesh->vertices = realloc(mesh->vertices, mesh->numVertices + 100);
    mesh->allocSize = mesh->numVertices + 100;
  }

  for(i=1, v=mesh->vertices; i < TV_VERTEX_ATTR_END; i<<=1, v+=sz)
  {
    sz = 0;
    if(mesh->format&i == 0)
    {
      continue;
    }
    switch(i)
    {
      case TV_VERTEX_ATTR_POS:
        sz += sizeof(struct tv_AttrPos);
        break;
      case TV_VERTEX_ATTR_COL:
        sz += sizeof(struct tv_AttrCol);
        break;
      case TV_VERTEX_ATTR_UV:
        sz += sizeof(struct tv_AttrTexco);
        break;
      default:
        break;
    }
    memcpy(v, vtx, sz);
  }
  mesh->numVertices++;
}

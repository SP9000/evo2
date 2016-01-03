#include <string.h>
#include "../components/enum.h"
#include "mesh.h"

/* Start initializes the Mesh component */
static void Start(struct tv_Component *c)
{
}

/* Size returns the size of the Mesh component */
static size_t Size()
{
  return sizeof(struct Mesh);
}

/* InitMesh initializes the allocated mesh with room for n vertices. */
void InitMesh(struct Mesh *m, int format, int n)
{
  int i, sz;
  /* calculate the vertex size */
  for(i=TV_VERTEX_ATTR_START, sz=0; i < TV_VERTEX_ATTR_END; i<<=1)
  {
    if((format & i) == 0)
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
  m->vertices = malloc(sz*n);
}

/* tv_NewMesh creates a new mesh pre-allocated with room for n vertices. */
struct Mesh * NewMesh(int format, int n)
{
  struct Mesh *m;
  struct tv_Component *c;

  m = malloc(sizeof(struct Mesh));
  InitMesh(m, format, n);

  c = (struct tv_Component*)m;
  c->id = COMPONENT_MESH;
  c->Size = Size;
  c->Start = Start;

  return m;
}

/* MeshAppend appends vtx to the mesh. */
void MeshAppend(struct Mesh *mesh, void *vtx)
{
  int i, sz;
  void *v;
  
  if(mesh->numVertices == mesh->allocSize)
  {
    mesh->vertices = realloc(mesh->vertices, mesh->numVertices + 100);
    mesh->allocSize = mesh->numVertices + 100;
  }

  for(i=TV_VERTEX_ATTR_START, v=mesh->vertices; i < TV_VERTEX_ATTR_END;
     i<<=1, v+=sz)
  {
    sz = 0;
    if((mesh->format & i) == 0)
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

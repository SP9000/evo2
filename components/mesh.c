#include <string.h>
#include "../components/enum.h"
#include "mesh.h"

/* vertexSize returns the size of each vertex in the mesh m. */
static unsigned vertexSize(uint16_t fmt)
{
  int i, size;
  /* calculate the vertex size */
  for(i=TV_VERTEX_ATTR_START, size=0; i < TV_VERTEX_ATTR_END; i<<=1){
    if((fmt & i) == 0)
      continue;
    switch(i){
      case TV_VERTEX_ATTR_POS:
        size += sizeof(struct tv_AttrPos);
        break;
      case TV_VERTEX_ATTR_COL:
        size += sizeof(struct tv_AttrCol);
        break;
      case TV_VERTEX_ATTR_UV:
        size += sizeof(struct tv_AttrTexco);
        break;
      default:
        break;
    }
  }
  return size;
}

/* tv_NewMesh creates a new mesh pre-allocated with room for n vertices. */
struct Mesh NewMesh(int format, int n)
{
  struct Mesh mesh = {
    .size = sizeof(struct Mesh) + vertexSize(format) * n,
    .format = format,
    .numverts = n,
  };
  return mesh;
}

/* MeshAppend appends vtx to the mesh. */
void MeshAppend(struct Mesh *m, void *vtx)
{
  uint16_t size;
  uint8_t *dst;

  if(m->numverts >= m->reserved)
    return;
  size = vertexSize(m->format);
  dst = m->verts + (size * m->numverts);
  memcpy(dst, vtx, size);
  m->numverts++;
}

#include <string.h>
#include "components/enum.h"
#include "entity.h"
#include "mesh.h"

/* makeQuad initializes the mesh component c to a simple white quad. */
static void makeQuad(void *c)
{
  struct Mesh *m;
  struct MeshBuffer *vb, *cb;
  const struct MeshAttr pos[] = {
    {.pos = {0,0,0,1}},
    {.pos = {1,0,0,1}},
    {.pos = {1,1,0,1}},

    {.pos = {0,0,0,1}},
    {.pos = {1,1,0,1}},
    {.pos = {0,1,0,1}}
  };
  const struct MeshAttr col[] = {
    {.col = {0xff,0xff,0xff,0xf}},
    {.col = {0xff,0xff,0xff,0xf}},
    {.col = {0xff,0xff,0xff,0xf}},

    {.col = {0xff,0xff,0xff,0xf}},
    {.col = {0xff,0xff,0xff,0xf}},
    {.col = {0xff,0xff,0xff,0xf}}
  };

  m = (struct Mesh*)c;
  cb = (struct MeshBuffer*)m->buffers;
  vb = (struct MeshBuffer*)m->buffers + sizeof(pos);

  vb->type = TV_VERTEX_ATTR_POS;
  cb->type = TV_VERTEX_ATTR_COL;
  memcpy(vb, pos, sizeof(pos));
  memcpy(cb, col, sizeof(col));
};

/* tv_NewMesh creates a new mesh pre-allocated with room for n vertices. */
struct Mesh NewMesh(uint16_t n, uint16_t buffs)
{
  struct Mesh mesh = {
    .size = sizeof(struct Mesh) + n * sizeof(struct MeshAttr) * buffs,
    .numVerts = n,
    .numBuffs = 0
  };
  return mesh;
}

/* MeshNewQuad creates returns a new mesh of a white qud. */
struct Mesh MeshNewQuad()
{
  struct Mesh mesh = {
    .size = sizeof(struct Mesh) + 6 * sizeof(struct MeshAttr) * 2,
    .numVerts = 6,
    .numBuffs = 0,
    .init = makeQuad
  };
  return mesh;
}

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
    {.pos = {0,0,0,255}},
    {.pos = {255,0,0,255}},
    {.pos = {255,255,0,255}},

    {.pos = {0,0,0,255}},
    {.pos = {255,255,0,255}},
    {.pos = {0,255,0,255}}
  };
  const struct MeshAttr col[] = {
    {.col = {0xff,0xff,0xff,0xff}},
    {.col = {0xff,0xff,0xff,0xff}},
    {.col = {0xff,0xff,0xff,0xff}},

    {.col = {0xff,0xff,0xff,0xff}},
    {.col = {0xff,0xff,0xff,0xff}},
    {.col = {0xff,0xff,0xff,0xff}}
  };

  m = (struct Mesh*)c;
  vb = (struct MeshBuffer*)(m->buffers);
  cb = (struct MeshBuffer*)(m->buffers + sizeof(pos));

  vb->type = TV_VERTEX_ATTR_POS;
  cb->type = TV_VERTEX_ATTR_COL;
  memcpy(vb, pos, sizeof(pos));
  memcpy(cb, col, sizeof(col));

  for(int i = 0; i < 4*6; ++i)
    printf("%d\n", *((uint8_t*)(cb) + i));
};

/* tv_NewMesh creates a new mesh pre-allocated with room for n vertices. */
struct Mesh NewMesh(uint16_t n, uint16_t buffs)
{
  struct Mesh mesh = {
    .C = {
      .size = sizeof(struct Mesh) + n * sizeof(struct MeshAttr) * buffs,
    },
    .numVerts = n,
    .numBuffs = 0
  };
  return mesh;
}

/* MeshNewQuad creates returns a new mesh of a white qud. */
struct Mesh MeshNewQuad()
{
  struct Mesh mesh = {
    .C = {
      .size = sizeof(struct Mesh) + 6 * sizeof(struct MeshAttr) * 2,
      .init = makeQuad
    },
    .numVerts = 6,
    .numBuffs = 0,
  };
  return mesh;
}

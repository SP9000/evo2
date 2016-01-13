#ifndef MESH_H
#define MESH_H

#include "entity.h"
#include "vector.h"

/*
 * tv_AttrType is an enumeration of all recognized per-vertex attributes.
 * Attributes are added to a vertex in order of this enumeration, so you may
 * assume that a vertex containing, e.g. position in color is formatted as:
 *  pos<vector3>, color<vector3>.
 */
enum tv_AttrType{
  TV_VERTEX_ATTR_START=1<<0,
  TV_VERTEX_ATTR_POS=1<<0,
  TV_VERTEX_ATTR_COL=1<<1,
  TV_VERTEX_ATTR_UV=1<<2,
  TV_VERTEX_ATTR_END=1<<3
};

/* MeshPos is a struct that represents an XYZW vertex position. */
struct MeshPos{
  uint8_t x, y, z, w;
};

/* MeshCol is a struct that represents an RGBA vertex color. */
struct MeshCol{
  uint8_t r, g, b, a;
};

/* MeshTexco is a struct that represents a 2D texture coordinate. */
struct MeshTexco{
  uint16_t u, v;
};

/* MeshAttr is a union representing one 1 attribute for 1 vertex. */
struct MeshAttr{
  union{
    struct MeshPos pos;
    struct MeshCol col;
    struct MeshTexco texco;
  };
};

/* MeshBuffer is a struct that holds per-vertex data for 1 attribute. */
struct MeshBuffer{
  uint8_t type;
  struct MeshAttr data[];
};

/* Mesh is a component that all associated buffers needed to render geometry. */
struct Mesh{
  TV_COMPONENT
  uint16_t numVerts;
  uint8_t numBuffs;
  struct MeshBuffer buffers[];
};

struct Mesh NewMesh(uint16_t, uint16_t);
size_t MeshSize(struct Mesh*);

struct Mesh NewMeshQuad(uint16_t);

#endif

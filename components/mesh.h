#ifndef MESH_H
#define MESH_H

#include "../entity.h"
#include "../vector.h"

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

struct tv_AttrPos{
  tv_Vector3 xyz;
};
struct tv_AttrCol{
  tv_Vector3 rgb;
};
struct tv_AttrTexco{
  tv_Vector2 uv;
};

/* Mesh is a component that contains vertex data. */
struct Mesh{
  TV_COMPONENT
  uint16_t numverts;   /* number of vertices in mesh */
  uint16_t reserved;   /* number of vertices mesh can hold */
  uint16_t format;     /* OR of tv_AttrType's comprising the vertex */
  uint8_t  verts[];    /* vertices */
};

struct Mesh NewMesh(int, int);
size_t MeshSize(struct Mesh*);
void MeshAppend(struct Mesh*, void*);

#endif

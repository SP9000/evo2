#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <OpenGL/gl.h>
#include "../entity.h"
#include "transform.h"

/**
 * tv_AttrType is an enumeration of all recognized per-vertex attributes.
 * Attributes are added to a vertex in order of this enumeration, so you may
 * assume that a vertex containing, e.g. position in color is formatted as:
 *  pos<vector3>, color<vector3>.
 */
enum tv_AttrType
{
  TV_VERTEX_ATTR_START=1<<0,
  TV_VERTEX_ATTR_POS=1<<0,
  TV_VERTEX_ATTR_COL=1<<1,
  TV_VERTEX_ATTR_UV=1<<2,
  TV_VERTEX_ATTR_END=1<<3
};

struct tv_AttrPos
{
  tv_Vector3 xyz;
};
struct tv_AttrCol
{
  tv_Vector3 rgb;
};
struct tv_AttrTexco
{
  tv_Vector2 uv;
};

/**
 * tv_Material contains OpenGL handles for the shader program to render with.
 */
struct tv_Material
{
  GLuint fs, vs, gs;
  GLuint vbo;
  GLuint mvp;
};

/**
 * tv_Mesh holds the vertices for a mesh.
 */
struct tv_Mesh
{
  int format; /* OR of tv_AttrType's comprising the vertex */
  int vertexSize; /* size of each vertex (in bytes) */
  int numVertices;
  int allocSize; /* the number of vertices that will fit before reallocation */
  void *vertices;
};

/**
 * Render is a component used to draw anything.
 * 
 */
struct Render 
{
  struct tv_Component co;
  struct tv_Material mat;
  struct Transform *transform;
  int    tileID; 
};

/**
 * RenderNew creates a new Render component.
 */
struct Render * NewRender();


/**
 * tv_NewMesh creates a new mesh pre-allocated with room for n vertices.
 */
struct tv_Mesh * tv_NewMesh(int format, int n);

/**
 * tv_MeshAppend appends vtx to the mesh.
 */
void tv_MeshAppend(struct tv_Mesh *mesh, void *vtx);


#endif

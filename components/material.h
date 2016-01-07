#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>
#include "../entity.h"
#include "../vector.h"

/* Material is a component that contains OpenGL handles for rendering. */
struct Material{
  struct tv_Component co;
  GLuint program;
  GLuint fs, vs, gs;
  GLuint mvp; /* modelview-projection matrix uniform handle */
};

struct Mesh * NewMesh(int, int);
void InitMesh(struct Mesh*, int, int);
void MeshAppend(struct Mesh*, void*);

#endif

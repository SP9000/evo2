#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

#define PI 3.1415926536
#define TWO_PI (PI * 2.0f)
#define MATRIX_STACK_SIZE 16

#ifdef _WIN32
#pragma pack(4)
#endif
#ifdef __GNUC__
struct __attribute__((packed, aligned(4)))
#elif defined(__WIN32__)
#pragma pack(2)
struct 
#else
#pragma message ("warning: matrix structure packing not guaranteed")
#endif
Mat4x4
{
  float a0, b0, c0, d0;
  float a1, b1, c1, d1;
  float a2, b2, c2, d2;
  float a3, b3, c3, d3;
};

void mat4x4_push(struct Mat4x4*);
void mat4x4_pop(struct Mat4x4*);

void mat4x4_load_identity(struct Mat4x4*);
void mat4x4_scale(struct Mat4x4*, float, float, float);
void mat4x4_translate(struct Mat4x4*, float, float, float);
void mat4x4_rotate(struct Mat4x4*, float, float, float, float);
void mat4x4_rotate_x(struct Mat4x4*, float);
void mat4x4_rotate_y(struct Mat4x4*, float);
void mat4x4_rotate_z(struct Mat4x4*, float);

float mat4x4_det(struct Mat4x4*);
bool mat4x4_inverse(struct Mat4x4, struct Mat4x4*);

struct Mat4x4 mat4x4_multiply(struct Mat4x4, struct Mat4x4);
tv_Vector4 mat4x4_multiply_vec4x1(struct Mat4x4, tv_Vector4);
tv_Vector3 mat4x4_multiply_vec3x1(struct Mat4x4, tv_Vector3);
void mat4x4_perspective(struct Mat4x4 *mat, float, float, float, float);
void mat4x4_orthographic(struct Mat4x4 *mat, float, float, float, float, float, float);

float *mat4x4_to_array(struct Mat4x4 *mat);

extern const struct Mat4x4 Mat4x4Identity;

#ifdef __cplusplus 
}
#endif
#endif

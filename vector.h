#ifndef TV_VECTOR_H
#define TV_VECTOR_H

#include <stdbool.h>
#include <stdio.h>

/**
 * A basic type for representing a point in 2-dimensional space.
 */
typedef struct tv_Vector2 
{
    float x, y;
}tv_Vector2;

/**
 * A basic type for representing a point in 3-dimensional space.
 */
typedef struct tv_Vector3 
{
    float x, y, z;
}tv_Vector3;

/**
 * A type for representing the position, scale, and rotation of an object.
 */
typedef struct tagTvTransform {
	tv_Vector3 position;
	tv_Vector3 scale;
	tv_Vector3 rotation;
}TvTransform;

/**
 * A type for representing a rectangle.
 */
struct tv_Rect 
{
    float x, y;
    float w, h;
};

/**
 * Checks if the given rectangle contains the given point.
 * @param r the rectangle to check for the point within.
 * @param point the point to determine if is in the bounds of the rect or not.
 * @return TRUE if the rectangle does contain the point, else FALSE.
 */
bool tv_RectContains(struct tv_Rect r, tv_Vector2 point);
/**
 * Checks if the given rectangle overlaps the other given rectangle.
 * @param r1 the first rectangle.
 * @param r2 the...second...rectangle.
 * @return TRUE if the rectangles overlap, else FALSE.
 */
bool tv_RectOverlaps(struct tv_Rect* r1, struct tv_Rect* r2);

/**
 * A basic type for representing a point in 4-dimensional space
 */
typedef struct tv_Vector4 
{
	float x, y, z, w;
}tv_Vector4;

typedef tv_Vector4 tv_Quaternion;

extern const tv_Vector2 tv_Vector2Zero;
extern const tv_Vector3 tv_Vector3Zero;
extern const tv_Vector4 tv_Vector4Zero;

extern const tv_Vector3 tv_Vector3Forward;
extern const tv_Vector4 tv_Vector4Forward;

/* new */
tv_Vector2 tv_Vector2_new(float x, float y);
tv_Vector3 tv_Vector3_new(float x, float y, float z);
tv_Vector4 tv_Vector4_new(float x, float y, float z, float w);

/* add */
void tv_Vector2Add(tv_Vector2 v1, tv_Vector2 v2, tv_Vector2* result);
void tv_Vector3Add(tv_Vector3 v1, tv_Vector3 v2, tv_Vector3* result);
void tv_Vector4Add(tv_Vector4 v1, tv_Vector4 v2, tv_Vector4* result);

/* sub */
void tv_Vector2Sub(tv_Vector2 v1, tv_Vector2 v2, tv_Vector2* result);
void tv_Vector3Sub(tv_Vector3 v1, tv_Vector3 v2, tv_Vector3* result);
void tv_Vector4Sub(tv_Vector4 v1, tv_Vector4 v2, tv_Vector4* result);

/* normalize */
void tv_Vector2Normalize(tv_Vector2 v, tv_Vector2* result);
void tv_Vector3Normalize(tv_Vector3 v, tv_Vector3* result);

/* scale */
void tv_Vector2Scale(tv_Vector2 *v, float factor);
void tv_Vector3Scale(tv_Vector3 *v, float factor);
void tv_Vector4Scale(tv_Vector4 *v, float factor);

/* cross product */
float tv_Vector2Cross(tv_Vector2* v1, tv_Vector2* v2);
void tv_Vector3Cross(tv_Vector3* v1, tv_Vector3* v2, tv_Vector3* result);
void tv_Vector4Cross(tv_Vector4* v1, tv_Vector4* v2, tv_Vector4* result);

/* dot-product */
float tv_Vector2Dot(tv_Vector2 v1, tv_Vector2 v2);
float tv_Vector3Dot(tv_Vector3 v1, tv_Vector3 v2);
float tv_Vector4Dot(tv_Vector4 v1, tv_Vector4 v2);

/* distance */
float tv_Vector2Distance(tv_Vector2 v1, tv_Vector2 v2);
float tv_Vector3Distance(tv_Vector3 v1, tv_Vector3 v2);
float tv_Vector4Distance(tv_Vector4 v1, tv_Vector4 v2);

/* magnitude */
float tv_Vector2Mag(tv_Vector2* v);
float tv_Vector3Mag(tv_Vector3* v);

/**
 * Get the unit direction vector from v1 to v2.
 * @param v1 the "start" vector.
 * @param v2 the "destination" vector.
 * @return a unit vector representing the direction of v1 to v2.
 */
void tv_Vector3Direction(tv_Vector3 v1, tv_Vector3 v2, tv_Vector3 *result);

/**
 * Linearly interpolates between the given vectors.
 * @param v1 the first vector to interpolate from.
 * @param v2 the vector to interpolate to.
 * @param t the time (0-1)
 * @return the new vector 
 */
tv_Vector2 tv_Vector2Lerp(tv_Vector2 v1, tv_Vector2 v2, float t);

/**
 * Linearly interpolates between the given 3-D vectors.
 * @param v1 the "start" vector.
 * @param v2 the "destination" vector.
 * @param t the time (0-1)
 * @return the new vector
 */
tv_Vector3 tv_Vector3Lerp(tv_Vector3 v1, tv_Vector3 v2, float t);

/**
 * Linearly interpolates between the given 4-D vectors.
 * @param v1 the "start" vector.
 * @param v2 the "destination" vector.
 * @param t the time (0-1)
 * @return the new vector
 */
tv_Vector4 tv_Vector4Lerp(tv_Vector4 v1, tv_Vector4 v2, float t);

#endif

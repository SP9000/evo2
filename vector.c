#include "vector.h"
#include <math.h>

/******************************************************************************
 * zero vectors
******************************************************************************/
const tv_Vector2 tv_Vector2Zero = {0, 0};
const tv_Vector3 tv_Vector3Zero = {0, 0, 0};
const tv_Vector4 tv_Vector4Zero = {0, 0, 0, 0};

const tv_Vector2 tv_Vector2One = {1, 1};
const tv_Vector3 tv_Vector3One = {1, 1, 1};
const tv_Vector4 tv_Vector4One = {1, 1, 1, 1};

/******************************************************************************
 * forward vectors- point in the positive Z direction
******************************************************************************/
const tv_Vector3 tv_Vector3_forward = {0.0f, 0.0f, 1.0f};
const tv_Vector4 tv_Vector4_forward = {0.0f, 0.0f, 1.0f, 1.0f};

/******************************************************************************
 * new
******************************************************************************/
tv_Vector2 tv_Vector2New(float x, float y) {
	tv_Vector2 ret = {x, y};
	return ret;
}
tv_Vector3 tv_Vector3New(float x, float y, float z) {
	tv_Vector3 ret = {x, y, z};
	return ret;
}
tv_Vector4 tv_Vector4New(float x, float y, float z, float w) {
	tv_Vector4 ret = {x, y, z, w};
	return ret;
}
/******************************************************************************
 * add
******************************************************************************/
void tv_Vector2Add(tv_Vector2 v1, tv_Vector2 v2, tv_Vector2 *result) {
	result->x = v1.x + v2.x;
	result->y = v1.y + v2.y;
}
void tv_Vector3Add(tv_Vector3 v1, tv_Vector3 v2, tv_Vector3 *result) {
	result->x = v1.x + v2.x;
	result->y = v1.y + v2.y;
	result->z = v1.z + v2.z;
}
void tv_Vector4Add(tv_Vector4 v1, tv_Vector4 v2, tv_Vector4 *result) {
	result->x = v1.x + v2.x;
	result->y = v1.y + v2.y;
	result->z = v1.z + v2.z;
	result->w = v1.w + v2.w;
}
/******************************************************************************
 * subtract
******************************************************************************/
void tv_Vector2Sub(tv_Vector2 v1, tv_Vector2 v2, tv_Vector2 *result) {
	result->x = v1.x - v2.x;
	result->y = v1.y - v2.y;
}
void tv_Vector3Sub(tv_Vector3 v1, tv_Vector3 v2, tv_Vector3 *result) {
	result->x = v1.x - v2.x;
	result->y = v1.y - v2.y;
	result->z = v1.z - v2.z;
}
void tv_Vector4Sub(tv_Vector4 v1, tv_Vector4 v2, tv_Vector4 *result) {
	result->x = v1.x - v2.x;
	result->y = v1.y - v2.y;
	result->z = v1.z - v2.z;
	result->w = v1.w - v2.w;
}
/******************************************************************************
 * scale
******************************************************************************/
void tv_Vector2Scale(tv_Vector2 *v, float factor) {
	v->x *= factor;
	v->y *= factor;
}
void tv_Vector3Scale(tv_Vector3 *v, float factor) {
	v->x *= factor;
	v->y *= factor;
	v->z *= factor;
}
void tv_Vector4Scale(tv_Vector4 *v, float factor) {
	v->x *= factor;
	v->y *= factor;
	v->z *= factor;
	v->w *= factor;
}
/******************************************************************************
 * dot product
******************************************************************************/
float tv_Vector2Dot(tv_Vector2 v1, tv_Vector2 v2) {
	return v1.x * v2.x + v1.y * v2.y;
}
float tv_Vector3Dot(tv_Vector3 v1, tv_Vector3 v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
float tv_Vector4Dot(tv_Vector4 v1, tv_Vector4 v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}
/******************************************************************************
 * normalize
******************************************************************************/
void tv_Vector2Normalize(tv_Vector2 v, tv_Vector2 *result) {
	float mag = tv_Vector2Mag(&v);
	/* assert(mag != 0.0f); */
	if (mag == 0.0f) {
		puts("warning: attempted to normalize a vector with magnitude "
		     "0");
		return;
	}
	result->x = v.x / mag;
	result->y = v.y / mag;
}
void tv_Vector3Normalize(tv_Vector3 v, tv_Vector3 *result) {
	float mag = tv_Vector3Mag(&v);
	/* assert(mag != 0.0f); */
	if (mag == 0.0f) {
		puts("warning: attempted to normalize a vector with magnitude "
		     "0");
		return;
	}
	result->x = v.x / mag;
	result->y = v.y / mag;
	result->z = v.z / mag;
}
/******************************************************************************
 * magnitude
******************************************************************************/
float tv_Vector2Mag(tv_Vector2 *v) {
	return (float)sqrt(v->x * v->x + v->y * v->y);
}
float tv_Vector3Mag(tv_Vector3 *v) {
	return (float)sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}
/******************************************************************************
 * cross product
******************************************************************************/
float tv_Vector2Cross(tv_Vector2 *v1, tv_Vector2 *v2) {
	return (v1->x * v2->y) - (v1->y * v2->x);
}
void tv_Vector3Cross(tv_Vector3 *v1, tv_Vector3 *v2, tv_Vector3 *result) {
	result->x = (v1->y * v2->z) - (v1->z * v2->y);
	result->y = (v1->z * v2->x) - (v1->x * v2->z);
	result->z = (v1->x * v2->y) - (v1->y * v2->x);
}
void tv_Vector4Cross(tv_Vector4 *v1, tv_Vector4 *v2, tv_Vector4 *result) {
	/* TODO: */
}
/******************************************************************************
 * distance
******************************************************************************/
float tv_Vector2Distance(tv_Vector2 v1, tv_Vector2 v2) {
	return (float)sqrt((v2.x * v2.x) - (v1.x * v1.x) + (v2.y * v2.y) -
	                   (v1.y * v1.y));
}
float tv_Vector3Distance(tv_Vector3 v1, tv_Vector3 v2) {
	return (float)sqrt((v2.x * v2.x) - (v1.x * v1.x) + (v2.y * v2.y) -
	                   (v1.y * v1.y) + (v2.z * v2.z) - (v1.z * v1.z));
}
float tv_Vector4Distance(tv_Vector4 v1, tv_Vector4 v2) {
	return (float)sqrt((v2.x * v2.x) - (v1.x * v1.x) + (v2.y * v2.y) -
	                   (v1.y * v1.y) + (v2.z * v2.z) - (v1.z * v1.z) +
	                   (v2.w * v2.w) - (v1.w * v1.w));
}
/******************************************************************************
 * LERP
******************************************************************************/
tv_Vector2 tv_Vector2Lerp(tv_Vector2 v1, tv_Vector2 v2, float t) {
	/* TODO: */
	tv_Vector2 ret = {0.0f, 0.0f};
	return ret;
}
tv_Vector3 tv_Vector3Lerp(tv_Vector3 v1, tv_Vector3 v2, float t) {
	/* TODO: */
	tv_Vector3 ret = {0.0f, 0.0f, 0.0f};
	return ret;
}
tv_Vector4 tv_Vector4Lerp(tv_Vector4 v1, tv_Vector4 v2, float t) {
	/* TODO: */
	tv_Vector4 ret = {0.0f, 0.0f, 0.0f, 0.0f};
	return ret;
}
/******************************************************************************
 * direction
******************************************************************************/
void tv_Vector3Direction(tv_Vector3 v1, tv_Vector3 v2, tv_Vector3 *result) {
	result->x = v1.x - v2.x;
	result->y = v1.y - v2.y;
	result->z = v1.z - v2.z;
	tv_Vector3Normalize(*result, result);
}
bool tv_RectContains(struct tv_Rect r, tv_Vector2 point) {
	if ((point.x >= r.x) && (point.x <= (r.x + r.w)) && (point.y >= r.y) &&
	    (point.y <= (r.y + r.h))) {
		return true;
	}
	return false;
}
bool tv_RectOverlaps(struct tv_Rect *r1, struct tv_Rect *r2) {
	if ((r1->x < (r2->x + r2->w)) && ((r1->x + r1->w) > r2->x) &&
	    (r1->y < (r2->y + r2->h)) && ((r1->y + r1->h) > r2->y)) {
		return true;
	}
	return false;
}

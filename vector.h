#ifndef TV_VECTOR_H
#define TV_VECTOR_H

#include <stdbool.h>
#include <stdio.h>

typedef struct tv_Vector2 { float x, y; } tv_Vector2;
typedef struct tv_Vector3 { float x, y, z; } tv_Vector3;
typedef struct tv_Vector4 { float x, y, z, w; } tv_Vector4;
typedef tv_Vector4 tv_Quaternion;

struct tv_Rect {
	float x, y;
	float w, h;
};

bool tv_RectContains(struct tv_Rect, tv_Vector2);
bool tv_RectOverlaps(struct tv_Rect *, struct tv_Rect *);

extern const tv_Vector2 tv_Vector2Zero;
extern const tv_Vector3 tv_Vector3Zero;
extern const tv_Vector4 tv_Vector4Zero;

extern const tv_Vector2 tv_Vector2One;
extern const tv_Vector3 tv_Vector3One;
extern const tv_Vector4 tv_Vector4One;

extern const tv_Vector3 tv_Vector3Forward;
extern const tv_Vector4 tv_Vector4Forward;

tv_Vector2 tv_Vector2_new(float, float);
tv_Vector3 tv_Vector3_new(float, float, float);
tv_Vector4 tv_Vector4_new(float, float, float, float);

void tv_Vector2Add(tv_Vector2, tv_Vector2, tv_Vector2 *);
void tv_Vector3Add(tv_Vector3, tv_Vector3, tv_Vector3 *);
void tv_Vector4Add(tv_Vector4, tv_Vector4, tv_Vector4 *);

void tv_Vector2Sub(tv_Vector2, tv_Vector2, tv_Vector2 *);
void tv_Vector3Sub(tv_Vector3, tv_Vector3, tv_Vector3 *);
void tv_Vector4Sub(tv_Vector4, tv_Vector4, tv_Vector4 *);

void tv_Vector2Normalize(tv_Vector2, tv_Vector2 *);
void tv_Vector3Normalize(tv_Vector3, tv_Vector3 *);

void tv_Vector2Scale(tv_Vector2 *, float);
void tv_Vector3Scale(tv_Vector3 *, float);
void tv_Vector4Scale(tv_Vector4 *, float);

float tv_Vector2Cross(tv_Vector2 *, tv_Vector2 *);
void tv_Vector3Cross(tv_Vector3 *, tv_Vector3 *, tv_Vector3 *);
void tv_Vector4Cross(tv_Vector4 *, tv_Vector4 *, tv_Vector4 *);

float tv_Vector2Dot(tv_Vector2, tv_Vector2);
float tv_Vector3Dot(tv_Vector3, tv_Vector3);
float tv_Vector4Dot(tv_Vector4, tv_Vector4);

float tv_Vector2Distance(tv_Vector2, tv_Vector2);
float tv_Vector3Distance(tv_Vector3, tv_Vector3);
float tv_Vector4Distance(tv_Vector4, tv_Vector4);

float tv_Vector2Mag(tv_Vector2 *);
float tv_Vector3Mag(tv_Vector3 *);

void tv_Vector3Direction(tv_Vector3, tv_Vector3, tv_Vector3 *);

tv_Vector2 tv_Vector2Lerp(tv_Vector2, tv_Vector2, float);
tv_Vector3 tv_Vector3Lerp(tv_Vector3, tv_Vector3, float);
tv_Vector4 tv_Vector4Lerp(tv_Vector4 v1, tv_Vector4 v2, float);

#endif

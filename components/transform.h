#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../entity.h"
#include "../vector.h"

/*
 * Transform is a component that is used to represent an entity's position,
 * rotation, and scale in the scene.
 */
struct Transform{
	TV_COMPONENT
	tv_Vector3 pos;
	tv_Quaternion rot;
	tv_Vector3 scale;
};

/* NewTransform creates a new transform component. */
struct Transform NewTransform(tv_Vector3,tv_Quaternion,tv_Vector3);

#endif

#include "transform.h"
#include "enum.h"

struct Transform NewTransform(tv_Vector3 pos,
		tv_Quaternion rot,
		tv_Vector3 scale)
{
	struct Transform t = {
		.C = {
			.size =  sizeof(struct Transform),
		},
		.pos = pos,
		.rot = rot,
		.scale = {
			.x = 1,
			.y = 1,
			.z = 1
		}
	};
	return t;
}


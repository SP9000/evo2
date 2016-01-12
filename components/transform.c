#include "transform.h"
#include "enum.h"

struct Transform NewTransform()
{
  struct Transform t = {
    .size =  sizeof(struct Transform),
    .pos = tv_Vector3Zero,
    .rot = tv_Vector4Zero,
    .scale = {
      .x = 1,
      .y = 1,
      .z = 1
    }
  };
  return t;
}


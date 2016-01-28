#ifndef CAM_H
#define CAM_H

#include "entity.h"
#include "matrix.h"

/* Cam is a struct that represents a viewport to be rendered to. */
struct Cam{
  TV_COMPONENT
  tv_Vector3 pos;
  tv_Vector3 rot;
};

struct Cam NewCam();
#endif

#include "cam.h"

struct Cam NewCam()
{
  struct Cam c = {
    .C = {
      .size = sizeof(struct Cam)
    },
    .pos = {0,0,0},
    .rot = {0,0,0}
  };
  return c;
}

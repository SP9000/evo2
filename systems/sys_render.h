#ifndef SYS_RENDER_H
#define SYS_RENDER_H

#include "../system.h"

struct sys_Render
{
  struct tv_System sys;
};

struct sys_Render * NewRenderSystem();

#endif
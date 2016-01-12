#ifndef SYS_RENDER_H
#define SYS_RENDER_H

#include "system.h"

/* sys_Render is the system responsible for all drawing */
struct sys_Render{
  struct tv_System sys;
};

struct sys_Render * NewRenderSystem();

#endif

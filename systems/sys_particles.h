#ifndef SYS_PARTICLES_H
#define SYS_PARTICLES_H

#include "system.h"

struct sys_Particles{
  struct tv_System sys;
};

void UpdateParticlesSystem();
struct sys_Particles * NewParticlesSystem();

#endif

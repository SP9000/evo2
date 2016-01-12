#ifndef PARTICLES_H
#define PARTICLES_H

#include <stdint.h>
#include "entity.h"
#include "vector.h"

enum{
  PARTICLES_GRAVITY = 1<<0,
  PARTICLES_TEXTURED = 1<<1,
  PARTICLES_FADE = 1<<2,
  PARTICLES_GROW = 1<<3,
  PARTICLES_SHRINK = 1<<4,
};

/* Particles is a component used by the particle system to emit particles. */
struct Particles{
  TV_COMPONENT
  uint16_t life;   /* ms each particlce lives */
  uint16_t flags;  /* bitmask of particle flags */
  uint16_t spread; /* units a particle may spawn outside its origin */
  uint8_t rate;    /* ms between each spawn */
  uint8_t tmr;     /* resets when == rate, tells system to spawn particle */
  union{
    uint32_t color;   /* if colored particle, the color spawned at */
    uint32_t texture; /* if textured particle, the texture applied */
  };
  tv_Vector2 minScale; /* minimum scale particles may be */
  tv_Vector2 maxScale; /* maximum scale particles may be */
  tv_Vector3 spawn;    /* origin of particle emission */
};

struct Particles NewParticles();

#endif

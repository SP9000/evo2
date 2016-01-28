#include "enum.h"
#include "particles.h"
#include "system.h"
#include "sys_particles.h"

#define MAX_PARTICLES 10000

struct Particle{
  tv_Vector3 pos;
  tv_Vector3 vel;
  uint8_t life;
};

struct Particle particles[MAX_PARTICLES]; /* global shared particle list. */

/* spawnParticle spawns a particle from the emitter p. */
static void spawnParticle(struct Particle *p)
{
  uint32_t i;
  for(i = 0; i < MAX_PARTICLES; ++i){
    if(particles[i].life == 0)
      particles[i] = *p;
  }
}

/* globalUpdate updates all emitted particles. */
static void globalUpdate()
{
  uint32_t i;
  for(i = 0; i < MAX_PARTICLES; ++i){
    if(particles[i].life != 0){
      particles[i].life--;
      particles[i].pos.x += particles[i].vel.x;
      particles[i].pos.y += particles[i].vel.y;
      particles[i].pos.z += particles[i].vel.z;
      /* TODO: handle other flags (fade, gravity, grow, etc.) */
    }
  }
}

/* implements returns true if the entity has a Particles component. */
static bool implements(struct tv_Entity *e)
{
  return tv_EntityGetComponent(e, COMPONENT_PARTICLES) != NULL;
}

/* update updates and spawns particles for all Particles components. */
static void update(struct tv_Entity *e)
{
  struct Particles *p;
  p = (struct Particles*)tv_EntityGetComponent(e, COMPONENT_PARTICLES);
  if(++p->tmr == p->rate){
    /* TODO: */
    struct Particle spawn = {
      .life = p->life,
      .pos = {
        .x = 0.0f,
        .y = 0.0f,
        .z = 0.0f
      },
      .vel = {
        .x = 0.5f,
        .y = 0.5f,
        .z = 0.0f
      }
    };
    spawnParticle(&spawn);
  }
}

/* InitParticlesSystem initializes the system that updates particle emitters. */
void InitParticlesSystem()
{
  struct tv_System sys = {
    .enabled = true,
    .Start = NULL,
    .Update = update,
    .Implements = implements,
    .GlobalUpdate = globalUpdate,
  };
  tv_RegisterSystem(&sys);
}

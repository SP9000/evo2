#include "enum.h"
#include "particles.h"
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

/* NewParticlesSystem creates a new system to update particle emitters. */
struct sys_Particles * NewParticlesSystem()
{
  struct tv_System *sys;
  sys = malloc(sizeof(struct sys_Particles));
  sys->Implements = implements;
  sys->Update = update;
  return (struct sys_Particles*)sys;
}

/* UpdateParticlesSystem updates all emitted particles. */
void UpdateParticlesSystem()
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

#include <string.h>
#include "system.h"

static struct tv_System systems[TV_NUM_SYSTEMS];
static unsigned short numSystems;

/* Remove system deletes the system at index id of systems. */
static void RemoveSystem(unsigned short id)
{
  memmove(&systems[id], &systems[id+1],
      sizeof(struct tv_System) * (numSystems-id));
  numSystems--;
}

/* tv_RegisterSystem registers sys to be updated each frame. */
void tv_RegisterSystem(struct tv_System *sys)
{
  sys->enabled = true;
  memcpy(&systems[numSystems], sys, sizeof(struct tv_System));
  numSystems++;
}

/* tv_SystemStartAll runs all registered TV_SYSTEM_START type systems. */
void tv_SystemStart()
{
  unsigned i;
  for(i = 0; i < numSystems; ++i){
    if(systems[i].enabled && (systems[i].type & TV_SYSTEM_START))
      tv_EntityStartAll(systems[i].Implements, systems[i].Start);
    systems[i].type ^= TV_SYSTEM_START;
    if(systems[i].type == TV_SYSTEM_NONE)
      RemoveSystem(i);
  }
}

/* tv_UpdateSystems updates all registered systems. */
void tv_SystemUpdate()
{
  unsigned i;
  for(i = 0; i < numSystems; ++i){
    if(systems[i].enabled && (systems[i].type & TV_SYSTEM_UPDATE))
      tv_EntityUpdateAll(systems[i].Implements, systems[i].Update);
  }
}

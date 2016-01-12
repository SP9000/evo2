#include <string.h>
#include "system.h"

static struct tv_System systems[TV_NUM_SYSTEMS];
static unsigned short numSystems;

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
    if(systems[i].enabled && systems[i].Start != NULL)
      tv_EntityStartAll(systems[i].Implements, systems[i].Start);
  }
}

/* tv_UpdateSystems updates all registered systems. */
void tv_SystemUpdate()
{
  unsigned i;
  for(i = 0; i < numSystems; ++i){
    if(systems[i].enabled && systems[i].GlobalUpdate != NULL)
      systems[i].GlobalUpdate();
  }
  for(i = 0; i < numSystems; ++i){
    if(systems[i].enabled && systems[i].Update != NULL)
      tv_EntityUpdateAll(systems[i].Implements, systems[i].Update,
          systems[i].cache);
  }
}

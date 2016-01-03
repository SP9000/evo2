#include "system.h"

static struct tv_System *systems[TV_MAX_SYSTEMS];
static unsigned numSystems;

void tv_RegisterSystem(struct tv_System *sys)
{
  sys->enabled = true;
  systems[numSystems] = sys;
  numSystems++;
}

void tv_UpdateSystems()
{
  unsigned i;
  for(i = 0; i < numSystems; ++i)
  {
    if(!systems[i]->enabled)
    {
      continue;
    }
    tv_EntityUpdateAll(systems[i]->Implements, systems[i]->Update);
  }
}
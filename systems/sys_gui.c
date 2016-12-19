#include "enum.h"
#include "gui.h"
#include "system.h"
#include "sys_gui.h"

bool implements(struct tv_Entity *e)
{
  /* TODO: implement simple inheritance or || all GUI types? */
  return tv_EntityGetComponent(e, COMPONENT_GUITEXT) != NULL;
}

void update(struct tv_Entity *e)
{

}

/* sys_GUIInit initializes the GUI system for use by the engine. */
void InitGUISystem()
{
  struct tv_System sys = {
    .enabled = true,
    .Start = NULL,
    .Update = update,
    .Implements = implements,
  };
  tv_RegisterSystem(&sys);
}


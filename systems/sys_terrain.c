#include "sys_terrain.h"
#include "components/enum.h"
#include "system.h"
#include "systems.h"
#include <stdbool.h>

/* implements returns true if the entity has Terrain & Mesh components. */
static bool implements(struct tv_Entity *e) {
	return tv_EntityGetComponent(e, COMPONENT_TERRAIN) != NULL &&
	       tv_EntityGetComponent(e, COMPONENT_MESH) != NULL;
}

/* Update gets a new mesh optimized for the main camera. */
static void update(struct tv_Entity *e) {}

/* InitTerrainSystem initializes the terrain system. */
void InitTerrainSystem() {
	struct tv_System sys = {
	    .enabled = true,
	    .Start = NULL,
	    .Update = update,
	    .Implements = implements,
	    .GlobalUpdate = NULL,
	};
	tv_RegisterSystem(&sys, SYSTEM_TERRAIN);
}

#ifndef ENTITY_H
#define ENTITY_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define TV_ENTITY_MAX_COMPONENTS 16 /* max number of components per entity. */
#define TV_ENTITY_NAMELEN 12 /* length of each entity's name (in bytes). */

/* TV_COMPONENT is a macro that embeds component data into a struct.
 * This macro must be the first declaration within a component structure.
 */
#define TV_COMPONENT struct tv_Component C;

/* tv_Component is a struct that contains essential component information. */
struct tv_Component{
	void (*init)(void*);
	uint16_t size;
};

/* tv_Entity is the basic container of all entities in the engine. */
struct tv_Entity 
{
	/* unique name used to refer to this entity. */
	char name[TV_ENTITY_NAMELEN];

	/* component unique identifiers. */
	uint16_t components[TV_ENTITY_MAX_COMPONENTS];

	/* the component data. */
	uint8_t data[];
};

struct tv_Entity * tv_EntityNew(int, ...);
void tv_EntityDestroy(struct tv_Entity*);
struct tv_Entity * tv_EntityAdd(struct tv_Entity*, uint16_t,
		struct tv_Component*);
struct tv_Entity * tv_EntityRemove(struct tv_Entity*, uint16_t);
void tv_EntityStartAll(bool (*test)(struct tv_Entity*),
		void (*start)(struct tv_Entity*), struct tv_Entity**);
void tv_EntityUpdateAll(bool (*test)(struct tv_Entity*),
		void (*update)(struct tv_Entity*), struct tv_Entity**);

unsigned tv_EntityNumComponents(struct tv_Entity*);
struct tv_Component * tv_EntityGetComponent(struct tv_Entity*, uint16_t);

#endif

#ifndef UTIL_H
#define UTIL_H

#endif

static struct tv_Entity *entities[MAX_ENTITIES];
static unsigned numEntities;
static unsigned pagetab[MAX_ENTITIES];

/* entitysize returns the size of e in bytes. */
static int entitysize(struct tv_Entity *e) {
	int i, size;
	for (i = 0, size = 0; i < TV_ENTITY_MAX_COMPONENTS; ++i) {
		if (e->components[i].id == COMPONENT_END)
			break;
		size += e->components[i].size;
	}
	return size + sizeof(struct tv_Entity);
}

/* tv_EntityInit copies e into the engine and returns a pointer to it. */
struct tv_Entity *tv_EntityInit(struct tv_Entity *e) {
	unsigned char *seek; /* allocation table iterator */
	unsigned pagebit;    /* bit # of current page being checked */
	int pagecnt;         /* consecutive available pages counter */
	int size;            /* entity size (in bytes) */
	int pagesize;        /* entity size (in pages) */

	size = tv_EntitySize(e);
	pagesize = size / PAGE_SIZE;
	if (size % PAGE_SIZE != 0)
		pagesize++;

	for (seek = alloctab, pagecnt = 0; seek < alloctab[MAX_ENTITIES];
	     ++seek) {
		for (pagebit = 31; pagebit > 0; --pagebit) {
			if (*seek & (1 << pagebit) != 0)
				pagecnt = 0;
			else if (++pagecnt >= size)
				goto found;
		}
	}
	return NULL;
found:
	while (pagesize-- > 0) {
		*seek |= (1 << pagebit);
		if (--pagebit < 0) {
			seek--;
			pagebit = 0;
		}
	}
	addr = ((unsigned char *)(entities)) + (seek - alloctab) +
	       ((31 - pagebit) * PAGE_SIZE);
	memcpy(addr, *e, size);
	entities[numEntities] = addr;
	return addr;
}

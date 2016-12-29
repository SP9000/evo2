#ifndef TERRAIN_H
#define TERRAIN_H

#include "entity.h"
#include <stdint.h>

/* Terrain is a component containing data for a large terrain. */
struct Terrain {
	TV_COMPONENT
	uint16_t w, h;
	struct {
		uint8_t z; /* relative z from tile to the left */
	} tiles[];
};

struct Terrain NewTerrain(int w, int h);

#endif

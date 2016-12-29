#include "particles.h"

/* NewParticles returns a new Particles component. */
struct Particles NewParticles() {
	struct Particles p = {.life = 32,
	                      .flags = 0,
	                      .spread = 0,
	                      .rate = 16,
	                      .tmr = 0,
	                      .color = 0xffffffff,
	                      .minScale = {.x = 1.0f, .y = 1.0f},
	                      .maxScale = {.x = 1.0f, .y = 1.0f},
	                      .spawn = {.x = 0.0f, .y = 0.0f, .z = 0.0f}};
	return p;
}

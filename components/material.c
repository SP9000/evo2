#include "material.h"
#include "../components/enum.h"
#include <string.h>

/* NewMaterial creates a new material component from the given shader sources */
struct Material NewMaterial(uint32_t ambient, uint32_t diffuse,
                            uint32_t specularity, uint32_t shininess) {
	struct Material m = {
	    .C =
	        {
	            .size = sizeof(struct Material),
	        },
	    .ambient = ambient,
	    .diffuse = diffuse,
	    .specularity = specularity,
	    .shininess = shininess,
	};
	return m;
}

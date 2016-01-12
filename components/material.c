#include <string.h>
#include "../components/enum.h"
#include "material.h"

/* NewMaterial creates a new material component from the given shader sources */
struct Material NewMaterial(uint32_t ambient, uint32_t diffuse,
    uint32_t specularity, uint32_t shininess)
{
  struct Material m = {
    .ambient = ambient,
    .diffuse = diffuse,
    .specularity = specularity,
    .shininess = shininess,
  };
  return m;
}
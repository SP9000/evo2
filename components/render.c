#include <assert.h>
#include <string.h>
#include "enum.h"
#include "render.h"
#include "../draw.h"

static struct Spritesheet loadedSheets[128];
static int numSheets = 0;

/**
 * LoadSheet loads a spritesheet from the file fileName 
 */
static struct Spritesheet * LoadSheet(const char *fileName)
{
  int i;
  size_t len;
  SDL_Surface *surf;
  struct Spritesheet *sheet;
  
  len = strlen(fileName);
  for(i = 0; i < numSheets; ++i) 
  {
    if(strncmp(loadedSheets[i].name, fileName, len) == 0)
    {
      return &loadedSheets[i];
    }
  }
  surf = SDL_LoadBMP(fileName);
  if(surf == NULL) 
  {
    return NULL;
  }
  sheet = &loadedSheets[i];
  sheet->tex = SDL_CreateTextureFromSurface(tv_DrawGetRenderer(), surf);
  sheet->w = surf->w;
  sheet->h = surf->h;
  sheet->xStep = 32;
  sheet->yStep = 32;

  numSheets++;
  SDL_FreeSurface(surf);
  return sheet;
}

static void Start(struct tv_Component *c)
{
  assert(tv_EntityGetComponent(c->entity, COMPONENT_TRANSFORM));
}

static size_t Size()
{
  return sizeof(struct Render);
}

struct Render * NewRender()
{
  struct Render *r;
  struct tv_Component *c;

  r = malloc(sizeof(struct Render));
  c = (struct tv_Component*)r;

  c->id     = COMPONENT_RENDER;
  c->Size   = Size;
  c->Start  = Start;
  r->sheet = NULL;  

  return r;
}

unsigned tv_EntityNumComponents(struct tv_Entity *e)
{
  return e->_numComponents;
}

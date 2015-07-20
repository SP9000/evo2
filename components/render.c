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
  struct Render *r;
  r = (struct Render*)c;

  r->transform = (struct Transform*)tv_EntityGetComponent(c->entity, COMPONENT_TRANSFORM);
  assert(r->transform);
}

/* TODO: for now, Update just renders a rectangle. */
static void Update(struct tv_Component *c)
{
  struct Render *r;
  SDL_Rect renderQuad;
  
  r = (struct Render*)c;

  renderQuad.x = 0;
  renderQuad.y = 0;
  renderQuad.w = r->transform->scale.x * 32;
  renderQuad.h = r->transform->scale.y * 32;
  
  SDL_SetRenderDrawColor(tv_DrawGetRenderer(), 255, 255, 0, 255);
  SDL_RenderFillRect(tv_DrawGetRenderer(), &renderQuad);
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
  c->Update = Update;

  r->sheet = NULL;  

  return r;
}


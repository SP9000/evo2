#include "transform.h"
#include "enum.h"

static void Start()
{
}

static void Update()
{
}

static size_t Size()
{
  return sizeof(struct Transform);
}

struct Transform * NewTransform()
{
  struct Transform *t;
  struct tv_Component *c;

  t = malloc(sizeof(struct Transform));
  c = (struct tv_Component*)t;

  c->id     = COMPONENT_TRANSFORM;
  c->Size   = Size;
  c->Update = Update;
  c->Start  = Start;

  t->pos     = tv_Vector3Zero;
  t->rot     = tv_Vector4Zero;
  t->scale.x = 1.0f;
  t->scale.y = 1.0f;
  t->scale.z = 1.0f;

  return t;
}


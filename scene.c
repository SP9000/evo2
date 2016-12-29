#include "scene.h"
#include "components/collider.h"
#include "components/enum.h"
#include "components/transform.h"
#include "debug.h"
#include "entity.h"

enum { SCENE_MAX_DYNAMIC_ENTITIES = 100 };

static struct tv_Entity *dynamicGraph[SCENE_MAX_DYNAMIC_ENTITIES];
static int numDynamic;

/* tv_SceneAdd adds e to the scene. */
// XXX
void tv_SceneAdd(struct tv_Entity *e) {
	static int seek;
	int i, wrap;

	if (numDynamic >= SCENE_MAX_DYNAMIC_ENTITIES)
		return;
	for (i = wrap = seek; i < SCENE_MAX_DYNAMIC_ENTITIES; ++i) {
		if (dynamicGraph[i] == NULL) {
			dynamicGraph[i] = e;
			break;
		}
		if (i == (wrap - 1)) {
			return;
		}
	}
	numDynamic++;
}

/* tv_SceneRemove removes e from the scene. */
void tv_SceneRemove(struct tv_Entity *e) {
	int i;
	if (numDynamic < 1)
		return;
	for (i = 0; i < SCENE_MAX_DYNAMIC_ENTITIES; ++i) {
		if (dynamicGraph[i] == e) {
			dynamicGraph[i] = NULL;
			break;
		}
	}
	if (i < SCENE_MAX_DYNAMIC_ENTITIES)
		numDynamic--;
}

#ifdef DEBUG
/* tv_ScenePrint prints a textual representation of the scenegraph. */
void tv_ScenePrint() {
	int i;
	debug_puts("dynamic scene entities:");
	for (i = 0; i < SCENE_MAX_DYNAMIC_ENTITIES; ++i) {
		if (dynamicGraph[i] != NULL)
			debug_printf(" %d: %p\n", i, dynamicGraph[i]);
	}
	debug_puts("end");
}
#endif

bool tv_SceneRaycast(tv_Vector3 start, tv_Vector3 dir, struct tv_Entity **) {
	int i;

	for (i = 0; i < numDynamic; ++i) {
		struct Collider *col;
		float a, b, radius;
		tv_Vector3 o, c, o_minus_c;
		struct Transform *t;
		struct tv_Entity *e;
		bool anyCollisions;

		e = dynamicGraph[i];
		t = (struct Transform *)tv_EntityGetComponent(
		    e, COMPONENT_TRANSFORM);
		col = (struct Collider *)tv_EntityGetComponent(
		    e, COMPONENT_COLLIDER);
		radius = col->radius;

		o = start;  /* origin of line */
		c = t->pos; /* center of sphere */
		tv_Vector3Sub(o, c, &o_minus_c);

		a = tv_Vector3Mag(&o_minus_c);
		a *= a;
		b = tv_Vector3Dot(dir, o_minus_c);
		b *= b;

		if (!anyCollisions) {
			anyCollisions = (b - a + (radius * radius)) >= 0.0f;
		}
	}
	return anyCollisions;
}

#if 0
enum{
  SCENE_MAX_CHILDREN = 16     /* max children per entity. */
  SCENE_MAX_PARENTS  = 16     /* max parents a node can have. */
  SCENE_MAX_ENTITIES = 1000   /* max entities in entire scene. */
};

/* node is a struct representing one object in the scene DAG. */
struct node{
  tv_Entity *e;
  uint16_t nodes[SCENE_MAX_CONNECTIVITY]; /* edges to each connected node. */
  uint16_t children[SCENE_MAX_CHILDREN];
  uint16_t parents[SCENE_MAX_PARENTS];
};

/* graph is the global scenegraph. */
static struct node graph[SCENE_MAX_ENTITIES];

/* addChild parents child to parent. */
static void addChild(int parent, int child)
{
  struct node *p, *c;
  int i;

  parent = &graph[parent];
  child = &graph[child];

  for(i = 0; p->children[i] != NULL; ++i){
    if(i > SCENE_MAX_CHILDREN) 
      return;
  }
  p->children[i] = child;
  for(i = 0; c->parents[i] != NULL; ++i){
    if(i > SCENE_MAX_PARENTS) 
      return;
  } 
  c->parents[i] = parent;
}

/* getID returns the ID (scenegraph array offset) of the entity e. */
static int getID(struct tv_Entity *e)
{
  //XXX: store ID's in table
  int i;
  for(i = 0; i < SCENE_MAX_ENTITIES; ++i){
    if(e == graph[i].e)
      return seek
  }
  return -1;
}

/* addNode creates a new node as a child of parent and adds it to the graph. */
static bool addNode(struct tv_Entity *e, struct node *parent)
{
  static int seek;
  int i;

  for(i = seek; graph[i].e != NULL; ++i)
    ;
  nodes[i].e = e;
  addChild(p, i);

  /* increment seek - in general allocations will trend upward. */
  seek++;
  if(seek > SCENE_MAX_CHILDREN)
    seek = 0; //XXX: reset to start of "dynamic" nodes
}

/* insert recursively inserts e into the scene.
 * case a) nodes do not overlap:
 *         i) return
 * case b) nodes overlap:
 *         i) add to current node
 *         ii) insert
 * case c) node contains node:
 *         i) insert
 */
static bool insert(struct node *parent, struct Collider *c)
{
  while(insert(e, c)){
    int i;
    for(i = 0; i < SCENE_MAX_CHILDREN; ++i){
      tv_Entity *p;
      p = parent->children[i];
      if(ColliderContains(p, c))
        insert(p, c);
      else if(ColliderOverlaps(p, c))
        addNode(p, c);
        insert(p, c);
      else{
        graph[nextFree].e = p;
        parent->children[i] = e;
      }
    }
  }
}

/* remove removes the given entity from the scene. */
static bool remove(struct tv_Entity *e)
{
  int i, j;
  int id;
  struct node *n;

  id = getID(e);
  if(id < 0)
    return;
  n = graph + id;

  for(i = 0; i < SCENE_MAX_PARENTS; ++i){
    struct node *p;
    if(n->parents[i] < 0)
      continue;

    p = &graph[n->children[i]];
    for(j = 0; j < SCENE_MAX_CHILDREN; ++j){
      if(p->children[j] == id)
        p->children[j] = 0;
    }
  }
}

/* tv_SceneAdd adds e to the scenegraph. */
void tv_SceneAdd(struct tv_Entity *e)
{
  struct Collider *c;
  c = tv_EntityGetComponent(e, COMPONENT_COLLIDER);
  insert(e, c);
}

/* tv_SceneUpdate updates e's position in the scenegraph. */
void tv_SceneUpdate(struct tv_Entity *e)
{
}

#ifdef DEBUG
static void printNode(node *n)
{
}
/* tv_ScenePrint prints a textual representation of the scenegraph. */
void tv_ScenePrint()
{
  int depth;
  char indent[SCENE_MAX_CHILDREN];

  tv_Entity *n = graph;
  while(n != NULL){
    printNode(n);
  }
}
#endif

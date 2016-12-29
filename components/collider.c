#include "collider.h"
#include "enum.h"
#include "transform.h"
#include "vector.h"

/* sphereIntoSphere returns true if c and into have overlapping radii. */
bool sphereIntoSphere(struct tv_Entity *c, struct tv_Entity *into) {
	struct Transform *t0, *t1;
	struct Collider *c0, *c1;
	int radius;

	t0 = (struct Transform *)tv_EntityGetComponent(c, COMPONENT_TRANSFORM);
	t1 = (struct Transform *)tv_EntityGetComponent(into,
	                                               COMPONENT_TRANSFORM);
	c0 = (struct Collider *)(tv_EntityGetComponent(c, COMPONENT_COLLIDER));
	c1 = (struct Collider *)(tv_EntityGetComponent(into,
	                                               COMPONENT_COLLIDER));
	radius = c0->radius + c1->radius;

	if (tv_Vector3Distance(t0->pos, t1->pos) < radius)
		return true;
	return false;
}

/* sphereContainsSphere returns true if into is completely inside c. */
bool sphereContainsSphere(struct tv_Entity *c, struct tv_Entity *into) {
	struct Transform *t0, *t1;
	struct Collider *c0, *c1;
	int radius;

	t0 = (struct Transform *)tv_EntityGetComponent(c, COMPONENT_TRANSFORM);
	t1 = (struct Transform *)tv_EntityGetComponent(into,
	                                               COMPONENT_TRANSFORM);
	c0 = (struct Collider *)(tv_EntityGetComponent(c, COMPONENT_COLLIDER));
	c1 = (struct Collider *)(tv_EntityGetComponent(into,
	                                               COMPONENT_COLLIDER));
	radius = abs(c0->radius - c1->radius);

	if (tv_Vector3Distance(t0->pos, t1->pos) < radius)
		return true;
	return false;
}

/* ColliderIsCollding returns true if c1 is colliding with c2. */
bool ColliderOverlaps(struct tv_Entity *c1, struct tv_Entity *c2) {
	return sphereIntoSphere(c1, c2);
}

/* ColliderContains returns true if c1 completely contains c2 */
bool ColliderContains(struct tv_Entity *c1, struct tv_Entity *c2) {
	return sphereContainsSphere(c1, c2);
}

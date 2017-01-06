#include "sys_render.h"
#include "components/cam.h"
#include "components/enum.h"
#include "components/material.h"
#include "components/mesh.h"
#include "components/transform.h"
#include "debug.h"
#include "draw.h"
#include "system.h"
#include "systems.h"

#define SYSTEM_RENDER_MAX_MESHES 2048
#define SYSTEM_RENDER_MAX_CAMS 8

static struct Transform *cam; /* the camera to render with */
static struct Cam *cams[SYSTEM_RENDER_MAX_CAMS];
static int numCams;

// XXX: proper scenegraph
static struct meshinfo {
	struct tv_Entity *e;
	struct Mesh *mesh;
	struct Transform *transform;
	struct Material *mat;
} meshes[SYSTEM_RENDER_MAX_MESHES];

/* start adds renderable geometry to the render system's scenegraph. */
static void start(struct tv_Entity *e) {
	int i;
	struct Transform *transform;
	struct Mesh *mesh;
	struct Material *mat;
	struct Cam *c;

	transform =
	    (struct Transform *)tv_EntityGetComponent(e, COMPONENT_TRANSFORM);
	mat = (struct Material *)tv_EntityGetComponent(e, COMPONENT_MATERIAL);
	mesh = (struct Mesh *)tv_EntityGetComponent(e, COMPONENT_MESH);

	if ((c = (struct Cam *)tv_EntityGetComponent(e, COMPONENT_CAM)) !=
	    NULL) {
		cam = transform;
		cams[numCams] = c;
		numCams++;
	}

	if (mesh != NULL) {
		// XXX: insert into scenegraph
		for (i = 0; i < SYSTEM_RENDER_MAX_MESHES; ++i) {
			if (meshes[i].mesh == NULL) {
				meshes[i].e = e;
				meshes[i].mesh = mesh;
				meshes[i].mat = mat;
				meshes[i].transform = transform;
				return;
			}
		}
	}
}

/* implements returns true if e is can be used by the render system. */
static bool implements(struct tv_Entity *e) {
	return (tv_EntityGetComponent(e, COMPONENT_TRANSFORM) != NULL) &&
	       (tv_EntityGetComponent(e, COMPONENT_MESH) != NULL);
}

/* update renders e. */
static void update(struct tv_Entity *e) {
	struct Mesh *mesh;
	struct Material *mat;
	struct Transform *t;
	struct Mat4x4 mv = Mat4x4Identity;

	mesh = (struct Mesh *)tv_EntityGetComponent(e, COMPONENT_MESH);
	mat = (struct Material *)tv_EntityGetComponent(e, COMPONENT_MATERIAL);
	t = (struct Transform *)tv_EntityGetComponent(e, COMPONENT_TRANSFORM);

	if (cam != NULL) {
		mat4x4_rotate_x(&mv, cam->rot.x);
		mat4x4_rotate_y(&mv, cam->rot.y);
		mat4x4_translate(&mv, -cam->pos.x, -cam->pos.y, -cam->pos.z);
	}

	mat4x4_translate(&mv, t->pos.x, t->pos.y, t->pos.z);
	tv_DrawModelview(&mv);
	tv_Draw(cams[0], mesh, mat);
}

/* InitRenderSystem initializes the rendering system. */
void InitRenderSystem() {
	struct tv_System sys = {.enabled = true,
	                        .Start = start,
	                        .Update = update,
	                        .Implements = implements,
	                        .GlobalUpdate = NULL};
	tv_RegisterSystem(&sys, SYSTEM_RENDER);
}

/* RenderSetEye sets the transform for the view the system renders from. */
void RenderSetEye(struct Transform *t) { cam = t; }

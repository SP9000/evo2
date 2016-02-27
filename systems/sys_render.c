#include "components/cam.h"
#include "components/enum.h"
#include "components/material.h"
#include "components/mesh.h"
#include "components/transform.h"
#include "debug.h"
#include "draw.h"
#include "system.h"
#include "sys_render.h"

#define SYSTEM_RENDER_MAX_MESHES 2048

static struct Transform *cam; /* the camera to render with */

//XXX: proper scenegraph
static struct meshinfo {
	struct Mesh *mesh;
	struct Transform *transform;
	struct Material *mat;
}meshes[SYSTEM_RENDER_MAX_MESHES];

/* start adds renderable geometry to the render system's scenegraph. */
static void start(struct tv_Entity *e)
{
	int i;
	struct Transform *transform;
	struct Mesh *mesh;
	struct Material *mat;

	transform = (struct Transform*)tv_EntityGetComponent(e,
			COMPONENT_TRANSFORM);
	mat = (struct Material*)tv_EntityGetComponent(e,
			COMPONENT_MATERIAL);
	mesh = (struct Mesh*)tv_EntityGetComponent(e,
			COMPONENT_MESH);

	if(tv_EntityGetComponent(e, COMPONENT_CAM) != NULL){
		cam = transform;
	}

	if(mesh != NULL){
		//XXX: insert into scenegraph
		for(i = 0; i < SYSTEM_RENDER_MAX_MESHES; ++i){
			if(meshes[i].mesh == NULL){
				meshes[i].mesh = mesh;
				meshes[i].mat = mat;
				meshes[i].transform = transform;
				return;
			}
		}
	}
}

/* update does nothing. */
static void update(struct tv_Entity *e)
{
}

/* render renders the scene as seen by cam. */
static void render()
{
	int i;
	struct Mat4x4 mv = Mat4x4Identity;

	if(cam != NULL){
		//mat4x4_rotate(&mv, cam->rot.x, 1.0f, 0.0f, 0.0f);
		//mat4x4_rotate(&mv, cam->rot.y, 0.0f, 1.0f, 0.0f);
		mat4x4_rotate_y(&mv, cam->rot.y);
		mat4x4_translate(&mv,-cam->pos.x, -cam->pos.y, -cam->pos.z - 6.0f);
	}

	//XXX: render from scenegraph
	for(i = 0; i < SYSTEM_RENDER_MAX_MESHES; ++i){
		if(meshes[i].mesh != NULL){
			struct meshinfo *m = &meshes[i];
			mat4x4_push(&mv);
			mat4x4_translate(&mv,
					-m->transform->pos.x,
					-m->transform->pos.y,
					-m->transform->pos.z);
			tv_DrawModelview(&mv);
			tv_Draw(m->mesh, m->mat);
			mat4x4_pop(&mv);
		}
	}
}

/* InitRenderSystem initializes the rendering system. */
void InitRenderSystem()
{
	struct tv_System sys = {
		.enabled = true,
		.Start = start,
		.Update = update,
		.Implements = NULL,
		.GlobalUpdate = render
	};
	tv_RegisterSystem(&sys);
}

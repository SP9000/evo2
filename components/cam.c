#include "cam.h"
#include "matrix.h"
#include "scene.h"
#include "vector.h"

const float screen_w = 640;
const float screen_h = 480;

/* NewCam creates and returns a new camera component */
struct Cam NewCam() {
	struct Cam c = {.C = {.size = sizeof(struct Cam)},
	                .pos = {0, 0, 0},
	                .rot = {0, 0, 0},
	                .viewport = {0, 0, 640, 480}};
	mat4x4_perspective(&c.proj, 30.0f, 640.0f / 480.0f, 0, 100);
	return c;
}

/* tv_CamSceneToScreen applies the camera's modelview-projection
 * matrix to the given scene coordinates and returns the clip coordinates of the
 * given scene position.
 */
tv_Vector2 tv_CamSceneToScreen(struct Cam *c, tv_Vector3 scene_coordinates) {
	struct Mat4x4 mv;
	tv_Vector4 res;
	tv_Vector2 ret;
	res.x = scene_coordinates.x;
	res.y = scene_coordinates.y;
	res.z = scene_coordinates.z;
	res.w = 1.0f;

	mat4x4_load_identity(&mv);
	mat4x4_translate(&mv, c->pos.x, c->pos.y, c->pos.z);
	mat4x4_rotate(&mv, c->rot.x, 1.0f, 0.0f, 0.0f);
	mat4x4_rotate(&mv, c->rot.y, 0.0f, 1.0f, 0.0f);
	mat4x4_rotate(&mv, c->rot.z, 0.0f, 0.0f, 1.0f);

	res = mat4x4_multiply_vec4x1(mv, res);
	res = mat4x4_multiply_vec4x1(c->proj, res);
	ret.x = (1.0f / res.w) * res.x * 0.5f + 0.5f;
	ret.y = (1.0f / res.w) * res.y * 0.5f + 0.5f;

	return ret;
}

/* tv_scene_raypick casts a ray from camera c at the given screen_coordinates */
bool tv_CamRaypick(struct Cam *c, tv_Vector2 screen_coordinates,
                   struct tv_Entity **hits) {
	struct Mat4x4 mv, pv_mat, inv_vp;
	tv_Vector3 start, dir;
	tv_Vector4 v;

	tv_Vector2 clip_coords;
	tv_Vector4 world1, world2;

	clip_coords.x = (screen_coordinates.x) / (float)screen_w * 2.0f - 1.0f;
	clip_coords.y =
	    ((float)screen_h - screen_coordinates.y) / (float)screen_h * 2.0f -
	    1.0f;

	/* apply view transformations to get view matrix (no model
	 * transformations) */
	mat4x4_load_identity(&mv);
	mat4x4_translate(&mv, c->pos.x, c->pos.y, c->pos.z);
	mat4x4_rotate(&mv, c->rot.x, 1.0f, 0.0f, 0.0f);
	mat4x4_rotate(&mv, c->rot.y, 0.0f, 1.0f, 0.0f);
	mat4x4_rotate(&mv, c->rot.z, 0.0f, 0.0f, 1.0f);

	/* perspective-view matrix */
	pv_mat = mat4x4_multiply(c->proj, mv);
	/* calcualate inverse (and verify if exists) */
	if (!mat4x4_inverse(pv_mat, &inv_vp)) {
		return NULL;
	}

	/* near plane */
	v.x = clip_coords.x;
	v.y = clip_coords.y;
	v.z = -1.0f;
	v.w = 1.0f;

	world1 = mat4x4_multiply_vec4x1(inv_vp, v);
	if (world1.w == 0.0f) {
		return NULL;
	}

	world1.w = 1.0f / world1.w;
	world1.x *= world1.w;
	world1.y *= world1.w;
	world1.z *= world1.w;

	/* far plane */
	v.z = 0.0f;
	world2 = mat4x4_multiply_vec4x1(inv_vp, v);
	if (world2.w == 0.0f) {
		return NULL;
	}

	world2.w = 1.0f / world2.w;
	world2.x *= world2.w;
	world2.y *= world2.w;
	world2.z *= world2.w;

	/* get the direction */
	tv_Vector4Sub(world2, world1, &v);
	dir.x = v.x;
	dir.y = v.y;
	dir.z = v.z;
	tv_Vector3Normalize(dir, &dir);

	start.x = world1.x;
	start.y = world1.y;
	start.z = world1.z;
	printf(
	    "casting ray: origin @ (%f, %f, %f)\n  direction: (%f, %f, %f)\n",
	    start.x, start.y, start.z, dir.x, dir.y, dir.z);

	return tv_SceneRaycast(start, dir, hits);
}

void tv_CamSetViewport(struct Cam *c, uint32_t x, uint32_t y, uint32_t w,
                       uint32_t h) {
	c->viewport.x = x;
	c->viewport.y = y;
	c->viewport.w = w;
	c->viewport.h = h;
}

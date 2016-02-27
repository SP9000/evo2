#include <string.h>
#include "components/enum.h"
#include "entity.h"
#include "mesh.h"

/* getVertex returns the ith vertex belonging to mesh. */
static uint8_t * getVertex(struct Mesh *mesh, unsigned i)
{
	if(i > mesh->numVerts || mesh->numBuffs < 1)
		return NULL;
	return mesh->buffers[i * 4];
}

/* getAABB generates an AABB for mesh. */
static void getAABB(struct Mesh *mesh)
{
	uint8_t minX, maxX;
	uint8_t minY, maxY;
	uint8_t minZ, maxZ;
	unsigned i;

	if(mesh->numVerts <= 0 || mesh->numBuffs < 1)
		return;

	for(i = 0; i < mesh->numVerts; ++i){
		uint8_t *v;
		v = getVertex(mesh, i);
		if(v[0] < minX)
			minX = v[0];
		if(v[0] > maxX)
			maxX = v[0];

		if(v[0] < minY)
			minY = v[1];
		if(v[0] > maxY)
			maxY = v[1];

		if(v[0] < minZ)
			minZ = v[2];
		if(v[0] > maxZ)
			maxZ = v[2];
	}

	mesh->aabb.w = maxX - minX;
	mesh->aabb.h = maxY - minY;
	mesh->aabb.d = maxZ - minZ;
}

/* makeQuad initializes the mesh component c to a simple white quad. */
static void makeQuad(void *c)
{
	struct Mesh *m;
	struct MeshBuffer *vb, *cb;
	const struct MeshAttr pos[] = {
		{.pos = {0,0,0,255}},
		{.pos = {255,0,0,255}},
		{.pos = {255,255,0,255}},

		{.pos = {0,0,0,255}},
		{.pos = {255,255,0,255}},
		{.pos = {0,255,0,255}}
	};
	const struct MeshAttr col[] = {
		{.col = {0xff,0xff,0xff,0xff}},
		{.col = {0xff,0xff,0xff,0xff}},
		{.col = {0xff,0xff,0xff,0xff}},

		{.col = {0xff,0xff,0xff,0xff}},
		{.col = {0xff,0xff,0xff,0xff}},
		{.col = {0xff,0xff,0xff,0xff}}
	};

	m = (struct Mesh*)c;
	vb = (struct MeshBuffer*)(m->buffers);
	cb = (struct MeshBuffer*)(m->buffers + sizeof(pos));

	vb->type = TV_VERTEX_ATTR_POS;
	cb->type = TV_VERTEX_ATTR_COL;
	memcpy(vb, pos, sizeof(pos));
	memcpy(cb, col, sizeof(col));
};

/* tv_NewMesh creates a new mesh pre-allocated with room for n vertices. */
struct Mesh NewMesh(uint16_t n, uint16_t buffs)
{
	struct Mesh mesh = {
		.C = {
			.size = sizeof(struct Mesh) + n
				* sizeof(struct MeshAttr) * buffs,
		},
		.primitive = TV_VERTEX_PRIMITIVE_TRIANGLES,
		.numVerts = n,
		.numBuffs = 0
	};
	return mesh;
}

/* MeshNewQuad creates returns a new mesh of a white qud. */
struct Mesh MeshNewQuad()
{
	struct Mesh mesh = {
		.C = {
			.size = sizeof(struct Mesh) + 6
				* sizeof(struct MeshAttr) * 2,
			.init = makeQuad
		},
		.primitive = TV_VERTEX_PRIMITIVE_TRIANGLES,
		.numVerts = 6,
		.numBuffs = 0,
	};
	return mesh;
}

#include "mesh.h"
#include "debug.h"
#include "entity.h"
#include <string.h>

#include "components/enum.h"

/* attrSize returns the size of the given vertex attribute in bytes. */
static unsigned attrSize(enum MeshAttrType a) {
	switch (a) {
	case TV_VERTEX_ATTR_POS:
		return 4 * sizeof(uint8_t);
	case TV_VERTEX_ATTR_COL:
		return 4 * sizeof(uint8_t);
	case TV_VERTEX_ATTR_UV:
		return 2 * sizeof(uint16_t);
	default:
		break;
	}

	debug_printf("unrecognized vertex attribute %d\n", a);
	return 4;
}

/* buffOffset returns the offset of the idxth buffer. */
static unsigned buffOffset(struct Mesh *m, unsigned idx) {
	unsigned i, offset;

	offset = 0;
	for (i = 0; i < idx; ++i) {
		offset += attrSize(m->attributes[i]) * m->numVerts;
	}
	return offset;
}

/* getVertex returns the ith vertex belonging to mesh. */
static uint8_t *getVertex(struct Mesh *mesh, unsigned i) {
	if (i > mesh->numVerts || mesh->numBuffs < 1)
		return NULL;
	return mesh->buffers + (i * 4);
}

/* getAABB generates an AABB for mesh. */
static void getAABB(struct Mesh *mesh) {
	uint8_t minX, maxX;
	uint8_t minY, maxY;
	uint8_t minZ, maxZ;
	unsigned i;

	if (mesh->numVerts <= 0 || mesh->numBuffs < 1)
		return;

	for (i = 0; i < mesh->numVerts; ++i) {
		uint8_t *v;
		v = getVertex(mesh, i);
		if (v[0] < minX)
			minX = v[0];
		if (v[0] > maxX)
			maxX = v[0];

		if (v[0] < minY)
			minY = v[1];
		if (v[0] > maxY)
			maxY = v[1];

		if (v[0] < minZ)
			minZ = v[2];
		if (v[0] > maxZ)
			maxZ = v[2];
	}

	mesh->aabb.w = maxX - minX;
	mesh->aabb.h = maxY - minY;
	mesh->aabb.d = maxZ - minZ;
}

/* makeQuad initializes the mesh component c to a simple white quad. */
static void makeQuad(void *c) {
	struct Mesh *m;
	struct MeshBuffer *vb, *cb;
	const struct MeshAttr pos[] = {
	    {.pos = {0, 0, 0, 255}},     {.pos = {255, 0, 0, 255}},
	    {.pos = {255, 255, 0, 255}},

	    {.pos = {0, 0, 0, 255}},     {.pos = {255, 255, 0, 255}},
	    {.pos = {0, 255, 0, 255}}};
	const struct MeshAttr col[] = {{.col = {0xff, 0xff, 0xff, 0xff}},
	                               {.col = {0xff, 0xff, 0xff, 0xff}},
	                               {.col = {0xff, 0xff, 0xff, 0xff}},

	                               {.col = {0xff, 0xff, 0xff, 0xff}},
	                               {.col = {0xff, 0xff, 0xff, 0xff}},
	                               {.col = {0xff, 0xff, 0xff, 0xff}}};

	m = (struct Mesh *)c;
	vb = (struct MeshBuffer *)(m->buffers);
	cb = (struct MeshBuffer *)(m->buffers + sizeof(pos));

	m->numBuffs = 2;
	m->attributes[0] = TV_VERTEX_ATTR_POS;
	m->attributes[1] = TV_VERTEX_ATTR_COL;
	memcpy(vb, pos, sizeof(pos));
	memcpy(cb, col, sizeof(col));
};

/* tv_NewMesh creates a new mesh pre-allocated with room for n vertices. */
struct Mesh NewMesh(uint16_t n, uint16_t buffs) {
	// XXX: stupidly reserves 16 bytes per vertex regardless of attribute
	// type
	struct Mesh mesh = {.C =
	                        {
	                            .size = sizeof(struct Mesh) +
	                                    n * 16 * sizeof(uint8_t) * buffs,
	                        },
	                    .primitive = TV_VERTEX_PRIMITIVE_TRIANGLES,
	                    .numVerts = n,
	                    .numBuffs = 0};
	return mesh;
}

/* MeshNewQuad creates and returns a new mesh of a white quad. */
struct Mesh MeshNewQuad() {
	struct Mesh mesh = {
	    .C = {.size = sizeof(struct Mesh) + 6 * sizeof(struct MeshAttr) * 2,
	          .init = makeQuad},
	    .primitive = TV_VERTEX_PRIMITIVE_TRIANGLES,
	    .numVerts = 6,
	    .numBuffs = 0,
	};
	return mesh;
}

/* MeshGetBufferAt returns the address of the mesh's ith buffer. */
uint8_t *MeshGetBufferAt(struct Mesh *mesh, unsigned i) {
	if (mesh == NULL) {
		debug_puts("NULL mesh");
		return NULL;
	}
	if (i >= mesh->numBuffs) {
		debug_printf("buffer index %d out of range.\n", i);
		return NULL;
	}

	return mesh->buffers + buffOffset(mesh, i);
}

/* MeshGetBuffer returns the buffer of the given attribute type. */
uint8_t *MeshGetBuffer(struct Mesh *mesh, enum MeshAttrType type) {
	unsigned i;

	for (i = 0; i < mesh->numBuffs; ++i) {
		if (mesh->attributes[i] == type) {
			return mesh->buffers + buffOffset(mesh, i);
		}
	}

	return NULL;
}

/* MeshColor sets all of mesh's vertices to the color c. */
void MeshColor(struct Mesh *mesh, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	unsigned i;
	uint8_t *cb;

	cb = MeshGetBuffer(mesh, TV_VERTEX_ATTR_COL);
	if (cb == NULL) {
		return;
	}

	for (i = 0; i < (mesh->numVerts * 4); i += 4) {
		cb[i + 0] = r;
		cb[i + 1] = g;
		cb[i + 2] = b;
		cb[i + 3] = a;
	}
}

/* MeshSetVertices sets the vertices of mesh to vertices. */
void MeshSetVertices(struct Mesh *mesh, uint16_t *vertices) {
	unsigned i;
	uint8_t *vb;

	vb = MeshGetBuffer(mesh, TV_VERTEX_ATTR_POS);
	if (vb == NULL) {
		return;
	}

	for (i = 0; i < (mesh->numVerts * 3); i += 3) {
		vb[i + 0] = vertices[i];
		vb[i + 1] = vertices[i + 1];
		vb[i + 2] = vertices[i + 2];
	}
}

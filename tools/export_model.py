import numpy as np
import sys
import trimesh

# normalize a vertex (to the range 0-255)
def normalize(v):
    return [int(v[0]), int(v[1]), int(v[2])] # XXX

if len(sys.argv) < 2:
    print("Usage: {0} model_filename\n", sys.argv[0])
    exit(0)

mesh = trimesh.load_mesh(sys.argv[1])
print len(mesh.vertices)
verts = mesh.vertices
faces = mesh.faces

for v0, v1, v2 in faces:
    o_face = [normalize(verts[v0]), normalize(verts[v1]), normalize(verts[v2])]
    for f in o_face:
        print("{0},{1},{2},{3}\n", f[0], f[1], f[2], 0xff)
        print("{0},{1},{2},{3}\n", 0xff,0xff,0xff,0xff)

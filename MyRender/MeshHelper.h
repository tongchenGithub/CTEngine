#ifndef __MeshHelper_H__
#define __MeshHelper_H__

#include "Vertex.h"

struct Face {
	int i1, i2, i3;
};

char *ReadFile(const char* file);

int LoadMesh(const char *file, Vertex*& pVertexs, int& vsize, Face*& pFaces, int& fsize);

#endif

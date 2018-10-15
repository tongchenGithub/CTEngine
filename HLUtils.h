#ifndef __BitmapHelper_H__
#define __BitmapHelper_H__
#include <string>

#include "Vertex.h"

struct Face {
	int i1, i2, i3;
};

char *ReadFile(const char* file);

// <summary>
/// ����һ������ģ��
/// </summary>
int LoadMesh(const char *file, Vertex*& pVertexs, int& vsize, Face*& pFaces, int& fsize);

// <summary>
/// ����BMP
/// </summary>
int* LoadBitmapFromFile(std::wstring filePath);

#endif
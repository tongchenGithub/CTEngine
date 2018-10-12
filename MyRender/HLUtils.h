#ifndef __BitmapHelper_H__
#define __BitmapHelper_H__
#include <string>

#include "Vertex.h"

struct Face {
	int i1, i2, i3;
};

char *ReadFile(const char* file);

// <summary>
/// 加载一批顶点模型
/// </summary>
int LoadMesh(const char *file, Vertex*& pVertexs, int& vsize, Face*& pFaces, int& fsize);

// <summary>
/// 加载BMP
/// </summary>
int* LoadBitmapFromFile(std::wstring filePath);

#endif
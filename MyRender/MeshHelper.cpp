#include "MeshHelper.h"
#include <stdio.h>
#include <tchar.h>

char *ReadFile(const char* file)
{
	FILE *pFile = fopen(file, "rb");
	if (!pFile) {
		return NULL;
	}

	char *pBuf;
	fseek(pFile, 0, SEEK_END);
	int len = ftell(pFile);
	pBuf = new char[len + 1];
	rewind(pFile);
	fread(pBuf, 1, len, pFile);
	pBuf[len] = '\0';
	fclose(pFile);
	return pBuf;
}

int LoadMesh(const char *file, Vertex*& pVertexs, int& vsize, Face*& pFaces, int& fsize)
{
	char* pFile;
	pFile = ReadFile(file);
	if (!pFile) {
		return 0;
	}

	char* pSrc;
	pSrc = pFile;

	int i, vc, fc;

	// 计算顶点和面的个数
	i = 0, vc = 0, fc = 0;
	char line[1024];
	memset(line, 0, 1024);
	for (; *pSrc != '\0';) {
		if (*pSrc == '\n') {
			if (line[0] == 'v') {
				++vc;
			}
			else if (line[0] == 'f') {
				++fc;
			}

			i = 0;
			memset(line, 0, 1024);
		}
		else {
			if (i > 1024) {
				delete pFile;
				return 0;
			}
			line[i++] = *pSrc;
		}
		++pSrc;
	}
	if (vc == 0 || fc == 0) {
		delete pFile;
		return 0;
	}

	vsize = vc; fsize = fc;
	pVertexs = new Vertex[vc];
	pFaces = new Face[fc];

	pSrc = pFile;

	// 读取数据
	i = 0, vc = 0, fc = 0;
	memset(line, 0, 1024);
	for (; *pSrc != '\0';) {
		if (*pSrc == '\n') {
			if (line[0] == 'v') {
				float x, y, z;
				sscanf(line, "v %f %f %f", &x, &y, &z);

				pVertexs[vc++] = { { x, y, z, 1.f },{ 0.f, 0.f, 0.f },{ 0.f, 1.f },{ 0.f, 0.f, 0.f }, 1.f };
			}
			else if (line[0] == 'f') {
				int p1, p2, p3;
				sscanf(line, "f %d %d %d", &p1, &p2, &p3);

				pFaces[fc++] = { p1 - 1, p2 - 1, p3 - 1 };
			}

			i = 0;
			memset(line, 0, 1024);
		}
		else {
			line[i++] = *pSrc;
		}
		++pSrc;
	}

	delete pFile;

	return 1;
}
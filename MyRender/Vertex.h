#ifndef __Vertex_H__
#define __Vertex_H__
#include "3DMath.h"

struct Color 
{
	float r;
	float g;
	float b; 
};

struct Texcoord 
{
	float u;
	float v; 
};

struct Vertex
{ // ��
	Vector pos;		// ����
	Color color;	// ��ɫ
	Texcoord tex;	// UV
	Vector normal;	// 
	float rhw;		// ͸�ӽ��� rhw = 1/w 
};
#endif
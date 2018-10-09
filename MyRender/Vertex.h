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
{ // 点
	Vector pos;		// 坐标
	Color color;	// 颜色
	Texcoord tex;	// UV
	Vector normal;	// 
	float rhw;		// 透视矫正 rhw = 1/w 
};
#endif
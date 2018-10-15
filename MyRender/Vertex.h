#ifndef __Vertex_H__
#define __Vertex_H__
#include "3DMath.h"

struct VColor
{
	float r;
	float g;
	float b; 

	VColor &operator+(const VColor& v) {
		r += v.r;
		g += v.g;
		b += v.b;
		return *this;
	}

	VColor &operator*(const float& f) {
		r *= f;
		g *= f;
		b *= f;
		return *this;
	}

	VColor &operator*(const VColor& v) {
		r *= v.r;
		g *= v.g;
		b *= v.b;
		return *this;
	}
};



struct Texcoord 
{
	float u;
	float v; 
};

struct Vertex
{ // 点
	Vector pos;		// 坐标
	VColor color;	// 颜色
	Texcoord tex;	// UV
	Vector normal;	// 法向量
	float rhw;		// 透视矫正 rhw = 1/w 
};
#endif
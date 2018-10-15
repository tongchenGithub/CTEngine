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
{ // ��
	Vector pos;		// ����
	VColor color;	// ��ɫ
	Texcoord tex;	// UV
	Vector normal;	// ������
	float rhw;		// ͸�ӽ��� rhw = 1/w 
};
#endif
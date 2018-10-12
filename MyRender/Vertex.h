#ifndef __Vertex_H__
#define __Vertex_H__
#include "3DMath.h"

struct VColor
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
	VColor color;	// ��ɫ
	Texcoord tex;	// UV
	Vector normal;	// ԭ�㵽�õ������
	float rhw;		// ͸�ӽ��� rhw = 1/w 
};
#endif
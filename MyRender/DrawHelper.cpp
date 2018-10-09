#include "DrawHelper.h"

// ����һ��ƽ��
void DrawPlane(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4)
{
	// ���������ƶ�һ��������Ȼ���ҵ���
	Vertex t1 = v1, t2 = v2, t3 = v3, t4 = v4;
	t1.tex.u = 0.f; t2.tex.u = 1.f; t3.tex.u = 1.f; t4.tex.u = 0.f;
	t1.tex.v = 0.f; t2.tex.v = 0.f; t3.tex.v = 1.f; t4.tex.v = 1.f;

	device->drawTriangle(t1, t2, t3);
	device->drawTriangle(t3, t4, t1);
}

// ����������
void DrawBox(float theta, float updown, float leftright)
{
	Matrix mm, rt, m;
	MatrixSetRotate(mm, 0.f, 1.f, 0.f, theta);	// ��ת����
	MatrixSetTranslate(rt, leftright, updown, 0.f);// ƽ�ƾ���
	MatrixMul(m, mm, rt);
	transform->setWorld(m);
	transform->update();

	Vertex vs[8] = {
		{ { -1.f,  1.f, -1.f, 1.f },{ 1.0f, 0.0f, 0.0f },{ 0.f, 0.f },{ -1.f,  1.f, -1.f, 0.f },  1.f },
		{ { -1.f,  1.f,  1.f, 1.f },{ 0.0f, 1.0f, 0.0f },{ 0.f, 1.f },{ -1.f,  1.f,  1.f, 0.f }, 1.f },
		{ { 1.f,  1.f,  1.f, 1.f },{ 0.0f, 0.0f, 1.0f },{ 1.f, 1.f },{ 1.f,  1.f,  1.f, 0.f }, 1.f },
		{ { 1.f,  1.f, -1.f, 1.f },{ 1.0f, 1.0f, 0.0f },{ 0.f, 1.f },{ 1.f,  1.f, -1.f, 0.f }, 1.f },

		{ { -1.f, -1.f, -1.f, 1.f },{ 0.0f, 0.0f, 1.0f },{ 1.f, 0.f },{ -1.f, -1.f, -1.f, 0.f }, 1.f },
		{ { -1.f, -1.f,  1.f, 1.f },{ 1.0f, 1.0f, 0.0f },{ 0.f, 1.f },{ -1.f, -1.f,  1.f, 0.f }, 1.f },
		{ { 1.f, -1.f,  1.f, 1.f },{ 1.0f, 0.0f, 0.0f },{ 1.f, 1.f },{ 1.f, -1.f,  1.f, 0.f }, 1.f },
		{ { 1.f, -1.f, -1.f, 1.f },{ 0.0f, 1.0f, 0.0f },{ 1.f, 1.f },{ 1.f, -1.f, -1.f, 0.f }, 1.f },
	};

	DrawPlane(vs[0], vs[1], vs[2], vs[3]);
	DrawPlane(vs[7], vs[4], vs[0], vs[3]);
	DrawPlane(vs[2], vs[6], vs[7], vs[3]);
	DrawPlane(vs[5], vs[1], vs[0], vs[4]);
	DrawPlane(vs[2], vs[1], vs[5], vs[6]);
	DrawPlane(vs[6], vs[5], vs[4], vs[7]);
}

// ����4����
void DrawTetrahedron(float theta, float updown, float leftright)
{
	Matrix mm, rt, m;
	MatrixSetRotate(mm, 0.f, 1.f, 0.f, theta);	// ��ת����
	MatrixSetTranslate(rt, leftright, updown, 0.f);
	MatrixMul(m, mm, rt);
	transform->setWorld(m);
	transform->update();

	Vertex vs[4] = {
		{ { 0.f,  0.f,  1.f, 1.f },{ 1.0f, 0.0f, 0.0f } },
		{ { -1.f,  0.f, -1.f, 1.f },{ 0.0f, 1.0f, 0.0f } },
		{ { 1.f,  0.f, -1.f, 1.f },{ 0.0f, 0.0f, 1.0f } },
		{ { 0.f,  2.f,  0.f, 1.f },{ 1.0f, 1.0f, 1.0f } },
	};

	device->drawTriangle(vs[1], vs[3], vs[2]);
	device->drawTriangle(vs[2], vs[3], vs[0]);
	device->drawTriangle(vs[0], vs[3], vs[1]);
	device->drawTriangle(vs[0], vs[1], vs[2]);
}
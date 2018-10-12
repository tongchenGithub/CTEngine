#include "HLUtils.h"
#include "Screen.h"
#include "Device.h"
#include "Transform.h"
#include "TypeDefine.h"
#include "Vertex.h"
#include "Light.h"
#include <tchar.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Screen* screen = NULL;
Device* device = NULL;
Transform* transform = NULL;
int *textures[3] = { 0,0,0 };

// 创建立方体纹理
int* CreateTexture()
{
	int *tex = (int*)malloc(100 * 100 * sizeof(int));

	int color[10][10];

	int c = 0x54FF9F;
	for (int i = 0; i < 10; i++) {
		int c1 = c;
		for (int j = 0; j < 10; j++) {
			color[i][j] = c1;
			c1 = (c1 == 0xffffff ? 0x54FF9F : 0xffffff); // 每次循环变化一种颜色
		}
		c = c == 0xffffff ? 0x54FF9F : 0xffffff;
	}

	// 100 x 100
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			tex[i * 100 + j] = color[i / 10][j / 10]; // 其实就是颜色相间的数组
		}
	}

	return tex;
}

// 绘制一个平面
void DrawPlane(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4)
{
	// 必须重新制定一下纹理，不然就乱掉了
	Vertex t1 = v1, t2 = v2, t3 = v3, t4 = v4;
	t1.tex.u = 0.f; t2.tex.u = 1.f; t3.tex.u = 1.f; t4.tex.u = 0.f;
	t1.tex.v = 0.f; t2.tex.v = 0.f; t3.tex.v = 1.f; t4.tex.v = 1.f;

	device->drawTriangle(t1, t2, t3);
	device->drawTriangle(t3, t4, t1);
}

// 绘制立方体
void DrawBox(float theta, float updown, float leftright)
{
	Matrix mm, rt, m;
	MatrixSetRotate(mm, 0.f, 1.f, 0.f, theta);	// 旋转矩阵
	MatrixSetTranslate(rt, leftright, updown, 0.f);// 平移矩阵
	MatrixMul(m, mm, rt);
	transform->setWorld(m);
	transform->update();

	Vertex vs[8] = {
		// 上4点
		{ { -1.f,  1.f, -1.f, 1.f },{ 1.0f, 0.0f, 0.0f },{ 0.f, 0.f },{ -1.f,  1.f, -1.f, 0.f },  1.f },
		{ { -1.f,  1.f,  1.f, 1.f },{ 0.0f, 1.0f, 0.0f },{ 0.f, 1.f },{ -1.f,  1.f,  1.f, 0.f }, 1.f },
		{ { 1.f,  1.f,  1.f, 1.f },{ 0.0f, 0.0f, 1.0f },{ 1.f, 1.f },{ 1.f,  1.f,  1.f, 0.f }, 1.f },
		{ { 1.f,  1.f, -1.f, 1.f },{ 1.0f, 1.0f, 0.0f },{ 0.f, 1.f },{ 1.f,  1.f, -1.f, 0.f }, 1.f },
		// 下4点
		{ { -1.f, -1.f, -1.f, 1.f },{ 0.0f, 0.0f, 1.0f },{ 1.f, 0.f },{ -1.f, -1.f, -1.f, 0.f }, 1.f },
		{ { -1.f, -1.f,  1.f, 1.f },{ 1.0f, 1.0f, 0.0f },{ 0.f, 1.f },{ -1.f, -1.f,  1.f, 0.f }, 1.f },
		{ { 1.f, -1.f,  1.f, 1.f },{ 1.0f, 0.0f, 0.0f },{ 1.f, 1.f },{ 1.f, -1.f,  1.f, 0.f }, 1.f },
		{ { 1.f, -1.f, -1.f, 1.f },{ 0.0f, 1.0f, 0.0f },{ 1.f, 1.f },{ 1.f, -1.f, -1.f, 0.f }, 1.f },
	};

	DrawPlane(vs[0], vs[1], vs[2], vs[3]); // 上
	DrawPlane(vs[7], vs[4], vs[0], vs[3]); // 正
	DrawPlane(vs[2], vs[6], vs[7], vs[3]); // 右
	DrawPlane(vs[5], vs[1], vs[0], vs[4]); // 左
	DrawPlane(vs[2], vs[1], vs[5], vs[6]); // 对面
	DrawPlane(vs[6], vs[5], vs[4], vs[7]); // 正面
}

// 绘制4面体
void DrawTetrahedron(float theta, float updown, float leftright)
{
	Matrix mm, rt, m;
	MatrixSetRotate(mm, 0.f, 1.f, 0.f, theta);	// 旋转矩阵
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

void FixNormal(Vertex& v1, Vertex& v2, Vertex& v3)
{
	Vector& p1 = v1.pos;
	Vector& p2 = v2.pos;
	Vector& p3 = v3.pos;

	Vector edge1, edge2, pn;
	VectorSub(edge1, p2, p1);
	VectorSub(edge2, p3, p2);
	VectorCrossProduct(pn, edge1, edge2);
	VectorNormalize(pn);

	pn.w = 0.f;

	v1.normal = pn;
	v2.normal = pn;
	v3.normal = pn;
}

void FixUv(Vertex& v1, Vertex& v2, Vertex& v3)
{
	v1.tex.u = 0.0f; v1.tex.v = 0.0f;
	v2.tex.u = 0.0f; v2.tex.v = 0.0f;
	v3.tex.u = 0.0f; v3.tex.v = 0.0f;
}

// 绘制已加载的模型
void DrawModel(Vertex* pVertexs, int vsize, Face* pFaces, int fsize, float theta)
{
	Matrix m;
	MatrixSetRotate(m, 0.f, 3.0f, 0.f, theta);
	transform->setWorld(m);
	transform->update();

	int i;
	for (i = 0; i < fsize; i++) {
		int i1 = pFaces[i].i1;
		int i2 = pFaces[i].i2;
		int i3 = pFaces[i].i3;

		Vertex v1 = pVertexs[i1];
		Vertex v2 = pVertexs[i2];
		Vertex v3 = pVertexs[i3];

		FixNormal(v1, v2, v3);
		FixUv(v1, v2, v3);
		device->drawTriangle(v1, v2, v3);
	}
}

void SetCamera(float x, float y, float z)
{
	Vector eye = { x, y, z, 1.f }, at = { 0.f, 0.f, 0.f, 1.f }, up = { 0.f, 1.f, 0.f, 1.f };
	Matrix m;
	MatrixSetLookAt(m, eye, at, up);
	transform->setView(m);
	transform->update();
}

void TransformLight(Light& light, float theta)
{
	Matrix m;
	MatrixSetRotate(m, 0.f, 1.0f, 0.f, theta);
	transform->setWorld(m);
	transform->update();

	transform->applyMV(light.direction, { -0.3f, 5.f, -0.3f, 0.f });
	VectorNormalize(light.direction);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	screen = new Screen();
	int ret = screen->init(WINDOW_WIDTH, WINDOW_HEIGHT, _T("3DRender"));
	if (ret < 0) {
		printf("screen init failed(%d)!\n", ret);
		exit(ret);
	}

	transform = new Transform();
	transform->init(WINDOW_WIDTH, WINDOW_HEIGHT);

	textures[0] = CreateTexture();

	textures[1] = LoadBitmapFromFile(_T("image/1.bmp"));

	// 准备设备
	Light light = { { -1.f, 1.f, -1.f, 0.f },{ 1.0f, 1.0f, 1.0f } };
	uint32* wfb = (uint32*)(screen->getFrameBuffer());
	device = new Device();
	device->init(WINDOW_WIDTH, WINDOW_HEIGHT, wfb, transform, textures, &light);

	// 准备mesh
	int vsize, fsize;
	Vertex* pVertexs;
	Face* pFaces;
	LoadMesh("models/teapot.obj", pVertexs, vsize, pFaces, fsize);

	device->setState(1);
	device->setDrawModel(1);

	float theta = 1.f;
	float updown = 0.f;
	float leftright = 0.f;
	float dist = 3.f;

	float light_theta = 1.f;
	unsigned long long beginTime = screen->GetCurTime();
	while (!screen->isExit()) {
		unsigned long long deltaTime = screen->GetCurTime() - beginTime;
		beginTime = screen->GetCurTime();
		device->clear();
		screen->dispatch();
		SetCamera(0.f, 2.f, dist);

		light_theta += 0.03f;
		TransformLight(light, light_theta);

		if (screen->getKeyUpEvent(VK_W))
			updown += 0.5f;
		if (screen->getKeyUpEvent(VK_S))
			updown -= 0.5f;

		if (screen->getKeyUpEvent(VK_A))
			leftright += 0.5f;
		if (screen->getKeyUpEvent(VK_D))
			leftright -= 0.5f;

		if (screen->isKeyPressed(VK_UP))
			dist -= 0.05f;
		if (screen->isKeyPressed(VK_DOWN))
			dist += 0.05f;

		if (screen->isKeyPressed(VK_LEFT))
			theta += 0.05f;
		if (screen->isKeyPressed(VK_RIGHT))
			theta -= 0.05f;

		if (screen->isKeyPressed(VK_HOME))
			light_theta += 0.05f;
		if (screen->isKeyPressed(VK_END))
			light_theta -= 0.05f;

		if (screen->getKeyUpEvent(VK_SPACE))
			device->ChangeState();

		if (screen->getKeyUpEvent(VK_1)) // 1 key
			device->ChangeInterp();

		if (screen->getKeyUpEvent(VK_2)) // 2 key
			device->ChangeCullMode();

		if (screen->getKeyUpEvent(VK_3)) // 3 key
			device->ChangeLight();

		if (screen->getKeyUpEvent(VK_4)) // 4 key
			device->ChangeBmp();

		if (screen->getKeyUpEvent(VK_RETURN))
		{
			device->ChangeDrawModel();
			device->clear();
		}

		int drawmodel = device->GetRealModel();
		if (drawmodel == 1)
		{
			// 绘制立方体
			DrawBox(theta, updown, leftright);
		}
		else if (drawmodel == 2)
		{
			// 绘制导入的mesh
			DrawModel(pVertexs, vsize, pFaces, fsize, theta);
		}
		else
		{
			// 绘制4面体
			DrawTetrahedron(theta, updown, leftright);
		}

		screen->dispatch();
		screen->update(deltaTime);
		Sleep(1);
	}

	device->close();
	screen->close();

	for (int i = 0; i < 3; i++) {
		if (textures[i]) {
			delete textures[i];
		}
	}

	delete[] pVertexs;
	delete[] pFaces;

	delete transform;
	delete device;
	delete screen;

	return 0;
}
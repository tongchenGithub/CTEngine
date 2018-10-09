#ifndef __Device_H__
#define __Device_H__
// 设备渲染

#include "TypeDefine.h"

class Transform;
struct Vertex;
struct Vector;
struct Color;
struct Texcoord;
struct Light;

class Device
{
public:
	Device();

	void init(int w, int h, uint32* fb, Transform* ts, int **tex, Light* light);
	void clear();
	void close();

	void setState(int s);
	void setDrawModel(int s);
	void ChangeState();
	void ChangeInterp();
	void ChangeCullMode();
	void ChangeDrawModel();
	void ChangeBmp();
	void ChangeLight();
	int GetRealModel();
	void drawPoint(const Vector& p, const Color& color, const Texcoord& tc, const Vector& normal);
	void drawLine(const Vector& p1, const Vector& p2);
	void drawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);

private:
	Transform* transform;
	Light* light;
	int** textures;
	uint32 ** framebuffer;
	float * zbuffer; 
	uint32 background; // 背景颜色
	uint32 foreground; // 线框颜色
	int width;
	int height;			
	int state;		// 绘制状态
	int interp;		// 插值
	int cullmode;	// 背面消除
	int drawmodel; // 绘制模型
	int drawBmp;	// 绘制导入的bmp
	bool bLight; // 光照
};
#endif
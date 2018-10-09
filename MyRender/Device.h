#ifndef __Device_H__
#define __Device_H__
// �豸��Ⱦ

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
	uint32 background; // ������ɫ
	uint32 foreground; // �߿���ɫ
	int width;
	int height;			
	int state;		// ����״̬
	int interp;		// ��ֵ
	int cullmode;	// ��������
	int drawmodel; // ����ģ��
	int drawBmp;	// ���Ƶ����bmp
	bool bLight; // ����
};
#endif
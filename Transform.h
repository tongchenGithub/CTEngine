#ifndef __Transform_H__
#define __Transform_H__
// 物体的tsf

#include "3DMath.h"

class Transform
{
public:
	void init(int width, int height);
	void update();	// 更新MVP
	void apply(Vector& b, const Vector& a);	// MVP*a = b
	void applyMV(Vector& b, const Vector& a);	// MV*a = b
	void homogenize(Vector& b, const Vector& a); // 归一化，得到屏幕坐标
	int checkCvv(const Vector& v);			// 检查CVV裁剪
	int checkBackCulling(const Vector& v);	// 检查背面剔除

	void setWorld(const Matrix& m);
	void setView(const Matrix& m);

private:
	Matrix world;		// 世界矩阵
	Matrix view;		// 视口矩阵
	Matrix projection;	// 透视矩阵
	Matrix transform;	// 变化矩阵
	float width, height; // screen
};
#endif
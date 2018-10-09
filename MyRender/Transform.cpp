#include "Transform.h"
#define PI 3.1415926

void Transform::init(int w, int h)
{
	width = w;
	height = h;
	MatrixSetIdentity(world);
	MatrixSetIdentity(view);
	float aspect = (float)width / height;
	MatrixSetPerspective(projection, PI * 0.5f, aspect, 1.f, 500.f);

	update();
}

void Transform::update()
{
	Matrix m;
	MatrixMul(m, world, view);
	MatrixMul(transform, m, projection);
}

void Transform::apply(Vector& b, const Vector& a)
{
	MatrixApply(b, a, transform);
}

void Transform::applyMV(Vector& b, const Vector& a)
{
	Matrix m;
	MatrixMul(m, world, view);
	MatrixApply(b, a, m);
}

void Transform::homogenize(Vector& b, const Vector& a)
{
	float rhw = 1 / a.w;
	b.x = (1.f + a.x * rhw) * width * 0.5;	// 屏幕坐标
	b.y = (1.f - a.y * rhw) * height * 0.5; // 屏幕坐标
	b.z = a.z * rhw;
	b.w = 1.0f;
}

int Transform::checkCvv(const Vector& v)
{
	// 可以进行透视除法后在进行和+-1，0的对比
	float w = v.w;
	int check = 0;
	if (v.z < 0.0f) check |= 1;
	if (v.z > w) check |= 2;
	if (v.x < -w) check |= 4;
	if (v.x > w) check |= 8;
	if (v.y < -w) check |= 16;
	if (v.y > w) check |= 32;
	return check;
}

int Transform::checkBackCulling(const Vector& v)
{
	// 视线方向和2点所在面片的夹角的cos 来判断是否可见
	float dot = VectorDotProduct({0.f, 0.f, -1.f, 0.f}, v);
	if (dot > 0) {
		return 0;
	}
	return 1;
}

void Transform::setView(const Matrix& m)
{
	view = m;
}

void Transform::setWorld(const Matrix& m)
{
	world = m;
}

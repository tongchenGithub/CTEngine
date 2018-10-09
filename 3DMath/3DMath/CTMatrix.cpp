#include "CTMatrix.h"
#include <math.h>

// 数学库
// matrix identity
void MatrixSetIdentity(Matrix& mt)
{
	mt.m[0][0] = mt.m[1][1] = mt.m[2][2] = mt.m[3][3] = 1.0f;
	mt.m[0][1] = mt.m[0][2] = mt.m[0][3] = 0.0f;
	mt.m[1][0] = mt.m[1][2] = mt.m[1][3] = 0.0f;
	mt.m[2][0] = mt.m[2][1] = mt.m[2][3] = 0.0f;
	mt.m[3][0] = mt.m[3][1] = mt.m[3][2] = 0.0f;
}

// matrix zero
void MatrixSetZero(Matrix& mt)
{
	mt.m[0][0] = mt.m[0][1] = mt.m[0][2] = mt.m[0][3] = 0.0f;
	mt.m[1][0] = mt.m[1][1] = mt.m[1][2] = mt.m[1][3] = 0.0f;
	mt.m[2][0] = mt.m[2][1] = mt.m[2][2] = mt.m[2][3] = 0.0f;
	mt.m[3][0] = mt.m[3][1] = mt.m[3][2] = mt.m[3][3] = 0.0f;
}

// matrix m = a + b
void MatrixAdd(Matrix& mt, const Matrix& a, const Matrix& b)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			mt.m[i][j] = a.m[i][j] + b.m[i][j];
	}
}

// matrix m = a - b
void MatrixSub(Matrix& mt, const Matrix& a, const Matrix& b)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			mt.m[i][j] = a.m[i][j] - b.m[i][j];
	}
}

// matrix m = a * b
void MatrixMul(Matrix& mt, const Matrix& a, const Matrix& b)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mt.m[j][i] = (a.m[j][0] * b.m[0][i]) +
				(a.m[j][1] * b.m[1][i]) +
				(a.m[j][2] * b.m[2][i]) +
				(a.m[j][3] * b.m[3][i]);
		}
	}
}

// matrix m = a * f
void MatrixScale(Matrix& mt, const Matrix& a, const float f)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			mt.m[i][j] = a.m[i][j] * f;
	}
}

// matrix v = x * m
void MatrixApply(Vector& v, const Vector& x, const Matrix& mt)
{
	float X = x.x, Y = x.y, Z = x.z, W = x.w;
	v.x = X * mt.m[0][0] + Y * mt.m[1][0] + Z * mt.m[2][0] + W * mt.m[3][0];
	v.y = X * mt.m[0][1] + Y * mt.m[1][1] + Z * mt.m[2][1] + W * mt.m[3][1];
	v.z = X * mt.m[0][2] + Y * mt.m[1][2] + Z * mt.m[2][2] + W * mt.m[3][2];
	v.w = X * mt.m[0][3] + Y * mt.m[1][3] + Z * mt.m[2][3] + W * mt.m[3][3];
}

// translate
void MatrixSetTranslate(Matrix& mt, float x, float y, float z)
{
	MatrixSetIdentity(mt);
	mt.m[3][0] = x;
	mt.m[3][1] = y;
	mt.m[3][2] = z;
}

// scale
void MatrixSetScale(Matrix& mt, float x, float y, float z)
{
	MatrixSetIdentity(mt);
	mt.m[0][0] = x;
	mt.m[1][1] = y;
	mt.m[2][2] = z;
}

// rotate
void MatrixSetRotate(Matrix& mt, float x, float y, float z, float theta)
{
	float qsin = (float)sin(theta * 0.5f);
	float qcos = (float)cos(theta * 0.5f);
	Vector vec = { x,y,z,1.0f };
	float w = qcos;
	VectorNormalize(vec);
	x = vec.x * qsin;
	y = vec.y * qsin;
	z = vec.z * qsin;
	mt.m[0][0] = 1 - 2 * y * y - 2 * z * z;
	mt.m[1][0] = 2 * x * y - 2 * w * z;
	mt.m[2][0] = 2 * x * z + 2 * w * y;
	mt.m[0][1] = 2 * x * y + 2 * w * z;
	mt.m[1][1] = 1 - 2 * x * x - 2 * z * z;
	mt.m[2][1] = 2 * y * z - 2 * w * x;
	mt.m[0][2] = 2 * x * z - 2 * w * y;
	mt.m[1][2] = 2 * y * z - 2 * w * x;
	mt.m[2][2] = 1 - 2 * x * x - 2 * y * y;
	mt.m[0][3] = mt.m[1][3] = mt.m[2][3] = 0.0f;
	mt.m[3][0] = mt.m[3][1] = mt.m[3][2] = 0.0f;
	mt.m[3][3] = 1.0f;
}

// lookat
void MatrixSetLookAt(Matrix& mt, const Vector& eye, const Vector& at, const Vector& up)
{
	Vector xaxis, yaxis, zaxis;

	VectorSub(zaxis, at, eye); // 眼睛前方 z 轴
	VectorNormalize(zaxis);
	VectorCrossProduct(xaxis, up, zaxis); // up 和 z = x 轴
	VectorNormalize(xaxis);
	VectorCrossProduct(yaxis, zaxis, xaxis);

	mt.m[0][0] = xaxis.x;
	mt.m[1][0] = xaxis.y;
	mt.m[2][0] = xaxis.z;
	mt.m[3][0] = -VectorDotProduct(xaxis, eye);

	mt.m[0][1] = yaxis.x;
	mt.m[1][1] = yaxis.y;
	mt.m[2][1] = yaxis.z;
	mt.m[3][1] = -VectorDotProduct(yaxis, eye);

	mt.m[0][2] = zaxis.x;
	mt.m[1][2] = zaxis.y;
	mt.m[2][2] = zaxis.z;
	mt.m[3][2] = -VectorDotProduct(zaxis, eye);

	mt.m[0][3] = mt.m[1][3] = mt.m[2][3] = 0.0f;
	mt.m[3][3] = 1.0f;
}

// perspective
void MatrixSetPerspective(Matrix& mt, float fovy, float aspect, float zn, float zf)
{
	float fax = 1.0f / (float)tan(fovy * 0.5f);
	MatrixSetZero(mt);
	mt.m[0][0] = (float)(fax / aspect);
	mt.m[1][1] = (float)(fax);
	mt.m[2][2] = zf / (zf - zn);
	mt.m[3][2] = -zn*zf / (zf - zn);
	mt.m[2][3] = 1;
}
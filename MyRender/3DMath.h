#ifndef __3DMath_H__  
#define __3DMath_H__  
#pragma comment(lib, "3DMath.lib") // 数学库

#define MATHDLL_API extern "C" _declspec(dllimport)  

struct Vector
{ // 齐次坐标
	float x, y, z, w;
};

struct Matrix
{ // 矩阵
	float m[4][4];
};

// length
MATHDLL_API float VectorLength(const Vector& v);

// add
MATHDLL_API void VectorAdd(Vector& v, const Vector& x, const Vector& y);

// sub
MATHDLL_API void VectorSub(Vector& v, const Vector& x, const Vector& y);

// dot product
MATHDLL_API float VectorDotProduct(const Vector& x, const Vector& y);

// cross product
MATHDLL_API void VectorCrossProduct(Vector& v, const Vector& x, const Vector& y);

// normalize
MATHDLL_API void VectorNormalize(Vector& v);

// interpolation
MATHDLL_API void VectorInterp(Vector& v, const Vector& x, const Vector& y, float t);


// matrix identity
MATHDLL_API void MatrixSetIdentity(Matrix& mt);

// matrix zero
MATHDLL_API void MatrixSetZero(Matrix& mt);

// matrix m = a + b
MATHDLL_API void MatrixAdd(Matrix& mt, const Matrix& a, const Matrix& b);

// matrix m = a - b
MATHDLL_API void MatrixSub(Matrix& mt, const Matrix& a, const Matrix& b);

// matrix m = a * b
MATHDLL_API void MatrixMul(Matrix& mt, const Matrix& a, const Matrix& b);

// matrix m = a * f
MATHDLL_API void MatrixScale(Matrix& mt, const Matrix& a, const float f);

// matrix v = x * m
MATHDLL_API void MatrixApply(Vector& v, const Vector& x, const Matrix& mt);

// translate
MATHDLL_API void MatrixSetTranslate(Matrix& mt, float x, float y, float z);

// scale
MATHDLL_API void MatrixSetScale(Matrix& mt, float x, float y, float z);

// rotate
MATHDLL_API void MatrixSetRotate(Matrix& mt, float x, float y, float z, float theta);

// lookat
MATHDLL_API void MatrixSetLookAt(Matrix& mt, const Vector& eye, const Vector& at, const Vector& up);

// perspective
MATHDLL_API void MatrixSetPerspective(Matrix& mt, float fovy, float aspect, float zn, float fn);
#endif
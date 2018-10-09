#pragma once
#include "CTVector.h"

#define MATHDLL_API extern "C" _declspec(dllexport)  

struct Matrix
{ // æÿ’Û
	float m[4][4];
};

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
MATHDLL_API void MatrixApply(Vector& v, const Vector& x, const Matrix& m);

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

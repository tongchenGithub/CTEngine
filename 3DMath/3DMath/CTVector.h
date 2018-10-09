#pragma once

#define MATHDLL_API extern "C" _declspec(dllexport)

struct Vector
{ // Æë´Î×ø±ê
	float x, y, z, w;
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

#include "CTVector.h"
#include <math.h>

// length
float VectorLength(const Vector& v)
{
	float sq = v.x * v.x + v.y * v.y + v.z * v.z;
	return (float)sqrt(sq);
}

// add
void VectorAdd(Vector& v, const Vector& x, const Vector& y)
{
	v.x = x.x + y.x;
	v.y = x.y + y.y;
	v.z = x.z + y.z;
	v.w = 1.0;
}

// sub
void VectorSub(Vector& v, const Vector& x, const Vector& y)
{
	v.x = x.x - y.x;
	v.y = x.y - y.y;
	v.z = x.z - y.z;
	v.w = 1.0f;
}

// dot product
float VectorDotProduct(const Vector& x, const Vector& y)
{
	return x.x * y.x + x.y * y.y + x.z * y.z;
}

// cross product
void VectorCrossProduct(Vector& v, const Vector& x, const Vector& y)
{
	v.x = x.y * y.z - x.z * y.y;
	v.y = x.z * y.x - x.x * y.z;
	v.z = x.x * y.y - x.y * y.x;
	v.w = 1.0f;
}

// normalize
void VectorNormalize(Vector& v)
{
	float len = VectorLength(v);
	if (len != 0.0f) {
		float inv = 1.0f / len;
		v.x *= inv;
		v.y *= inv;
		v.z *= inv;
	}
}

// ²åÖµ
float interp(float x1, float x2, float t)
{
	return x1 + (x2 - x1)*t;
}

// interpolation
void VectorInterp(Vector& v, const Vector& x, const Vector& y, float t)
{
	v.x = interp(x.x, y.x, t);
	v.y = interp(x.y, y.y, t);
	v.z = interp(x.z, y.z, t);
	v.w = 1.0f;
}

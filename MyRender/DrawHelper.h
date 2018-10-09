#ifndef __DrawHelper_H__  
#define __DrawHelper_H__  

#include "Vertex.h"
#include "3DMath.h"
#include "Device.h"
#include "Transform.h"

void DrawPlane(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4);

void DrawBox(float theta, float updown, float leftright);

void DrawTetrahedron(float theta, float updown, float leftright);
#endif

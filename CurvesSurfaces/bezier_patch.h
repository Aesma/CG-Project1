#ifndef BEZIER_PATCH_H
#define BEZIER_PATCH_H

#include "surface.h"
#include <vector>

class BezierPatch :public Surface
{
public:
	BezierPatch();
	void Paint(ArgParser *arg);
	TriangleMesh* OutputTriangles(ArgParser *args);
};

#endif
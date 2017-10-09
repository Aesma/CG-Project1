#ifndef SURFACE_REVOLUTION_H
#define SURFACE_REVOLUTION_H

#include "surface.h"
#include "curve.h"

class SurfaceOfRevolution :public Surface
{
public:
	SurfaceOfRevolution(Curve *c);
	void Paint(ArgParser *arg);
	TriangleMesh* OutputTriangles(ArgParser *args);
private:
	Curve *curve;
};

#endif
#ifndef CURVE_H
#define CURVE_H

#include "spline.h"

#define M_PI 3.14159265358979323846

class Curve:public Spline
{
public:
	virtual void set(int i, Vec3f v);
	virtual void Paint(ArgParser *arg);
	virtual TriangleMesh* OutputTriangles(ArgParser *args);
	~Curve();
protected:
	int curve_tessellation;
protected:
	void drawLine();
	void drawPoints();
	void drawCurve(ArgParser *arg);
};

#endif
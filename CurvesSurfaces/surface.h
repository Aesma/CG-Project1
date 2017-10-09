#ifndef SURFACE_H
#define SURFACE_H

#include "spline.h"

class Surface:public Spline
{
public:
	virtual void set(int i, Vec3f v);
	virtual void Paint(ArgParser *arg);
	~Surface();
public:
	int curve_tessellation;
protected:
	void drawLine();
	void drawPoints();
	void drawCurve(ArgParser *arg);
protected:
	int type;
};

#endif
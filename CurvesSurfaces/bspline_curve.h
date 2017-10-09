#ifndef BSPLINE_CURVE_H
#define BSPLINE_CURVE_H

#include "curve.h"

#include <cmath>

class BSplineCurve :public Curve
{
public:
	BSplineCurve(int nvm_v);
	void Paint(ArgParser *arg);
	void OutputBezier(FILE *file);
	void OutputBSpline(FILE *file);
};

#endif
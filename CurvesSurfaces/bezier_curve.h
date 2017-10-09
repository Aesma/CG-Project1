#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H

#include "curve.h"

class BezierCurve :public Curve
{
public:
	BezierCurve(int num_v);
	void Paint(ArgParser *args);
	void OutputBezier(FILE *file);
	void OutputBSpline(FILE *file);
	void addControlPoint(int selectedPoint, float x, float y);
	void deleteControlPoint(int selectedPoint);
};
#endif
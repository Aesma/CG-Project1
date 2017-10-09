#ifndef SPLINE_H
#define SPLINE_H

#include <fstream>
#include <GL/glut.h>
#include <cmath>
#include "triangle_mesh.h"
#include "arg_parser.h"
#include "matrix.h"

class Spline
{
public:
	// ���ڻ�ͼ��FOR VISUALIZATION
	virtual void Paint(ArgParser *args);

	// ����ʵ����������ת����FOR CONVERTING BETWEEN SPLINE TYPES
	virtual void OutputBezier(FILE *file);
	virtual void OutputBSpline(FILE *file);

	// ���ڵõ����Ƶ��FOR CONTROL POINT PICKING
	virtual int getNumVertices();
	virtual Vec3f getVertex(int i);

	// ���ڱ༭������FOR EDITING OPERATIONS
	virtual void moveControlPoint(int selectedPoint, float x, float y);
	virtual void addControlPoint(int selectedPoint, float x, float y);
	virtual void deleteControlPoint(int selectedPoint);

	// ���ڲ��������ε�FOR GENERATING TRIANGLES
	virtual TriangleMesh* OutputTriangles(ArgParser *args);
public:
	int num_vertices;
	Vec3f* vertices;
	int type_id;
};

#endif
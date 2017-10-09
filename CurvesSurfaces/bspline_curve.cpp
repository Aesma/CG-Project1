#include "bspline_curve.h"

BSplineCurve::BSplineCurve(int num_v)
{
	num_vertices = num_v;
	vertices = new Vec3f[num_vertices];
	type_id = 2;
}

void BSplineCurve::Paint(ArgParser *arg)
{
	Curve::Paint(arg);

	/*glColor3f(0, 1.0f, 0);
	glPointSize(1.0f);
	glBegin(GL_POINTS);
	for (GLfloat t = 0; t <= 1.0f; t += 0.001f)
	{
		GLfloat x = vertices[0].x()*pow(1.0f - t, 3) + 3 * vertices[1].x()*t*pow(1.0f - t, 2) + 3 * vertices[2].x()*t*t*(1.0f - t) + vertices[3].x()*pow(t, 3);
		GLfloat y = vertices[0].y()*pow(1.0f - t, 3) + 3 * vertices[1].y()*t*pow(1.0f - t, 2) + 3 * vertices[2].y()*t*t*(1.0f - t) + vertices[3].y()*pow(t, 3);
		GLfloat z = vertices[0].z()*pow(1.0f - t, 3) + 3 * vertices[1].z()*t*pow(1.0f - t, 2) + 3 * vertices[2].z()*t*t*(1.0f - t) + vertices[3].z()*pow(t, 3);

		glVertex3f(x, y, z);
	}
	glEnd();*/
}

void BSplineCurve::OutputBezier(FILE *file)
{
	Matrix bspline;
	for (int i = 0; i < num_vertices; i++)
	{
		bspline.Set(i, 0, vertices[i].x());
		bspline.Set(i, 1, vertices[i].y());
		bspline.Set(i, 2, vertices[i].z());
	}
	float beizer_g[16] = { -1, 3, -3, 1, 3, -6, 3, 0, -3, 3, 0, 0, 1, 0, 0, 0 };
	Matrix beizer_G(beizer_g);
	float bs_g[16] = { -1, 3, -3, 1, 3, -6, 0, 4, -3, 3, 3, 1, 1, 0, 0, 0 };
	Matrix bs_G(bs_g);
	bs_G = bs_G*(1.0f / 6.0f);
	beizer_G.Inverse();
	Matrix beizer = bspline*bs_G*beizer_G;
	fprintf(file, "bezier  \n");
	fprintf(file, "num_vertices  %d\n", num_vertices);
	for (int i = 0; i < num_vertices; i++)
	{
		float x = beizer.Get(i, 0);
		float y = beizer.Get(i, 1);
		float z = beizer.Get(i, 2);
		fprintf(file, "%f ", x);
		fprintf(file, "%f ", y);
		fprintf(file, "%f ", z);
		fprintf(file, "\n");
	}
}

void BSplineCurve::OutputBSpline(FILE *file)
{
	fprintf(file, "bspline  \n");
	fprintf(file, "num_vertices  %d\n", num_vertices);
	for (int i = 0; i < num_vertices; i++)
	{
		float x = vertices[i].x();
		float y = vertices[i].y();
		float z = vertices[i].z();
		fprintf(file, "%f ", x);
		fprintf(file, "%f ", y);
		fprintf(file, "%f ", z);
		fprintf(file, "\n");
	}
}

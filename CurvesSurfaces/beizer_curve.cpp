#include "bezier_curve.h"

BezierCurve::BezierCurve(int num_v)
{
	num_vertices = num_v;
	vertices = new Vec3f[num_vertices];
	type_id = 1;
}

void BezierCurve::Paint(ArgParser *arg)
{
	Curve::Paint(arg);

/*	glColor3f(0, 1.0f, 0);
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

void BezierCurve::OutputBezier(FILE *file)
{
	fprintf(file, "bezier  \n");
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

void BezierCurve::OutputBSpline(FILE *file)
{
	Matrix beizer;
	for (int i = 0; i < num_vertices; i++)
	{
		beizer.Set(i, 0, vertices[i].x());
		beizer.Set(i, 1, vertices[i].y());
		beizer.Set(i, 2, vertices[i].z());
	}
	float beizer_g[16] = { -1, 3, -3, 1, 3, -6, 3, 0, -3, 3, 0, 0, 1, 0, 0, 0 };
	Matrix beizer_G(beizer_g);
	float bs_g[16] = { -1, 3, -3, 1, 3, -6, 0, 4, -3, 3, 3, 1, 1, 0, 0, 0 };
	Matrix bs_G(bs_g);
	bs_G = bs_G*(1.0f / 6.0f);
	bs_G.Inverse();
	Matrix bspline = beizer*beizer_G * bs_G;
	fprintf(file, "bspline  \n");
	fprintf(file, "num_vertices  %d\n", num_vertices);
	for (int i = 0; i < num_vertices; i++)
	{
		/*float x = vertices[i].x();
		float y = vertices[i].y();
		float z = vertices[i].z();*/
		float x = bspline.Get(i, 0);
		float y = bspline.Get(i, 1);
		float z = bspline.Get(i, 2);
		fprintf(file, "%f ", x);
		fprintf(file, "%f ", y);
		fprintf(file, "%f ", z);
		fprintf(file, "\n");
	}
}

void BezierCurve::addControlPoint(int selectedPoint, float x, float y)//同一个位置添加3个点
{
	num_vertices += 3;
	Vec3f *temp = new Vec3f[num_vertices];
	for (int i = 0; i < num_vertices - 3; i++)
	{
		temp[i] = vertices[i];
	}
	temp[num_vertices - 1] = Vec3f(x, y, 0);
	temp[num_vertices - 2] = Vec3f(x, y, 0);
	temp[num_vertices - 3] = Vec3f(x, y, 0);

	delete[]vertices;
	vertices = new Vec3f[num_vertices];

	for (int i = 0; i < num_vertices; i++)
	{
		vertices[i] = temp[i];
	}

	delete[]temp;
}

void BezierCurve::deleteControlPoint(int selectedPoint)//一次删除3个点 删除选择的点以及下标离它最近的两个点
{
	if (num_vertices < 5){
		return;
	}
	num_vertices -= 3;
	Vec3f *temp = new Vec3f[num_vertices];
	int pre = selectedPoint;
	int last = selectedPoint;
	int count = 1;
	while (count != 3){
		count++;
		if (count % 2 == 0){
			pre--;
			if (pre < 0){
				pre++;
				last++;
			}
		}
		else{
			last++;
			if (last == (num_vertices + 3)){
				last--;
				pre--;
			}
		}
	}
	for (int i = 0; i < pre; i++)
	{
		temp[i] = vertices[i];
	}
	for (int i = last + 1; i < num_vertices; i++)
	{
		temp[i - 3] = vertices[i];
	}
	delete[]vertices;

	vertices = new Vec3f[num_vertices];
	for (int i = 0; i < num_vertices; i++)
	{
		vertices[i] = temp[i];
	}

	delete[]temp;
}
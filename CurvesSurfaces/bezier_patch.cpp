#include "bezier_patch.h"

BezierPatch::BezierPatch()
{
	num_vertices = 16;
	vertices = new Vec3f[num_vertices];
}

void BezierPatch::Paint(ArgParser *arg)
{
	Surface::Paint(arg);
}

TriangleMesh* BezierPatch::OutputTriangles(ArgParser *args)
{
	TriangleNet *tri = new TriangleNet(args->patch_tessellation, args->patch_tessellation);
	GLfloat range = 1.0f / args->patch_tessellation;
	GLfloat m_2[16] = { -1, 3, -3, 1, 3, -6, 3, 0, -3, 3, 0, 0, 1, 0, 0, 0 };
	Matrix m2(m_2);
	Matrix m3 = m2;
	m3.Transpose();
	for (int u = 0; u <= args->patch_tessellation; u ++)
	{
		float u_tess = u*1.0f / args->patch_tessellation;
		Vec3f ver;
		for (int v = 0; v <= args->patch_tessellation; v ++)
		{
			float v_tess = v*1.0f / args->patch_tessellation;
			GLfloat m_u[4] = { pow(u_tess, 3), pow(u_tess, 2), u_tess, 1 };
			Matrix mu(m_u);
			Matrix temp1 = mu*m2;
			Vec3f vs[4];
			for (int i = 0; i < 4; i++)
			{
				vs[i] = temp1.Get(0, 0)*vertices[0 + i] + temp1.Get(1, 0)*vertices[4 + i] + temp1.Get(2, 0)*vertices[8 + i] + temp1.Get(3, 0)*vertices[12 + i];
			}
			Vec3f vs2[4];
			for (int i = 0; i < 4; i++)
			{
				vs2[i] = vs[0] * m3.Get(0, i) + vs[1] * m3.Get(1, i) + vs[2] * m3.Get(2, i) + vs[3] * m3.Get(3, i);
			}
			ver = vs2[0] * pow(v_tess, 3) + vs2[1] * pow(v_tess, 2) + vs2[2] * v_tess + vs2[3];
			tri->SetVertex(v, u, ver);
		}
	}
	return tri;
}

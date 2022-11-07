#include "pch.h"
#include "GD3Vary.h"

void GD3Vary::Move(GD3Point * p, double mx, double my, double mz)
{
	double matrix[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { mx, my, mz, 1 } };
	GTools::GraphMulVaryMatrix(p, matrix);
}
void GD3Vary::Scale(GD3Point * p, double sx, double sy, double sz)
{
	double matrix[4][4] = { { sx, 0, 0, 0 }, { 0, sy, 0, 0 }, { 0, 0, sz, 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrix);
}
void GD3Vary::Spin(GD3Point * p, double sx, double sy, double sz)
{
	double matrixX[4][4] = { { 1, 0, 0, 0 }, { 0, cos(sx), sin(sx), 0 }, { 0, -sin(sx), cos(sx), 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixX);
	double matrixY[4][4] = { { cos(sy), 0, -sin(sy), 0 }, { 0, 1, 0, 0 }, { sin(sy), 0, cos(sy), 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixY);
	double matrixZ[4][4] = { { cos(sz), sin(sz), 0, 0 }, { -sin(sz), cos(sz), 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixZ);
}
void GD3Vary::Reflact(GD3Point * p, bool bx, bool by, bool bz)
{
	if (bx)
	{
		double matrixX[4][4] = { { 1, 0, 0, 0 }, { 0, -1, 0, 0 }, { 0, 0, -1, 0 }, { 0, 0, 0, 1 } };
		GTools::GraphMulVaryMatrix(p, matrixX);
	}
	if (by)
	{
		double matrixY[4][4] = { { -1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, -1, 0 }, { 0, 0, 0, 1 } };
		GTools::GraphMulVaryMatrix(p, matrixY);
	}
	if (bz)
	{
		double matrixZ[4][4] = { { -1, 0, 0, 0 }, { 0, -1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
		GTools::GraphMulVaryMatrix(p, matrixZ);
	}
}
void GD3Vary::FlatReflact(GD3Point * p, bool bxoy, bool byoz, bool bxoz)
{
	if (bxoy)
	{
		double matrixX[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, -1, 0 }, { 0, 0, 0, 1 } };
		GTools::GraphMulVaryMatrix(p, matrixX);
	}
	if (byoz)
	{
		double matrixY[4][4] = { { -1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
		GTools::GraphMulVaryMatrix(p, matrixY);
	}
	if (bxoz)
	{
		double matrixZ[4][4] = { { 1, 0, 0, 0 }, { 0, -1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
		GTools::GraphMulVaryMatrix(p, matrixZ);
	}

}
void GD3Vary::Miscut(GD3Point * p, double xgz, double xdy, double yhz, double ybx, double zfy, double zcx)
{
	double matrixX[4][4] = { { 1, 0, 0, 0 }, { xdy, 1, 0, 0 }, { xgz, 0, 1, 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixX);
	double matrixY[4][4] = { { 1, ybx, 0, 0 }, { 0, 1, 0, 0 }, { 0, yhz, 1, 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixY);
	double matrixZ[4][4] = { { 1, 0, zcx, 0 }, { 0, 1, zfy, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixZ);
}
void GD3Vary::OrgMove(GD3Point * p, double mx, double my, double mz)
{
	double matrix[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { -mx, -my, -mz, 1 } };
	GTools::GraphMulVaryMatrix(p, matrix);
}
void GD3Vary::OrgSpin(GD3Point * p, double sx, double sy, double sz)
{
	double matrixX[4][4] = { { 1, 0, 0, 0 }, { 0, cos(sx), -sin(sx), 0 }, { 0, sin(sx), cos(sx), 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixX);
	double matrixY[4][4] = { { cos(sy), 0, sin(sy), 0 }, { 0, 1, 0, 0 }, { -sin(sy), 0, cos(sy), 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixY);
	double matrixZ[4][4] = { { cos(sz), -sin(sz), 0, 0 }, { sin(sz), cos(sz), 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixZ);
}
void GD3Vary::OrgReflact(GD3Point * p, bool bx, bool by, bool bz)
{
	Reflact(p, bx, by, bz);
}
void GD3Vary::OrgFlatReflact(GD3Point * p, bool bxoy, bool byoz, bool bxoz)
{
	FlatReflact(p, bxoy, byoz, bxoz);
}

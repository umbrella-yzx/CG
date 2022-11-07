#include "pch.h"
#include "GData.h"

const double GTools::MATH_PI = 3.1415926535;
double GTools::AngleToRadian(double a)
{
	return a / 180.0 * MATH_PI;
}
double GTools::RadianToAngle(double a)
{
	return a / MATH_PI * 180.0;
}
void GTools::GraphMulVaryMatrix(GD3Point * p, double matrix[][4])
{
	double PointVector[4] = { p->x, p->y, p->z, 1.0 };
	double ResultVector[4] = { 0 };
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			ResultVector[j] += PointVector[i] * matrix[i][j];
		}

	}
	for (i = 0; i < 4; i++)//�������任ǰ�󣬶�Ҫ�������ĵ���ά����Ϊ1
	{
		ResultVector[i] /= ResultVector[3];
	}
	p->x = ResultVector[0];
	p->y = ResultVector[1];
	p->z = ResultVector[2];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
GD3Point::GD3Point() :x(0), y(0), z(0) {}
GD3Point::GD3Point(double x, double y, double z) : x(x), y(y), z(z)
{

}
GD3Point::GD3Point(const GD3Point & p)
{
	this->x = p.x;
	this->y = p.y;
	this->z = p.z;
}
GD3Point& GD3Point::operator=(const GD3Point & p)
{
	this->x = p.x;
	this->y = p.y;
	this->z = p.z;
	return *this;
}
bool GD3Point::operator==(const GD3Point & p)
{
	if (this->x == p.x && this->y == p.y && this->z == p.z)
		return true;
	return false;
}
void GD3Point::ParseSpherical(double R, double aAngle, double bAngle)
{
	this->x = R * sin(aAngle)*sin(bAngle);
	this->y = R * cos(aAngle);
	this->z = R * sin(aAngle)*cos(bAngle);
}
GD3Point::GD3Point(double * arr)
{
	this->x = arr[0];
	this->y = arr[1];
	this->z = arr[2];
}
void GD3Point::toArrayDouble(double arr[])
{
	arr[0] = this->x;
	arr[1] = this->y;
	arr[2] = this->z;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
GD3Vector::GD3Vector() {};
GD3Vector::GD3Vector(double x, double y, double z) :GD3Point(x, y, z)
{

}
GD3Vector::GD3Vector(GD3Vector & v) : GD3Point(v.x, v.y, v.z)
{

}
GD3Vector::GD3Vector(GD3Point & p) : GD3Point(p)
{

}
GD3Vector::GD3Vector(GD3Point & ps, GD3Point & pe)
{
	this->x = pe.x - ps.x;
	this->y = pe.y - ps.y;
	this->z = pe.z - ps.z;
}
GD3Vector& GD3Vector::operator=(const GD3Vector & v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return *this;
}
bool GD3Vector::operator==(const GD3Vector & v)
{
	if (this->x == v.x && this->y == v.y && this->z == v.z)
		return true;
	return false;
}
double GD3Vector::GetModuleLength()
{
	return sqrt(x*x + y * y + z * z);
}
void GD3Vector::Untization()
{
	double mod = GetModuleLength();
	this->x /= mod;
	this->y /= mod;
	this->z /= mod;
}
GD3Vector GD3Vector::operator+(const GD3Vector & v)
{
	GD3Vector r(*this);
	r.x += v.x;
	r.y += v.y;
	r.z += v.z;
	return r;
}
GD3Vector GD3Vector::operator-(const GD3Vector & v)
{
	GD3Vector r(*this);
	r.x -= v.x;
	r.y -= v.y;
	r.z -= v.z;
	return r;
}
double GD3Vector::operator*(const GD3Vector & v)
{
	return this->x*v.x + this->y*v.y + this->z*v.z;
}
GD3Vector GD3Vector::CrossMultiply(GD3Vector & v)
{
	GD3Vector r(*this);
	r.x = v.z*this->y - v.y*this->z;
	r.y = v.x*this->z - v.z*this->x;
	r.z = v.y*this->x - v.x*this->y;
	return r;
}
double GD3Vector::CosRadian(GD3Vector & v)
{
	return (*this)*v / (this->GetModuleLength() * v.GetModuleLength());
}
GD3Vector::GD3Vector(double * arr) :GD3Point(arr)
{

}
///////////////////////////////////////////////////////////////////////////////////////////////////////
GD3NormalLine::GD3NormalLine() {}
GD3NormalLine::GD3NormalLine(double x, double y, double z) :GD3Vector(x, y, z)
{

}
GD3NormalLine::GD3NormalLine(GD3Vector & v) : GD3Vector(v)
{

}
GD3NormalLine::GD3NormalLine(GD3NormalLine & n) : GD3Vector(n.x, n.y, n.z)
{

}
GD3NormalLine::GD3NormalLine(GD3Vector & v1, GD3Vector & v2)
{
	GD3Vector nl = v1.CrossMultiply(v2);
	this->x = nl.x;
	this->y = nl.y;
	this->z = nl.z;
}
GD3NormalLine& GD3NormalLine::operator=(const GD3NormalLine & n)
{
	this->x = n.x;
	this->y = n.y;
	this->z = n.z;
	return *this;
}
GD3NormalLine::GD3NormalLine(double * arr) :GD3Vector(arr)
{

}
///////////////////////////////////////////////////////////////////////////////////
GD3Flat::GD3Flat() {}
GD3Flat::GD3Flat(GD3Point & p1, GD3Point & p2, GD3Point & p3) :p1(p1), p2(p2), p3(p3)
{

}
GD3NormalLine GD3Flat::GetNormalLine()
{
	GD3Vector v1(p1, p2);
	GD3Vector v2(p2, p3);
	GD3NormalLine nl(v1, v2);
	return nl;
}
GD3NormalLine GD3Flat::GetUntizationNormalLine()
{
	GD3Vector v1(p1, p2);
	GD3Vector v2(p2, p3);
	GD3NormalLine nl(v1, v2);
	nl.Untization();
	return nl;
}
GD3Flat::GD3Flat(GD3Point * arr)
{
	this->p1 = arr[0];
	this->p2 = arr[1];
	this->p3 = arr[2];
}
void GD3Flat::toArrayPoint(GD3Point arr[])
{
	arr[0] = this->p1;
	arr[1] = this->p2;
	arr[2] = this->p3;
}
///////////////////////////////////////////////////////////////////////////////////
GD2Point::GD2Point() :x(0), y(0) {};
GD2Point::GD2Point(double x, double y) :x(x), y(y)
{

}
GD2Point::GD2Point(const GD2Point & p) : x(p.x), y(p.y)
{

}
GD2Point& GD2Point::operator=(const GD2Point & p)
{
	this->x = p.x;
	this->y = p.y;
	return *this;
}
///////////////////////////////////////////////////////////////////////////////////
GD2Vector::GD2Vector() {}
GD2Vector::GD2Vector(double x, double y) :GD2Point(x, y)
{

}
GD2Vector::GD2Vector(GD2Vector & v) : GD2Point(v.x, v.y)
{

}
GD2Vector::GD2Vector(GD2Point & p) : GD2Point(p)
{

}
GD2Vector::GD2Vector(GD2Point & ps, GD2Point & pe)
{
	this->x = pe.x - ps.x;
	this->y = pe.y - ps.y;
}
GD2Vector& GD2Vector::operator=(const GD2Vector & v)
{
	this->x = v.x;
	this->y = v.y;
	return *this;
}
bool GD2Vector::operator==(const GD2Vector & v)
{
	if (this->x == v.x && this->y == v.y)
		return true;
	return false;
}
double GD2Vector::GetModuleLength()
{
	return sqrt(x*x + y * y);
}
void GD2Vector::Untization()
{
	double mod = this->GetModuleLength();
	this->x /= mod;
	this->y /= mod;
}
GD2Vector GD2Vector::operator+(const GD2Vector & v)
{
	GD2Vector r(*this);
	r.x += v.x;
	r.y += v.y;
	return r;
}
GD2Vector GD2Vector::operator-(const GD2Vector & v)
{
	GD2Vector r(*this);
	r.x -= v.x;
	r.y -= v.y;
	return r;
}
double GD2Vector::operator*(const GD2Vector & v)
{
	return this->x*v.x + this->y*v.y;
}

double GD2Vector::CosRadian(GD2Vector & v)
{
	return (*this)*v / (this->GetModuleLength()*v.GetModuleLength());
}
///////////////////////////////////////////////////////////////////////////////////
GD2Line::GD2Line() {}
GD2Line::GD2Line(GD2Point & p1, GD2Point & p2) :p1(p1), p2(p2)
{

}
GD2Line::GD2Line(GD2Line & l) : p1(l.p1), p2(l.p2)
{

}
double GD2Line::GetDistance()
{
	return sqrt(pow(p2.x - p1.x, 2.0) + pow(p2.y - p1.y, 2.0));
}
GD2Line::GD2Line(GD2Point * arr)
{
	this->p1 = arr[0];
	this->p2 = arr[1];
}
void GD2Line::toArrayPoint(GD2Point arr[])
{
	arr[0] = this->p1;
	arr[1] = this->p2;
}
///////////////////////////////////////////////////////////////////////////////////
GD2Flat::GD2Flat() {}
GD2Flat::GD2Flat(GD2Point & p1, GD2Point & p2, GD2Point & p3) :p1(p1), p2(p2), p3(p3)
{

}
GD2Flat::GD2Flat(GD2Flat & f) : p1(f.p1), p2(f.p2), p3(f.p3)
{

}
GD2Flat::GD2Flat(GD2Point * arr)
{
	this->p1 = arr[0];
	this->p2 = arr[1];
	this->p3 = arr[2];
}
void GD2Flat::toArrayPoint(GD2Point arr[])
{
	arr[0] = this->p1;
	arr[1] = this->p2;
	arr[2] = this->p3;
}
/////////////////////////////////////////////////////////////////////////////
GD3Triangle::GD3Triangle() :p1(0), p2(0), p3(0)
{

}
GD3Triangle::GD3Triangle(long p1, long p2, long p3) : p1(p1), p2(p2), p3(p3)
{

}
GD3Triangle::GD3Triangle(const GD3Triangle & t) : p1(t.p1), p2(t.p2), p3(t.p3)
{

}
GD3Triangle& GD3Triangle::operator=(const GD3Triangle & t)
{
	this->p1 = t.p1;
	this->p2 = t.p2;
	this->p3 = t.p3;
	return *this;
}
/////////////////////////////////////////////////////////////////////////////
GD3DataGroup::GD3DataGroup()
{
	this->pointCount = 0;
	this->trangleCount = 0;
	this->points = NULL;
	this->trangles = NULL;
}
GD3DataGroup::GD3DataGroup(GD3DataGroup & dg)
{
	this->allocMemory(dg.pointCount, dg.trangleCount);
	int i;
	for (i = 0; i < this->pointCount; i++)
	{
		this->points[i] = dg.points[i];
	}
	for (i = 0; i < this->trangleCount; i++)
	{
		this->trangles[i] = dg.trangles[i];
	}
}
GD3DataGroup& GD3DataGroup::operator=(const GD3DataGroup & dg)
{
	this->allocMemory(dg.pointCount, dg.trangleCount);
	int i;
	for (i = 0; i < this->pointCount; i++)
	{
		this->points[i] = dg.points[i];
	}
	for (i = 0; i < this->trangleCount; i++)
	{
		this->trangles[i] = dg.trangles[i];
	}
	return *this;
}
GD3DataGroup::~GD3DataGroup()
{
	freeMemory();
}
void GD3DataGroup::freeMemory()
{
	if (points)
		delete[] points;
	if (trangles)
		delete[] trangles;
	points = NULL;
	trangles = NULL;
	pointCount = 0;
	trangleCount = 0;
}
void GD3DataGroup::allocMemory(long pointCount, long trangleCount)
{
	this->freeMemory();
	this->pointCount = pointCount;
	this->trangleCount = trangleCount;
	this->points = new GD3Point[this->pointCount];
	this->trangles = new GD3Triangle[this->trangleCount];
}
long GD3DataGroup::getPointCount()
{
	return this->pointCount;
}
long GD3DataGroup::getTrangleCount()
{
	return this->trangleCount;
}
GD3Point & GD3DataGroup::pointAt(long index)
{
	return this->points[index];
}
GD3Triangle & GD3DataGroup::trangleAt(long index)
{
	return this->trangles[index];
}
//////////////////////////////////////////////////////////////////////////
GD3Camera::GD3Camera()
{
	fov = 30;
	cNear = 10;
	cFar = 50;
	proj_type = PROJ_TYPE::PRES_PROJ;
	pos = new GD3Point();
}

GD3Camera::GD3Camera(double fov, double cNear, double cFar, GD3Point* pos, PROJ_TYPE type)
{
	this->fov = fov;
	this->cNear = cNear;
	this->cFar = cFar;
	this->proj_type = type;
	this->pos = new GD3Point(pos->x, pos->y, pos->z);
}

void GD3Camera::WorldOrgToScreenOrg(GD3Point* p, PROJ_TYPE type)
{
	switch (type)
	{
	case GD3Camera::PRES_PROJ:
		WorldOrgToScreenOrgByPres(p);
		break;
	case GD3Camera::ORTH_PROJ:
		WorldOrgToScreenOrgByOrth(p);
		break;
	default:
		WorldOrgToScreenOrgByPres(p);
		break;
	}
}

GD3Camera::~GD3Camera() 
{
	delete pos;
	pos = nullptr;
}

void GD3Camera::WorldOrgToScreenOrgByOrth(GD3Point * p)
{

}

void GD3Camera::WorldOrgToScreenOrgByPres(GD3Point * p)
{
	WorldOrgToViewOrg(p);
	ViewOrgToScreenOrg(p);
}

void GD3Camera::WorldOrgToViewOrg(GD3Point * p)
{
	double M[4][4];
	GD3Vector eyePt(pos->x, pos->y, pos->z);
	GD3Vector lookCenter(0.f, 0.f, -1.f);
	GD3Vector upVec(0.f, 1.f, 0.f);
	GD3MatrixLookAtLH(M, eyePt, eyePt + lookCenter, upVec);
	GTools::GraphMulVaryMatrix(p, M);
}

void GD3Camera::ViewOrgToScreenOrg(GD3Point * p)
{
	auto cot = [=](const double angle)->double {
		return 1 / angle;
	};
	double nearClipPlaneHeight = 2 * cNear*tan(fov / 2);
	double farClipPlaneHeight = 2 * cFar*tan(fov / 2);
	double aspect = 1.f;
	double M[4][4]
	{
		{cot(fov / 2) / aspect,0,0,0},
		{0,cot(fov / 2),0,0},
		{0,0,(cFar + cNear) / (cFar - cNear),1},
		{0,0,(-2 * cNear*cFar) / (cFar - cNear),0}
	};
	GTools::GraphMulVaryMatrix(p, M);

}

void GD3Camera::GD3MatrixLookAtLH(double M[][4], GD3Vector & eyePt, GD3Vector & lookCenter, GD3Vector & upVec)
{
	direction = lookCenter - eyePt;
	right = direction.CrossMultiply(upVec);
	up = upVec;
	GD3Vector position;
	position.x = pos->x;
	position.y = pos->y;
	position.z = pos->z;
	M = new double[4][4]
	{
		{right.x,up.x,direction.x,0},
		{right.y,up.y,direction.y,0},
		{right.z,up.z,direction.z,0},
		{-(position*right),-(position*up),-(position*direction),1}
	};
}
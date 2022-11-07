#pragma once
#include<cmath>
#include<vector>
#include<iterator>
//向前申明
class GD3Point;

//工具类
class GTools
{
public:
	static const double MATH_PI;
	/*弧度角度互转*/
	static double AngleToRadian(double a);
	static double RadianToAngle(double a);
	//乘4*4三维变换矩阵
	static void GraphMulVaryMatrix(GD3Point * p, double matrix[][4]);
};

//三维点类
class GD3Point
{
public:
	double x;
	double y;
	double z;
	GD3Point();
	GD3Point(double x, double y, double z);
	GD3Point(const GD3Point & p);
	GD3Point& operator=(const GD3Point & p);
	bool operator==(const GD3Point & p);
	void ParseSpherical(double R, double aAngle, double bAngle);
	GD3Point(double * arr);
	void toArrayDouble(double arr[]);
};
//三维向量类
class GD3Vector : public GD3Point
{
public:
	GD3Vector();
	GD3Vector(double x, double y, double z);
	GD3Vector(GD3Vector & v);
	GD3Vector(GD3Point & p);
	GD3Vector(GD3Point & ps, GD3Point & pe);
	GD3Vector& operator=(const GD3Vector & v);
	bool operator==(const GD3Vector & v);
	double GetModuleLength();//获取向量模长
	void Untization();//单位化
	GD3Vector operator+(const GD3Vector & v);//向量加法
	GD3Vector operator-(const GD3Vector & v);//向量减法
	double operator*(const GD3Vector & v);//向量点乘
	GD3Vector CrossMultiply(GD3Vector & v);//向量叉乘
	double CosRadian(GD3Vector & v);//向量夹角
	GD3Vector(double * arr);
};
//三维法向量类
class GD3NormalLine :public GD3Vector
{
public:
	GD3NormalLine();
	GD3NormalLine(double x, double y, double z);
	GD3NormalLine(GD3Vector & v);
	GD3NormalLine(GD3NormalLine & n);
	GD3NormalLine(GD3Vector & v1, GD3Vector & v2);
	GD3NormalLine& operator=(const GD3NormalLine & n);
	GD3NormalLine(double * arr);
};
//三维平面类
class GD3Flat
{
public:
	GD3Point p1;
	GD3Point p2;
	GD3Point p3;
	GD3Flat();
	GD3Flat(GD3Point & p1, GD3Point & p2, GD3Point & p3);
	GD3NormalLine GetNormalLine();
	GD3NormalLine GetUntizationNormalLine();
	GD3Flat(GD3Point * arr);
	void toArrayPoint(GD3Point arr[]);
};
//二维点类
class GD2Point
{
public:
	double x;
	double y;
	GD2Point();
	GD2Point(double x, double y);
	GD2Point(const GD2Point & p);
	GD2Point& operator=(const GD2Point & p);
};
//二维向量类
class GD2Vector : public GD2Point
{
public:
	GD2Vector();
	GD2Vector(double x, double y);
	GD2Vector(GD2Vector & v);
	GD2Vector(GD2Point & p);
	GD2Vector(GD2Point & ps, GD2Point & pe);
	GD2Vector& operator=(const GD2Vector & v);
	bool operator==(const GD2Vector & v);
	double GetModuleLength();//获取向量模长
	void Untization();//单位化
	GD2Vector operator+(const GD2Vector & v);//向量加法
	GD2Vector operator-(const GD2Vector & v);//向量减法
	double operator*(const GD2Vector & v);//向量点乘
	double CosRadian(GD2Vector & v);//向量夹角
};
//二维直线类
class GD2Line
{
public:
	GD2Point p1;
	GD2Point p2;
	GD2Line();
	GD2Line(GD2Line & l);
	GD2Line(GD2Point & p1, GD2Point & p2);
	double GetDistance();
	GD2Line(GD2Point * arr);
	void toArrayPoint(GD2Point arr[]);
};
//二维平面类
class GD2Flat
{
public:
	GD2Point p1;
	GD2Point p2;
	GD2Point p3;
	GD2Flat();
	GD2Flat(GD2Point & p1, GD2Point & p2, GD2Point & p3);
	GD2Flat(GD2Flat & f);
	GD2Flat(GD2Point * arr);
	void toArrayPoint(GD2Point arr[]);
};
//三角片面顶点类
class GD3Triangle
{
public:
	long p1;
	long p2;
	long p3;
	GD3Triangle();
	GD3Triangle(long p1, long p2, long p3);
	GD3Triangle(const GD3Triangle & t);
	GD3Triangle& operator=(const GD3Triangle & t);
};
//三维数据存储类
class GD3DataGroup
{
public:
	GD3DataGroup();
	GD3DataGroup(GD3DataGroup & dg);
	GD3DataGroup& operator=(const GD3DataGroup & dg);
	~GD3DataGroup();
	void allocMemory(long pointCount, long trangleCount);
	long getPointCount();
	long getTrangleCount();
	GD3Point & pointAt(long index);
	GD3Triangle & trangleAt(long index);
private:
	void freeMemory();
	long pointCount;
	long trangleCount;
	GD3Point * points;
	GD3Triangle * trangles;
};

class GD3Camera 
{
public:
	static enum PROJ_TYPE
	{
		ORTH_PROJ,
		PRES_PROJ
	};
	double fov;
	double cNear;
	double cFar;
	GD3Point* pos;
	GD3Vector direction;//相当于z轴
	GD3Vector up;//相当于y轴
	GD3Vector right;//相当于x轴
	PROJ_TYPE proj_type;

public:
	GD3Camera();
	GD3Camera(double fov, double cNear, double cFar, GD3Point* pos, PROJ_TYPE type);
	void WorldOrgToScreenOrg(GD3Point* p, PROJ_TYPE type);
	~GD3Camera();

private:
	void WorldOrgToScreenOrgByOrth(GD3Point* p);
	void WorldOrgToScreenOrgByPres(GD3Point* p);
	void WorldOrgToViewOrg(GD3Point* p);
	void ViewOrgToScreenOrg(GD3Point* p);
	void GD3MatrixLookAtLH(double M[][4], GD3Vector& eyePt, GD3Vector& lookCenter, GD3Vector& upVec);
};


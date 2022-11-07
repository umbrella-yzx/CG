#pragma once
#include<cmath>
#include<vector>
#include<iterator>
//��ǰ����
class GD3Point;

//������
class GTools
{
public:
	static const double MATH_PI;
	/*���ȽǶȻ�ת*/
	static double AngleToRadian(double a);
	static double RadianToAngle(double a);
	//��4*4��ά�任����
	static void GraphMulVaryMatrix(GD3Point * p, double matrix[][4]);
};

//��ά����
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
//��ά������
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
	double GetModuleLength();//��ȡ����ģ��
	void Untization();//��λ��
	GD3Vector operator+(const GD3Vector & v);//�����ӷ�
	GD3Vector operator-(const GD3Vector & v);//��������
	double operator*(const GD3Vector & v);//�������
	GD3Vector CrossMultiply(GD3Vector & v);//�������
	double CosRadian(GD3Vector & v);//�����н�
	GD3Vector(double * arr);
};
//��ά��������
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
//��άƽ����
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
//��ά����
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
//��ά������
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
	double GetModuleLength();//��ȡ����ģ��
	void Untization();//��λ��
	GD2Vector operator+(const GD2Vector & v);//�����ӷ�
	GD2Vector operator-(const GD2Vector & v);//��������
	double operator*(const GD2Vector & v);//�������
	double CosRadian(GD2Vector & v);//�����н�
};
//��άֱ����
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
//��άƽ����
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
//����Ƭ�涥����
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
//��ά���ݴ洢��
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
	GD3Vector direction;//�൱��z��
	GD3Vector up;//�൱��y��
	GD3Vector right;//�൱��x��
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


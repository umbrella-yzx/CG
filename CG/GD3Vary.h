#pragma once
#include "GData.h"

class GD3Vary
{
public:
	//x,y,zΪ��ά����㣬�����ַ�������޸�ֵ
	//ƽ�Ʊ任��x,y,z�ֱ�ƽ��mx,my,mz����
	static void Move(GD3Point * p, double mx, double my, double mz);
	//�����任��x,y,z�ֱ����sx,sy,sz����
	static void Scale(GD3Point * p, double sx, double sy, double sz);
	//��ת�任������������x,y,z����תsx,sy,sz�Ƕȣ������ƣ�,���������������ת
	static void Spin(GD3Point * p, double sx, double sy, double sz);
	//����任���������ζ�x,y,z�ᷴ�䣬�����Ӧ��bx,by,bzֵΪ�棬��������
	static void Reflact(GD3Point * p, bool bx, bool by, bool bz);
	//����任���������ζ�xoy,yoz,xozƽ�淴�䣬�����Ӧ��xoy,yoz,xozֵΪ�棬��������
	static void FlatReflact(GD3Point * p, bool bxoy, bool byoz, bool bxoz);
	//���б任������������x,y,z����У��ֱ��뿪z,y����x���ƶ�gz,dy���룬��������
	static void Miscut(GD3Point * p, double xgz, double xdy, double yhz, double ybx, double zfy, double zcx);

	//����ϵ�ƶ��任��x,y,z�ֱ�Ϊ����ϵƽ��mx,my,mz���λ��
	static void OrgMove(GD3Point * p, double mx, double my, double mz);
	//����ϵ��ת�任������ϵ������x,y,z����תsx,sy,sz�Ƕȣ������ƣ����λ��
	static void OrgSpin(GD3Point * p, double sx, double sy, double sz);
	//����ϵ����任��ֱ�Ӳ��õ�任��ʽ
	static void OrgReflact(GD3Point * p, bool bx, bool by, bool bz);
	static void OrgFlatReflact(GD3Point * p, bool bxoy, bool byoz, bool bxoz);
};


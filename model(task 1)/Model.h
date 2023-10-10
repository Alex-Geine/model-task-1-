#pragma once
#include "pch.h"

class Model {		
private:
	double
		l, //������ ��������
		a, //��������� �������
		w, //������� �������
		f0, //��������� ����������
		df0, //��������� ������� ��������
		t = 0, //�����
		h = 0.00001, //��� ��������������
		T0, //����������� �������
		Y0, //����������� ����������
		niu, //����������� ������� ������
		k; //����������� ������ ������

	double maxf0 = 0;
	double maxdf0 = 0;

public:
	
	int index = 0;		

	//�������, ������������ ��������� �������
	void GetPar(CRITICAL_SECTION*cs, double& l, double& a, double& w, double& f0, double& df0, double& t, double &T0, double& Y0, double& maxf0, double& maxdf0);
	//�������, ������������ ��������� ������� ��� �������
	void GetPar(CRITICAL_SECTION* cs, double& l, double& a, double& w, double& f0, double& df0,  double&niu, double&k);

	//������� ���������� ����������
	void UpdatePar(double L,
		double A,
		double W,
		double f0,
		double df0,
		double niu,
		double k);

	//����� �����-�����
	void RK();

	void Clear();

	//������� ����������� �� f
	double V(double df);

	//������� ����������� �� z
	double U(double f, double df, double z);

	//������� �����-�����
	void Calculate(CRITICAL_SECTION* cs);
};

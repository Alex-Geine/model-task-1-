#pragma once
#include "Model.h"
#include<gdiplus.h>
#include <vector>

using namespace std;
using namespace Gdiplus;



class Controller {	
private:	
	Model* mod;
	MSG msg;
	CRITICAL_SECTION cs;
	CRITICAL_SECTION csModels;
	ULONG_PTR token;

	HANDLE GET_PAR;
	HANDLE TREAD;

	//������ �� ���������� ��� �������� ��������
	vector<PointF> phasePoints;


	

	double
		l, //������ ��������
		a, //��������� �������
		w, //������� �������
		f0, //��������� ����������
		df0, //��������� ������� ��������
		t,	//�����
		T0,	//�������� �� ������� 
		Y0;	//�������� � �����������

	double maxf0, maxdf0;
	
	

	
	

	//�������, ������� �������� � ������ � �������
	DWORD WINAPI ModelFunk();

	static DWORD WINAPI StaticModelFunk(PVOID param) {
		Controller* This = (Controller*)param;
		return This->ModelFunk();
	}

	

public:
	//���������� � �������
	struct MINF {
		Model* mod;
		MINF(Model* mod) :mod(mod)
		{
		}
		double
			l, //������ ��������
			a, //��������� �������
			w, //������� �������
			f0, //��������� ����������
			df0, //��������� ������� ��������
			t,	//�����
			T0,	//�������� �� ������� 
			Y0;	//�������� � �����������

		COLORREF col;

		double maxf0, maxdf0;
	};

	MINF* minf;
	vector<MINF*> Models;
	
	//������� ������
	void Clear();
	
	//��������� ��������� �������� �������
	void DrawMainGr(LPDRAWITEMSTRUCT Item1);

	//��������� ��������� �������� �������
	void DrawPhase(LPDRAWITEMSTRUCT Item1);

	//�������� ��������� ������
	void UpdPar(
		double l, //������ ��������
		double a, //��������� �������
		double w, //������� �������
		double f0, //��������� ����������
		double df0, //��������� ������� ��������	
		double niu, //����������� ������� ������
		double k
	);

	//��������� ��������
	void Start();

	//���������� ���������
	void Draw();
	
	//������� ����
	void CreateMinf(		
		double l, //������ ��������
		double a, //��������� �������
		double w, //������� �������
		double f0, //��������� ����������
		double df0, //��������� ������� ��������	
		double niu, //����������� ������� ������
		double k,
		COLORREF col);
	

	//�����������
	Controller(): mod(new Model())
	{		
		GdiplusStartupInput si;
		GdiplusStartup(&token, &si, NULL);

		minf = new MINF(mod);

		//����������� ������
		InitializeCriticalSection(&cs);
		//��������� ��� ��������� ����������
		HANDLE GET_PAR =
			CreateEvent(NULL, FALSE, FALSE, LPWSTR("GET_PAR"));
	}
	//����������
	~Controller() {
		GdiplusShutdown(token);
	}

	
};
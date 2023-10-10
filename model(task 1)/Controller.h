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

	double maxla = 0;

	

	
	int curMod;
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
		HANDLE TREAD;
		CRITICAL_SECTION cs;
		//������ �� ���������� ��� �������� ��������
		vector<PointF> phasePoints;

		double maxf0, maxdf0;
		int id;
	};

	MINF* minf;
	vector<MINF*> Models;
	
	

	//�������, ������� �������� � ������ � �������
	DWORD WINAPI ModelFunk(int id);

	static DWORD WINAPI StaticModelFunk(PVOID param) {
		Controller* This = (Controller*)param;
		return This->ModelFunk(This->curMod);
	}

	

public:
	int drawId = 0;
	double maxf0 = 0, maxdf0 = 0;
	double xst = 0, yst = 0, scalegr = 1;
	double xstTr = 0, ystTr = 0, scalegrTr = 1;
	void GetParOfModel(
		int id, 
		double &l, //������ ��������
		double &a, //��������� �������
		double &w, //������� �������
		double &f0, //��������� ����������
		double &df0, //��������� ������� ��������	
		double &niu, //����������� ������� ������
		double &k,
		COLORREF &col);
	void UpdateModel(
		int id,
		double l, //������ ��������
		double a, //��������� �������
		double w, //������� �������
		double f0, //��������� ����������
		double df0, //��������� ������� ��������	
		double niu, //����������� ������� ������
		double k,
		COLORREF col);
	//������� ������
	void DeleteModel(int id);
	
	//������� ������
	void Clear();
	
	//��������� ��������� �������� �������6
	void DrawMainGr(LPDRAWITEMSTRUCT Item1);

	//��������� ��������� �������� �������
	void DrawPhase(LPDRAWITEMSTRUCT Item1);

	//��������� ��������� �������� �������
	void DrawPhaseTr(LPDRAWITEMSTRUCT Item1);

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
		COLORREF col,
		int id);
	

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
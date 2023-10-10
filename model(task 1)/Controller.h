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



	//вектор со значениями для фазового портрета
	vector<PointF> phasePoints;	

	double
		l, //Длинна маятника
		a, //Амплитуда подвеса
		w, //частота подвеса
		f0, //начальное отклонение
		df0, //начальная угловая скорость
		t,	//время
		T0,	//поправка ко времени 
		Y0;	//поправка к координатам

	double maxla = 0;

	

	
	int curMod;
	//информация о моделях
	struct MINF {
		Model* mod;
		MINF(Model* mod) :mod(mod)
		{
		}
		double
			l, //Длинна маятника
			a, //Амплитуда подвеса
			w, //частота подвеса
			f0, //начальное отклонение
			df0, //начальная угловая скорость
			t,	//время
			T0,	//поправка ко времени 
			Y0;	//поправка к координатам

		COLORREF col;
		HANDLE TREAD;
		CRITICAL_SECTION cs;
		//вектор со значениями для фазового портрета
		vector<PointF> phasePoints;

		double maxf0, maxdf0;
		int id;
	};

	MINF* minf;
	vector<MINF*> Models;
	
	

	//функция, которая работает в потоке с моделью
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
		double &l, //Длинна маятника
		double &a, //Амплитуда подвеса
		double &w, //частота подвеса
		double &f0, //начальное отклонение
		double &df0, //начальная угловая скорость	
		double &niu, //коэффициент вязкого трения
		double &k,
		COLORREF &col);
	void UpdateModel(
		int id,
		double l, //Длинна маятника
		double a, //Амплитуда подвеса
		double w, //частота подвеса
		double f0, //начальное отклонение
		double df0, //начальная угловая скорость	
		double niu, //коэффициент вязкого трения
		double k,
		COLORREF col);
	//удаляет модель
	void DeleteModel(int id);
	
	//очищает данные
	void Clear();
	
	//запускает отрисовку главного графика6
	void DrawMainGr(LPDRAWITEMSTRUCT Item1);

	//запускает отрисовку главного графика
	void DrawPhase(LPDRAWITEMSTRUCT Item1);

	//запускает отрисовку главного графика
	void DrawPhaseTr(LPDRAWITEMSTRUCT Item1);

	//апдейтит параметры модели
	void UpdPar(
		double l, //Длинна маятника
		double a, //Амплитуда подвеса
		double w, //частота подвеса
		double f0, //начальное отклонение
		double df0, //начальная угловая скорость	
		double niu, //коэффициент вязкого трения
		double k
	);

	

	//запусткает отрисовку
	void Draw();
	
	//создать МИНФ
	void CreateMinf(		
		double l, //Длинна маятника
		double a, //Амплитуда подвеса
		double w, //частота подвеса
		double f0, //начальное отклонение
		double df0, //начальная угловая скорость	
		double niu, //коэффициент вязкого трения
		double k,
		COLORREF col,
		int id);
	

	//конструктор
	Controller(): mod(new Model())
	{		
		GdiplusStartupInput si;
		GdiplusStartup(&token, &si, NULL);

		minf = new MINF(mod);

		//критическая секция
		InitializeCriticalSection(&cs);
		//сообщение для получения параметров
		HANDLE GET_PAR =
			CreateEvent(NULL, FALSE, FALSE, LPWSTR("GET_PAR"));
		
	}
	//деструктор
	~Controller() {
		GdiplusShutdown(token);
	}

	
};
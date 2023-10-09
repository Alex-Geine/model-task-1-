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

	double maxf0, maxdf0;
	
	

	
	

	//функция, которая работает в потоке с моделью
	DWORD WINAPI ModelFunk();

	static DWORD WINAPI StaticModelFunk(PVOID param) {
		Controller* This = (Controller*)param;
		return This->ModelFunk();
	}

	

public:
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

		double maxf0, maxdf0;
	};

	MINF* minf;
	vector<MINF*> Models;
	
	//очищает данные
	void Clear();
	
	//запускает отрисовку главного графика
	void DrawMainGr(LPDRAWITEMSTRUCT Item1);

	//запускает отрисовку главного графика
	void DrawPhase(LPDRAWITEMSTRUCT Item1);

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

	//запускает шарманку
	void Start();

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
		COLORREF col);
	

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
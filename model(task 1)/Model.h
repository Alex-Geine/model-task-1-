#pragma once
#include "pch.h"

class Model {		
private:
	double
		l, //Длинна маятника
		a, //Амплитуда подвеса
		w, //частота подвеса
		f0, //начальное отклонение
		df0, //начальная угловая скорость
		t = 0, //время
		h = 0.00001, //шаг интегрирования
		T0, //коэффициент времени
		Y0, //коэффициент координаты
		niu, //коэффициент вязкого трения
		k; //коэффициент сухого трения

	double maxf0 = 0;
	double maxdf0 = 0;

public:
	
	int index = 0;		

	//функция, возвращающая параметры системы
	void GetPar(CRITICAL_SECTION*cs, double& l, double& a, double& w, double& f0, double& df0, double& t, double &T0, double& Y0, double& maxf0, double& maxdf0);
	//функция, возвращающая параметры системы для апдейта
	void GetPar(CRITICAL_SECTION* cs, double& l, double& a, double& w, double& f0, double& df0,  double&niu, double&k);

	//функция обновления параметров
	void UpdatePar(double L,
		double A,
		double W,
		double f0,
		double df0,
		double niu,
		double k);

	//Метод Рунге-Кутты
	void RK();

	void Clear();

	//Функция производной от f
	double V(double df);

	//Функция производной от z
	double U(double f, double df, double z);

	//Считает Рунге-Кутту
	void Calculate(CRITICAL_SECTION* cs);
};

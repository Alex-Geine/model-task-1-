#include "pch.h"
#include "Model.h"

#define _USE_MATH_DEFINES
#include  <math.h>
#define NOT_UPDATE -777


//функцкия управления отрисовкой
void Model::Calculate(CRITICAL_SECTION* cs) {
	index += 1;
	EnterCriticalSection(cs);
	RK();
	t += h;
	LeaveCriticalSection(cs);		
}

//функция обновления параметров
void Model::UpdatePar(
	double L, 
	double A, 
	double W,
	double f0,
	double df0,
	double niu,
	double k
	) {
	if(L != NOT_UPDATE)
		this->l = L;
	if (A != NOT_UPDATE)
		this->a = A;
	if (W != NOT_UPDATE)	
		this->w = W;
	if (f0 != NOT_UPDATE)
		this->f0 = f0;
	if (df0 != NOT_UPDATE)
		this->df0 = df0;
	if (niu != NOT_UPDATE)
		this->niu = niu;
	if (k != NOT_UPDATE)
		this->k = k;

	Y0 = l;
	T0 = sqrt(10 / l);
}


//Метод Рунге-Кутты
void Model::RK() {
	double q0 = U(t, f0, df0);
	double k0 = V(df0);
	
	double q1 = U(t + h/2, f0 + k0 * h / 2, df0 + q0 * h / 2);
	double k1 = V(df0 + q0 * h / 2);

	double q2 = U(t + h / 2, f0 + k1 * h / 2, df0 + q1 * h / 2);
	double k2 = V(df0 + q1 * h / 2);

	double q3 = U(t + h, f0 + k2 * h, df0 + q2 * h);
	double k3 = V(df0 + q2 * h);

	df0 += h / 6 * (q0 + 2 * q1 + 2 * q2 + q3);
	f0 += h / 6 * (k0 + 2 * k1 + 2 * k2 + k3);

	if (fabs(maxf0) < fabs(f0)) maxf0 = fabs(f0);
	if (fabs(maxdf0) < fabs(df0)) maxdf0 = fabs(df0);
}

//Функция z
double Model::V(double df) {
	return df0;
}
void Model::Clear() {
	maxf0 = 0;
	maxdf0 = 0;
}



//Функция производной от z
double Model::U(double t, double f, double df) {
	double sign = -1;
	if (df0 < 0)
		sign = 1;

	return -a * w * w * sin(w * t) * sin(f * M_PI / 180) - sin(f * M_PI / 180) + fabs(df) * k * sign + df * df * niu * sign;
}


//функция, возвращающая параметры системы
void Model::GetPar(CRITICAL_SECTION* cs,double& l, double& a, double& w, double& f0, double& df0, double& t, double& T0, double& Y0, double& maxf0, double& maxdf0) {
	EnterCriticalSection(cs);
	l = this->l;
	t = this->t;
	a = this->a;
	w = this->w;
	f0 = this->f0;
	df0 = this->df0;
	T0 = this->T0;
	Y0 = this->Y0;
	maxf0 = this->maxf0;
	maxdf0 = this->maxdf0;

	LeaveCriticalSection(cs);
}
//функция, возвращающая параметры системы для апдейта
void Model::GetPar(CRITICAL_SECTION* cs, double& l, double& a, double& w, double& f0, double& df0, double& niu, double& k) {
	EnterCriticalSection(cs);
	l = this->l;	
	a = this->a;
	w = this->w;
	f0 = this->f0;
	df0 = this->df0;
	niu = this->niu;
	k = this->k;	

	LeaveCriticalSection(cs);
}
#include "pch.h"
#include "Controller.h"

#define _USE_MATH_DEFINES
#include  <math.h>


//�����, ������ ���������
DWORD WINAPI Controller::ModelFunk() {
	HANDLE cur = GetCurrentThread();
	while (1) {
		if( (!(mod->index % 1000)) && (mod->index != 0)) {
			SuspendThread(cur);
		}

		mod->Calculate(&cs);
	}
	
	return 0;
}



//�������� ��������� ������
void Controller::UpdPar(
	double l, //������ ��������
	double a, //��������� �������
	double w, //������� �������
	double f0, //��������� ����������
	double df0, //��������� ������� ��������	
	double niu, //����������� ������� ������
	double k
) 
{
	mod->UpdatePar(l,a,w,f0,df0,niu,k);
}

//��������� ������
void Controller::Start() {  
	//������ ��������� ������ ��������� �   ������ ������	
	TREAD = CreateThread(NULL, NULL, StaticModelFunk, (void*)this, 0, NULL);	
}

//���������� ���������
void Controller::Draw() {
	EnterCriticalSection(&csModels);
	mod->GetPar(&cs,l, a, w, f0, df0, t, T0, Y0, maxf0, maxdf0);
	phasePoints.push_back(PointF(f0, df0 * T0));
	LeaveCriticalSection(&csModels);
	ResumeThread(TREAD);			
}

//��������� ��������� �������� �������
void Controller::DrawMainGr(LPDRAWITEMSTRUCT Item1) {
	//��������� ��������� ���������
		double ItemWidth = Item1->rcItem.right - Item1->rcItem.left,
			ItemHeight = Item1->rcItem.bottom - Item1->rcItem.top;
		//��������� ������� � ������� ����������
		double top = 2 * (l + a) * (1 + 0.2);
		double bottom = 0;
		double left = 0;
		double right = 2 * (l + a) * (1 + 0.2);

		//xPadding = (right - left) / 10;
		//yPadding = (top - bottom) / 10;

		double steplenY = (top - bottom) / 10,
			steplenX = (right - left) / 10;

		double xScale = ItemWidth / (right - left);
		double yScale = -ItemHeight / (top - bottom);



		Bitmap Image(ItemWidth, ItemHeight);
		Graphics gr(&Image);
		gr.Clear(Color::White);
		//�����������
		gr.SetSmoothingMode(SmoothingModeAntiAlias);

		//�������������� ����(������� � ����������� ������ �������
		Matrix matr;
		matr.Scale(xScale, yScale + 1); //��������������
		matr.Translate(right / 2, -top / 2); //������� ������ ���������


		gr.SetTransform(&matr);


		Pen BackGroundPen(Color::DarkGray, 0.005);
		Pen pen(Color::BlueViolet, 0.005);

		Pen StickPen(Color::CornflowerBlue, 0.02);
		SolidBrush brush(Color::Black);
		SolidBrush PlatformBrush(Color::Crimson);
		Gdiplus::Font font((L"Times New Roman"), 14, FontStyle::FontStyleRegular, UnitPixel);

		//���

		gr.DrawLine(&pen, PointF(-l - a, 0), PointF(l + a, 0));
		gr.DrawLine(&pen, PointF(0, l + a), PointF(0, -l - a));

		double bollWidth = l / 5;
		double platformWidth = l / 8;
		double platformHeigtht = platformWidth / 2;

		double T = t * T0;

		//���������� ��������� �������
		double yPl = a * Y0 * sin(w * T);
		double xBoll = l * sin(f0 * M_PI / 180);
		double yBoll = l * cos(f0 * M_PI / 180);

			gr.FillRectangle(&PlatformBrush, RectF(-platformWidth / 2, -yPl - platformHeigtht / 2, platformWidth, platformHeigtht));
			gr.FillEllipse(&brush, RectF(xBoll - bollWidth / 2, -yBoll - yPl - bollWidth / 2, bollWidth, bollWidth));
			gr.DrawLine(&StickPen, PointF(0, -yPl), PointF(xBoll, -yBoll- yPl));
		Graphics grnew(Item1->hDC);
		grnew.DrawImage(&Image, 0, 0);
}

//��������� ��������� �������� �������
void Controller::DrawPhase(LPDRAWITEMSTRUCT Item1) {
		//��������� ��������� ���������
		double ItemWidth = Item1->rcItem.right - Item1->rcItem.left,
			ItemHeight = Item1->rcItem.bottom - Item1->rcItem.top;
		//��������� ������� � ������� ����������
		double top = 2 * (maxdf0 * T0) * (1 + 0.2);
		double bottom = 0;
		double left = 0;
		double right = 2 * (maxf0) * (1 + 0.2);

		//xPadding = (right - left) / 10;
		//yPadding = (top - bottom) / 10;

		double steplenY = (top - bottom) / 10,
			steplenX = (right - left) / 10;

		double xScale = ItemWidth / (right - left);
		double yScale = -ItemHeight / (top - bottom);



		Bitmap Image(ItemWidth, ItemHeight);
		Graphics gr(&Image);
		gr.Clear(Color::White);
		//�����������
		gr.SetSmoothingMode(SmoothingModeAntiAlias);

		//�������������� ����(������� � ����������� ������ �������
		Matrix matr;
		matr.Scale(xScale, yScale + 1); //��������������
		matr.Translate(right / 2, -top / 2); //������� ������ ���������


		gr.SetTransform(&matr);


		Pen BackGroundPen(Color::DarkGray, 0.005);
		Pen pen(Color::BlueViolet, 0.006);

		Pen StickPen(Color::CornflowerBlue, 0.02);
		SolidBrush brush(Color::Black);
		SolidBrush PlatformBrush(Color::Crimson);
		Gdiplus::Font font((L"Times New Roman"), 14, FontStyle::FontStyleRegular, UnitPixel);

		
		//��������
		for (int i = 0; i < 10; i++)
		{
			//��������������
			gr.DrawLine(&BackGroundPen, PointF(-right / 2, top / 2 - i * steplenY), PointF(right / 2, top / 2 - i * steplenY));

			//������������
			gr.DrawLine(&BackGroundPen, PointF(-right / 2 + i * steplenX, top/2), PointF(-right / 2 + i * steplenX, -top/2));
		}

		//������� ���
		//��������������
		gr.DrawLine(&pen, PointF(-right/2, 0), PointF(right/2, 0));

		//������������
		gr.DrawLine(&pen, PointF(0, top / 2), PointF(0, -top / 2));

		gr.ResetTransform();

		//������� � ����
		for (int i = 0; i < 11; i++)
		{
			CString str;

			//�� Y
			str.Format(L"%.2f", top/2 - i * steplenY);
			PointF strPoint(0, top/2 - i * steplenY);
			matr.TransformPoints(&strPoint);
			gr.DrawString(str, str.GetLength() + 1, &font, strPoint, &brush);

			//�� X
			str.Format(L"%.2f", right /2  - i * steplenX);
			strPoint.X = right / 2 - i  * steplenX;
			strPoint.Y = 0;
			matr.TransformPoints(&strPoint);
			gr.DrawString(str, str.GetLength() + 1, &font, strPoint, &brush);
		}

		gr.SetTransform(&matr);
		if (phasePoints.size() >= 2) {
			for (int i = 0; i < phasePoints.size() - 1; i++) {
				gr.DrawLine(&StickPen, phasePoints[i], phasePoints[i + 1]);
			}
		}

		

		Graphics grnew(Item1->hDC);
		grnew.DrawImage(&Image, 0, 0);
	
}

//������� ������
void Controller::Clear() {
	phasePoints.clear();
}

//������� ����
void Controller::CreateMinf(
	double l, //������ ��������
	double a, //��������� �������
	double w, //������� �������
	double f0, //��������� ����������
	double df0, //��������� ������� ��������	
	double niu, //����������� ������� ������
	double k,
	COLORREF col) {
	EnterCriticalSection(&csModels);
	Model* mod = new Model;
	mod->UpdatePar(l, a, w, f0, df0, niu, k);
	MINF* m = new MINF(mod);
	m->col = col;
	Models.push_back(m);
	LeaveCriticalSection(&csModels);
}

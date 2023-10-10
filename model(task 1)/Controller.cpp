#include "pch.h"
#include "Controller.h"

#define _USE_MATH_DEFINES
#include  <math.h>


//�����, ������ ���������
DWORD WINAPI Controller::ModelFunk(int id) {
	HANDLE cur = GetCurrentThread();
	Model* mod = Models[id]->mod;
	CRITICAL_SECTION Cs = Models[id]->cs;

	while (1) {
		if( (!(mod->index % 100000)) && (mod->index != 0)) {
			SuspendThread(cur);
		}

		mod->Calculate(&Cs);
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



//���������� ���������(������� ���� ������� � �������� ���� ����������)
void Controller::Draw() {
	EnterCriticalSection(&csModels);

	for (int i = 0; i < Models.size(); i++) {
		MINF* minf = Models[i];
		Model* mod = Models[i]->mod;
		mod->GetPar(&minf->cs, minf->l, minf->a, minf->w, minf->f0, minf->df0, minf->t, minf->T0, minf->Y0, minf->maxf0, minf->maxdf0);
		minf->phasePoints.push_back(PointF(minf->f0, minf->df0 * minf->T0));

		//���������� ������������ �������� ��� ��������
		if (maxf0 < minf->maxf0) maxf0 = minf->maxf0;
		if (maxdf0 < (minf->maxdf0 * minf->T0)) maxdf0 = (minf->maxdf0 * minf->T0);
		if (maxla < (minf->l + minf->a)) {
			maxla = (minf->l + minf->a);
			l = minf->l;
			a = minf->a;
		}

		ResumeThread(minf->TREAD);
	}	
	
	LeaveCriticalSection(&csModels);				
}

//��������� ��������� �������� �������
void Controller::DrawMainGr(LPDRAWITEMSTRUCT Item1) {
	if (Models.size() != 0) {
		//��������� ��������� ���������
		double ItemWidth = Item1->rcItem.right - Item1->rcItem.left,
			ItemHeight = Item1->rcItem.bottom - Item1->rcItem.top;
		//��������� ������� � ������� ����������
		double top = 2 * (maxla) * (1 + 0.2);
		double bottom = 0;
		double left = 0;
		double right = 2 * (maxla) * (1 + 0.2);

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

		
		
		
		Gdiplus::Font font((L"Times New Roman"), 14, FontStyle::FontStyleRegular, UnitPixel);

		//���

		gr.DrawLine(&pen, PointF(-l - a, 0), PointF(l + a, 0));
		gr.DrawLine(&pen, PointF(0, l + a), PointF(0, -l - a));

		double bollWidth = l / 5;
		double platformWidth = l / 8;
		double platformHeigtht = platformWidth / 2;

		//��������� ���������
		for (int i = 0; i < Models.size(); i++) {
			MINF* minf = Models[i];

			Color color;
			color.SetFromCOLORREF(minf->col);
			//SolidBrush br()
			SolidBrush brush(color);
			Pen StickPen(color, 0.02);

			double T = minf->t * minf->T0;

			//���������� ��������� �������
			double yPl = minf->a * minf->Y0 * sin(minf->w * T);
			double xBoll = minf->l * sin(minf->f0 * M_PI / 180);
			double yBoll = minf->l * cos(minf->f0 * M_PI / 180);

			gr.FillRectangle(&brush, RectF(-platformWidth / 2, -yPl - platformHeigtht / 2, platformWidth, platformHeigtht));
			gr.FillEllipse(&brush, RectF(xBoll - bollWidth / 2, -yBoll - yPl - bollWidth / 2, bollWidth, bollWidth));
			gr.DrawLine(&StickPen, PointF(0, -yPl), PointF(xBoll, -yBoll - yPl));
		}
		
		Graphics grnew(Item1->hDC);
		grnew.DrawImage(&Image, 0, 0);
	}	
}

//��������� ��������� �������� �������
void Controller::DrawPhase(LPDRAWITEMSTRUCT Item1) {
	if (Models.size() != 0) {
		//��������� ��������� ���������
		double ItemWidth = Item1->rcItem.right - Item1->rcItem.left,
			ItemHeight = Item1->rcItem.bottom - Item1->rcItem.top;
		//��������� ������� � ������� ����������
		double top = 2 * (maxdf0) * (1 + 0.2);
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
		matr.Scale(xScale * scalegr, (yScale + 1) * scalegr); //��������������
		matr.Translate(right / 2 + xst, -top / 2 + yst); //������� ������ ���������


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
			gr.DrawLine(&BackGroundPen, PointF(-right / 2, top / 2 - i * steplenY ), PointF(right / 2, top / 2 - i * steplenY ));

			//������������
			gr.DrawLine(&BackGroundPen, PointF(-right / 2 + i * steplenX, top / 2 ), PointF(-right / 2 + i * steplenX, -top / 2 ));
		}

		//������� ���
		//��������������
		gr.DrawLine(&pen, PointF(-right / 2, 0), PointF(right / 2, 0));

		//������������
		gr.DrawLine(&pen, PointF(0, top / 2), PointF(0, -top / 2));

		gr.ResetTransform();

		//������� � ����
		for (int i = 0; i < 11; i++)
		{
			CString str;

			//�� Y
			str.Format(L"%.2f", top / 2 - i * steplenY);
			PointF strPoint(0, top / 2 - i * steplenY);
			matr.TransformPoints(&strPoint);
			gr.DrawString(str, str.GetLength() + 1, &font, strPoint, &brush);

			//�� X
			str.Format(L"%.2f", right / 2 - i * steplenX);
			strPoint.X = right / 2 - i * steplenX;
			strPoint.Y = 0;
			matr.TransformPoints(&strPoint);
			gr.DrawString(str, str.GetLength() + 1, &font, strPoint, &brush);
		}

		gr.SetTransform(&matr);

		//��������� �������� �������� 

		for (int i = 0; i < Models.size(); i++) {
			MINF* minf = Models[i];
			Color color;
			color.SetFromCOLORREF(minf->col);			
			Pen StickPen(color, 0.02);

			if (minf->phasePoints.size() >= 2) {
				for (int i = 0; i < minf->phasePoints.size() - 1; i++) {
					gr.DrawLine(&StickPen, minf->phasePoints[i], minf->phasePoints[i + 1]);
				}
			}
		}
		



		Graphics grnew(Item1->hDC);
		grnew.DrawImage(&Image, 0, 0);
	}
}

//��������� ��������� ������� ������� ����������
void Controller::DrawPhaseTr(LPDRAWITEMSTRUCT Item1) {
	if (drawId != 0) {
		MINF* minfa = nullptr;
		for (int i = 0; i < Models.size(); i++) {
			minfa = Models[i];
			if (minfa->id == drawId)
				i = Models.size();			
		}
		
		Color color;
		color.SetFromCOLORREF(minfa->col);
		Pen StickPen(color, 0.02);
		//��������� ��������� ���������
		double ItemWidth = Item1->rcItem.right - Item1->rcItem.left,
			ItemHeight = Item1->rcItem.bottom - Item1->rcItem.top;
		//��������� ������� � ������� ����������
		double top = 2 * (maxdf0) * (1 + 0.2);
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
		matr.Scale(xScale * scalegrTr, (yScale + 1)*scalegrTr ); //��������������
		matr.Translate(right / 2 + xstTr, -top / 2 + ystTr); //������� ������ ���������


		gr.SetTransform(&matr);


		Pen BackGroundPen(Color::DarkGray, 0.005);
		Pen pen(Color::BlueViolet, 0.006);

		
		SolidBrush brush(Color::Black);
		SolidBrush PlatformBrush(Color::Crimson);
		Gdiplus::Font font((L"Times New Roman"), 14, FontStyle::FontStyleRegular, UnitPixel);


		//��������
		for (int i = 0; i < 10; i++)
		{
			//��������������
			gr.DrawLine(&BackGroundPen, PointF(-right / 2, top / 2 - i * steplenY), PointF(right / 2, top / 2 - i * steplenY));

			//������������
			gr.DrawLine(&BackGroundPen, PointF(-right / 2 + i * steplenX, top / 2), PointF(-right / 2 + i * steplenX, -top / 2));
		}

		//������� ���
		//��������������
		gr.DrawLine(&pen, PointF(-right / 2, 0), PointF(right / 2, 0));

		//������������
		gr.DrawLine(&pen, PointF(0, top / 2), PointF(0, -top / 2));

		gr.ResetTransform();

		//������� � ����
		for (int i = 0; i < 11; i++)
		{
			CString str;

			//�� Y
			str.Format(L"%.2f", top / 2 - i * steplenY);
			PointF strPoint(0, top / 2 - i * steplenY);
			matr.TransformPoints(&strPoint);
			gr.DrawString(str, str.GetLength() + 1, &font, strPoint, &brush);

			//�� X
			str.Format(L"%.2f", right / 2 - i * steplenX);
			strPoint.X = right / 2 - i * steplenX;
			strPoint.Y = 0;
			matr.TransformPoints(&strPoint);
			gr.DrawString(str, str.GetLength() + 1, &font, strPoint, &brush);
		}

		gr.SetTransform(&matr);

		//��������� �������� �������� 

		
			

			if (minfa->phasePoints.size() >= 2) {
				for (int i = 0; i < minfa->phasePoints.size() - 1; i++) {
					gr.DrawLine(&StickPen, minfa->phasePoints[i], minfa->phasePoints[i + 1]);
				}
			}
		




		Graphics grnew(Item1->hDC);
		grnew.DrawImage(&Image, 0, 0);
	}
}

//������� ������
void Controller::Clear() {
	for (int i = 0; i < Models.size(); i++) {
		EnterCriticalSection(&csModels);
		Models[i]->phasePoints.clear();
		Models[i]->mod->Clear();
		LeaveCriticalSection(&csModels);
		
	}
	maxf0 = 0; maxdf0 = 0; maxla = 0;
	xst = 0; yst = 0; scalegr = 1;
	xstTr = 0; ystTr = 0; scalegrTr = 1;
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
	COLORREF col,
	int id) {

	Model* model = new Model;
	model->UpdatePar(l, a, w, f0, df0, niu, k);
	MINF* m = new MINF(model);
	m->col = col;
	m->id = id;

	EnterCriticalSection(&csModels);	
	Models.push_back(m);
	LeaveCriticalSection(&csModels);
	
	
	curMod = Models.size() - 1;
	Models[curMod]->TREAD = CreateThread(NULL, NULL, StaticModelFunk, (void*)this, 0, NULL);
}

//������� ������
void Controller::DeleteModel(int id) {
	//������� �������
	EnterCriticalSection(&csModels);
	auto iter = Models.begin();
	for (int i = 0; i < Models.size(); i++) {
		
		if (Models[i]->id == id) {
			TerminateThread(TREAD, 0);
			iter += i;
			Models.erase(iter);
			i = Models.size();
		}
	}

	LeaveCriticalSection(&csModels);
	

}

void Controller::UpdateModel(
	int id,
	double l, //������ ��������
	double a, //��������� �������
	double w, //������� �������
	double f0, //��������� ����������
	double df0, //��������� ������� ��������	
	double niu, //����������� ������� ������
	double k,
	COLORREF col) 
{
	EnterCriticalSection(&csModels);
	auto iter = Models.begin();
	for (int i = 0; i < Models.size(); i++) {

		if (Models[i]->id == id) {
			EnterCriticalSection(&(Models[i]->cs));
			Models[i]->mod->UpdatePar(l, a, w, f0, df0, niu, k);
			Models[i]->col = col;
			LeaveCriticalSection(&(Models[i]->cs));
		}
	}

	LeaveCriticalSection(&csModels);


}

void Controller::GetParOfModel(
	int id,
	double &l, //������ ��������
	double &a, //��������� �������
	double &w, //������� �������
	double &f0, //��������� ����������
	double &df0, //��������� ������� ��������	
	double &niu, //����������� ������� ������
	double &k,
	COLORREF &col) {
	EnterCriticalSection(&csModels);
	auto iter = Models.begin();
	for (int i = 0; i < Models.size(); i++) {

		if (Models[i]->id == id) {
			EnterCriticalSection(&(Models[i]->cs));
			Models[i]->mod->GetPar(&(Models[i]->cs),l, a, w, f0, df0, niu, k);
			LeaveCriticalSection(&(Models[i]->cs));
			col = Models[i]->col;
		}
	}

	LeaveCriticalSection(&csModels);
}
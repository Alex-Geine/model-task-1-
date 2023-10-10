// ModelSetter.cpp: файл реализации
//

#include "pch.h"
#include "model(task 1).h"
#include "afxdialogex.h"
#include "ModelSetter.h"

#define NON_UPDATE -777
// Диалоговое окно ModelSetter

IMPLEMENT_DYNAMIC(ModelSetter, CDialogEx)

ModelSetter::ModelSetter(CWnd* pParent /*=nullptr*/, Controller* con)
	: CDialogEx(IDD_DIALOG4, pParent), control(con)
	, L(1)
	, A(0.1)
	, w(0.01)
	, f0(40)
	, df0(0)
	, niu(0)
	, k(0)
{
}
	

ModelSetter::~ModelSetter()
{
}

void ModelSetter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, L);
	DDX_Text(pDX, IDC_EDIT2, A);
	DDX_Text(pDX, IDC_EDIT3, w);
	DDX_Text(pDX, IDC_EDIT4, f0);
	DDX_Text(pDX, IDC_EDIT5, df0);
	DDX_Text(pDX, IDC_EDIT6, niu);
	DDX_Text(pDX, IDC_EDIT7, k);

	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, color);
}


BEGIN_MESSAGE_MAP(ModelSetter, CDialogEx)
	ON_BN_CLICKED(IDOK, &ModelSetter::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений ModelSetter


void ModelSetter::OnBnClickedOk()
{	
	UpdateData();
	//проверка на неотрицательность
	if ((L < 0) || (A < 0) || (w < 0)) {
		MessageBox(L"ERROR!", L"Negative values", NULL);
	}
	else {
		if (upd) {
			
			pcol = color.GetColor();
			//проверка на изменение параметров
			if (L == Lpast)
				L = NON_UPDATE;
			if (A == Apast)
				A = NON_UPDATE;
			if (w == wpast)
				w = NON_UPDATE;
			if (f0 == f0past)
				f0 = NON_UPDATE;
			if (df0 == df0past)
				df0 = NON_UPDATE;
			if (k == kpast)
				k = NON_UPDATE;
			if (niu == niupast)
				niu = NON_UPDATE;

			control->UpdateModel(idUpd, L, A, w, f0, df0, niu, k, pcol);
			upd = false;
		}
		else {
			id++;
			UpdateData();
			COLORREF col = color.GetColor();

			control->CreateMinf(L, A, w, f0, df0, niu, k, col, id);

			const int size = 100;
			string st = to_string(id);
			const char* stBuf = st.c_str();   // 1. string to const char *

			size_t sz;                          // save converted string's length + 1
			wchar_t output[size] = L"";          // return data, result is CString data

			mbstowcs_s(&sz, output, size, stBuf, size); // converting function

			CString cst = output;
			ModelsItems->AddString((LPCTSTR)cst);
		}
	}
	
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnOK();
}


void ModelSetter::OnCancel()
{
	
	// TODO: добавьте специализированный код или вызов базового класса

	CDialogEx::OnCancel();
}

//устанавливает предыдущие значения для конкретной модели
void ModelSetter::SetValues() {	
	

	control->GetParOfModel(idUpd, L,A, w, f0, df0, niu, k, pcol);

	Lpast = L;
	Apast = A;
	wpast = w;
	f0past = f0;
	df0past = df0;
	niupast = niu;
	kpast = k;
	
	color.SetColor(pcol);
	UpdateData(false);

}
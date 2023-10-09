// ModelSetter.cpp: файл реализации
//

#include "pch.h"
#include "model(task 1).h"
#include "afxdialogex.h"
#include "ModelSetter.h"


// Диалоговое окно ModelSetter

IMPLEMENT_DYNAMIC(ModelSetter, CDialogEx)

ModelSetter::ModelSetter(CWnd* pParent /*=nullptr*/, Controller* con)
	: CDialogEx(IDD_DIALOG4, pParent), control(con)
	, L(0)
	, A(0)
	, w(0)
	, f0(0)
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
	COLORREF col = color.GetAutomaticColor();
	
	control->CreateMinf(L, A, w, f0, df0, niu, k, col);

	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnOK();
}

#pragma once
#include "afxdialogex.h"
#include "Controller.h"



// Диалоговое окно ModelSetter

class ModelSetter : public CDialogEx
{
	DECLARE_DYNAMIC(ModelSetter)

public:
	ModelSetter(CWnd* pParent = nullptr, Controller* con = nullptr);   // стандартный конструктор
	virtual ~ModelSetter();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	Controller* control;
	double L;
	double A;
	double w;
	double f0;
	double df0;
	double niu;
	double k;
	CMFCColorButton color;
	afx_msg void OnBnClickedOk();
};

#pragma once
#include "afxdialogex.h"
#include "Controller.h"
#include <iostream>
#include <string>

using namespace std;



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

	double Lpast;
	double Apast;
	double wpast;
	double f0past;
	double df0past;
	double niupast;
	double kpast;
	COLORREF pcol = NULL;

	int id = 0;
	CListBox* ModelsItems;
	int idUpd;
	void SetValues();
	bool upd = false;
	
	CMFCColorButton color;
	afx_msg void OnBnClickedOk();
	virtual void OnCancel();
};

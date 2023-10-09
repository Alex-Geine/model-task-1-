
// model(task 1)Dlg.h: файл заголовка
//

#pragma once
#include "Drawer.h"
#include "Model.h"
#include "Controller.h"
#include "Phase_D.h"
#include "Portret.h"
#include "ModelsMenu.h"


// Диалоговое окно Cmodeltask1Dlg
class Cmodeltask1Dlg : public CDialogEx
{
// Создание
public:
	Cmodeltask1Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODELTASK_1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	Model mod;
	Drawer MainGraph;
	UINT_PTR timer;
	MSG msg;
	Controller* control;

	Phase_D* phd;
	Portret* por;
	ModelsMenu* menu;

	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit2();
	double L;
	double A;
	double W;
	double f0;
	double df0;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	double niu;
	double k;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};

#pragma once
#include "afxdialogex.h"
#include "ModelSetter.h"
#include "Controller.h"

// Диалоговое окно ModelsMenu

class ModelsMenu : public CDialogEx
{
	DECLARE_DYNAMIC(ModelsMenu)

public:
	ModelsMenu(CWnd* pParent = nullptr, Controller* con = nullptr);   // стандартный конструктор
	virtual ~ModelsMenu();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	ModelSetter* modSet;
	CListBox ModelsItems;
	Controller* control;
	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton6();
	CMFCColorButton colorCheck;
	afx_msg void OnLbnSelchangeList1();
};

// ModelsMenu.cpp: файл реализации
//

#include "pch.h"
#include "model(task 1).h"
#include "afxdialogex.h"
#include "ModelsMenu.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

// Диалоговое окно ModelsMenu

IMPLEMENT_DYNAMIC(ModelsMenu, CDialogEx)

ModelsMenu::ModelsMenu(CWnd* pParent /*=nullptr*/, Controller* con)
	: CDialogEx(IDD_DIALOG3, pParent), control(con)
{
	CWnd* m_Parent;
	m_Parent = GetDesktopWindow();
	modSet = new ModelSetter(m_Parent, control);
	modSet->Create(IDD_DIALOG4, m_Parent);	
	modSet->ModelsItems = &(this->ModelsItems);
}

ModelsMenu::~ModelsMenu()
{
}

void ModelsMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, ModelsItems);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON2, colorCheck);
}


BEGIN_MESSAGE_MAP(ModelsMenu, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ModelsMenu::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ModelsMenu::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &ModelsMenu::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &ModelsMenu::OnBnClickedButton6)
	ON_LBN_SELCHANGE(IDC_LIST1, &ModelsMenu::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// Обработчики сообщений ModelsMenu

//добавить
void ModelsMenu::OnBnClickedButton1()
{
	modSet->ShowWindow(1);				
}

//Удалить
void ModelsMenu::OnBnClickedButton2()
{
	// TODO: добавьте свой код обработчика уведомлений
	int cursel = ModelsItems.GetCurSel();
	if (cursel != LB_ERR) {
		CString stId;
		//получение id удаляемого элемента
		ModelsItems.GetText(cursel, stId);
		int ID = _wtoi_l(stId, 0);
		control->drawId = 0;
		control->DeleteModel(ID);

		ModelsItems.DeleteString(cursel);

	}
}


//Изменить
void ModelsMenu::OnBnClickedButton3()
{
	int cursel = ModelsItems.GetCurSel();
	if (cursel != LB_ERR) {
		CString stId;
		//получение id удаляемого элемента
		ModelsItems.GetText(cursel, stId);
		int ID = _wtoi_l(stId, 0);
		modSet->idUpd = ID;
		modSet->upd = true;
		modSet->SetValues();
		modSet->ShowWindow(1);

	}
}


void ModelsMenu::OnBnClickedButton6()
{
	int cursel = ModelsItems.GetCurSel();
	if (cursel != LB_ERR) {
		CString stId;
		//получение id удаляемого элемента
		ModelsItems.GetText(cursel, stId);
		int ID = _wtoi_l(stId, 0);
		control->drawId = ID;
	}
}

//выбор нового элемента
void ModelsMenu::OnLbnSelchangeList1()
{
	int cursel = ModelsItems.GetCurSel();
	if (cursel != LB_ERR) {
		CString stId;
		//получение id удаляемого элемента
		ModelsItems.GetText(cursel, stId);
		int ID = _wtoi_l(stId, 0);
		double trash;
		COLORREF col = NULL;
		control->GetParOfModel(ID, trash, trash, trash, trash, trash, trash, trash, col);		

		colorCheck.SetColor(col);		
	}
	// TODO: добавьте свой код обработчика уведомлений
}

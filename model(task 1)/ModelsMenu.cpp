// ModelsMenu.cpp: файл реализации
//

#include "pch.h"
#include "model(task 1).h"
#include "afxdialogex.h"
#include "ModelsMenu.h"
#include <iostream>
#include <string>

using namespace std;

// Диалоговое окно ModelsMenu

IMPLEMENT_DYNAMIC(ModelsMenu, CDialogEx)

ModelsMenu::ModelsMenu(CWnd* pParent /*=nullptr*/, Controller* con)
	: CDialogEx(IDD_DIALOG3, pParent), control(con)
{
	CWnd* m_Parent;
	m_Parent = GetDesktopWindow();
	modSet = new ModelSetter(m_Parent);
	modSet->Create(IDD_DIALOG4, m_Parent);
}

ModelsMenu::~ModelsMenu()
{
}

void ModelsMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, ModelsItems);
}


BEGIN_MESSAGE_MAP(ModelsMenu, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ModelsMenu::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ModelsMenu::OnBnClickedButton2)
END_MESSAGE_MAP()


// Обработчики сообщений ModelsMenu

//добавить
void ModelsMenu::OnBnClickedButton1()
{
	id++;
	const int size = 100;
	string st = to_string(id);
	const char* stBuf = st.c_str();   // 1. string to const char *

	size_t sz;                          // save converted string's length + 1
	wchar_t output[size] = L"";          // return data, result is CString data

	mbstowcs_s(&sz, output, size, stBuf, size); // converting function

	CString cst = output;
	ModelsItems.AddString((LPCTSTR)cst);

	modSet->ShowWindow(1);	
}

//Удалить
void ModelsMenu::OnBnClickedButton2()
{
	// TODO: добавьте свой код обработчика уведомлений
	int cursel = ModelsItems.GetCurSel();
	if (cursel != LB_ERR) {
		ModelsItems.DeleteString(cursel);
	}
}

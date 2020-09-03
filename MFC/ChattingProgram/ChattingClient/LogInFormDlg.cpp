// LogInForm.cpp: 구현 파일
//

#include "pch.h"
#include "ChattingClient.h"
#include "LogInFormDlg.h"
#include "afxdialogex.h"
#include "ChattingClientDlg.h"

// LogInForm 대화 상자

IMPLEMENT_DYNAMIC(LogInForm, CDialogEx)

LogInForm::LogInForm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LogInForm, pParent)
{

}

LogInForm::~LogInForm()
{
}

void LogInForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LogInForm, CDialogEx)
	ON_BN_CLICKED(IDC_LOGIN_BTN, &LogInForm::OnBnClickedLoginBtn)
END_MESSAGE_MAP()


// LogInForm 메시지 처리기

void LogInForm::OnBnClickedLoginBtn()
{
	CString id, password;
	GetDlgItemText(IDC_ID_EDIT, id);
	GetDlgItemText(IDC_PW_EDIT, password);

	UserDB User;
	int loginResult = User.Login((const wchar_t*)(LPCTSTR)id, (const wchar_t*)(LPCTSTR)password);

	switch(loginResult){
	case 1: // id && password is correct
	{
		this->ShowWindow(SW_HIDE);
		CChattingClientDlg dlg;
		dlg.DoModal();
		break;
	}
	case -1: // DB connection fail
		MessageBox(NULL, L"DB연결에 실패했습니다.", MB_OK);
		break;
	case -2: // query extraction fail
		MessageBox(NULL, L"query 추출에 실패했습니다.", MB_OK);
		break;
	case -3: // id or password is incorrect
		MessageBox(NULL, L"Id 또는 Password를 잘못 입력했습니다.", MB_OK);
		break;
	}

}

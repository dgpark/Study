// LogInForm.cpp: 구현 파일
//

#include "pch.h"
#include "ChattingClient.h"
#include "LogInForm.h"
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

	if (id == L"test" && password == L"test") {
		this->ShowWindow(SW_HIDE);
		CChattingClientDlg dlg;
		dlg.DoModal();
	}
	else {
		MessageBox(_T("Id 또는 Password를 잘못 입력했습니다."));
	}
}

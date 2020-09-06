// LogInForm.cpp: 구현 파일
//

#include "pch.h"
#include "ChattingClient.h"
#include "RegisterDlg.h"
#include "LogInFormDlg.h"
#include "afxdialogex.h"
#include "ChattingClientDlg.h"
//#include "UserDB.h"

// LogInForm 대화 상자

IMPLEMENT_DYNAMIC(LogInFormDlg, CDialogEx)

LogInFormDlg::LogInFormDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGINFORM_DIALOG, pParent)
{

}

LogInFormDlg::~LogInFormDlg()
{
}

void LogInFormDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LogInFormDlg, CDialogEx)
	ON_BN_CLICKED(IDC_LOGIN_BTN, &LogInFormDlg::OnBnClickedLoginBtn)
	ON_BN_CLICKED(IDC_REGISTER_BTN, &LogInFormDlg::OnBnClickedRegisterBtn)
END_MESSAGE_MAP()


// LogInForm 메시지 처리기

void LogInFormDlg::OnBnClickedLoginBtn()
{
	CString id, password;
	GetDlgItemText(IDC_ID_EDIT, id);
	GetDlgItemText(IDC_PW_EDIT, password);

	UserDB User;
	if (!User.Connect()) {
		MessageBox(NULL, L"DB연결에 실패했습니다.", MB_OK);
	}
	else {
		if (User.Login(m_hWnd, (const wchar_t*)(LPCTSTR)id, (const wchar_t*)(LPCTSTR)password)) {
			CChattingClientDlg dlg;
			dlg.DoModal();
		}
	} // end of Connect
}


void LogInFormDlg::OnBnClickedRegisterBtn()
{
	RegisterDlg dlg;
	dlg.DoModal();
}

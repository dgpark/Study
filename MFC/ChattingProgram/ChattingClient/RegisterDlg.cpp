// RegisterDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ChattingClient.h"
#include "RegisterDlg.h"
#include "LogInFormDlg.h"
#include "afxdialogex.h"


// RegisterDlg 대화 상자

IMPLEMENT_DYNAMIC(RegisterDlg, CDialogEx)

RegisterDlg::RegisterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGISTER_DIALOG, pParent)
{

}

RegisterDlg::~RegisterDlg()
{

}

void RegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RegisterDlg, CDialogEx)
	ON_BN_CLICKED(IDREGISTER, &RegisterDlg::OnBnClickedRegister)
	ON_BN_CLICKED(IDC_ID_DU_CHECK_BUTTON, &RegisterDlg::OnBnClickedIdDuCheckButton)
END_MESSAGE_MAP()


// RegisterDlg 메시지 처리기


void RegisterDlg::OnBnClickedRegister()
{
	CString id, password, pf_name;
	GetDlgItemText(IDC_ID_EDIT, id);
	GetDlgItemText(IDC_PW_EDIT, password);
	GetDlgItemText(IDC_PW_EDIT, pf_name);

	UserDB User;

	if (id.GetLength() != 0 && password.GetLength() != 0 && pf_name.GetLength() != 0) { // id, password, 프로필이름 규칙 만족하는 경우. (나중에 함수로 변경)
		if (!User.Connect()) {
			MessageBox(NULL, L"DB연결에 실패했습니다.", MB_OK);
		}
		else {
			if (User.Register(m_hWnd, id, password, pf_name)) {
				LogInFormDlg dlg;
				dlg.DoModal();
			}
		}
	}
	else { // 나중에 함수안에서 예외처리
		MessageBox(NULL, L"아이디, 비밀번호, 프로필이름을 바르게 입력하세요.", MB_OK);
	}

	
}


void RegisterDlg::OnBnClickedIdDuCheckButton()
{
	CString id;
	GetDlgItemText(IDC_ID_EDIT, id);

	UserDB User;
	if (!User.Connect()) {
		MessageBox(NULL, L"DB연결에 실패했습니다.", MB_OK);
	}
	else {
		User.IdDuCheck(m_hWnd,(const wchar_t*)(LPCTSTR)id);
	}

}

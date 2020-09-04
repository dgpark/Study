// RegisterDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ChattingClient.h"
#include "RegisterDlg.h"
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
	CString id, password, pfName;
	GetDlgItemText(IDC_ID_EDIT, id);
	GetDlgItemText(IDC_PW_EDIT, password);
	GetDlgItemText(IDC_PW_EDIT, pfName);


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
		bool DuplicateCheck = User.IdCheck((const wchar_t*)(LPCTSTR)id);
		switch (DuplicateCheck) {
		case 0: // 사용가능
			MessageBox(NULL, L"id를 사용하여도 좋습니다.", MB_OK);
			break;
		case 1:
			MessageBox(NULL, L"중복된 id입니다.", MB_OK);
			break;
		case -1: // query extraction fail
			MessageBox(NULL, L"query 추출에 실패했습니다.", MB_OK);
			break;
		}
	}

}

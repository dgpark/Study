// LogInForm.cpp: 구현 파일
//

#include "pch.h"
#include "ChattingClient.h"
#include "LogInForm.h"
#include "afxdialogex.h"
#include "ChattingClientDlg.h"
#include <mysql.h>

#pragma comment(lib, "libmySQL.lib")


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

/*
CStringW ConvertUTF8ToUnicode(const CStringA& utf8)
{
	if (utf8.IsEmpty()) return L""; // nothing to do
	CStringW uni;
	int cc = 0;
	// get length (cc) of the new widechar excluding the \0 terminator first
	if ((cc = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0) - 1) > 0)
	{
		// convert
		wchar_t* buf = uni.GetBuffer(cc);
		if (buf) MultiByteToWideChar(CP_UTF8, 0, utf8, -1, buf, cc);
		uni.ReleaseBuffer();
	}
	return uni;
}
*/

void LogInForm::OnBnClickedLoginBtn()
{
	CString id, password;
	GetDlgItemText(IDC_ID_EDIT, id);
	GetDlgItemText(IDC_PW_EDIT, password);

	MYSQL* connection = nullptr, mysql;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int query_stat;

	mysql_init(&mysql);
	connection = mysql_real_connect(&mysql, "localhost", "root", "test", "chattingaccount", 3306, NULL, 0);

	if (connection == NULL) {
		MessageBox(_T("DB연결에 실패했습니다."));
	}
	else {
		char* query = "SELECT * FROM user";
		query_stat = mysql_query(connection, query);

		if (query_stat != 0) {
			MessageBox(_T("query 추출에 실패했습니다."));
		}
		else {
			sql_result = mysql_store_result(connection);
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				CString msg;
				//msg.Format((L"%s"), ConvertUTF8ToUnicode(sql_row[0]));
				msg.Format((L"id : %S, password : %S, profile name : %S"),sql_row[0], sql_row[1], sql_row[2]); // %s shows chinese characters. Use %S to show utf8 to unicode encoding.

				MessageBox(NULL, msg, MB_OK);
			}

		}
	}


	if (id == L"test" && password == L"test") {
		this->ShowWindow(SW_HIDE);
		CChattingClientDlg dlg;
		dlg.DoModal();
	}
	else {
		MessageBox(_T("Id 또는 Password를 잘못 입력했습니다."));
	}

}

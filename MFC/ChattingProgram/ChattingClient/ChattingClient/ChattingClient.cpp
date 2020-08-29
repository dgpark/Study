
// ChattingClient.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "ChattingClient.h"
#include "ChattingClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChattingClientApp

BEGIN_MESSAGE_MAP(CChattingClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CChattingClientApp 생성

CChattingClientApp::CChattingClientApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CChattingClientApp 개체입니다.

CChattingClientApp theApp;


// CChattingClientApp 초기화

BOOL CChattingClientApp::InitInstance()
{
	CWinApp::InitInstance();

	CChattingClientDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}


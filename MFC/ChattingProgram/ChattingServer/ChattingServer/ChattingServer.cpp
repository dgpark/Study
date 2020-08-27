
// ChattingServer.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "ChattingServer.h"
#include "ChattingServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChattingServerApp

BEGIN_MESSAGE_MAP(CChattingServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CChattingServerApp 생성

CChattingServerApp::CChattingServerApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CChattingServerApp 개체입니다.

CChattingServerApp theApp;


// CChattingServerApp 초기화

BOOL CChattingServerApp::InitInstance()
{
	CWinApp::InitInstance();

	CChattingServerDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}


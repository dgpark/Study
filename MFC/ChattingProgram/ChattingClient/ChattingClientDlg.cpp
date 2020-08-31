
// ChattingClientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ChattingClient.h"
#include "ChattingClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChattingClientDlg 대화 상자

int MyClient::ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char* ap_recv_data, BS a_body_size)
{
	if (a_msg_id == NM_CHAT_DATA) {
		mp_parent->AddEventString((wchar_t*)ap_recv_data);
	}
	return 1;
}

CChattingClientDlg::CChattingClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATTINGCLIENT_DIALOG, pParent), m_client(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChattingClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENT_LIST, m_event_list);
}

BEGIN_MESSAGE_MAP(CChattingClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND_BTN, &CChattingClientDlg::OnBnClickedSendBtn)
	ON_MESSAGE(26001, &CChattingClientDlg::OnConnected)
	ON_MESSAGE(26002, &CChattingClientDlg::OnReadAndClose)
END_MESSAGE_MAP()


// CChattingClientDlg 메시지 처리기

BOOL CChattingClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	m_client.ConnectToServer(/*L"192.168.43.113"*/L"127.0.0.1", 27100, m_hWnd);
	//AddEventString(L"클라이언트 서비스를 시작합니다.");
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CChattingClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CChattingClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChattingClientDlg::OnBnClickedSendBtn()
{
	CString str;
	GetDlgItemText(IDC_CHAT_EDIT, str);
	SetDlgItemText(IDC_CHAT_EDIT, L"");

	if (m_client.IsConnected()) {
		m_client.SendFrameData(NM_CHAT_DATA, (char*)(const wchar_t*)str, (str.GetLength() + 1) * 2);
	}
}

void CChattingClientDlg::AddEventString(const wchar_t* ap_string) 
{
	int index = m_event_list.InsertString(-1, ap_string);
	m_event_list.SetCurSel(index);
}


afx_msg LRESULT CChattingClientDlg::OnConnected(WPARAM wParam, LPARAM lParam)
{
	if (m_client.ResultOfConnection(lParam) == 1) {
		AddEventString(L"서버에 접속했습니다!");
	}
	else {
		AddEventString(L"서버에 접속할수 없습니다!");
	}
	
	return 0;
}


afx_msg LRESULT CChattingClientDlg::OnReadAndClose(WPARAM wParam, LPARAM lParam)
{
	// 접속한 서버에서 데이터를 전송하거나 접속을 해제할 떄 발생하는 메시지를 처리한다.
	m_client.ProcessServerEvent(wParam, lParam); // FD_READ, FD_CLOSE
	return 0;
}

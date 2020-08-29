
// ChattingClientDlg.h: 헤더 파일
//

#pragma once

#define NM_CHAT_DATA	1

class CChattingClientDlg;

class MyClient : public ClientSocket
{
private:
	CChattingClientDlg* mp_parent;
	
public:
	MyClient(CChattingClientDlg* ap_parent) : ClientSocket(0x27)
	{
		mp_parent = ap_parent;
	}

	virtual int ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char* ap_recv_data, BS a_body_size);
};

// CChattingClientDlg 대화 상자
class CChattingClientDlg : public CDialogEx
{
private:
	MyClient m_client;

// 생성입니다.
public:
	CChattingClientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	void AddEventString(const wchar_t* ap_string);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATTINGCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_event_list;
	afx_msg void OnBnClickedSendBtn();
protected:
	afx_msg LRESULT OnConnected(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReadAndClose(WPARAM wParam, LPARAM lParam);
};

#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#define LM_SEND_COMPLETED      29001
#define LM_RECV_COMPLETED      29002

typedef unsigned short int BS;
#define HEAD_SIZE	2+sizeof(BS)

//전송과 수신에 공통적으로 작업할 내용을 구현한 클래스
class ExchangeManager {
protected:
	// 전송 or 수신을 위해 할당된 메모리의 전체 크기와 현재 작업중인 크기
	int m_total_size, m_cur_size;
	// 전송 or 수신을 위해 할당된 메모리의 시작 주소
	char* mp_data;

public:
	ExchangeManager(); // 생성자 선언
	~ExchangeManager(); // 소멸자 선언

	// 전송 or 수신에 사용할 메모리를 할당
	// a_data_size에 할당할 크기를 명시하면 함수의 반환값으로
	// 할당된 메모리의 주소를 반환. (반환된 주소는 이 클래스가 관리)
	char* MemoryAlloc(int a_data_size);
	// 전송 또는 수신에 사용되던 메모리 제거
	void DeleteData();

	inline int GetTotalSize() { return m_total_size; }
	inline int GetCurSize() { return m_cur_size; }
};

class SendManager : public ExchangeManager
{
public:
	// 현재 전송할 위치와 크기를 계산
	int GetPosition(char** ap_data, int a_data_size = 2048);
	// 전송이 완료되었는지 체크
	inline char IsProcessing() { return m_total_size != m_cur_size; }
};

class RecvManager : public ExchangeManager {
public:
	// 수신된 데이터를 기존 수신된 데이터에 추가한다.
	int AddData(char* ap_data, int a_size);
	// 수신된 데이터를 하나로 합친 메모리의 시작 주소를 얻는다.
	inline char* GetData() { return mp_data; }
};

class Socket {
protected:
	// 프로토콜의 유효성을 체크하기 위한 구분 값을 저장할 변수
	unsigned char m_valid_key;
	char* mp_send_data, * mp_recv_data; // 전송과 수신에 사용할 버퍼
	// 데이터가 수신되거나 상대편이 접속을 해제했을 때 메시지를 수신할 윈도우 핸들 값
	HWND mh_notify_wnd;
	// 데이터가 수신되거나 상대편이 접속을 해제했을 때 사용할 메시지 ID
	int m_data_notify_id;
public:
	// 객체 생성시에 프로토콜 구분 값과 데이터 수신 및 연결 해제에 사용할 메시지 ID를 지정해야 함.
	Socket() {};
	Socket(unsigned char a_valid_key, int a_data_notify_id);
	~Socket();

	// 연결된 대상에게 네트워크로 데이터를 전송할 때 사용할 함수
	// 이 함수는 전달된 정보를 가지고 하나의 메모리에 약속된 Head 정보를 구성해서 전송.
	int SendFrameData(SOCKET ah_socket, unsigned char a_message_id, const char* ap_body_data, BS a_body_size);
	// 재시도 수신을 지원하는 함수
	int ReceiveData(SOCKET ah_socket, BS a_body_size);
	// 데이터가 수신되었을때 수신된 데이터를 처리하는 함수
	void ProcessRecvEvent(SOCKET ah_socket);
	
	// 접속된 대상을 끊을때 사용하는 함수 (자식 클래스에서 꼭 재정의해서 사용해야 함)
	virtual void DisconnectSocket(SOCKET ah_socket, int a_error_code);
	// 수신된 데이터를 처리하는 함수
	virtual int ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char* ap_recv_data, BS a_body_size);
	
	// ASCII 형식의 문자열을 유니코드로 변환
	static void AsciiToUnicode(wchar_t* ap_dest_ip, char* ap_src_ip);
	// 유니코드 형식의 문자열을 ASCII로 변환
	static void UnicodeToAscii(char* ap_dest_ip, wchar_t* ap_src_ip);
};

class UserData {
protected:
	// 클라이언트와 통신하기 위해 사용할 소켓 핸들
	SOCKET mh_socket;
	// 클라이언트에게서 큰 데이터를 전송하기 위해 사용할 객체
	SendManager* mp_send_man;
	// 클라이언트에게서 큰 데이터를 수신하기 위해 사용할 객체
	RecvManager* mp_recv_man;
	// 클라이언트의 IP 주소
	wchar_t m_ip_address[16];
public:
	UserData();
	virtual ~UserData();

	inline SOCKET GetHandle() { return mh_socket; }
	inline void SetHandle(SOCKET ah_socket) { mh_socket = ah_socket; }
	inline SendManager *GetSendMan() { return mp_send_man; }
	inline RecvManager *GetRecvMan() { return mp_recv_man; }

	wchar_t* GetIP();
	void SetIP(const wchar_t* ap_ip_address);
	void CloseSocket(char a_linger_flag);

	virtual UserData *CreateObject() { return new UserData; }
};

/* //추후 로그인 기능 구현
class UserAccount : public UserData {
protected:
	wchar_t id[32];
	wchar_t password[32];
public:
	wchar_t *GetID();
	wchar_t *GetPassword();
	void SetID(const wchar_t* ap_id);
	void SetPassword(const wchar_t* ap_password);

	virtual UserData* createObject() { return new UserAccount; }
};
*/

class ServerSocket : public Socket {
protected:
	// listen 작업에 사용할 소켓 핸들
	SOCKET mh_listen_socket;
	// 새로운 클라이언트가 접속했을 때 발생할 메시지 ID 값
	int m_accept_notify_id;
	// 서버가 관리할 최대 사용자 수
	unsigned short int m_max_user_count;
	// 최대 사용자를 저장하기 위해서 사용할 객체들
	UserData** mp_user_list;
public:
	ServerSocket(unsigned char a_valid_key, unsigned short int a_max_user_count, UserData* ap_user_data,
		int a_accept_notify_id = 25001, int a_data_notify_id = 25002);
	virtual ~ServerSocket();

	// 서버 서비스를 시작한다. 반환값이 1이면 성공. -1이면 소켓 생성 실패, -2이면 생성된 소켓을 바인드하는데 실패
	int StartServer(const wchar_t* ap_ip_address, int a_port, HWND ah_notify_wnd);
	// 새로운 클라이언트가 접속할때 사용할 함수 - FD_ACCEPT와 연결된 메시지가 발생했을때 사용하면 된다.
	// 반환값 1 : 성공, -1 : accept 실패, -2 : 접속 가능한 최대 사용자수 초과
	int ProcessToAccept(WPARAM wParam, LPARAM lParam);
	// Accept 시에 추가적으로 해야할 작업이 있다면 이 함수를 오버라이딩해서 처리해야함
	virtual void AddWorkForAccept(UserData* ap_user) { }
	
	// 최대 사용자수 초과시에 추가적으로 해야할 작업이 있다면 이 함수를 오버라이딩해서 처리해야함
	virtual void ShowLimitError(const wchar_t* ap_ip_address) { }

	void ProcessClientEvent(WPARAM wParam, LPARAM lParam);

	// 소켓 핸들을 사용하여 어떤 사용자인지 찾는다. 찾으면 사용자의 위치를 반환한다.
	inline int FindUserIndex(SOCKET ah_socket)
	{
		for (int i = 0; i < m_max_user_count; i++) if (mp_user_list[i]->GetHandle() == ah_socket) return i;
		return -1;
	}
	// 소켓 핸들을 사용하여 어떤 사용자인지 찾는다. 찾으면 사용자 정보를 관리하는 객체의 주소를 반환한다.
	inline UserData* FindUserData(SOCKET ah_socket)
	{
		for (int i = 0; i < m_max_user_count; i++) if (mp_user_list[i]->GetHandle() == ah_socket) return mp_user_list[i];
		return NULL;
	}
	// 클라이언트가 접속해제시에 추가적으로 해야할 작업이 있다면 이 함수를 오버라이딩해서 처리해야함
	// a_error_code : 0이면 정상종료, -1이면 키값이 유효한지 않아서 종료, -2이면 바디정보 수신중에 오류 발생
	virtual void AddWorkForCloseUser(UserData* ap_user, int a_error_code) {};
	// ah_socket 핸들 값을 사용하는 소켓 사용자를 강제로 종료 시킨다.
	virtual void DisconnectSocket(int ah_socket, int a_error_code);
	// FD_READ 이벤트가 발생했을때 실제 데이터를 처리하는 함수 
	// (서버 소켓을 상속 받은 클래스에서 반드시 재정의하여 자신이 정의한 메시지를 처리해야 한다.)
	virtual int ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char* ap_recv_data, BS a_body_size);

	// 전체 사용자에 대한 정보를 얻는 경우
	inline UserData** GetUserList() { return mp_user_list; }

	// 색인을 사용하여 특정 사용자에 대한 정보를 얻는 경우
	inline UserData* GetUserData(int a_index) { return mp_user_list[a_index]; }

	// 최대 사용자 수를 얻는 경우
	unsigned short int GetMaxUserCount() { return m_max_user_count; }
};

class ClientSocket : public Socket
{
protected:
	// 서버와 통신하기 위해 사용할 소켓 핸들
	SOCKET mh_socket;
	// 0: 접속 안됨, 1: 접속 시도중, 2: 접속 중
	char m_connect_flag;
	// 서버에 접속을 시도한 결과를 알려줄 윈도우 메시지를 저장한다.
	int m_connect_notify_id;
	// 서버에 큰 데이터를 전송하기 위해 사용할 객체
	SendManager m_send_man;
	// 서버에 큰 데이터를 수신하기 위해 사용할 객체
	RecvManager m_recv_man;

public:
	ClientSocket(unsigned char a_valid_key, int a_connect_notify_id = 26001, int a_data_notify_id = 26002);
	virtual ~ClientSocket();

	inline SendManager* GetSendMan() { return &m_send_man; }  // 전송용 객체의 주소를 얻는다.
	inline RecvManager* GetRecvMan() { return &m_recv_man; }  // 수신용 객체의 주소를 얻는다.

	// 서버에 접속을 시도한다.
	int ConnectToServer(const wchar_t* ap_ip_address, int a_port_num, HWND ah_notify_wnd);
	// 서버 접속에 대한 결과가 메시지로 전달되었을때 이 함수를 사용
	// 반환값이 1 : 서버에 접속 성공, 0 : 서버에 접속 실패
	int ResultOfConnection(LPARAM lParam);
	// 서버가 데이터를 전송하거나 연결을 해제했을때 발생하는 윈도우 메시지에서 이 함수를 사용하면 됩니다.
	// 반환값이 0 이면 서버가 접속을 해제, 1이면 서버에서 데이터를 수신
	int ProcessServerEvent(WPARAM wParam, LPARAM lParam);
	// 서버와 강제로 접속을 해제할 때 사용.
	virtual void DisconnectSocket(SOCKET ah_socket, int a_error_code);
	// 서버로 데이터를 전송할 때 사용합니다. 메시지 ID와 전송할 데이터의 주소, 데이터의 크기를 넘겨주면
	// 약속된 프로토콜 형식으로 구성해서 전송.
	int SendFrameData(unsigned char a_message_id, const char* ap_body_data, BS a_body_size);
	// FD_READ 이벤트가 발생했을때 실제 데이터를 처리하는 함수 
	// (서버 소켓을 상속 받은 클래스에서 반드시 재정의하여 자신이 정의한 메시지를 처리해야 한다.)
	virtual int ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char* ap_recv_data, BS a_body_size);

	// 서버와의 접속상태를 알고 싶을때 사용. 0 : 해제상태, 1 : 접속상태
	// 내부적으로는 상태를 세가지로 관리하지만 외부에 알려줄때는 두가지 상태로 알려준다.
	// '접속 시도중' 상태는 해제로 간주.
	inline int IsConnected() { return m_connect_flag == 2; }
	// 서버와 통신하기 위해 생성한 소켓의 핸들 값을 알고 싶을 때 사용한다.
	inline SOCKET GetHandle() { return mh_socket; }
};


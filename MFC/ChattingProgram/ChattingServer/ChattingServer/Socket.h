#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#define LM_SEND_COMPLETED      29001
#define LM_RECV_COMPLETED      29002

typedef unsigned short int BS;
#define HEAD_SIZE	2+sizeof(BS)

//���۰� ���ſ� ���������� �۾��� ������ ������ Ŭ����
class ExchangeManager {
protected:
	// ���� or ������ ���� �Ҵ�� �޸��� ��ü ũ��� ���� �۾����� ũ��
	int m_total_size, m_cur_size;
	// ���� or ������ ���� �Ҵ�� �޸��� ���� �ּ�
	char* mp_data;

public:
	ExchangeManager(); // ������ ����
	~ExchangeManager(); // �Ҹ��� ����

	// ���� or ���ſ� ����� �޸𸮸� �Ҵ�
	// a_data_size�� �Ҵ��� ũ�⸦ ����ϸ� �Լ��� ��ȯ������
	// �Ҵ�� �޸��� �ּҸ� ��ȯ. (��ȯ�� �ּҴ� �� Ŭ������ ����)
	char* MemoryAlloc(int a_data_size);
	// ���� �Ǵ� ���ſ� ���Ǵ� �޸� ����
	void DeleteData();

	inline int GetTotalSize() { return m_total_size; }
	inline int GetCurSize() { return m_cur_size; }
};

class SendManager : public ExchangeManager
{
public:
	// ���� ������ ��ġ�� ũ�⸦ ���
	int GetPosition(char** ap_data, int a_data_size = 2048);
	// ������ �Ϸ�Ǿ����� üũ
	inline char IsProcessing() { return m_total_size != m_cur_size; }
};

class RecvManager : public ExchangeManager {
public:
	// ���ŵ� �����͸� ���� ���ŵ� �����Ϳ� �߰��Ѵ�.
	int AddData(char* ap_data, int a_size);
	// ���ŵ� �����͸� �ϳ��� ��ģ �޸��� ���� �ּҸ� ��´�.
	inline char* GetData() { return mp_data; }
};

class Socket {
protected:
	// ���������� ��ȿ���� üũ�ϱ� ���� ���� ���� ������ ����
	unsigned char m_valid_key;
	char* mp_send_data, * mp_recv_data; // ���۰� ���ſ� ����� ����
	// �����Ͱ� ���ŵǰų� ������� ������ �������� �� �޽����� ������ ������ �ڵ� ��
	HWND mh_notify_wnd;
	// �����Ͱ� ���ŵǰų� ������� ������ �������� �� ����� �޽��� ID
	int m_data_notify_id;
public:
	// ��ü �����ÿ� �������� ���� ���� ������ ���� �� ���� ������ ����� �޽��� ID�� �����ؾ� ��.
	Socket();
	Socket(unsigned char a_valid_key, int a_data_notify_id);
	~Socket();

	// ����� ��󿡰� ��Ʈ��ũ�� �����͸� ������ �� ����� �Լ�
	// �� �Լ��� ���޵� ������ ������ �ϳ��� �޸𸮿� ��ӵ� Head ������ �����ؼ� ����.
	int SendFrameData(SOCKET ah_socket, unsigned char a_message_id, const char* ap_body_data, BS a_body_size);
	// ��õ� ������ �����ϴ� �Լ�
	int ReceiveData(SOCKET ah_socket, BS a_body_size);
	// �����Ͱ� ���ŵǾ����� ���ŵ� �����͸� ó���ϴ� �Լ�
	void ProcessRecvEvent(SOCKET ah_socket);
	
	// ���ӵ� ����� ������ ����ϴ� �Լ� (�ڽ� Ŭ�������� �� �������ؼ� ����ؾ� ��)
	virtual void DisconnectSocket(SOCKET ah_socket, int a_error_code);
	// ���ŵ� �����͸� ó���ϴ� �Լ�
	virtual int ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char* ap_recv_data, BS a_body_size);
	
	// ASCII ������ ���ڿ��� �����ڵ�� ��ȯ
	static void AsciiToUnicode(wchar_t* ap_dest_ip, char* ap_src_ip);
	// �����ڵ� ������ ���ڿ��� ASCII�� ��ȯ
	static void UnicodeToAscii(char* ap_dest_ip, wchar_t* ap_src_ip);
};

class UserData {
protected:
	// Ŭ���̾�Ʈ�� ����ϱ� ���� ����� ���� �ڵ�
	SOCKET mh_socket;
	// Ŭ���̾�Ʈ���Լ� ū �����͸� �����ϱ� ���� ����� ��ü
	SendManager* mp_send_man;
	// Ŭ���̾�Ʈ���Լ� ū �����͸� �����ϱ� ���� ����� ��ü
	RecvManager* mp_recv_man;
	// Ŭ���̾�Ʈ�� IP �ּ�
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

/* //���� �α��� ��� ����
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
	// listen �۾��� ����� ���� �ڵ�
	SOCKET mh_listen_socket;
	// ���ο� Ŭ���̾�Ʈ�� �������� �� �߻��� �޽��� ID ��
	int m_accept_notify_id;
	// ������ ������ �ִ� ����� ��
	unsigned short int m_max_user_count;
	// �ִ� ����ڸ� �����ϱ� ���ؼ� ����� ��ü��
	UserData** mp_user_list;
public:
	ServerSocket(unsigned char a_valid_key, unsigned short int a_max_user_count, UserData* ap_user_data,
		int a_accept_notify_id = 25001, int a_data_notify_id = 25002);
	virtual ~ServerSocket();

	// ���� ���񽺸� �����Ѵ�. ��ȯ���� 1�̸� ����. -1�̸� ���� ���� ����, -2�̸� ������ ������ ���ε��ϴµ� ����
	int StartServer(const wchar_t* ap_ip_address, int a_port, HWND ah_notify_wnd);
	// ���ο� Ŭ���̾�Ʈ�� �����Ҷ� ����� �Լ� - FD_ACCEPT�� ����� �޽����� �߻������� ����ϸ� �ȴ�.
	// ��ȯ�� 1 : ����, -1 : accept ����, -2 : ���� ������ �ִ� ����ڼ� �ʰ�
	int ProcessToAccept(WPARAM wParam, LPARAM lParam);
	// Accept �ÿ� �߰������� �ؾ��� �۾��� �ִٸ� �� �Լ��� �������̵��ؼ� ó���ؾ���
	virtual void AddWorkForAccept(UserData* ap_user) { }
	
	// �ִ� ����ڼ� �ʰ��ÿ� �߰������� �ؾ��� �۾��� �ִٸ� �� �Լ��� �������̵��ؼ� ó���ؾ���
	virtual void ShowLimitError(const wchar_t* ap_ip_address) { }

	void ProcessClientEvent(WPARAM wParam, LPARAM lParam);

	// ���� �ڵ��� ����Ͽ� � ��������� ã�´�. ã���� ������� ��ġ�� ��ȯ�Ѵ�.
	inline int FindUserIndex(SOCKET ah_socket)
	{
		for (int i = 0; i < m_max_user_count; i++) if (mp_user_list[i]->GetHandle() == ah_socket) return i;
		return -1;
	}
	// ���� �ڵ��� ����Ͽ� � ��������� ã�´�. ã���� ����� ������ �����ϴ� ��ü�� �ּҸ� ��ȯ�Ѵ�.
	inline UserData* FindUserData(SOCKET ah_socket)
	{
		for (int i = 0; i < m_max_user_count; i++) if (mp_user_list[i]->GetHandle() == ah_socket) return mp_user_list[i];
		return NULL;
	}
	// Ŭ���̾�Ʈ�� ���������ÿ� �߰������� �ؾ��� �۾��� �ִٸ� �� �Լ��� �������̵��ؼ� ó���ؾ���
	// a_error_code : 0�̸� ��������, -1�̸� Ű���� ��ȿ���� �ʾƼ� ����, -2�̸� �ٵ����� �����߿� ���� �߻�
	virtual void AddWorkForCloseUser(UserData* ap_user, int a_error_code) {};
	// ah_socket �ڵ� ���� ����ϴ� ���� ����ڸ� ������ ���� ��Ų��.
	virtual void DisconnectSocket(int ah_socket, int a_error_code);
	// FD_READ �̺�Ʈ�� �߻������� ���� �����͸� ó���ϴ� �Լ� 
	// (���� ������ ��� ���� Ŭ�������� �ݵ�� �������Ͽ� �ڽ��� ������ �޽����� ó���ؾ� �Ѵ�.)
	virtual int ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char* ap_recv_data, BS a_body_size);

	// ��ü ����ڿ� ���� ������ ��� ���
	inline UserData** GetUserList() { return mp_user_list; }

	// ������ ����Ͽ� Ư�� ����ڿ� ���� ������ ��� ���
	inline UserData* GetUserData(int a_index) { return mp_user_list[a_index]; }

	// �ִ� ����� ���� ��� ���
	unsigned short int GetMaxUserCount() { return m_max_user_count; }
};

class ClientSocket : public Socket
{
protected:
	// ������ ����ϱ� ���� ����� ���� �ڵ�
	SOCKET mh_socket;
	// 0: ���� �ȵ�, 1: ���� �õ���, 2: ���� ��
	char m_connect_flag;
	// ������ ������ �õ��� ����� �˷��� ������ �޽����� �����Ѵ�.
	int m_connect_notify_id;
	// ������ ū �����͸� �����ϱ� ���� ����� ��ü
	SendManager m_send_man;
	// ������ ū �����͸� �����ϱ� ���� ����� ��ü
	RecvManager m_recv_man;

public:
	ClientSocket(unsigned char a_valid_key, int a_connect_notify_id = 26001, int a_data_notify_id = 26002);
	virtual ~ClientSocket();

	inline SendManager* GetSendMan() { return &m_send_man; }  // ���ۿ� ��ü�� �ּҸ� ��´�.
	inline RecvManager* GetRecvMan() { return &m_recv_man; }  // ���ſ� ��ü�� �ּҸ� ��´�.

	// ������ ������ �õ��Ѵ�.
	int ConnectToServer(const wchar_t* ap_ip_address, int a_port_num, HWND ah_notify_wnd);
	// ���� ���ӿ� ���� ����� �޽����� ���޵Ǿ����� �� �Լ��� ���
	// ��ȯ���� 1 : ������ ���� ����, 0 : ������ ���� ����
	int ResultOfConnection(LPARAM lParam);
	// ������ �����͸� �����ϰų� ������ ���������� �߻��ϴ� ������ �޽������� �� �Լ��� ����ϸ� �˴ϴ�.
	// ��ȯ���� 0 �̸� ������ ������ ����, 1�̸� �������� �����͸� ����
	int ProcessServerEvent(WPARAM wParam, LPARAM lParam);
	// ������ ������ ������ ������ �� ���.
	virtual void DisconnectSocket(SOCKET ah_socket, int a_error_code);
	// ������ �����͸� ������ �� ����մϴ�. �޽��� ID�� ������ �������� �ּ�, �������� ũ�⸦ �Ѱ��ָ�
	// ��ӵ� �������� �������� �����ؼ� ����.
	int SendFrameData(unsigned char a_message_id, const char* ap_body_data, BS a_body_size);
	// FD_READ �̺�Ʈ�� �߻������� ���� �����͸� ó���ϴ� �Լ� 
	// (���� ������ ��� ���� Ŭ�������� �ݵ�� �������Ͽ� �ڽ��� ������ �޽����� ó���ؾ� �Ѵ�.)
	virtual int ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char* ap_recv_data, BS a_body_size);

	// �������� ���ӻ��¸� �˰� ������ ���. 0 : ��������, 1 : ���ӻ���
	// ���������δ� ���¸� �������� ���������� �ܺο� �˷��ٶ��� �ΰ��� ���·� �˷��ش�.
	// '���� �õ���' ���´� ������ ����.
	inline int IsConnected() { return m_connect_flag == 2; }
	// ������ ����ϱ� ���� ������ ������ �ڵ� ���� �˰� ���� �� ����Ѵ�.
	inline SOCKET GetHandle() { return mh_socket; }
};


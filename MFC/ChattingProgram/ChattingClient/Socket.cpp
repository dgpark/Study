#include "Socket.h"


ExchangeManager::ExchangeManager() {
	mp_data = nullptr;
	m_total_size = 0;
	m_cur_size = 0;
}

ExchangeManager::~ExchangeManager() {
	DeleteData();
}

char* ExchangeManager::MemoryAlloc(int a_data_size) {
	// ������ ����ϴ� �޸𸮿� ���� �ʿ��� �޸� ũ�Ⱑ �����ϸ� �ٽ� �޸� �Ҵ��� �ʿ�x
	// (������ ũ���� �����͸� ���������� �����ϰų� �����ϴ� ��찡 ����.)
	if (m_total_size != a_data_size) {
		if (mp_data != nullptr) delete[] mp_data;
		// ������ ũ��� �޸𸮸� �Ҵ��Ѵ�.
		mp_data = new char[a_data_size];
		// �Ҵ�� ũ�⸦ ����Ѵ�.
		m_total_size = a_data_size;
	}
	// �۾� ��ġ�� ���� ù ��ġ�� �ʱ�ȭ�Ѵ�.
	m_cur_size = 0;
	// �Ҵ�� �޸��� ���� ��ġ�� ��ȯ�Ѵ�.
	return mp_data;
}

void ExchangeManager::DeleteData()
{
	if (mp_data != nullptr) {
		//�Ҵ�� �޸𸮸� �����ϰ� �۾��� ���õ� �������� �ʱ�ȭ
		delete[] mp_data;
		mp_data = nullptr;
		m_total_size = 0;
	}
}

int SendManager::GetPosition(char** ap_data, int a_data_size) {
	// ���ο� ���� ��ġ�� ���� �ּҸ� ù��° ���ڿ� ����
	*ap_data = mp_data + m_cur_size;

	// ���� ũ�⸦ ����ϱ� ���ؼ� 2048bytes�� ���� ũ�Ⱑ �ִ� ũ�⺸�� ������ üũ�Ѵ�.
	if (m_cur_size + a_data_size < m_total_size) {
		// �ִ� ũ�⺸�� ���� ��� 2048bytes ��ŭ �����ϸ� �ȴ�.
		// ���� ��ġ�� ����� �� �ֵ��� ������ �� ũ�⸦ ���Ѵ�.
		m_cur_size += a_data_size;
	}
	else {
		// 2048bytes ���� ���� ���, ������ ���� ũ�⸸ �����Ѵ�.
		a_data_size = m_total_size - m_cur_size;
		// ���� ��ġ�� ������ ��ġ�� �ű��.(������ ����)
		m_cur_size = m_total_size;
	}
	//���� ����ũ�⸦ ��ȯ
	return a_data_size;
}

int RecvManager::AddData(char* ap_data, int a_size) {
	// ���ŵ� �����͸� ���� ���� ������ �ڿ� �߰��Ѵ�.
	memcpy(mp_data + m_cur_size, ap_data, a_size);
	// �� ���� ũ�⸦ ���
	m_cur_size += a_size;
	// ���� ���ŵ� �������� ũ�⸦ ��ȯ
	return m_cur_size;
}

Socket::Socket(unsigned char a_valid_key, int a_data_notify_id) {
	// ����ڰ� ������ �������� ���� ���� �����Ѵ�.
	m_valid_key = a_valid_key;
	// ���ۿ����� ����� 8 Kbytes �޸𸮸� �Ҵ��Ѵ�.
	mp_send_data = new char[8192];
	// �ڽ��� ������ �������� ���� ����Ʈ�� ���� ���� �̸� �־�д�.
	*(unsigned char*)mp_send_data = a_valid_key; // default

	// ���ſ����� ����� 8 Kbytes �޸𸮸� �Ҵ�
	mp_recv_data = new char[8192];
	// ������ ���� �� ���� ���� �޽����� ���� ������ �ڵ� ���� �ʱ�ȭ�Ѵ�.
	mh_notify_wnd = nullptr; //NULL
	// ������ ���� �� ���� ���� �޽��� ID�� ����� ���� ����ڿ��� �Ѱܹ޾� �����Ѵ�.
	m_data_notify_id = a_data_notify_id;

	// ���� �ý����� ����ϵ��� ����
	WSADATA temp;
	WSAStartup(0x0202, &temp);
}

Socket::~Socket() {
	// ���۰� ���ſ� ����ϴ� �޸𸮸� ����
	delete[] mp_send_data;
	delete[] mp_recv_data;

	// ���� �ý����� �� �̻� ������� �ʵ��� ����
	WSACleanup();
}

int Socket::SendFrameData(SOCKET ah_socket, unsigned char a_message_id, const char* ap_body_data, BS a_body_size) {
	// �޽��� ID�� �� ��° ����Ʈ�� ����. ù ��° ����Ʈ���� ���а��� �̹� ����ִ�.(��ü �����ڿ��� �۾���)
	*(unsigned char*)(mp_send_data + 1) = a_message_id;
	// ����°�� �׹�° ����Ʈ�� 'Body" �������� ũ�⸦ ����.(����� 2 bytes ũ��. 4 bytes�� ��� BS�� ����)
	*(BS*)(mp_send_data + 2) = a_body_size;
	// �ټ���° ��ġ�� 'Body'�� �����ϴ� �����͸� �����Ѵ�.
	memcpy(mp_send_data + HEAD_SIZE, ap_body_data, a_body_size);
	// �������� ������ ����. ���� �ѷ��� Head ũ�� + Body ũ��� ����.
	if (send(ah_socket, mp_send_data, HEAD_SIZE + a_body_size, 0) == (a_body_size + HEAD_SIZE)) return 1; //���� ����

	return 0; // ���� ����
}

int Socket::ReceiveData(SOCKET ah_socket, BS a_body_size)
{
	BS total_size = 0, retry = 0;
	int read_size;

	// ������ ������ ������ a_body_size�� ������ ũ�⸸ŭ �ѹ��� �� ������ �� �ֱ� ������
	// �ݺ����� �̿��ؼ� ������ ��õ��ϸ鼭 �д´�.
	while (total_size < a_body_size) {
		// ó������ a_body_size��ŭ �б⸦ �õ������� �ѹ��� �� ������ ��� ������ ���� ũ�⸦ 
		// ������ ������ ũ�⸦ ��� �ݺ��ؼ� �д´�.
		read_size = recv(ah_socket, mp_recv_data + total_size, a_body_size - total_size, 0);
		if (read_size == SOCKET_ERROR) {
			//������ ������ ���Ͽ� ������ �� ��� 0.5�ʵ��� 10ȸ �ݺ��ϸ鼭 ��õ��Ѵ�.
			retry++;
			Sleep(50);
			if (retry > 10) break;
		}
		else {
			// ������ ���ŵ� ũ�⸦ total_size ������ �ջ��Ѵ�.
			if (read_size > 0) total_size = (BS)(total_size + read_size);
			// �� ���ŵ� ũ�Ⱑ ���� a_body_size���� �۴ٸ� ���� ���°� ���� �ʴٴ�
			// ���̱� ������ �ణ�� ������ �ָ鼭 �ٽ� �б⸦ �õ��ϴ� ���� ����.
			//if (total_size < a_body_size) Sleep(5); // �׷��� �ӵ� ������ ������ �� �� �����Ƿ� 5ms���� ������ �ִ� �ڵ�� ���x

			// �߰��� ������ ���� ��õ��� �ߴ��� �ٽ� ������ �����ߴٸ� ��õ� Ƚ�� �ʱ�ȭ
			retry = 0;
		}
	}
	return retry <= 10; // ���� ���� : 1, ���Ž��� :0
}

void Socket::ProcessRecvEvent(SOCKET ah_socket) {
	unsigned char msg_id;
	BS body_size;
	// FD_READ �̺�Ʈ�� �����ϰ� �߻����� �ʵ��� FD_READ �̺�Ʈ�� �����Ѵ�.
	//::WSAEventSelect(); // WSAAsyncSelect�� WSAEventSelect�� �ٲٱ�.
	::WSAAsyncSelect(ah_socket, mh_notify_wnd, m_data_notify_id, FD_CLOSE);

	unsigned char key = 0;
	// ���� ���� �����Ѵ�.
	recv(ah_socket, (char *)&key, 1, 0);
	// ����ڰ� ������ ���� ���� ��ġ�ϴ��� üũ�Ѵ�.
	if (key == m_valid_key) {
		// Message ID�� �����Ѵ�. (1 byte)
		recv(ah_socket, (char*)&msg_id, 1, 0);
		// Body size�� �����Ѵ�. (2 bytes)
		recv(ah_socket, (char*)&body_size, sizeof(BS), 0);
		if (body_size > 0) { // body size�� 0�� ��쿡�� ������ �ʿ� x
			// Body size�� ũ�� ������ recv �Լ��� �ƴ� �������� ��õ� ������ ������
			// ReceiveData �Լ��� �����͸� ����.
			if (!ReceiveData(ah_socket, body_size)) {
				// ������ ���� ���н� ����� ������ ����.
				DisconnectSocket(ah_socket, -2);
				return;
			}
		}
		// ���������� 'Head'�� 'Body'�� ������ ��쿡�� �� �������� ����Ͽ� ����ڰ� ���ϴ� �۾��� ó��
		// ProcessRecvData �Լ��� ��ӹ��� �ڽ� Ŭ�������� �������̵� ����� �������Ͽ� �ڽŵ��� ���ϴ� �۾��� �߰��� �Լ�
		if (ProcessRecvData(ah_socket, msg_id, mp_recv_data, body_size) == 1) {
			// ���Ͽ� ������ �߻����� �ʾҴٸ� �ٽ� ���� �̺�Ʈ ó���� �����ϵ��� FD_READ �ɼ��� �߰�
			::WSAAsyncSelect(ah_socket, mh_notify_wnd, m_data_notify_id, FD_CLOSE | FD_READ);
		}
	}
	else DisconnectSocket(ah_socket, -1); // key���� invalid�ϸ� ���� ����.
}

void Socket::DisconnectSocket(SOCKET ah_socket, int a_error_code) {

}
int Socket::ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char* ap_recv_data, BS a_body_size) {
	return 0;
}

void Socket::AsciiToUnicode(wchar_t* ap_dest_ip, char* ap_src_ip) {
	// ASCII ������ ���ڿ��� �����ڵ�� ��ȯ
	int ip_length = strlen(ap_src_ip) + 1;
	// 1����Ʈ ������ ���ڿ��� ����Ʈ ������ �̿��Ͽ� 2����Ʈ �������� ����
	memset(ap_dest_ip, 0, ip_length << 1);
	for (int i = 0; i < ip_length; ++i) ap_dest_ip[i] = ap_src_ip[i];
}

void Socket::UnicodeToAscii(char* ap_dest_ip, wchar_t* ap_src_ip) {
	// �����ڵ� ������ ���ڿ��� ASCII�� ��ȯ
	int ip_length = wcslen(ap_src_ip) + 1;
	// 2����Ʈ ������ ���ڿ��� 1����Ʈ �������� ����
	for (int i = 0; i < ip_length; ++i) {
		ap_dest_ip[i] = (char)ap_src_ip[i];
	}
}

UserData::UserData() {
	mh_socket = INVALID_SOCKET;		// ���� �ڵ� �ʱ�ȭ
	m_ip_address[0] = 0;			// �ּ� �� �ʱ�ȭ
	mp_send_man = new SendManager;	// ���ۿ� ��ü ����
	mp_recv_man = new RecvManager;	// ���ſ� ��ü ����
}

UserData::~UserData() {
	// ������ �����Ǿ� �ִٸ� ������ ����.
	if (mh_socket != INVALID_SOCKET) closesocket(mh_socket);
	// ���۰� ������ ���� �����ߴ� ��ü�� ����.
	delete mp_send_man;
	delete mp_recv_man;
}

wchar_t* UserData::GetIP() {
	return m_ip_address;
}

void UserData::SetIP(const wchar_t* ap_ip_address) {
	wcscpy_s(m_ip_address, ap_ip_address);
}

void UserData::CloseSocket(char a_linger_flag) {
	if (mh_socket != INVALID_SOCKET) {
		if (a_linger_flag) {
			// onoff�� TRUE�̹Ƿ� ������ ������, linger���� 0�̹Ƿ� 0�ʵ��� ������ ����(��, ���� �ʴ°Ͱ� ������ ������������) ���ۿ� �����ִ� �����ʹ� �������� ������ ���� �ǽ�
			LINGER temp_linger = { TRUE, 0 };
			// ���� �ɼ��� �����Ͽ� ������ �����͸� �������̴��� ������ ��� ������ �� �ִ�.
			setsockopt(mh_socket, SOL_SOCKET, SO_LINGER, (char*)&temp_linger, sizeof(temp_linger));
		}
		// ������ �����Ǿ� �ִٸ� ������ ����
		closesocket(mh_socket);
		mh_socket = INVALID_SOCKET; //���� �ڵ� �ʱ�ȭ
	}
}

ServerSocket::ServerSocket(unsigned char a_valid_key, unsigned short int a_max_user_count, UserData* ap_user_data, 
	int a_accept_notify_id, int a_data_notify_id) : Socket(a_valid_key, a_data_notify_id) {
	// ������ ������ �ִ� ����� ���� �����Ѵ�.
	m_max_user_count = a_max_user_count;
	// Listen �۾��� ������ �ʱ�ȭ�Ѵ�.
	mh_listen_socket = INVALID_SOCKET;

	// �ִ� ����� ����ŭ ����� ������ ������ ��ü�� ������ �����͸� �����Ѵ�.
	mp_user_list = new UserData *[m_max_user_count];
	// �ִ� ����� ����ŭ ����� ������ ������ ��ü�� ���������� �����Ѵ�.
	for (int i = 0; i < m_max_user_count; ++i) {
		// ������ ���ÿ� Ư�� Ŭ���� ���Ŀ� ���ӵ��� �ʵ��� ��� �Լ��� ����ؼ� ��ü�� �����Ѵ�.
		// CreateObject �Լ��� �Ű������� ���޵� ap_user_data�� ������ ��ü�� �����Ѵ�.
		mp_user_list[i] = ap_user_data->CreateObject();
	}
	// ���ο� ����ڰ� ���������� �߻��� �޽��� ID�� �����Ѵ�.
	m_accept_notify_id = a_accept_notify_id;
	// ����� ������ �����ϱ� ���� �Ű������� ���޹��� ��ü�� �����Ѵ�. �̹� ������ ������ ��ü��
	// mp_user_list�� �Ҵ�Ǿ� �ֱ� ������ ������ �ʿ䰡 ����.
	delete ap_user_data;
}

ServerSocket::~ServerSocket() {
	// listen ������ �����Ǿ� �ִٸ� ����
	if (mh_listen_socket != INVALID_SOCKET) closesocket(mh_listen_socket);
	// �ִ� ����� ����ŭ �����Ǿ� �ִ� ��ü�� �����Ѵ�.
	for (int i = 0; i < m_max_user_count; ++i) {
		delete mp_user_list[i];
	}
	// ����� ��ü�� �����ϱ� ���� �����ߴ� �����͸� ����
	delete[] mp_user_list;
}

int ServerSocket::StartServer(const wchar_t* ap_ip_address, int a_port, HWND ah_notify_wnd) {
	// �񵿱� ������ ���Ͽ� �̺�Ʈ(FD_ACCEPT, FD_READ, FD_CLOSE) �߻�������
	// ���޵Ǵ� �޽����� ������ �������� �ڵ��� �����Ѵ�.
	mh_notify_wnd = ah_notify_wnd;

	struct sockaddr_in serv_addr;
	// listen �۾��� ������ TCP �������� ����
	mh_listen_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	// ���� ������ �����ߴ��� üũ�Ѵ�.
	if (mh_listen_socket < 0) return -1; // -1 : ��Ĺ ���� ����

	char temp_ip_address[16];
	// �����ڵ� �������� ���޵� IP�ּҸ� ASCII �������� ����
	UnicodeToAscii(temp_ip_address, (wchar_t*)ap_ip_address);
	memset((char*)&serv_addr, 0, sizeof(serv_addr));
	// ��Ʈ��ũ ��ġ�� mh_listen_socket�� �����ϱ� ���ؼ� IP�ּҿ�
	// ��Ʈ��ȣ�� ������ �⺻ ������ �����Ѵ�.
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(temp_ip_address);
	serv_addr.sin_port = htons((short unsigned int)a_port);
	// ��Ʈ��ũ ��ġ�� mh_listen_socket ������ �����Ѵ�.
	if (bind(mh_listen_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		//������ ��� ������ �����ϰ� mh_listen_socket ������ �ʱ�ȭ�Ѵ�.
		closesocket(mh_listen_socket);
		mh_listen_socket = INVALID_SOCKET;
		return -2; // -2 : bind ����
	}
	// Ŭ���̾�Ʈ ������ ����Ѵ�. �� �������� Ŭ���̾�Ʈ�� ������ ����������.
	listen(mh_listen_socket, 5);
	// ���ο� Ŭ���̾�Ʈ�� ���������� �߻��ϴ� FD_ACCEPT �̺�Ʈ�� üũ�ؼ� ah_notify_wnd��
	// �ش��ϴ� ������� m_accept_notify_id �޽����� �����ϴ� �񵿱⸦ �����Ѵ�.
	// accept �Լ��� �ٷ� ȣ���ϸ� ���ο� ����ڰ� �����Ҷ����� ���α׷��� ��������� ������ ������
	// �񵿱� ���� ���
	WSAAsyncSelect(mh_listen_socket, ah_notify_wnd, m_accept_notify_id, FD_ACCEPT);

	return 1; // 1: listen �۾� ����
}

int ServerSocket::ProcessToAccept(WPARAM wParam, LPARAM lParam) {
	struct sockaddr_in cli_addr;
	int temp_client_info_size = sizeof(cli_addr), i;
	// ���� ������ �õ��ϴ� Ŭ���̾�Ʈ�� ����� ������ �����Ѵ�.
	SOCKET h_client_socket = accept((SOCKET)wParam, (struct sockaddr*)&cli_addr, &temp_client_info_size);

	if (h_client_socket == INVALID_SOCKET) return -1;
	else {
		UserData* p_user;
		wchar_t temp_ip_address[16];
		// ���� ������ Ŭ���̾�Ʈ�� IP�� �����ڵ� ������ ���ڿ��� ��ȯ
		AsciiToUnicode(temp_ip_address, inet_ntoa(cli_addr.sin_addr));
		// ����� ������ ������ ��ü�� �߿� ���� ������ �������� ���� ��ü�� ã�Ƽ�
		// ���� ������ ����� ������ �����Ѵ�.
		for (i = 0; i < m_max_user_count; ++i) {
			p_user = mp_user_list[i];
			// ����� ������ ���� �ڵ� ���� INVALID_SOCKET�̶�� �ش� ��ü�� �̻������ ��ü�̴�.
			if (p_user->GetHandle() == INVALID_SOCKET) {
				p_user->SetHandle(h_client_socket);	// ����� ������ ������ ����
				p_user->SetIP(temp_ip_address);		// ����� ������ IP �ּҸ� ����
				// ����� Ŭ���̾�Ʈ�� �����͸� ���� (FD_READ)�ϰų� ������ ����(FD_CLOSE)�ϸ�
				// mh_notify_wnd �ڵ� ���� �ش��ϴ� ������� m_data_notify_id �޽���ID��
				// ���޵ǵ��� �񵿱⸦ �����Ѵ�.
				WSAAsyncSelect(h_client_socket, mh_notify_wnd, m_data_notify_id, FD_READ | FD_CLOSE);
				// ���ο� ����ڰ� ������ ������ ó���ؾ��� �۾��� �Ѵ�. (Ŭ���� ����ڰ� ���� �����ؾ���. virtual)
				AddWorkForAccept(p_user);
				break;
			}
		}
		// �ִ� �����ڼ��� �ʰ��Ͽ� �� �̻� Ŭ���̾�Ʈ�� ������ ����� �� ���� ���
		if (i == m_max_user_count) {
			// �����ڼ� �ʰ��� ���� �۾��� �Ѵ�. (Ŭ���� ����ڰ� ���� �����ؾ� ��. virtual)
			ShowLimitError(temp_ip_address);
			// ������ ������ �����Ѵ�.
			closesocket(h_client_socket);
			return -2; // -2: ����� �ʰ�
		}
	}
	return 1; // ���������� ���� ó����.
}

void ServerSocket::ProcessClientEvent(WPARAM wParam, LPARAM lParam) {
	if (WSAGETSELECTEVENT(lParam) == FD_READ) {
		ProcessRecvEvent((SOCKET)wParam); // ���۵� �����͸� �м��ؼ� ó���ϴ� �Լ� ȣ��
	}
	else { // FD_CLOSE, Ŭ���̾�Ʈ�� ������ ������ ���
		UserData* p_data = FindUserData((SOCKET)wParam);
		AddWorkForCloseUser(p_data, 0);
		// ������ ������ ������ �ݰ� �ʱ�ȭ�Ѵ�.
		p_data->CloseSocket(0);
	}
}

void ServerSocket::DisconnectSocket(int ah_socket, int a_error_code) {
	// ���� �ڵ��� ����Ͽ� ����� ������ ã�´�.
	UserData* p_user_data = FindUserData(ah_socket);
	// ������ �����ϱ� ���� �۾��ؾ� �� ������ ó��
	AddWorkForCloseUser(p_user_data, a_error_code);
	// �ش� ������� ������ �ݴ´�.
	p_user_data->CloseSocket(1);
}

//virtual�� �ڽ� Ŭ�������� �Լ� ������ �ʿ�.
int ServerSocket::ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char* ap_recv_data, BS a_body_size) {
	// ���� �ڵ� ���� ����Ͽ� �� ������ ����ϴ� ����ڸ� ã�´�.
	UserData* p_user_data = FindUserData(ah_socket);

	if (a_msg_id == 251) { // ���� �޽��� 251���� Ŭ���̾�Ʈ�� ū�뷮�� �����͸� �����ϱ� ���� ���
		char* p_send_data;
		// ���� ���� ��ġ�� ��´�.
		BS send_size = p_user_data->GetSendMan()->GetPosition(&p_send_data);
		// ������ �����Ͱ� �� �ִٸ� ���� �޽��� ��ȣ�� 252�� ����Ͽ� Ŭ���̾�Ʈ���� �����͸� ����
		if (p_user_data->GetSendMan()->IsProcessing()) SendFrameData(ah_socket, 252, p_send_data, send_size);
		else {
			// ������ ���ҵ� �������� ������ �κ��̶�� ���� �޽��� ��ȣ�� 253���� ����Ͽ� Ŭ���̾�Ʈ���� ������ ����
			SendFrameData(ah_socket, 253, p_send_data, send_size);
			// ������ �����͸� �����ϰ� ���ۿ� ����ߴ� �޸𸮸� �����Ѵ�.
			p_user_data->GetSendMan()->DeleteData();
			// ���� ������ ����ϴ� �����쿡 ������ �Ϸ�Ǿ����� �˷��ش�.
			// ������ �Ϸ�Ǿ����� ���α׷��� � ǥ�ø� �ϰ� �ʹٸ� �ش� �����쿡�� ������Ͽ� define �س��� LM_SEND_COMPLETED �޽����� üũ�ϸ� �ȴ�.
			::PostMessage(mh_notify_wnd, LM_SEND_COMPLETED, (WPARAM)p_user_data, 0);
		}
	}
	else if (a_msg_id == 252) {
		// 252���� ��뷮�� �����͸� �����Ҷ� ����ϴ� ����� �޽��� ��ȣ
		// ���ŵ� �����ʹ� ������ �����ϴ� ��ü�� �Ѱܼ� �����͸� ��ģ��.
		p_user_data->GetRecvMan()->AddData(ap_recv_data, a_body_size);
		// 252���� ������ �߰��� ������ �����Ͱ� �ִٴ� ���̱� ������ ���� �޽��� 251���� Ŭ���̾�Ʈ�� �����Ͽ�
		// �߰� �����͸� ��û
		SendFrameData(ah_socket, 251, NULL, 0);
	}
	else if (a_msg_id == 253) {
		// 253���� ��뷮�� �����͸� �����Ҷ� ����ϴ� ����� �޽��� ��ȣ
		// ���ŵ� �����ʹ� ������ �����ϴ� ��ü�� �Ѱܼ� �����͸� ��ģ��.
		p_user_data->GetRecvMan()->AddData(ap_recv_data, a_body_size);
		// 253���� ������ ������ �Ϸ�Ǿ��ٴ� �޽����̱� ������ ���� ������ ����ϴ� �����쿡 �Ϸ�Ǿ����� �˷��ش�.
		// ���� �����쿡�� ������ �Ϸ�� �����͸� ����Ϸ��� ������Ͽ� define�� LM_RECV_COMPLETED �޽����� ����ϸ� �ȴ�.
		// LM_RECV_COMPLETED �޽����� ������ ó���⿡�� �����Ҷ� ����� �޸𸮸� DeleteData �Լ��� ȣ���ؼ� �����ؾ� �Ѵ�.
		::PostMessageW(mh_notify_wnd, LM_RECV_COMPLETED, (WPARAM)p_user_data, 0);
	}
	// ���ŵ� �����͸� ���������� ó����. ����, ���� �����͸� ó���ϴ��߿� ������ ���������� 0�� ��ȯ�ؾ� �Ѵ�.
	// 0�� ��ȯ�ϸ� �̼��Ͽ� ���ؼ� �񵿱� �۾��� �ߴܵȴ�.
	return 1;
}

ClientSocket::ClientSocket(unsigned char a_valid_key,
	int a_connect_notify_id, int a_data_notify_id) : Socket(a_valid_key, a_data_notify_id)
{
	// ���� ���¸� '���� ����'�� �ʱ�ȭ �Ѵ�.
	m_connect_flag = 0;
	// ���� �ڵ��� �ʱ�ȭ �Ѵ�.
	mh_socket = INVALID_SOCKET;
	// FD_CONNECT �̺�Ʈ �߻��ÿ� ����� ������ �޽��� ��ȣ�� ����Ѵ�.
	m_connect_notify_id = a_connect_notify_id;
}

ClientSocket::~ClientSocket()
{
	// ������ ����ϱ� ���� ������ �����Ǿ� �ִٸ� ������ �����Ѵ�.
	if (mh_socket != INVALID_SOCKET) closesocket(mh_socket);
}

int ClientSocket::ConnectToServer(const wchar_t* ap_ip_address, int a_port_num, HWND ah_notify_wnd)
{
	// ������ �õ����̰ų� ���ӵ� ���¶�� ������ �õ����� �ʴ´�.
	if (m_connect_flag != 0) return 0; // �ߺ� �õ� �Ǵ� �ߺ� ���� ����

	// ���� �̺�Ʈ�� ���� ������ �޽����� ���� �������� �ڵ��� �����Ѵ�.
	mh_notify_wnd = ah_notify_wnd;
	// ������ ����� ������ �����Ѵ�. (TCP)
	mh_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in srv_addr;
	char temp_ip_address[16];
	// �����ڵ� �������� ���޵� IP �ּҸ� ASCII �������� �����Ѵ�.
	UnicodeToAscii(temp_ip_address, (wchar_t*)ap_ip_address);
	// ������ �����ϱ� ���Ͽ� ������ IP �ּҿ� ��Ʈ ��ȣ�� ���� ������ ����
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr(temp_ip_address);
	srv_addr.sin_port = htons(a_port_num);

	// ������ �����ϴ� connect �Լ��� ������� ���¿� ������ �ֱ� ������ �񵿱⸦ ����
	// ���� ���ӿ� ���� ����� FD_CONNECT �̺�Ʈ�� �߻��ϸ� ah_notify_wnd�� �ش��ϴ� �������
	// m_connect_notify_id�� �ش��ϴ� ������ �޽����� �����Ѵ�.
	WSAAsyncSelect(mh_socket, ah_notify_wnd, m_connect_notify_id, FD_CONNECT);
	// ������ ������ �õ��Ѵ�.
	connect(mh_socket, (sockaddr*)&srv_addr, sizeof(srv_addr));
	// ���� ���¸� '���� �õ���'���� �����Ѵ�.
	m_connect_flag = 1;

	return 1;
}

int ClientSocket::ResultOfConnection(LPARAM lParam)
{
	if (WSAGETSELECTERROR(lParam) == 0) { // ���� ������ ����. ��, ������ ���������� ����
		m_connect_flag = 2; // ���� ���¸� '����'���� ����
		// ���ӵ� �������� �������� �����Ͱ� ���ŵǰų� ������ �����Ǿ����� ������ �޽�����
		// ������ �ֵ��� �񵿱⸦ ����
		WSAAsyncSelect(mh_socket, mh_notify_wnd, m_data_notify_id, FD_READ | FD_CLOSE);
		return 1; // ���� ����
	}
	else {
		// ���� ����
		closesocket(mh_socket);		// ������ ����ϱ� ���� ���� ������ ����
		mh_socket = INVALID_SOCKET; // ������ �ʱ�ȭ
		m_connect_flag = 0;			// ���� ���¸� '����'�� ����
	}
	return 0; // ���� ����
}

int ClientSocket::ProcessServerEvent(WPARAM wParam, LPARAM lParam) 
{
	// ������ ���� �Ǿ��� ��, �߰����� �޽����� ������� �ʰ� �� �Լ��� ��ȯ ������
	// �����ؼ� ����� �� �ֵ��� FD_READ�� 1, FD_CLOSE�� 0���� ��ȯ�ϵ��� ����.
	int state = 1;
	if (WSAGETSELECTEVENT(lParam) == FD_READ) {
		// �������� �����͸� ������ ��� ���ŵ� �����͸� ó���ϱ� ���� �Լ��� ȣ��
		ProcessRecvEvent((SOCKET)wParam);
	}
	else { // FD_CLOSE, ������ ������ ������ ���
		state = 0;
		m_connect_flag = 0;			// ���� ���¸� '����'�� �����Ѵ�.
		closesocket(mh_socket);		// ������ ����ϱ� ���� ������ ������ �����Ѵ�.
		mh_socket = INVALID_SOCKET;	// ���� �ڵ��� �����ϴ� ������ �ʱ�ȭ �Ѵ�.
	}
	return state; // �̺�Ʈ ������ ��ȯ
}

void ClientSocket::DisconnectSocket(SOCKET ah_socket, int a_error_code)
{
	// ���� ���¸� '����'�� ����
	m_connect_flag = 0;
	LINGER temp_linger = { TRUE, 0 };
	// �������� �����͸� �����ϰ� �ִ� ���¶�� ������ ������ �������� ���ϱ� ������
	// ���� �ɼ��� �����Ͽ� �����͸� �����ϰ� �ִ��� ������ ������ �� �ֵ��� �Ѵ�.
	setsockopt(mh_socket, SOL_SOCKET, SO_LINGER, (char*)&temp_linger, sizeof(temp_linger));
	// ������ �����Ѵ�.
	closesocket(mh_socket);
	// ���� �ڵ� ���� �����ϴ� ������ �ʱ�ȭ �Ѵ�.
	mh_socket = INVALID_SOCKET;
}

int ClientSocket::SendFrameData(unsigned char a_message_id, const char* ap_body_data, BS a_body_size)
{
	return Socket::SendFrameData(mh_socket, a_message_id, ap_body_data, a_body_size);
}

int ClientSocket::ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char* ap_recv_data, BS a_body_size)
{
	if (a_msg_id == 251) {
		char* p_send_data; // ���� �޽��� 251���� ������ ū�뷮�� �����͸� �����ϱ� ���� ���
		// ���� ���� ��ġ�� ��´�.
		BS send_size = m_send_man.GetPosition(&p_send_data);
		// ������ �����Ͱ� �� �ִٸ� ���� �޽��� ��ȣ�� 252�� ����Ͽ� �������� �����͸� �����Ѵ�.
		if (m_send_man.IsProcessing()) Socket::SendFrameData(mh_socket, 252, p_send_data, send_size);
		else {
			// ������ ���ҵ� �������� ������ �κ��̶�� ���� �޽��� ��ȣ�� 253���� ����Ͽ� �������� �����͸� �����Ѵ�.
			Socket::SendFrameData(mh_socket, 253, p_send_data, send_size);
			// ������ �����͸� �����ϰ� ���ۿ� ����ߴ� �޸𸮸� �����Ѵ�.
			m_send_man.DeleteData();
			// Ŭ���̾�Ʈ ������ ����ϴ� �����쿡 ������ �Ϸ�Ǿ����� �˷��ش�.
			// ������ �Ϸ�Ǿ����� ���α׷��� � ǥ�ø� �ϰ� �ʹٸ� �ش� �����쿡�� LM_SEND_COMPLETED �޽����� üũ�ϸ� �ȴ�.
			::PostAppMessage(mh_notify_wnd, LM_SEND_COMPLETED, 0, 0);
		}
	}
	else if (a_msg_id == 252) {
		// 252���� ��뷮�� �����͸� �����Ҷ� ����ϴ� ����� �޽��� ��ȣ�̴�.
		// ���ŵ� �����ʹ� ������ �����ϴ� ��ü�� �Ѱܼ� �����͸� ��ģ��.
		m_recv_man.AddData(ap_recv_data, a_body_size);
		// 252���� ������ �߰��� ������ �����Ͱ� �ִٴ� ���̱� ������ ���� �޽��� 251���� ������ �����Ͽ�
		// �߰� �����͸� ��û
		Socket::SendFrameData(mh_socket, 251, NULL, 0);
	}
	else if (a_msg_id == 253) {
		// 253���� ��뷮�� �����͸� �����Ҷ� ����ϴ� ����� �޽��� ��ȣ�̴�.
		// ���ŵ� �����ʹ� ������ �����ϴ� ��ü�� �Ѱܼ� �����͸� ��ģ��.
		m_recv_man.AddData(ap_recv_data, a_body_size);
		// 253���� ������ ������ �Ϸ�Ǿ��ٴ� �޽����̱� ������ Ŭ���̾�Ʈ ������ ����ϴ� �����쿡 �Ϸ�Ǿ����� �˷��ش�.
		// ���� �����쿡�� ������ �Ϸ�� �����͸� ����Ϸ��� LM_RECV_COMPLETED �޽����� ����ϸ� �ȴ�.
		// LM_RECV_COMPLETED �޽����� ������ ó���⿡�� �����Ҷ� ����� �޸𸮸� DeleteData �Լ��� ȣ���ؼ� �����ؾ��Ѵ�.
		::PostMessage(mh_notify_wnd, LM_RECV_COMPLETED, 0, 0);
	}

	// ���ŵ� �����͸� ���������� ó����. ����, ���� �����͸� ó���ϴ� �߿� ������ ���������� 0�� ��ȯ�ؾ� �Ѵ�.
	// 0�� ��ȯ�ϸ� �� ���Ͽ� ���ؼ� �񵿱� �۾��� �ߴܵȴ�.
	return 1;
}

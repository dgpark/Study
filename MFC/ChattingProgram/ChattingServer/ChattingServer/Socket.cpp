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
	// 기존에 사용하던 메모리와 현재 필요한 메모리 크기가 동일하면 다시 메모리 할당할 필요x
	// (일정한 크기의 데이터를 지속적으로 전송하거나 수신하는 경우가 많다.)
	if (m_total_size != a_data_size) {
		if (mp_data != nullptr) delete[] mp_data;
		// 시정한 크기로 메모리를 할당한다.
		mp_data = new char[a_data_size];
		// 할당된 크기를 기억한다.
		m_total_size = a_data_size;
	}
	// 작업 위치를 가장 첫 위치로 초기화한다.
	m_cur_size = 0;
	// 할당된 메모리의 시작 위치를 반환한다.
	return mp_data;
}

void ExchangeManager::DeleteData()
{
	if (mp_data != nullptr) {
		//할당된 메모리를 제거하고 작업과 관련된 변수들을 초기화
		delete[] mp_data;
		mp_data = nullptr;
		m_total_size = 0;
	}
}

int SendManager::GetPosition(char** ap_data, int a_data_size) {
	// 새로운 전송 위치에 대한 주소를 첫번째 인자에 저장
	*ap_data = mp_data + m_cur_size;

	// 전송 크기를 계산하기 위해서 2048bytes를 더한 크기가 최대 크기보다 작은지 체크한다.
	if (m_cur_size + a_data_size < m_total_size) {
		// 최대 크기보다 작은 경우 2048bytes 만큼 전송하면 된다.
		// 다음 위치를 계산할 수 있도록 전송한 총 크기를 구한다.
		m_cur_size += a_data_size;
	}
	else {
		// 2048bytes 보다 작은 경우, 실제로 남은 크기만 전송한다.
		a_data_size = m_total_size - m_cur_size;
		// 현재 위치를 마지막 위치로 옮긴다.(마지막 전송)
		m_cur_size = m_total_size;
	}
	//계산된 전송크기를 반환
	return a_data_size;
}

int RecvManager::AddData(char* ap_data, int a_size) {
	// 수신된 데이터를 기존 수신 데이터 뒤에 추가한다.
	memcpy(mp_data + m_cur_size, ap_data, a_size);
	// 총 수신 크기를 계산
	m_cur_size += a_size;
	// 현재 수신된 데이터의 크기를 반환
	return m_cur_size;
}
Socket::Socket() {
	int a = -1;
}
Socket::Socket(unsigned char a_valid_key, int a_data_notify_id) {
	// 사용자가 지정한 프로토콜 구분 값을 저장한다.
	m_valid_key = a_valid_key;
	// 전송용으로 사용할 8 Kbytes 메모리를 할당한다.
	mp_send_data = new char[8192];
	// 자신이 전송할 프레임의 선두 바이트에 구분 값을 미리 넣어둔다.
	*(unsigned char*)mp_send_data = a_valid_key; // default

	// 수신용으로 사용할 8 Kbytes 메모리를 할당
	mp_recv_data = new char[8192];
	// 데이터 수신 및 연결 해제 메시지를 받은 윈도우 핸들 값을 초기화한다.
	mh_notify_wnd = nullptr; //NULL
	// 데이터 수신 및 연결 해제 메시지 ID로 사용할 값을 사용자에게 넘겨받아 저장한다.
	m_data_notify_id = a_data_notify_id;

	// 소켓 시스템을 사용하도록 설정
	WSADATA temp;
	WSAStartup(0x0202, &temp);
}

Socket::~Socket() {
	// 전송과 수신에 사용하던 메모리를 제거
	delete[] mp_send_data;
	delete[] mp_recv_data;

	// 소켓 시스템을 더 이상 사용하지 않도록 설정
	WSACleanup();
}

int Socket::SendFrameData(SOCKET ah_socket, unsigned char a_message_id, const char* ap_body_data, BS a_body_size) {
	// 메시지 ID를 두 번째 바이트에 저장. 첫 번째 바이트에는 구분값이 이미 들어있다.(객체 생성자에서 작업함)
	*(unsigned char*)(mp_send_data + 1) = a_message_id;
	// 세번째와 네번째 바이트에 'Body" 데이터의 크기를 저장.(현재는 2 bytes 크기. 4 bytes의 경우 BS값 변경)
	*(BS*)(mp_send_data + 2) = a_body_size;
	// 다섯번째 위치에 'Body'를 구성하는 데이터를 복사한다.
	memcpy(mp_send_data + HEAD_SIZE, ap_body_data, a_body_size);
	// 소켓으로 데이터 전송. 전송 총량은 Head 크기 + Body 크기와 같다.
	if (send(ah_socket, mp_send_data, HEAD_SIZE + a_body_size, 0) == (a_body_size + HEAD_SIZE)) return 1; //전송 성공

	return 0; // 전송 실패
}

int Socket::ReceiveData(SOCKET ah_socket, BS a_body_size)
{
	BS total_size = 0, retry = 0;
	int read_size;

	// 소켓의 수신이 느려서 a_body_size에 지정한 크기만큼 한번에 못 수신할 수 있기 때문에
	// 반복문을 이용해서 여러번 재시도하면서 읽는다.
	while (total_size < a_body_size) {
		// 처음에는 a_body_size만큼 읽기를 시도하지만 한번에 다 못읽은 경우 실제로 읽은 크기를 
		// 제외한 나머지 크기를 계속 반복해서 읽는다.
		read_size = recv(ah_socket, mp_recv_data + total_size, a_body_size - total_size, 0);
		if (read_size == SOCKET_ERROR) {
			//데이터 수신중 소켓에 오류가 난 경우 0.5초동안 10회 반복하면서 재시도한다.
			retry++;
			Sleep(50);
			if (retry > 10) break;
		}
		else {
			// 실제로 수신된 크기를 total_size 변수에 합산한다.
			if (read_size > 0) total_size = (BS)(total_size + read_size);
			// 총 수신된 크기가 아직 a_body_size보다 작다면 수신 상태가 좋지 않다는
			// 뜻이기 때문에 약간의 지연을 주면서 다시 읽기를 시도하는 것이 좋다.
			//if (total_size < a_body_size) Sleep(5); // 그러나 속도 저하의 원인이 될 수 있으므로 5ms동안 지연을 주는 코드는 사용x

			// 중간에 오류가 나서 재시도를 했더라도 다시 수신을 시작했다면 재시도 횟수 초기화
			retry = 0;
		}
	}
	return retry <= 10; // 수신 성공 : 1, 수신실패 :0
}

void Socket::ProcessRecvEvent(SOCKET ah_socket) {
	unsigned char msg_id;
	BS body_size;
	// FD_READ 이벤트가 과도하게 발생하지 않도록 FD_READ 이벤트를 제거한다.
	//::WSAEventSelect(); // WSAAsyncSelect를 WSAEventSelect로 바꾸기.
	::WSAAsyncSelect(ah_socket, mh_notify_wnd, m_data_notify_id, FD_CLOSE);

	unsigned char key = 0;
	// 구분 값을 수신한다.
	recv(ah_socket, (char *)&key, 1, 0);
	// 사용자가 지정한 구분 값과 일치하는지 체크한다.
	if (key == m_valid_key) {
		// Message ID를 수신한다. (1 byte)
		recv(ah_socket, (char*)&msg_id, 1, 0);
		// Body size를 수신한다. (2 bytes)
		recv(ah_socket, (char*)&body_size, sizeof(BS), 0);
		if (body_size > 0) { // body size가 0인 경우에는 수신할 필요 x
			// Body size는 크기 때문에 recv 함수가 아닌 안정적인 재시도 수신이 가능한
			// ReceiveData 함수로 데이터를 수신.
			if (!ReceiveData(ah_socket, body_size)) {
				// 데이터 수신 실패시 연결된 소켓을 해제.
				DisconnectSocket(ah_socket, -2);
				return;
			}
		}
		// 정상적으로 'Head'와 'Body'를 수신한 경우에는 이 정보들을 사용하여 사용자가 원하는 작업을 처리
		// ProcessRecvData 함수는 상속받은 자식 클래스에서 오버라이딩 기술로 재정의하여 자신들이 원하는 작업을 추가할 함수
		if (ProcessRecvData(ah_socket, msg_id, mp_recv_data, body_size) == 1) {
			// 소켓에 문제가 발생하지 않았다면 다시 수신 이벤트 처리가 가능하도록 FD_READ 옵션을 추가
			::WSAAsyncSelect(ah_socket, mh_notify_wnd, m_data_notify_id, FD_CLOSE | FD_READ);
		}
	}
	else DisconnectSocket(ah_socket, -1); // key값이 invalid하면 접속 해제.
}

void Socket::DisconnectSocket(SOCKET ah_socket, int a_error_code) {

}
int Socket::ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char* ap_recv_data, BS a_body_size) {
	return 0;
}

void Socket::AsciiToUnicode(wchar_t* ap_dest_ip, char* ap_src_ip) {
	// ASCII 형식의 문자열을 유니코드로 변환
	int ip_length = strlen(ap_src_ip) + 1;
	// 1바이트 형식의 문자열을 시프트 연산을 이용하여 2바이트 형식으로 변경
	memset(ap_dest_ip, 0, ip_length << 1);
	for (int i = 0; i < ip_length; ++i) ap_dest_ip[i] = ap_src_ip[i];
}

void Socket::UnicodeToAscii(char* ap_dest_ip, wchar_t* ap_src_ip) {
	// 유니코드 형식의 문자열을 ASCII로 변환
	int ip_length = wcslen(ap_src_ip) + 1;
	// 2바이트 형식의 문자열을 1바이트 형식으로 변경
	for (int i = 0; i < ip_length; ++i) {
		ap_dest_ip[i] = (char)ap_src_ip[i];
	}
}

UserData::UserData() {
	mh_socket = INVALID_SOCKET;		// 소켓 핸들 초기화
	m_ip_address[0] = 0;			// 주소 값 초기화
	mp_send_man = new SendManager;	// 전송용 객체 생성
	mp_recv_man = new RecvManager;	// 수신용 객체 생성
}

UserData::~UserData() {
	// 소켓이 생성되어 있다면 소켓을 제거.
	if (mh_socket != INVALID_SOCKET) closesocket(mh_socket);
	// 전송과 수신을 위해 생성했던 객체를 제거.
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
			// onoff가 TRUE이므로 소켓을 열지만, linger값이 0이므로 0초동안 소켓을 열고(즉, 열지 않는것과 같으나 비정상종료임) 버퍼에 남아있던 데이터는 버려지는 비정상 종료 실시
			LINGER temp_linger = { TRUE, 0 };
			// 링거 옵션을 변경하여 소켓이 데이터를 수신중이더라도 소켓을 즉시 제거할 수 있다.
			setsockopt(mh_socket, SOL_SOCKET, SO_LINGER, (char*)&temp_linger, sizeof(temp_linger));
		}
		// 소켓이 생성되어 있다면 소켓을 제거
		closesocket(mh_socket);
		mh_socket = INVALID_SOCKET; //소켓 핸들 초기화
	}
}

ServerSocket::ServerSocket(unsigned char a_valid_key, unsigned short int a_max_user_count, UserData* ap_user_data, 
	int a_accept_notify_id, int a_data_notify_id) : Socket(a_valid_key, a_data_notify_id) {
	// 서버에 접속할 최대 사용자 수를 저장한다.
	m_max_user_count = a_max_user_count;
	// Listen 작업용 소켓을 초기화한다.
	mh_listen_socket = INVALID_SOCKET;

	// 최대 사용자 수만큼 사용자 정보를 저장할 객체를 관리할 포인터를 생성한다.
	mp_user_list = new UserData *[m_max_user_count];
	// 최대 사용자 수만큼 사용자 정보를 저장할 객체를 개별적으로 생성한다.
	for (int i = 0; i < m_max_user_count; ++i) {
		// 다형성 사용시에 특정 클래스 형식에 종속되지 않도록 멤버 함수를 사용해서 객체를 생성한다.
		// CreateObject 함수는 매개변수로 전달된 ap_user_data와 동일한 객체를 생성한다.
		mp_user_list[i] = ap_user_data->CreateObject();
	}
	// 새로운 사용자가 접속했을때 발생할 메시지 ID를 저장한다.
	m_accept_notify_id = a_accept_notify_id;
	// 사용자 정보를 생성하기 위해 매개변수로 전달받은 객체를 제거한다. 이미 동일한 형식의 개체가
	// mp_user_list에 할당되어 있기 때문에 보관할 필요가 없다.
	delete ap_user_data;
}

ServerSocket::~ServerSocket() {
	// listen 소켓이 생성되어 있다면 제거
	if (mh_listen_socket != INVALID_SOCKET) closesocket(mh_listen_socket);
	// 최대 사용자 수만큼 생성되어 있던 객체를 제거한다.
	for (int i = 0; i < m_max_user_count; ++i) {
		delete mp_user_list[i];
	}
	// 사용할 객체를 관리하기 위해 생성했던 포인터를 제거
	delete[] mp_user_list;
}

int ServerSocket::StartServer(const wchar_t* ap_ip_address, int a_port, HWND ah_notify_wnd) {
	// 비동기 형식의 소켓에 이벤트(FD_ACCEPT, FD_READ, FD_CLOSE) 발생했을떄
	// 전달되는 메시지를 수신할 윈도우의 핸들을 저장한다.
	mh_notify_wnd = ah_notify_wnd;

	struct sockaddr_in serv_addr;
	// listen 작업용 소켓을 TCP 형식으로 생성
	mh_listen_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	// 소켓 생성에 성공했는지 체크한다.
	if (mh_listen_socket < 0) return -1; // -1 : 소캣 생성 실패

	char temp_ip_address[16];
	// 유니코드 형식으로 전달된 IP주소를 ASCII 형식으로 변경
	UnicodeToAscii(temp_ip_address, (wchar_t*)ap_ip_address);
	memset((char*)&serv_addr, 0, sizeof(serv_addr));
	// 네트워크 장치에 mh_listen_socket을 연결하기 위해서 IP주소와
	// 포트번호를 가지고 기본 정보를 구성한다.
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(temp_ip_address);
	serv_addr.sin_port = htons((short unsigned int)a_port);
	// 네트워크 장치에 mh_listen_socket 소켓을 연결한다.
	if (bind(mh_listen_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		int errorCheck = WSAGetLastError();
		//실패한 경우 소켓을 제거하고 mh_listen_socket 변수를 초기화한다.
		closesocket(mh_listen_socket);
		mh_listen_socket = INVALID_SOCKET;
		return -2; // -2 : bind 오류
	}
	// 클라이언트 접속을 허락한다. 이 시점부터 클라이언트의 접속이 가능해진다.
	listen(mh_listen_socket, 5);
	// 새로운 클라이언트가 접속했을때 발생하는 FD_ACCEPT 이벤트를 체크해서 ah_notify_wnd에
	// 해당하는 윈도우로 m_accept_notify_id 메시지를 전달하는 비동기를 설정한다.
	// accept 함수를 바로 호출하면 새로운 사용자가 접속할때까지 프로그램이 응답없음에 빠지기 때문에
	// 비동기 설정 사용
	WSAAsyncSelect(mh_listen_socket, ah_notify_wnd, m_accept_notify_id, FD_ACCEPT);

	return 1; // 1: listen 작업 성공
}

int ServerSocket::ProcessToAccept(WPARAM wParam, LPARAM lParam) {
	struct sockaddr_in cli_addr;
	int temp_client_info_size = sizeof(cli_addr), i;
	// 새로 접속을 시도하는 클라이언트와 통신할 소켓을 생성한다.
	SOCKET h_client_socket = accept((SOCKET)wParam, (struct sockaddr*)&cli_addr, &temp_client_info_size);

	if (h_client_socket == INVALID_SOCKET) return -1;
	else {
		UserData* p_user;
		wchar_t temp_ip_address[16];
		// 새로 접속한 클라이언트의 IP를 유니코드 형식의 문자열로 변환
		AsciiToUnicode(temp_ip_address, inet_ntoa(cli_addr.sin_addr));
		// 사용자 정보를 저장할 객체들 중에 아직 소켓을 배정받지 않은 객체를 찾아서
		// 현재 접속한 사용자 정보를 저장한다.
		for (i = 0; i < m_max_user_count; ++i) {
			p_user = mp_user_list[i];
			// 사용자 정보의 소켓 핸들 값이 INVALID_SOCKET이라면 해당 객체는 미사용중인 객체이다.
			if (p_user->GetHandle() == INVALID_SOCKET) {
				p_user->SetHandle(h_client_socket);	// 사용자 정보에 소켓을 저장
				p_user->SetIP(temp_ip_address);		// 사용자 정보에 IP 주소를 저장
				// 연결된 클라이언트가 데이터를 전송 (FD_READ)하거나 연결을 해제(FD_CLOSE)하면
				// mh_notify_wnd 핸들 값에 해당하는 윈도우로 m_data_notify_id 메시지ID가
				// 전달되도록 비동기를 설정한다.
				WSAAsyncSelect(h_client_socket, mh_notify_wnd, m_data_notify_id, FD_READ | FD_CLOSE);
				// 새로운 사용자가 접속한 시점에 처리해야할 작업을 한다. (클래스 사용자가 직접 구현해야함. virtual)
				AddWorkForAccept(p_user);
				break;
			}
		}
		// 최대 접속자수를 초과하여 더 이상 클라이언트의 접속을 허락할 수 없는 경우
		if (i == m_max_user_count) {
			// 접속자수 초과에 대한 작업을 한다. (클래스 사용자가 직접 구현해야 함. virtual)
			ShowLimitError(temp_ip_address);
			// 접속한 소켓을 제거한다.
			closesocket(h_client_socket);
			return -2; // -2: 사용자 초과
		}
	}
	return 1; // 정상적으로 접속 처리함.
}

void ServerSocket::ProcessClientEvent(WPARAM wParam, LPARAM lParam) {
	if (WSAGETSELECTEVENT(lParam) == FD_READ) {
		ProcessRecvEvent((SOCKET)wParam); // 전송된 데이터를 분석해서 처리하는 함수 호출
	}
	else { // FD_CLOSE, 클라이언트가 접속을 해제한 경우
		UserData* p_data = FindUserData((SOCKET)wParam);
		AddWorkForCloseUser(p_data, 0);
		// 접속을 해제한 소켓을 닫고 초기화한다.
		p_data->CloseSocket(0);
	}
}

void ServerSocket::DisconnectSocket(int ah_socket, int a_error_code) {
	// 소켓 핸들을 사용하여 사용자 정보를 찾는다.
	UserData* p_user_data = FindUserData(ah_socket);
	// 접속을 해제하기 전에 작업해야 할 내용을 처리
	AddWorkForCloseUser(p_user_data, a_error_code);
	// 해당 사용자의 소켓을 닫는다.
	p_user_data->CloseSocket(1);
}

//virtual로 자식 클래스에서 함수 재정의 필요.
int ServerSocket::ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char* ap_recv_data, BS a_body_size) {
	// 소켓 핸들 값을 사용하여 이 소켓을 사용하는 사용자를 찾는다.
	UserData* p_user_data = FindUserData(ah_socket);

	if (a_msg_id == 251) { // 예약 메시지 251번은 클라이언트에 큰용량의 데이터를 전송하기 위해 사용
		char* p_send_data;
		// 현재 전송 위치를 얻는다.
		BS send_size = p_user_data->GetSendMan()->GetPosition(&p_send_data);
		// 전송할 데이터가 더 있다면 예약 메시지 번호인 252를 사용하여 클라이언트에게 데이터를 전송
		if (p_user_data->GetSendMan()->IsProcessing()) SendFrameData(ah_socket, 252, p_send_data, send_size);
		else {
			// 지금이 분할된 데이터의 마지막 부분이라면 예약 메시지 번호인 253번을 사용하여 클라이언트에게 데이터 전송
			SendFrameData(ah_socket, 253, p_send_data, send_size);
			// 마지막 데이터를 전송하고 전송에 사용했던 메모리를 삭제한다.
			p_user_data->GetSendMan()->DeleteData();
			// 서버 소켓을 사용하는 윈도우에 전송이 완료되었음을 알려준다.
			// 전송이 완료되었을때 프로그램에 어떤 표시를 하고 싶다면 해당 윈도우에서 헤더파일에 define 해놓은 LM_SEND_COMPLETED 메시지를 체크하면 된다.
			::PostMessage(mh_notify_wnd, LM_SEND_COMPLETED, (WPARAM)p_user_data, 0);
		}
	}
	else if (a_msg_id == 252) {
		// 252번은 대용량의 데이터를 수신할때 사용하는 예약된 메시지 번호
		// 수신된 데이터는 수신을 관리하는 객체로 넘겨서 데이터를 합친다.
		p_user_data->GetRecvMan()->AddData(ap_recv_data, a_body_size);
		// 252번은 아직도 추가로 수신할 데이터가 있다는 뜻이기 때문에 예약 메시지 251번을 클라이언트에 전송하여
		// 추가 데이터를 요청
		SendFrameData(ah_socket, 251, NULL, 0);
	}
	else if (a_msg_id == 253) {
		// 253번은 대용량의 데이터를 수신할때 사용하는 예약된 메시지 번호
		// 수신된 데이터는 수신을 관리하는 객체로 넘겨서 데이터를 합친다.
		p_user_data->GetRecvMan()->AddData(ap_recv_data, a_body_size);
		// 253번은 데이터 수신이 완료되었다는 메시지이기 때문에 서버 소켓을 사용하는 윈도우에 완료되었음을 알려준다.
		// 따라서 윈도우에서 수신이 완료된 데이터를 사용하려면 헤더파일에 define한 LM_RECV_COMPLETED 메시지를 사용하면 된다.
		// LM_RECV_COMPLETED 메시지를 수신한 처리기에서 수신할때 사용한 메모리를 DeleteData 함수를 호출해서 제거해야 한다.
		::PostMessageW(mh_notify_wnd, LM_RECV_COMPLETED, (WPARAM)p_user_data, 0);
	}
	// 수신된 데이터를 정상적으로 처리함. 만약, 수신 데이터를 처리하던중에 소켓을 제거했으면 0을 반환해야 한다.
	// 0을 반환하면 이소켓에 대해서 비동기 작업이 중단된다.
	return 1;
}

ClientSocket::ClientSocket(unsigned char a_valid_key,
	int a_connect_notify_id, int a_data_notify_id) : Socket(a_valid_key, a_data_notify_id)
{
	// 접속 상태를 '해제 상태'로 초기화 한다.
	m_connect_flag = 0;
	// 소켓 핸들을 초기화 한다.
	mh_socket = INVALID_SOCKET;
	// FD_CONNECT 이벤트 발생시에 사용할 윈도우 메시지 번호를 기억한다.
	m_connect_notify_id = a_connect_notify_id;
}

ClientSocket::~ClientSocket()
{
	// 서버와 통신하기 위해 소켓이 생성되어 있다면 소켓을 제거한다.
	if (mh_socket != INVALID_SOCKET) closesocket(mh_socket);
}

int ClientSocket::ConnectToServer(const wchar_t* ap_ip_address, int a_port_num, HWND ah_notify_wnd)
{
	// 접속을 시도중이거나 접속된 상태라면 접속을 시도하지 않는다.
	if (m_connect_flag != 0) return 0; // 중복 시도 또는 중복 접속 오류

	// 소켓 이벤트로 인한 윈도우 메시지를 받을 윈도우의 핸들을 저장한다.
	mh_notify_wnd = ah_notify_wnd;
	// 서버와 통신할 소켓을 생성한다. (TCP)
	mh_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in srv_addr;
	char temp_ip_address[16];
	// 유니코드 형식으로 전달된 IP 주소를 ASCII 형식으로 변경한다.
	UnicodeToAscii(temp_ip_address, (wchar_t*)ap_ip_address);
	// 서버에 접속하기 위하여 서버의 IP 주소와 포트 번호로 접속 정보를 구성
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr(temp_ip_address);
	srv_addr.sin_port = htons(a_port_num);

	// 서버에 접속하는 connect 함수가 응답없음 상태에 빠질수 있기 때문에 비동기를 설정
	// 서버 접속에 대한 결과인 FD_CONNECT 이벤트가 발생하면 ah_notify_wnd에 해당하는 윈도우로
	// m_connect_notify_id에 해당하는 윈도우 메시지를 전송한다.
	WSAAsyncSelect(mh_socket, ah_notify_wnd, m_connect_notify_id, FD_CONNECT);
	// 서버에 접속을 시도한다.
	connect(mh_socket, (sockaddr*)&srv_addr, sizeof(srv_addr));
	// 접속 상태를 '접속 시도중'으로 변경한다.
	m_connect_flag = 1;

	return 1;
}

int ClientSocket::ResultOfConnection(LPARAM lParam)
{
	if (WSAGETSELECTERROR(lParam) == 0) { // 접속 에러가 없음. 즉, 서버에 성공적으로 접속
		m_connect_flag = 2; // 접속 상태를 '접속'으로 변경
		// 접속된 소켓으로 서버에서 데이터가 수신되거나 연결이 해제되었을때 윈도우 메시지를
		// 받을수 있도록 비동기를 설정
		WSAAsyncSelect(mh_socket, mh_notify_wnd, m_data_notify_id, FD_READ | FD_CLOSE);
		return 1; // 접속 성공
	}
	else {
		// 접속 실패
		closesocket(mh_socket);		// 서버와 통신하기 위해 만든 소켓을 제거
		mh_socket = INVALID_SOCKET; // 소켓을 초기화
		m_connect_flag = 0;			// 접속 상태를 '해제'로 변경
	}
	return 0; // 접속 실패
}

int ClientSocket::ProcessServerEvent(WPARAM wParam, LPARAM lParam) 
{
	// 접속이 해제 되었을 때, 추가적인 메시지를 사용하지 않고 이 함수의 반환 값으로
	// 구별해서 사용할 수 있도록 FD_READ는 1, FD_CLOSE는 0값을 반환하도록 구현.
	int state = 1;
	if (WSAGETSELECTEVENT(lParam) == FD_READ) {
		// 서버에서 데이터를 전송한 경우 수신된 데이터를 처리하기 위한 함수를 호출
		ProcessRecvEvent((SOCKET)wParam);
	}
	else { // FD_CLOSE, 서버가 접속을 해제한 경우
		state = 0;
		m_connect_flag = 0;			// 접속 상태를 '해제'로 변경한다.
		closesocket(mh_socket);		// 서버와 통신하기 위해 생성한 소켓을 제거한다.
		mh_socket = INVALID_SOCKET;	// 소켓 핸들을 저장하는 변수를 초기화 한다.
	}
	return state; // 이벤트 종류를 반환
}

void ClientSocket::DisconnectSocket(SOCKET ah_socket, int a_error_code)
{
	// 접속 상태를 '해제'로 변경
	m_connect_flag = 0;
	LINGER temp_linger = { TRUE, 0 };
	// 서버에서 데이터를 수신하고 있는 상태라면 강제로 소켓을 제거하지 못하기 때문에
	// 링거 옵션을 설정하여 데이터를 수신하고 있더라도 소켓을 제거할 수 있도록 한다.
	setsockopt(mh_socket, SOL_SOCKET, SO_LINGER, (char*)&temp_linger, sizeof(temp_linger));
	// 소켓을 제거한다.
	closesocket(mh_socket);
	// 소켓 핸들 값을 저장하는 변수를 초기화 한다.
	mh_socket = INVALID_SOCKET;
}

int ClientSocket::SendFrameData(unsigned char a_message_id, const char* ap_body_data, BS a_body_size)
{
	return Socket::SendFrameData(mh_socket, a_message_id, ap_body_data, a_body_size);
}

int ClientSocket::ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char* ap_recv_data, BS a_body_size)
{
	if (a_msg_id == 251) {
		char* p_send_data; // 예약 메시지 251번은 서버에 큰용량의 데이터를 전송하기 위해 사용
		// 현재 전송 위치를 얻는다.
		BS send_size = m_send_man.GetPosition(&p_send_data);
		// 전송할 데이터가 더 있다면 예약 메시지 번호인 252를 사용하여 서버에게 데이터를 전송한다.
		if (m_send_man.IsProcessing()) Socket::SendFrameData(mh_socket, 252, p_send_data, send_size);
		else {
			// 지금이 분할된 데이터의 마지막 부분이라면 예약 메시지 번호인 253번을 사용하여 서버에게 데이터를 전송한다.
			Socket::SendFrameData(mh_socket, 253, p_send_data, send_size);
			// 마지막 데이터를 전송하고 전송에 사용했던 메모리를 삭제한다.
			m_send_man.DeleteData();
			// 클라이언트 소켓을 사용하는 윈도우에 전송이 완료되었음을 알려준다.
			// 전송이 완료되었을때 프로그램에 어떤 표시를 하고 싶다면 해당 윈도우에서 LM_SEND_COMPLETED 메시지를 체크하면 된다.
			::PostAppMessage(mh_notify_wnd, LM_SEND_COMPLETED, 0, 0);
		}
	}
	else if (a_msg_id == 252) {
		// 252번은 대용량의 데이터를 수신할때 사용하는 예약된 메시지 번호이다.
		// 수신된 데이터는 수신을 관리하는 객체로 넘겨서 데이터를 합친다.
		m_recv_man.AddData(ap_recv_data, a_body_size);
		// 252번은 아직도 추가로 수신할 데이터가 있다는 뜻이기 때문에 예약 메시지 251번을 서버에 전송하여
		// 추가 데이터를 요청
		Socket::SendFrameData(mh_socket, 251, NULL, 0);
	}
	else if (a_msg_id == 253) {
		// 253번은 대용량의 데이터를 수신할때 사용하는 예약된 메시지 번호이다.
		// 수신된 데이터는 수신을 관리하는 객체로 넘겨서 데이터를 합친다.
		m_recv_man.AddData(ap_recv_data, a_body_size);
		// 253번은 데이터 수신이 완료되었다는 메시지이기 때문에 클라이언트 소켓을 사용하는 윈도우에 완료되었음을 알려준다.
		// 따라서 윈도우에서 수신이 완료된 데이터를 사용하려면 LM_RECV_COMPLETED 메시지를 사용하면 된다.
		// LM_RECV_COMPLETED 메시지를 수신한 처리기에서 수신할때 사용한 메모리를 DeleteData 함수를 호출해서 제거해야한다.
		::PostMessage(mh_notify_wnd, LM_RECV_COMPLETED, 0, 0);
	}

	// 수신된 데이터를 정상적으로 처리함. 만약, 수신 데이터를 처리하던 중에 소켓을 제거했으면 0을 반환해야 한다.
	// 0을 반환하면 이 소켓에 대해서 비동기 작업이 중단된다.
	return 1;
}

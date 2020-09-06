#include "UserDB.h"
#include <stdio.h>

UserDB::UserDB() {
	MYSQL* connection = nullptr, mysql;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int query_stat;
}

UserDB::~UserDB() {
	mysql_close(connection);
}

bool UserDB::Connect() {
	mysql_init(&mysql);
	connection = mysql_real_connect(&mysql, "localhost", "root", "test", "chattingaccount", 3306, NULL, 0);
	if (connection == NULL) return false;
	return true;
}

bool UserDB::Register(HWND register_wnd, const wchar_t* id, const wchar_t* password, const wchar_t* pf_name) {
	char query[100];
	snprintf(query, sizeof(query), "insert into user value('%S', '%S', '%S')",id, password, pf_name);

	if (!IdDuCheck(register_wnd, id)) {
		query_stat = mysql_query(connection, query); // new registeration data insert.
		if (query_stat == 0) { // query extraction fail.
			return true;
		}
	}

	return false;
}

bool UserDB::Login(HWND register_wnd, const wchar_t* id, const wchar_t* password) {
	char query[100];
	snprintf(query, sizeof(query), "select * from user where id='%S' and password='%S'", id, password);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0) { // query extraction fail.
		MessageBox(register_wnd, NULL, L"query ���⿡ �����߽��ϴ�.", MB_OK);
	}
	else {
		sql_result = mysql_store_result(connection);
		if ((sql_row = mysql_fetch_row(sql_result)) != NULL) { // id�� ���� �ϳ�. (ȸ����Ͻÿ� id�� �ߺ��� ������ ����ǹǷ� while������ fetch�� ���� �ʿ� x)
			return true; // login success
		}
		else {
			MessageBox(register_wnd, NULL, L"Id �Ǵ� Password�� �߸� �Է��߽��ϴ�.", MB_OK);
		}
	}

	return false;
}

bool UserDB::IdDuCheck(HWND register_wnd, const wchar_t* id) {
	char query[100];
	snprintf(query, sizeof(query), "select * from user where id='%S'", id);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0) { // query extraction fail.
		MessageBox(register_wnd, NULL, L"query ���⿡ �����߽��ϴ�.", MB_OK);
	}
	else {
		sql_result = mysql_store_result(connection);
		if ((sql_row = mysql_fetch_row(sql_result)) != NULL) { 
			MessageBox(register_wnd, NULL, L"�ߺ��� id�Դϴ�.", MB_OK);
			return true;
		}
		else {
			MessageBox(register_wnd, NULL, L"id�� ����Ͽ��� �����ϴ�.", MB_OK);
		}
	}

	return false;
}
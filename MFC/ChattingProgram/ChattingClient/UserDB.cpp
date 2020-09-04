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

int UserDB::Login(const wchar_t* id, const wchar_t* password) {
	char query[100];
	snprintf(query, sizeof(query), "select * from user where id='%S' and password='%S'", id, password);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0) { // query extraction fail.
		return -1;
	}
	else {
		sql_result = mysql_store_result(connection);
		if ((sql_row = mysql_fetch_row(sql_result)) != NULL) { // id는 오직 하나. (회원등록시에 id는 중복이 없도록 저장되므로 while문으로 fetch를 받을 필요 x)
			return 1;
		}
		else {
			return -2; // id or password is incorrect
		}
	}

	return 0;
}

int UserDB::IdCheck(const wchar_t* id) {
	char query[100];
	snprintf(query, sizeof(query), "select * from user where id='%S'", id);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0) { // query extraction fail.
		return -1;
	}
	else {
		sql_result = mysql_store_result(connection);
		if ((sql_row = mysql_fetch_row(sql_result)) != NULL) { 
			return 1; // 중복 id
		}
		else {
			return 0; // id 사용 가능
		}
	}

	return 0;
}
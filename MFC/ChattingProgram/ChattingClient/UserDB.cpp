#include "UserDB.h"
#include <stdio.h>
#include <mysql.h>

#pragma comment(lib, "libmySQL.lib")


int UserDB::Login(const wchar_t* id, const wchar_t* password) {
	MYSQL* connection = nullptr, mysql;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int query_stat;

	mysql_init(&mysql);
	connection = mysql_real_connect(&mysql, "localhost", "root", "test", "chattingaccount", 3306, NULL, 0);

	if (connection == NULL) {
		mysql_close(connection);
		return -1;
	}
	else {
		char query[100];
		snprintf(query, sizeof(query), "select * from user where id='%S' and password='%S'", id, password);

		query_stat = mysql_query(connection, query);
		if (query_stat != 0) {
			mysql_close(connection);
			return -2;
		}
		else {
			sql_result = mysql_store_result(connection);
			if ((sql_row = mysql_fetch_row(sql_result)) != NULL) { // id는 오직 하나. (회원등록시에 id는 중복이 없도록 필터링하여 저장된다.) 
				mysql_close(connection);
				return 1;
			}
			else {
				mysql_close(connection);
				return -3;
			}
		}
	}

	mysql_close(connection);
	return 0;
}
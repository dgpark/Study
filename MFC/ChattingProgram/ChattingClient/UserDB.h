#pragma once
#include <mysql.h>

#pragma comment(lib, "libmySQL.lib")

class UserDB {
private:
	MYSQL* connection, mysql;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int query_stat;

public:
	UserDB();
	~UserDB();
	bool Connect();
	int Login(const wchar_t *id, const wchar_t *password);
	int IdCheck(const wchar_t* id);

	//void Register();
	//void setProfileName();
	//void getProfileName();
};

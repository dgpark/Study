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

	bool Register(HWND register_wnd, const wchar_t* id, const wchar_t* password, const wchar_t* pf_name);

	bool Login(HWND register_wnd, const wchar_t *id, const wchar_t *password);
	bool IdDuCheck(HWND register_wnd, const wchar_t* id);

	//void setProfileName();
	//void getProfileName();
};

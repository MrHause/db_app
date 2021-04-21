#pragma once
#include <mysql.h>
#include <string>
#include <stdlib.h>

class dataBaseAPI
{
private:
	MYSQL* conn;
	dataBaseAPI();
	//dataBaseAPI(const dataBaseAPI &){}
	~dataBaseAPI(){}
	void printConnectionError();
	bool userNameValidate(std::string name);
	bool getUserByNameAndValidePw(std::string name, std::string pw);
public:
	static dataBaseAPI & getSingleton()
	{
		static dataBaseAPI singleton;
		return singleton;
	}
	//dataBaseAPI(const char* host, const char* user, const char* password, const char* db_name, unsigned int port);
	bool db_connect(const char* host, const char* user, const char* password, const char* db_name, unsigned int port);
	bool isConnected();
	bool isUserExist(std::string name);
	bool userVerify(std::string name, std::string pw);

	void test();
};


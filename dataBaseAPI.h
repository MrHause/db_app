#pragma once
#include <mysql.h>
#include <string>
#include <stdlib.h>

class dataBaseAPI
{
private:
	typedef struct{
		std::string hashedPw;
		unsigned int salt;
	}password_t;

	MYSQL* conn;
	void printConnectionError();
	bool userNameValidate(std::string name);
	bool getUserByNameAndValidePw(std::string name, std::string pw);
	
public:
	dataBaseAPI();
	~dataBaseAPI() {}
	//dataBaseAPI(const char* host, const char* user, const char* password, const char* db_name, unsigned int port);
	bool db_connect(const char* host, const char* user, const char* password, const char* db_name, unsigned int port);
	bool isConnected();
	bool isUserExist(std::string name);
	bool userVerify(std::string name, std::string pw);

	password_t hashPassword(std::string pw);
	bool addNewUser(std::string name, std::string pw, int score);
	void test();
};


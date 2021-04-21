#define _CRT_RAND_S  
#include "dataBaseAPI.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <random>
#include "sha256.h"

dataBaseAPI::dataBaseAPI() {
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "qweasd", "testdb", 3306, NULL, 0);
}

bool dataBaseAPI::db_connect(const char* host, const char* user, const char* password, const char* db_name, unsigned int port) {
	conn = mysql_real_connect(conn, host, user, password, db_name, port, NULL, 0);
	if (conn)
		return false;
	else
		return true;
}

bool dataBaseAPI::isConnected() {
	if (conn)
		return true;
	else
		return false;
}

bool dataBaseAPI::isUserExist(std::string name) {
	//TODO przebudowaæ formê zagnie¿dzonych if
	if (isConnected()) {
		if (userNameValidate(name))
			return true;
		else
			return false;
	}
	else {
		printConnectionError();
		return false;
	}
}

void dataBaseAPI::printConnectionError() {
	puts("No connection with data base");
}

bool dataBaseAPI::userNameValidate(std::string name) {
	MYSQL_ROW row;
	MYSQL_RES* res;
	std::string query = "select * from testdb.test where name = \"" + name + "\"";
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		if (row)
			return true;
		else
			return false;
	}
}

bool dataBaseAPI::userVerify(std::string name, std::string pw) {
	if (isConnected()) {
		if ( getUserByNameAndValidePw(name, pw) )
			return true;
		else
			return false;
	}
	else {
		printConnectionError();
		return false;
	}
}

bool dataBaseAPI::getUserByNameAndValidePw(std::string name, std::string pw) {
	MYSQL_ROW row;
	MYSQL_RES* res;
	std::string query = "SELECT EXISTS (select * from testdb.test where name = \"" + name + "\"" + "AND password = \"" + pw + "\")";
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		if (row[0][0] == '1')
			return true;
		else
			return false;
	}
}

dataBaseAPI::password_t dataBaseAPI::hashPassword(std::string pw) {
	password_t type;
	std::string text;
	errno_t ret = rand_s(&type.salt);
	if (!ret) {
		text = std::to_string(type.salt);
	}
	type.hashedPw = sha256(text);
	return type;
}

bool dataBaseAPI::addNewUser(std::string name, std::string pw, int score) {
	//std::string query = "SELECT EXISTS (select * from testdb.test where name = \"" + name + "\"" + "AND password = \"" + pw + "\")";
	password_t pw_t = hashPassword(pw);
	//std::string query = "INSERT INTO testdb.test (name, score, password, salt) VALUES (\""+name + "\",\"" + std::to_string(score) + "\",\"" + pw_t.hashedPw + "\",\"" + std::to_string(pw_t.salt) +"\")";
	std::string query = "INSERT INTO testdb.test(name, score, password, salt) VALUES('" +name+ "', '" +std::to_string(score)+ "', '" + pw_t.hashedPw + "', '" + std::to_string(pw_t.salt) + "')";
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate)
		return true;
	else
		return false;
}

void dataBaseAPI::test() {
	MYSQL_ROW row;
	MYSQL_RES* res;
	int qstate = 0;
	if (conn) {
		puts("Successful connection to database!");

		std::string query = "SELECT * FROM test";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("ID: %s, Name: %s, Value: %s PW: %s\n", row[0], row[1], row[2], row[3]);
			}
		}
		else
		{
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		}
	}
	else {
		puts("Connection to database has failed!");
	}
}


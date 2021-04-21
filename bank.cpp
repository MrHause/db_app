
#include "Bank.h"

Bank::Bank(dataBaseAPI* db) {
	db_conn = db;
}

bool Bank::userLogin(std::string name, std::string pw) {
	if (db_conn->userVerify(name, pw))
		return true;
	else
		return false;
}
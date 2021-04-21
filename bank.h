#include "dataBaseAPI.h"
#include <string>
#include <stdio.h>
class Bank
{
private:
	dataBaseAPI *db_conn;
public:
	Bank(dataBaseAPI *db);
	~Bank() {};

	bool userLogin(std::string name, std::string pw);
	
	void test();
};

// MySqlTest.cpp : Defines the entry point for the console application.
//

#include <mysql.h>
#include <iostream>
#include "dataBaseAPI.h"
#include "bank.h"

int main()
{ 
	dataBaseAPI singleObject;
	singleObject.test();
	if (singleObject.isUserExist("Jimmy"))
		std::cout << "user found"<<std::endl;
	else
		std::cout << "user not found"<<std::endl;

	if( singleObject.userVerify("Jimmy", "bbb") )
		std::cout << "user ok"<<std::endl;
	else
		std::cout << "user not found"<<std::endl;

	//std::string some = singleObject.hashPassword("asdzxc123");
	if (singleObject.addNewUser("filip", "asdzxc", 1200))
		std::cout << "add correct" << std::endl;
	else
		std::cout << "error during adding" << std::endl;
	//proper app
	Bank user(&singleObject);
	if (user.userLogin("Jimmy", "bbb"))
		std::cout << "user logged as Jimmy" << std::endl;
	else
		std::cout << "user does not exist or wrong password" << std::endl;


	return 0;
}

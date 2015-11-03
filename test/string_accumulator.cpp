#include <iostream>
#include <string>

void main()
{
	std::string str;
	std::string str2 = "12345";

	std::cout << "main() start" << std::endl;

	//str << "asdf";	// error
	//str << str2;		// error

	std::cin >> str;
	std::cout << str << std::endl;
	//"asdf" >> str;		// error

	std::cin >> str;
	std::cout << str << std::endl;

}
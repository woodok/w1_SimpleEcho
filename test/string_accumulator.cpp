#include <iostream>
#include <string>

void main()
{
	std::string str;
	std::string str2 = "12345";

	std::cout << "main() start" << std::endl;

	//str << "asdf";	// error
	//str << str2;		// error

	std::cout << "put some: ";
	std::cin >> str;
	std::cout << str << std::endl;
	std::cout << "str.length(): " << str.length() << std::endl;
	//"asdf" >> str;		// error

	std::cout << "put some: ";
	std::cin >> str;		// ������ ����� ������ ���ư�
	std::cout << str << std::endl;
	std::cout << "str.length(): " << str.length() << std::endl;

}
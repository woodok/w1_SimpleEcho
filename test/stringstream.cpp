#include <iostream>
#include <sstream>
#include <string>

int main()
{
	std::stringstream ss;
	std::string str = "12345|asdfp|oiu|1022|rewq";
	const char * cstr = str.c_str();
	//const char * cstr2 = "1234";
	//const char * cstr3 = "56789";
	std::string cstr2 = "1234";
	std::string cstr3 = "56789";

	std::cout << "string: " << str << std::endl;
	std::cout << "c string: " << cstr << std::endl;

	ss << str;
	ss << cstr2;
	ss << cstr3;

	std::cout << "stringstream: " << ss.str() << std::endl;
	std::cout << "getline():" << std::endl;
	while (getline(ss, str, '|'))
		std::cout << str << std::endl;
	//std::cout << "getline():" << (getline(ss, str, '|')).str() << std::endl;	// error
	std::cout << "stringstream: " << ss.str() << std::endl;
	
	int i1 = 100;
	int i2 = 123;

	ss << i1;
	ss << i2;

	//int out;
	//ss.clear();
	//ss >> out;
	//std::cout << "int: " << out << std::endl;
	//ss >> out;
	//std::cout << "int: " << out << std::endl;
	
	//ss.clear();
	getline(ss, str, '|');
	std::cout << str << std::endl;
	//std::cout << std::stoi(str) << std::endl;

	return 0;
}

// stringstream에 operator>> 하면 push_front 일까 push_back 일까..? push back.
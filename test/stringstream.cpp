#include <iostream>
#include <sstream>
#include <string>

int main()
{
	std::stringstream ss;
	std::string str = "asdfp|oiu|1022|rewq";
	const char * cstr = str.c_str();
	const char * cstr2 = "1234";
	const char * cstr3 = "56789";

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



}

#include <iostream>
#include <sstream>
#include <cstring>

int main()
{
	char buf[10];
	strcpy_s(buf, "012345678");

	std::stringstream ss;
	ss << buf;
	std::cout << ss.str() << std::endl;

	ss.str(std::string());
	ss.clear();

	strcpy_s(buf, "asdf");
	ss << buf;
	std::cout << ss.str() << std::endl;

	return 0;
}
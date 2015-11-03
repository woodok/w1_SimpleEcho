#include <iostream>
#include <sstream>
#include <string>

int main()
{
	std::stringstream ss;
	ss << "12345";

	int strlen = ss.str().length();

	return 0;
}
#include <iostream>
#include <string>
#include <algorithm>

int main(void)
{
	std::cout << "main() start" << std::endl;

	std::string str = "|asimef|1n290qwe|nefj19|";

	std::cout << "original string:" << str << std::endl;
	std::replace(str.begin(), str.end(), '|', ' ');
	std::cout << "new string:" << str << std::endl;

	std::cout << "main() end" << std::endl;
	return 0;
}
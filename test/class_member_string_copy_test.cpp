#include <iostream>
#include <string>

class Test
{
public:
	std::string str;

public:
	Test(std::string _str)
	{
		str = _str;
		std::cout << "Test object created" << std::endl;
	}
	Test(const Test& _test)
	{
		str = _test.str;
		std::cout << "Test object created" << std::endl;
	}
};

int main()
{
	std::cout << "main() start" << std::endl;

	Test orig("Test1");
	Test copy(orig);

	std::cout << orig.str << std::endl;
	std::cout << copy.str << std::endl;

	orig.str += " edited";

	std::cout << orig.str << std::endl;
	std::cout << copy.str << std::endl;

	std::cout << "main() end" << std::endl;

	return 0;
}
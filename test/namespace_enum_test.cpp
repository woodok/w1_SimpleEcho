#include<iostream>

namespace AAA
{
	namespace BBB
	{
		enum {
			CONST_A = 1,
			CONST_B = 10,
			CONST_C = 22
		};
	}
}

void func_int(int _input)
{
	std::cout << "func_int(" << _input << ") " << std::endl;
}

int main()
{
	std::cout << "AAA::BBB::CONST_A: " << AAA::BBB::CONST_A << std::endl;
	func_int(AAA::BBB::CONST_C);

	return 0;
}
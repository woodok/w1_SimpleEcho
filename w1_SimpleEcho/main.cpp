#include "header.h"

int main(void)
{
	std::cout << "main() start" << std::endl << std::endl;

	UserInfoList ul;
	RoomInfoList rl;

	ul.add("man", INVALID_HANDLE_VALUE);
	ul.add("hama", INVALID_HANDLE_VALUE);
	ul.add("hoho1", INVALID_HANDLE_VALUE);
	ul.add("hoho2", INVALID_HANDLE_VALUE);
	ul.add("hoho3", INVALID_HANDLE_VALUE);

	std::cout << "now find value.." << std::endl;

	int key = 1;

	std::cout << ul.head[0]->get_key() << std::endl;
	std::vector<UserInfo *>::iterator it;

	try {
		it = ul.find(1);
	} 
	catch (std::exception e)
	{
		std::cout << "error occured" << std::endl;
		std::cerr << e.what() << std::endl;
	}

	std::cout << "find value successfully" << std::endl;

	if (it == ul.head.end())
		std::cout << "There is no key" << std::endl;
	else
		std::cout << "key: " << (*it)->get_key() << std::endl;

	std::cout << **it << std::endl;
	std::cout << "ul.print(2):" << std::endl;
	ul.print(2);

	ul.print();


	std::cout << std::endl << "main() end" << std::endl;
}
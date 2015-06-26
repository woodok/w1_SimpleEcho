#include "../w1_SimpleEcho/header.h"

int main()
{
	
	std::list<RoomInfo *> rList;
	rList.push_back(new RoomInfo());
	rList.push_back(new RoomInfo("room2"));
	
	std::list<RoomInfo>::iterator it;
	std::cout << "main() called successfully" << std::endl;

	//RoomInfo rm1("title");
	//RoomInfo rm2("tititle");

	//std::cout << "rm1 == rm2 : " << (rm1 == rm2) << std::endl;
	//rm1.key = rm2.key;
	//std::cout << "rm1 == rm2 : " << (rm1 == rm2) << std::endl;
	//std::cout << rm1.title << std::endl;


}
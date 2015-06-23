#include "../w1_SimpleEcho/header.h"

int main()
{
	std::list<RoomInfo *> rList;
	rList.push_back(new RoomInfo());
	rList.push_back(new RoomInfo("room2"));
	
	std::list<RoomInfo>::iterator it;


}
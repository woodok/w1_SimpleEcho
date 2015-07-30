#include "functions.h"

void Buffer::operator<< (const UserInfo& ui)
{
	data += ui.key;
	data += '|';
	data += ui.id;
	data += '|';
	//data += static_cast<std::string>((ui.hSocket));
	//data += '|';
	data += ui.roomNumber;
	data += '|';
}
void Buffer::operator<< (const RoomInfo& ri)
{
	data += ri.key;
	data += ri.title;
}
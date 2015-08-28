#include "clntHeader.h"

UInfo::UInfo()
{
	uKey = USER_INFO::DEFAULT_USER_KEY;
	status = USER_INFO::STATUS_NOT_READY;
}
UInfo::UInfo(UserKey _uKey, std::string&& _userNick, int _status)
{
	uKey = _uKey;
	userNick = _userNick;
	status = _status;
}
RInfo::RInfo()
{
	rKey = ROOM_INFO::DEFAULT_ROOM_KEY;
	curNumPart = 0;
}
RInfo::RInfo(RoomKey _rKey, std::string&& _rTitle, int _curNumPart)
{
	rKey = _rKey;
	rTitle = _rTitle;
	curNumPart = _curNumPart;
}

ClientFSM::ClientFSM() : state(ClientFSM::STATE_LOGIN) {};
void ClientFSM::start()
{

}
void ClientFSM::running()
{
	while (true)
	{
		switch (state)
		{
		case STATE_LOGIN:
			Login::display();
			//rev

			state = STATE_LOBBY;
			break;
		case STATE_LOBBY:

			break;
		case STATE_CREATINGROOM:

			break;
		case STATE_CHATTING:

			break;
		case STATE_QUIT:

			break;
		}
	}
}
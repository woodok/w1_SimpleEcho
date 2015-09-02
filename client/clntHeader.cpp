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
UInfo::UInfo(const UInfo& _uInfo)
{
	uKey = _uInfo.uKey;
	userNick = _uInfo.userNick;
	status = _uInfo.status;
}
UInfo::UInfo(UInfo&& _uInfo)
{
	//rev
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
RInfo::RInfo(const RInfo& _rInfo)
{
	rKey = _rInfo.rKey;
	rTitle = _rInfo.rTitle;
	curNumPart = _rInfo.curNumPart;
}
RInfo::RInfo(RInfo&& _rInfo)
{
	//rev
}

Buffer::Buffer()
{
	uList.reserve(100);
	rList.reserve(100);
}

void decoding(std::stringstream&& origSs, Buffer& decodedBuf)
{
	int ssLen;
	std::string temp;
	getline(origSs, temp, '|');
	ssLen = stoi(temp);
	getline(origSs, temp, '|');
	decodedBuf.state = stoi(temp);
	switch (decodedBuf.state) {
	case PROTOCOL::Client::State::LOGIN:
		//rev stringstream 예제 만들어서 테스트해보기.

		break;
	case PROTOCOL::Client::State::LOBBY:

		break; 
	case PROTOCOL::Client::State::CREATE_ROOM:

			break;
	case PROTOCOL::Client::State::CHATTING:
		
		break;
	
	}
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
#include "clntHeader.h"

UInfo::UInfo()
{
	uKey = USER_INFO::DEFAULT_USER_KEY;
	status = USER_INFO::STATUS_NOT_READY;
}
UInfo::UInfo(std::string _uKey, std::string&& _userNick, std::string _status)
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
}
RInfo::RInfo(std::string _rKey, std::string&& _rTitle, std::string _curNumPart)
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

//  
//
void stateDistinguisher(const ConnectionInfo& conInfo, int& state, int& msgLen)
{
	char buf[MYCONST::BUF_SIZE];
	recv(conInfo.hSocket, buf, MYCONST::BUF_SIZE - 1, 0);
	/*strLen = strbuf.size();
	send(hSocket, strbuf.c_str(), strLen, 0);
	readLen = 0;
	while (1)
	{
		readLen += recv(hSocket, &message[readLen], BUF_SIZE - 1, 0);
		if (readLen >= strLen)
			break;
	}
	message[strLen] = 0;*/

}

void decoding(std::stringstream& origSs, Buffer& decodedBuf)
{
	int ssLen;
	std::string temp;
	getline(origSs, temp, '|');
	ssLen = stoi(temp);
	getline(origSs, temp, '|');
	decodedBuf.state = stoi(temp);
	switch (decodedBuf.state) {
	case PROTOCOL::State::LOGIN:
		//rev stringstream 예제 만들어서 테스트해보기.

		break;
	case PROTOCOL::State::LOBBY:

		break; 
	case PROTOCOL::State::CREATE_ROOM:

		break;
	case PROTOCOL::State::CHATTING:
		
		break;
	
	}
}
// ClassFSM 필요 없을 듯..
//ClientFSM::ClientFSM() : state(ClientFSM::STATE_LOGIN) {};
//void ClientFSM::init()
//{
//	state = STATE_LOGIN;
//
//}
//void ClientFSM::running()
//{
//	Buffer data;
//	std::stringstream rcvSs;
//	char cbuf[MYCONST::BUF_SIZE];
//
//	while (true)
//	{
//		switch (state)
//		{
//		case STATE_LOGIN:
//			//Login::display();
//			//rev
//
//			state = STATE_LOBBY;
//			break;
//		case STATE_LOBBY:
//
//			break;
//		case STATE_CREATINGROOM:
//
//			break;
//		case STATE_CHATTING:
//
//			break;
//		case STATE_QUIT:
//
//			break;
//		}
//	}
//}
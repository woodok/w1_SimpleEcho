#include "clntHeader.h"


void proc_lobby(std::stringstream& ss, int _state, bool& _exitFlag)
{
	// display lobby
	//		show gameroom list
	//		Display menu
	//		Take menu number and Do it
	//
	//		show gameroom list. 
	while (1) {
		recv(hSock, cbuf, BUF_SIZE - 1, 0);
		reset_sstream(ssbuf);		// reset sstream
		ssbuf << cbuf;
		std::getline(ssbuf, sbuf, '|');
		if (std::stoi(sbuf) == PROTOCOL::Server::Lobby::DATA_READY) {
			std::getline(ssbuf, sbuf, '|');
			msglen = std::stoi(sbuf);
		}
	}

	//send(hSock, )		//rev
	std::cout << std::endl << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << "Load room list.." << std::endl;
	std::cout << "Room list" << std::endl;
	std::cout << "Room#\t\t" << "Title\t\t" << "current people\t\t" << "Room status" << std::endl;

}
void proc_createRoom(std::stringstream& ss, int _state, bool& _exitFlag)
{

}
void proc_chatting(std::stringstream& ss, int _state, bool& _exitFlag)
{

}

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

ToClntBuffer::ToClntBuffer()
{
	uList.reserve(100);
	rList.reserve(100);
}
int receiving(const ConnectionInfo& conInfo, ToClntBuffer& clntBuf, std::stringstream& ssBuf)
{
	//rev
	// hand shaking (msg length check) 부터..
	// receiving은 server side와 client side로 각각 구현해야할까..?
	// hand shaking 이 필요한 state를 추려내기 -> server side 와 client side 가 다를 수 있음
	// state 판정 -> 판정 결과에 따라 switch 하여 hand shaking 있는 경우, 없는 경우로 나뉨..
	char 
	return 0;
}
int sending(const ConnectionInfo& conInfo, const std::stringstream& ssBuf)
{

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

void decoding(std::stringstream& origSs, ToClntBuffer& decodedBuf)
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
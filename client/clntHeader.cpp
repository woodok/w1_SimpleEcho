#include "clntHeader.h"

// display lobby
//		show gameroom list
//		Display menu
//		Take menu number and Do it
//
//		show gameroom list. 
void proc_lobby(std::stringstream& _ssbuf, const SOCKET _hSock, int _state, bool& _exitFlag)
{
	char cbuf[MYCONST::BUF_SIZE];
	std::string sbuf;
	int msglen;
	int recvlen;

	switch (_state)
	{
	case PROTOCOL::Server::Lobby::INIT:
		reset_sstream(_ssbuf);
		_ssbuf << PROTOCOL::Client::Lobby::LOAD_LIST << '|';
		sbuf = _ssbuf.str();
		send(_hSock, sbuf.c_str(), sbuf.length(), 0);

		recv(_hSock, cbuf, MYCONST::BUF_SIZE - 1, 0);
		reset_sstream(_ssbuf);
		_ssbuf << cbuf;
		std::getline(_ssbuf, sbuf, '|');
		_state = std::stoi(sbuf);
		break;
	case PROTOCOL::Server::Lobby::DATA_READY:
		std::getline(_ssbuf, sbuf, '|');	// _ssbuf deserializing
		msglen = std::stoi(sbuf);		// get msglen from _ssbuf
		reset_sstream(_ssbuf);
		_ssbuf << PROTOCOL::Client::Lobby::CONFIRMED << '|';
		sbuf = _ssbuf.str();
		send(_hSock, sbuf.c_str(), sbuf.length, 0);
		
		reset_sstream(_ssbuf);
		while (recvlen < msglen) {
			recvlen += recv(_hSock, cbuf, MYCONST::BUF_SIZE, 0);
			_ssbuf << cbuf;
		}

		std::cout << std::endl << std::endl;
		std::cout << "========================================" << std::endl;
		std::cout << "Load room list.." << std::endl;
		std::cout << "Room list" << std::endl;
		std::cout << "Room#\t\t" << "Title\t\t" << "current people\t\t" << "Room status" << std::endl;
	
		int lineChange = 0;
		while (std::getline(_ssbuf, sbuf, '|')) {
			std::cout << sbuf << "\t\t";
			lineChange++;
			if ((lineChange %= 4) == 0)
				std::cout << std::endl;			
		}

		// Room list print completed. Now waiting for user's choice.
		int menuSel = 0;
		bool menuExitFlag = true;
		do {
			std::cout << "Select menu? 1) Join room   2) Create new room   3) Reload list   0) Quit" << std::endl;
			std::cout << ">> " << std::endl;
			std::cin >> menuSel;
			switch (menuSel) {
			case 1:
				//rev Join room 선택한 경우 이후 과정. 방번호 물어보고 이를 서버에 전송

				break;
			case 2:
				_state = PROTOCOL::Server::CreateRoom::INIT;
				break;
			case 3:
				_state = PROTOCOL::Server::Lobby::INIT;
				break;
			case 0:
				std::cout << "Choose to exit." << std::endl;
				_exitFlag = true;
				break;
			default:
				std::cout << "Wrong input. Try again." << std::endl;
				menuExitFlag = false;
				break;
			}
		} while (!menuExitFlag);
		
		break;		
	case PROTOCOL::Server::Lobby::CREATE_ROOM_OK:
		_state = PROTOCOL::Server::CreateRoom::INIT;
		break;
	case PROTOCOL::Server::Lobby::JOIN_ROOM_OK:
		_state = PROTOCOL::Server::Chatting::INIT;
		break;
	case PROTOCOL::Server::Lobby::CREATE_ROOM_FAIL:		
		std::cout << "Create room failed." << std::endl;
		std::cout << "Get back to lobby.." << std::endl;
		_state = PROTOCOL::Server::Lobby::INIT;
		break;
	case PROTOCOL::Server::Lobby::JOIN_ROOM_FAIL:		
		std::cout << "Join room failed." << std::endl;
		_state = PROTOCOL::Server::Lobby::INIT;
		break;
	case PROTOCOL::Server::Lobby::LOAD_LIST:	
		//rev 이건 필요 없을 듯..
		break;
	}

	while (1) {
		recv(_hSock, cbuf, MYCONST::BUF_SIZE - 1, 0);
		reset_sstream(_ssbuf);		// reset sstream
		_ssbuf << cbuf;
		std::getline(_ssbuf, sbuf, '|');
		if (std::stoi(sbuf) == PROTOCOL::Server::Lobby::DATA_READY) {
			std::getline(_ssbuf, sbuf, '|');
			msglen = std::stoi(sbuf);
		}
	}
}
void proc_createRoom(std::stringstream& ss, SOCKET hSock, int _state, bool& _exitFlag)
{

}
void proc_chatting(std::stringstream& ss, SOCKET hSock, int _state, bool& _exitFlag)
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
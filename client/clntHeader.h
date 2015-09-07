
#ifndef __CLNTHEADER_H_
#define __CLNTHEADER_H_

#include "../w1_SimpleEcho/header.h"
#include "../w1_SimpleEcho/protocol.h"

typedef struct UInfo
{
	std::string uKey;		// userkey
	std::string userNick;	// user's nick name
	std::string status;		// user's ready/not ready status in room
	
	UInfo();
	UInfo(std::string _uKey, std::string&& _userNick, std::string _status);
	UInfo(const UInfo& _uInfo);		// copy constructor
	UInfo(UInfo&& _uInfo);		// move constructor
} UInfo;
typedef struct RInfo
{
	std::string rKey;		// room key
	std::string rTitle;		// room title
	std::string curNumPart;	// number of current participants to the room
	
	RInfo();
	RInfo(std::string _rKey, std::string&& _rTitle, std::string _curNumPart);
	RInfo(const RInfo& _rInfo);		// copy constructor
	RInfo(RInfo&& _rInfo);		// move constructor
} RInfo;

typedef struct Buffer
{
public:
	int state;
	int packetType;
	std::string userNick;
	UserKey uKey;
	RoomKey rKey;
	std::vector<UInfo> uList;
	std::vector<RInfo> rList;
	std::string chat;
	
public:
	Buffer();
} Buffer;
//namespace client
//{
//	void LoginProcess();
//	void LobbyProcess();
//	void CreatingRoomProcess();
//	void ChattingProcess();
//
//	void displayLogin();
//	void displayLobby(std::stringstream&& _ss);
//	void displayCreatingRoom();
//	void displayChatting();
//
//
//	void login()
//	{
//		std::cout << "--------------------------------------" << std::endl;
//		std::cout << "Please put your nickname: " << std::endl;
//		//std::cin >> nickbuf;
//	}
//}

void decoding(std::stringstream&& origSs, Buffer& decodedBuf);		//rev 

//?? class FSM�� ������ ����ϴ°�..?
//		�������̽� ����ϰ�.
class ClientFSM
{
	enum {
		STATE_LOGIN,
		STATE_LOBBY,
		STATE_CREATINGROOM,
		STATE_CHATTING,
		STATE_QUIT
	};
private:
	int state;
public:
	ClientFSM();
	void init();
	void running();
	
	
};

////?? �̷��� ��ġ�°� ������ 
////		class State�� ������ ����ϴ°�..?
////		�׸��� �������̽� ���
//class Login
//{
//private:
//public:
//	static void display();
//
//};
//class Lobby
//{
//private:
//public:
//	static void display();
//
//};
//class CreatingRoom
//{
//private:
//public:
//	static void display();
//
//};
//class Chatting
//{
//private:
//public:
//	static void display();
//
//};
//class Quit
//{
//private:
//public:
//	static void display();
//
//};


#endif // !__CLNTHEADER_H_
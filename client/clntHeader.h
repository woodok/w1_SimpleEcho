
#ifndef __CLNTHEADER_H_
#define __CLNTHEADER_H_

#include "../w1_SimpleEcho/header.h"

typedef struct UInfo
{
	UserKey uKey;			// userkey
	std::string userNick;	// user's nick name
	int status;				// user's ready/not ready status in room
	
	UInfo();
	UInfo(UserKey _uKey, std::string&& _userNick, int _status);
	UInfo(const UInfo& _uInfo);		// copy constructor
	UInfo(UInfo&& _uInfo);		// move constructor
} UInfo;
typedef struct RInfo
{
	RoomKey rKey;		// room key
	std::string rTitle;	// room title
	int curNumPart;		// number of current participants to the room
	
	RInfo();
	RInfo(RoomKey _rKey, std::string&& _rTitle, int _curNumPart);
	RInfo(const RInfo& _rInfo);		// copy constructor
	RInfo(RInfo&& _rInfo);		// move constructor
} RInfo;

typedef struct Buffer
{
	int state;
	int packetType;
	std::string userNick;
	UserKey uKey;
	RoomKey rKey;
	std::vector<UInfo> uList;
	std::vector<RInfo> rLIst;
	std::string chat;
	
	//Buffer();		// 없어도 될 듯..
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

void decoding()		//rev 
{}

//?? class FSM을 정의해 상속하는건..?
//		인터페이스 사용하고.
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
	void start();
	void running();
	
	
};

//?? 이렇게 겹치는게 많으니 
//		class State를 정의해 상속하는건..?
//		그리고 인터페이스 사용
class Login
{
private:
public:
	static void display();

};
class Lobby
{
private:
public:
	static void display();

};
class CreatingRoom
{
private:
public:
	static void display();

};
class Chatting
{
private:
public:
	static void display();

};
class Quit
{
private:
public:
	static void display();

};


#endif // !__CLNTHEADER_H_
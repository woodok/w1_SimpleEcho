
#ifndef __CLNTHEADER_H_
#define __CLNTHEADER_H_

#include "../w1_SimpleEcho/header.h"

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
	void start();
	void running();
	
	
};

//?? �̷��� ��ġ�°� ������ 
//		class State�� ������ ����ϴ°�..?
//		�׸��� �������̽� ���
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
//466p, 515p 참조

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <Windows.h>
#include <process.h>

#include "clntHeader.h"

#define BUF_SIZE 100
#define NAME_SIZE 20

unsigned WINAPI SendMsg(void * arg);
unsigned WINAPI RecvMsg(void * arg);
void ErrorHandling(char * msg);

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];

// Global variables for thread
std::string sbuf;
std::stringstream ssbuf;
int msglen = 0;
int state = 0;
bool exitFlag = false;

int main(int argc, char * argv[])
{
	WSADATA wsaData;
	SOCKET hSock;
	SOCKADDR_IN servAdr;
	HANDLE hSndThread, hRcvThread;
	char cbuf[BUF_SIZE];

	if (argc != 4) {
		printf("Usage: %s <IP> <port> <name>\n", argv[0]);
		exit(1);
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");

	sprintf(name, "[%s]", argv[3]);
	hSock = socket(PF_INET, SOCK_STREAM, 0);
	puts("socket() ok");

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr(argv[1]);
	servAdr.sin_port = htons(atoi(argv[2]));

	if (connect(hSock, (SOCKADDR *)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("connect() error");
	puts("connect() ok");

	// Login stage
	//		get nickname
	//		serialization
	//		send file
	//		
	//		get nickname
	std::cout << std::endl << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << "New guest connected." << std::endl;
	while (1) {
		std::string nick;
		int servConfirmed;
		std::cout << "Put your nickname: " << std::endl;
		std::cin >> nick;
		//		serialization
		ssbuf << PROTOCOL::Client::Login::LOGIN << '|' << nick << '|';
		//		send file
		sbuf = ssbuf.str();
		send(hSock, sbuf.c_str(), sbuf.length(), 0);
		//		earning server confirm
		recv(hSock, cbuf, BUF_SIZE - 1, 0);
		reset_sstream(ssbuf);	// reset sstream
		ssbuf << cbuf;
		std::getline(ssbuf, sbuf, '|');
		servConfirmed = std::stoi(sbuf);
		if (servConfirmed == PROTOCOL::Server::Login::LOGIN_OK) {
			break;
		}
		std::cout << "The nickname was not accepted. Try new nickname" << std::endl;
	}

	reset_sstream(ssbuf);
	ssbuf << PROTOCOL::Client::Lobby::LOAD_LIST << '|';
	sbuf = ssbuf.str();
	send(hSock, sbuf.c_str(), sbuf.length(), 0);

	recv(hSock, cbuf, BUF_SIZE - 1, 0);
	reset_sstream(ssbuf);
	ssbuf << cbuf;
	std::getline(ssbuf, sbuf, '|');
	state = std::stoi(sbuf);

	// Wrap up process		//rev
	//

	// CreatingRoom stage
	//		Take title of the new room
	std::cout << std::endl << std::endl;
	
	// Chatting stage
	//		Chatting
	//		Taking menu operations.
	std::cout << std::endl << std::endl;


	//
	hSndThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void *)&hSock, 0, NULL);
	hRcvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void *)&hSock, 0, NULL);
	puts("thread creation ok");
	puts("All things set. You go.");

	WaitForSingleObject(hSndThread, INFINITE);
	WaitForSingleObject(hRcvThread, INFINITE);

	closesocket(hSock);
	WSACleanup();
	return 0;
}

unsigned WINAPI SendMsg(void * arg)
{
	SOCKET hSock = *((SOCKET *)arg);
	char nameMsg[NAME_SIZE + BUF_SIZE];
	while (1)
	{
		fgets(msg, BUF_SIZE, stdin);
		if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
		{
			closesocket(hSock);
			exit(0);
		}
		sprintf(nameMsg, "%s %s", name, msg);
		send(hSock, nameMsg, strlen(nameMsg), 0);
	}
	return 0;
}

unsigned WINAPI RecvMsg(void * arg)
{
	int hSock = *((SOCKET*)arg);
	char nameMsg[NAME_SIZE + BUF_SIZE];
	int strLen;

	// State machine
	//		distribute state
	//
	while (1)
	{
		//rev 각 proc_%%% 작업 중.. 접속 정보를 어떻게 넘겨줄 것인가?
		if (state > PROTOCOL::Client::Lobby::NO_MEANING_FIRST && state < PROTOCOL::Client::Lobby::NO_MEANING_LAST) {
			proc_lobby(ssbuf, hSock, state, exitFlag);
		}
		else if (state > PROTOCOL::Client::CreateRoom::NO_MEANING_FIRST && state < PROTOCOL::Client::CreateRoom::NO_MEANING_LAST) {
			proc_createRoom(ssbuf, hSock, state, exitFlag);
		}
		else if (state > PROTOCOL::Client::Chatting::NO_MEANING_FIRST && state < PROTOCOL::Client::Chatting::NO_MEANING_LAST){
			proc_chatting(ssbuf, hSock, state, exitFlag);
		}
		else {
			std::cout << "Error occred: unexpected type of message received." << std::endl;
			std::cout << "Client close" << std::endl;
			break;
		}
		if (exitFlag == true)
		{
			std::cout << "quit game.." << std::endl;
			break;
		}
	}

	/*while (1)
	{
		strLen = recv(hSock, nameMsg, NAME_SIZE + BUF_SIZE - 1, 0);
		if (strLen == -1)
			return -1;
		nameMsg[strLen] = 0;
		fputs(nameMsg, stdout);
	}*/

	return 0;
}

void ErrorHandling(char * msg)
{
	fputs(msg, stderr);
	putc('\n', stderr);
	exit(0);
}
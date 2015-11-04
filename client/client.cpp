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
	std::string nick;
	std::stringstream ssbuf;
	int servConfirmed;
	std::cout << std::endl << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << "New guest connected." << std::endl;
	while (1) {
		std::cout << "Put your nickname: " << std::endl;
		std::cin >> nick;
		//		serialization
		//buf = PROTOCOL::Client::Login::LOGIN + '|' + nick + '|';		//rev error. why??
		ssbuf << PROTOCOL::Client::Login::LOGIN << '|' << nick << '|';
		//		send file
		int buflen = ssbuf.str().length();
		send(hSock, ssbuf.str().c_str(), buflen, 0);
		recv(hSock, cbuf, BUF_SIZE - 1, 0);
		ssbuf << cbuf;
		servConfirmed = std::stoi(ssbuf.str());		//rev getline() 먼저 사용
		if (servConfirmed == PROTOCOL::Server::Login::LOGIN_OK) {
			break;
		}
		std::cout << "The nickname was not accepted. Try new nickname" << std::endl;
	}

	// Lobby stage
	//		show gameroom list
	//		Display menu
	//		Take menu number and Do it
	//
	//?? stringstream 초기화 하는 방법..?
	//?? cbuf에 여러번 받아올 시 cbuf 초기화 없이 그냥 계속 써도 되나..?
	send(hSock, )
	std::cout << std::endl << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << "Load room list.." << std::endl;
	std::cout << "Room list" << std::endl;
	std::cout << "Room#\t\t" << "Title\t\t" << "current people\t\t" << "Room status" << std::endl;




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
	while (1)
	{
		strLen = recv(hSock, nameMsg, NAME_SIZE + BUF_SIZE - 1, 0);
		if (strLen == -1)
			return -1;
		nameMsg[strLen] = 0;
		fputs(nameMsg, stdout);
	}
	return 0;
}

void ErrorHandling(char * msg)
{
	fputs(msg, stderr);
	putc('\n', stderr);
	exit(0);
}
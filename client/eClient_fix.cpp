#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <WinSock2.h>
#include "clntHeader.h"

#include "../w1_SimpleEcho/header.h"

//#define BUF_SIZE 1024
void ErrorHandling(char * message);

int main()
{
	/*WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAdr;*/		//rev conInfo 안으로 다 들어감
	ConnectionInfo conInfo;
	//char message[BUF_SIZE];		//rev 앞으로 코드에서 나오는 부분 모두 수정
	int strLen, readLen;

	bool flagExit = false;
	int state;
	char cbuf[MYCONST::BUF_SIZE];
	Buffer recvBuf;

	if (WSAStartup(MAKEWORD(2, 2), &conInfo.wsaData) != 0)
		ErrorHandling("WSAStartup() error");

	conInfo.hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (conInfo.hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&(conInfo.servAdr), 0, sizeof(conInfo.servAdr));		//? 함수 안에 들어가는걸 이렇게 써도 되나..?
	conInfo.servAdr.sin_family = AF_INET;
	conInfo.servAdr.sin_addr.s_addr = inet_addr(server_address);
	//servAdr.sin_addr.s_addr = inetPton(argv[1]);
	conInfo.servAdr.sin_port = htons(atoi(server_port));

	if (connect(conInfo.hSocket, (SOCKADDR *)&(conInfo.servAdr), sizeof(conInfo.servAdr)) == SOCKET_ERROR)	//? 함수 안에 들어가는걸 이렇게 써도 되나..?
		ErrorHandling("connect() error");
	else
		puts("Connected..........");

	//rev 
	// state machine 
	while (flagExit != false)
	{


	}



	// close connection & wrap-up
	closesocket(hSocket);
	WSACleanup();
	return 0;
}

void ErrorHandling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
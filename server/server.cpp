#include <cstdio>
#include <cstdlib>
#include <process.h>
#include <WinSock2.h>
#include <Windows.h>

#include <iostream>
#include <sstream>
#include <string>

#include "servHeader.h"
#include "../w1_SimpleEcho/protocol.h"

#define BUF_SIZE 100
#define READ 3
#define WRITE 5

typedef struct		// socket info
{
	SOCKET hClntSock;
	SOCKADDR_IN clntAdr;
} PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

typedef struct		// bufferinfo
{
	OVERLAPPED overlapped;
	WSABUF wsaBuf;
	char buffer[BUF_SIZE];
	int rwMode;
} PER_IO_DATA, *LPPER_IO_DATA;

DWORD WINAPI EchoThreadMain(LPVOID CompletionPortIO);
void ErrorHandling(char * message);

UserInfoList ul;
RoomInfoList ri;

int main(int argc, char * argv[])
{
	WSADATA wsaData;
	HANDLE hComPort;
	SYSTEM_INFO sysInfo;
	LPPER_IO_DATA ioInfo;
	LPPER_HANDLE_DATA handleInfo;

	SOCKET hServSock;
	SOCKADDR_IN servAdr;
	int recvBytes, i, flags = 0;

	//if (argc != 2) {
	//	printf("Usage : %s <port>\n", argv[0]);
	//	exit(1);
	//}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");

	hComPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	GetSystemInfo(&sysInfo);
	for (i = 0; i < sysInfo.dwNumberOfProcessors; i++)
		_beginthreadex(NULL, 0, (unsigned(__stdcall *)(void*))EchoThreadMain, (LPVOID)hComPort, 0, NULL);
	puts("thread creation ok");

	hServSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	//servAdr.sin_port = htons(atoi(argv[1]));
	servAdr.sin_port = htons(atoi("9190"));
	puts("socket() ok");

	bind(hServSock, (SOCKADDR *)&servAdr, sizeof(servAdr));
	puts("bind() ok");
	listen(hServSock, 5);
	puts("listen() ok");

	puts("All things set.");

	while (1)
	{
		SOCKET hClntSock;
		SOCKADDR_IN clntAdr;
		int addrLen = sizeof(clntAdr);
		hClntSock = accept(hServSock, (SOCKADDR *)&clntAdr, &addrLen);
		handleInfo = (LPPER_HANDLE_DATA)malloc(sizeof(PER_HANDLE_DATA));
		handleInfo->hClntSock = hClntSock;
		memcpy(&(handleInfo->clntAdr), &clntAdr, addrLen);

		CreateIoCompletionPort((HANDLE)hClntSock, hComPort, (DWORD)handleInfo, 0);

		ioInfo = (LPPER_IO_DATA)malloc(sizeof(PER_IO_DATA));
		memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
		ioInfo->wsaBuf.len = BUF_SIZE;
		ioInfo->wsaBuf.buf = ioInfo->buffer;
		ioInfo->rwMode = READ;
		WSARecv(handleInfo->hClntSock, &(ioInfo->wsaBuf), 1, (LPDWORD)&recvBytes, (LPDWORD)&flags, &(ioInfo->overlapped), NULL);
	}
	return 0;
}

DWORD WINAPI EchoThreadMain(LPVOID pComPort)
{
	HANDLE hComPort = (HANDLE)pComPort;
	SOCKET sock;
	DWORD bytesTrans;
	LPPER_HANDLE_DATA handleInfo;
	LPPER_IO_DATA ioInfo;
	DWORD flags = 0;

	while (1)
	{
		GetQueuedCompletionStatus(hComPort, &bytesTrans, (LPDWORD)&handleInfo, (LPOVERLAPPED *)&ioInfo, INFINITE);
		sock = handleInfo->hClntSock;

		if (ioInfo->rwMode == READ)	
		{
			puts("message received.");
			if (bytesTrans == 0)		// EOF 전송 시
			{
				closesocket(sock);
				free(handleInfo); free(ioInfo);
				continue;
			}
			
			//
			// client 에서 받은 메시지 deserialize process

			// 실험
			//std::string str;
			//std::stringstream ss("");
			//ss << ioInfo->buffer;		// 이상한 값까지 같이 찍혀나옴. buffer 안에 있는 값을 string 만큼만 복사하는게 아니라 전부 다집어넣는 듯..

			std::string tmpStr;
			std::stringstream tmpSs;
			tmpSs << ioInfo->buffer;

			std::getline(tmpSs, tmpStr, '|');
			int msgType = std::stoi(tmpStr);

			switch (msgType) {
			case PROTOCOL::Client::Login::LOGIN:
				std::getline(tmpSs, tmpStr, '|');
				ul.add(tmpStr, handleInfo->hClntSock);
				break;
			case PROTOCOL::Client::Lobby::CONFIRMED:	break;
			case PROTOCOL::Client::Lobby::LOAD_LIST:

				break;
			case PROTOCOL::Client::Lobby::JOIN_ROOM:

				break;
			case PROTOCOL::Client::CreateRoom::CONFIRMED:	break;
			case PROTOCOL::Client::CreateRoom::CREATE_ROOM:

				break;
			case PROTOCOL::Client::Chatting::CONFIRMED:	break;
			case PROTOCOL::Client::Chatting::QUIT_ROOM:

				break;
			case PROTOCOL::Client::Chatting::MY_STATE_READY:

				break;
			case PROTOCOL::Client::Chatting::MY_STATE_NOT_READY:

				break;
			case PROTOCOL::Client::Chatting::ROOM_STATE_PLAYING:

				break;
			case PROTOCOL::Client::Chatting::ROOM_STATE_NOT_PLAYING:

				break;
			case PROTOCOL::Client::Chatting::CHAT:

				break;
			}
			
			//
			// data 송신 위한 버퍼 세팅
			memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
			//ioInfo->wsaBuf.len = bytesTrnas;		//rev 송신 버퍼 크기 수정
			//std::cout << "sending buffer len: " << ioInfo->wsaBuf.len << std::endl;
			ioInfo->rwMode = WRITE;
			WSASend(sock, &(ioInfo->wsaBuf), 1, NULL, 0, &(ioInfo->overlapped), NULL);

			// data 수신 위한 버퍼 세팅
			ioInfo = (LPPER_IO_DATA)malloc(sizeof(PER_IO_DATA));
			memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
			ioInfo->wsaBuf.len = BUF_SIZE;
			ioInfo->wsaBuf.buf = ioInfo->buffer;
			ioInfo->rwMode = READ;
			WSARecv(sock, &(ioInfo->wsaBuf), 1, NULL, &flags, &(ioInfo->overlapped), NULL);
		}
		else
		{
			puts("message sent");
			free(ioInfo);
		}
	}
	return 0;
}

void ErrorHandling(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}





//
// ioInfo 안의 overlapped 라는 멤버가 의미하는 것이 뭐지..?
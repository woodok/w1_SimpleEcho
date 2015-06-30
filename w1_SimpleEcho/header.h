// find(..) 함수의 작동원리? obj의 ==operator를 이용하나?
// enum Vs const int 사용법 확인
// enum을 class로 넣어야하는지, namespace로 넣어야하는지..
// 각 클래스 상세 기술 문서 만들기

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <list>
#include <WinSock2.h>
#include <algorithm>

namespace USER_INFO
{
	enum { ID_SIZE = 20 };
};

class UserInfo
{
private:
	static int createdObjNum;
private:
	int key;		// unique key for distinguishing user
	char id[USER_INFO::ID_SIZE];	// login id
	HANDLE hSocket;
	int roomNumber;		// the number of room which the user currently participate. (Not in the room = 0)
public:
	UserInfo(char * _id, HANDLE _hSocket, int _roomNum) : roomNumber(_roomNum)
	{
		key = ++createdObjNum;
		strncpy_s(id, _id, USER_INFO::ID_SIZE);
		hSocket = _hSocket;
		std::cout << "UserInfo(..) called" << std::endl;
	}
	UserInfo() : roomNumber(0)
	{
		key = ++createdObjNum;
		strncpy_s(id, "Default", USER_INFO::ID_SIZE);
		hSocket = INVALID_HANDLE_VALUE;
		std::cout << "UserInfo() called" << std::endl;
	}
	~UserInfo()
	{
		std::cout << "~UserInfo() called" << std::endl;
	}
	
	// Accessor
	const char * get_id() const;		//? 이렇게 되는 경우 혹시 리턴값으로부터 멤버 수정할 수도..?
	int get_roomNumber() const;
	int get_key() const;
	HANDLE get_hSocket() const;

	// Mutator
	void set_id(char * _newid);
	void set_roomNumber(int _newRoomNum);
	void set_key(int _newkey);
	void set_hSocket(HANDLE _newhSocket);
};

class ROOM_INFO
{
public:
	enum { TITLE_SIZE = 100, MAX_USER = 4 };
};

class RoomInfo
{
private:
	static int createdObjNum;
public:
	int key;
	char title[ROOM_INFO::TITLE_SIZE];
	std::list<HANDLE> users;
public:
	RoomInfo(char * _title)
	{
		strncpy_s(title, _title, ROOM_INFO::TITLE_SIZE);
		key = ++createdObjNum;
		std::cout << "RoomInfo(..) called" << std::endl;
	}
	RoomInfo()
	{
		strncpy_s(title, "No title", ROOM_INFO::TITLE_SIZE);
		key = ++createdObjNum;
		std::cout << "RoomInfo() called" << std::endl;
	}
	~RoomInfo()
	{
		std::cout << "~RoomInfo() called" << std::endl;
	}
	bool joinUser(HANDLE _hSocket);
	bool quitUser(HANDLE _hSocket);
	bool operator==(RoomInfo& _comparedRoom);

	// Accessor
	int get_key();
	const char * get_title();
	
	// Mutator
	void set_title(char * _newTitle);
};
int RoomInfo::createdObjNum = 0;

// UserInfo
const char* UserInfo::get_id() const	{ return id; }
int UserInfo::get_roomNumber() const	{ return roomNumber; }
int UserInfo::get_key() const			{ return key; }
HANDLE UserInfo::get_hSocket() const	{ return hSocket; }
void UserInfo::set_id(char * _newid)	{ strncpy_s(id, _newid, USER_INFO::ID_SIZE); }
void UserInfo::set_roomNumber(int _newRoomNumber)	{ roomNumber = _newRoomNumber; }
void UserInfo::set_key(int _newkey)		{ key = _newkey; }
void UserInfo::set_hSocket(HANDLE _newhSocket)		 { 	hSocket = _newhSocket; }

// RoomInfo
bool RoomInfo::joinUser(HANDLE _hSocket)
{
	if (users.size() < ROOM_INFO::MAX_USER) {
		users.push_back(_hSocket);
		return true;
	}
	else {
		std::cout << "The room is full." << std::endl;
		return false;
	}
}
bool RoomInfo::quitUser(HANDLE _hSocket)
{
	std::list<HANDLE>::iterator iter;
	if ((iter = std::find(users.begin(), users.end(), _hSocket)) != users.end()) {
		users.erase(iter);
		return true;
	}
	else {
		std::cout << "There is no such value in the list 'users'" << std::endl;
		return false;
	}
}
bool RoomInfo::operator==(RoomInfo& _comparedRoom)
{
	if (key == _comparedRoom.key)
		return true;
	else
		return false;
}
int RoomInfo::get_key()		{ return key; }
const char * RoomInfo::get_title()	{ return title; }
void RoomInfo::set_title(char * _newTitle)	{ strncpy_s(title, _newTitle, ROOM_INFO::TITLE_SIZE); }

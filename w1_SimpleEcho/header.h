// find(..) 함수의 작동원리? obj의 ==operator를 이용하나?
// enum Vs const int 사용법 확인
// enum을 class로 넣어야하는지, namespace로 넣어야하는지..
// 각 클래스 상세 기술 문서 만들기

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <list>
#include <vector>
#include <WinSock2.h>
#include <algorithm>
#include <string>

typedef int UserKey;
typedef int RoomKey;

namespace USER_INFO
{
	enum { ID_SIZE = 20 };
};

class UserInfo
{
private:
	int key;		// unique key for distinguishing user
	std::string id;		// login id
	HANDLE hSocket;
	int roomNumber;		// the number of room which the user currently participate. (Not in the room = 0)
public:
	UserInfo(std::string _id, HANDLE _hSocket, int _roomNum = 0) : roomNumber(_roomNum)
	{
		id = _id;
		hSocket = _hSocket;
		std::cout << "UserInfo(..) called" << std::endl;
	}
	UserInfo() : roomNumber(0)
	{
		id = "Default";
		hSocket = INVALID_HANDLE_VALUE;
		std::cout << "UserInfo() called" << std::endl;
	}
	~UserInfo()
	{
		std::cout << "~UserInfo() called" << std::endl;
	}
	
	// Accessor
	const std::string& get_id() const;
	int get_roomNumber() const;
	int get_key() const;
	HANDLE get_hSocket() const;

	// Mutator
	void set_id(std::string _newid);
	void set_roomNumber(int _newRoomNum);
	void set_key(int _newkey);
	void set_hSocket(HANDLE _newhSocket);

	bool operator== (int _key) const;
	bool operator== (const UserInfo& _uInfo) const;

};

// UserInfoList stored in Vector
class UserInfoList
{
public:
	std::vector<UserInfo *> head;
private:
	int objCreated;
public:
	UserInfoList() : objCreated(0) {}
	~UserInfoList();
	void add(std::string _newid, HANDLE _hSocket, int _newRoomNum = 0);
	void del(int _key);
	//UserInfo& find(int _key);
	//UserInfo* find(int _key);
	std::vector<UserInfo *>::iterator& find(int _key);
};

class ROOM_INFO
{
public:
	enum { TITLE_SIZE = 100, MAX_USER = 4 };
};

class RoomInfo
{
public:
	int key;
	std::string title;
	std::list<HANDLE> users;
public:
	RoomInfo(std::string _title)
	{
		title = _title;
		std::cout << "RoomInfo(..) called" << std::endl;
	}
	RoomInfo()
	{
		title = "No title";
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
	const std::string& get_title() const;
	
	// Mutator
	void set_key(int _key);
	void set_title(std::string _newTitle);
};

// RoomInfoList stored in Vector
class RoomInfoList
{
	std::list<RoomInfo *> head;
	//rev
private:
};

// UserInfo
const std::string& UserInfo::get_id() const	{ return id; }
int UserInfo::get_roomNumber() const	{ return roomNumber; }
int UserInfo::get_key() const			{ return key; }
HANDLE UserInfo::get_hSocket() const	{ return hSocket; }
void UserInfo::set_id(std::string _newid)	{ id = _newid; }
void UserInfo::set_roomNumber(int _newRoomNumber)	{ roomNumber = _newRoomNumber; }
void UserInfo::set_key(int _newkey)		{ key = _newkey; }
void UserInfo::set_hSocket(HANDLE _newhSocket)		 { 	hSocket = _newhSocket; }
bool UserInfo::operator== (int _key) const
{
	return key == _key;
}
bool UserInfo::operator== (const UserInfo& _uInfo) const
{
	return key == _uInfo.key;
}

// UserInfoList
void UserInfoList::add(std::string _newid, HANDLE _hSocket, int _newRoomNum) 
{
	head.push_back(new UserInfo(_newid, _hSocket, _newRoomNum));
}
void UserInfoList::del(int _key)				//rev
{
	// del operation modularization 이전
	/*std::vector<UserInfo *>::iterator it = std::find_if(head.begin(), head.end(), [&_key](UserInfo *& e) {
		if ((*e).get_key() == _key)
			return true;
		else
			return false;
	});
	delete(*it);
	*it = nullptr;
	head.erase(it);
*/

	std::vector<UserInfo *>::iterator & temp = find(_key);
	delete(*temp);
	*temp = nullptr;
	head.erase(temp);
}
std::vector<UserInfo *>::iterator&  UserInfoList::find(int _key)
{
	std::vector<UserInfo *>::iterator it = std::find_if(head.begin(), head.end(), [&_key](UserInfo *& e) {
		if (e->get_key() == _key)
			return true;
		else
			return false;
	});
	
	return it;
}

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
const std::string& RoomInfo::get_title() const	{ return title; }
void RoomInfo::set_key(int _key) { key = _key; }
void RoomInfo::set_title(std::string _newTitle)	{ title = _newTitle; }

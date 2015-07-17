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
#include <utility>

typedef int UserKey;
typedef int RoomKey;

namespace USER_INFO
{
	enum { ID_SIZE = 20 };
};

class UserInfo
{
private:
	UserKey key;		// unique key for distinguishing user
	std::string id;		// login id
	HANDLE hSocket;
	RoomKey roomNumber;		// the number of room which the user currently participate. (Not in the room = 0)
public:
	UserInfo(std::string _id, HANDLE _hSocket, RoomKey _roomNum = 0) : roomNumber(_roomNum)
	{
		id = _id;				//? move semantic 사용해야하나..?
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
	RoomKey get_roomNumber() const;
	UserKey get_key() const;
	HANDLE get_hSocket() const;

	// Mutator
	void set_id(std::string _newid);
	void set_roomNumber(RoomKey _newRoomNum);
	void set_key(UserKey _newkey);
	void set_hSocket(HANDLE _newhSocket);

	bool operator== (UserKey _key) const;
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
	~UserInfoList()
	{
		for_each(head.begin(), head.end(), [](UserInfo *& e) {
			delete(e);
			e = nullptr;
		});
	}
	void add(std::string _newid, HANDLE _hSocket, RoomKey _newRoomNum = 0);
	void del(UserKey _key);
	std::vector<UserInfo *>::iterator& find(UserKey _key);
};

class ROOM_INFO
{
public:
	enum { TITLE_SIZE = 100, MAX_USER = 4 };
};

class RoomInfo
{
private:
	RoomKey key;
	std::string title;
	std::vector<std::pair<UserKey, HANDLE>> users;
public:
	RoomInfo(std::string _title)
	{
		title = _title;
		users.reserve(ROOM_INFO::MAX_USER);
		std::cout << "RoomInfo(..) called" << std::endl;
	}
	RoomInfo()
	{
		title = "No title";
		users.reserve(ROOM_INFO::MAX_USER);
		std::cout << "RoomInfo() called" << std::endl;
	}
	~RoomInfo()
	{
		std::cout << "~RoomInfo() called" << std::endl;
	}
	bool joinUser(UserKey _uKey, HANDLE _hSocket);
	bool quitUser(UserKey _uKey, HANDLE _hSocket);
	bool operator==(RoomInfo& _comparedRoom);
	bool operator==(RoomKey _roomKey);

	// Accessor
	RoomKey get_key() const;
	const std::string& get_title() const;
	
	// Mutator
	void set_key(RoomKey _key);
	void set_title(std::string _newTitle);
};

// RoomInfoList stored in Vector
class RoomInfoList
{
public:
	std::list<RoomInfo *> head;
	//rev
private:
};

// UserInfo
const std::string& UserInfo::get_id() const	{ return id; }
RoomKey UserInfo::get_roomNumber() const	{ return roomNumber; }
UserKey UserInfo::get_key() const			{ return key; }
HANDLE UserInfo::get_hSocket() const	{ return hSocket; }
void UserInfo::set_id(std::string _newid)	{ id = _newid; }
void UserInfo::set_roomNumber(RoomKey _newRoomNumber)	{ roomNumber = _newRoomNumber; }
void UserInfo::set_key(UserKey _newkey)		{ key = _newkey; }
void UserInfo::set_hSocket(HANDLE _newhSocket)		 { 	hSocket = _newhSocket; }
bool UserInfo::operator== (UserKey _key) const
{
	return key == _key;
}
bool UserInfo::operator== (const UserInfo& _uInfo) const
{
	return key == _uInfo.key;
}

// UserInfoList
void UserInfoList::add(std::string _newid, HANDLE _hSocket, RoomKey _newRoomNum) 
{
	head.push_back(new UserInfo(_newid, _hSocket, _newRoomNum));
}
void UserInfoList::del(UserKey _key)
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
std::vector<UserInfo *>::iterator&  UserInfoList::find(UserKey _key)
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
bool RoomInfo::joinUser(UserKey _uKey, HANDLE _hSocket)
{
	if (users.size() < ROOM_INFO::MAX_USER) {
		users.push_back(std::make_pair(_uKey, _hSocket));			//? move semantic 써야하지 않나..? 
		return true;
	}
	else {
		std::cout << "The room is already full." << std::endl;
		return false;
	}
}
bool RoomInfo::quitUser(UserKey _uKey, HANDLE _hSocket)
{
	std::vector<std::pair<UserKey, HANDLE>>::iterator it;
	it = find_if(users.begin(), users.end(), [=](std::pair<UserKey, HANDLE>& e) {
		if (e.first == _uKey)
			return true;
		else
			return false;
	});

	if (it != users.end() )
	{
		users.erase(it);
	}
	else {
		std::cout << "There is no such user(UserKey: " 
			<< _uKey << ") in this room(RoomKey: " << key << ")." << std::endl;
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
bool RoomInfo::operator==(RoomKey _roomKey)
{
	if (key == _roomKey)
		return true;
	else
		return false;
}
RoomKey RoomInfo::get_key()	const	{ return key; }
const std::string& RoomInfo::get_title() const	{ return title; }
void RoomInfo::set_key(RoomKey _key) { key = _key; }
void RoomInfo::set_title(std::string _newTitle)	{ title = _newTitle; }

// RoomInfoList class
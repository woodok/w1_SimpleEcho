
#ifndef __HEADER_H_
#define __HEADER_H_

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <list>
#include <vector>
#include <WinSock2.h>
#include <algorithm>
#include <string>
#include <utility>
#include <sstream>

#include "functions.h"
#include "protocol.h"

//#define BUF_SIZE 1000

typedef int UserKey;
typedef int RoomKey;

const char * server_address = "127.0.0.1";		//? loopback 주소 맞나..?
const char * server_port = "9190";

namespace MYCONST
{
	static const int BUF_SIZE = 1000;

}
namespace USER_INFO
{
	enum {
		DEFAULT_USER_KEY = -1,
		ID_SIZE = 20,			// max length of id number (, which has no meaning now cause id type changed to std::string)
		STATUS_NOT_READY = 0,
		STATUS_READY = 1
	};
};
class ROOM_INFO
{
public:
	enum { 
		TITLE_SIZE = 100,		// max length of title number (, which has no meaning now cause title type changed to std::string)
		MAX_USER = 4,			// max participants number per room
		DEFAULT_ROOM_KEY = -1,			// has no room key
		STATE_NOT_PLAYING = 0,
		STATE_PLAYING = 1
	};
};

class UserInfo
{
private:
	UserKey key;		// unique key for distinguishing user
	std::string id;		// login id
	SOCKET hSocket;
	RoomKey roomNumber;		// the number of room which the user currently participate. (Not in the room = 0)
public:
	UserInfo(UserKey _key, std::string _id, SOCKET _hSocket, RoomKey _roomNum = ROOM_INFO::DEFAULT_ROOM_KEY)
		: key(_key), roomNumber(_roomNum)
	{
		id = _id;				//? move semantic 사용해야하나..?
		hSocket = _hSocket;
		spellingCheck();
		std::cout << "UserInfo(..) called" << std::endl;
	}
	UserInfo() : key(USER_INFO::DEFAULT_USER_KEY), roomNumber(ROOM_INFO::DEFAULT_ROOM_KEY)
	{
		id = "Default";
		hSocket = INVALID_HANDLE_VALUE;
		std::cout << "UserInfo() called" << std::endl;
	}
	~UserInfo()
	{
		std::cout << "~UserInfo() called" << std::endl;
	}
	// member functions
	void spellingCheck();			// replace protocol reserved delimiter
	// Accessor
	const std::string& get_id() const;
	RoomKey get_roomNumber() const;
	UserKey get_key() const;
	SOCKET get_hSocket() const;
	// Mutator
	void set_id(std::string _newid);
	void set_roomNumber(RoomKey _newRoomNum);
	void set_key(UserKey _newkey);
	void set_hSocket(SOCKET _newhSocket);
	// operator overloading
	bool operator== (UserKey _key) const;
	bool operator== (const UserInfo& _uInfo) const;
	friend class Buffer;
	friend std::ostream& operator<<(std::ostream& os, const UserInfo& ui);
};

// UserInfoList stored in Vector
class UserInfoList
{
public:
	std::vector<UserInfo *> head;
private:
	int objCreated;		// the number of UserInfo object created
public:
	UserInfoList() : objCreated(0) {}
	~UserInfoList()
	{
		for_each(head.begin(), head.end(), [](UserInfo *& e) {
			delete(e);
			e = nullptr;
		});
	}
	void add(std::string _newid, SOCKET _hSocket, RoomKey _newRoomNum = ROOM_INFO::DEFAULT_ROOM_KEY);
	void del(UserKey _key);
	std::vector<UserInfo *>::iterator find(UserKey _key);
	std::vector<UserInfo *>::const_iterator find(UserKey _key) const;
	void print(std::vector<UserInfo *>::const_iterator& it) const;
	void print(UserKey _key) const;
	void print() const;
};

class RoomInfo
{
private:
	RoomKey key;
	std::string title;
	std::vector<std::pair<UserKey, SOCKET>> users;
public:
	RoomInfo(RoomKey _key, std::string _title) : key(_key)
	{
		title = _title;
		users.reserve(ROOM_INFO::MAX_USER);
		spellingCheck();
		std::cout << "RoomInfo(..) called" << std::endl;
	}
	RoomInfo()
	{
		key = ROOM_INFO::DEFAULT_ROOM_KEY;
		title = "No title";
		users.reserve(ROOM_INFO::MAX_USER);
		std::cout << "RoomInfo() called" << std::endl;
	}
	~RoomInfo()
	{
		std::cout << "~RoomInfo() called" << std::endl;
	}

	// member functions
	void spellingCheck();
	bool joinUser(UserKey _uKey, SOCKET _hSocket);
	bool quitUser(UserKey _uKey);

	// Accessor
	RoomKey get_key() const;
	const std::string& get_title() const;
	
	// Mutator
	void set_key(RoomKey _key);
	void set_title(std::string _newTitle);

	bool operator==(const RoomInfo& _comparedRoom) const;
	bool operator==(RoomKey _roomKey) const;
	friend class Buffer;
	friend std::ostream& operator<<(std::ostream&, const RoomInfo&);
};

// RoomInfoList stored in Vector
class RoomInfoList
{
public:
	std::vector<RoomInfo *> head;
private:
	int objCreated;			// the number of RoomInfo object created
public:
	RoomInfoList() : objCreated(0) {}
	~RoomInfoList()
	{
		for_each(head.begin(), head.end(), [](RoomInfo *& e) {
			delete(e);
			e = nullptr;
		});
	}
	void add(std::string _title);
	void del(RoomKey _key);
	std::vector<RoomInfo *>::iterator find(RoomKey _key);
	std::vector<RoomInfo *>::const_iterator find(RoomKey _key) const;
	void print(std::vector<RoomInfo *>::const_iterator& it) const;
	void print(RoomKey rk) const;
	void print() const;
};

void reset_sstream(std::stringstream& ss);

#endif // !__HEADER_H_
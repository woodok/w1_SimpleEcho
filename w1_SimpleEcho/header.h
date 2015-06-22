#include <iostream>
#include <cstdlib>
#include <cstring>
#include <list>

class UserInfo
{
private:
	static int createdObjNum;
public:
	enum {
		ID_SIZE = 20
	};
private:
	int key;		// unique key for distinguishing user
	char id[ID_SIZE];	// login id
	HANDLE hSocket;
	int roomNumber;		// the number of room which the user currently participate. (Not in the room = 0)
public:
	UserInfo(char * _id, HANDLE _hSocket, int _roomNum) : roomNumber(_roomNum)
	{
		key = ++createdObjNum;
		strncpy_s(id, _id, ID_SIZE);
		hSocket = _hSocket;
	}
	UserInfo() : roomNumber(0)
	{
		key = ++createdObjNum;
		strncpy_s(id, "Default", ID_SIZE);
		hSocket = INVALID_HANDLE_VALUE;
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

class RoomInfo
{
private:
	static int createdObjNum;
public:
	enum {
		TITLE_SIZE = 100,
		MAX_USER = 4
	};
private:
	int key;
	char title[TITLE_SIZE];
	std::list<HANDLE> users;
public:
	RoomInfo(char * _title)
	{
		strncpy_s(title, _title, TITLE_SIZE);
		key = ++createdObjNum;
	}
	RoomInfo()
	{
		strncpy_s(title, "No title", TITLE_SIZE);
		key = ++createdObjNum;
	}
	boolean joinUser(HANDLE _hSocket);
	boolean quitUser(HANDLE _hSocket);

	// Accessor
	int get_key();
	const char * get_title();
	
	// Mutator
	void set_title(char * _newTitle);
};

// UserInfo
const char* UserInfo::get_id() const	{ return id; }
int UserInfo::get_roomNumber() const	{ return roomNumber; }
int UserInfo::get_key() const			{ return key; }
HANDLE UserInfo::get_hSocket() const	{ return hSocket; }
void UserInfo::set_id(char * _newid)	{ strncpy_s(id, _newid, UserInfo::ID_SIZE); }
void UserInfo::set_roomNumber(int _newRoomNumber)	{ roomNumber = _newRoomNumber; }
void UserInfo::set_key(int _newkey)		{ key = _newkey; }
void UserInfo::set_hSocket(HANDLE _newhSocket)		 { 	hSocket = _newhSocket; }

// RoomInfo
boolean RoomInfo::joinUser(HANDLE _hSocket)
{
	
}
boolean RoomInfo::quitUser(HANDLE _hSocket)
{

}

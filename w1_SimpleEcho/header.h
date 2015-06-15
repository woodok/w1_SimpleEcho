#include <iostream>
#include <cstdlib>
#include <cstring>

class User
{
	static int createdObjNum;
	enum {
		NAME_SIZE = 20,
		NICK_SIZE = 20
	};
private:
	char name[NAME_SIZE];
	char nick[NICK_SIZE];
	int roomNumber;
	int userKey;
public:
	User(char * _name, char * _nick, int _roomNum) : roomNumber(_roomNum)
	{
		strncpy(name, _name, NAME_SIZE);
		strncpy(nick, _nick, NICK_SIZE);
		userKey = createdObjNum++;
	}
	User() : roomNumber(0)
	{
		strncpy(name, "Default", NAME_SIZE);
		strncpy(nick, "Default", NICK_SIZE);
		userKey = createdObjNum++;
	}
	
	// Accessor
	const char * get_name() const;		//? 이렇게 되는 경우 혹시 리턴값으로부터 멤버 수정할 수도..?
	const char * get_nick() const;		//? 이렇게 되는 경우 혹시 리턴값으로부터 멤버 수정할 수도..?
	int get_roomNumber() const;
	int get_userKey() const;

	// Mutator
	void set_name(char * _newName);
	void set_nick(char * _newNick);
	void set_roomNumber(int _newRoomNum);
	void set_userKey(int _newUserKey);

};

const char* User::get_name() const
{
	return name;
};
const char * User::get_nick() const
{
	return nick;
};
int User::get_roomNumber() const
{
	return roomNumber;
};
int User::get_userKey() const
{
	return userKey;
}
void User::set_name(char * _newName)
{
	strncpy(name, _newName, User::NAME_SIZE);
};
void User::set_nick(char * _newNick)
{
	strncpy(nick, _newNick, User::NICK_SIZE);
};
void User::set_roomNumber(int _newRoomNumber)
{
	roomNumber = _newRoomNumber;
};
void User::set_userKey(int _newUserKey)
{
	userKey = _newUserKey;
};

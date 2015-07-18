
#include "header.h"

// UserInfo
void UserInfo::spellingCheck()
{
	std::replace(id.begin(), id.end(), '|', '_');
}
const std::string& UserInfo::get_id() const	{ return id; }
RoomKey UserInfo::get_roomNumber() const	{ return roomNumber; }
UserKey UserInfo::get_key() const			{ return key; }
HANDLE UserInfo::get_hSocket() const	{ return hSocket; }
void UserInfo::set_id(std::string _newid)
{
	id = _newid;
	spellingCheck();
}
void UserInfo::set_roomNumber(RoomKey _newRoomNumber)	{ roomNumber = _newRoomNumber; }
void UserInfo::set_key(UserKey _newkey)		{ key = _newkey; }
void UserInfo::set_hSocket(HANDLE _newhSocket)		 { hSocket = _newhSocket; }
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
	objCreated++;
	head.push_back(new UserInfo(objCreated, _newid, _hSocket, _newRoomNum));
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

	if (it != users.end())
	{
		users.erase(it);
	}
	else {
		std::cout << "There is no such user(UserKey: "
			<< _uKey << ") in this room(RoomKey: " << key << ")." << std::endl;
		return false;
	}
}
void RoomInfo::spellingCheck()
{
	std::replace(title.begin(), title.end(), '|', '_');
}
RoomKey RoomInfo::get_key()	const	{ return key; }
const std::string& RoomInfo::get_title() const	{ return title; }
void RoomInfo::set_key(RoomKey _key) { key = _key; }
void RoomInfo::set_title(std::string _newTitle)	{
	title = _newTitle;
	spellingCheck();
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

// RoomInfoList class


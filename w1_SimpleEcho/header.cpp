
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
std::ostream& operator<<(std::ostream& os, const UserInfo& ui)
{
	std::cout << "key:" << ui.key << " |id:" << ui.id << " |socket:" << ui.hSocket 
		<< " |room number:" << ui.roomNumber;
	return os;
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
std::vector<UserInfo *>::iterator UserInfoList::find(UserKey _key)
{
	std::vector<UserInfo *>::iterator it = head.end();
	it = std::find_if(head.begin(), head.end(), [_key](UserInfo *& e) {
		if (e->get_key() == _key)
			return true;
		else
			return false;
	});

	return it;
}
std::vector<UserInfo *>::const_iterator UserInfoList::find(UserKey _key) const
{
	std::vector<UserInfo *>::const_iterator it = head.cend();		//rev UserInfo *const 냐.. const UserInfo * 냐.. 
																	//		아무래도 내가 const_iterator 쓰임을 잘못 알고 있는 모양.. 
																	//		찾아보기: const_iterator, cbegin(), cend() 등등...
	it = std::find_if(head.cbegin(), head.cend(), [_key](UserInfo * const& e) {
		if (e->get_key() == _key)
			return true;
		else
			return false;
	});

	return it;
}
void UserInfoList::print(std::vector<UserInfo *>::const_iterator& it) const
{
	std::cout << **it;
}
void UserInfoList::print(UserKey _key) const
{
	print(find(_key));
	std::cout << std::endl;
}
void UserInfoList::print() const
{
	//for_each(head.cbegin(), head.cend(), print(UserInfo * & e));		//? error
	//for_each(head.cbegin(), head.cend(), print(std::vector<UserInfo*>::const_iterator& it));		//? 형식이름을 사용할 수 없습니다??
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "UserInfoList::print()\t>>" << std::endl;
	for (auto it = head.cbegin(); it != head.cend(); ++it) {
		print(it);
		std::cout << "\t>>" << std::endl;
	}
	std::cout << "end()" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
}

// RoomInfo
bool RoomInfo::joinUser(UserKey _uKey, HANDLE _hSocket)
{
	if (users.size() < ROOM_INFO::MAX_USER) {
		users.push_back(std::make_pair(_uKey, _hSocket));	//? move semantic 써야하지 않나..? 
		return true;
	}
	else {
		std::cout << "The room is already full." << std::endl;
		return false;
	}
}
bool RoomInfo::quitUser(UserKey _uKey)
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
		return true;
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
bool RoomInfo::operator==(const RoomInfo& _comparedRoom) const
{
	if (key == _comparedRoom.key)
		return true;
	else
		return false;
}
bool RoomInfo::operator==(RoomKey _roomKey) const 
{
	if (key == _roomKey)
		return true;
	else
		return false;
}
std::ostream& operator<<(std::ostream& os, const RoomInfo& ri)
{
	std::cout << "key:" << ri.key << " |title:" << ri.title
		<< " |participants(" << ri.users.size() << "): ";
}

// RoomInfoList class
void RoomInfoList::add(std::string _title)
{
	objCreated++;
	head.push_back(new RoomInfo(objCreated, _title));
}
void RoomInfoList::del(RoomKey _key)
{
	std::vector<RoomInfo *>::iterator& it = find(_key);

	delete(*it);
	*it = nullptr;
	head.erase(it);
}
std::vector<RoomInfo *>::iterator& RoomInfoList::find(RoomKey _key)
{
	std::vector<RoomInfo *>::iterator& it = head.end();
	it = find_if(head.begin(), head.end(), [_key](RoomInfo *& e) {
		if (e->get_key() == _key)
			return true;
		else
			return false;
	});
	return it;
}
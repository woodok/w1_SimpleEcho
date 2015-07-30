#ifndef __FUNCTIONS_H_
#define __FUNCTIONS_H_

#include "header.h"

namespace BUFFER_CONST
{
	enum {
		SIZE = 1000
	};
}
namespace PACKET_TYPE
{
	enum {

	};
}
class Buffer
{
public:
	std::string data;
public:
	Buffer()
	{
		data.reserve(BUFFER_CONST::SIZE);
		std::cout << "Buffer() called" << std::endl;
	}
	~Buffer()
	{
		std::cout << "~Buffer() called" << std::endl;
	}
private:
	void operator<<(const UserInfo& _ui);
	void operator<<(const RoomInfo& _ri);
public:
	void serialize(const UserInfo& _ui);
	void serialize(const RoomInfo& _ri);
	void serialize(const UserInfoList& _uList);
	void serialize(const RoomInfoList& _rList);
	void deserialize(UserInfoList& _uList) const;
	void deserialize(RoomInfoList& _rList) const;

	// accessor
	std::string& get_data();
	// mutator
	

};


#endif // !__FUNCTIONS_H_
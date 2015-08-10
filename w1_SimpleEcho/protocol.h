
#ifndef __PROTOCOL_H_
#define __PROTOCOL_H_

namespace PROTOCOL
{
	class Login
	{
	public:
		enum {
			LOGIN,
			LAST
		};
	};
	class Lobby
	{
	public:
		enum{
			CREATE_ROOM = Login::LAST,
			CREATE_ROOM_FAIL,
			JOIN_ROOM,
			JOIN_ROOM_FAIL,
			RELOAD,
			LAST
		};
	};
	class CreateRoom
	{
	public:
		enum {
			CREATE_ROOM = Lobby::LAST,
			CREATE_ROOM_FAIL,
			LAST
		};
	};
	class Chatting
	{
	public:
		enum {
			QUIT_ROOM = CreateRoom::LAST,
			GUEST_STATE_READY,
			GUEST_STATE_NOT_READY,
			ROOM_STATE_NOT_PLAYING,
			ROOM_STATE_PLAYING,
			CHAT,
			LAST
		};
	};
}



#endif // !__PROTOCOL_H_
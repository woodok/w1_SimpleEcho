
#ifndef __PROTOCOL_H_
#define __PROTOCOL_H_

namespace PROTOCOL
{
	// client -> server protocol
	namespace Client
	{
		namespace Login
		{
			enum {
				BEGIN = 0,

				LAST
			};
		}
		namespace Lobby
		{
			enum {
				BEGIN = Login::LAST,

				LAST
			};
		}
		namespace CreateRoom
		{
			enum {
				BEGIN = Lobby::LAST,

				LAST
			};
		}
		namespace Chatting
		{
			enum {
				BEGIN = CreateRoom::LAST,

				LAST
			};
		}
	}

	// server -> client protocol
	namespace Server
	{
		namespace Login
		{
			enum {
				BEGIN = 0,
				LOGIN,
				LAST
			};
		}
		namespace Lobby
		{
			enum{
				BEGIN = Login::LAST,
				CREATE_ROOM,
				CREATE_ROOM_FAIL,
				JOIN_ROOM,
				JOIN_ROOM_FAIL,
				RELOAD,
				LAST
			};
		}
		namespace CreateRoom
		{
			enum {
				BEGIN = Lobby::LAST,
				CREATE_ROOM,
				CREATE_ROOM_FAIL,
				LAST
			};
		}
		namespace Chatting
		{
			enum {
				BEGIN = CreateRoom::LAST,
				QUIT_ROOM,
				GUEST_STATE_READY,
				GUEST_STATE_NOT_READY,
				ROOM_STATE_NOT_PLAYING,
				ROOM_STATE_PLAYING,
				CHAT,
				LAST
			};
		}
	}
}



#endif // !__PROTOCOL_H_
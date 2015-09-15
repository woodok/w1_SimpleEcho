
#ifndef __PROTOCOL_H_
#define __PROTOCOL_H_

namespace PROTOCOL
{
	namespace State
	{
		enum {
			LOGIN,
			LOBBY,
			CREATE_ROOM,
			CHATTING
		};
	}
	// client -> server protocol
	namespace Client
	{
		namespace Login
		{
			enum {
				NO_MEANING_FIRST = 0,	// no meaning
				// meaningful protocol keyword place from here
				CONFIRMED,
				LOGIN,
				// meaningful protocol keyword place to here
				NO_MEANING_LAST			// no meaning
			};
		}
		namespace Lobby
		{
			enum {
				NO_MEANING_FIRST = Login::NO_MEANING_LAST,	// no meaning
				// meaningful protocol keyword place from here
				CONFIRMED,
				LOAD_LIST,
				JOIN_ROOM,
				NO_MEANING_LAST		// no meaning
			};
		}
		namespace CreateRoom
		{
			enum {
				NO_MEANING_FIRST = Lobby::NO_MEANING_LAST,		// no meaning
				// meaningful protocol keyword place from here
				CONFIRMED,
				CREATE_ROOM,
				NO_MEANING_LAST		// no meaning
			};
		}
		namespace Chatting
		{
			enum {
				NO_MEANING_FIRST = CreateRoom::NO_MEANING_LAST,		// no meaning
				// meaningful protocol keyword place from here
				CONFIRMED,
				QUIT_ROOM,
				MY_STATE_READY,
				MY_STATE_NOT_READY,
				ROOM_STATE_PLAYING,
				ROOM_STATE_NOT_PLAYING,
				CHAT,
				NO_MEANING_LAST		// no meaning
			};
		}
	}

	// server -> client protocol
	namespace Server
	{
		namespace Connection
		{
			enum {
				NO_MEANING_FIRST = Client::Chatting::NO_MEANING_LAST,	// no meaning
				// meaningful protocol keyword place from here
				READY,
				// meaningful protocol keyword place to here
				NO_MEANING_LAST			// no meaning
			};
		}
		namespace Login
		{
			enum {
				NO_MEANING_FIRST = 	Connection::NO_MEANING_LAST,	// no meaning
				// meaningful protocol keyword place from here
				DATA_READY,
				LOGIN_OK,
				NO_MEANING_LAST		// no meaning
			};
		}
		namespace Lobby
		{
			enum{
				NO_MEANING_FIRST = Login::NO_MEANING_LAST,	// no meaning
				// meaningful protocol keyword place from here
				DATA_READY,
				CREATE_ROOM_OK,
				CREATE_ROOM_FAIL,
				JOIN_ROOM_OK,
				JOIN_ROOM_FAIL,
				LOAD_LIST,
				NO_MEANING_LAST		// no meaning
			};
		}
		namespace CreateRoom
		{
			enum {
				NO_MEANING_FIRST = Lobby::NO_MEANING_LAST,	// no meaning
				// meaningful protocol keyword place from here
				DATA_READY,
				CREATE_ROOM_OK,
				CREATE_ROOM_FAIL,
				NO_MEANING_LAST		// no meaning
			};
		}
		namespace Chatting
		{
			enum {
				NO_MEANING_FIRST = CreateRoom::NO_MEANING_LAST,	// no meaning
				// meaningful protocol keyword place from here
				DATA_READY,
				QUIT_USER,
				JOIN_USER,
				GUEST_STATE_READY,
				GUEST_STATE_NOT_READY,
				ROOM_STATE_PLAYING,
				ROOM_STATE_NOT_PLAYING,
				CHAT,
				NO_MEANING_LAST		// no meaning
			};
		}
	}
}



#endif // !__PROTOCOL_H_
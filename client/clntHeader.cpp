#include "clntHeader.h"

ClientFSM::ClientFSM() : state(ClientFSM::STATE_LOGIN) {};
void ClientFSM::start()
{

}
void ClientFSM::running()
{
	while (true)
	{
		switch (state)
		{
		case STATE_LOGIN:
			Login::display();
			//rev

			state = STATE_LOBBY;
		case STATE_LOBBY:

		case STATE_CREATINGROOM:

		case STATE_CHATTING:

		case STATE_QUIT:

		}
	}
}
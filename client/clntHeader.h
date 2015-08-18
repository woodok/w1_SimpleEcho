#include "../w1_SimpleEcho/header.h"

namespace client
{
	void LoginProcess();
	void LobbyProcess();
	void CreatingRoomProcess();
	void ChattingProcess();

	void displayLogin();
	void displayLobby(std::stringstream&& _ss);
	void displayCreatingRoom();
	void displayChatting();


	void login()
	{
		std::cout << "--------------------------------------" << std::endl;
		std::cout << "Please put your nickname: " << std::endl;
		//std::cin >> nickbuf;
	}
}
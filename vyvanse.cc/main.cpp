#include "Offsets.h"
#include "Cheats.h"
#include <iostream>
#include <stdio.h>
#include <iomanip>

int main()
{

	std::printf(
	"\033[38;5;165mvyvanse.cc External for CS2\n"
	"Author: 44\n"
	"Source Code: https://github.com/9xN/vyvanse.cc\n"
	"\n"
	"- Aimbot and RCS features may result in VAC Bans, use with caution.\n"
	"- Press [HOME] to show or hide Menu.\n"
	"\n"
	);
	auto ProcessStatus = ProcessMgr.Attach("cs2.exe");
	switch (ProcessStatus) {
	case 1:
		std::cout << "[ERROR] Please launch the game first!" << std::endl;
		goto END;
	case 2: 
		std::cout << "[ERROR] Failed to hook process, please run the cheat in UAC." << std::endl; 
		goto END; 
	case 3:
		std::cout << "[ERROR] Failed to get module address." << std::endl; 
		goto END; 
	default: 
		break;
	}

	if (!Offset::UpdateOffsets())
	{
		std::cout << "[ERROR] Failed to update offsets." << std::endl;
		goto END;
	}

	if (!gGame.InitAddress())
	{
		std::cout << "[ERROR] Failed to call InitAddress()."<< std::endl;
		goto END;
	}
	std::cout << "[Game] Process ID: " << ProcessMgr.ProcessID << std::endl;
	std::cout << "[Game] Client Address: " << gGame.GetClientDLLAddress() << std::endl;
	std::cout << "Offset:" << std::endl;
	std::cout << "--EntityList:" << std::setiosflags(std::ios::uppercase) << std::hex << Offset::EntityList << std::endl;
	std::cout << "--Matrix:" << std::setiosflags(std::ios::uppercase) << std::hex << Offset::Matrix << std::endl;
	std::cout << "--LocalPlayerController:" << std::setiosflags(std::ios::uppercase) << std::hex << Offset::LocalPlayerController << std::endl;
	std::cout << "--ViewAngles:" << std::setiosflags(std::ios::uppercase) << std::hex << Offset::ViewAngle << std::endl;
	std::cout << "--LocalPlayerPawn:" << std::setiosflags(std::ios::uppercase) << std::hex << Offset::LocalPlayerPawn << std::endl;
	std::cout << std::endl;
	std::cout << "Cheat running successfully!" << std::endl;
	std::cout << "Have fun..." << std::endl;

	try
	{
		Gui.AttachAnotherWindow("Counter-Strike 2", "SDL_app", Cheats::Run);
	}
	catch (OSImGui::OSException& e)
	{
		try
		{
			Gui.AttachAnotherWindow("·´¿Ö¾«Ó¢£ºÈ«Çò¹¥ÊÆ", "SDL_app", Cheats::Run);
		}
		catch (OSImGui::OSException& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

END:
	std::cout << std::endl;
	system("pause");
	return 0;
}
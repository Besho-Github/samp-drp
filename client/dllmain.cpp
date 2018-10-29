#include "dllmain.h"

HMODULE module = NULL;

static void Thread()
{
	DWORD samp_module = reinterpret_cast<DWORD>(GetModuleHandle("samp.dll"));

	if (!samp_module)
	{
		FreeLibraryAndExitThread(module, 0);
	}
	else
	{
		if (!Addresses::GetAddresses(samp_module))
		{
			FreeLibraryAndExitThread(module, 0);
		}
		else
		{
			if (Utils::fexists("samp-drp.ini"))
			{
				Network::connect_to_server = GetPrivateProfileInt("Settings", "ConnectToServer", 1, ".\\samp-drp.ini");			
			}
			else
			{
				WritePrivateProfileString("Settings", "ConnectToServer", "1", ".\\samp-drp.ini");
			}

			Network::ReceivePacket = reinterpret_cast<ReceivePacket_t>(Utils::DetourFunc(reinterpret_cast<uint8_t*>((samp_module + Addresses::ReceivePacket_offset)), reinterpret_cast<uint8_t*>(Network::PacketReceived), 6));

			std::string server_ip, server_port;

			DiscordRichPresence discord_presence;
			discord_presence = { 0 };
			discord_presence.startTimestamp = time(0);

			// I'm not going to get the player name from command line, because I want to keep track of changes, hence I'm getting the offset for player name.
			Utils::ReadSampCommandLine(std::string(GetCommandLine()), server_ip, server_port);

			// I want to keep track of host name changes, etc. That is something the client is not aware of, so a query does the job.
			SampQuery query(server_ip, std::stoi(server_port), 1000);
			SampQuery::ServerInformation server_info;
			server_info = { 0 };

			while (1)
			{
				if (!Network::drp_initialized)
				{
					// If it isn't NULL, means connect_to_server is true. If it's minor than the current tick, then the server doesn't use the plugin, so we initialize DRP as if connect_to_server was false.
					if (Network::connect_tick != NULL && (Network::connect_tick < GetTickCount()))
					{
						Discord_Initialize(Network::application_id.c_str(), NULL, 0, NULL);
						Network::drp_initialized = true;
						Network::connect_to_server = 0;
					}
					Sleep(200);
				}
				else
				{
					if (!Network::connect_to_server)
					{
						if (query.GetInformation(&server_info) == SAMP_QUERY_SUCCESS)
						{
							Network::details = "Playing as " + Addresses::GetPlayerName(samp_module);
							Network::state = "At " + server_info.hostname;
							Network::small_image_text = "Players: " + std::to_string(server_info.total_players) + '/' + std::to_string(server_info.max_players);

							if (server_info.is_locked)
							{
								Network::small_image = "locked";
							}
							else
							{
								Network::small_image = "unlocked";
							}

							Network::large_image = "sa_big_img";
							Network::large_image_text = server_ip + ':' + server_port;
						}
					}

					discord_presence.details = Network::details.c_str();
					discord_presence.largeImageKey = Network::large_image.c_str();
					discord_presence.largeImageText = Network::large_image_text.c_str();
					discord_presence.smallImageKey = Network::small_image.c_str();
					discord_presence.smallImageText = Network::small_image_text.c_str();
					discord_presence.state = Network::state.c_str();

					Discord_UpdatePresence(&discord_presence);

					Sleep(15000);
				}
			}
		}
	}
}

BOOLEAN WINAPI DllMain(IN HINSTANCE hDllHandle, IN DWORD nReason, IN LPVOID Reserved)
{
	if (nReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hDllHandle);
		module = hDllHandle;
		return CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Thread), 0, 0, 0) > 0;
	}
	if (nReason == DLL_PROCESS_DETACH)
	{
		Discord_Shutdown();
	}
	return 1;
}
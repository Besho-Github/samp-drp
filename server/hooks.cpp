#include "hooks.h"

namespace Hooks
{
	namespace Application
	{
		std::string application_id = "None";
		std::string details = "None";
		std::string state = "None";
		std::string large_image = "None";
		std::string large_image_text = "None";
		std::string small_image = "None";
		std::string small_image_text = "None";
	}

	RakServer* pRakServer = NULL;
	DWORD FUNC_GetPacketID = NULL;
	subhook::Hook GetPacketID_hook;

	typedef BYTE(*getPacketId)(Packet *p);

	BYTE HOOK_GetPacketID(Packet *p)
	{
		subhook::ScopedHookRemove remove(&GetPacketID_hook);

		const BYTE packetId = (reinterpret_cast<getPacketId>(FUNC_GetPacketID))(p);
		const WORD playerid = p->playerIndex;

		if (packetId == 0xFF)
		{
			return 0xFF;
		}

		if (packetId == incoming_packets::ID_DISCORD_USER)
		{
			if (Players.find(playerid) == Players.end())
			{
				Players.insert({ playerid, std::make_shared<Player>() });

				RakNet::BitStream bs;
				bs.Write(static_cast<uint8_t>(outgoing_packets::ID_INITIALIZE));
				bs.Write(static_cast<uint8_t>(Application::application_id.length() + 1));
				bs.Write(Application::application_id.c_str(), Application::application_id.length() + 1);
				bs.Write(static_cast<uint8_t>(Application::details.length() + 1));
				bs.Write(Application::details.c_str(), Application::details.length() + 1);
				bs.Write(static_cast<uint8_t>(Application::state.length() + 1));
				bs.Write(Application::state.c_str(), Application::state.length() + 1);
				bs.Write(static_cast<uint8_t>(Application::large_image.length() + 1));
				bs.Write(Application::large_image.c_str(), Application::large_image.length() + 1);
				bs.Write(static_cast<uint8_t>(Application::large_image_text.length() + 1));
				bs.Write(Application::large_image_text.c_str(), Application::large_image_text.length() + 1);
				bs.Write(static_cast<uint8_t>(Application::small_image.length() + 1));
				bs.Write(Application::small_image.c_str(), Application::small_image.length() + 1);
				bs.Write(static_cast<uint8_t>(Application::small_image_text.length() + 1));
				bs.Write(Application::small_image_text.c_str(), Application::small_image_text.length() + 1);
				pRakServer->Send(&bs, HIGH_PRIORITY, RELIABLE, 0, pRakServer->GetPlayerIDFromIndex(playerid), false);
			}
		}
		else if (packetId == incoming_packets::ID_PLAYER_DISCONNECT || packetId == incoming_packets::ID_PLAYER_TIMEOUT)
		{
			if (Players.find(playerid) != Players.end())
			{
				Players.erase(playerid);
			}
		}

		if (!GetPacketID_hook.GetTrampoline())
		{
			return packetId;
		}
		else
		{
			return (reinterpret_cast<getPacketId>(GetPacketID_hook.GetTrampoline()))(p);
		}
	}
}
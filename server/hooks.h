#ifndef _HOOKS_H
#define _HOOKS_H

#include "main.h"

namespace Hooks
{
	enum incoming_packets
	{
		ID_PLAYER_DISCONNECT = 32,
		ID_PLAYER_TIMEOUT = 33,
		ID_DISCORD_USER = 253
	};

	enum outgoing_packets
	{
		ID_INITIALIZE = 248,
		ID_SET_DETAILS = 249,
		ID_SET_STATE = 250,
		ID_SET_LARGE_IMAGE = 251,
		ID_SET_LARGE_IMAGE_TEXT = 252,
		ID_SET_SMALL_IMAGE = 253,
		ID_SET_SMALL_IMAGE_TEXT = 254
	};

	namespace Application
	{
		extern std::string application_id;
		extern std::string details;
		extern std::string state;
		extern std::string large_image;
		extern std::string large_image_text;
		extern std::string small_image;
		extern std::string small_image_text;
	}

	extern RakServer* pRakServer;
	extern DWORD FUNC_GetPacketID;
	extern subhook::Hook GetPacketID_hook;

	BYTE HOOK_GetPacketID(Packet *p);
}

#endif
#include "natives.h"

// native DRP_InitializeDiscordPlugin(const application_id[], const details[], const state[], const large_image[], const large_image_text[], const small_image[], const small_image_text[]);
cell AMX_NATIVE_CALL Natives::InitializeDiscordPlugin(AMX* amx, cell* params)
{
	Hooks::Application::application_id = amx_GetCppString(amx, params[1]);
	Hooks::Application::details = amx_GetCppString(amx, params[2]);
	Hooks::Application::state = amx_GetCppString(amx, params[3]);
	Hooks::Application::large_image = amx_GetCppString(amx, params[4]);
	Hooks::Application::large_image_text = amx_GetCppString(amx, params[5]);
	Hooks::Application::small_image = amx_GetCppString(amx, params[6]);
	Hooks::Application::small_image_text = amx_GetCppString(amx, params[7]);
	return 1;
}

// native DRP_IsPlayerUsingClientPlugin(const playerid);
cell AMX_NATIVE_CALL Natives::IsPlayerUsingDiscordPlugin(AMX* amx, cell* params)
{
	if (Players.find(params[1]) == Players.end())
	{
		return 0;
	}
	else return 1;
}

// native DRP_GetPlayerDetails(const playerid, details[], const length);
cell AMX_NATIVE_CALL Natives::GetPlayerDetails(AMX* amx, cell* params)
{
	if (Players.find(params[1]) == Players.end())
	{
		return 0;
	}
	else
	{
		const int playerid = params[1];

		amx_SetCppString(amx, params[2], Players[playerid]->details, params[3]);
	}
	return 1;
}

// native DRP_GetPlayerLargeImageKey(const playerid, large_imagekey[], const length);
cell AMX_NATIVE_CALL Natives::GetPlayerLargeImageKey(AMX* amx, cell* params)
{
	if (Players.find(params[1]) == Players.end())
	{
		return 0;
	}
	else
	{
		const int playerid = params[1];

		amx_SetCppString(amx, params[2], Players[playerid]->large_image, params[3]);
	}
	return 1;
}

// native DRP_GetPlayerSmallImageKey(const playerid, small_imagekey[], const length);
cell AMX_NATIVE_CALL Natives::GetPlayerSmallImageKey(AMX* amx, cell* params)
{
	if (Players.find(params[1]) == Players.end())
	{
		return 0;
	}
	else
	{
		const int playerid = params[1];

		amx_SetCppString(amx, params[2], Players[playerid]->small_image, params[3]);
	}
	return 1;
}

// native DRP_GetPlayerSmallImageText(const playerid, small_image_text[], const length);
cell AMX_NATIVE_CALL Natives::GetPlayerSmallImageText(AMX* amx, cell* params)
{
	if (Players.find(params[1]) == Players.end())
	{
		return 0;
	}
	else
	{
		const int playerid = params[1];

		amx_SetCppString(amx, params[2], Players[playerid]->small_image_text, params[3]);
	}
	return 1;
}

// native DRP_GetPlayerLargeImageText(const playerid, large_image_text[], const length);
cell AMX_NATIVE_CALL Natives::GetPlayerLargeImageText(AMX* amx, cell* params)
{
	if (Players.find(params[1]) == Players.end())
	{
		return 0;
	}
	else
	{
		const int playerid = params[1];

		amx_SetCppString(amx, params[2], Players[playerid]->large_image_text, params[3]);
	}
	return 1;
}

// native DRP_GetPlayerState(const playerid, state[], const length);
cell AMX_NATIVE_CALL Natives::GetPlayerState(AMX* amx, cell* params)
{
	if (Players.find(params[1]) == Players.end())
	{
		return 0;
	}
	else
	{
		const int playerid = params[1];

		amx_SetCppString(amx, params[2], Players[playerid]->state, params[3]);
	}
	return 1;
}

// native DRP_SetPlayerDetails(const playerid, const details[]);
cell AMX_NATIVE_CALL Natives::SetPlayerDetails(AMX* amx, cell* params)
{
	if (Players.find(params[1]) == Players.end())
	{
		return 0;
	}
	else
	{
		const int playerid = params[1];

		Players[playerid]->details = amx_GetCppString(amx, params[2]);

		RakNet::BitStream bs;
		bs.Write(static_cast<uint8_t>(Hooks::outgoing_packets::ID_SET_DETAILS));
		bs.Write(static_cast<uint8_t>(Players[playerid]->details.length() + 1));
		bs.Write(Players[playerid]->details.c_str(), Players[playerid]->details.length() + 1);
		Hooks::pRakServer->Send(&bs, HIGH_PRIORITY, RELIABLE, 0, Hooks::pRakServer->GetPlayerIDFromIndex(playerid), false);
	}
	return 1;
}

// native DRP_SetPlayerLargeImageKey(const playerid, const large_image_key[]);
cell AMX_NATIVE_CALL Natives::SetPlayerLargeImageKey(AMX* amx, cell* params)
{
	if (Players.find(params[1]) == Players.end())
	{
		return 0;
	}
	else
	{
		const int playerid = params[1];

		Players[playerid]->large_image = amx_GetCppString(amx, params[2]);

		RakNet::BitStream bs;
		bs.Write(static_cast<uint8_t>(Hooks::outgoing_packets::ID_SET_LARGE_IMAGE));
		bs.Write(static_cast<uint8_t>(Players[playerid]->large_image.length() + 1));
		bs.Write(Players[playerid]->large_image.c_str(), Players[playerid]->large_image.length() + 1);
		Hooks::pRakServer->Send(&bs, HIGH_PRIORITY, RELIABLE, 0, Hooks::pRakServer->GetPlayerIDFromIndex(playerid), false);
	}
	return 1;
}

// native DRP_SetPlayerLargeImageText(const playerid, const large_image_text[]);
cell AMX_NATIVE_CALL Natives::SetPlayerLargeImageText(AMX* amx, cell* params)
{
	if (Players.find(params[1]) == Players.end())
	{
		return 0;
	}
	else
	{
		const int playerid = params[1];

		Players[playerid]->large_image_text = amx_GetCppString(amx, params[2]);

		RakNet::BitStream bs;
		bs.Write(static_cast<uint8_t>(Hooks::outgoing_packets::ID_SET_LARGE_IMAGE_TEXT));
		bs.Write(static_cast<uint8_t>(Players[playerid]->large_image_text.length() + 1));
		bs.Write(Players[playerid]->large_image_text.c_str(), Players[playerid]->large_image_text.length() + 1);
		Hooks::pRakServer->Send(&bs, HIGH_PRIORITY, RELIABLE, 0, Hooks::pRakServer->GetPlayerIDFromIndex(playerid), false);
	}
	return 1;
}

// native DRP_SetPlayerSmallImageKey(const playerid, const small_image_key[]);
cell AMX_NATIVE_CALL Natives::SetPlayerSmallImageKey(AMX* amx, cell* params)
{
	if (Players.find(params[1]) == Players.end())
	{
		return 0;
	}
	else
	{
		const int playerid = params[1];

		Players[playerid]->small_image = amx_GetCppString(amx, params[2]);

		RakNet::BitStream bs;
		bs.Write(static_cast<uint8_t>(Hooks::outgoing_packets::ID_SET_SMALL_IMAGE));
		bs.Write(static_cast<uint8_t>(Players[playerid]->small_image.length() + 1));
		bs.Write(Players[playerid]->small_image.c_str(), Players[playerid]->small_image.length() + 1);
		Hooks::pRakServer->Send(&bs, HIGH_PRIORITY, RELIABLE, 0, Hooks::pRakServer->GetPlayerIDFromIndex(playerid), false);
	}
	return 1;
}

// native DRP_SetPlayerSmallImageText(const playerid, const small_image_text[]);
cell AMX_NATIVE_CALL Natives::SetPlayerSmallImageText(AMX* amx, cell* params)
{
	if (Players.find(params[1]) == Players.end())
	{
		return 0;
	}
	else
	{
		const int playerid = params[1];

		Players[playerid]->small_image_text = amx_GetCppString(amx, params[2]);

		RakNet::BitStream bs;
		bs.Write(static_cast<uint8_t>(Hooks::outgoing_packets::ID_SET_SMALL_IMAGE_TEXT));
		bs.Write(static_cast<uint8_t>(Players[playerid]->small_image_text.length() + 1));
		bs.Write(Players[playerid]->small_image_text.c_str(), Players[playerid]->small_image_text.length() + 1);
		Hooks::pRakServer->Send(&bs, HIGH_PRIORITY, RELIABLE, 0, Hooks::pRakServer->GetPlayerIDFromIndex(playerid), false);
	}
	return 1;
}

// native DRP_SetPlayerState(const playerid, const state[]);
cell AMX_NATIVE_CALL Natives::SetPlayerState(AMX* amx, cell* params)
{
	if (Players.find(params[1]) == Players.end())
	{
		return 0;
	}
	else
	{
		const int playerid = params[1];

		Players[playerid]->state = amx_GetCppString(amx, params[2]);

		RakNet::BitStream bs;
		bs.Write(static_cast<uint8_t>(Hooks::outgoing_packets::ID_SET_STATE));
		bs.Write(static_cast<uint8_t>(Players[playerid]->state.length() + 1));
		bs.Write(Players[playerid]->state.c_str(), Players[playerid]->state.length() + 1);
		Hooks::pRakServer->Send(&bs, HIGH_PRIORITY, RELIABLE, 0, Hooks::pRakServer->GetPlayerIDFromIndex(playerid), false);
	}
	return 1;
}

AMX_NATIVE_INFO Natives::Functions[] =
{
	{ "DRP_InitializeDiscordPlugin", Natives::InitializeDiscordPlugin },
	{ "DRP_IsPlayerUsingClientPlugin", Natives::IsPlayerUsingDiscordPlugin },
	{ "DRP_GetPlayerDetails", Natives::GetPlayerDetails },
	{ "DRP_GetPlayerLargeImageKey", Natives::GetPlayerLargeImageKey },
	{ "DRP_GetPlayerSmallImageKey", Natives::GetPlayerSmallImageKey },
	{ "DRP_GetPlayerSmallImageText", Natives::GetPlayerSmallImageText },
	{ "DRP_GetPlayerLargeImageText", Natives::GetPlayerLargeImageText },
	{ "DRP_GetPlayerState", Natives::GetPlayerState },
	{ "DRP_SetPlayerDetails", Natives::SetPlayerDetails },
	{ "DRP_SetPlayerLargeImageKey", Natives::SetPlayerLargeImageKey },
	{ "DRP_SetPlayerLargeImageText", Natives::SetPlayerLargeImageText },
	{ "DRP_SetPlayerSmallImageKey", Natives::SetPlayerSmallImageKey },
	{ "DRP_SetPlayerSmallImageText", Natives::SetPlayerSmallImageText },
	{ "DRP_SetPlayerState", Natives::SetPlayerState },
	{ 0, 0 }
};
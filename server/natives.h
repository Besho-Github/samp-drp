#ifndef _NATIVES_H
#define _NATIVES_H

#include "main.h"

namespace Natives
{
	cell AMX_NATIVE_CALL InitializeDiscordPlugin(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL IsPlayerUsingDiscordPlugin(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL GetPlayerDetails(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL GetPlayerLargeImageKey(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL GetPlayerSmallImageKey(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL GetPlayerSmallImageText(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL GetPlayerLargeImageText(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL GetPlayerState(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL SetPlayerDetails(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL SetPlayerLargeImageKey(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL SetPlayerLargeImageText(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL SetPlayerSmallImageKey(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL SetPlayerSmallImageText(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL SetPlayerState(AMX* amx, cell* params);

	extern AMX_NATIVE_INFO Functions[];
}
#endif
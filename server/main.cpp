#include "main.h"

void **ppPluginData;

extern void *pAMXFunctions;

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{ 
	ppPluginData = ppData;
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = reinterpret_cast<logprintf_t>(ppData[PLUGIN_DATA_LOGPRINTF]);
	
	#ifdef _WIN32
		Hooks::FUNC_GetPacketID = FindPattern("\x8B\x44\x24\x04\x85\xC0\x75\x03\x0C\xFF\xC3", "xxxxxxx???x");
	#else
		Hooks::FUNC_GetPacketID = FindPattern("\x55\xB8\x00\x00\x00\x00\x89\xE5\x8B\x55\x00\x85\xD2", "xx????xxxx?xx");
	#endif

	if (Hooks::FUNC_GetPacketID != NULL)
	{
		Hooks::GetPacketID_hook.Install(reinterpret_cast<void*>(Hooks::FUNC_GetPacketID), reinterpret_cast<void*>(Hooks::HOOK_GetPacketID));
		logprintf("Discord Rich Presence Plugin Loaded.");
	}
	else
	{
		logprintf("Error: SA-MP version not supported.");
	}

	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	Players.clear();

	logprintf("Discord Rich Presence Plugin Unloaded");
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}


PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	static bool rakserver_hook = false;

	if (!rakserver_hook)
	{
		rakserver_hook = true;

		int(*pfn_GetRakServer)(void) = (int(*)(void))ppPluginData[PLUGIN_DATA_RAKSERVER];
		Hooks::pRakServer = reinterpret_cast<RakServer*>(pfn_GetRakServer());
	}

	return amx_Register(amx, Natives::Functions, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}
#include "addresses.h"

namespace Addresses
{
	DWORD ReceivePacket_offset = NULL;
	DWORD PlayerName_offset = NULL; // This offset is for the first name you joined it and it won't update.
	DWORD PlayerNameTwo_offset = NULL; // This offset is for name changes, but will be NULL if it wasn't changed once, so we need both.

	bool GetAddresses(const DWORD &samp_module)
	{
		switch (*reinterpret_cast<BYTE*>(samp_module + 0x129)) // Client Version
		{
			case SAMP_037_R1: // 0.3.7-R1
			{
				ReceivePacket_offset = 0x31710;
				PlayerName_offset = 0x219A6F;
				PlayerNameTwo_offset = 0x12D900;
				break;
			}
			case SAMP_037_R2: // 0.3.7-R2
			{
				ReceivePacket_offset = 0x317F0;
				PlayerName_offset = 0x219A77;
				PlayerNameTwo_offset = 0x12D900;
				break;
			}
			case SAMP_03DL_R1: // 0.3.DL-R1
			{
				ReceivePacket_offset = 0x34CC0;
				PlayerName_offset = 0x2AC187;
				PlayerNameTwo_offset = 0x17FBC0;
				break;
			}
			default:
			{
				return false;
			}
		}
		return true;
	}

	std::string GetPlayerName(const DWORD &samp_module)
	{
		if ((reinterpret_cast<const char*>(samp_module + PlayerNameTwo_offset) != NULL) && (reinterpret_cast<const char*>(samp_module + PlayerNameTwo_offset)[0] == '\0'))
		{
			return std::string(reinterpret_cast<const char*>(samp_module + PlayerName_offset));
		}
		else
		{
			return std::string(reinterpret_cast<const char*>(samp_module + PlayerNameTwo_offset));
		}
	}
}
#ifndef _ADDRESSES_H_
#define _ADDRESSES_H_

#include "dllmain.h"

#define SAMP_037_R1 (0xF4)
#define SAMP_037_R2 (0xC)
#define SAMP_03DL_R1 (0x31)

namespace Addresses
{
	extern DWORD ReceivePacket_offset;
	extern DWORD PlayerName_offset;
	extern DWORD PlayerNameTwo_offset;

	bool GetAddresses(const DWORD &samp_module);
	std::string GetPlayerName(const DWORD &samp_module);
}

#endif 
#ifndef _MAIN_H_
#define _MAIN_H_

#ifdef _WIN32
	#include <Windows.h>
	#include <Psapi.h>
#endif

#include <unordered_map>
#include <memory>

#include "SDK/amx/amx2.h"
#include "SDK/plugincommon.h"
#include "subhook/subhook.h"
#include <raknet/BitStream.h>

#include "Structs.h"
#include "player.h"
#include "utils.h"
#include "natives.h"
#include "hooks.h"

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long DWORD;
typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef float FLOAT;

#endif
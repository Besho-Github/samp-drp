#ifndef _DRP_UTILS_H_
#define _DRP_UTILS_H_

#include "dllmain.h"

namespace Utils
{
	bool fexists(const char *filename);
	LPVOID DetourFunc(BYTE* Source, BYTE* Destination, int numbytes);
	void ReadSampCommandLine(std::string commandline, std::string &server_ip, std::string &server_port);
}

#endif
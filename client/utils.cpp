#include "utils.h"

namespace Utils
{
	bool fexists(const char* filename)
	{
		std::ifstream ifile(filename);
		return (bool)ifile;
	}

	LPVOID DetourFunc(BYTE* Source, BYTE* Destination, int numbytes)
	{
		BYTE * AllocJmp;
		DWORD dwProtect;
		DWORD JmpOff;
		DWORD val;

		if (Source == NULL) return NULL;
		if (Destination == NULL) return NULL;
		if (numbytes < 5) return NULL;

		AllocJmp = (BYTE*)malloc(5 + numbytes);

		VirtualProtect(AllocJmp, 5 + numbytes, PAGE_EXECUTE_READWRITE, &dwProtect);
		VirtualProtect(Source, numbytes, PAGE_EXECUTE_READWRITE, &dwProtect);

		memcpy(AllocJmp, Source, numbytes);

		if (AllocJmp[0] == 0xE9 || AllocJmp[0] == 0xE8)
		{
			val = *(DWORD*)(&AllocJmp[1]);
			*(DWORD*)(&AllocJmp[1]) = val + Source - AllocJmp;
		}

		AllocJmp += numbytes;
		DWORD JmpToOrigin = (DWORD)((Source + numbytes) - (AllocJmp + 5));

		AllocJmp[0] = 0xE9;
		*(DWORD*)(AllocJmp + 1) = JmpToOrigin;

		JmpOff = (DWORD)(Destination - Source) - 5;

		AllocJmp -= numbytes;

		Source[0] = 0xE9;
		*(DWORD*)(Source + 1) = JmpOff;

		VirtualProtect(Source, numbytes, dwProtect, &dwProtect);

		return AllocJmp;
	}

	void ReadSampCommandLine(std::string commandline, std::string &server_ip, std::string &server_port)
	{
		for (auto i = commandline.begin(); i < commandline.end(); i++)
		{
			if (*i == '-')
			{
				i++;

				switch (*i)
				{
					case 'h':
					{
						i += 2;

						while (i != commandline.end() && *i != ' ')
						{
							server_ip += *i;
							i++;
						}
						break;
					}
					case 'p':
					{
						i += 2;

						while (i != commandline.end() && *i != ' ')
						{
							server_port += *i;
							i++;
						}
						break;
					}
				}
			}
		}
	}
}
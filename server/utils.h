#ifndef _UTILS_H
#define _UTILS_H

#include "main.h"

typedef void(*logprintf_t)(char* format, ...);
extern logprintf_t logprintf;

bool memory_compare(const BYTE *data, const BYTE *pattern, const char *mask);
DWORD FindPattern(char *pattern, char *mask);

#endif

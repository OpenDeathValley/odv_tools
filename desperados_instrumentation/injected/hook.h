#ifndef HOOK_H_
#define HOOK_H_

#include "dbg.h"
#include "pestuff.h"
#include "ddproxy.h"

#pragma warning(disable: 4201)  // Disable warning message for C4201 - use of nameless struct/union
#include "ddraw.h"

#include <windows.h>

#define GUID_FORMAT "%08lX-%04hX-%04hX-%02hhX%02hhX-%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX"
#define PGUID_ARG(guid) guid->Data1, guid->Data2, guid->Data3, guid->Data4[0], guid->Data4[1], guid->Data4[2], guid->Data4[3], guid->Data4[4], guid->Data4[5], guid->Data4[6], guid->Data4[7]

VOID DoHook(VOID);

#endif // HOOK_H_
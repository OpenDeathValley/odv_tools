#ifndef HOOK_H_
#define HOOK_H_

#include "dbg.h"
#include "pestuff.h"
#include "ddproxy.h"
#include "instruvm.h"

#pragma warning(disable: 4201)  // Disable warning message for C4201 - use of nameless struct/union
#include "ddraw.h"

#include <windows.h>

#define LDE_X86 0

#ifdef __cplusplus
    extern "C"
#endif
int __stdcall LDE(void* address , DWORD type);

#define GUID_FORMAT "%08lX-%04hX-%04hX-%02hhX%02hhX-%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX"
#define PGUID_ARG(guid) guid->Data1, guid->Data2, guid->Data3, guid->Data4[0], guid->Data4[1], guid->Data4[2], guid->Data4[3], guid->Data4[4], guid->Data4[5], guid->Data4[6], guid->Data4[7]

typedef struct _PUSHED_REGS {
    DWORD Edi;
    DWORD Esi;
    DWORD Ebp;
    DWORD Esp;  
    DWORD Ebx; 
    DWORD Edx; 
    DWORD Ecx;
    DWORD Eax;
} PUSHED_REGS, *PPUSHED_REGS;

VOID DoHook(VOID);
VOID MakeHook(VOID);

#endif // HOOK_H_
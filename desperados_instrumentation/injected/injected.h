#ifndef _INJECTED_H_
#define _INJECTED_H_

#include <stdio.h>
#include <Windows.h>

#include "dbg.h"
#include "pestuff.h"
#include "hook.h"

typedef struct _PE_INFO {
    ULONG_PTR ModuleBase;
    DWORD ModuleSize;
    ULONG_PTR ModuleInjectedBase;
    ULONG_PTR ModuleInjectedSize;
    ULONG_PTR VAOfEntryPoint;
    ULONG_PTR DDRawBase;
    ULONG_PTR DDRawSize;
    BYTE ByteReplaced;
} PE_INFO, *PPE_INFO;

#endif  // _INJECTED_H_
#ifndef _INSTRUVM_H_
#define _INSTRUVM_H_

#include <stdio.h>
#include <Windows.h>

#include "hook.h"
#include "dbg.h"

DWORD HookScriptEntry(VOID);
DWORD HookVMEntry(VOID);
DWORD HookVMExecOpcode(VOID);

typedef struct _SCRIPT_INFO {
    DWORD dwUnk;
    PCHAR pName;
    DWORD dwSize;
} SCRIPT_INFO, *PSCRIPT_INFO;

typedef struct _CUNK_VM {
    DWORD dwUnk_dword_00;
    DWORD dwUnk_dword_01;
    DWORD dwUnk_dword_02;
    DWORD dwUnk_dword_03;
    DWORD dwUnk_dword_04;
    DWORD dwUnk_dword_05;
    DWORD dwUnk_dword_06;
} CUNK_VM, *PCUNK_VM;

#endif  // _INSTRUVM_H_
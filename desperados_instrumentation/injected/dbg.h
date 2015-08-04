#ifndef _DBG_H
#define _DBG_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define FILE_DBG "dbg_msg.txt"

VOID MakeConsole(VOID);
VOID hexdump(PVOID *data, int size);
VOID dbg_msg(LPCSTR szFormat, ...);

#endif

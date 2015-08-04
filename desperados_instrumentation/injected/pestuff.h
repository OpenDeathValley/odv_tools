#ifndef PESTUFF_H_
#define PESTUFF_H_

#include "dbg.h"

#include <windows.h>
#include <Dbghelp.h>

enum CHAMP_PE
{
    EXPORT_TABLE,
    EXPORT_TABLE_SIZE,
    SIZE_OF_IMAGE,
    NB_SECTIONS,
    PE_SECTIONS,
    ENTRY_POINT
};

enum CHAMP_SECTION
{
    SEC_NAME = 0,
    SEC_VIRT_SIZE,
    SEC_VIRT_ADDR,
    SEC_RAW_SIZE,
    SEC_RAW_ADDR,
    SEC_CHARAC
};

PVOID ParsePE(ULONG_PTR hMod, DWORD dwChamp);
BOOL ReplaceIATEntryInMod(HMODULE hMod, LPCSTR ModName, PROC pfnCurrent, PROC pfnNew);

#endif // PESTUFF_H_
#include "pestuff.h"

PVOID ParsePE(ULONG_PTR hMod, DWORD dwChamp)
{
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)hMod;
    PIMAGE_NT_HEADERS pPE;
    PIMAGE_DATA_DIRECTORY rvas;
    DWORD nmbOfRva;

    if (pDosHeader->e_magic != 'ZM')
        return (PVOID)NULL;
    pPE = (PIMAGE_NT_HEADERS)(pDosHeader->e_lfanew + (BYTE *)hMod);
    if (pPE->Signature != 'EP')
        return (PVOID)NULL;
    pPE = (PIMAGE_NT_HEADERS)(pDosHeader->e_lfanew + (BYTE *)hMod);
    nmbOfRva = pPE->OptionalHeader.NumberOfRvaAndSizes;
    rvas = (PIMAGE_DATA_DIRECTORY) &pPE->OptionalHeader.DataDirectory;
    switch(dwChamp) {
        case SIZE_OF_IMAGE:
            return (PVOID)pPE->OptionalHeader.SizeOfImage;
        case NB_SECTIONS:
            return (PVOID)(DWORD)pPE->FileHeader.NumberOfSections;
        case PE_SECTIONS:
            return (PVOID)IMAGE_FIRST_SECTION(pPE);//(void*)((BYTE *)pPE + sizeof(IMAGE_NT_HEADERS64));
        case EXPORT_TABLE:
            if (nmbOfRva >= 1)
                return (PVOID)(rvas[0].VirtualAddress);
            else
                return (PVOID)NULL;
        case EXPORT_TABLE_SIZE:
            if (nmbOfRva >= 1)
                return (PVOID)(rvas[0].Size);
            else
                return (PVOID)NULL;
        case ENTRY_POINT:
            return (PVOID)pPE->OptionalHeader.AddressOfEntryPoint;
    }
    return (PVOID)NULL;
}

BOOL ReplaceIATEntryInMod(HMODULE hMod, LPCSTR ModName, PROC pfnCurrent, PROC pfnNew)
{
    ULONG Size = 0;
    PIMAGE_IMPORT_DESCRIPTOR pImportDesc = NULL;
    PIMAGE_THUNK_DATA pThunk = NULL;
    DWORD dwOldProt = 0;
    PROC* ppfn = NULL;
    LPCSTR ActualModName;

    pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToDataEx(hMod, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &Size, NULL);
    if (pImportDesc == NULL) {
        dbg_msg("[-] ImageDirectoryEntryToDataEx failed\n");
        return FALSE;
    }
    for (; pImportDesc->Name; pImportDesc++) {
        ActualModName = (LPCSTR)((PBYTE) hMod + pImportDesc->Name);
        if (lstrcmpiA(ActualModName, ModName) == 0)
            break;
    }
    if (pImportDesc->Name == 0) {
        dbg_msg("[-] ReplaceIATEntryInMod - no import found for %s\n", ModName);
        return FALSE;
    }
    pThunk = (PIMAGE_THUNK_DATA)((PBYTE) hMod + pImportDesc->FirstThunk);
    for (; pThunk->u1.Function; pThunk++) {
        ppfn = (PROC*) &pThunk->u1.Function;
        if (*ppfn == pfnCurrent) {
            VirtualProtect(ppfn, sizeof(pfnNew), PAGE_EXECUTE_READWRITE, &dwOldProt);
            *ppfn = pfnNew;
            VirtualProtect(ppfn, sizeof(pfnNew), dwOldProt, &dwOldProt);
            return TRUE;
        }
    }
    return FALSE;
}
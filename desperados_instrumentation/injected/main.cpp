#include "injected.h"

PVOID protVectoredHandler;
PE_INFO pinfo = {0};

LONG CALLBACK ProtectionFaultVectoredHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
    DWORD dwOldProt;

    if (ExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_BREAKPOINT) {
        dbg_msg("[+] ProtectionFaultVectoredHandler - EIP           : 0x%08X\n", ExceptionInfo->ContextRecord->Eip);
        if (ExceptionInfo->ContextRecord->Eip == pinfo.VAOfEntryPoint) {
            VirtualProtect((LPVOID)(pinfo.VAOfEntryPoint), 0x1, PAGE_EXECUTE_READWRITE, &dwOldProt);
            *(BYTE*)(pinfo.VAOfEntryPoint) = pinfo.ByteReplaced;
            VirtualProtect((LPVOID)(pinfo.VAOfEntryPoint), 0x1, dwOldProt, &dwOldProt);
            pinfo.DDRawBase = (ULONG_PTR)GetModuleHandleA("DDRAW.dll");
            pinfo.DDRawSize = (ULONG_PTR)ParsePE(pinfo.DDRawBase, SIZE_OF_IMAGE);
            DoHook();
            MakeHook();
            return EXCEPTION_CONTINUE_EXECUTION;
        }
    }
    else if (ExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_ACCESS_VIOLATION) {
        if (!(ExceptionInfo->ContextRecord->Eip >= pinfo.DDRawBase && ExceptionInfo->ContextRecord->Eip <= (pinfo.DDRawBase + pinfo.DDRawSize))) {
            dbg_msg("[+] ProtectionFaultVectoredHandler - EIP           : 0x%08X\n", ExceptionInfo->ContextRecord->Eip);
        }
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    DWORD dwOldProt;
    (void)hinstDLL;
    (void)lpReserved;

    if (fdwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(GetModuleHandleA(NULL));
        MakeConsole();
        dbg_msg("[+] DLL_PROCESS_ATTACH\n");
        protVectoredHandler = AddVectoredExceptionHandler(0, ProtectionFaultVectoredHandler);
        pinfo.ModuleBase = (ULONG_PTR)GetModuleHandleA(NULL);
        pinfo.VAOfEntryPoint = (ULONG_PTR)ParsePE(pinfo.ModuleBase, ENTRY_POINT) + pinfo.ModuleBase;
        dbg_msg("[+] ModuleBase         : 0x%08X\n", pinfo.ModuleBase);
        pinfo.ModuleInjectedBase = (ULONG_PTR)hinstDLL;
        dbg_msg("[+] ModuleInjectedBase : 0x%08X\n", pinfo.ModuleInjectedBase);
        pinfo.ModuleInjectedSize = (ULONG_PTR)ParsePE(pinfo.ModuleInjectedBase, SIZE_OF_IMAGE);
        dbg_msg("[+] ModuleInjectedSize : 0x%08X\n", pinfo.ModuleInjectedBase);
        // PUT BP AT ENTRYPOINT
        VirtualProtect((LPVOID)(pinfo.VAOfEntryPoint), 0x1, PAGE_EXECUTE_READWRITE, &dwOldProt);
        pinfo.ByteReplaced = *(BYTE*)(pinfo.VAOfEntryPoint);
        *(BYTE*)(pinfo.VAOfEntryPoint) = 0xCC;
        VirtualProtect((LPVOID)(pinfo.VAOfEntryPoint), 0x1, dwOldProt, &dwOldProt);
    }
    return TRUE;
}
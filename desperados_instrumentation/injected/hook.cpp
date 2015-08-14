#include "hook.h"

extern struct proxy_IDirectDraw *proxy_lplpDD;
extern DWORD g_dwWidth;
extern DWORD g_dwHeight;
WNDPROC OldWndProc;

LRESULT __stdcall MyWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT Ps;
    HDC hDC;

    switch (Msg) {
        case WM_PAINT:
            hDC = BeginPaint(hWnd, &Ps);
            EndPaint(hWnd, &Ps);
            return TRUE;
    }
    return CallWindowProc(OldWndProc, hWnd, Msg, wParam, lParam);
}

HWND __stdcall MyCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName,
    DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu,
    HINSTANCE hInstance, LPVOID lpParam)
{
    HWND w;
    DWORD return_addr;

    __asm {
        mov eax, [ebp + 4]
        mov return_addr, eax
    }

    dbg_msg("[+] CreateWindowExA(dwExStyle = 0x%08X,\n", dwExStyle);
    dbg_msg("    lpClassName = %s, lpWindowName = %s\n", lpClassName, lpWindowName);
    dbg_msg("    dwStyle = 0x%08X, x = 0x%08X (%d), y = 0x%08X (%d),\n", dwStyle, x, x, y, y);
    dbg_msg("    nWidth = 0x%08X (%d), nHeight = 0x%08X (%d),\n", nWidth, nWidth, nHeight, nHeight);
    dbg_msg("    hWndParent = 0x%08X, hMenu = 0x%08X, hInstance = 0x%08X\n", hWndParent, hMenu, hInstance);
    dbg_msg("    lpParam = 0x%08X); return_addr = 0x%08X\n", lpParam, return_addr);

    nWidth = 640;
    nHeight = 480;
    dwStyle = WS_OVERLAPPEDWINDOW;

    w = CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
    dbg_msg("[+] w = 0x%08X\n", w);
    OldWndProc = (WNDPROC)SetWindowLong(w, GWL_WNDPROC, (long)MyWndProc);
    dbg_msg("[+] OldWndProc = 0x%08X\n", OldWndProc);
    return w;
}

BOOL __stdcall MySetWindowPos(  _In_     HWND hWnd,
  _In_opt_ HWND hWndInsertAfter,
  _In_     int  X,
  _In_     int  Y,
  _In_     int  cx,
  _In_     int  cy,
  _In_     UINT uFlags)
{
    dbg_msg("[+] SetWindowPos(cx = 0x%08X, cy = 0x%08X\n", cx, cy);
    return SetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
}


HRESULT WINAPI MyDirectDrawCreate(GUID FAR *lpGUID, LPDIRECTDRAW FAR *lplpDD, IUnknown FAR *pUnkOuter)
{
    DWORD return_addr;
    HRESULT hRes;

    __asm {
        mov eax, [ebp + 4]
        mov return_addr, eax
    }
    if (lpGUID) {
        dbg_msg("[+] DirectDrawCreate(lpGUID = {" GUID_FORMAT "},\n", PGUID_ARG(lpGUID));
    }
    else {
        dbg_msg("[+] DirectDrawCreate(lpGUID = NULL,\n");
    }
    dbg_msg("   LPDIRECTDRAW = 0x%08X, pUnkOuter = 0x%08X); return_addr = 0x%08X\n", lplpDD, pUnkOuter, return_addr);
    hRes = DirectDrawCreate(lpGUID, lplpDD, pUnkOuter);
    if (hRes == DD_OK) {
        proxy_lplpDD = new proxy_IDirectDraw(*lplpDD);
        *lplpDD = (LPDIRECTDRAW)proxy_lplpDD;
    }
    return hRes;
}

VOID DoHook(VOID)
{
    if (ReplaceIATEntryInMod(GetModuleHandle(NULL), "USER32.dll",
        GetProcAddress(GetModuleHandle("USER32.dll"), "SetWindowPos"),
        (PROC)MySetWindowPos) == FALSE) {
        dbg_msg("[+] ReplaceIATEntryInMod failed for SetWindowPos\n");
    }
    if (ReplaceIATEntryInMod(GetModuleHandle(NULL), "USER32.dll",
        GetProcAddress(GetModuleHandle("USER32.dll"), "CreateWindowExA"),
        (PROC)MyCreateWindowExA) == FALSE) {
        dbg_msg("[+] ReplaceIATEntryInMod failed for CreateWindowExA\n");
    }
    if (ReplaceIATEntryInMod(GetModuleHandle(NULL), "DDRAW.dll",
        GetProcAddress(GetModuleHandle("DDRAW.dll"), "DirectDrawCreate"),
        (PROC)MyDirectDrawCreate) == FALSE) {
        dbg_msg("[+] ReplaceIATEntryInMod failed for DirectDrawCreate\n");
    }
}

BOOL SetupHook(char *module, char *name_export, void *Hook_func, void *trampo, DWORD addr)
{
    DWORD dwOldProtect;
    DWORD dwLen = 0;
    FARPROC Proc;
    
    if (addr != 0) {
        Proc = (FARPROC)addr;
    }
    else {
        Proc = GetProcAddress(GetModuleHandleA(module), name_export);
        if (!Proc) {
            dbg_msg("[-] GetProcAddress() failed: %lu\n", GetLastError());
            return FALSE;
        }
    }
    while (dwLen < 5)
        dwLen += LDE((BYTE*)Proc + dwLen , LDE_X86);
    memcpy(trampo, Proc, dwLen);
    *(BYTE*)((BYTE*)trampo + dwLen) = 0xE9;
    *(DWORD*)((BYTE*)trampo + dwLen + 1) = (BYTE*)Proc - (BYTE*)trampo - 5;
    VirtualProtect(Proc, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    *(BYTE*)Proc = 0xE9;
    *(DWORD*)((char*)Proc + 1) = (BYTE*)Hook_func - (BYTE*)Proc - 5;
    VirtualProtect(Proc, dwLen, dwOldProtect, &dwOldProtect);
    return TRUE;
}

extern DWORD (__stdcall *ResumeScriptEntry)(VOID);
extern DWORD (__stdcall *ResumeVMEntry)(VOID);
extern DWORD (__stdcall *ResumeVMExecOpcode)(VOID);

/* 
.text:00618000 8B 44 24 04             mov     eax, [esp+arg_0]
.text:00618004 56                      push    esi
.text:00618005 8B F1                   mov     esi, ecx
.text:00618007 8B 4E 58                mov     ecx, [esi+58h]
.text:0061800A 50                      push    eax
.text:0061800B 51                      push    ecx
.text:0061800C 8B 4E 04                mov     ecx, [esi+4]
.text:0061800F E8 1C 08 00 00          call    sub_
*/
unsigned char PatternHook_0[20] = {
    0x8B, 0x44, 0x24, 0x04, 0x56, 0x8B, 0xF1, 0x8B, 0x4E, 0x58, 0x50, 0x51,
    0x8B, 0x4E, 0x04, 0xE8, 0x1C, 0x08, 0x00, 0x00
};


/*
.text:00618050 53                                      push    ebx
.text:00618051 55                                      push    ebp
.text:00618052 56                                      push    esi
.text:00618053 83 CB FF                                or      ebx, 0FFFFFFFFh
.text:00618056 57                                      push    edi
.text:00618057 8B F1                                   mov     esi, ecx
.text:00618059 8B FB                                   mov     edi, ebx
.text:0061805B
.text:0061805B                         loc_61805B:
.text:0061805B
.text:0061805B 8B 4E 58                                mov     ecx, [esi+58h]
.text:0061805E 8B 46 3C                                mov     eax, [esi+3Ch]
.text:00618061 8B A9 C0 00 00 00                       mov     ebp, [ecx+0C0h]
*/
unsigned char PatternHook_1[20] = {
    0x53, 0x55, 0x56, 0x83, 0xCB, 0xFF, 0x57, 0x8B, 0xF1, 0x8B, 0xFB, 0x8B,
    0x4E, 0x58, 0x8B, 0x46, 0x3C, 0x8B, 0xA9, 0xC0
};

/* 
.text:0061805B 8B 4E 58                                mov     ecx, [esi+58h]
.text:0061805E 8B 46 3C                                mov     eax, [esi+3Ch]
.text:00618061 8B A9 C0 00 00 00                       mov     ebp, [ecx+0C0h]
.text:00618067 8D 14 40                                lea     edx, [eax+eax*2]
.text:0061806A 8D 54 95 00                             lea     edx, [ebp+edx*4+0]
*/
unsigned char PatternHook_2[20] = {
    0x8B, 0x4E, 0x58, 0x8B, 0x46, 0x3C, 0x8B, 0xA9, 0xC0, 0x00, 0x00, 0x00,
    0x8D, 0x14, 0x40, 0x8D, 0x54, 0x95, 0x00, 0x89
};


VOID MakeHook(VOID)
{
    if (!memcmp((const void*)0x618000, PatternHook_0, sizeof (PatternHook_0))) {
        ResumeScriptEntry = (DWORD(__stdcall *)(VOID))VirtualAlloc(0, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        memset(ResumeScriptEntry, 0x90, 0x1000);
        SetupHook("MOO", "MOO", &HookScriptEntry, ResumeScriptEntry, 0x618000);
    }
    else {
        dbg_msg("[-] can't match pattern for hooking 0\n");
    }
    if (!memcmp((const void*)0x618050, PatternHook_1, sizeof (PatternHook_1))) {
        ResumeVMEntry = (DWORD(__stdcall *)(VOID))VirtualAlloc(0, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        memset(ResumeVMEntry, 0x90, 0x1000);
        SetupHook("MOO", "MOO", &HookVMEntry, ResumeVMEntry, 0x618050);
    }
    else {
        dbg_msg("[-] can't match pattern for hooking 1\n");
    }    
    if (!memcmp((const void*)0x0061805B, PatternHook_2, sizeof (PatternHook_2))) {
        ResumeVMExecOpcode = (DWORD(__stdcall *)(VOID))VirtualAlloc(0, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        memset(ResumeVMExecOpcode, 0x90, 0x1000);
        SetupHook("MOO", "MOO", &HookVMExecOpcode, ResumeVMExecOpcode, 0x0061805B);
    }
    else {
        dbg_msg("[-] can't match pattern for hooking 1\n");
    }

}
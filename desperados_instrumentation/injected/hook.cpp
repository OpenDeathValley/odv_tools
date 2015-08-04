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
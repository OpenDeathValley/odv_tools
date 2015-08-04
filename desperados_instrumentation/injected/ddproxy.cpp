#include "ddproxy.h"

extern PE_INFO pinfo;
struct proxy_IDirectDraw *proxy_lplpDD = NULL;
struct proxy_IDirectDraw7 *proxy7_lplpDD = NULL;
HWND g_hWnd;
PDWORD g_pdwPalette16BPP = NULL;
BOOL g_bProxyDbg = FALSE;

LPCSTR GetStrDDError(HRESULT hRes)
{
    switch (hRes) {
        case DDERR_INCOMPATIBLEPRIMARY:
            return ("DDERR_INCOMPATIBLEPRIMARY");
        case DDERR_INVALIDCAPS:
            return ("DDERR_INVALIDCAPS");
        case DDERR_INVALIDOBJECT:
            return ("DDERR_INVALIDOBJECT");
        case DDERR_INVALIDPARAMS:
            return ("DDERR_INVALIDPARAMS");
        case DDERR_INVALIDPIXELFORMAT:
            return ("DDERR_INVALIDPIXELFORMAT");
        case DDERR_NOALPHAHW:
            return ("DDERR_NOALPHAHW");
        case DDERR_NOCOOPERATIVELEVELSET:
            return ("DDERR_NOCOOPERATIVELEVELSET");
        case DDERR_NODIRECTDRAWHW:
            return ("DDERR_NODIRECTDRAWHW");
        case DDERR_NOEMULATION:
            return ("DDERR_NOEMULATION");
        case DDERR_NOEXCLUSIVEMODE:
            return ("DDERR_NOEXCLUSIVEMODE");
        case DDERR_NOFLIPHW:
            return ("DDERR_NOFLIPHW");
        case DDERR_NOMIPMAPHW:
            return ("DDERR_NOMIPMAPHW");
        case DDERR_NOOVERLAYHW:
            return ("DDERR_NOOVERLAYHW");
        case DDERR_NOZBUFFERHW:
            return ("DDERR_NOZBUFFERHW");
        case DDERR_OUTOFMEMORY:
            return ("DDERR_OUTOFMEMORY");
        case DDERR_OUTOFVIDEOMEMORY:
            return ("DDERR_OUTOFVIDEOMEMORY");
        case DDERR_PRIMARYSURFACEALREADYEXISTS:
            return ("DDERR_PRIMARYSURFACEALREADYEXISTS");
        case DDERR_UNSUPPORTEDMODE:
            return ("DDERR_UNSUPPORTEDMODE");
    }
    return ("Unknow DDERR");
}

proxy_IDirectDraw::proxy_IDirectDraw(LPDIRECTDRAW lplpDD)
{
    this->r_lplpDD = lplpDD;
}

proxy_IDirectDraw::~proxy_IDirectDraw()
{

}

/*** IUnknown methods ***/

HRESULT __stdcall proxy_IDirectDraw::QueryInterface(REFIID riid, LPVOID* obp)
{
    HRESULT hRes;
    DWORD return_addr;
    LPOLESTR lpwzGuid = NULL;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        StringFromIID(riid, &lpwzGuid);
        if (lpwzGuid) {

            dbg_msg("[+] proxy_IDirectDraw::QueryInterface(riid = %S, obp = 0x%08X) return_addr = 0x%08X\n", lpwzGuid, obp, return_addr);
            CoTaskMemFree((LPVOID)lpwzGuid);
            lpwzGuid = NULL;

        }
        else {
            dbg_msg("[+] proxy_IDirectDraw::QueryInterface(???, obp = 0x%08X) return_addr = 0x%08X\n", obp, return_addr);
        }
    }
    if (IsEqualIID(riid, IID_IDirectDraw7) == TRUE) {
        if ((hRes = r_lplpDD->QueryInterface(riid, obp)) == S_OK) {
            proxy7_lplpDD = new proxy_IDirectDraw7(*(LPDIRECTDRAW7*)obp);
            *obp = (LPDIRECTDRAW7)proxy7_lplpDD;
            return hRes;
        }
    }
    return r_lplpDD->QueryInterface(riid, obp);
}

ULONG __stdcall proxy_IDirectDraw::AddRef()
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::AddRef(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->AddRef();
}

ULONG __stdcall proxy_IDirectDraw::Release()
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::Release(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->Release();
}

/*** IDirectDraw methods ***/

HRESULT __stdcall proxy_IDirectDraw::Compact()
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::Compact(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->Compact();
}

HRESULT __stdcall proxy_IDirectDraw::CreateClipper(DWORD dwFlags, LPDIRECTDRAWCLIPPER FAR *lplpDDClipper, IUnknown FAR *pUnkOuter)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::CreateClipper(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->CreateClipper(dwFlags, lplpDDClipper, pUnkOuter);
}

HRESULT __stdcall proxy_IDirectDraw::CreatePalette(DWORD dwFlags, LPPALETTEENTRY lpColorTable, LPDIRECTDRAWPALETTE FAR* lplpDDPalette, IUnknown FAR *pUnkOuter)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::CreatePalette(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->CreatePalette(dwFlags, lpColorTable, lplpDDPalette, pUnkOuter);
}

HRESULT __stdcall proxy_IDirectDraw::CreateSurface(LPDDSURFACEDESC lpDDSurfaceDesc, LPDIRECTDRAWSURFACE FAR *lplpDDSurface, IUnknown FAR *pUnkOuter)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::CreateSurface(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->CreateSurface(lpDDSurfaceDesc, lplpDDSurface, pUnkOuter);
}

HRESULT __stdcall proxy_IDirectDraw::DuplicateSurface(LPDIRECTDRAWSURFACE lpDDSurface, LPDIRECTDRAWSURFACE FAR *lplpDupDDSurface)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::DuplicateSurface(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->DuplicateSurface(lpDDSurface, lplpDupDDSurface);
}

HRESULT __stdcall proxy_IDirectDraw::EnumDisplayModes(DWORD dwFlags, LPDDSURFACEDESC lpDDSurfaceDesc, LPVOID lpContext, LPDDENUMMODESCALLBACK lpEnumCallback)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::EnumDisplayModes(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->EnumDisplayModes(dwFlags, lpDDSurfaceDesc, lpContext, lpEnumCallback);
}

HRESULT __stdcall proxy_IDirectDraw::EnumSurfaces(DWORD dwFlags,LPDDSURFACEDESC lpDDSD, LPVOID lpContext,LPDDENUMSURFACESCALLBACK lpEnumCallback)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::EnumSurfaces(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->EnumSurfaces(dwFlags, lpDDSD, lpContext, lpEnumCallback);
}

HRESULT __stdcall proxy_IDirectDraw::FlipToGDISurface()
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::FlipToGDISurface(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->FlipToGDISurface();
}

HRESULT __stdcall proxy_IDirectDraw::GetCaps(LPDDCAPS lpDDDriverCaps,LPDDCAPS lpDDHELCaps)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::GetCaps(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->GetCaps(lpDDDriverCaps, lpDDHELCaps);
}

HRESULT __stdcall proxy_IDirectDraw::GetDisplayMode(LPDDSURFACEDESC lpDDSurfaceDesc)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::GetDisplayMode(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->GetDisplayMode(lpDDSurfaceDesc);
}

HRESULT __stdcall proxy_IDirectDraw::GetFourCCCodes(DWORD FAR *lpNumCodes, DWORD FAR *lpCodes)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::GetFourCCCodes(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->GetFourCCCodes(lpNumCodes, lpCodes);
}

HRESULT __stdcall proxy_IDirectDraw::GetGDISurface(LPDIRECTDRAWSURFACE FAR *lplpGDIDDSSurface)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::GetGDISurface(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->GetGDISurface(lplpGDIDDSSurface);
}

HRESULT __stdcall proxy_IDirectDraw::GetMonitorFrequency(LPDWORD lpdwFrequency)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::GetMonitorFrequency(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->GetMonitorFrequency(lpdwFrequency);
}

HRESULT __stdcall proxy_IDirectDraw::GetScanLine(LPDWORD lpdwScanLine)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::GetScanLine(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->GetScanLine(lpdwScanLine);
}

HRESULT __stdcall proxy_IDirectDraw::GetVerticalBlankStatus(LPBOOL lpbIsInVB)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::GetVerticalBlankStatus(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->GetVerticalBlankStatus(lpbIsInVB);
}

HRESULT __stdcall proxy_IDirectDraw::Initialize(GUID FAR *lpGUID)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::Initialize(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->Initialize(lpGUID);
}

HRESULT __stdcall proxy_IDirectDraw::RestoreDisplayMode()
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::RestoreDisplayMode(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->RestoreDisplayMode();
}

HRESULT __stdcall proxy_IDirectDraw::SetDisplayMode(DWORD dwWidth, DWORD dwHeight, DWORD dwBpp)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::SetDisplayMode(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->SetDisplayMode(dwWidth, dwHeight, dwBpp);
}

HRESULT __stdcall proxy_IDirectDraw::WaitForVerticalBlank(DWORD dwFlags, HANDLE hEvent)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::WaitForVerticalBlank(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->WaitForVerticalBlank(dwFlags, hEvent);
}

/* proxy_IDirectDraw7 */

proxy_IDirectDraw7::proxy_IDirectDraw7(LPDIRECTDRAW7 lplpDD)
{
    this->r_lplpDD = lplpDD;
    this->proxy7_PrimarySurface = NULL;
    this->lplpDDBackSurface = NULL;
    this->lplpDDEmuPrimarySurface = NULL;
    this->lplpDDEmuBackSurface = NULL;
    this->dwWidth = 0;
    this->dwHeight = 0;
}

proxy_IDirectDraw7::~proxy_IDirectDraw7()
{
    this->r_lplpDD->Release();
}

/*** IUnknown methods ***/

HRESULT __stdcall proxy_IDirectDraw7::QueryInterface(REFIID riid, LPVOID* obp)
{
    LPOLESTR lpwzGuid = NULL;
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        StringFromIID(riid, &lpwzGuid);
        if (lpwzGuid) {
            dbg_msg("[+] proxy_IDirectDraw7::QueryInterface(riid = %S, 0x%08X) return_addr = 0x%08X\n", lpwzGuid, obp, return_addr);
            CoTaskMemFree((LPVOID)lpwzGuid);
            lpwzGuid = NULL;
        }
        else {
            dbg_msg("[+] proxy_IDirectDraw7::QueryInterface(???, 0x%08X) return_addr = 0x%08X\n", obp);
        }
    }
    return r_lplpDD->QueryInterface(riid, obp);
}

ULONG __stdcall proxy_IDirectDraw7::AddRef()
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::AddRef(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->AddRef();
}

ULONG __stdcall proxy_IDirectDraw7::Release()
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::Release(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->Release();
}

/*** IDirectDraw methods ***/

HRESULT __stdcall proxy_IDirectDraw7::Compact()
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::Compact(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->Compact();
}

HRESULT __stdcall proxy_IDirectDraw7::CreateClipper(DWORD dwFlags, LPDIRECTDRAWCLIPPER FAR *lplpDDClipper, IUnknown FAR *pUnkOuter)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::CreateClipper(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->CreateClipper(dwFlags, lplpDDClipper, pUnkOuter);
}

HRESULT __stdcall proxy_IDirectDraw7::CreatePalette(DWORD dwFlags, LPPALETTEENTRY lpColorTable, LPDIRECTDRAWPALETTE FAR* lplpDDPalette, IUnknown FAR *pUnkOuter)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::CreatePalette(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->CreatePalette(dwFlags, lpColorTable, lplpDDPalette, pUnkOuter);
}

HRESULT __stdcall proxy_IDirectDraw7::DuplicateSurface(LPDIRECTDRAWSURFACE7 lpDDSurface, LPDIRECTDRAWSURFACE7 FAR *lplpDupDDSurface)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::DuplicateSurface(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->DuplicateSurface(lpDDSurface, lplpDupDDSurface);
}

HRESULT __stdcall proxy_IDirectDraw7::EnumDisplayModes(DWORD dwFlags, LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext, LPDDENUMMODESCALLBACK2 lpEnumCallback)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::EnumDisplayModes(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->EnumDisplayModes(dwFlags, lpDDSurfaceDesc, lpContext, lpEnumCallback);
}

HRESULT __stdcall proxy_IDirectDraw7::EnumSurfaces(DWORD dwFlags, LPDDSURFACEDESC2 lpDDSD, LPVOID lpContext, LPDDENUMSURFACESCALLBACK7 lpEnumCallback)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::EnumSurfaces(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->EnumSurfaces(dwFlags, lpDDSD, lpContext, lpEnumCallback);
}

HRESULT __stdcall proxy_IDirectDraw7::FlipToGDISurface()
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::FlipToGDISurface(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->FlipToGDISurface();
}

HRESULT __stdcall proxy_IDirectDraw7::GetCaps(LPDDCAPS lpDDDriverCaps,LPDDCAPS lpDDHELCaps)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::GetCaps(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->GetCaps(lpDDDriverCaps, lpDDHELCaps);
}

HRESULT __stdcall proxy_IDirectDraw7::GetDisplayMode(LPDDSURFACEDESC2 lpDDSurfaceDesc)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::GetDisplayMode(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->GetDisplayMode(lpDDSurfaceDesc);
}

HRESULT __stdcall proxy_IDirectDraw7::GetFourCCCodes(DWORD FAR *lpNumCodes, DWORD FAR *lpCodes)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::GetFourCCCodes(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->GetFourCCCodes(lpNumCodes, lpCodes);
}

HRESULT __stdcall proxy_IDirectDraw7::GetGDISurface(LPDIRECTDRAWSURFACE7 FAR *lplpGDIDDSSurface)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::GetGDISurface(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->GetGDISurface(lplpGDIDDSSurface);
}

HRESULT __stdcall proxy_IDirectDraw7::GetMonitorFrequency(LPDWORD lpdwFrequency)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::GetMonitorFrequency(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->GetMonitorFrequency(lpdwFrequency);
}

HRESULT __stdcall proxy_IDirectDraw7::GetScanLine(LPDWORD lpdwScanLine)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::GetScanLine(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->GetScanLine(lpdwScanLine);
}

HRESULT __stdcall proxy_IDirectDraw7::GetVerticalBlankStatus(LPBOOL lpbIsInVB)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::GetVerticalBlankStatus(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->GetVerticalBlankStatus(lpbIsInVB);
}

HRESULT __stdcall proxy_IDirectDraw7::Initialize(GUID FAR *lpGUID)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::Initialize(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->Initialize(lpGUID);
}

HRESULT __stdcall proxy_IDirectDraw7::RestoreDisplayMode()
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::RestoreDisplayMode(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->RestoreDisplayMode();
}

HRESULT __stdcall proxy_IDirectDraw7::SetCooperativeLevel(HWND hWnd, DWORD dwFlags)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::SetCooperativeLevel(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->SetCooperativeLevel(hWnd, dwFlags);
}

HRESULT __stdcall proxy_IDirectDraw7::WaitForVerticalBlank(DWORD dwFlags, HANDLE hEvent)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        if (!(return_addr >= pinfo.ModuleInjectedBase && return_addr <= (pinfo.ModuleInjectedBase + pinfo.ModuleInjectedSize))) {
            dbg_msg("[+] proxy_IDirectDraw7::WaitForVerticalBlank(); return_addr = 0x%08X\n", return_addr);
        }
    }
    return r_lplpDD->WaitForVerticalBlank(dwFlags, hEvent);
}

/*** Added in the v2 interface ***/
HRESULT __stdcall proxy_IDirectDraw7::GetAvailableVidMem(LPDDSCAPS2 lpDDSCaps2, LPDWORD lpdwTotal, LPDWORD lpdwFree)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::GetAvailableVidMem(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->GetAvailableVidMem(lpDDSCaps2, lpdwTotal, lpdwFree);
}

/*** Added in the V4 Interface ***/
HRESULT __stdcall proxy_IDirectDraw7::GetSurfaceFromDC(HDC hdc, LPDIRECTDRAWSURFACE7 *lpDDS)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::GetSurfaceFromDC(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->GetSurfaceFromDC(hdc, lpDDS);
}

HRESULT __stdcall proxy_IDirectDraw7::RestoreAllSurfaces()
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::RestoreAllSurfaces(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->RestoreAllSurfaces();
}

HRESULT __stdcall proxy_IDirectDraw7::TestCooperativeLevel()
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::TestCooperativeLevel(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->TestCooperativeLevel();
}

HRESULT __stdcall proxy_IDirectDraw7::GetDeviceIdentifier(LPDDDEVICEIDENTIFIER2 lpdddi, DWORD dwFlags)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::GetDeviceIdentifier(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->GetDeviceIdentifier(lpdddi, dwFlags);
}

HRESULT __stdcall proxy_IDirectDraw7::StartModeTest(LPSIZE lpModesToTest, DWORD dwNumEntries, DWORD dwFlags)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::StartModeTest(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->StartModeTest(lpModesToTest, dwNumEntries, dwFlags);
}

HRESULT __stdcall proxy_IDirectDraw7::EvaluateMode(DWORD dwFlags, DWORD *pSecondsUntilTimeout)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::EvaluateMode(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDD->EvaluateMode(dwFlags, pSecondsUntilTimeout);
}

///* proxy_IDirectDrawSurface7 */
proxy_IDirectDrawSurface7::proxy_IDirectDrawSurface7(LPDIRECTDRAWSURFACE7 lplpDDSurface, BOOL bPrimary = FALSE)
{
    this->r_lplpDDSurface = lplpDDSurface;
    this->bPrimary = bPrimary;
}

proxy_IDirectDrawSurface7::~proxy_IDirectDrawSurface7()
{
    this->r_lplpDDSurface->Release();
}

/*** IUnknown methods ***/
HRESULT __stdcall proxy_IDirectDrawSurface7::QueryInterface(REFIID riid, LPVOID* obp)
{
    DWORD return_addr;

    __asm {
        mov eax, [ebp + 4]
        mov return_addr, eax
    }
    dbg_msg("[+] proxy_IDirectDrawSurface7::QueryInterface(); return_addr = 0x%08X\n", return_addr);
    return r_lplpDDSurface->QueryInterface(riid, obp);
}

ULONG __stdcall proxy_IDirectDrawSurface7::AddRef()
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::AddRef(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->AddRef();
}

ULONG __stdcall proxy_IDirectDrawSurface7::Release()
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::Release(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->Release();
}

/*** IDirectDrawSurface methods ***/
HRESULT __stdcall proxy_IDirectDrawSurface7::AddAttachedSurface(LPDIRECTDRAWSURFACE7 lpDDSAttachedSurface)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::AddAttachedSurface(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->AddAttachedSurface(lpDDSAttachedSurface);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::AddOverlayDirtyRect(LPRECT lpRect)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::AddOverlayDirtyRect(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->AddOverlayDirtyRect(lpRect);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::BltBatch(LPDDBLTBATCH lpDDBltBatch, DWORD dwCount, DWORD dwFlags)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::BltBatch(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->BltBatch(lpDDBltBatch, dwCount, dwFlags);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::BltFast(DWORD dwX, DWORD dwY, LPDIRECTDRAWSURFACE7 lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwTrans)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::BltFast(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->BltFast(dwX, dwY, lpDDSrcSurface, lpSrcRect, dwTrans);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::DeleteAttachedSurface(DWORD dwFlags, LPDIRECTDRAWSURFACE7 lpDDSAttachedSurface)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::DeleteAttachedSurface(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->DeleteAttachedSurface(dwFlags, lpDDSAttachedSurface);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::EnumAttachedSurfaces(LPVOID lpContext, LPDDENUMSURFACESCALLBACK7 lpEnumSurfacesCallback)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::EnumAttachedSurfaces(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->EnumAttachedSurfaces(lpContext, lpEnumSurfacesCallback);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::EnumOverlayZOrders(DWORD dwFlags, LPVOID lpContext, LPDDENUMSURFACESCALLBACK7 lpfnCallback)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::EnumOverlayZOrders(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->EnumOverlayZOrders(dwFlags, lpContext, lpfnCallback);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::GetBltStatus(DWORD dwFlags)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::GetBltStatus(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->GetBltStatus(dwFlags);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::GetCaps(LPDDSCAPS2 lpDDSCaps)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::GetCaps(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->GetCaps(lpDDSCaps);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::GetClipper(LPDIRECTDRAWCLIPPER FAR *lplpDDClipper)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::GetClipper(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->GetClipper(lplpDDClipper);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::GetColorKey(DWORD dwFlags, LPDDCOLORKEY lpDDColorKey)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::GetColorKey(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->GetColorKey(dwFlags, lpDDColorKey);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::GetDC(HDC FAR *lphDC)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::GetDC(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->GetDC(lphDC);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::GetFlipStatus(DWORD dwFlags)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::GetFlipStatus(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->GetFlipStatus(dwFlags);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::GetOverlayPosition(LPLONG lplX, LPLONG lplY)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::GetOverlayPosition(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->GetOverlayPosition(lplX, lplY);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::GetPalette(LPDIRECTDRAWPALETTE FAR *lplpDDPalette)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::GetPalette(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->GetPalette(lplpDDPalette);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::Initialize(LPDIRECTDRAW lpDD, LPDDSURFACEDESC2 lpDDSurfaceDesc)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::Initialize(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->Initialize(lpDD, lpDDSurfaceDesc);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::GetSurfaceDesc(LPDDSURFACEDESC2 lpDDSurfaceDesc)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::GetSurfaceDesc(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->GetSurfaceDesc(lpDDSurfaceDesc);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::IsLost()
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::IsLost(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->IsLost();
}

HRESULT __stdcall proxy_IDirectDrawSurface7::Lock(LPRECT lpDestRect, LPDDSURFACEDESC2 lpDDSurfaceDesc, DWORD dwFlags, HANDLE hEvent)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::Lock(); return_addr = 0x%08X\n", return_addr);
    }
    return this->r_lplpDDSurface->Lock(lpDestRect, lpDDSurfaceDesc, dwFlags, hEvent);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::ReleaseDC(HDC hDC)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::ReleaseDC(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->ReleaseDC(hDC);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::Restore()
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::Restore(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->Restore();
}

HRESULT __stdcall proxy_IDirectDrawSurface7::SetClipper(LPDIRECTDRAWCLIPPER lpDDClipper)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        if (!(return_addr >= pinfo.ModuleInjectedBase && return_addr <= (pinfo.ModuleInjectedBase + pinfo.ModuleInjectedSize))) {
            dbg_msg("[+] proxy_IDirectDrawSurface7::SetClipper(); return_addr = 0x%08X\n", return_addr);
        }
    }
    return r_lplpDDSurface->SetClipper(lpDDClipper);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::SetColorKey(DWORD dwFlags, LPDDCOLORKEY lpDDColorKey)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::SetColorKey(); return_addr = 0x%08X, lppds = 0x%08X, dwFlags = 0x%08X, lpDDColorKey = 0x%08X\n", return_addr, this, dwFlags, lpDDColorKey);
        dbg_msg("[+] dwColorSpaceLowValue  = 0x%08X\n", lpDDColorKey->dwColorSpaceLowValue);
        dbg_msg("[+] dwColorSpaceHighValue = 0x%08X\n", lpDDColorKey->dwColorSpaceHighValue);
    }
    return r_lplpDDSurface->SetColorKey(dwFlags, lpDDColorKey);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::SetOverlayPosition(LONG lX, LONG lY)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::SetOverlayPosition(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->SetOverlayPosition(lX, lY);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::SetPalette(LPDIRECTDRAWPALETTE lpDDPalette)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::SetPalette(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->SetPalette(lpDDPalette);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::Unlock(LPRECT lpRect)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::Unlock(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->Unlock(lpRect);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::UpdateOverlay(LPRECT lpSrcRect, LPDIRECTDRAWSURFACE7 lpDDDestSurface, LPRECT lpDestRect, DWORD dwFlags, LPDDOVERLAYFX lpDDOverlayFx)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::UpdateOverlay(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->UpdateOverlay(lpSrcRect, lpDDDestSurface, lpDestRect, dwFlags, lpDDOverlayFx);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::UpdateOverlayDisplay(DWORD dwFlags)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::UpdateOverlayDisplay(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->UpdateOverlayDisplay(dwFlags);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::UpdateOverlayZOrder(DWORD dwFlags, LPDIRECTDRAWSURFACE7 lpDDSReference)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::UpdateOverlayZOrder(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->UpdateOverlayZOrder(dwFlags, lpDDSReference);
}

/*** Added in the v2 interface ***/
HRESULT __stdcall proxy_IDirectDrawSurface7::GetDDInterface(LPVOID FAR *lplpDD)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::GetDDInterface(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->GetDDInterface(lplpDD);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::PageLock(DWORD dwFlags)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::PageLock(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->PageLock(dwFlags);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::PageUnlock(DWORD dwFlags)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::PageUnlock(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->PageUnlock(dwFlags);
}

/*** Added in the v3 interface ***/
HRESULT __stdcall proxy_IDirectDrawSurface7::SetSurfaceDesc(LPDDSURFACEDESC2 lpddsd2, DWORD dwFlags)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::SetSurfaceDesc(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->SetSurfaceDesc(lpddsd2, dwFlags);
}

/*** Added in the v4 interface ***/
HRESULT __stdcall proxy_IDirectDrawSurface7::SetPrivateData(REFGUID guidTag, LPVOID lpData, DWORD cbSize, DWORD dwFlags)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::SetPrivateData(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->SetPrivateData(guidTag, lpData, cbSize, dwFlags);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::GetPrivateData(REFGUID guidTag, LPVOID lpBuffer, LPDWORD lpcbBufferSize)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::GetPrivateData(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->GetPrivateData(guidTag, lpBuffer, lpcbBufferSize);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::FreePrivateData(REFGUID guidTag)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::FreePrivateData(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->FreePrivateData(guidTag);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::GetUniquenessValue(LPDWORD lpValue)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::GetUniquenessValue(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->GetUniquenessValue(lpValue);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::ChangeUniquenessValue()
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::ChangeUniquenessValue(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->ChangeUniquenessValue();
}

/*** Moved Texture7 methods here ***/
HRESULT __stdcall proxy_IDirectDrawSurface7::SetPriority(DWORD dwPriority)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::SetPriority(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->SetPriority(dwPriority);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::GetPriority(LPDWORD lpdwPriority)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::GetPriority(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->GetPriority(lpdwPriority);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::SetLOD(DWORD dwMaxLOD)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::SetLOD(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->SetLOD(dwMaxLOD);
}

HRESULT __stdcall proxy_IDirectDrawSurface7::GetLOD(LPDWORD lpdwMaxLOD)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::GetLOD(); return_addr = 0x%08X\n", return_addr);
    }
    return r_lplpDDSurface->GetLOD(lpdwMaxLOD);
}

/*
    ----------------------------------------------

    RANDOM FUNCTIONS

    ----------------------------------------------
*/

VOID SetClipCursor(VOID)
{
    RECT rcClient;
    POINT ptPoint;

    ptPoint.x = ptPoint.y = 0;
    if (g_hWnd==NULL) {
        return;
    }
    if (GetClientRect(g_hWnd, &rcClient) == FALSE) {
        dbg_msg("[-] %s - GetClientRect fail : %lu\n",  __FUNCTION__, GetLastError());
        return;
    }
    if (ClientToScreen(g_hWnd, &ptPoint) == FALSE) {
        dbg_msg("[-] %s - ClientToScreen fail : %lu\n",  __FUNCTION__, GetLastError());
        return;
    }
    rcClient.left += ptPoint.x;
    rcClient.right += ptPoint.x;
    rcClient.top += ptPoint.y;
    rcClient.bottom += ptPoint.y;
    if (ClipCursor(&rcClient) == FALSE) {
        dbg_msg("[-] %s - ClipCursor fail : %lu\n",  __FUNCTION__, GetLastError());
        return;
    }
}

VOID AdjustWindow(HWND hWnd, DWORD dwWidth, DWORD dwHeight)
{
    RECT rcRect;
    RECT rcOwner;

    SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
    SetWindowLong(hWnd, GWL_EXSTYLE, 0);
    rcRect.top = 0;
    rcRect.left = 0;
    rcRect.right = dwWidth;
    rcRect.bottom = dwHeight;
    GetWindowRect(hWnd, &rcOwner);
    SetWindowPos(hWnd, 0, 0, 0, rcRect.right - rcRect.left, rcRect.bottom - rcRect.top, 0);
    ShowWindow(hWnd, SW_SHOWNORMAL);
    InvalidateRect(hWnd, NULL, TRUE);
}

VOID SetPixelFormat(LPDDSURFACEDESC2 lpDDSurfaceDesc)
{
    lpDDSurfaceDesc->dwFlags |= DDSD_PIXELFORMAT;
    lpDDSurfaceDesc->ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
    lpDDSurfaceDesc->ddpfPixelFormat.dwFlags = DDPF_RGB;
    lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount = 16;
    lpDDSurfaceDesc->ddpfPixelFormat.dwRBitMask = 0xf800;
    lpDDSurfaceDesc->ddpfPixelFormat.dwGBitMask = 0x07e0;
    lpDDSurfaceDesc->ddpfPixelFormat.dwBBitMask = 0x001f;
    lpDDSurfaceDesc->ddpfPixelFormat.dwRGBAlphaBitMask = 0x0000;
}

VOID GetRectWindow(LPRECT lpRect)
{
    POINT ptPoint;

    ptPoint.x = ptPoint.y = 0;
    GetClientRect(g_hWnd, lpRect);
    ClientToScreen(g_hWnd, &ptPoint);
    OffsetRect(lpRect, ptPoint.x, ptPoint.y);
}

/*
    Palette used to emulat bit block transfer from 16 to 32
*/
VOID InitPalette(VOID)
{
    int i;

    if (g_pdwPalette16BPP) {
        return;
    }
    g_pdwPalette16BPP = (PDWORD)malloc(0x10000 * sizeof (DWORD));
    if (g_pdwPalette16BPP == NULL) {
        dbg_msg("[-] %s - malloc fail\n", __FUNCTION__);
        ExitProcess(42);
    }
    /* RGB565 */
    for (i = 0; i < 0x10000; i++) {
        g_pdwPalette16BPP[i] = (i & 0x1F) << 3 | (i & 0x7E0) << 5 | (i & 0xF800) <<8;
    }
}

HRESULT __stdcall proxy_IDirectDraw7::BuildPrimary(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPDIRECTDRAWSURFACE7 FAR *lplpDDSurface, IUnknown FAR *pUnkOuter)
{
    HRESULT hRes;
    DDSURFACEDESC2 ddsd;
    struct proxy_IDirectDrawSurface7 *proxy7_Surface = NULL;

    (void)pUnkOuter;
    memcpy(&ddsd, lpDDSurfaceDesc, lpDDSurfaceDesc->dwSize);
    SetPixelFormat(&ddsd);
    ddsd.dwFlags &= ~(DDSD_BACKBUFFERCOUNT);
    ddsd.dwFlags |= (DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT);
    ddsd.ddsCaps.dwCaps &= ~(DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX);
    ddsd.ddsCaps.dwCaps |= (DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY);
    ddsd.dwWidth = this->GetWidth();
    ddsd.dwHeight = this->GetHeight();
    hRes = this->r_lplpDD->CreateSurface(&ddsd, lplpDDSurface, 0);
    if (hRes != DD_OK) {
        dbg_msg("[-] %s - CreateSurface failed, hRes = 0x%08X (%s)\n", __FUNCTION__, hRes, GetStrDDError(hRes));
        ExitProcess(0);
    }
    proxy7_Surface = new proxy_IDirectDrawSurface7(*(LPDIRECTDRAWSURFACE7*)lplpDDSurface, TRUE);
    if (proxy7_Surface == NULL) {
        dbg_msg("[-] %s - alloc primary surface failed\n", __FUNCTION__);
        ExitProcess(0);
    }
    this->SetPrimarySurface(proxy7_Surface);
     *lplpDDSurface = (LPDIRECTDRAWSURFACE7)proxy7_Surface;
    return DD_OK;
}

HRESULT __stdcall proxy_IDirectDraw7::BuildEmuPrimary(VOID)
{
    LPDIRECTDRAWSURFACE7 lplpDDSurfacTemp;
    DDSURFACEDESC2 ddsd;
    HRESULT hRes;

    if (this->GetEmuPrimarySurface() == NULL) {
        memset(&ddsd, 0, sizeof (DDSURFACEDESC2));
        ddsd.dwSize = sizeof (DDSURFACEDESC2);
        ddsd.dwFlags = DDSD_CAPS;
        ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
        hRes = r_lplpDD->CreateSurface(&ddsd, &lplpDDSurfacTemp, 0);
        if (hRes != DD_OK) {
            dbg_msg("[+] %s - CreateSurface - CreateSurface failed, hRes = 0x%08X (%s)\n", __FUNCTION__, hRes, GetStrDDError(hRes));
            ExitProcess(0);
        }
        this->SetEmuPrimarySurface(lplpDDSurfacTemp);
    }
    else {
        dbg_msg("[-] %s - EmuPrimarySurface != NULL // TODO!\n", __FUNCTION__);
        ExitProcess(42);
    }
    return DD_OK;
}

HRESULT __stdcall proxy_IDirectDraw7::BuildEmuBack(VOID)
{
    LPDIRECTDRAWSURFACE7 lplpDDSurfacTemp;
    DDSURFACEDESC2 ddsd;
    HRESULT hRes;

    if (this->GetEmuBackSurface() == NULL) {
        memset(&ddsd, 0, sizeof (DDSURFACEDESC2));
        ddsd.dwSize = sizeof (DDSURFACEDESC2);
        ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
        ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
        ddsd.dwWidth = this->GetWidth();
        ddsd.dwHeight = this->GetHeight();
        hRes = r_lplpDD->CreateSurface(&ddsd, &lplpDDSurfacTemp, 0);
        if (hRes != DD_OK) {
            dbg_msg("[+] %s - CreateSurface EmuBackSurface failed, hRes = 0x%08X (%s)\n", __FUNCTION__, hRes, GetStrDDError(hRes));
            ExitProcess(0);
        }
        this->SetEmuBackSurface(lplpDDSurfacTemp);
    }
    else {
        dbg_msg("[-] %s - EmuBackSurface != NULL // TODO!\n", __FUNCTION__);
        ExitProcess(42);
    }
    return DD_OK;
}

HRESULT __stdcall proxy_IDirectDraw7::BuildBack(LPDDSURFACEDESC2 lpDDSurfaceDesc)
{
    HRESULT hRes;
    DDSURFACEDESC2 ddsd;
    LPDIRECTDRAWSURFACE7 lplpDDSurfacFake;

    memcpy(&ddsd, lpDDSurfaceDesc, lpDDSurfaceDesc->dwSize);
    SetPixelFormat(&ddsd);
    ddsd.dwFlags &= ~(DDSD_BACKBUFFERCOUNT | DDSD_REFRESHRATE);
    ddsd.dwFlags |= (DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT);
    ddsd.ddsCaps.dwCaps &= ~(DDSCAPS_BACKBUFFER | DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX | DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM);
    ddsd.ddsCaps.dwCaps |= (DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN);
    ddsd.dwWidth = this->GetWidth();
    ddsd.dwHeight = this->GetHeight();
    hRes = r_lplpDD->CreateSurface(&ddsd, &lplpDDSurfacFake, 0);
    if (hRes != DD_OK) {
        dbg_msg("[+] %s - CreateSurface BackSurface failed, hRes = 0x%08X (%s)\n", __FUNCTION__, hRes, GetStrDDError(hRes));
        ExitProcess(0);
    }
    this->SetBackSurface(lplpDDSurfacFake);
    return DD_OK;
}

/*
    ----------------------------------------------

    HOOKED (with modifications) IDirectDraw

    ----------------------------------------------

*/

/*
    Desperados calls this function with dwFlags = 0x00000413
    (DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE | DDSCL_MULTITHREADED)
*/
HRESULT __stdcall proxy_IDirectDraw::SetCooperativeLevel(HWND hWnd, DWORD dwFlags)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw::SetCooperativeLevel(); return_addr = 0x%08X\n", return_addr);
    }
    g_hWnd = hWnd;
    dwFlags &= ~(DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE);
    dwFlags |= DDSCL_NORMAL;
    return r_lplpDD->SetCooperativeLevel(hWnd, dwFlags);
}


/*
    ----------------------------------------------

    HOOKED (with modifications) IDirectDraw7

    ----------------------------------------------

*/

/*
    Desperados calls this function with dwBpp = 16, dwRefresh = 0 and dwFlags = 0
    This function is only necessary when in FULLSCREEN mode
*/
HRESULT __stdcall proxy_IDirectDraw7::SetDisplayMode(DWORD dwWidth, DWORD dwHeight, DWORD dwBpp, DWORD dwRefreshRate, DWORD dwFlags)
{
    DWORD return_addr;

    (void)dwFlags;
    (void)dwBpp;
    (void)dwRefreshRate;
    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDraw7::SetDisplayMode(dwWidth = 0x%08X (%d), dwHeight = 0x%08X (%d)); return_addr = 0x%08X\n", dwWidth, dwWidth, dwHeight, dwHeight, return_addr);
    }
    this->SetWidthAndHeight(dwWidth, dwHeight);
    AdjustWindow(g_hWnd, dwWidth, dwHeight);
    if (FAILED(r_lplpDD->CreateClipper(0, &this->lpddclipper, NULL))) {
        dbg_msg("[-] CreateClipper failed\n");
        ExitProcess(42);
    }
    if (FAILED(this->lpddclipper->SetHWnd(0, g_hWnd))) {
        dbg_msg("[-] CreateClipper failed\n");
        ExitProcess(42);
    }
    return DD_OK;
}

/*
    Desperados builds its primary surface with
    lpDDSurfaceDesc->dwFlags = 0x21 (DDSD_CAPS | DDSD_BACKBUFFERCOUNT)
    and lpDDSurfaceDesc->ddsCaps.dwCaps = 0x218 (DDSCAPS_COMPLEX | DDSCAPS_FLIP | DDSCAPS_PRIMARYSURFACE).
    Other surfaces are created with lpDDSurfaceDesc->dwFlags = 0x7(DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH)
    and lpDDSurfaceDesc->ddsCaps.dwCaps = 0x840 (DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY)
*/
HRESULT __stdcall proxy_IDirectDraw7::CreateSurface(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPDIRECTDRAWSURFACE7 FAR *lplpDDSurface, IUnknown FAR *pUnkOuter)
{
    DWORD return_addr;
    HRESULT hRes = DD_OK;
    DDSURFACEDESC2 ddsd;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        if (return_addr >= pinfo.ModuleInjectedBase && return_addr <= (pinfo.ModuleInjectedBase + pinfo.ModuleInjectedSize)) {
            dbg_msg("[+] proxy_IDirectDraw7::CreateSurface() called from inside\n");
            ExitProcess(42);
        }
        if (!(return_addr >= pinfo.ModuleInjectedBase && return_addr <= (pinfo.ModuleInjectedBase + pinfo.ModuleInjectedSize))) {
            dbg_msg("[+] proxy_IDirectDraw7::CreateSurface(); return_addr = 0x%08X : lplpDD = 0x%08X ; dwFlags = 0x%08X\n", return_addr, this, lpDDSurfaceDesc->dwFlags);
        }
    }
    memcpy(&ddsd, lpDDSurfaceDesc, sizeof (DDSURFACEDESC2));
    if ((ddsd.dwFlags & DDSD_CAPS) && (ddsd.ddsCaps.dwCaps & DDSCAPS_PRIMARYSURFACE)) {
        this->BuildPrimary(lpDDSurfaceDesc, lplpDDSurface, pUnkOuter);
        this->BuildBack(lpDDSurfaceDesc);
        this->BuildEmuPrimary();
        this->BuildEmuBack();
        dbg_msg("PrimarySurface = 0x%08X, EmuPrimarySurface = 0x%08X, EmuBackSurface = 0x%08X, BackSurface = 0x%08X\n", this->GetPrimarySurface(), proxy7_lplpDD->GetEmuPrimarySurface(), this->GetEmuBackSurface(), this->GetBackSurface());
        return hRes;
    }
    if ((ddsd.dwFlags & DDSD_CAPS) && (ddsd.ddsCaps.dwCaps & DDSCAPS_BACKBUFFER)) {
        dbg_msg("[-] %s - BACKBUFFER TODO!\n", __FUNCTION__);
        ExitProcess(42);
        /* return hRes; */
    }
    SetPixelFormat(&ddsd);
    ddsd.dwSize = sizeof (DDSURFACEDESC2);
    ddsd.dwFlags |= (DDSD_CAPS);
    ddsd.ddsCaps.dwCaps |= (DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN);
    ddsd.ddsCaps.dwCaps &= ~(DDSCAPS_VIDEOMEMORY);    // wtf, Desperados puts sometime this caps ...
    hRes = r_lplpDD->CreateSurface(&ddsd, lplpDDSurface, pUnkOuter);
    if (hRes) {
        dbg_msg("[+] %s - CreateSurface GENERIC failed, hRes = 0x%08X (%s)\n", __FUNCTION__, hRes, GetStrDDError(hRes));
        ExitProcess(0);
    }
    //*lplpDDSurface = new proxy_IDirectDrawSurface7(*(LPDIRECTDRAWSURFACE7*)lplpDDSurface);
    //dbg_msg("[+] Created lplpDDSurface = 0x%08X\n", *lplpDDSurface);
    return hRes;
}

/*
    16 bpp (RGB565)
*/
HRESULT __stdcall proxy_IDirectDrawSurface7::GetPixelFormat(LPDDPIXELFORMAT lpDDPixelFormat)
{
    DWORD return_addr;
    HRESULT hRes = DD_OK;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::GetPixelFormat() return_addr = 0x%08X : lpDDS = 0x%08X %s\n", return_addr, this, this->IsPrimary() ? "[PRIM]" : "");
    }
    memset(lpDDPixelFormat, 0, sizeof(DDPIXELFORMAT));
    lpDDPixelFormat->dwSize = sizeof(DDPIXELFORMAT);
    lpDDPixelFormat->dwRGBBitCount = 16;
    lpDDPixelFormat->dwRBitMask = 0xf800;
    lpDDPixelFormat->dwGBitMask = 0x7e0;
    lpDDPixelFormat->dwBBitMask = 0x1f;
    lpDDPixelFormat->dwRGBAlphaBitMask = 0x0000;
    return hRes;
}

HRESULT __stdcall proxy_IDirectDrawSurface7::GetAttachedSurface(LPDDSCAPS2 lpDDSCaps, LPDIRECTDRAWSURFACE7 FAR *lplpDDAttachedSurface)
{
    DWORD return_addr;
    HRESULT hRes;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        if (return_addr >= pinfo.ModuleInjectedBase && return_addr <= (pinfo.ModuleInjectedBase + pinfo.ModuleInjectedSize)) {
            dbg_msg("[+] proxy_IDirectDraw7::GetAttachedSurface() called from inside\n");
            ExitProcess(42);
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::GetAttachedSurface(); return_addr = 0x%08X : lpDDS = 0x%08X ; %s ; dwCaps = 0x%08X (%s)\n", return_addr, this, this->IsPrimary() ? "[PRIM]" : "", lpDDSCaps->dwCaps, (lpDDSCaps->dwCaps & DDSCAPS_BACKBUFFER) ? "DDSCAPS_BACKBUFFER" : "");
    }
    if (lpDDSCaps->dwCaps & DDSCAPS_BACKBUFFER) {
        dbg_msg("    BACKBUFFER attached = 0x%08X\n", proxy7_lplpDD->GetBackSurface());
        *lplpDDAttachedSurface = proxy7_lplpDD->GetBackSurface();
        return DD_OK;
    }
    hRes = r_lplpDDSurface->GetAttachedSurface(lpDDSCaps, lplpDDAttachedSurface);
    return hRes;
}

HRESULT __stdcall proxy_IDirectDrawSurface7::Blt(LPRECT lpDestRect, LPDIRECTDRAWSURFACE7 lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx)
{
    DWORD return_addr = 0;
    RECT rcEmu;
    HRESULT hRes;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::Blt() return_addr = 0x%08X : lpDDS = 0x%08X %s\n", return_addr, this, this->IsPrimary() ? "[PRIM]" : "");
        dbg_msg("    lpDDSrcSurfaceDst = 0x%08X ; lpDestRect = 0x%08X ; lpDDSrcSurface = 0x%08X ; lpSrcRect = 0x%08X ; dwFlags = 0x%08X ; lpDDBltFx = 0x%08X\n", this, lpDestRect, lpDDSrcSurface, lpSrcRect, dwFlags, lpDDBltFx);
    }
    if (this->IsPrimary() == TRUE) {
        if (lpDestRect) {
            memcpy(&rcEmu, lpDestRect, sizeof (RECT));
        }
        else {
            rcEmu.left = 0;
            rcEmu.top = 0;
            rcEmu.right = proxy7_lplpDD->GetWidth();
            rcEmu.bottom = proxy7_lplpDD->GetHeight();
        }
        hRes = this->r_lplpDDSurface->Blt(&rcEmu, lpDDSrcSurface, lpSrcRect, dwFlags, lpDDBltFx);
        if (hRes) {
            dbg_msg("%s - Blt failed, hRes = 0x%08X (%s)\n", __FUNCTION__, hRes, GetStrDDError(hRes));
            ExitProcess(42);
        }
    }
    else {
        hRes = this->r_lplpDDSurface->Blt(lpDestRect, lpDDSrcSurface, lpSrcRect, dwFlags, lpDDBltFx);
        if (hRes) {
            dbg_msg("%s - Blt failed, hRes = 0x%08X (%s)\n", __FUNCTION__, hRes, GetStrDDError(hRes));
            ExitProcess(42);
        }
    }
    return hRes;
}

HRESULT __stdcall proxy_IDirectDrawSurface7::Flip(LPDIRECTDRAWSURFACE7 lpDDSurfaceTargetOverride, DWORD dwFlags)
{
    DWORD return_addr;

    if (g_bProxyDbg == TRUE) {
        __asm {
            mov eax, [ebp + 4]
            mov return_addr, eax
        }
        dbg_msg("[+] proxy_IDirectDrawSurface7::Flip() return_addr = 0x%08X : lpDDS = 0x%08X %s, src = 0x%08X, dwFlags = 0x%08X\n", return_addr, this, this->IsPrimary() ? "[PRIM]" : "", lpDDSurfaceTargetOverride, dwFlags);
    }
    if ((dwFlags & DDFLIP_WAIT))
        proxy7_lplpDD->WaitForVerticalBlank(DDWAITVB_BLOCKEND , 0);
    if (this->IsPrimary() == TRUE) {
        if (lpDDSurfaceTargetOverride) {
            dbg_msg("[+] %s - lpDDSurfaceTargetOverride != NULL ; TODO !\n", __FUNCTION__);
            ExitProcess(42);
        }
        return this->FlipBlt(NULL, proxy7_lplpDD->GetBackSurface(), NULL, DDBLT_WAIT);
    }
    return r_lplpDDSurface->Flip(lpDDSurfaceTargetOverride, dwFlags);
}

HRESULT WINAPI ConvertSurface16toSurface32(LPDIRECTDRAWSURFACE7 lpDDDstSurface, LPRECT lpDestRect, LPDIRECTDRAWSURFACE7 lpDDSrcSurface, LPRECT lpSrcRect)
{
    HRESULT hRes;
    PWORD pwSrc16 = NULL;
    PDWORD pdwDest = NULL;
    DDSURFACEDESC2 ddsdSrc;
    DDSURFACEDESC2 ddsdDst;
    LPVOID lpSurface;
    DWORD dwWidth;
    DWORD dwHeight;

    memset(&ddsdDst,0, sizeof (DDSURFACEDESC2));
    memset(&ddsdSrc,0, sizeof(DDSURFACEDESC2));
    ddsdDst.dwSize = sizeof (DDSURFACEDESC2);
    ddsdDst.dwFlags = DDSD_LPSURFACE | DDSD_PITCH;
    ddsdSrc.dwSize = sizeof(DDSURFACEDESC2);
    ddsdSrc.dwFlags = DDSD_LPSURFACE | DDSD_PITCH;
    hRes = lpDDDstSurface->Lock(lpDestRect, (LPDDSURFACEDESC2)&ddsdDst, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WRITEONLY | DDLOCK_WAIT, 0);
    if (hRes) {
        dbg_msg("[-] %s - Lock failed, hRes = 0x%08X (%s)\n", __FUNCTION__, hRes, GetStrDDError(hRes));
        ExitProcess(42);
    }
    hRes = lpDDSrcSurface->Lock(lpSrcRect, (LPDDSURFACEDESC2)&ddsdSrc, DDLOCK_SURFACEMEMORYPTR|DDLOCK_READONLY|DDLOCK_WAIT, 0);
    if (hRes) {
        dbg_msg("[-] fail to lock\n");
        ExitProcess(42);
    }
    dwWidth = lpDestRect->right - lpDestRect->left;
    dwHeight = lpDestRect->bottom - lpDestRect->top;
    lpSurface = ddsdSrc.lpSurface;
    ddsdDst.lPitch >>= 2;
    pdwDest = (PDWORD)ddsdDst.lpSurface;
    pdwDest += lpDestRect->top*ddsdDst.lPitch;
    pdwDest += lpDestRect->left;
    ddsdSrc.lPitch >>= 1;
    if (lpSurface) {
        pwSrc16 = (PWORD)lpSurface;
    }
    else {
        pwSrc16 = (PWORD)ddsdSrc.lpSurface;
    }
    pwSrc16 += lpSrcRect->top*ddsdSrc.lPitch;
    pwSrc16 += lpSrcRect->left;
    if (g_pdwPalette16BPP == NULL) {
        InitPalette();
    }
    for (DWORD dwY = 0; dwY < dwHeight; dwY++) {
        for (DWORD dwX = 0; dwX < dwWidth; dwX++) {
            *(pdwDest++) = g_pdwPalette16BPP[*(pwSrc16++)];
        }
        pdwDest += (ddsdDst.lPitch - dwWidth);
        pwSrc16 += (ddsdSrc.lPitch - dwWidth);
    }
    lpDDDstSurface->Unlock(lpDestRect);
    lpDDSrcSurface->Unlock(lpSrcRect);
    return hRes;
}

HRESULT __stdcall proxy_IDirectDrawSurface7::FlipBlt(LPRECT lpDestRect, LPDIRECTDRAWSURFACE7 lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags)
{
    HRESULT hRes;
    DDSURFACEDESC2 ddsd;
    RECT rcWinRect, rcEmu, rcRect;
    LPDIRECTDRAWSURFACE7 lplpDDSurfacTemp;

    if (g_bProxyDbg == TRUE) {
        dbg_msg("[+] proxy_IDirectDrawSurface7::FlipBlt() : lpDDS = 0x%08X %s\n", this, this->IsPrimary() ? "[PRIM]" : "");
        dbg_msg("    lpDestRect = 0x%08X, lpDDSrcSurface = 0x%08X, lpSrcRect = 0x%08X, dwFlags = 0x%08X\n", lpDestRect, lpDDSrcSurface, lpSrcRect, dwFlags);
    }
    if (dwFlags & DDFLIP_WAIT) {
        proxy7_lplpDD->WaitForVerticalBlank(DDWAITVB_BLOCKEND , 0);
    }
    GetRectWindow(&rcWinRect);
    rcEmu.left = 0;
    rcEmu.top = 0;
    rcEmu.right = proxy7_lplpDD->GetWidth();
    rcEmu.bottom = proxy7_lplpDD->GetHeight();
    if (this->r_lplpDDSurface != lpDDSrcSurface){
        hRes = this->r_lplpDDSurface->Blt(&rcEmu, proxy7_lplpDD->GetBackSurface(), NULL, DDBLT_WAIT, 0);
        if (hRes) {

        }
    }
    ConvertSurface16toSurface32(proxy7_lplpDD->GetEmuBackSurface(), &rcEmu, this->r_lplpDDSurface, &rcEmu);
    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize = sizeof (DDSURFACEDESC2);
    proxy7_lplpDD->GetEmuBackSurface()->GetSurfaceDesc((LPDDSURFACEDESC2)&ddsd);
    rcRect.left = 0;
    rcRect.top = 0;
    rcRect.bottom = rcWinRect.bottom - rcWinRect.top;
    rcRect.right = rcWinRect.right  - rcWinRect.left;
    ddsd.dwHeight = rcRect.bottom;
    ddsd.dwWidth = rcRect.right;
    ddsd.dwFlags = (DDSD_HEIGHT | DDSD_WIDTH | DDSD_CAPS);
    ddsd.ddsCaps.dwCaps = (DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY);;
    hRes = proxy7_lplpDD->GetRealOne()->CreateSurface(&ddsd, &lplpDDSurfacTemp, 0);
    if (hRes) {
        dbg_msg("[-] %s - CreateSurface failed, hRes = 0x%08X (%s)\n", __FUNCTION__, hRes, GetStrDDError(hRes));
        ExitProcess(42);
    }
    hRes = lplpDDSurfacTemp->Blt(&rcRect, proxy7_lplpDD->GetEmuBackSurface(), &rcEmu, DDBLT_WAIT, 0);
    if (hRes) {
        dbg_msg("[-] %s - Blt failed, hRes = 0x%08X (%s)\n", __FUNCTION__, hRes, GetStrDDError(hRes));
        ExitProcess(42);
    }
    hRes = proxy7_lplpDD->GetEmuPrimarySurface()->BltFast(rcWinRect.left, rcWinRect.top, lplpDDSurfacTemp, &rcRect, DDBLTFAST_WAIT);
    if (hRes) {
        dbg_msg("[-] %s - BltFast failed, hRes = 0x%08X (%s)\n", __FUNCTION__, hRes, GetStrDDError(hRes));
        ExitProcess(42);
    }
    lplpDDSurfacTemp->Release();
    return hRes;
}
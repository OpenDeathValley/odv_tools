#ifndef _DDPROXY_H_
#define _DDPROXY_H_

#include "injected.h"
#include "dbg.h"

#pragma warning(disable: 4201)  // Disable warning message for C4201 - use of nameless struct/union
#include "ddraw.h"

#include <windows.h>
#include <vector>

struct proxy_IDirectDraw:public IDirectDraw
{
    public:
        proxy_IDirectDraw(LPDIRECTDRAW lplpDD);
        virtual ~proxy_IDirectDraw();

        /*** IUnknown methods ***/
        HRESULT __stdcall QueryInterface(REFIID riid, LPVOID* obp);
        ULONG __stdcall AddRef();
        ULONG __stdcall Release();
        /*** IDirectDraw methods ***/
        HRESULT __stdcall Compact();
        HRESULT __stdcall CreateClipper(DWORD dwFlags, LPDIRECTDRAWCLIPPER FAR *lplpDDClipper, IUnknown FAR *pUnkOuter);
        HRESULT __stdcall CreatePalette(DWORD dwFlags, LPPALETTEENTRY lpColorTable, LPDIRECTDRAWPALETTE FAR* lplpDDPalette, IUnknown FAR *pUnkOuter);
        HRESULT __stdcall CreateSurface(LPDDSURFACEDESC lpDDSurfaceDesc, LPDIRECTDRAWSURFACE FAR *lplpDDSurface, IUnknown FAR *pUnkOuter);
        HRESULT __stdcall DuplicateSurface(LPDIRECTDRAWSURFACE lpDDSurface, LPDIRECTDRAWSURFACE FAR *lplpDupDDSurface);
        HRESULT __stdcall EnumDisplayModes(DWORD dwFlags, LPDDSURFACEDESC lpDDSurfaceDesc, LPVOID lpContext, LPDDENUMMODESCALLBACK lpEnumCallback);
        HRESULT __stdcall EnumSurfaces(DWORD dwFlags, LPDDSURFACEDESC lpDDSD, LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpEnumCallback);
        HRESULT __stdcall FlipToGDISurface();
        HRESULT __stdcall GetCaps(LPDDCAPS lpDDDriverCaps, LPDDCAPS lpDDHELCaps);
        HRESULT __stdcall GetDisplayMode(LPDDSURFACEDESC lpDDSurfaceDesc);
        HRESULT __stdcall GetFourCCCodes(DWORD FAR *lpNumCodes, DWORD FAR *lpCodes);
        HRESULT __stdcall GetGDISurface(LPDIRECTDRAWSURFACE FAR *lplpGDIDDSSurface);
        HRESULT __stdcall GetMonitorFrequency(LPDWORD lpdwFrequency);
        HRESULT __stdcall GetScanLine(LPDWORD lpdwScanLine);
        HRESULT __stdcall GetVerticalBlankStatus(LPBOOL lpbIsInVB);
        HRESULT __stdcall Initialize(GUID FAR *lpGUID);
        HRESULT __stdcall RestoreDisplayMode();
        HRESULT __stdcall SetCooperativeLevel(HWND hWnd, DWORD dwFlags);
        HRESULT __stdcall SetDisplayMode(DWORD dwWidth, DWORD dwHeight, DWORD dwBpp);
        HRESULT __stdcall WaitForVerticalBlank(DWORD dwFlags, HANDLE hEvent);
    private:
        LPDIRECTDRAW r_lplpDD;
};

struct proxy_IDirectDrawSurface7:public IDirectDrawSurface7
{
    public:
        proxy_IDirectDrawSurface7(LPDIRECTDRAWSURFACE7 lpDDS7, BOOL bPrimary);
        virtual ~proxy_IDirectDrawSurface7();

        /*** IUnknown methods ***/
        HRESULT __stdcall QueryInterface(REFIID riid,LPVOID* obp);
        ULONG __stdcall AddRef();
        ULONG __stdcall Release();
        /*** IDirectDrawSurface methods ***/
        HRESULT __stdcall AddAttachedSurface(LPDIRECTDRAWSURFACE7 lpDDSAttachedSurface);
        HRESULT __stdcall AddOverlayDirtyRect(LPRECT lpRect);
        HRESULT __stdcall Blt(LPRECT lpDestRect,LPDIRECTDRAWSURFACE7 lpDDSrcSurface,LPRECT lpSrcRect,DWORD dwFlags,LPDDBLTFX lpDDBltFx);
        HRESULT __stdcall BltBatch(LPDDBLTBATCH lpDDBltBatch,DWORD dwCount,DWORD dwFlags);
        HRESULT __stdcall BltFast(DWORD dwX,DWORD dwY,LPDIRECTDRAWSURFACE7 lpDDSrcSurface,LPRECT lpSrcRect,DWORD dwTrans);
        HRESULT __stdcall DeleteAttachedSurface(DWORD dwFlags,LPDIRECTDRAWSURFACE7 lpDDSAttachedSurface);
        HRESULT __stdcall EnumAttachedSurfaces(LPVOID lpContext,LPDDENUMSURFACESCALLBACK7 lpEnumSurfacesCallback);
        HRESULT __stdcall EnumOverlayZOrders(DWORD dwFlags,LPVOID lpContext,LPDDENUMSURFACESCALLBACK7 lpfnCallback);
        HRESULT __stdcall Flip(LPDIRECTDRAWSURFACE7 lpDDSurfaceTargetOverride,DWORD dwFlags);
        HRESULT __stdcall GetAttachedSurface(LPDDSCAPS2 lpDDSCaps,LPDIRECTDRAWSURFACE7 FAR *lplpDDAttachedSurface);
        HRESULT __stdcall GetBltStatus(DWORD dwFlags);
        HRESULT __stdcall GetCaps(LPDDSCAPS2 lpDDSCaps);
        HRESULT __stdcall GetClipper(LPDIRECTDRAWCLIPPER FAR *lplpDDClipper);
        HRESULT __stdcall GetColorKey(DWORD dwFlags,LPDDCOLORKEY lpDDColorKey);
        HRESULT __stdcall GetDC(HDC FAR *lphDC);
        HRESULT __stdcall GetFlipStatus(DWORD dwFlags);
        HRESULT __stdcall GetOverlayPosition(LPLONG lplX,LPLONG lplY);
        HRESULT __stdcall GetPalette(LPDIRECTDRAWPALETTE FAR *lplpDDPalette);
        HRESULT __stdcall GetPixelFormat(LPDDPIXELFORMAT lpDDPixelFormat);
        HRESULT __stdcall Initialize(LPDIRECTDRAW lpDD,LPDDSURFACEDESC2 lpDDSurfaceDesc);
        HRESULT __stdcall GetSurfaceDesc(LPDDSURFACEDESC2 lpDDSurfaceDesc);
        HRESULT __stdcall IsLost();
        HRESULT __stdcall Lock(LPRECT lpDestRect,LPDDSURFACEDESC2 lpDDSurfaceDesc,DWORD dwFlags,HANDLE hEvent);
        HRESULT __stdcall ReleaseDC(HDC hDC);
        HRESULT __stdcall Restore();
        HRESULT __stdcall SetClipper(LPDIRECTDRAWCLIPPER lpDDClipper);
        HRESULT __stdcall SetColorKey(DWORD dwFlags,LPDDCOLORKEY lpDDColorKey);
        HRESULT __stdcall SetOverlayPosition(LONG lX,LONG lY);
        HRESULT __stdcall SetPalette(LPDIRECTDRAWPALETTE lpDDPalette);
        HRESULT __stdcall Unlock(LPRECT lpRect);
        HRESULT __stdcall UpdateOverlay(LPRECT lpSrcRect,LPDIRECTDRAWSURFACE7 lpDDDestSurface,LPRECT lpDestRect,DWORD dwFlags,LPDDOVERLAYFX lpDDOverlayFx);
        HRESULT __stdcall UpdateOverlayDisplay(DWORD dwFlags);
        HRESULT __stdcall UpdateOverlayZOrder(DWORD dwFlags,LPDIRECTDRAWSURFACE7 lpDDSReference);
        /*** Added in the v2 interface ***/
        HRESULT __stdcall GetDDInterface(LPVOID FAR *lplpDD);
        HRESULT __stdcall PageLock(DWORD dwFlags);
        HRESULT __stdcall PageUnlock(DWORD dwFlags);
        /*** Added in the v3 interface ***/
        HRESULT __stdcall SetSurfaceDesc(LPDDSURFACEDESC2 lpddsd2,DWORD dwFlags);
        /*** Added in the v4 interface ***/
        HRESULT __stdcall SetPrivateData(REFGUID guidTag,LPVOID lpData,DWORD cbSize,DWORD dwFlags);
        HRESULT __stdcall GetPrivateData(REFGUID guidTag,LPVOID lpBuffer,LPDWORD lpcbBufferSize);
        HRESULT __stdcall FreePrivateData(REFGUID guidTag);
        HRESULT __stdcall GetUniquenessValue(LPDWORD lpValue);
        HRESULT __stdcall ChangeUniquenessValue();
        /*** Moved Texture7 methods here ***/
        HRESULT __stdcall SetPriority(DWORD dwPriority);
        HRESULT __stdcall GetPriority(LPDWORD lpdwPriority);
        HRESULT __stdcall SetLOD(DWORD dwMaxLOD);
        HRESULT __stdcall GetLOD(LPDWORD lpdwMaxLOD);

        void SetIsPrimary() {
            this->bPrimary = TRUE;
        }

        BOOL IsPrimary() {
            return this->bPrimary;
        }

        HRESULT __stdcall FlipBlt(LPRECT lpDestRect, LPDIRECTDRAWSURFACE7 lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags);

    private:
        LPDIRECTDRAWSURFACE7 r_lplpDDSurface;
        BOOL bPrimary;
};

struct proxy_IDirectDraw7:public IDirectDraw7
{
    public:
        proxy_IDirectDraw7(LPDIRECTDRAW7 lplpDD);
        virtual ~proxy_IDirectDraw7();

        /*** IUnknown methods ***/
        HRESULT __stdcall QueryInterface(REFIID riid, LPVOID* obp);
        ULONG __stdcall AddRef();
        ULONG __stdcall Release();
        /*** IDirectDraw methods ***/
        HRESULT __stdcall Compact();
        HRESULT __stdcall CreateClipper(DWORD dwFlags, LPDIRECTDRAWCLIPPER FAR *lplpDDClipper, IUnknown FAR *pUnkOuter);
        HRESULT __stdcall CreatePalette(DWORD dwFlags, LPPALETTEENTRY lpColorTable, LPDIRECTDRAWPALETTE FAR* lplpDDPalette, IUnknown FAR *pUnkOuter);
        HRESULT __stdcall CreateSurface(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPDIRECTDRAWSURFACE7 FAR *lplpDDSurface, IUnknown FAR *pUnkOuter);
        HRESULT __stdcall DuplicateSurface(LPDIRECTDRAWSURFACE7 lpDDSurface, LPDIRECTDRAWSURFACE7 FAR *lplpDupDDSurface);
        HRESULT __stdcall EnumDisplayModes(DWORD dwFlags, LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext, LPDDENUMMODESCALLBACK2 lpEnumCallback);
        HRESULT __stdcall EnumSurfaces(DWORD dwFlags, LPDDSURFACEDESC2 lpDDSD, LPVOID lpContext, LPDDENUMSURFACESCALLBACK7 lpEnumCallback);
        HRESULT __stdcall FlipToGDISurface();
        HRESULT __stdcall GetCaps(LPDDCAPS lpDDDriverCaps, LPDDCAPS lpDDHELCaps);
        HRESULT __stdcall GetDisplayMode(LPDDSURFACEDESC2 lpDDSurfaceDesc);
        HRESULT __stdcall GetFourCCCodes(DWORD FAR *lpNumCodes, DWORD FAR *lpCodes);
        HRESULT __stdcall GetGDISurface(LPDIRECTDRAWSURFACE7 FAR *lplpGDIDDSSurface);
        HRESULT __stdcall GetMonitorFrequency(LPDWORD lpdwFrequency);
        HRESULT __stdcall GetScanLine(LPDWORD lpdwScanLine);
        HRESULT __stdcall GetVerticalBlankStatus(LPBOOL lpbIsInVB);
        HRESULT __stdcall Initialize(GUID FAR *lpGUID);
        HRESULT __stdcall RestoreDisplayMode();
        HRESULT __stdcall SetCooperativeLevel(HWND hWnd, DWORD dwFlags);
        HRESULT __stdcall SetDisplayMode(DWORD dwWidth, DWORD dwHeight, DWORD dwBpp, DWORD dwRefreshRate, DWORD dwFlags);
        HRESULT __stdcall WaitForVerticalBlank(DWORD dwFlags, HANDLE hEvent);
        /*** Added in the v2 interface ***/
        HRESULT __stdcall GetAvailableVidMem(LPDDSCAPS2 lpDDSCaps2, LPDWORD lpdwTotal, LPDWORD lpdwFree);
        /*** Added in the V4 Interface ***/
        HRESULT __stdcall GetSurfaceFromDC(HDC hdc, LPDIRECTDRAWSURFACE7 *lpDDS);
        HRESULT __stdcall RestoreAllSurfaces();
        HRESULT __stdcall TestCooperativeLevel();
        HRESULT __stdcall GetDeviceIdentifier(LPDDDEVICEIDENTIFIER2 lpdddi, DWORD dwFlags);
        HRESULT __stdcall StartModeTest(LPSIZE lpModesToTest, DWORD dwNumEntries, DWORD dwFlags);
        HRESULT __stdcall EvaluateMode(DWORD dwFlags, DWORD *pSecondsUntilTimeout);

        HRESULT __stdcall BuildPrimary(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPDIRECTDRAWSURFACE7 FAR *lplpDDSurface, IUnknown FAR *pUnkOuter);
        HRESULT __stdcall proxy_IDirectDraw7::BuildBack(LPDDSURFACEDESC2 lpDDSurfaceDesc);
        HRESULT __stdcall proxy_IDirectDraw7::BuildEmuPrimary(VOID);
        HRESULT __stdcall proxy_IDirectDraw7::BuildEmuBack(VOID);

        VOID SetWidthAndHeight(DWORD dwWidth, DWORD dwHeight) {
            this->dwWidth = dwWidth;
            this->dwHeight = dwHeight;
        }

        DWORD GetWidth(VOID) {
            return this->dwWidth;
        }

        DWORD GetHeight(VOID) {
            return this->dwHeight;
        }

        LPDIRECTDRAW7 GetRealOne(VOID) {
            return this->r_lplpDD;
        }

        VOID SetPrimarySurface(struct proxy_IDirectDrawSurface7 *proxy7_PrimarySurface) {
            if (this->proxy7_PrimarySurface != NULL) {
                delete [] this->proxy7_PrimarySurface;
            }
            this->proxy7_PrimarySurface = proxy7_PrimarySurface;
        }

        struct proxy_IDirectDrawSurface7 *GetPrimarySurface(VOID) {
            return this->proxy7_PrimarySurface;
        }

        VOID SetEmuPrimarySurface(LPDIRECTDRAWSURFACE7 lpDDSurface) {
            if (this->lplpDDEmuPrimarySurface != NULL) {
                this->lplpDDEmuPrimarySurface->Release();
            }
            this->lplpDDEmuPrimarySurface = lpDDSurface;
        }

        LPDIRECTDRAWSURFACE7 GetEmuPrimarySurface(VOID) {
            return this->lplpDDEmuPrimarySurface;
        }

        VOID SetEmuBackSurface(LPDIRECTDRAWSURFACE7 lpDDSurface) {
            if (this->lplpDDEmuBackSurface != NULL) {
                this->lplpDDEmuBackSurface->Release();
            }
            this->lplpDDEmuBackSurface = lpDDSurface;
        }

        LPDIRECTDRAWSURFACE7 GetEmuBackSurface(VOID) {
            return this->lplpDDEmuBackSurface;
        }

        VOID SetBackSurface(LPDIRECTDRAWSURFACE7 lplpDDBackSurface) {
            if (this->lplpDDBackSurface != NULL) {
                this->lplpDDBackSurface->Release();
            }
            this->lplpDDBackSurface = lplpDDBackSurface;
        }

        LPDIRECTDRAWSURFACE7 GetBackSurface(VOID) {
            return this->lplpDDBackSurface;
        }

    private:
        struct proxy_IDirectDrawSurface7 *proxy7_PrimarySurface;
        LPDIRECTDRAWSURFACE7 lplpDDBackSurface;
        LPDIRECTDRAWSURFACE7 lplpDDEmuPrimarySurface;
        LPDIRECTDRAWSURFACE7 lplpDDEmuBackSurface;
        LPDIRECTDRAW7 r_lplpDD;
        DWORD dwWidth;
        DWORD dwHeight;
        LPDIRECTDRAWCLIPPER lpddclipper;
};

#endif // _DDPROXY_H_
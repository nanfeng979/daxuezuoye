/*==========================================================================
 *
 *  Copyright (C) 1995 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       ddutil.cpp
 *  Content:    Routines for loading bitmap and palettes from resources
 *
 ***************************************************************************/

#pragma message("linking with Microsoft's DirectDraw library ...")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "ddraw.lib")


#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */

extern IDirectDrawPalette * DDLoadPalette(IDirectDraw7 *pdd, LPTSTR szBitmap);
extern IDirectDrawSurface7 * DDLoadBitmap(IDirectDraw7 *pdd, LPTSTR szBitmap, int dx, int dy);
extern HRESULT              DDReLoadBitmap(IDirectDrawSurface7 *pdds, LPTSTR szBitmap);
extern HRESULT              DDCopyBitmap(IDirectDrawSurface7 *pdds, HBITMAP hbm, int x, int y, int dx, int dy);
extern DWORD                DDColorMatch(IDirectDrawSurface7 *pdds, COLORREF rgb);
extern HRESULT              DDSetColorKey(IDirectDrawSurface7 *pdds, COLORREF rgb);
extern LPDIRECTDRAWCLIPPER  CreateDDClipper(LPDIRECTDRAW7 lpDDraw7, LPDIRECTDRAWSURFACE7 lpDDS,int clipnumber,LPRECT clipsqe);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

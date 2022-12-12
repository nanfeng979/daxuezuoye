#undef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include "ddutil.h"
#include "stdio.h"

/*
 *  DDLoadBitmap
 *
 *  create a DirectDrawSurface from a bitmap resource.
 *
 */
extern "C" IDirectDrawSurface7 * DDLoadBitmap(IDirectDraw7 *pdd, LPTSTR szBitmap, int dx, int dy)
{
    HBITMAP             hbm;
    BITMAP              bm;
    DDSURFACEDESC2       ddsd;
    IDirectDrawSurface7 *pdds;

    //
    //  try to load the bitmap as a resource, if that fails, try it as a file
    //
    hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, dx, dy, LR_CREATEDIBSECTION);

    if (hbm == NULL)
        hbm = (HBITMAP)LoadImage(NULL, szBitmap, IMAGE_BITMAP, dx, dy, LR_LOADFROMFILE|LR_CREATEDIBSECTION);

    if (hbm == NULL)
        return NULL;

    //
    // get size of the bitmap
    //
    GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap

    //
    // create a DirectDrawSurface for this bitmap
    //
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth = bm.bmWidth;
    ddsd.dwHeight = bm.bmHeight;

    if (pdd->CreateSurface(&ddsd, &pdds, NULL) != DD_OK)
        return NULL;

    DDCopyBitmap(pdds, hbm, 0, 0, 0, 0);

    DeleteObject(hbm);

    return pdds;
}

/*
 *  DDReLoadBitmap
 *
 *  load a bitmap from a file or resource into a directdraw surface.
 *  normaly used to re-load a surface after a restore.
 *
 */
HRESULT DDReLoadBitmap(IDirectDrawSurface7 *pdds, LPTSTR szBitmap)
{
    HBITMAP             hbm;
    HRESULT             hr;

    //
    //  try to load the bitmap as a resource, if that fails, try it as a file
    // ����Դ����
    hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

    if (hbm == NULL) //���ļ�����
        hbm = (HBITMAP)LoadImage(NULL, szBitmap, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);

    if (hbm == NULL)
    {
        OutputDebugString(TEXT("handle is null\n"));
        return E_FAIL;
    }

    hr = DDCopyBitmap(pdds, hbm, 0, 0, 0, 0); //������ҳ��
    if (hr != DD_OK)
    {
        OutputDebugString(TEXT("ddcopybitmap failed\n"));
    }


    DeleteObject(hbm);
    return hr;
}

/*
 *  DDCopyBitmap
 *
 *  draw a bitmap into a DirectDrawSurface
 *
 */
extern "C" HRESULT DDCopyBitmap(IDirectDrawSurface7 *pdds, HBITMAP hbm, int x, int y, int dx, int dy)
{
    HDC                 hdcImage;
    HDC                 hdc;
    BITMAP              bm;
    DDSURFACEDESC2       ddsd;
    HRESULT             hr;

    if (hbm == NULL || pdds == NULL)
        return E_FAIL;

    //
    // make sure this surface is restored.
    //
    pdds->Restore();

    //
    //  select bitmap into a memoryDC so we can use it.
    //
    hdcImage = CreateCompatibleDC(NULL); //��Ӧ�ó�����Ļ���Ӧ���ڴ�DC
    if (!hdcImage)
        OutputDebugString(TEXT("createcompatible dc failed\n"));
    SelectObject(hdcImage, hbm);

    //
    // get size of the bitmap
    //
    GetObject(hbm, sizeof(bm), &bm);    // get size of bitmap ȡ��ͼ��ĳߴ�
    dx = dx == 0 ? bm.bmWidth  : dx;    // use the passed size, unless zero
    dy = dy == 0 ? bm.bmHeight : dy;    // ��������Ŀ�͸�Ϊ�㣬��ȡͼ��Ŀ�͸�

    //
    // get size of surface.
    //
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    pdds->GetSurfaceDesc(&ddsd);  //ȡ�ñ�������ԣ���͸�

    if ((hr = pdds->GetDC(&hdc)) == DD_OK) //���hdc��ס����
    {
        //��������
		StretchBlt(hdc, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, x, y, dx, dy, SRCCOPY);
        pdds->ReleaseDC(hdc); //�ͷű��棬����
    }

    DeleteDC(hdcImage);

    return hr;
}

//
//  DDLoadPalette
//
//  Create a DirectDraw palette object from a bitmap resoure
//
//  if the resource does not exist or NULL is passed create a
//  default 332 palette.
//
extern "C" IDirectDrawPalette * DDLoadPalette(IDirectDraw7 *pdd, LPTSTR szBitmap)
{
    IDirectDrawPalette* ddpal;
    int                 i;
    int                 n;
    HANDLE              fh;
    HRSRC               h;
    LPBITMAPINFOHEADER  lpbi;
    PALETTEENTRY        ape[256];
    RGBQUAD *           prgb;

    //
    // build a 332 palette as the default.
    //
    for (i=0; i<256; i++)
    {
        ape[i].peRed   = (BYTE)(((i >> 5) & 0x07) * 255 / 7);
        ape[i].peGreen = (BYTE)(((i >> 2) & 0x07) * 255 / 7);
        ape[i].peBlue  = (BYTE)(((i >> 0) & 0x03) * 255 / 3);
        ape[i].peFlags = (BYTE)0;
    }

    //
    // get a pointer to the bitmap resource.
    //
    if (szBitmap && (h = FindResource(NULL, szBitmap, RT_BITMAP)))
    {
        lpbi = (LPBITMAPINFOHEADER)LockResource(LoadResource(NULL, h));
        if (!lpbi)
            OutputDebugString(TEXT("lock resource failed\n"));
        prgb = (RGBQUAD*)((BYTE*)lpbi + lpbi->biSize);

        if (lpbi == NULL || lpbi->biSize < sizeof(BITMAPINFOHEADER))
            n = 0;
        else if (lpbi->biBitCount > 8)
            n = 0;
        else if (lpbi->biClrUsed == 0)
            n = 1 << lpbi->biBitCount;
        else
            n = lpbi->biClrUsed;

        //
        //  a DIB color table has its colors stored BGR not RGB
        //  so flip them around.
        //
        for(i=0; i<n; i++ )
        {
            ape[i].peRed   = prgb[i].rgbRed;
            ape[i].peGreen = prgb[i].rgbGreen;
            ape[i].peBlue  = prgb[i].rgbBlue;
            ape[i].peFlags = 0;
        }
    }
	else if (
				szBitmap && 
				(fh = CreateFile(szBitmap,GENERIC_READ,FILE_SHARE_READ,  NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE
			)
    {
        BITMAPFILEHEADER bf;
        BITMAPINFOHEADER bi;

        ReadFile(fh, &bf, sizeof(bf),NULL,0);
        ReadFile(fh, &bi, sizeof(bi),NULL,0);
        ReadFile(fh, ape, sizeof(ape),NULL,0);
        CloseHandle(fh);

        if (bi.biSize != sizeof(BITMAPINFOHEADER))
            n = 0;
        else if (bi.biBitCount > 8)
            n = 0;
        else if (bi.biClrUsed == 0)
            n = 1 << bi.biBitCount;
        else
            n = bi.biClrUsed;

        //
        //  a DIB color table has its colors stored BGR not RGB
        //  so flip them around.
        //
        for(i=0; i<n; i++ )
        {
            BYTE r = ape[i].peRed;
            ape[i].peRed  = ape[i].peBlue;
            ape[i].peBlue = r;
        }
    }

    pdd->CreatePalette(DDPCAPS_8BIT, ape, &ddpal, NULL);

    return ddpal;
}

/*
 * DDColorMatch
 *
 * convert a RGB color to a pysical color.
 *
 * we do this by leting GDI SetPixel() do the color matching
 * then we lock the memory and see what it got mapped to.
 */
//���ָ����ɫ����Ӧ�ĵ�ɫ������
extern "C" DWORD DDColorMatch(IDirectDrawSurface7 *pdds, COLORREF rgb)
{
    COLORREF rgbT;
    HDC hdc;
    DWORD dw = CLR_INVALID;
    DDSURFACEDESC2 ddsd;
    HRESULT hres;

    //
    //  use GDI SetPixel to color match for us
    //
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
        rgbT = GetPixel(hdc, 0, 0);             // save current pixel value
        SetPixel(hdc, 0, 0, rgb);               // set our value
        pdds->ReleaseDC(hdc);
    }

    //
    // now lock the surface so we can read back the converted color
    //
    ddsd.dwSize = sizeof(ddsd);
    while ((hres = pdds->Lock(NULL, &ddsd, 0, NULL)) == DDERR_WASSTILLDRAWING)
        ;

    if (hres == DD_OK)
    {
        dw  = *(DWORD *)ddsd.lpSurface;                     // get DWORD
//        dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount)-1;  // mask it to bpp
        pdds->Unlock(NULL);
    }

    //
    //  now put the color that was there back.
    //
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
        SetPixel(hdc, 0, 0, rgbT);
        pdds->ReleaseDC(hdc);
    }

    return dw;
}

/*
 * DDSetColorKey
 *
 * set a color key for a surface, given a RGB.
 * if you pass CLR_INVALID as the color key, the pixel
 * in the upper-left corner will be used.
 */
extern "C" HRESULT DDSetColorKey(IDirectDrawSurface7 *pdds, COLORREF rgb)
{
    DDCOLORKEY          ddck;

    ddck.dwColorSpaceLowValue  = DDColorMatch(pdds, rgb);
    ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
    return pdds->SetColorKey(DDCKEY_SRCBLT, &ddck);
}

LPDIRECTDRAWCLIPPER CreateDDClipper(LPDIRECTDRAW7 lpDDraw7, LPDIRECTDRAWSURFACE7 lpDDS,int clipnumber,LPRECT clipsqe)
{
	LPDIRECTDRAWCLIPPER lpDDtempclip;
	LPRGNDATA clipregion;

	if(FAILED(lpDDraw7->CreateClipper(0,&lpDDtempclip,NULL)))
	{
		OutputDebugString(TEXT("DirectDraw Create clipper error!"));
		return(NULL);
	}

	clipregion = (LPRGNDATA)malloc(sizeof(RGNDATAHEADER)+clipnumber * sizeof(RECT));
	memcpy(clipregion->Buffer,clipsqe,sizeof(RECT) * clipnumber);

	clipregion->rdh.dwSize = sizeof(RGNDATAHEADER);
	clipregion->rdh.iType = RDH_RECTANGLES;
	clipregion->rdh.nCount = clipnumber;
	clipregion->rdh.nRgnSize = clipnumber * sizeof(RECT);
	clipregion->rdh.rcBound.left = 80000;
	clipregion->rdh.rcBound.top = 80000;
	clipregion->rdh.rcBound.right = -80000;
	clipregion->rdh.rcBound.bottom = -80000;

	for (int i =0;i<clipnumber;i++)
	{
		if (clipsqe[i].left<clipregion->rdh.rcBound.left)
		{
			clipregion->rdh.rcBound.left = clipsqe[i].left;
		}

		if (clipsqe[i].top<clipregion->rdh.rcBound.top)
		{
			clipregion->rdh.rcBound.top = clipsqe[i].top;
		}

		if (clipsqe[i].right>clipregion->rdh.rcBound.right)
		{
			clipregion->rdh.rcBound.right = clipsqe[i].right;
		}

		if (clipsqe[i].bottom>clipregion->rdh.rcBound.bottom)
		{
			clipregion->rdh.rcBound.bottom = clipsqe[i].bottom;
		}
	}

	if(FAILED(lpDDtempclip->SetClipList(clipregion,0)))
	{
		free(clipregion);
		return(NULL);
	}
	if(FAILED(lpDDS->SetClipper(lpDDtempclip)))
	{
		free(clipregion);
		return(NULL);
	}
	free(clipregion);

	return(lpDDtempclip);
}

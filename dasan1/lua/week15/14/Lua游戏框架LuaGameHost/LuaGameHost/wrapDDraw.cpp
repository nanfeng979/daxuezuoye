/*==========================================================================
*
*  Copyright (C) 2008 South China Institute Of Software Engineering,GZU. All Rights Reserved.
*
*  File:       wrapDDraw.cpp
*  Content:    DirectDraw Wrapper
*  Author:	   YuanGuanYuan
*  Create:	   2008-11-08
***************************************************************************/


#include "stdafx.h"
#include "wrapddraw.h"
#include "ddutil.h"

LPDIRECTDRAW7            lpDD			=	NULL;			//DirectDraw����
LPDIRECTDRAWCLIPPER		 lpClipper		=	NULL;		//DirectDrawClipper����
LPDIRECTDRAWCLIPPER		 lpBackClipper	=	NULL;	//�������ü���
LPDIRECTDRAWSURFACE7     lpDDSFront		=	NULL;	//���¾�ΪDirectDrawSurface����
LPDIRECTDRAWSURFACE7     lpDDSBack		=	NULL;   

extern bool g_bWindowed;
extern HWND g_hMainWindow;

DDraw_Image dd_Image[MAX_IMAGES];

int Game_LoadImages();
void RestoreSufaces();


int DDraw_Init(void)
{
	//����DirectDraw����
	HRESULT hr;
	hr = DirectDrawCreateEx(NULL, (LPVOID*)&lpDD,IID_IDirectDraw7, NULL);

	if (FAILED(hr))
		return 0;


	for (int i=0;i<MAX_IMAGES;i++)
	{
		if(dd_Image[i].Surface)
		{
			dd_Image[i].Surface->Release();
			dd_Image[i].Surface=NULL;
			dd_Image[i].HasColorKey = false;
		}
	}

	return 1;
}

int DDraw_Shutdown(void)
{
	if (lpDD !=NULL)
	{
		lpDD->Release();
		lpDD = NULL;
	}
	return 1;
}



int DDraw_InitSurfaces(int nWindowWidth, int nWindowHeight,int nBPP)
{
	DDSURFACEDESC2 ddsd;
	DDSCAPS2 ddscaps;
	HRESULT hr;
	RECT backrect = {0,0,nWindowWidth,nWindowHeight};


	if (g_bWindowed)
	{
		//����Э������Ϊ����ģʽ
		hr = lpDD->SetCooperativeLevel(g_hMainWindow, DDSCL_NORMAL);
		if (FAILED(hr))
			return 0;

		//������ҳ��
		ZeroMemory(&ddsd, sizeof(ddsd));
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags = DDSD_CAPS;  //ָ����Щ����������
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;  //��ҳ��
		hr = lpDD->CreateSurface(&ddsd, &lpDDSFront, NULL); //������ҳ�� 
		if (FAILED(hr))
			return 0;

		//����Clipper�ü���
		hr = lpDD->CreateClipper(0, &lpClipper, NULL);
		if (FAILED(hr))
			return 0;
		hr = lpClipper->SetHWnd(0, g_hMainWindow);
		if (FAILED(hr))
			return 0;
		lpDDSFront->SetClipper(lpClipper);
		if (FAILED(hr))
			return 0;


		//��������ҳ�棬���ں�̨����ͼ���ţ�����ָ����Ⱥ͸߶�
		ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;    
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
		ddsd.dwWidth = nWindowWidth;         
		ddsd.dwHeight = nWindowHeight;      
		hr = lpDD->CreateSurface( &ddsd, &lpDDSBack, NULL );
		if (FAILED(hr))
			return 0;

		//����Clipper�ü���
		lpBackClipper =	CreateDDClipper(lpDD,lpDDSBack,1,&backrect);			
		if(lpBackClipper == NULL)
		{
			return 0;
		}
	}
	else
	{
		// Get exclusive mode
		hr = lpDD->SetCooperativeLevel(g_hMainWindow, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
		if (FAILED(hr))
			return 0;

		hr = lpDD->SetDisplayMode( nWindowWidth, nWindowHeight, nBPP, 0, 0);
		if (FAILED(hr))
			return 0;

		// Create the primary surface with 1 back buffer
		ZeroMemory(&ddsd,sizeof(ddsd));
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
		ddsd.dwBackBufferCount = 1;
		hr = lpDD->CreateSurface( &ddsd, &lpDDSFront, NULL);
		if (FAILED(hr))
			return 0;

		ZeroMemory(&ddscaps, sizeof(ddscaps));
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
		hr = lpDDSFront->GetAttachedSurface(&ddscaps, &lpDDSBack);
		if (FAILED(hr))
			return 0;

		//����Clipper�ü���
		lpBackClipper =	CreateDDClipper(lpDD,lpDDSBack,1,&backrect);			
		if(lpBackClipper == NULL)
		{
			return 0;
		}

	}

	return DD_OK;
}

int DDraw_FreeSurfaces( void )
{
	if( lpDD != NULL )
	{
		if( lpDDSBack!= NULL )
		{
			lpDDSBack->Release(); lpDDSBack= NULL;
		}
		if( lpDDSFront != NULL )
		{
			lpDDSFront->Release(); lpDDSFront = NULL;
		}
	}

	return DD_OK;
}




int DDraw_LoadImage(TCHAR * filename)
{
	int image_id = -1;

	for (int i = 0; i<MAX_IMAGES; i++)
	{
		if(!dd_Image[i].Surface)
		{
			image_id = i;
			break;
		}
	}

	if (image_id == -1)
	{
		return -1;
	}

	dd_Image[image_id].Surface = DDLoadBitmap(lpDD,filename,0,0);
	DDSURFACEDESC2 desc;
	desc.dwSize = sizeof(DDSURFACEDESC2);
	dd_Image[image_id].Surface->GetSurfaceDesc(&desc);
	dd_Image[image_id].Width = desc.dwWidth;
	dd_Image[image_id].Height = desc.dwHeight;
	dd_Image[image_id].HasColorKey = false;
	
	return image_id;
}

int DDraw_SetColorKey(int id,COLORREF colorKey)
{
	if (!dd_Image[id].Surface)
	{
		return 0;
	}

	DDSetColorKey(dd_Image[id].Surface,colorKey);
	dd_Image[id].HasColorKey = true;
	
	return 1;
}


int DDraw_PaintImage(int id,POINT targetPoint)
{
	DWORD flag;

	if (!dd_Image[id].Surface)
	{
		return 0;
	}

	RECT targetRect = {targetPoint.x,targetPoint.y, targetPoint.x + dd_Image[id].Width, targetPoint.y + dd_Image[id].Height };

	flag = dd_Image[id].HasColorKey?DDBLT_WAIT|DDBLT_KEYSRC:DDBLT_WAIT;

	HRESULT rval=lpDDSBack->Blt( &targetRect, dd_Image[id].Surface, NULL, flag  , NULL);
	if(rval == DDERR_SURFACELOST)    
		lpDDSBack->Restore();

	return 1;
}

int DDraw_StretchPaintImage(int id,RECT targetRect,RECT sourceRect)
{
	DWORD flag;

	if (!dd_Image[id].Surface)
	{
		return 0;
	}
	
	flag = dd_Image[id].HasColorKey?DDBLT_WAIT|DDBLT_KEYSRC:DDBLT_WAIT;
	HRESULT rval=lpDDSBack->Blt(IsRectEmpty(&targetRect)?NULL:&targetRect, dd_Image[id].Surface, IsRectEmpty(&sourceRect)?NULL:&sourceRect, flag  , NULL);
	if(rval == DDERR_SURFACELOST)    
		lpDDSBack->Restore();

	return 1;
}


int DDraw_FillRectangle(COLORREF color, RECT r)
{
	DDBLTFX bltfx;
	bltfx.dwSize=sizeof(DDBLTFX);
	bltfx.dwFillColor=DDColorMatch(lpDDSBack,color);
	lpDDSBack->Blt(&r,NULL,NULL,DDBLT_COLORFILL | DDBLT_WAIT,&bltfx);

	return 1;
}


int DDraw_TextOut(TCHAR * str,int x, int y,COLORREF color)
{
	HDC hdc;
	if (SUCCEEDED(lpDDSBack->GetDC(&hdc)))
	{
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, color); 
		TextOut(hdc, x, y, str, _tcslen(str));

		lpDDSBack->ReleaseDC(hdc);
	}

	return 1;
}
int DDraw_Show()
{
	if (g_bWindowed)
	{
		RECT ClientRect;
		POINT pt;
		GetClientRect(g_hMainWindow, &ClientRect);
		pt.x=pt.y=0;
		ClientToScreen(g_hMainWindow, &pt);
		OffsetRect(&ClientRect, pt.x, pt.y);
		//���� lpDDSBack ��������ݵ���ҳ��
		HRESULT rval=lpDDSFront->Blt(&ClientRect, lpDDSBack, NULL, DDBLT_WAIT, NULL); //��ʹ��ColorKey
		if(rval == DDERR_SURFACELOST) 
			RestoreSufaces();

	}
	else
	{
		HRESULT rval=lpDDSFront->Flip(NULL,DDFLIP_WAIT);
		if(rval == DDERR_SURFACELOST) 
			RestoreSufaces();
	}

	return 1;
}

void RestoreSufaces()
{
	lpDDSFront->Restore();
	lpDDSBack->Restore();
	Game_LoadImages();
}

int DDraw_DeleteImage(int id)
{
	if (dd_Image[id].Surface)
	{
		dd_Image[id].Surface->Release();
		dd_Image[id].Surface = NULL;
		dd_Image[id].HasColorKey = false;
	}
	return 1;
}
int DDraw_DeleteAllImage(void)
{
	for (int i=0;i<MAX_IMAGES;i++)
	{
		if (dd_Image[i].Surface)
		{
			dd_Image[i].Surface->Release();
			dd_Image[i].Surface = NULL;
			dd_Image[i].HasColorKey = false;
		}
	}
	return 1;
}
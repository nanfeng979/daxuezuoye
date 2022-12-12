/*==========================================================================
*
*  Copyright (C) 2008 South China Institute Of Software Engineering,GZU. All Rights Reserved.
*
*  File:       wrapDDraw.h
*  Content:    DirectDraw Wrapper
*  Author:	   YuanGuanYuan
*  Create:	   2008-11-08
***************************************************************************/

#include <ddraw.h>
#include <Windows.h>

#define MAX_IMAGES		256

typedef struct tag_DDraw_Image
{
	LPDIRECTDRAWSURFACE7 Surface;
	int Width;
	int Height;
	COLORREF ColorKey;
	bool HasColorKey;
}
DDraw_Image, * DDraw_Image_Ptr;


int DDraw_Init(void);
int DDraw_Shutdown(void);
int DDraw_InitSurfaces(int nWindowWidth, int nWindowHeight,int nBPP);
int DDraw_FreeSurfaces( void );
int DDraw_LoadImage(TCHAR * filename);
int DDraw_SetColorKey(int id,COLORREF colorKey);
int DDraw_PaintImage(int id,POINT targetPoint);
int DDraw_StretchPaintImage(int id,RECT targetRect,RECT sourceRect);
int DDraw_FillRectangle(COLORREF color,RECT r);
int DDraw_TextOut(TCHAR * str,int x, int y,COLORREF color);
int DDraw_Show();
int DDraw_DeleteImage(int id);
int DDraw_DeleteAllImage(void);
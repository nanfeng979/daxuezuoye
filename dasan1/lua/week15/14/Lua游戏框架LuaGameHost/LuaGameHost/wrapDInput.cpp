/*==========================================================================
*
*  Copyright (C) 2008 South China Institute Of Software Engineering,GZU. All Rights Reserved.
*
*  File:       wrapDInput.cpp
*  Content:    DirectInput Wrapper
*  Author:	   YuanGuanYuan
*  Create:	   2008-11-08
***************************************************************************/


#include "stdafx.h"
#include "wrapdinput.h"
#include <stdio.h>

extern HWND g_hMainWindow;
extern HINSTANCE g_hInstance;

LPDIRECTINPUT7 m_DirectInput;			//DirectInput 对象
LPDIRECTINPUTDEVICE lpDInputKey;		//DirectInput 键盘设备
LPDIRECTINPUTDEVICE lpDInputMouse;		//DirectInput 鼠标设备

BYTE g_KbrdState [ 256 ];
BYTE g_LastKbrdState [ 256 ];
unsigned int g_KbrdDelay [ 256 ];
bool g_KbrdFrameState [ 256 ];
int g_iKeyDelayActive           = TRUE;

DIMOUSESTATE g_mouseState;
DIMOUSESTATE g_LastMouseState;
unsigned int g_mouseButtonDelay[4];
bool g_mouseButtonFrameState[4];

int DInput_SetAcquire(bool active)
{
	// Nothing to do if lpDInputkey is NULL
	if( NULL == lpDInputKey )
		return S_FALSE;

	if( active ) 
	{
		// Acquire the input device 
		lpDInputKey->Acquire();
		lpDInputMouse->Acquire();
	} 
	else 
	{
		// Unacquire the input device 
		lpDInputKey->Unacquire();
		lpDInputMouse->Unacquire();
	}

	return S_OK;
}

int DInput_Init()				//初始化 DirectInput 
{
	HRESULT hr;
	hr = DirectInput8Create( g_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_DirectInput, NULL );
	if (FAILED(hr))
		return 0;
	
	hr = m_DirectInput->CreateDevice(GUID_SysKeyboard, &lpDInputKey, NULL);
	if (FAILED(hr))
		return 0;
	hr = lpDInputKey->SetCooperativeLevel(g_hMainWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr))
		return 0;
	hr = lpDInputKey->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
		return 0;


	hr = m_DirectInput->CreateDevice(GUID_SysMouse,&lpDInputMouse,NULL);
	if (FAILED(hr))
		return 0;
	hr = lpDInputMouse->SetCooperativeLevel(g_hMainWindow,DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);//DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	if (FAILED(hr))
		return 0;
	hr = lpDInputMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr))
		return 0;


	hr = lpDInputKey->Acquire();
	if (FAILED(hr))
		return 0;

	hr = lpDInputMouse->Acquire();
	if (FAILED(hr))
		return 0;


	return S_OK;
}

int DInput_Shutdown()
{
	if (m_DirectInput!=NULL)
	{
		if (lpDInputMouse!=NULL)
		{
			lpDInputMouse->Release();
			lpDInputMouse = NULL;
		}
		if (lpDInputKey!=NULL)
		{
			lpDInputKey->Release();
			lpDInputKey = NULL;
		}
		m_DirectInput->Release();
		m_DirectInput = NULL;
	}
	return S_OK;
}




void DInput_GetKeyboardState ()
{
	CopyMemory(g_LastKbrdState,g_KbrdState,256);

	HRESULT hr;
	hr = lpDInputKey->GetDeviceState ( 256, ( LPVOID ) g_KbrdState );
	if(FAILED(hr))
	{
		lpDInputKey->Acquire();
	}

	unsigned int iCurrTickCount = GetTickCount ();

	for ( int iCurrKeyIndex = 0; iCurrKeyIndex < 256; ++ iCurrKeyIndex )
	{
		g_KbrdFrameState [ iCurrKeyIndex ] = FALSE;
		if ( g_KbrdState [ iCurrKeyIndex ] )
		{
			if ( g_KbrdDelay [ iCurrKeyIndex ] == 0 || ! g_iKeyDelayActive )
			{
				g_KbrdFrameState [ iCurrKeyIndex ] = TRUE;
				g_KbrdDelay [ iCurrKeyIndex ] = iCurrTickCount + KEY_DELAY;
			}
			else
				if ( iCurrTickCount >= g_KbrdDelay [ iCurrKeyIndex ] )
					g_KbrdDelay [ iCurrKeyIndex ] = 0;
		}
	}

//#if _DEBUG
//	TCHAR buf[1024];
//	TCHAR keybuf[256];
//	static int t = 0;
//	buf[0]=0;
//	for (int i=0; i<256;i++)
//	{
//		if(g_LastKbrdState[i] != g_KbrdState[i] )
//		{
//			if (g_KbrdState[i])
//			{
//				_stprintf(keybuf,TEXT("Hit Key:%d"),i);
//			}
//			else
//			{
//				_stprintf(keybuf,TEXT("Release Key:%d"),i);
//			}
//			strcat(buf,keybuf);
//		}
//	}
//	int len = strlen(buf);
//	if(len!=0)
//	{
//		_stprintf(keybuf,TEXT("中间查询次数:%d"),t);
//		strcat(buf,keybuf);
//
//		strcat(buf,TEXT("\n"));
//
//		OutputDebugString(buf);
//		t = 0;
//
//		action = true;
//	}
//	else
//	{
//		action = false;
//	}
//	t++;
//	//OutputDebugString(TEXT("DInput_GetKeyboardState\r\n"));
//endif
}

void DInput_GetMouseState()
{
	CopyMemory(g_LastMouseState.rgbButtons,g_mouseState.rgbButtons,4);

	HRESULT hr;

	hr = lpDInputMouse->GetDeviceState(sizeof(DIMOUSESTATE),(LPVOID)&g_mouseState);
	if(FAILED(hr))
	{
		lpDInputMouse->Acquire();
	}

	unsigned int iCurrTickCount = GetTickCount ();
	for (int i = 0;i<4;i++)
	{
		g_mouseButtonFrameState[i] =FALSE;
		if (g_mouseState.rgbButtons[i])
		{
			if (g_mouseButtonDelay[i] == 0 || !g_iKeyDelayActive)
			{
				g_mouseButtonFrameState[i] = TRUE;
				g_mouseButtonDelay[i] = iCurrTickCount + KEY_DELAY;
			}
			else
			{
				if (iCurrTickCount>=g_mouseButtonDelay[i])
				{
					g_mouseButtonDelay[i] = 0;
				}
			}
		}
	}
}

/**************************************************************************************
*
*	DInput_GetKeyState ()
*
*	Returns the state of a given key.
*/

int DInput_GetKeyState ( int iScanCode )
{
//#if _DEBUG
//	TCHAR buf[250];
//	_stprintf(buf, TEXT("DInput_GetKeyState,Key:%d\r\n"),iScanCode);
//	OutputDebugString(buf);
//#endif

	if ( g_KbrdState [ iScanCode ] && g_KbrdFrameState [ iScanCode ] )
		return TRUE;

	return FALSE;
}

/**************************************************************************************
*
*	DInput_GetAnyKeyState ()
*
*	Returns whether or not any key has been pressed.
*/

int DInput_GetAnyKeyState ()
{
	for ( int iCurrKeyIndex = 0; iCurrKeyIndex < 256; ++ iCurrKeyIndex )
		if ( g_KbrdState [ iCurrKeyIndex ] && g_KbrdFrameState [ iCurrKeyIndex ] )
			return TRUE;

	return FALSE;
}

/**************************************************************************************
*
*   DInput_EnableKeyDelay ()
*
*   Enables the key delay.
*/

void DInput_EnableKeyDelay ()
{
	g_iKeyDelayActive = TRUE;
}

/**************************************************************************************
*
*   DInput_DisableKeyDelay ()
*
*   Disables the key delay.
*/

void DInput_DisableKeyDelay ()
{
	g_iKeyDelayActive = FALSE;
}






int DInput_GetKeyAction(int iScanCode, bool hitDown)
{
//#if _DEBUG
//	TCHAR buf[250];
//	_stprintf(buf, TEXT("DInput_GetKeyboardState,Key:%d,Action:%d\r\n"),iScanCode,hitDown);
//	OutputDebugString(buf);
//#endif

	if (g_LastKbrdState[iScanCode] == g_KbrdState[iScanCode] )
	{
		return 0;
	}

	int ret = hitDown?g_KbrdState [ iScanCode ]:g_LastKbrdState[ iScanCode ];
	return ret;
}

int DInput_GetMouseButtonState ( int iButtonID )
{
	if ( g_mouseState.rgbButtons [ iButtonID ] && g_mouseButtonFrameState [ iButtonID ] )
		return TRUE;

	return FALSE;
}

int DInput_GetMouseButtonAction(int iButtonID, bool hitDown)
{
	
	if (g_LastMouseState.rgbButtons[iButtonID] == g_mouseState.rgbButtons[iButtonID] )
	{
		return 0;
	}

	int ret = hitDown?g_mouseState.rgbButtons [ iButtonID ]:g_LastMouseState.rgbButtons[ iButtonID ];
	return ret;
}


LONG DInput_GetMouseXOffset()
{
	return g_mouseState.lX;
}

LONG DInput_GetMouseYOffset()
{
	return g_mouseState.lY;
}

LONG DInput_GetMouseZOffset()
{
	return g_mouseState.lZ;
}
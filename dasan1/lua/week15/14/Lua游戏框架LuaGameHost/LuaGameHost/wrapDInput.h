/*==========================================================================
*
*  Copyright (C) 2008 South China Institute Of Software Engineering,GZU. All Rights Reserved.
*
*  File:       wrapDInput.h
*  Content:    DirectInput Wrapper
*  Author:	   YuanGuanYuan
*  Create:	   2008-11-08
***************************************************************************/

#include <dinput.h>
#define KEY_DELAY					135

int DInput_Init();
int DInput_Shutdown();
int DInput_SetAcquire(bool active);
void DInput_GetKeyboardState ();
void DInput_GetMouseState();


int DInput_GetKeyState ( int iScanCode );
int DInput_GetKeyAction( int iScanCode, bool hitDown);
int DInput_GetAnyKeyState ();
void DInput_EnableKeyDelay ();
void DInput_DisableKeyDelay ();
int DInput_GetMouseButtonState ( int iButtonID );
int DInput_GetMouseButtonAction(int iButtonID, bool hitDown);
LONG DInput_GetMouseXOffset();
LONG DInput_GetMouseYOffset();
LONG DInput_GetMouseZOffset();
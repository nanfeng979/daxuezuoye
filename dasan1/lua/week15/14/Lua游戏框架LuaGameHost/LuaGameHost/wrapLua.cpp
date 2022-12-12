/*==========================================================================
*
*  Copyright (C) 2008 South China Institute Of Software Engineering,GZU. All Rights Reserved.
*
*  File:       wrapLua.cpp
*  Content:    Lua Wrapper,HostAPI
*  Author:	   YuanGuanYuan
*  Create:	   2008-11-08
***************************************************************************/


#include "stdafx.h"
#include "wrapLua.h"
#include <dinput.h>

#include "wrapDDraw.h"
#include "wrapDInput.h"
#include "wrapDMusic.h"
#include "wrapDSound.h"
#include "wrapTimer.h"

lua_State * g_pLuaState;							// Lua State


void Lua_Init ()
{
	// Open a new Lua state

	g_pLuaState = lua_open ( LUA_STACK_SIZE );
	luaL_openlibs(g_pLuaState);

	// Register our host API with Lua

	lua_register ( g_pLuaState, "RGB", HAPI_RGB );
	lua_register ( g_pLuaState, "GetRandomNumber", HAPI_GetRandomNumber );
	lua_register ( g_pLuaState, "GetTickCount", HAPI_GetTickCount );
	lua_register ( g_pLuaState, "ToggleScreenMode", HAPI_ToggleScreenMode );
	lua_register ( g_pLuaState, "IntersectRect", HAPI_IntersectRect );

	lua_register ( g_pLuaState, "LoadImage", HAPI_LoadImage );
	lua_register ( g_pLuaState, "SetColorKey", HAPI_SetColorKey );
	lua_register ( g_pLuaState, "PaintImage", HAPI_PaintImage );
	lua_register ( g_pLuaState, "StretchPaintImage", HAPI_StretchPaintImage );
	lua_register ( g_pLuaState, "FillRectangle", HAPI_FillRectangle );
	lua_register ( g_pLuaState, "TextOut", HAPI_TextOut );
	lua_register ( g_pLuaState, "Show", HAPI_Show );
	lua_register ( g_pLuaState, "DeleteImage", HAPI_DeleteImage );
	lua_register ( g_pLuaState, "DeleteAllImage", HAPI_DeleteAllImage );

	lua_register ( g_pLuaState, "GetKeyState",     		HAPI_GetKeyState        	);
	lua_register ( g_pLuaState, "GetKeyAction",     		HAPI_GetKeyAction        	);
	lua_register ( g_pLuaState, "GetAnyKeyState",			HAPI_GetAnyKeyState     );
	lua_register ( g_pLuaState, "EnableKeyDelay", 		HAPI_EnableKeyDelay     	);
	lua_register ( g_pLuaState, "DisableKeyDelay",    HAPI_DisableKeyDelay      		);
	lua_register ( g_pLuaState, "GetMouseButtonState",HAPI_GetMouseButtonState);
	lua_register ( g_pLuaState, "GetMouseButtonAction",HAPI_GetMouseButtonAction);
	lua_register ( g_pLuaState, "GetMouseXOffset",		HAPI_GetMouseXOffset    	);
	lua_register ( g_pLuaState, "GetMouseYOffset",		HAPI_GetMouseYOffset    	);
	lua_register ( g_pLuaState, "GetMouseZOffset",		HAPI_GetMouseZOffset    	);

	lua_register ( g_pLuaState, "LoadSound", HAPI_LoadSound);
	lua_register ( g_pLuaState, "ReplicateSound", HAPI_ReplicateSound);
	lua_register ( g_pLuaState, "PlaySound", HAPI_PlaySound);
	lua_register ( g_pLuaState, "StopSound", HAPI_StopSound);
	lua_register ( g_pLuaState, "StopAllSounds", HAPI_StopAllSounds);
	lua_register ( g_pLuaState, "DeleteSound", HAPI_DeleteSound);
	lua_register ( g_pLuaState, "DeleteAllSounds", HAPI_DeleteAllSounds);
	lua_register ( g_pLuaState, "GetSoundStatus", HAPI_GetSoundStatus);
	lua_register ( g_pLuaState, "SetSoundVolume", HAPI_SetSoundVolume);
	lua_register ( g_pLuaState, "SetSoundFreq", HAPI_SetSoundFreq);
	lua_register ( g_pLuaState, "SetSoundPan", HAPI_SetSoundPan);

	lua_register ( g_pLuaState, "LoadMIDI", HAPI_LoadMIDI);
	lua_register ( g_pLuaState, "PlayMIDI", HAPI_PlayMIDI);
	lua_register ( g_pLuaState, "StopMIDI", HAPI_StopMIDI);
	lua_register ( g_pLuaState, "DeleteAllMIDI", HAPI_DeleteAllMIDI);
	lua_register ( g_pLuaState, "DeleteMIDI", HAPI_DeleteMIDI);
	lua_register ( g_pLuaState, "GetMIDIStatus", HAPI_GetMIDIStatus);

	lua_register ( g_pLuaState, "GetTimerState", HAPI_GetTimerState );
	lua_register ( g_pLuaState, "ClearTimer", HAPI_ClearTimer );
	lua_register ( g_pLuaState, "InitTimer", HAPI_InitTimer );

	srand(GetTickCount());
}

void Lua_RegisterDInputKeyboardMapping()
{
	SetGlobalNumber("DIK_0",             DIK_0)
		SetGlobalNumber("DIK_1",             DIK_1)
		SetGlobalNumber("DIK_2",             DIK_2)
		SetGlobalNumber("DIK_3",             DIK_3)
		SetGlobalNumber("DIK_4",             DIK_4)
		SetGlobalNumber("DIK_5",             DIK_5)
		SetGlobalNumber("DIK_6",             DIK_6)
		SetGlobalNumber("DIK_7",             DIK_7)
		SetGlobalNumber("DIK_8",             DIK_8)
		SetGlobalNumber("DIK_9",             DIK_9)
		SetGlobalNumber("DIK_A",             DIK_A)
		SetGlobalNumber("DIK_ABNT_C1",       DIK_ABNT_C1)
		SetGlobalNumber("DIK_ABNT_C2",       DIK_ABNT_C2)
		SetGlobalNumber("DIK_ADD",           DIK_ADD)
		SetGlobalNumber("DIK_APOSTROPHE",    DIK_APOSTROPHE)
		SetGlobalNumber("DIK_APPS",          DIK_APPS)
		SetGlobalNumber("DIK_AT",            DIK_AT)
		SetGlobalNumber("DIK_AX",            DIK_AX)
		SetGlobalNumber("DIK_B",             DIK_B)
		SetGlobalNumber("DIK_BACK",          DIK_BACK)
		SetGlobalNumber("DIK_BACKSLASH",     DIK_BACKSLASH)
		SetGlobalNumber("DIK_C",             DIK_C)
		SetGlobalNumber("DIK_CALCULATOR",    DIK_CALCULATOR)
		SetGlobalNumber("DIK_CAPITAL",       DIK_CAPITAL)
		SetGlobalNumber("DIK_COLON",         DIK_COLON)
		SetGlobalNumber("DIK_COMMA",         DIK_COMMA)
		SetGlobalNumber("DIK_CONVERT",       DIK_CONVERT)
		SetGlobalNumber("DIK_D",             DIK_D)
		SetGlobalNumber("DIK_DECIMAL",       DIK_DECIMAL)
		SetGlobalNumber("DIK_DELETE",        DIK_DELETE)
		SetGlobalNumber("DIK_DIVIDE",        DIK_DIVIDE)
		SetGlobalNumber("DIK_DOWN",          DIK_DOWN)
		SetGlobalNumber("DIK_E",             DIK_E)
		SetGlobalNumber("DIK_END",           DIK_END)
		SetGlobalNumber("DIK_EQUALS",        DIK_EQUALS)
		SetGlobalNumber("DIK_ESCAPE",        DIK_ESCAPE)
		SetGlobalNumber("DIK_F",             DIK_F)
		SetGlobalNumber("DIK_F1",            DIK_F1)
		SetGlobalNumber("DIK_F2",            DIK_F2)
		SetGlobalNumber("DIK_F3",            DIK_F3)
		SetGlobalNumber("DIK_F4",            DIK_F4)
		SetGlobalNumber("DIK_F5",            DIK_F5)
		SetGlobalNumber("DIK_F6",            DIK_F6)
		SetGlobalNumber("DIK_F7",            DIK_F7)
		SetGlobalNumber("DIK_F8",            DIK_F8)
		SetGlobalNumber("DIK_F9",            DIK_F9)
		SetGlobalNumber("DIK_F10",           DIK_F10)
		SetGlobalNumber("DIK_F11",           DIK_F11)
		SetGlobalNumber("DIK_F12",           DIK_F12)
		SetGlobalNumber("DIK_F13",           DIK_F13)
		SetGlobalNumber("DIK_F14",           DIK_F14)
		SetGlobalNumber("DIK_F15",           DIK_F15)
		SetGlobalNumber("DIK_G",             DIK_G)
		SetGlobalNumber("DIK_GRAVE",         DIK_GRAVE)
		SetGlobalNumber("DIK_H",             DIK_H)
		SetGlobalNumber("DIK_HOME",          DIK_HOME)
		SetGlobalNumber("DIK_I",             DIK_I)
		SetGlobalNumber("DIK_INSERT",        DIK_INSERT)
		SetGlobalNumber("DIK_J",             DIK_J)
		SetGlobalNumber("DIK_K",             DIK_K)
		SetGlobalNumber("DIK_KANA",          DIK_KANA)
		SetGlobalNumber("DIK_KANJI",         DIK_KANJI)
		SetGlobalNumber("DIK_L",             DIK_L)
		SetGlobalNumber("DIK_LBRACKET",      DIK_LBRACKET)
		SetGlobalNumber("DIK_LCONTROL",      DIK_LCONTROL)
		SetGlobalNumber("DIK_LEFT",          DIK_LEFT)
		SetGlobalNumber("DIK_LMENU",         DIK_LMENU)
		SetGlobalNumber("DIK_LSHIFT",        DIK_LSHIFT)
		SetGlobalNumber("DIK_LWIN",          DIK_LWIN)
		SetGlobalNumber("DIK_M",             DIK_M)
		SetGlobalNumber("DIK_MAIL",          DIK_MAIL)
		SetGlobalNumber("DIK_MEDIASELECT",   DIK_MEDIASELECT)
		SetGlobalNumber("DIK_MEDIASTOP",     DIK_MEDIASTOP)
		SetGlobalNumber("DIK_MINUS",         DIK_MINUS)
		SetGlobalNumber("DIK_MULTIPLY",      DIK_MULTIPLY)
		SetGlobalNumber("DIK_MUTE",          DIK_MUTE)
		SetGlobalNumber("DIK_MYCOMPUTER",    DIK_MYCOMPUTER)
		SetGlobalNumber("DIK_N",             DIK_N)
		SetGlobalNumber("DIK_NEXT",          DIK_NEXT)
		SetGlobalNumber("DIK_NEXTTRACK",     DIK_NEXTTRACK)
		SetGlobalNumber("DIK_NOCONVERT",     DIK_NOCONVERT)
		SetGlobalNumber("DIK_NUMLOCK",       DIK_NUMLOCK)
		SetGlobalNumber("DIK_NUMPAD0",       DIK_NUMPAD0)
		SetGlobalNumber("DIK_NUMPAD1",       DIK_NUMPAD1)
		SetGlobalNumber("DIK_NUMPAD2",       DIK_NUMPAD2)
		SetGlobalNumber("DIK_NUMPAD3",       DIK_NUMPAD3)
		SetGlobalNumber("DIK_NUMPAD4",       DIK_NUMPAD4)
		SetGlobalNumber("DIK_NUMPAD5",       DIK_NUMPAD5)
		SetGlobalNumber("DIK_NUMPAD6",       DIK_NUMPAD6)
		SetGlobalNumber("DIK_NUMPAD7",       DIK_NUMPAD7)
		SetGlobalNumber("DIK_NUMPAD8",       DIK_NUMPAD8)
		SetGlobalNumber("DIK_NUMPAD9",       DIK_NUMPAD9)
		SetGlobalNumber("DIK_NUMPADCOMMA",   DIK_NUMPADCOMMA)
		SetGlobalNumber("DIK_NUMPADENTER",   DIK_NUMPADENTER)
		SetGlobalNumber("DIK_NUMPADEQUALS",  DIK_NUMPADEQUALS)
		SetGlobalNumber("DIK_O",             DIK_O)
		SetGlobalNumber("DIK_OEM_102",       DIK_OEM_102)
		SetGlobalNumber("DIK_P",             DIK_P)
		SetGlobalNumber("DIK_PAUSE",         DIK_PAUSE)
		SetGlobalNumber("DIK_PERIOD",        DIK_PERIOD)
		SetGlobalNumber("DIK_PLAYPAUSE",     DIK_PLAYPAUSE)
		SetGlobalNumber("DIK_POWER",         DIK_POWER)
		SetGlobalNumber("DIK_PREVTRACK",     DIK_PREVTRACK)
		SetGlobalNumber("DIK_PRIOR",         DIK_PRIOR)
		SetGlobalNumber("DIK_Q",             DIK_Q)
		SetGlobalNumber("DIK_R",             DIK_R)
		SetGlobalNumber("DIK_RBRACKET",      DIK_RBRACKET)
		SetGlobalNumber("DIK_RCONTROL",      DIK_RCONTROL)
		SetGlobalNumber("DIK_RETURN",        DIK_RETURN)
		SetGlobalNumber("DIK_RIGHT",         DIK_RIGHT)
		SetGlobalNumber("DIK_RMENU",         DIK_RMENU)
		SetGlobalNumber("DIK_RSHIFT",        DIK_RSHIFT)
		SetGlobalNumber("DIK_RWIN",          DIK_RWIN)
		SetGlobalNumber("DIK_S",             DIK_S)
		SetGlobalNumber("DIK_SCROLL",        DIK_SCROLL)
		SetGlobalNumber("DIK_SEMICOLON",     DIK_SEMICOLON)
		SetGlobalNumber("DIK_SLASH",         DIK_SLASH)
		SetGlobalNumber("DIK_SLEEP",         DIK_SLEEP)
		SetGlobalNumber("DIK_SPACE",         DIK_SPACE)
		SetGlobalNumber("DIK_STOP",          DIK_STOP)
		SetGlobalNumber("DIK_SUBTRACT",      DIK_SUBTRACT)
		SetGlobalNumber("DIK_SYSRQ",         DIK_SYSRQ)
		SetGlobalNumber("DIK_T",             DIK_T)
		SetGlobalNumber("DIK_TAB",           DIK_TAB)
		SetGlobalNumber("DIK_U",             DIK_U)
		SetGlobalNumber("DIK_UNDERLINE",     DIK_UNDERLINE)
		SetGlobalNumber("DIK_UNLABELED",     DIK_UNLABELED)
		SetGlobalNumber("DIK_UP",            DIK_UP)
		SetGlobalNumber("DIK_V",             DIK_V)
		SetGlobalNumber("DIK_VOLUMEDOWN",    DIK_VOLUMEDOWN)
		SetGlobalNumber("DIK_VOLUMEUP",      DIK_VOLUMEUP)
		SetGlobalNumber("DIK_W",             DIK_W)
		SetGlobalNumber("DIK_WAKE",          DIK_WAKE)
		SetGlobalNumber("DIK_WEBBACK",       DIK_WEBBACK)
		SetGlobalNumber("DIK_WEBFAVORITES",  DIK_WEBFAVORITES)
		SetGlobalNumber("DIK_WEBFORWARD",    DIK_WEBFORWARD)
		SetGlobalNumber("DIK_WEBHOME",       DIK_WEBHOME)
		SetGlobalNumber("DIK_WEBREFRESH",    DIK_WEBREFRESH)
		SetGlobalNumber("DIK_WEBSEARCH",     DIK_WEBSEARCH)
		SetGlobalNumber("DIK_WEBSTOP",       DIK_WEBSTOP)
		SetGlobalNumber("DIK_X",             DIK_X)
		SetGlobalNumber("DIK_Y",             DIK_Y)
		SetGlobalNumber("DIK_YEN",           DIK_YEN)
		SetGlobalNumber("DIK_Z",             DIK_Z)
}

//void Lua_RegisterDInputMouseButtonMapping()
//{
//		SetGlobalNumber("DIMOFS_BUTTON0",  DIMOFS_BUTTON0)
//		SetGlobalNumber("DIMOFS_BUTTON1",  DIMOFS_BUTTON1)
//		SetGlobalNumber("DIMOFS_BUTTON2",  DIMOFS_BUTTON2)
//		SetGlobalNumber("DIMOFS_BUTTON3",  DIMOFS_BUTTON3)
//		SetGlobalNumber("DIMOFS_BUTTON4",  DIMOFS_BUTTON4)
//		SetGlobalNumber("DIMOFS_BUTTON5",  DIMOFS_BUTTON5)
//		SetGlobalNumber("DIMOFS_BUTTON6",  DIMOFS_BUTTON6)
//		SetGlobalNumber("DIMOFS_BUTTON7",  DIMOFS_BUTTON7)
//		SetGlobalNumber("DIMOFS_X",		   DIMOFS_X)
//		SetGlobalNumber("DIMOFS_Y",		   DIMOFS_Y)
//		SetGlobalNumber("DIMOFS_Z",		   DIMOFS_Z)
//}

/******************************************************************************************
*
*	ShutDownLua ()
*
*	Shuts down Lua by closing the global state.
*/

void Lua_ShutDown ()
{
	// Close Lua state

	lua_close ( g_pLuaState );
}

int Lua_DoFile(TCHAR * fileName)
{
	return luaL_dofile( g_pLuaState,fileName );
}

//调用 lua 无参数函数
//返回调用是否成功
int Lua_CallSub(TCHAR * func )
{
	lua_getglobal ( g_pLuaState, func );
	return	lua_pcall ( g_pLuaState, 0, 0,0 );

}
//调用 lua 无参数函数,该函数有 int 类型返回值
//返回:调用不成功:-1
//		调用成功: 返回 lua 之返回值
int Lua_CallFunction(TCHAR * func)
{
	lua_getglobal ( g_pLuaState, func );

	if(lua_pcall ( g_pLuaState, 0, 1,0 ))
	{
		return -1;
	}

	if (!lua_isnumber(g_pLuaState,-1))
	{
		return -1;
	}

	int ret = lua_tonumber(g_pLuaState,-1);
	lua_pop(g_pLuaState,1);
	return ret;
}

int Lua_ReadGlobalNumber(TCHAR * varName)
{
	int ret;
	lua_getglobal(g_pLuaState,varName);
	ret = lua_tonumber(g_pLuaState,-1);
	lua_pop(g_pLuaState,1);
	return ret;
}

bool Lua_ReadGlobalBoolean(TCHAR * varName)
{
	bool ret;
	lua_getglobal(g_pLuaState,varName);
	ret = lua_toboolean(g_pLuaState,-1);
	lua_pop(g_pLuaState,1);
	return ret;
}

void Lua_ReadGlobalString(TCHAR * varName,TCHAR * buf)
{
	const char * ret;
	//int size;
	lua_getglobal(g_pLuaState,varName);
	//size = lua_objlen(g_pLuaState,-1);
	ret = lua_tostring(g_pLuaState,-1);
	strcpy(buf,ret);
	lua_pop(g_pLuaState,1);
}


// ---- Host API ------------------------------------------------------------------------------

/*
The following functions are registered with the Lua scripting system so that Lua
scripts can call them. This allows them to interact with and control this program (the
host application). Together they form the Host API (HAPI). Within this program they are
all prefixed with "HAPI_" to separate them from normal functions. Within the Lua script
they do not carry this prefix.

C functions can only be registered with Lua if their signatures are of a proper type,
namely:

int FunctionName ( lua_State * pLuaState )

Therefore, all functions in this section will follow this convention.
*/
//int RGB(r,g,b)
int HAPI_RGB ( lua_State * pLuaState )
{
	int r = GetIntParam( 1 );
	int g = GetIntParam( 2 );
	int b = GetIntParam( 3 );

	ReturnNumer( RGB(r,g,b) );

	return 1;
}
//int GetTickCount
int HAPI_GetTickCount ( lua_State * pLuaState )
{
	ReturnNumer( GetTickCount() );
	return 1;
}

//int GetRandomNumber(min,max)
int HAPI_GetRandomNumber ( lua_State * pLuaState )
{
	// Read in parameters

	int iMin = GetIntParam ( 1 );
	int iMax = GetIntParam ( 2 );

	// Return a random number between iMin and iMax

	ReturnNumer ( ( rand () % ( iMax + 1 - iMin ) ) + iMin );
	return 1;
}
//bool x y width height  IntersectRect(x1,y1,width1,height1,x2,y2,width2,height2)
int HAPI_IntersectRect(lua_State * pLuaState )
{
	int x1 = GetIntParam( 1 );
	int y1 = GetIntParam( 2 );
	int width1 = GetIntParam( 3 );
	int height1 = GetIntParam( 4 );
	int x2 = GetIntParam( 5 );
	int y2 = GetIntParam( 6 );
	int width2 = GetIntParam( 7 );
	int height2 = GetIntParam( 8 );
	RECT r;
	RECT r1 = {x1,y1,x1 + width1,y1 + height1};
	RECT r2 = {x2,y2,x2 + width2,y2 + height2};
	BOOL ret;

	ret = IntersectRect(&r,&r1,&r2);

	ReturnBoolean( ret );
	ReturnNumer( r.left );
	ReturnNumer( r.top );
	ReturnNumer( r.right - r.left );
	ReturnNumer( r.bottom - r.top );

	return 5;
}

int Game_ToggleScreenMode(void);
//int ToggleScreenMode()
int HAPI_ToggleScreenMode( lua_State * pLuaState)
{
	ReturnNumer( Game_ToggleScreenMode() );
	return 1;
}

//Image
//int LoadImage(fileName)
int HAPI_LoadImage ( lua_State * pLuaState )
{
	const TCHAR * s = GetStringParam( 1 );
	ReturnNumer( DDraw_LoadImage((TCHAR *)s) );
	return 1;
}

//int SetColorKey(imageID,colorKey)
int HAPI_SetColorKey( lua_State * pLuaState)
{
	int id = GetIntParam( 1 );
	COLORREF color = GetIntParam( 2 );

	ReturnNumer( DDraw_SetColorKey(id,color) );

	return 1;
}

//int PaintImage(imageID,x,y)
int HAPI_PaintImage( lua_State * pLuaState)
{
	int id = GetIntParam( 1 );
	int x = GetIntParam( 2 );
	int y = GetIntParam( 3 );
	POINT p = {x,y};

	ReturnNumer( DDraw_PaintImage(id,p) );

	return 1;
}


//int StretchPaintImage(imageID,left,top,width,height,srcLeft,srcTop,srcWidth,srcHeight)
int HAPI_StretchPaintImage( lua_State * pLuaState)
{
	int id = GetIntParam( 1 );
	int left = GetIntParam( 2 );
	int top = GetIntParam( 3 );
	int width = GetIntParam( 4 );
	int height = GetIntParam( 5 );

	RECT targetRect = {left,top,left + width,top + height};

	left = GetIntParam( 6 );
	top = GetIntParam( 7 );
	width = GetIntParam( 8 );
	height = GetIntParam( 9 );
	RECT sourceRect = {left,top,left + width,top + height};

	ReturnNumer( DDraw_StretchPaintImage(id,targetRect,sourceRect) );

	return 1;
}

//int FillRectangle(color, left,top,right,bottom)
int HAPI_FillRectangle( lua_State * pLuaState)
{
	COLORREF color = GetIntParam( 1 );
	int left = GetIntParam( 2 );
	int top = GetIntParam( 3 );
	int right = GetIntParam( 4 );
	int bottom = GetIntParam( 5 );
	RECT r = {left,top,right,bottom};

	ReturnNumer( DDraw_FillRectangle(color,r) );

	return 1;
}

//int TextOut(str, x,y,color)
int HAPI_TextOut( lua_State * pLuaState)
{
	const TCHAR * s = GetStringParam( 1 );
	int x = GetIntParam( 2 );
	int y = GetIntParam( 3 );
	COLORREF color = GetIntParam( 4 );

	ReturnNumer( DDraw_TextOut((TCHAR *)s,x,y,color) );

	return 1;
}

//int Show()
int HAPI_Show( lua_State * pLuaState)
{
	ReturnNumer( DDraw_Show() );
	return 1;
}

//int DeleteImage(imageID)
int HAPI_DeleteImage( lua_State * pLuaState)
{
	int id =GetIntParam( 1 );
	ReturnNumer( DDraw_DeleteImage(id) );
	return 1;
}

//int DeleteAllImage()
int HAPI_DeleteAllImage(lua_State * pLuaState)
{
	ReturnNumer( DDraw_DeleteAllImage() );
	return 1;
}

//int GetKeyState( iScanCode )
int HAPI_GetKeyState(lua_State * pLuaState)
{
	int iScanCode = GetIntParam( 1 );
	ReturnBoolean( DInput_GetKeyState(iScanCode) );
	return 1;
}
//int GetKeyAction( iScanCode,hitDown )
int HAPI_GetKeyAction(lua_State * pLuaState)
{
	int iScanCode = GetIntParam( 1 );
	bool hitDown = GetBooleanParam( 2 );
	int ret = DInput_GetKeyAction(iScanCode,hitDown) ;
	ReturnBoolean( ret);
	return 1;
}

//int GetAnyKeyState(  )
int HAPI_GetAnyKeyState(lua_State * pLuaState)
{
	ReturnBoolean( DInput_GetAnyKeyState() );
	return 1;
}

// EnableKeyDelay(  )
int HAPI_EnableKeyDelay(lua_State * pLuaState)
{
	DInput_EnableKeyDelay() ;
	return 0;
}

// DisableKeyDelay(  )
int HAPI_DisableKeyDelay(lua_State * pLuaState)
{
	DInput_DisableKeyDelay() ;
	return 0;
}

//int GetMouseButtonState( iButtinID )
int HAPI_GetMouseButtonState(lua_State * pLuaState)
{
	int iButtonID = GetIntParam( 1 );
	ReturnBoolean( DInput_GetMouseButtonState(iButtonID) );
	return 1;
}
//bool GetMouseButtonAction(ibuttonID,hitDown)
int HAPI_GetMouseButtonAction(lua_State * pLuaState)
{
	int iButtonID = GetIntParam( 1 );
	bool hitDown = GetBooleanParam( 2 );
	int ret = DInput_GetMouseButtonAction(iButtonID,hitDown) ;
	ReturnBoolean( ret);
	return 1;

}

//int GetMouseXOffset(  )
int HAPI_GetMouseXOffset(lua_State * pLuaState)
{
	ReturnNumer( DInput_GetMouseXOffset() );
	return 1;
}

//int GetMouseYOffset(  )
int HAPI_GetMouseYOffset(lua_State * pLuaState)
{
	ReturnNumer( DInput_GetMouseYOffset() );
	return 1;
}

//int GetMouseZOffset(  )
int HAPI_GetMouseZOffset(lua_State * pLuaState)
{
	ReturnNumer( DInput_GetMouseZOffset() );
	return 1;
}



//Sound
//int LoadSound(str)
int HAPI_LoadSound(lua_State * pLuaState)
{
	const TCHAR * fileName = GetStringParam( 1 );

	ReturnNumer( DSound_LoadSound( (TCHAR *) fileName ) );
	return 1;
}

//int ReplicateSound( id )
int HAPI_ReplicateSound(lua_State * pLuaState)
{
	int id = GetIntParam( 1 );
	ReturnNumer( DSound_ReplicateSound( id ) );
	return 1;
}
//int PlaySound(id,loop)
int HAPI_PlaySound(lua_State * pLuaState)
{
	int id = GetIntParam( 1 );
	bool loop = GetBooleanParam( 2 );
	DWORD flag = loop?DSBPLAY_LOOPING:0;
	ReturnNumer( DSound_PlaySound(id,flag) );
	return 1;
}
//int StopSound(id)
int HAPI_StopSound(lua_State * pLuaState)
{
	int id = GetIntParam( 1 );
	ReturnNumer( DSound_StopSound( id ) );
	return 1;
}
//int StopAllSounds()
int HAPI_StopAllSounds(lua_State * pLuaState)
{
	ReturnNumer( DSound_StopAllSounds() );
	return 1;
}
//int StopSound(id)
int HAPI_DeleteSound(lua_State * pLuaState)
{
	int id = GetIntParam( 1 );
	ReturnNumer( DSound_DeleteSound( id ) );
	return 1;
}
// int DeleteAllSounds()
int HAPI_DeleteAllSounds(lua_State * pLuaState)
{
	ReturnNumer( DSound_DeleteAllSounds() );
	return 1;
}
//bool GetSoundStatus
int HAPI_GetSoundStatus(lua_State * pLuaState)
{
	int id = GetIntParam( 1 );
	DWORD status = DSound_GetSoundStatus( id );
	BOOL stopped = ((DSBSTATUS_TERMINATED  & status) == DSBSTATUS_TERMINATED ) || ((DSBSTATUS_BUFFERLOST  & status) == DSBSTATUS_BUFFERLOST );

	ReturnBoolean( ! stopped );
	return 1;
}
//int SetSoundVolue(id,vol)
int HAPI_SetSoundVolume(lua_State * pLuaState)
{
	int id = GetIntParam( 1 );
	int vol = GetIntParam( 2 );

	ReturnNumer( DSound_SetSoundVolume( id,vol ) );
	return 1;
}
//int SetSoundFreq(id,freq)
int HAPI_SetSoundFreq(lua_State * pLuaState)
{
	int id = GetIntParam( 1 );
	int freq = GetIntParam( 2 );

	ReturnNumer( DSound_SetSoundFreq( id,freq ) );
	return 1;

}
//int SetSoundPan(id,pan)
int HAPI_SetSoundPan(lua_State * pLuaState)
{
	int id = GetIntParam( 1 );
	int pan = GetIntParam( 2 );

	ReturnNumer( DSound_SetSoundPan( id,pan ) );
	return 1;
}

//int LoadMIDI(str)
int HAPI_LoadMIDI(lua_State * pLuaState)
{
	const TCHAR * fileName = GetStringParam( 1 );
	ReturnNumer( DMusic_LoadMIDI((TCHAR *)fileName) );
	return 1;
}
//int PlayMIDI(id)
int HAPI_PlayMIDI(lua_State * pLuaState)
{
	int id = GetIntParam( 1 );
	ReturnNumer( DMusic_PlayMIDI(id) );
	return 1;
}
//int StopMIDI(id)
int HAPI_StopMIDI(lua_State * pLuaState)
{
	int id = GetIntParam( 1 );
	ReturnNumer( DMusic_StopMIDI(id) );
	return 1;
}
//int DeleteAllMIDI()
int HAPI_DeleteAllMIDI(lua_State * pLuaState)
{
	ReturnNumer( DMusic_DeleteAllMIDI() );
	return 1;
}
//int DeleteMIDI(id)
int HAPI_DeleteMIDI(lua_State * pLuaState)
{
	int id = GetIntParam( 1 );
	ReturnNumer( DMusic_DeleteMIDI(id) );
	return 1;
}
//bool GetMIDIStatus(id)
int HAPI_GetMIDIStatus(lua_State * pLuaState)
{
	int id = GetIntParam( 1 );
	ReturnBoolean( MIDI_PLAYING == DMusic_GetMIDIStatus(id) ? TRUE : FALSE  );
	return 1;
}

//Timer
//bool GetTimerState ( id )
int HAPI_GetTimerState (lua_State * pLuaState)
{
	int id = GetIntParam( 1 );
	ReturnBoolean( Timer_GetTimerState(id) );
	return 1;
}

//ClearTimer( id )
int HAPI_ClearTimer (lua_State * pLuaState)
{
	int id = GetIntParam( 1 );
	Timer_ClearTimer(id) ;
	return 0;
}

//int InitTimer( iLength )
int HAPI_InitTimer (lua_State * pLuaState)
{
	int iLength = GetIntParam( 1 );
	ReturnNumer( Timer_InitTimer(iLength) );
	return 1;
}
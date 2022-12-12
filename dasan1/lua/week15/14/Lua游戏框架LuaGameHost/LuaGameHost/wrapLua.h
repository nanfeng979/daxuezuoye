/*==========================================================================
*
*  Copyright (C) 2008 South China Institute Of Software Engineering,GZU. All Rights Reserved.
*
*  File:       wrapLua.h
*  Content:    Lua Wrapper,HostAPI
*  Author:	   YuanGuanYuan
*  Create:	   2008-11-08
***************************************************************************/


#include <lua.hpp>


/******************************************************************************************
*
*	CallLuaFunc ()
*
*	Calls a Lua function.
*/

#define CallLuaFunc( FuncName, Params, Results )	\
	{													\
	lua_getglobal ( g_pLuaState, FuncName );		\
	lua_call ( g_pLuaState, Params, Results );		\
	}


/******************************************************************************************
*
*	GetIntParam ()
*
*	Returns an integer parameter.
*/

#define GetIntParam( Index )	\
	\
	( int ) lua_tonumber ( g_pLuaState, Index );

#define  GetStringParam( Index ) \
	\
	lua_tostring( g_pLuaState, Index);

#define  GetBooleanParam( Index ) \
	\
	lua_toboolean( g_pLuaState, Index);
/******************************************************************************************
*
*	ReturnNumer ()
*
*	Returns a numeric value to a Lua caller.
*/

#define ReturnNumer( Numer )	\
	\
	lua_pushnumber ( g_pLuaState, Numer );

#define  ReturnBoolean( Numer )	\
	\
	lua_pushboolean(g_pLuaState, Numer);


#define  SetGlobalNumber( VarName, Number ) \
	lua_pushnumber( g_pLuaState, Number);	\
	lua_setglobal( g_pLuaState, VarName);



void Lua_Init ();
void Lua_ShutDown ();
int Lua_DoFile(TCHAR * fileName);
int Lua_CallSub(TCHAR * func );
int Lua_CallFunction(TCHAR * func);

void Lua_RegisterDInputKeyboardMapping();
//void Lua_RegisterDInputMouseButtonMapping();
int Lua_ReadGlobalNumber(TCHAR * varName);
bool Lua_ReadGlobalBoolean(TCHAR * varName);
void Lua_ReadGlobalString(TCHAR * varName,TCHAR * buf);

//Misc
int HAPI_RGB(lua_State * pLuaState);
int HAPI_GetRandomNumber ( lua_State * pLuaState );
int HAPI_GetTickCount ( lua_State * pLuaState );
int HAPI_ToggleScreenMode( lua_State * pLuaState);
//bool x y width height  IntersectRect(x1,y1,width1,height1,x2,y2,width2,height2)
int HAPI_IntersectRect(lua_State * pLuaState );

//Image
int HAPI_LoadImage ( lua_State * pLuaState );
int HAPI_SetColorKey( lua_State * pLuaState);
int HAPI_PaintImage( lua_State * pLuaState);
int HAPI_StretchPaintImage( lua_State * pLuaState);
int HAPI_FillRectangle( lua_State * pLuaState);
int HAPI_TextOut( lua_State * pLuaState);
int HAPI_Show( lua_State * pLuaState);
int HAPI_DeleteImage( lua_State * pLuaState);
int HAPI_DeleteAllImage(lua_State * pLuaState);

//Input
int HAPI_GetKeyState(lua_State * pLuaState);
int HAPI_GetKeyAction(lua_State * pLuaState);
int HAPI_GetAnyKeyState(lua_State * pLuaState);
int HAPI_EnableKeyDelay(lua_State * pLuaState);
int HAPI_DisableKeyDelay(lua_State * pLuaState);
int HAPI_GetMouseButtonState(lua_State * pLuaState);
int HAPI_GetMouseButtonAction(lua_State * pLuaState);
int HAPI_GetMouseXOffset(lua_State * pLuaState);
int HAPI_GetMouseYOffset(lua_State * pLuaState);
int HAPI_GetMouseZOffset(lua_State * pLuaState);

//Sound
int HAPI_LoadSound(lua_State * pLuaState);
int HAPI_ReplicateSound(lua_State * pLuaState);
int HAPI_PlaySound(lua_State * pLuaState);
int HAPI_StopSound(lua_State * pLuaState);
int HAPI_StopAllSounds(lua_State * pLuaState);
int HAPI_DeleteSound(lua_State * pLuaState);
int HAPI_DeleteAllSounds(lua_State * pLuaState);
int HAPI_GetSoundStatus(lua_State * pLuaState);
int HAPI_SetSoundVolume(lua_State * pLuaState);
int HAPI_SetSoundFreq(lua_State * pLuaState);
int HAPI_SetSoundPan(lua_State * pLuaState);

//Music
int HAPI_LoadMIDI(lua_State * pLuaState);
int HAPI_PlayMIDI(lua_State * pLuaState);
int HAPI_StopMIDI(lua_State * pLuaState);
int HAPI_DeleteAllMIDI(lua_State * pLuaState);
int HAPI_DeleteMIDI(lua_State * pLuaState);
int HAPI_GetMIDIStatus(lua_State * pLuaState);


//Timer
int HAPI_GetTimerState (lua_State * pLuaState);
int HAPI_HandleTimers (lua_State * pLuaState);
int HAPI_ClearTimer (lua_State * pLuaState);
int HAPI_InitTimer (lua_State * pLuaState);
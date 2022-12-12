/*==========================================================================
*
*  Copyright (C) 2008 South China Institute Of Software Engineering,GZU. All Rights Reserved.
*
*  File:       wrapDMusic.h
*  Content:    Direct Music Wrapper
*  Author:	   YuanGuanYuan
*  Create:	   2008-11-08
***************************************************************************/

#pragma once

#include <dmusici.h>
#include <dsound.h>

typedef struct DMUSIC_MIDI_TYP
{
	IDirectMusicSegment * dm_segment;
	IDirectMusicSegmentState * dm_segstate;
	int id;
	int state;
}
DMUSIC_MIDI, *DMUSIC_MIDI_PTR;


#define DM_NUM_SEGMENTS                     64

#define MIDI_NULL                           0
#define MIDI_LOADED                         1
#define MIDI_PLAYING                        2
#define MIDI_STOPPED                        3
#define MULTI_TO_WIDE( x,y )  MultiByteToWideChar( CP_ACP,MB_PRECOMPOSED, y,-1,x,_MAX_PATH);
#define DD_INIT_STRUCT(ddstruct) { memset(&ddstruct,0,sizeof(ddstruct)); ddstruct.dwSize=sizeof(ddstruct); }

int DMusic_Init(void);
int DMusic_Shutdown(void);

int DMusic_LoadMIDI(char *filename);
int DMusic_PlayMIDI(int id);
int DMusic_StopMIDI(int id);
int DMusic_DeleteAllMIDI(void);
int DMusic_DeleteMIDI(int id);
int DMusic_GetMIDIStatus(int id);

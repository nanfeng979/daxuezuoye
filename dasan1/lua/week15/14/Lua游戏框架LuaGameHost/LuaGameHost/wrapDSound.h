/*==========================================================================
*
*  Copyright (C) 2008 South China Institute Of Software Engineering,GZU. All Rights Reserved.
*
*  File:       wrapDSound.h
*  Content:    DirectSound Wrapper
*  Author:	   YuanGuanYuan
*  Create:	   2008-11-08
***************************************************************************/


#include <mmsystem.h>

#include <dsound.h>


#ifndef DSBCAPS_CTRLDEFAULT
#define DSBCAPS_CTRLDEFAULT ( DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME )
#endif

#define MAX_SOUNDS                          256

#define SOUND_NULL                          0
#define SOUND_LOADED                        1
#define SOUND_PLAYING                       2
#define SOUND_STOPPED                       3
#define DSVOLUME_TO_DB(volume) ((DWORD)(-30*(100 - volume)))

typedef struct pcm_sound_typ
{
	LPDIRECTSOUNDBUFFER dsbuffer;
	int state;
	int rate;
	int size;
	int id;
}
pcm_sound, *pcm_sound_ptr;


int DSound_Init(void);
int DSound_Shutdown(void);

int DSound_LoadSound(TCHAR *filename, int control_flags = DSBCAPS_CTRLDEFAULT);
int DSound_ReplicateSound(int source_id);
int DSound_PlaySound(int id, int flags=0, int volume=0, int rate=0, int pan=0);
int DSound_StopSound(int id);
int DSound_StopAllSounds(void);
int DSound_DeleteSound(int id);
int DSound_DeleteAllSounds(void);
int DSound_GetSoundStatus(int id);
int DSound_SetSoundVolume(int id,int vol);
int DSound_SetSoundFreq(int id,int freq);
int DSound_SetSoundPan(int id,int pan);

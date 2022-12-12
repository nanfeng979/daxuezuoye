/*==========================================================================
*
*  Copyright (C) 2008 South China Institute Of Software Engineering,GZU. All Rights Reserved.
*
*  File:       wrapDSound.cpp
*  Content:    DirectSound Wrapper
*  Author:	   YuanGuanYuan
*  Create:	   2008-11-08
***************************************************************************/

#include "stdafx.h"

#include "wrapDSound.h"

extern HWND g_hMainWindow;

LPDIRECTSOUND lpds = NULL;
DSBUFFERDESC dsbd;

LPDIRECTSOUNDBUFFER	lpdsbprimary = NULL;
pcm_sound sound_fx[MAX_SOUNDS];

WAVEFORMATEX pcmwf;

BOOL GetWaveData(void * pRes, WAVEFORMATEX * & pWaveHeader, void * & pbWaveData, DWORD & cbWaveSize);
BOOL CreateSoundBuffer(WAVEFORMATEX * pcmwf, LPDIRECTSOUNDBUFFER & m_pDsb,DWORD m_dwTheSound);
BOOL SetSoundData(void * pSoundData, DWORD dwSoundSize,LPDIRECTSOUNDBUFFER & m_pDsb) ;
//BOOL Create(LPVOID pSoundData, HWND  hWnd,LPDIRECTSOUNDBUFFER buffer);

///////////////////////////////////////////////////////////

int DSound_LoadSound(char *filename, int control_flags)
{
	// this function loads a .wav file, sets up the directsound 
	// buffer and loads the data into memory, the function returns 
	// the id number of the sound

	int	sound_id = -1,       // id of sound to be loaded
		index;               // looping variable


	// step one: are there any open id's ?
	for (index=0; index < MAX_SOUNDS; index++)
	{	
		// make sure this sound is unused
		if (sound_fx[index].state==SOUND_NULL)
		{
			sound_id = index;
			break;
		} // end if

	} // end for index

	// did we get a free id?
	if (sound_id==-1)
		return(-1);

	
	HANDLE fh = CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if (NULL == fh)
	{
		return -1;
	}
	DWORD size;
	DWORD bytesRead;
	UCHAR *fileBuffer;      
	
	size = GetFileSize(fh,NULL);

	fileBuffer = (UCHAR *)malloc(size);
	ReadFile(fh,LPVOID(fileBuffer),size,&bytesRead,NULL);
	CloseHandle(fh);

	DWORD m_dwTheSound = 0;
	LPVOID m_pTheSound = 0;

	//读入音频数据，创建缓冲区，设置数据
	WAVEFORMATEX * pcmwf;
	if( ! GetWaveData(LPVOID(fileBuffer), pcmwf, m_pTheSound, m_dwTheSound) ||
		! CreateSoundBuffer(pcmwf,sound_fx[sound_id].dsbuffer,m_dwTheSound) ||
		! SetSoundData(m_pTheSound, m_dwTheSound,sound_fx[sound_id].dsbuffer) )
		return FALSE;


	// GetWaveData       读取声效数据
	//     pSoundData为原数据，pcmwf, m_pTheSound, m_dwTheSound，提取出来的head，Data，Length
	// CreateSoundBuffer 创建缓冲区
	// SetSoundData      设置缓冲区的数据

	// set rate and size in data structure
	sound_fx[sound_id].rate  = pcmwf->nSamplesPerSec;// wfmtx.nSamplesPerSec;
	sound_fx[sound_id].size  = m_dwTheSound;
	sound_fx[sound_id].state = SOUND_LOADED;


	// release the temp buffer
	free(fileBuffer);

	// return id
	return(sound_id);

} // end DSound_Load_WAV

///////////////////////////////////////////////////////////

int DSound_ReplicateSound(int source_id)
{
	// this function replicates the sent sound and sends back the
	// id of the replicated sound, you would use this function
	// to make multiple copies of a gunshot or something that
	// you want to play multiple times simulataneously, but you
	// only want to load once

	if (source_id!=-1)
	{
		// duplicate the sound buffer
		// first hunt for an open id

		for (int id=0; id < MAX_SOUNDS; id++)
		{
			// is this sound open?
			if (sound_fx[id].state==SOUND_NULL)
			{
				// first make an identical copy
				sound_fx[id] = sound_fx[source_id];

				// now actually replicate the directsound buffer
				if (FAILED(lpds->DuplicateSoundBuffer(sound_fx[source_id].dsbuffer,
					&sound_fx[id].dsbuffer)))
				{
					// reset sound to NULL
					sound_fx[id].dsbuffer = NULL;
					sound_fx[id].state    = SOUND_NULL;

					// return error
					return(-1);
				} // end if

				// now fix up id
				sound_fx[id].id = id;

				// return replicated sound
				return(id);

			} // end if found

		} // end for id

	} // end if
	else
		return(-1);

	// else failure
	return(-1);

} // end DSound_Replicate_Sound

//////////////////////////////////////////////////////////

int DSound_Init(void)
{
	// this function initializes the sound system
	static int first_time = 1; // used to track the first time the function
	// is entered

	// test for very first time
	if (first_time)
	{		
		// clear everything out
		memset(sound_fx,0,sizeof(pcm_sound)*MAX_SOUNDS);

		// reset first time
		first_time = 0;

		// create a directsound object
		if (FAILED(DirectSoundCreate(NULL, &lpds, NULL)))
			return(0);

		// set cooperation level
		if (FAILED(lpds->SetCooperativeLevel((HWND)g_hMainWindow,DSSCL_NORMAL)))
			return(0);

	} // end if

	// initialize the sound fx array
	for (int index=0; index<MAX_SOUNDS; index++)
	{
		// test if this sound has been loaded
		if (sound_fx[index].dsbuffer)
		{
			// stop the sound
			sound_fx[index].dsbuffer->Stop();

			// release the buffer
			sound_fx[index].dsbuffer->Release();

		} // end if

		// clear the record out
		memset(&sound_fx[index],0,sizeof(pcm_sound));

		// now set up the fields
		sound_fx[index].state = SOUND_NULL;
		sound_fx[index].id    = index;

	} // end for index

	// return sucess
	return(1);

} // end DSound_Init

///////////////////////////////////////////////////////////

int DSound_Shutdown(void)
{
	// this function releases all the memory allocated and the directsound object
	// itself

	// first turn all sounds off
	DSound_StopAllSounds();

	// now release all sound buffers
	for (int index=0; index<MAX_SOUNDS; index++)
		if (sound_fx[index].dsbuffer)
			sound_fx[index].dsbuffer->Release();

	// now release the directsound interface itself
	if (lpds)
		lpds->Release();

	// return success
	return(1);

} // end DSound_Shutdown

///////////////////////////////////////////////////////////

int DSound_PlaySound(int id, int flags, int volume, int rate, int pan)
{
	// this function plays a sound, the only parameter that 
	// works is the flags which can be 0 to play once or
	// DSBPLAY_LOOPING

	if (sound_fx[id].dsbuffer)
	{
		// reset position to start
		if (FAILED(sound_fx[id].dsbuffer->SetCurrentPosition(0)))
			return(0);

		// play sound
		if (FAILED(sound_fx[id].dsbuffer->Play(0,0,flags)))
			return(0);
	} // end if

	// return success
	return(1);

} // end DSound_Play

///////////////////////////////////////////////////////////

int DSound_SetSoundVolume(int id,int vol)
{
	// this function sets the volume on a sound 0-100

	if (sound_fx[id].dsbuffer->SetVolume(DSVOLUME_TO_DB(vol))!=DS_OK)
		return(0);

	// return success
	return(1);

} // end DSound_Set_Volume

///////////////////////////////////////////////////////////

int DSound_SetSoundFreq(int id,int freq)
{
	// this function sets the playback rate

	if (sound_fx[id].dsbuffer->SetFrequency(freq)!=DS_OK)
		return(0);

	// return success
	return(1);

} // end DSound_Set_Freq

///////////////////////////////////////////////////////////

int DSound_SetSoundPan(int id,int pan)
{
	// this function sets the pan, -10,000 to 10,0000

	if (sound_fx[id].dsbuffer->SetPan(pan)!=DS_OK)
		return(0);

	// return success
	return(1);

} // end DSound_Set_Pan

////////////////////////////////////////////////////////////

int DSound_StopSound(int id)
{
	// this function stops a sound from playing
	if (sound_fx[id].dsbuffer)
	{
		sound_fx[id].dsbuffer->Stop();
		sound_fx[id].dsbuffer->SetCurrentPosition(0);
	} // end if

	// return success
	return(1);

} // end DSound_Stop_Sound

///////////////////////////////////////////////////////////

int DSound_DeleteAllSounds(void)
{
	// this function deletes all the sounds

	for (int index=0; index < MAX_SOUNDS; index++)
		DSound_DeleteSound(index);

	// return success always
	return(1);

} // end DSound_Delete_All_Sounds

///////////////////////////////////////////////////////////

int DSound_DeleteSound(int id)
{
	// this function deletes a single sound and puts it back onto the available list

	// first stop it
	if (!DSound_StopSound(id))
		return(0);

	// now delete it
	if (sound_fx[id].dsbuffer)
	{
		// release the com object
		sound_fx[id].dsbuffer->Release();
		sound_fx[id].dsbuffer = NULL;

		// return success
		return(1);
	} // end if

	// return success
	return(1);

} // end DSound_Delete_Sound

///////////////////////////////////////////////////////////

int DSound_StopAllSounds(void)
{
	// this function stops all sounds

	for (int index=0; index<MAX_SOUNDS; index++)
		DSound_StopSound(index);	

	// return success
	return(1);

} // end DSound_Stop_All_Sounds

///////////////////////////////////////////////////////////

int DSound_GetSoundStatus(int id)
{
	// this function returns the status of a sound
	if (sound_fx[id].dsbuffer)
	{
		ULONG status; 

		// get the status
		sound_fx[id].dsbuffer->GetStatus(&status);

		// return the status
		return(status);

	} // end if
	else // total failure
		return(-1);

} // end DSound_Status_Sound

//
//
////与上一Create函数入口参数不同
//BOOL Create(LPVOID pSoundData, HWND  hWnd,LPDIRECTSOUNDBUFFER buffer) {
//
//	DWORD m_dwTheSound = 0;
//	LPVOID m_pTheSound = 0;
//
//	//读入音频数据，创建缓冲区，设置数据
//	WAVEFORMATEX * pcmwf;
//	if( ! GetWaveData(pSoundData, pcmwf, m_pTheSound, m_dwTheSound) ||
//		! CreateSoundBuffer(pcmwf,buffer,m_dwTheSound) ||
//		! SetSoundData(m_pTheSound, m_dwTheSound,buffer) )
//		return FALSE;
//
//
//	// GetWaveData       读取声效数据
//	//     pSoundData为原数据，pcmwf, m_pTheSound, m_dwTheSound，提取出来的head，Data，Length
//	// CreateSoundBuffer 创建缓冲区
//	// SetSoundData      设置缓冲区的数据
//	return TRUE;
//}


BOOL GetWaveData(void * pRes, WAVEFORMATEX * & pWaveHeader, void * & pbWaveData, DWORD & cbWaveSize) {
	// pWaveHeader 音频数据的格式指针，指向文件中的格式的开始位置,用于设置缓冲区格式
	// pbWaveData  音频数据的指针，指向文件中的音频数据开始位置
	// cbWaveSize  音频数据的长度，用于设置DirectSound缓冲区的大小
	// 该函数 从资源数据* pRes中，提取格式的位置指针，音频数据起始位置的指针，数据的长度。

	pWaveHeader = 0;
	pbWaveData = 0;
	cbWaveSize = 0;

	DWORD * pdw = (DWORD *)pRes;
	//DWORD dwRiff = *pdw++;
	DWORD dwRiff = *pdw++;// dwRiff=pdw; pdw=pdw+sizeof(DWORD)
	DWORD dwLength = *pdw++;  //数据长度（字节），从该位置到文件尾
	DWORD dwType = *pdw++;

	if( dwRiff != mmioFOURCC('R', 'I', 'F', 'F') )
		return FALSE;      // not even RIFF
	//The mmioFOURCC macro converts four characters into a four-character code.

	if( dwType != mmioFOURCC('W', 'A', 'V', 'E') )
		return FALSE;      // not a WAV

	DWORD * pdwEnd = (DWORD *)((BYTE *)pdw + dwLength-4);//文件尾：减去一个DWORD=4 byte

	while( pdw < pdwEnd ) {
		dwType = *pdw++;
		dwLength = *pdw++;

		switch( dwType ) {
			case mmioFOURCC('f', 'm', 't', ' ')://format
				if( !pWaveHeader ) {
					if( dwLength < sizeof(WAVEFORMAT) )
						return FALSE;      // not a WAV

					pWaveHeader = (WAVEFORMATEX *)pdw;

					if( pbWaveData && cbWaveSize )//判断是否结束，格式头和数据读完就结束
						return TRUE;
				}
				break;

			case mmioFOURCC('d', 'a', 't', 'a')://data
				pbWaveData = LPVOID(pdw);
				cbWaveSize = dwLength;

				if( pWaveHeader ) //判断是否结束。   
					return TRUE;
				break;
		}
		pdw = (DWORD *)((BYTE *)pdw + ((dwLength+1)&~1));//跳过该段数据,保证为偶数字节
	}

	return FALSE;
}


BOOL CreateSoundBuffer(WAVEFORMATEX * pcmwf, LPDIRECTSOUNDBUFFER & m_pDsb,DWORD m_dwTheSound)
{
	DSBUFFERDESC dsbdesc;

	// Set up DSBUFFERDESC structure.
	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC)); // Zero it out.
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	// Need no controls (pan, volume, frequency).
	dsbdesc.dwFlags = DSBCAPS_STATIC|DSBCAPS_CTRLPAN|DSBCAPS_CTRLVOLUME;		// assumes that the sound is played often
	dsbdesc.dwBufferBytes = m_dwTheSound;   //设置缓冲区的大小
	dsbdesc.lpwfxFormat = pcmwf;            //设置格式   
	// Create buffer.
	HRESULT hRes;
	if( DS_OK != (hRes = lpds->CreateSoundBuffer(&dsbdesc, &m_pDsb, 0)) ) {//m_pDsb directsound buffer
		// Failed.
		m_pDsb = 0;
		return FALSE;
	}

	return TRUE;
}


BOOL SetSoundData(void * pSoundData, DWORD dwSoundSize,LPDIRECTSOUNDBUFFER & m_pDsb) 
{
	LPVOID lpvPtr1;
	DWORD dwBytes1;
	// Obtain write pointer.
	HRESULT hr = m_pDsb->Lock(0, 0, &lpvPtr1, &dwBytes1, 0, 0, DSBLOCK_ENTIREBUFFER);    
	// If DSERR_BUFFERLOST is returned, restore and retry lock.
	if(DSERR_BUFFERLOST == hr) {
		m_pDsb->Restore();
		hr = m_pDsb->Lock(0, 0, &lpvPtr1, &dwBytes1, 0, 0, DSBLOCK_ENTIREBUFFER);
	}
	if(DS_OK == hr) {
		// Write to pointers.
		::CopyMemory(lpvPtr1, pSoundData, dwBytes1);//拷贝音频数据
		// Release the data back to DirectSound.
		hr = m_pDsb->Unlock(lpvPtr1, dwBytes1, 0, 0);
		if(DS_OK == hr)
			return TRUE;
	}
	// Lock, Unlock, or Restore failed.
	return FALSE;
}
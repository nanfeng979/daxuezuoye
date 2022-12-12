/*==========================================================================
*
*  Copyright (C) 2008 South China Institute Of Software Engineering,GZU. All Rights Reserved.
*
*  File:       wrapDMusic.cpp
*  Content:    DirectMusic Wrapper
*  Author:	   YuanGuanYuan
*  Create:	   2008-11-08
***************************************************************************/


#include "stdafx.h"
#include "wrapDMusic.h"
#include <direct.h>

IDirectMusicPerformance * dm_perf = NULL;
IDirectMusicLoader * dm_loader = NULL;

DMUSIC_MIDI dm_midi[DM_NUM_SEGMENTS];
int dm_active_id = -1;

extern HWND g_hMainWindow;
extern LPDIRECTSOUND lpds;

int DMusic_LoadMIDI(char *filename)
{
	// this function loads a midi segment

	DMUS_OBJECTDESC ObjDesc; 
	HRESULT hr;
	IDirectMusicSegment* pSegment = NULL;

	int index; // loop var

	// look for open slot for midi segment
	int id = -1;

	for (index = 0; index < DM_NUM_SEGMENTS; index++)
	{
		// is this one open
		if (dm_midi[index].state == MIDI_NULL)
		{
			// validate id, but don't validate object until loaded
			id = index;
			break;
		} // end if

	} // end for index

	// found good id?
	if (id==-1)
		return(-1);

	// get current working directory
	char szDir[_MAX_PATH];
	WCHAR wszDir[_MAX_PATH]; 

	if(_getcwd( szDir, _MAX_PATH ) == NULL)
	{
		return(-1);;
	} // end if

	MULTI_TO_WIDE(wszDir, szDir);

	// tell the loader were to look for files
	hr = dm_loader->SetSearchDirectory(GUID_DirectMusicAllTypes,wszDir, FALSE);

	if (FAILED(hr)) 
	{
		return (-1);
	} // end if

	// convert filename to wide string
	WCHAR wfilename[_MAX_PATH]; 
	MULTI_TO_WIDE(wfilename, filename);

	// setup object description
	DD_INIT_STRUCT(ObjDesc);
	ObjDesc.guidClass = CLSID_DirectMusicSegment;
	wcscpy(ObjDesc.wszFileName, wfilename );
	ObjDesc.dwValidData = DMUS_OBJ_CLASS | DMUS_OBJ_FILENAME;

	// load the object and query it for the IDirectMusicSegment interface
	// This is done in a single call to IDirectMusicLoader::GetObject
	// note that loading the object also initializes the tracks and does 
	// everything else necessary to get the MIDI data ready for playback.

	hr = dm_loader->GetObject(&ObjDesc,IID_IDirectMusicSegment, (void**) &pSegment);

	if (FAILED(hr))
		return(-1);

	// ensure that the segment plays as a standard MIDI file
	// you now need to set a parameter on the band track
	// Use the IDirectMusicSegment::SetParam method and let 
	// DirectMusic find the trackby passing -1 (or 0xFFFFFFFF) in the dwGroupBits method parameter.

	hr = pSegment->SetParam(GUID_StandardMIDIFile,-1, 0, 0, (void*)dm_perf);

	if (FAILED(hr))
		return(-1);

	// This step is necessary because DirectMusic handles program changes and 
	// bank selects differently for standard MIDI files than it does for MIDI 
	// content authored specifically for DirectMusic. 
	// The GUID_StandardMIDIFile parameter must be set before the instruments are downloaded. 

	// The next step is to download the instruments. 
	// This is necessary even for playing a simple MIDI file 
	// because the default software synthesizer needs the DLS data 
	// for the General MIDI instrument set
	// If you skip this step, the MIDI file will play silently.
	// Again, you call SetParam on the segment, this time specifying the GUID_Download parameter:

	hr = pSegment->SetParam(GUID_Download, -1, 0, 0, (void*)dm_perf);

	if (FAILED(hr))
		return(-1);

	// at this point we have MIDI loaded and a valid object

	dm_midi[id].dm_segment  = pSegment;
	dm_midi[id].dm_segstate = NULL;
	dm_midi[id].state       = MIDI_LOADED;

	// return id
	return(id);

} // end DMusic_Load_MIDI

//////////////////////////////////////////////////////////

int DMusic_PlayMIDI(int id)
{
	// play sound based on id

	if (dm_midi[id].dm_segment && dm_midi[id].state!=MIDI_NULL)
	{
		// if there is an active midi then stop it
		if (dm_active_id!=-1)
			DMusic_StopMIDI(dm_active_id);

		// play segment and force tracking of state variable
		dm_perf->PlaySegment(dm_midi[id].dm_segment, 0, 0, &dm_midi[id].dm_segstate);
		dm_midi[id].state = MIDI_PLAYING;

		// set the active midi segment
		dm_active_id = id;
		return(1);
	}  // end if
	else
		return(0);

} // end DMusic_Play

//////////////////////////////////////////////////////////

int DMusic_StopMIDI(int id)
{
	// stop a midi segment
	if (dm_midi[id].dm_segment && dm_midi[id].state!=MIDI_NULL)
	{
		// play segment and force tracking of state variable
		dm_perf->Stop(dm_midi[id].dm_segment, NULL, 0, 0);
		dm_midi[id].state = MIDI_STOPPED;

		// reset active id
		dm_active_id = -1;

		return(1);
	}  // end if
	else
		return(0);

} // end DMusic_Stop

///////////////////////////////////////////////////////////

int DMusic_DeleteMIDI(int id)
{
	// this function deletes one MIDI segment

	// Unload instruments this will cause silence.
	// CloseDown unloads all instruments, so this call is also not 
	// strictly necessary.
	if (dm_midi[id].dm_segment)
	{
		dm_midi[id].dm_segment->SetParam(GUID_Unload, -1, 0, 0, (void*)dm_perf); 

		// Release the segment and set to null
		dm_midi[id].dm_segment->Release(); 
		dm_midi[id].dm_segment  = NULL;
		dm_midi[id].dm_segstate = NULL;
		dm_midi[id].state       = MIDI_NULL;
	} // end if

	return(1);

} // end DMusic_Delete_MIDI

//////////////////////////////////////////////////////////

int DMusic_DeleteAllMIDI(void)
{
	// delete all the MIDI 
	int index; // loop var

	// free up all the segments
	for (index = 0; index < DM_NUM_SEGMENTS; index++)
	{
		// Unload instruments this will cause silence.
		// CloseDown unloads all instruments, so this call is also not 
		// strictly necessary.
		if (dm_midi[index].dm_segment)
		{
			dm_midi[index].dm_segment->SetParam(GUID_Unload, -1, 0, 0, (void*)dm_perf); 

			// Release the segment and set to null
			dm_midi[index].dm_segment->Release(); 
			dm_midi[index].dm_segment  = NULL;
			dm_midi[index].dm_segstate = NULL;
			dm_midi[index].state       = MIDI_NULL;
		} // end if

	} // end for index

	return(1);

} // end DMusic_Delete_All_MIDI

//////////////////////////////////////////////////////////

int DMusic_GetMIDIStatus(int id)
{
	// this checks the status of a midi segment

	if (dm_midi[id].dm_segment && dm_midi[id].state !=MIDI_NULL )
	{
		// get the status and translate to our defines
		if (dm_perf->IsPlaying(dm_midi[id].dm_segment,NULL) == S_OK) 
			dm_midi[id].state = MIDI_PLAYING;
		else
			dm_midi[id].state = MIDI_STOPPED;

		return(dm_midi[id].state);
	} // end if
	else
		return(0);

} // end DMusic_Status_MIDI

///////////////////////////////////////////////////////////

int DMusic_Init(void)
{
	// this function initializes directmusic, it also checks if directsound has
	// been initialized, if so it connect the wave output to directsound, otherwise
	// it creates it's own directsound object, hence you must start directsound up
	// first if you want to use both directsound and directmusic

	int index; // looping var

	// set up directmusic
	// initialize COM
	if (FAILED(CoInitialize(NULL)))
	{    
		// Terminate the application.
		return(0);
	}   // end if

	// create the performance
	if (FAILED(CoCreateInstance(CLSID_DirectMusicPerformance,
		NULL,
		CLSCTX_INPROC,
		IID_IDirectMusicPerformance,
		(void**)&dm_perf)))    
	{
		// return null        
		return(0);
	} // end if

	// initialize the performance, check if directsound is on-line if so, use the
	// directsound object, otherwise create a new one
	if (FAILED(dm_perf->Init(NULL, lpds, g_hMainWindow)))
	{
		return(0);// Failure -- performance not initialized
	} // end if 

	// add the port to the performance
	if (FAILED(dm_perf->AddPort(NULL)))
	{    
		return(0);// Failure -- port not initialized
	} // end if

	// create the loader to load object(s) such as midi file
	if (FAILED(CoCreateInstance(
		CLSID_DirectMusicLoader,
		NULL,
		CLSCTX_INPROC, 
		IID_IDirectMusicLoader,
		(void**)&dm_loader)))
	{
		// error
		return(0);
	} // end if

	// reset all the midi segment objects
	for (index = 0; index < DM_NUM_SEGMENTS; index++)
	{
		// reset the object
		dm_midi[index].dm_segment  = NULL;  
		dm_midi[index].dm_segstate = NULL;  
		dm_midi[index].state       = MIDI_NULL;
		dm_midi[index].id          = index;
	} // end for index

	// reset the active id
	dm_active_id = -1;

	// all good baby
	return(1);

} // end DMusic_Init

////////////////////////////////////////////////////////////

int DMusic_Shutdown(void)
{
	// If there is any music playing, stop it. This is 
	// not really necessary, because the music will stop when
	// the instruments are unloaded or the performance is    
	// closed down.
	if (dm_perf)
		dm_perf->Stop(NULL, NULL, 0, 0 ); 

	// delete all the midis if they already haven't been
	DMusic_DeleteAllMIDI();

	// CloseDown and Release the performance object.    
	if (dm_perf)
	{
		dm_perf->CloseDown();
		dm_perf->Release();     
	} // end if

	// Release the loader object.
	if (dm_loader)
		dm_loader->Release();     

	// Release COM
	CoUninitialize(); 

	// return success
	return(1);

} // end DMusic_Shutdown

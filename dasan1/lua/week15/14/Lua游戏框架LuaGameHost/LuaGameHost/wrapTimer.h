/*==========================================================================
*
*  Copyright (C) 2008 South China Institute Of Software Engineering,GZU. All Rights Reserved.
*
*  File:       wrapTimer.h
*  Content:    Timer Wrapper
*  Author:	   YuanGuanYuan
*  Create:	   2008-11-08
***************************************************************************/

#define MAX_TIMER_COUNT				256

// ---- Timers ----------------------------------------------------------------------------

typedef struct
{
	bool bIsNull;

	int iLength;
	int iActiveTime;
	bool bIsActive;
}
Timer;


void Timer_HandleTimers();
int Timer_Init();

bool Timer_GetTimerState ( int hTimer );
void Timer_ClearTimer ( int hTimer );
int Timer_InitTimer ( int iLength );
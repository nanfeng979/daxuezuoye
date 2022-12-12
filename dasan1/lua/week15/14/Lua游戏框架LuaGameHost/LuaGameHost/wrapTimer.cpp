#include "stdafx.h"
#include "wrapTimer.h"

Timer g_Timers [ MAX_TIMER_COUNT ];

int Timer_Init()
{
	for ( int iCurrTimerIndex = 0; iCurrTimerIndex < MAX_TIMER_COUNT; ++ iCurrTimerIndex )
		g_Timers [ iCurrTimerIndex ].bIsNull = TRUE;
	
	return 1;
}
/**************************************************************************************
*
*	Timer_InitTimer ()
*
*	Initializes a timer.
*/

int Timer_InitTimer ( int iLength )
{
	bool bWasFreeTimerFound = FALSE;
	int iCurrTimerIndex = 0;
	for ( iCurrTimerIndex = 0; iCurrTimerIndex < MAX_TIMER_COUNT; ++ iCurrTimerIndex )
	{
		if ( g_Timers [ iCurrTimerIndex ].bIsNull )
		{
			bWasFreeTimerFound = TRUE;
			g_Timers [ iCurrTimerIndex ].bIsNull = FALSE;
			g_Timers [ iCurrTimerIndex ].iLength = iLength;
			g_Timers [ iCurrTimerIndex ].iActiveTime = GetTickCount () + iLength;
			break;
		}
	}

	if ( bWasFreeTimerFound )
		return iCurrTimerIndex;
	else
		return -1;
}

/**************************************************************************************
*
*	Timer_ClearTimer ()
*
*	Clears a timer.
*/

void Timer_ClearTimer ( int hTimer )
{
	if ( hTimer >= 0 && hTimer < MAX_TIMER_COUNT )
		g_Timers [ hTimer ].bIsNull = TRUE;
}

/**************************************************************************************
*
*	Timer_HandleTimers ()
*
*	Called once per frame to keep timers running.
*/

void Timer_HandleTimers ()
{
	int iCurrTickCount = GetTickCount ();

	for ( int iCurrTimerIndex = 0; iCurrTimerIndex < MAX_TIMER_COUNT; ++ iCurrTimerIndex )
	{
		g_Timers [ iCurrTimerIndex ].bIsActive = FALSE;

		if ( ! g_Timers [ iCurrTimerIndex ].bIsNull )
		{
			if ( iCurrTickCount >= g_Timers [ iCurrTimerIndex ].iActiveTime )
			{
				g_Timers [ iCurrTimerIndex ].bIsActive = TRUE;
				g_Timers [ iCurrTimerIndex ].iActiveTime = iCurrTickCount + g_Timers [ iCurrTimerIndex ].iLength;
			}
		}
	}
}

/**************************************************************************************
*
*	Timer_GetTimerState ()
*
*	Returns the state of the timer
*/

bool Timer_GetTimerState ( int hTimer )
{
	return g_Timers [ hTimer ].bIsActive;
}

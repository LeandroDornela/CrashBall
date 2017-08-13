//////////////////////////////////////////////////////////////////////////////////////////
//	TIMER.cpp
//	Functions for timer class
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#include "TIMER.h"

void TIMER::Reset()
{
	//startTime=(double)timeGetTime();
}

double TIMER::GetTime()
{
	if(isPaused)
		return pauseTime-startTime;
	else
		//return ((double)timeGetTime())-startTime;
		return 0;
}

void TIMER::Pause()
{
	//Only pause if currently unpaused
	if(isPaused)
		return;

	isPaused=true;
	//pauseTime=(double)timeGetTime();
}

void TIMER::Unpause()
{
	//Only unpause if currently paused
	if(!isPaused)
		return;

	isPaused=false;

	//Update start time to reflect pause
	//startTime+=((double)timeGetTime()-pauseTime);
}

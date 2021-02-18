//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/InterruptOnlyProgressBar.h $
//  
//  Owner: Matt Joss
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __InterruptOnlyProgressBar__
#define __InterruptOnlyProgressBar__

#include "ProgressBar.h"

class DrawInterrupter;

#pragma export on

// all this does is check for key/mouse interrupts, and return WasCancelled == true if
// they occur.  It doesn't display a progress UI.
class WIDGET_DECL CInterruptOnlyProgressImpl: public CProgressBar
{
public:
	CInterruptOnlyProgressImpl(): fpInterrupt(nil) {};
	~CInterruptOnlyProgressImpl();

	// Check this to see if the user cancelled the action
	virtual bool16	WasCancelled(bool8 setGlobalErrorState = kTrue);

	// Call this anytime during the tasks to immediately terminate
	// the entire progress bar process.  Usually called when an 
	// error condition is encountered during one of the sub tasks.  
	virtual void	Abort() {}

	//Enabling this will keep any subsequent progress bars from subdividing your progress bar
	virtual void	DisableChildProgressBars(bool16 /*disable*/) {};

	//Not usually necessary to call this.  It will return whether or not the registration of this progress
	//bar was successful(reasons for failure include another progress bar calling DisableChildProgressBars())
	virtual bool16	WasRegisterSuccessful() { return kTrue; }

	// Call this to set the position of the progressbar to a location within the specified range
	virtual void	SetPosition(int32) {}

private:
	DrawInterrupter* fpInterrupt;
};

#pragma export off

#endif

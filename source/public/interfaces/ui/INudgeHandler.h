//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/INudgeHandler.h $
//  
//  Owner: lance bushore
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
#ifndef __INudgeHandler__
#define __INudgeHandler__

class IControlView;
/**	This interface supports nudging values in editboxes. There's some user behavior we want to support which requires us
	to have this fancy interface. Namely:
	If the user clicks once on a nudge arrow button for an editbox, we want to increase the value in the editbox, and notify so the action associated with the editbox will happen.
	If the user holds shift and clicks once on a nudge arrow button for an editbox, we want to increase the value in the editbox by a larger amount, and notify so the action associated with the editbox will happen.
	If the user clicks on the nudge arrow and holds down the mouse button, we want to do the nudging, but not actually do the action for the new value until they release the mouse.
	Typically a 3rd party would not have to call or implement this interface.
*/
class INudgeHandler : public IPMUnknown
{
public:
	/** Nudging is beginning
	*/
	virtual void StartNudging() = 0;

	/** Nudge one increment
	*/
	virtual void DoNudge() = 0;

	/** Nudging is complete. This typically does a broadcast
	*/
	virtual void EndNudging() = 0;
	
	/** Set if we're doing large or small nudging.
		@param largeNudge true if we are going to do large nudging.
	*/
	virtual void SetLargeNudge(bool16 largeNudge) = 0;

	/** Get if we're doing large or small nudging.
		@return kTrue if we are going to do large nudging.
	*/
	virtual bool16 GetLargeNudge() = 0;
	
	/** Set if we are going to nudge up or down.
		@param nudgeUp kTrue if we are going to nudge up
	*/
	virtual void SetNudgeUp(bool16 nudgeUp) = 0;

	/** Get if we are going to nudge up or down.
		@return kTrue if we're nudging up
	*/
	virtual bool16 GetNudgeUp() = 0;

	/** Set the editbox we're going to be nudging.
		@param ebView the editbox widget we're going to nudge.
	*/
	virtual void SetAssociateEditBox(IControlView * ebView) = 0;
	
	/** Get the editbox we're going to be nudging.
		@return the editbox widget we're nudging
	*/
	virtual IControlView * GetAssociateEditBox() = 0;
};

#endif
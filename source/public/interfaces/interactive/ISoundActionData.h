//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ISoundActionData.h $
//  
//  Owner: Tim Wright
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
#ifndef __ISoundActionData_h__
#define __ISoundActionData_h__

#include "IBehaviorData.h"
#include "BehaviorID.h"

//========================================================================================
// CLASS ISoundActionData
//========================================================================================

/** Data interface for Sound Behavior */
class ISoundActionData : public IBehaviorData
{
public:
	enum Operation { kPlay = 0, kStop, kPause, kResume, kStopAll };
	
	/** Set play operation (kPlay, kStop, kPause, kResume, or kStopAll) */
	virtual void		SetOperation(const Operation& inOperation) = 0;

	/** Get play operation (kPlay, kStop, kPause, kResume, or kStopAll) */
	virtual Operation	GetOperation() const = 0;
	
	/** Set UID of sound page item to use for action. */
	virtual void		SetSound(const UID& inSound) = 0;

	/** Get UID of sound page item to use for action. */
	virtual UID			GetSound() const = 0;

	//These values only apply to a kPlay operation.

	/** Set Volume to play sound 0.0 to 1.0 (1.0 is full volume, 0.0 is silent). /Volume in sound action dict */
	virtual void		SetVolume(const PMReal& inVolume) = 0;

	/** Get Volume to play sound 0.0 to 1.0 (1.0 is full volume, 0.0 is silent). /Volume in sound action dict  */
	virtual PMReal		GetVolume() const = 0;
	
	/** Set whether to play sound syncronously (wait until sound is done before proceeding with other actions). /Synchronous in sound action dict  */
	virtual void		SetSynchronous(bool16 inSynchronous) = 0;

	/** Get whether to play sound syncronously (wait until sound is done before proceeding with other actions). /Synchronous in sound action dict */
	virtual bool16		GetSynchronous() const = 0;
	
	/** Set whether to Repeat sound indefinitely. /Repeat in sound action dict */
	virtual void		SetRepeat(bool16 inRepeat) = 0;

	/** Get whether to Repeat sound indefinitely. /Repeat in sound action dict */
	virtual bool16		GetRepeat() const = 0;
};

#endif // __ISoundActionData_h__

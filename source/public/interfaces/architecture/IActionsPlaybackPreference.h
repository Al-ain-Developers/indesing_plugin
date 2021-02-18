//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IActionsPlaybackPreference.h $
//  
//  Owner: jargast
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
#ifndef __IActionsPlaybackPreference__
#define __IActionsPlaybackPreference__

#include "IPMUnknown.h"
#include "AppFrameworkID.h"

/**
 Data interface for the actions playback preference. This is used to store the
 playback options on the session, as well as for the kSetActionsPlaybackOptionsCmdBoss command.
 
 Note: The default value for this preference is kTrue.
 */
class IActionsPlaybackPreference : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IACTIONSPLAYBACKPREFERENCE };
	enum PlaybackSpeed { kAccelerated, kStepByStep, kPauseFor };

	/**
	 Sets the playback speed preference.
	 
	 @param newSpeed		IN new playback speed.
	 */
	virtual void SetPlaybackSpeed (PlaybackSpeed newSpeed) = 0;
	
	/**
	 Returns the value of the playback speed preference.
	 
	 @return PlaybackSpeed
	 */
	virtual PlaybackSpeed GetPlaybackSpeed() const = 0;
	
	/**
	 Sets the pause seconds preference.
	 
	 @param pauseAmount		IN new pause amount.
	 */
	virtual void SetPauseForSeconds (PMReal pauseAmount) = 0;

	/**
	 Gets the pause seconds preference.
	 
	 @param newSpeed		IN new playback speed.
	 */
	virtual PMReal GetPauseForSeconds (void) const = 0;
};


#endif //__IActionsPlaybackPreference__

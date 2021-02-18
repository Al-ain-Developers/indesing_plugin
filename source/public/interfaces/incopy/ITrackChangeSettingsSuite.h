//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ITrackChangeSettingsSuite.h $
//  
//  Owner: Michele Goodwin
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
#ifndef __ITrackChangeSettingsSuite__
#define __ITrackChangeSettingsSuite__

#include "IPMUnknown.h"
#include "InCopySharedID.h"

/**
	ITrackChangeSettingsSuite

	This is a suite for getting a setting track changes settings.
*/

class ITrackChangeSettingsSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITRACKCHANGESETTINGSSUITE };

	/**	Can set the story's track changes state?
		@param none
		@return bool16 
	 */
	virtual bool16 CanSetStoryTrackingState() const = 0;

	/**	Get the story's current track change state.
		@param none
		@return bool16 
	 */
	virtual bool16  GetStoryTrackingState() const = 0;

	/**	Set the story or stories track change state.
		@param bool16
		@param UIDList* - uid list for multiple stories, nil means current story's only
		@return ErrorCode 
	 */
	virtual ErrorCode SetStoryTrackingState(bool16 bTrackingState, UIDList* cmdUIDList = nil) = 0;


#ifdef DEBUG

	/**	Can dump redline information?
		@param none
		@return bool16 
	 */
	virtual bool16 CanDumpRedline() const = 0;

	/**	Dump redline information via TRACE calls.
		@param none
		@return none 
	 */
	virtual ErrorCode DumpRedline() = 0;

	/**	Can dump delete text owned items?
		@param none
		@return bool16 
	 */
	virtual bool16 CanDumpDeleteOwnedItems() const = 0;

	/**	Dump delete text owned items via TRACE calls.
		@param none
		@return none 
	 */
	virtual ErrorCode DumpDeleteOwnedItems() = 0;

#endif // DEBUG
};

#endif
//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IShowTrackChangesPrefs.h $
//  
//  Owner: Michele Stutzman
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
#ifndef __IShowTrackChangesPrefs__
#define __IShowTrackChangesPrefs__

#include "IPMUnknown.h"
#include "InCopySharedID.h"

/** Interface to get and set whether track changes are showing or not.

	@see kWorkspaceBoss
*/
class IShowTrackChangesPrefs : public IPMUnknown
{
public:	
 	enum { kDefaultIID = IID_ISHOWTRACKCHANGESPREFS };
 
	/** Allows the user to determine whether track changes are shown.
		@param bShown - kTrue will show track changes, kFalse will not
	*/
	virtual void SetShowTrackChanges(const bool16 bShown) = 0;

	/** Indicates to the client whether track changes should be shown.
		@return kTrue means show track changes, kFalse means do not
	*/
	virtual const bool16 GetShowTrackChanges() = 0;
};

#endif // __IShowTrackChangesPrefs__

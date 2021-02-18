//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGuidePrefs.h $
//  
//  Owner: psorrick
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
#ifndef __IGuidePrefs__
#define __IGuidePrefs__

#include "IPMUnknown.h"
#include "SpreadID.h"

/** Interface relating to guide preferences (kGuideItemBoss).
	@see kDocWorkspaceBoss
	@see kWorkspaceBoss
	@see kGuideItemBoss
	@see kSetGuidePrefsCmdBoss 

*/
class IGuidePrefs : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IGUIDEPREFERENCES };
	////
	//// Guide Preferences:
	////	Affects margin, column and ruler guides
	////
	
	// Are guides drawn in front or back by default
	virtual void  SetGuidesInBack(const bool16 bBack) = 0;
	virtual const bool16 GetGuidesInBack() = 0;

	// Are guides shown or hidden by default
	virtual void  SetGuidesShown(const bool16 bShown) = 0;
	virtual const bool16 GetGuidesShown() = 0;

	// Are guides locked or unlocked by default
	virtual void  SetGuidesLocked(const bool16 bLocked) = 0;
	virtual const bool16 GetGuidesLocked() = 0;

	// Are guide have threhold
	virtual void   SetGuidesThreshold(const PMReal threshold) = 0;
	virtual PMReal GetGuidesThreshold() = 0;

	// Are guide have color
	virtual void  SetGuidesColor(const UID uiColorUID) = 0;
	virtual UIDRef GetGuidesColor() = 0;

	virtual const bool16 GetGuidesShown_DURING_CONVERSION_ONLY() = 0;
	virtual const bool16 GetGuidesLocked_DURING_CONVERSION_ONLY() = 0;
	virtual int32 GetGuidesColorIndex_DURING_CONVERSION_ONLY() = 0;
};

#endif

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IOverprintBlackPreference.h $
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
#ifndef __IOverprintBlackPreference__
#define __IOverprintBlackPreference__

#include "IPMUnknown.h"
#include "ColorSystemID.h"

/**
 Data interface for the overprint black preference. This is used to store the
 overprint black setting for the application and document preferences, as well
 as for the kSetOverprintBlackCmdBoss command.
 
 Note: The default value for this preference is kTrue.
 */
class IOverprintBlackPreference : public IPMUnknown
{
public:
	/**
	 Sets the overprint black preference.
	 
	 @param overprintVal		IN kTrue if black should overprint by default, else kFalse
	 */
	virtual void SetOverprint (bool8 overprintVal) = 0;
	
	/**
	 Returns the value of the overprint black preference.
	 
	 @return kTrue if black should overprint by default, else kFalse
	 */
	virtual bool8 GetOverprint() const = 0;
};


#endif

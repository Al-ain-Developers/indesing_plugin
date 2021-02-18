//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFontLockingData.h $
//  
//  Owner: nmccully
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
#ifndef __IFontLockingData__
#define __IFontLockingData__

#include "IPMUnknown.h"
#include "LinguisticID.h"

//---------------------------------------------------------------
// class IFontLockingData
//---------------------------------------------------------------

//	IFontLockingData::AllowFontLocking() enables/disables font change locking.
//	See ProcessResponderCmds in TextEditCommand.cpp and FontLockingData.cpp in Linguistics. 

/** This interface is added to some text edit command bosses. 
	@ingroup text_story
	@ingroup text_font
*/
class IFontLockingData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFONTLOCKINGDATA };
	
	enum FontLockLevel {
			kTurnOffFontLocking = 0,
			kSuppressFontLockingAlert,
			kAllowFontLockingNoOverride,		// will show alert without override option, but informing about prefs
			kAllowFontLockingWithOverride,		// will show alert with Cmd-Opt override option info
		 };

	virtual void	SetFontLockingLevel( FontLockLevel allowFontLocking ) = 0;
	virtual FontLockLevel	GetFontLockingLevel() const = 0;
	virtual bool16	AllowFontLocking() const = 0;
};

#endif

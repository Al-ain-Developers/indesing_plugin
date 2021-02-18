//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IRulerPrefs.h $
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
#ifndef __IRulerPrefs__
#define __IRulerPrefs__

#include "IPMUnknown.h"

class IRulerPrefs : public IPMUnknown
{
public:	
	////
	//// Ruler Preferences
	////
	
	// Are Rulers shown or hidden by default
	virtual void SetRulersShown(bool16 bShown) = 0;
	virtual bool16 GetRulersShown() = 0;

};

#endif

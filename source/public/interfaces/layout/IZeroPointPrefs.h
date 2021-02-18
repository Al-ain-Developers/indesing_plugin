//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IZeroPointPrefs.h $
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
#ifndef __IZeroPointPrefs__
#define __IZeroPointPrefs__

#include "IPMUnknown.h"
#include "PMPoint.h"
#include "SpreadID.h"

class IZeroPointPrefs : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IZEROPOINTPREFERENCES };

	////
	//// ZeroPoint Preferences
	////
	
	// ZeroPoint default location
	virtual void SetZeroPoint(PMPoint zeroPoint) = 0;
	virtual PMPoint GetZeroPoint() = 0;

	// Is ZeroPoint locked or unlocked by default
	virtual void SetZeroPointLock(bool16 bLock) = 0;
	virtual bool16 GetZeroPointLock() = 0;

};

#endif

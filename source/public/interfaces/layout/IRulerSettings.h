//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IRulerSettings.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IRulerSettings__
#define __IRulerSettings__

#include "IPMUnknown.h"
#include "PMPoint.h"

//---------------------------------------------------------------
// Interface IRulerSettings
//---------------------------------------------------------------

class IRulerSettings : public IPMUnknown
{
public:
	enum		Orientation { kHorizontal, kVertical };
	
	virtual	void			SetOrientation( Orientation nOrientation ) = 0;	
			// sets the ruler's orientation, default is kHorizontal.
	virtual	Orientation	GetOrientation() const = 0;	
			// returns the ruler's orientation, default is kHorizontal.
	virtual	ClassID		GetUnitOfMeasure() const = 0;	
			// returns XUnitOfMeasure on kHorizontal and YUnitOfMeasure on kVertical
	virtual	PMPoint		GetZeroPoint() const = 0;
			// returns the zero point
	virtual	void			SetZeroPoint( const PMPoint &rPoint ) = 0;
			// sets the zero point -- allowed only for the text ruler
	inline	bool16		IsHorizontal() const { return this->GetOrientation() == kHorizontal; }
			// returns whether the ruler is in horizontal mode or not (=vertical).
};

#endif

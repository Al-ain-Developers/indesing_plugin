//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IMeasurementType.h $
//  
//  Owner: lance bushore
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
#ifndef __IMeasurementType__
#define __IMeasurementType__

#include "IPMUnknown.h"
#include "K2Vector.h"
#include "widgetid.h"

class  IMeasurementType : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMEASUREMENTTYPE };

	virtual int32 GetUnitOfMeasureIndex() const = 0;
	
	// clients return false if they don't want their strings dynamically changed.
	virtual bool16 ShouldRebuildStringList() const = 0;
	
	typedef enum { kTextMeasureKind, kObjectMeasureKind, kTextMeasureOffsetKind } MeasureKind;
	virtual MeasureKind WhatKind() const = 0;

	virtual void GetMeasurementEntries(K2Vector<PMString*>	*measureEntries) const = 0;
	
	// set this value to true if you need the edit box to switch x and y measure based on
	// vertical text direction
	virtual void SetCheckVertical(bool16 checkVertical) = 0;
	virtual bool16 GetCheckVertical() const = 0;
};

#endif	//__IMeasurementType__

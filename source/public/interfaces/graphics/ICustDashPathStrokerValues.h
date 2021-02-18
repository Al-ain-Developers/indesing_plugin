//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ICustDashPathStrokerValues.h $
//  
//  Owner: Greg St. Pierre
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __ICustDashPathStrokerValues__
#define __ICustDashPathStrokerValues__

#include "InstStrokeFillID.h"

#include "IDashedAttributeValues.h"

class ICustomDashedPathStrokerValues : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICUSTOMDASHEDPATHSTROKERVALUES };

	/** 
	 @return number of values 
	 */
	virtual uint32 GetDashCount() const = 0;

	/** 
	 Retrieves a single entry from the dash array

	 @param index IN The index of the dash to return. Must be < GetDashCount()
	 @return nth dash 
	 */
	virtual PMReal GetNthDash(uint32 index) const = 0;

	/**
	 Sets the dash array

	 @param count IN The number of dashes in the array. May be zero to clear array
	 @param dashes IN The new dash array. May be nil if count is zero
	 */
	virtual void SetDashes(uint32 count, PMReal const *dashes) = 0;

	/**
	 Retrieves dash array in one call

	 @return dash array
	 */
	virtual PMReal const *GetDashes() const = 0;

	/**
	 Retrieves corner adjustment

	 @return current corner adjustment
	 @see IDashedAttributeValues
	 */
	virtual IDashedAttributeValues::CornerAdjustment GetCornerAdjustment() const = 0;

	/**
	 Sets corner adjustment

	 @param cornerAdjust IN New corner adjustment
	 */
	virtual void SetCornerAdjustment(IDashedAttributeValues::CornerAdjustment cornerAdjust) = 0;

	/**
	 Retrieves line cap

	 @return current line cap
	 */
	virtual int32 GetLineCap() const = 0;

	/**
	 Sets line cap

	 @param lineCap IN The new line cap
	 */
	virtual void SetLineCap(int32 lineCap) = 0;
};

#endif //!def __ICustDashPathStrokerValues__

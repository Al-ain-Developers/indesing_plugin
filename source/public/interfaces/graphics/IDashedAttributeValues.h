//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDashedAttributeValues.h $
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
#ifndef __IDashedAttributeValues__
#define __IDashedAttributeValues__

#include "IPMUnknown.h"
#include "InstStrokeFillID.h"

/**
 Interface for storing a dashed stroke's attributes, including the dash array, its
 phase, and any corner adjustment that should be done
 */
class IDashedAttributeValues : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDASHEDATTRIBUTEVALUES };

	/**
	 The various kinds of corner adjustment possible. Specifies whether to skip adjustment,
	 adjust by modifying dashes only, adjust by modifying gaps only, or adjust by modifying
	 both dashes and gaps
	 */
	enum CornerAdjustment { kNone, kAdjustDashes, kAdjustGaps, kAdjustBoth, kDefault = kAdjustBoth };

	/** 
	 Sets a value in the dash array
	 
	 The sequence of values represent alternating dash and gap numbers.  
	 The first value is dash0, the second value is gap0, the third value is dash1, etc.
	
	 Setting higher number dash/gaps will implicitly set lower number dash/gaps
	 if lower number dash/gaps have not been set yet.
	
	 For example, the client sets dash0 to 30 pt.  The client then sets
	 dash2 to 45 pt.  This results in gap0 set to 30, and dash1, gap1, and dash2
	 set to 45.
	 
	 @param n		The index of the entry to set
	 @param value	Its value
	 */
	virtual void SetValue(int32 n, const PMReal& value) = 0;
	
	/**
	 Gets a value in the dash array. If asking for a value greater than defined in 
	 NumValues it will return the same value as the last valid value
	 
	 @param n		The index of the entry to get
	 @return Its value
	 @see NumValues
	 */
	virtual PMReal GetValue(int32 n) const = 0;
	
	/**
	 @return the number of valid values. This returns 1 to 6
	 */
	virtual int32 NumValues() const = 0;
	
	/**
	 Removes all values from n to the number of dashes
	 
	 @param n		The index of the entry at which to start removal
	 */
	virtual void ClearFrom (int32 n) = 0;
	
	/**
	 Retrieves the entire dash array at once. fltArray must have NumValues elements
	 
	 @param fltArray	Array into which to store the dash array
	 */
	virtual void GetDashArray (float* fltArray) const = 0;
	
	/**
	 Compares two attribute values for equality
	 
	 @param iDashedVal	The attribute values to compare against this one
	 @return kTrue if the attributes are equal, else kFalse
	 */
	virtual bool16 IsEqual (const IDashedAttributeValues* iDashedVal) const = 0;
	
	/**
	 @return the dash's phase
	 */
	virtual PMReal	GetPhase (void) const = 0;
	
	/**
	 Sets the dash's phase
	 
	 @param newPhase	The new phase to use
	 */
	virtual void	SetPhase( PMReal newPhase ) = 0;
	
	/**
	 Copies dashed attributes from fromDash to this
	 
	 @param iDashedVal	The attributes to copy
	 */
	virtual void Copy (const IDashedAttributeValues* iDashedVal) = 0;

	/**
	 Sets the corner adjustment
	 
	 @param cornerAdjustment	The corner adjustment to use
	 */
	virtual void SetCornerAdjustment( CornerAdjustment cornerAdjustment ) = 0;

	/**
	 @return the corner adjustment
	 */
	virtual CornerAdjustment GetCornerAdjustment() const = 0;
};

#endif

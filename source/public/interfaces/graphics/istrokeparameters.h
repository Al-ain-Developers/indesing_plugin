//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/istrokeparameters.h $
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
//  Defines the interface by which a stroker determines its parameters, which
//  
//  for now include start and width pairs (each is a percentage of the stroke width)
//  
//========================================================================================

#pragma once
#ifndef __IStrokeParameters__
#define __IStrokeParameters__

#include "ScotchRulesID.h"

/**
 Stores parameters used by the scotch rules stroker. Each parameter consists of
 a pair of values: one that specifies the start position as a percentage of the
 stroke weight, and one that specifies the width (also as a percentage)
 */

class IStrokeParameters : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTROKEPARAMETERS };

	/**
	 Returns the number of parameters in this object

	 @return number of parameters
	 */
	virtual int32 GetParamCount() const = 0;
	
	/**
	 Sets the number of parameters in this object

	 @param count IN The number of parameters this object should hold
	 */
	virtual void SetParamCount(int32 count) = 0;
	
	/**
	 Returns the start value for the specified parameter

	 @param n IN The index of the desired parameter
	 @return The parameter's start value
	 */
	virtual PMReal GetNthParamStart(int32 n) const = 0;
	
	/**
	 Sets the start value for the specified parameter

	 @param n IN The index of the desired parameter
	 @param start IN The parameter's start value
	 */
	virtual void SetNthParamStart(int32 n, PMReal const &start) = 0;
	
	/**
	 Returns the width value for the specified parameter

	 @param n IN The index of the desired parameter
	 @return The parameter's width value
	 */
	virtual PMReal GetNthParamWidth(int32 n) const = 0;
	
	/**
	 Sets the width value for the specified parameter

	 @param n IN The index of the desired parameter
	 @param width IN The parameter's width value
	 */
	virtual void SetNthParamWidth(int32 n, PMReal const &width) = 0;

	/**
	 Tests for equivalence

	 @param other IN The object against which this object is to be tested
	 @return kTrue if two objects are equivalent, else kFalse
	 */
	virtual bool16 IsEqual(IStrokeParameters const *other) const = 0;

	/**
	 Canonicalizes parameters: normalizes start/width pairs,
	 sorts by start value, then collapses overlapping pairs
	 
	 @return The new parameter count
	 */
	virtual int32 Canonicalize() = 0;
};

#endif //!def __IStrokeParameters__

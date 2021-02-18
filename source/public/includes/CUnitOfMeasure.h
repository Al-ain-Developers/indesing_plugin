//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CUnitOfMeasure.h $
//  
//  Owner: Michael Burbidge
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
#ifndef 	__CUNITOFMEASURE__
#define __CUNITOFMEASURE__

#include "IUnitOfMeasure.h"
#include "HelperInterface.h"

//========================================================================================
// CLASS CUnitOfMeasure
//========================================================================================

#ifdef PUBLIC_BUILD
#pragma export on
#endif

class PUBLIC_DECL CUnitOfMeasure : public IUnitOfMeasure
{
// ----- Constructor/destructor
public:
	CUnitOfMeasure(IPMUnknown *boss);
	virtual ~CUnitOfMeasure();

	virtual PMReal GetSmallIncrement() const; // get a reasonable increment, 
	virtual PMReal GetLargeIncrement() const; // get a reasonable increment, 

// ----- Utility	
protected:
	
	// removes number from start of string, puts number value in numOut, sets boolean if number is negative,
	// returns kFalse if no number found
	virtual bool16 EvaluateRemoveLeadingNumber(PMString* strInOut,PMReal *numOut, bool16 *isNegOut = nil);
	
	virtual void FormatFractionalPortion(PMReal units, PMString *outStr, int32 nDecimalPlaces = 3, bool16 bStripTrailingZeros = kTrue) const;

// ----- Flags
public:
	virtual IUnitOfMeasure::UnitFlags GetUnitFlags() const;

DECLARE_HELPER_METHODS()
};

#pragma export off

#endif

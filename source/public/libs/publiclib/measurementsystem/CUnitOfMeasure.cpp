//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/measurementsystem/CUnitOfMeasure.cpp $
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

#include "VCPublicHeaders.h"

#include "CUnitOfMeasure.h"
#include "IWidgetUtils.h"

//========================================================================================
// CLASS CUnitOfMeasure
//========================================================================================
DEFINE_HELPER_METHODS(CUnitOfMeasure)

//----------------------------------------------------------------------------------------
// CUnitOfMeasure::CUnitOfMeasure
//----------------------------------------------------------------------------------------

CUnitOfMeasure::CUnitOfMeasure(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss)
{
}

//----------------------------------------------------------------------------------------
// CUnitOfMeasure::~CUnitOfMeasure
//----------------------------------------------------------------------------------------

CUnitOfMeasure::~CUnitOfMeasure()
{
}

//----------------------------------------------------------------------------------------
// CUnitOfMeasure::GetIncrement
//----------------------------------------------------------------------------------------

PMReal CUnitOfMeasure::GetSmallIncrement() const
{
	return PMReal(1.0);
}

PMReal CUnitOfMeasure::GetLargeIncrement() const
{
	return PMReal(10.0);
}

//----------------------------------------------------------------------------------------
// CUnitOfMeasure::EvaluateRemoveLeadingNumber
//----------------------------------------------------------------------------------------

bool16 CUnitOfMeasure::EvaluateRemoveLeadingNumber(PMString* strInOut,PMReal* numOut,bool16 *isNegOut)
{
	if(isNegOut)
		*isNegOut = kFalse;
		
	PMString::ConversionError parseErr;
	CharCounter lenNotNum ;
	strInOut->StripWhiteSpace();

	*numOut = strInOut->GetAsDouble(&parseErr,&lenNotNum);
	if(parseErr == PMString::kNoError)
	{
		//entire string was number.
		strInOut->Remove(0,kMaxInt32);
		if(isNegOut && *numOut < 0.0)
			*isNegOut = kTrue;
		return kTrue;
	}
	else if(parseErr == PMString::kNoNumber)
	{
		//string didn't start with number
		// this case will also be hit if the user typed something like -p5.

		PMString negSign("-");	// as I understand it, '-' is always the negative sign. no need to translate.
		if(strInOut->IsEqual(negSign,kTrue,kTrue))
		{
			if(isNegOut)
				*isNegOut = kTrue;

			strInOut->Remove(0,negSign.CharCount());// take off the negative sign.
			if (strInOut->CharCount())
				return kTrue;
		}
		return kFalse;
	}
	else if(parseErr == PMString::kNotJustNumber)
	{
		// string started with number, but also had some other stuff.
		PMString negSign("-");	// as I understand it, '-' is always the negative sign. no need to translate.
		if(isNegOut && strInOut->IsEqual(negSign,kTrue,kTrue))
			*isNegOut = kTrue;
		
		CharCounter lengthToChop = strInOut->CharCount() - lenNotNum;
		strInOut->Remove(0,lengthToChop);

		return kTrue;
	}
	ASSERT_FAIL("Unknown parsing error");
 	return kFalse;
	
}

//----------------------------------------------------------------------------------------
// CUnitOfMeasure::FormatFractionalPortion
//----------------------------------------------------------------------------------------

void CUnitOfMeasure::FormatFractionalPortion(PMReal units, PMString *outStr, int32 nDecimalPlaces, bool16 bStripTrailingZeros) const
{
	outStr->Clear();

	int32 wholeUnits = ::ToInt32(units);
	PMReal fractionalUnits = PMReal(units - wholeUnits);
	outStr->AsNumber(fractionalUnits, nDecimalPlaces, kTrue /* round */, bStripTrailingZeros /* eliminateTrailingZeros */);
	Utils<IWidgetUtils>()->FormatUserDecimal(outStr);
}

//----------------------------------------------------------------------------------------
// CUnitOfMeasure::GetUnitFlags
//----------------------------------------------------------------------------------------

IUnitOfMeasure::UnitFlags CUnitOfMeasure::GetUnitFlags() const
{
	return static_cast<IUnitOfMeasure::UnitFlags>(kUnitIsXMeasure | kUnitIsYMeasure);
}



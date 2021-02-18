//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/measurementsystem/Points.cpp $
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

// ----- Interfaces -----

#include "IUnitOfMeasureSettings.h"

// ----- Includes -----

#include "LocaleSetting.h"
#include "MeasurementDef.h"
#include "Points.h"
#include "RsrcSpec.h"
#include "RulerType.fh"

// ----- Utility files -----

#include "PreferenceUtils.h"
#include "StringUtils.h"

//========================================================================================
// CLASS Points
//========================================================================================

// BP 05/03/01: moved to  .../source/components/public/PublicImpl.cpp
// CREATE_PMINTERFACE(Points, kPointsImpl)

//----------------------------------------------------------------------------------------
// Points::Points
//----------------------------------------------------------------------------------------

Points::Points(IPMUnknown *boss) :
	CUnitOfMeasure(boss)
{
}

//----------------------------------------------------------------------------------------
// Points::~Points
//----------------------------------------------------------------------------------------

Points::~Points()
{
}

//----------------------------------------------------------------------------------------
// Points::UnitsToPoints
//----------------------------------------------------------------------------------------

PMReal Points::UnitsToPoints(const PMReal& units) const
{
	PMReal pointsPerInch = 72.0;
	InterfacePtr<IUnitOfMeasureSettings> iMeasurePrefs((IUnitOfMeasureSettings*)::QueryPreferences(IID_IUNITOFMEASURESETTINGS, GetExecutionContextSession()->GetActiveContext()));
	if (iMeasurePrefs)
		pointsPerInch = iMeasurePrefs->GetPointsPerInch();

	return units * (72.0 / pointsPerInch);
}

//----------------------------------------------------------------------------------------
// Points::PointsToUnits
//----------------------------------------------------------------------------------------

PMReal Points::PointsToUnits(const PMReal& points) const
{
	PMReal pointsPerInch = 72.0;
	InterfacePtr<IUnitOfMeasureSettings> iMeasurePrefs((IUnitOfMeasureSettings*)::QueryPreferences(IID_IUNITOFMEASURESETTINGS, GetExecutionContextSession()->GetActiveContext()));
	if (iMeasurePrefs)
		pointsPerInch = iMeasurePrefs->GetPointsPerInch();

	return points * (pointsPerInch / 72.0);
}

//----------------------------------------------------------------------------------------
// Points::GetName
//----------------------------------------------------------------------------------------

void Points::GetName(PMString * pName)
{
	// clear out the return string
	pName->clear();
	
	pName->SetKey("Points");
//	pName->Translate();
}

//----------------------------------------------------------------------------------------
// Points::Format
//----------------------------------------------------------------------------------------

void Points::Format(const PMReal& units, PMString& str, PMString *fractionalPortionString) const
{
	str.clear();
	str.SetKey("^1 pointAbbr", PMString::kTranslateDuringCall);
	
	PMString numString;
	numString.AsNumber(units,3,kTrue,kTrue);
		
	StringUtils::ReplaceStringParameters(&str, numString);
	
	// optionally, return the fractional portion in its own string
	if (fractionalPortionString) 
		FormatFractionalPortion(units, fractionalPortionString, 3, kTrue);
}

//----------------------------------------------------------------------------------------
// Points::Parse
// Points are of the form "[+|-]xxx.yyy[pt]"
//----------------------------------------------------------------------------------------

bool16 Points::Parse(const PMString& str, PMReal& points, const bool16 alwaysUseEnglishAbbreviations)
{
	PMString copyToParse(str);
	PMReal number;
	bool16 foundNumber = EvaluateRemoveLeadingNumber(&copyToParse,&number);
	
	// Check the measurement suffix (could be null, that's OK)
	PMString ptString, ptString2, pointString, pointsString;
	if (alwaysUseEnglishAbbreviations == kTrue)
	{
		ptString = "pt";
		ptString.SetTranslatable(kFalse);
	
		ptString2 = "pts";
		ptString2.SetTranslatable(kFalse);
	
		pointString = "Point";
		pointString.SetTranslatable(kFalse);
	
		pointsString = "Points";
		pointsString.SetTranslatable(kFalse);
	}
	else
	{
		ptString = "pointAbbr";
		ptString.Translate();
		ptString.StripWhiteSpace(PMString::kLeadingWhiteSpace);
		
		ptString2 = "pointAbbr2";
		ptString2.Translate();
		ptString2.StripWhiteSpace(PMString::kLeadingWhiteSpace);
		
		pointString = "Point";
		pointString.Translate();
		pointString.StripWhiteSpace(PMString::kLeadingWhiteSpace);
		
		pointsString = "Points";
		pointsString.Translate();
		pointsString.StripWhiteSpace(PMString::kLeadingWhiteSpace);

		#ifdef DEBUG
		// Since we are storing the English translation locally,
		// make sure it doesn't get out of sync with what's in the string table
		if (LocaleSetting::GetLocale().GetUserInterfaceId() == k_enUS)
		{
			PMString 	ptStringTable("pt", PMString::kUnknownEncoding),
						ptString2Table("pts", PMString::kUnknownEncoding),
						pointStringTable("Point", PMString::kUnknownEncoding),
						pointsStringTable("Points", PMString::kUnknownEncoding);
			
			if (ptStringTable != ptString || ptString2Table != ptString2 || pointStringTable != pointString || pointsStringTable != pointsString)
				ASSERT_FAIL("Points::Parse: A Point abbreviation doesn't match what's in the string table!");
		}
		#endif
	}
		
	if (foundNumber)
	{
		if(copyToParse.empty() || copyToParse.IsEqual(ptString, kFalse /*casesensitive*/) || copyToParse.IsEqual(ptString2, kFalse /*casesensitive*/) ||
		 		copyToParse.IsEqual(pointString, kFalse /*casesensitive*/) || copyToParse.IsEqual(pointsString, kFalse /*casesensitive*/))
		{
			// Must call UnitsToPoints even though this is Points measurement system because "Units" and "Points"
			// may not be the same number now that points per inch can be customized.
			points = UnitsToPoints(number);
			return kTrue;
		}
	}

	return kFalse;
}

//----------------------------------------------------------------------------------------
// Points::GetRulerSpecRsrcSpec
//----------------------------------------------------------------------------------------

RsrcSpec Points::GetRulerSpecRsrcSpec() const
{
	// BP 03/23/01: Cleaning up hard coded kApplicationPluginID, new GetPluginID() in PersistUtils.
	const PluginID thisPlugInID = ::GetPluginID( this );
	return RsrcSpec(thisPlugInID, kRulerRsrcType, kPointsRulerSpecId,kTrue);  
}

//----------------------------------------------------------------------------------------
// Points::GetUnitFlags
//----------------------------------------------------------------------------------------

IUnitOfMeasure::UnitFlags Points::GetUnitFlags() const
{
	return static_cast<IUnitOfMeasure::UnitFlags>(CUnitOfMeasure::GetUnitFlags() | kUnitIsLineMeasure | kUnitIsTextMeasure | kUnitIsTextSizeMeasure | kUnitIsPrintMeasure);
}

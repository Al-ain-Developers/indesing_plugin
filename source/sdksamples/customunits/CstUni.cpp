//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customunits/CstUni.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

//interfaces
#include "IEnvironment.h"
#include "ISession.h"
#include "IUnitOfMeasure.h"

#include "CUnitOfMeasure.h"
#include "LocaleSetting.h"
#include "PMString.h"
#include "RsrcSpec.h"
#include "RulerType.fh"
#include "StringUtils.h"

#include "CstUniID.h"
#include "CstUniDef.h"
#include "CstUniScriptingDefs.h"

#define CSTUNICONVERSIONFACTOR		20.0


/** CstUni
	Methods provide for the conversion between the points and the custom units, formatting
	and tokenization, the ruler resource for the custom units.
	  
	Implements IUnitOfMeasure based on the partial implementation
	of CUnitOfMeasure. 
	
	@ingroup customunits
*/
class CstUni : public CUnitOfMeasure
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		CstUni(IPMUnknown* boss) : CUnitOfMeasure(boss) {}

		/** 
			Destructor.
		*/
		virtual ~CstUni() {}
		
		/**
			Convert from custom units to points. For the purpose of this example,
			assuming that one custom unit is equal to 20 points.

			@param units the custom units.
			@return the points.
		*/
		virtual PMReal UnitsToPoints(const PMReal& units) const;

		/**
			Convert from points to custom units. For the purpose of this example,
			assuming that one custom unit is equal to 20 points.

			@param points the points.
			@return the custom units.
		*/
		virtual PMReal PointsToUnits(const PMReal& points) const;

		/**
			Get the small increment for the ruler of this custom units.
		*/
		virtual PMReal GetSmallIncrement() const; 

		/** 
			Get the large increment for the ruler of this custom units.
		*/
		virtual PMReal GetLargeIncrement() const; 

		/**
			Get the name of the custom units.
		*/
		virtual void GetName(PMString* pName);

		/**
			Get the format for the custom units.
		*/
		virtual void Format(const PMReal& units, PMString& str, PMString* fractionalPortionString) const;

		/** 
			Parse the string and convert it to the points.
		*/
		virtual bool16 Parse(const PMString& str, PMReal& points, const bool16 alwaysUseEnglishAbbreviations);
		
		/**
			Get the ruler resource spec for the custom units.
		*/
		virtual RsrcSpec GetRulerSpecRsrcSpec() const;

		/**
			Get the unit flag which this unit will be used in UI. 
			@see IUnitOfMeasure for definition of each flag.
		*/
		virtual IUnitOfMeasure::UnitFlags GetUnitFlags() const;

		/** Returns the ScriptID associated with this unit of measure in the given scripting DOM */
		virtual ScriptID GetScriptID( const ScriptInfo::RequestContext& ) const { return en_MeasCstUni ; }

	private:
		/**
			replaces user defined decimal string with '.'.
		*/
		void	StripUserDecimal(PMString* string) const;

		/** 
			replaces '.' with user defined decimal string.
		*/
		void	FormatUserDecimal(PMString* string) const;			
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(CstUni, kCstUniImpl)


/* UnitsToPoints
*/
PMReal CstUni::UnitsToPoints(const PMReal& units) const
{
	// For the purpose of this example, assuming that one custom unit 
	// is equal to 20 points.
	return units * CSTUNICONVERSIONFACTOR;
}

/* PointsToUnits
*/
PMReal CstUni::PointsToUnits(const PMReal& points) const
{
	return points / CSTUNICONVERSIONFACTOR;
}

/* GetName
*/
void CstUni::GetName(PMString* pName)
{
	ASSERT(pName);
	// clear out the return string
	pName->Clear();
	pName->SetKey(kCstUnisString); 
}

/* Format
*/
void CstUni::Format(const PMReal& units, PMString& str, PMString* fractionalPortionString) const
{
	str.Clear();
	str.SetKey(kCstUniAbbrPlaceHolderString); // "^1customAbbr^2"
	str.Translate();
	
	int32 customUnits = (int32)::ToDouble(units);
	PMReal points = (units - customUnits) * CSTUNICONVERSIONFACTOR;
	points = abs(points);
	
	PMString pointString;
	pointString.AsNumber(points, 3, /* digitsPrecision */ kTrue, /* round */ kTrue /* eliminateTrailingZeros */);

	// Here we have to see if we rounded to 20 for display, hence we are checking
	// the string, not the value. This is so we don't display 2cu20, when the value 
	// is 2cu19.99
	if (pointString == PMString("20"))
	{
		pointString.AsNumber(0, 3, kTrue, kTrue);
		if (units < 0)
			customUnits--;
		else
			customUnits++;
	}
	FormatUserDecimal(&pointString); // turn '.' into ',' if appropriate

	PMString cuString;
	cuString.AsNumber(customUnits);
		
	StringUtils::ReplaceStringParameters(&str, cuString, pointString);

	// Need this check to catch numbers like -0cu6 between -1 and 0 customunit.
	if ((units < 0) && (customUnits == 0))
	{
		PMString negSign("-");	// '-' is always the negative sign. No need to translate.
		str.Insert(negSign);
	}	

	if (fractionalPortionString)
	    fractionalPortionString->SetString(pointString);
}

/* Parse
*/
bool16 CstUni::Parse(const PMString& str, PMReal& points, const bool16 alwaysUseEnglishAbbreviations)
{
	PMString copyToParse(str);
	PMReal realLeft;
	bool16 isNegNum;
	bool16 foundNumber = CUnitOfMeasure::EvaluateRemoveLeadingNumber(&copyToParse, &realLeft, &isNegNum);
	
	// Check the measurement suffix 
	PMString cuString, customUnitString, customUnitsString;
	if (alwaysUseEnglishAbbreviations == kTrue)
	{
		cuString = "cu"; // "customAbbr"
		cuString.SetTranslatable(kFalse);
	
		customUnitString = "CustomUnit[US]"; // "CustomUnit"
		customUnitString.SetTranslatable(kFalse);
	
		customUnitsString = "CustomUnits[US]"; // "CstUni"
		customUnitsString.SetTranslatable(kFalse);
	}
	else
	{	
		cuString = kCstUniAbbrString; // "customAbbr"
		cuString.Translate();
		cuString.StripWhiteSpace(PMString::kLeadingWhiteSpace);
	
		customUnitString = kCstUniString; // "CustomUnit"
		customUnitString.Translate();
		customUnitString.StripWhiteSpace(PMString::kLeadingWhiteSpace);
	
		customUnitsString = kCstUnisString; // "CstUni"
		customUnitsString.Translate();
		customUnitsString.StripWhiteSpace(PMString::kLeadingWhiteSpace);

		#ifdef DEBUG
		// Since we are storing the English translation locally,
		// make sure it doesn't get out of sync with what's in the string table
		if (LocaleSetting::GetLocale().GetUserInterfaceId() == k_enUS)
		{
			PMString 	cuStringTable("cu", PMString::kEncodingASCII),
						customUnitStringTable("CustomUnit[US]", PMString::kEncodingASCII),
						customUnitsStringTable("CustomUnits[US]", PMString::kEncodingASCII);
			
			if (cuStringTable != cuString || customUnitStringTable != customUnitString || customUnitsStringTable != customUnitsString)
				ASSERT_FAIL("CstUni::Parse: A CustomUnit[US] abbreviation doesn't match what's in the string table!");
		}
		#endif
	}
	
	if (foundNumber && (copyToParse.empty() || copyToParse.Compare(kFalse, cuString) == 0 ||
		 copyToParse.Compare(kFalse, customUnitString) == 0 || copyToParse.Compare(kFalse, customUnitsString) == 0))
	{	
		points = UnitsToPoints(realLeft);
		return kTrue;
	}
	else if(!copyToParse.empty()) 
	{

		PMString cuCompare(copyToParse);
		if (cuCompare.CharCount() > cuString.CharCount())
			cuCompare.Remove(cuString.CharCount(), kMaxInt32);

		PMString customUnitCompare(copyToParse);
		if (customUnitCompare.CharCount() > customUnitString.CharCount())
			customUnitCompare.Remove(customUnitString.CharCount(), kMaxInt32);

		PMString customUnitsCompare(copyToParse);
		if (customUnitsCompare.CharCount() > customUnitsString.CharCount())
			customUnitsCompare.Remove(customUnitsString.CharCount(), kMaxInt32);
		
		if(customUnitsCompare.Compare(kFalse, customUnitsString) == 0)
			copyToParse.Remove(0, customUnitsString.CharCount()); // strip off the CstUni string.
		else if(customUnitCompare.Compare(kFalse, customUnitString) == 0) 
			copyToParse.Remove(0, customUnitString.CharCount()); // strip off the CustomUnit string.
		else if(cuCompare.Compare(kFalse, cuString) == 0)
			copyToParse.Remove(0, cuString.CharCount()); // strip off the cu string.
		else
			return kFalse;

		PMString::ConversionError convertErr = PMString::kNoError;
		StripUserDecimal(&copyToParse); // turn ',' into '.' if appropriate.
		PMReal realRight(copyToParse.GetAsDouble(&convertErr));
		if(isNegNum)
			realRight *= -1.0;
		points = UnitsToPoints(realLeft + realRight / CSTUNICONVERSIONFACTOR);

		return (convertErr == PMString::kNoError);
	}
	return kFalse;
}

/* GetRulerSpecRsrcSpec
*/
RsrcSpec CstUni::GetRulerSpecRsrcSpec() const
{
	return RsrcSpec(kCstUniPluginID, kRulerRsrcType, kCstUniRulerSpecId, kTrue);
}

/* GetSmallIncrement
*/
PMReal CstUni::GetSmallIncrement() const 
{
	return PMReal(1.0 / 20.0);// 1/20 custom unit, or 1 point
}

/* GetLargeIncrement
*/
PMReal CstUni::GetLargeIncrement() const
{
	return PMReal(1.0); // 1 custom unit
}

/* GetUnitFlags
*/
IUnitOfMeasure::UnitFlags CstUni::GetUnitFlags() const
{
	// suppose we would allow this custom unit used in the print dialog ...
	return static_cast<IUnitOfMeasure::UnitFlags>(CUnitOfMeasure::GetUnitFlags() | kUnitIsPrintMeasure);
}

/* FormatUserDecimal
*/
void CstUni::FormatUserDecimal(PMString* string) const
{
	InterfacePtr<IEnvironment> env(GetExecutionContextSession(),UseDefaultIID());
	if (env == nil)
	{
		ASSERT_FAIL("CstUni::FormatUserDecimal: The environment interface for this session is nil.");
		return;
	}

	PMString userDecString = env->GetCurrentDecimalPt();
	int32 decPos = string->IndexOfCharacter('.');
	if(decPos >= 0)
	{
		// the decimal character('.') appears in the string.
		// if all the characters before it are legal numbers, replace it.
		PMString testString(*string);
		testString.Remove(decPos,kMaxInt32);
		PMString::ConversionError err = PMString::kNoError;
		testString.GetAsDouble(&err);
		if(err == PMString::kNoError)
		{
			string->Remove(decPos,1);
			string->Insert(userDecString, decPos);
		}
	}
}

/* StripUserDecimal
*/
void CstUni::StripUserDecimal(PMString* string) const
{
	InterfacePtr<IEnvironment> env(GetExecutionContextSession(),UseDefaultIID());
	if (env == nil)
	{
		ASSERT_FAIL("CstUni::StripUserDecimal: The environment interface for this session is nil.");
		return;
	}

	PMString userDecString = env->GetCurrentDecimalPt();
	int32 decPos = string->IndexOfString(userDecString);

	// Since the user decimal character typically is either '.' or ',', 
	// so we do the extra check for ',' if current decimal setting is not '.'
	if (decPos < 0)
	{
		userDecString = "localizedDecimal";
		userDecString.Translate();
		decPos = string->IndexOfString(userDecString);
	}

	if(decPos >= 0)
	{
		// the user decimal character(typically either '.' or ',') appears in the string.
		// if all the characters before it are legal numbers, replace it.
		PMString testString(*string);
		testString.Remove(decPos, kMaxInt32);
		PMString::ConversionError err = PMString::kNoError;
		testString.GetAsDouble(&err);
		if((err == PMString::kNoError) || (testString.empty()))
		{
			string->Remove(decPos, userDecString.CharCount());
			string->Insert('.', decPos);
		}
	}
}



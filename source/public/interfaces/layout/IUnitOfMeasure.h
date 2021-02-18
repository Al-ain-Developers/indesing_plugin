//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IUnitOfMeasure.h $
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
#ifndef __IUNITOFMEASURE__
#define __IUNITOFMEASURE__

#include "IPMUnknown.h"
#include "MeasurementSystemID.h"
#include "RequestContext.h"

class PMString;
class RsrcSpec;

/** IUnitOfMeasure represents a unit of measurement in the measurement system. @see IMeasurementSystem */
class IUnitOfMeasure : public IPMUnknown
{
public:
	/** Return the name of this unit */
	virtual void GetName(PMString* pName) = 0;

	/** Convert a value in this unit to points */
	virtual PMReal UnitsToPoints(const PMReal& units) const = 0;
	/** Convert a value in points to this unit */
	virtual PMReal PointsToUnits(const PMReal& points) const = 0;

	/** Format a value in this unit as a string */
	virtual void Format(const PMReal& units, PMString& str, PMString *fractionalPortionString = nil) const = 0;
	/** Parse a string like "1 in" into points.
		@parma str IN, the string to be parsed
		@param points OUT, the resulting points
		@parma alwaysUseEnglishAbbreviations IN, whether to always use the English abbreviations for units such as "in". If false then the translation of the string in the current locale is used.
		@return bool16, Whether the parsing succeeded.
	*/
	virtual bool16 Parse(const PMString& str, PMReal& points, const bool16 alwaysUseEnglishAbbreviations = kFalse) = 0;

	/** Get a reasonable small increment */
	virtual PMReal GetSmallIncrement() const = 0;
	/** Get a reasonable large increment */
	virtual PMReal GetLargeIncrement() const = 0;

	/** Get the ruler spec for this unit */
	virtual RsrcSpec GetRulerSpecRsrcSpec() const = 0;

	/** Unit Type Flags */
	typedef enum {
		/** use this unit in X measurements on spread */
		kUnitIsXMeasure				= 0x0001,
		/** use this unit in Y measurements on spread */
		kUnitIsYMeasure				= 0x0002,
		/** use this unit in typographic distance measurements (excludes text size) */
		kUnitIsTextMeasure			= 0x0004,
		/** use this unit in text size measurements */
		kUnitIsTextSizeMeasure		= 0x0008,
		/** use this unit in print dialog measurements */
		kUnitIsPrintMeasure			= 0x0010,
		/** use this unit in line dialog measurements */
		kUnitIsLineMeasure			= 0x0020
	} UnitFlags;
	/** Get the unit flags for this unit */
	virtual UnitFlags GetUnitFlags() const = 0;

	/** Returns the ScriptID associated with this unit of measure in the given scripting DOM */
	virtual ScriptID GetScriptID( const ScriptInfo::RequestContext& context ) const = 0;
};

#endif

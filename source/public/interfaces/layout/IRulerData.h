//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IRulerData.h $
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
#ifndef __IRULERDATA__
#define __IRULERDATA__

#include "PMTypes.h"
#include "PMPoint.h"
#include "RulerID.h"

//========================================================================================
// Forward declaration
//========================================================================================

class IPMFont;
class IControlView;

//========================================================================================
// CLASS RulerTickSpec
//========================================================================================

struct RulerTickSpec
{
	typedef			base_type data_type;
	PMReal			fStartingZoomFactor;
	PMReal			fMajorDivisionLength;
	K2Vector<int16>	fSubDivisionsCount;
	K2Vector<int16>	fTickHeightPercentages;
};

//========================================================================================
// CLASS IRulerData
//========================================================================================

class IRulerData : public IPMUnknown
{
// ----- Constructors/desctructors
public:
	enum { kDefaultIID = IID_IRULERDATA };

	virtual void	Init(const ClassID& unitOfMeasureID) = 0;
		// Initialize the data that describes the appearance of a ruler. Get the appearance
		// data from the unit of measure boss.

// ----- Accessors
public:
	virtual IPMFont*		QueryFont() const = 0;
	virtual PMReal			GetFontPtSize() const = 0;
	virtual ClassID			GetUnitOfMeasure() const = 0;

	virtual PMReal			GetMajorDivisionLength(const PMReal &curZoomFactor) const = 0;

	virtual int16			GetFractionFlag() const = 0; 
	virtual int16			GetDecimalFlag() const = 0;
	virtual int32			GetNumberOfTickSpecs() const = 0;
	virtual const RulerTickSpec	&GetTickSpec(const PMReal& curZoomFactor) const = 0;

	// inVal is in pasteboard coords 
	// The result is in pasteboard coords
	// returns kTrue if hit a tick mark, else false
	virtual bool16			GetHorzAdjustedValue (PMReal* inOutVal, const PMReal& xScaleFactor, const PMReal& xTranslation) const = 0;
	virtual bool16			GetVertAdjustedValue (PMReal* inOutVal, const PMReal& yScaleFactor, const PMReal& yTranslation) const = 0;

	virtual PMReal			GetNearestTick(const PMReal &position, const PMReal &zoomFactor, bool16 isHorzRuler, PMReal& lowerBound, PMReal& upperBound) = 0;
};

#endif

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IMeasureUnitsCmdData.h $
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
//  
//  Data interface for measure unit command.
//  includes : 	Set the horizontal and vertical unit of measure, plus other measurement related settings.
//  
//========================================================================================

#pragma once
#ifndef __IMeasureUnitsCmdData__
#define __IMeasureUnitsCmdData__

#include "IPMUnknown.h"
#include "UIDRef.h" 

class IDataBase;

/**	IMeasureUnitsCmdData is the data interface for the measure units command.
*/
class IMeasureUnitsCmdData : public IPMUnknown
{
public:
	/** Set the measure units command, command data.
		@param doc which document to affect
		@param hMeasureUnits horizontal units to use for measurement system. kInvalidClass to leave unchanged
		@param vMeasureUnits vertical units to use for measurement system. kInvalidClass to leave unchanged
		@param textMeasureUnits text distance units to use for measurement system. kInvalidClass to leave unchanged, UNUSED
		@param textSizeMeasureUnits text size units to use for measurement system. kInvalidClass to leave unchanged
		@param printMeasureUnits printer dialog units to use for measurement system. kInvalidClass to leave unchanged, UNUSED
		@param lineMeasureUnits line units to use for measurement system. kInvalidClass to leave unchanged
		@param customHPoints custom points for horz ruler. -1 to leave unchanged.
		@param customVPoints custom points for vert ruler. -1 to leave unchanged.
		@param keyNudgeInc keyboard nudge increment. -1 to leave unchanged.
		@param pointsPerInch Points per inch value. Typically 72.0. Use -1 to leave unchanged. Only used for points and picas measurement systems
	*/
	virtual void Set(	const	UIDRef&	doc,
						const	ClassID	hMeasureUnits,
						const	ClassID	vMeasureUnits,
						const	ClassID	textMeasureUnits = kInvalidClass,
						const	ClassID	textSizeMeasureUnits = kInvalidClass,
						const	ClassID	printMeasureUnits = kInvalidClass,
						const	ClassID	lineMeasureUnits = kInvalidClass,
						const   PMReal customHPoints = -1,
						const   PMReal customVPoints = -1,
						const	PMReal keyNudgeInc = -1,
						const	PMReal pointsPerInch = -1) = 0;

	/** Returns the document to affect.
	*/
	virtual const UIDRef& GetDocument() const = 0;

	/** Returns the horizontal units.
	*/
	virtual const ClassID GetHMeasureUnits() const = 0;

	/** Returns the vertical units.
	*/
	virtual const ClassID GetVMeasureUnits() const = 0;

	/** Returns the text distance units.
	*/
	virtual const ClassID GetTextMeasureUnits() const = 0;

	/** Returns the text size units.
	*/
	virtual const ClassID GetTextSizeMeasureUnits() const = 0;

	/** Returns the printer dialog units.
	*/
	virtual const ClassID GetPrintMeasureUnits() const = 0;

	/** Returns the line units.
	*/
	virtual const ClassID GetLineMeasureUnits() const = 0;

	/** Returns the custom points for horizontal ruler.
	*/
	virtual const PMReal   GetHorzCustomPoints() const = 0;

	/** Returns the custom points for vertical ruler.
	*/
	virtual const PMReal   GetVertCustomPoints() const = 0;

	/** Returns the keyboard nudge increment.
	*/
	virtual const PMReal   GetKeyNudgeInc() const = 0;

	/** Returns the Points per inch value.
	*/
	virtual const PMReal   GetPointsPerInch() const = 0;
};


#endif // __IMeasureUnitsCmdData__

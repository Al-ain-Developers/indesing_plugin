//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IStepAndRepeatSuite.h $
//  
//  Owner: Ryan Gano
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
#ifndef __ISTEPANDREPEATSUITE__
#define __ISTEPANDREPEATSUITE__

// Interface Includes:
#include "IPMUnknown.h"
#include "ShuksanID.h"

// Implementation includes:
#include "PMPoint.h"

// Forward declarations
class IControlView;

/** Defines the interface for a step and repeat suite to be used in the new selection architecture
	@ingroup layout_suite
*/
class IStepAndRepeatSuite : public IPMUnknown
{
public:
    enum { kDefaultIID = IID_ISTEPANDREPEATSUITE };

// ----- Abilities
	/**	Can this selection be step and repeated
		@param none
		@return bool16
	 */
	virtual bool16	CanStepAndRepeat() const = 0;

	/**	Can this selection be step and repeated vertically
		@param none
		@return bool16
	 */
	virtual bool16	CanStepAndRepeatVertical() const = 0; 

	/**	Can this selection be step and repeated horizontally
		@param none
		@return bool16
	 */
	virtual bool16	CanStepAndRepeatHorizontal() const = 0;

	/**	Can values be passed in to Step and Repeat (Text for instance cannot receive values)
		@param offset - The values client would like to use
		@param repeatCountOrRowCount - The number of times client would like to repeat the step and repeat. When columnCount is not -1, this is the rowCount.
		@param columnCount - The number of times client would like to repeat columns when creating a grid. Use a value of -1 when not creating a grid.
		@return bool16
	 */
	virtual bool16	AreValuesAllowed(const PBPMPoint& offset, int32 repeatCountOrRowCount, int32 columnCount) const = 0;

// ----- Manipulators

	/**	Perform the Step and Repeat action
		@param offset - Offset to use
		@param repeatCountOrRowCount - Number of times to repeat, or number of rows to create.
		@param columnCount - Number of columns to create, -1 when just doing a standard "repeat" Step and Repeat.
		@param layerRef - This is the layer to step and repeat onto
		@return ErrorCode - kSuccess or kFailure
	 */
	virtual ErrorCode StepAndRepeat(const PBPMPoint& offset, int32 repeatCountOrRowCount, int32 columnCount, const UIDRef& layerRef) = 0;

	/**	Finalize the selection after the Step and Repeat action. e.g. Select just the newly created items.
		@param allStepAndRepeatItems - all the items that are stepped and repeated. This includes the original items and the newly created ones.
		@return ErrorCode - kSuccess or kFailure
	*/
	virtual ErrorCode FinalizeSelection(const UIDList& allStepAndRepeatItems) = 0;
};

#endif		// __ISTEPANDREPEATSUITE__
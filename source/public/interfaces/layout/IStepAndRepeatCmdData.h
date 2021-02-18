//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IStepAndRepeatCmdData.h $
//  
//  Owner: Joe Shankar
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
//  Data interface for step and repeat command.
//  
//========================================================================================

#pragma once
#ifndef __IStepAndRepeatCmdData__
#define __IStepAndRepeatCmdData__

#include "IPMUnknown.h"
#include "PMPoint.h"
#include "PMReal.h"

/** Data interface for the "Step and Repeat" command.
*/
class IStepAndRepeatCmdData : public IPMUnknown
{
public:
	/** Set the command data

		@param repeatCountOrRowCount IN how many times to repeat the command. When columnCount is not -1, this value is a rowCount
		@param columnCount IN how many times to repeat the command. -1 when not creating a grid.
		@param horizontalOffset IN horizonal spacing used to offset each new instance
		@param verticalOffset IN vertical spacing used to offset each new instance
		@param parentLayerRef IN destination's parent layer
		@param preserveLayers IN should layers be preserved
	*/
	virtual void Set(const int32	repeatCountOrRowCount,
					 const int32	columnCount,
					 const PMReal&  horizontalOffset,
					 const PMReal&  verticalOffset,
					 const UIDRef&  parentLayerRef,
					 bool16	        preserveLayers
					 ) = 0;

	/** Get the command data

		@param repeatCountOrRowCount IN how many times to repeat the command. When columnCount is -1, this is a standard repeatCount. When columnCount is not -1, see below.
		@param columnCount IN how many times to repeat the command for columns. -1 if not creating a grid.
		@param horizontalOffset IN horizonal spacing used to offset each new instance
		@param verticalOffset IN vertical spacing used to offset each new instance
		@param parentLayerRef IN destination's parent layer
		@param preserveLayers IN should layers be preserved
	*/
	virtual void Get(int32&	 repeatCountOrRowCount,
					 int32&	 columnCount,
					 PMReal& horizontalOffset,
					 PMReal& verticalOffset,
					 UIDRef& parentLayerRef,
					 bool16& preserveLayers
					 ) = 0;
};

#endif // __IStepAndRepeatCmdData__

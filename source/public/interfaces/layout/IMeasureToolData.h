//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IMeasureToolData.h $
//  
//  Owner: Yeming Liu
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
#ifndef __IMEASURETOOLDATA__
#define __IMEASURETOOLDATA__

#include "IPMUnknown.h"

#include "MeasureToolID.h"

/**
   This is a data interface to allow clients to access information about current measure line.
   There is one measure line per layout view.
*/
class IMeasureToolData : public IPMUnknown
{
	public:	
		enum { kDefaultIID = IID_IMEASURETOOLDATA};

		/**
		   Set the start point of current measure line.

           @param startPoint The new start point of measure line.
		*/
		virtual void SetStartPoint(const PMPoint& startPoint) = 0;

		/**
		   Get the start point of current measure line.

           @return PMPoint of start point.
		*/
		virtual const PMPoint& GetStartPoint() = 0;

		/**
		   Set the end point of current measure line.

           @param endPoint The new end point of measure line.
		*/
		virtual void SetEndPoint(const PMPoint& endPoint) = 0;

		/**
		   Get the end point of current measure line.

           @return PMPoint of end point.
		*/
		virtual const PMPoint& GetEndPoint() = 0;

		/**
		   Set the middle point of the measure line. This is only when measure line is a protractor.

		   @param middlePoint The new middle point of the protractor.
		*/
		virtual void  SetMiddlePoint(const PMPoint& middlePoint) = 0;

		/**
		   Get the middle point of current measure line. This is only when measure line is a protractor.

           @return PMPoint of middle point.
		*/
		virtual const PMPoint& GetMiddlePoint() = 0;

		// --- Get/Set protractor flag.

		/**
		   Set kTrue if current measure line is protractor; otherwise set kFalse.

           @param bool16 kTrue(is a protractor) or kFalse(not a protractor).
		*/
		virtual void   SetProtractorFlag(const bool16& isProtractor) = 0;

		/**
		   Determine that if current measure line is protractor or not.

           @return bool16 kTrue if it is a protractor; otherwise return kFalse.
		*/
		virtual bool16 GetProtractorFlag() = 0;

		/**
		   Determine if there is a measure line in current workspace.

           @return bool16 kTrue if there is a measure line; otherwise return kFalse.
		*/
		virtual bool16 HasMeasureLine() = 0;

		// --- Get/Set visibility of the measure line.
		/**
		   Set the visible flag if current measure line is visible. Meausre line will be hidden 
		   if current active tool is not measure tool.

		   @param bool16 kTrue(if visible) or kFalse(if not visible)
		*/
		virtual void   SetVisibility(const bool16& isVisible) = 0;

		/**
		   Get the visible flag if current measure line. 

           @return bool16 kTrue if measure line is visible, otherwise return kFalse.
		*/
		virtual bool16 GetVisibility() = 0;
};

#endif // __IMEASURETOOLDATA__

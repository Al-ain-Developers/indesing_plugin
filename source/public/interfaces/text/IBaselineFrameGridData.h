//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IBaselineFrameGridData.h $
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

#ifndef __IBaselineFrameGridData__
#define __IBaselineFrameGridData__

#include "IPMUnknown.h"
#include "TextID.h"

class IBaselineFrameGridData : public IPMUnknown
{
	public:	
		enum { kDefaultIID = IID_IBASELINEFRAMEGRIDDATA };

		typedef enum { kTopOfPage, kTopOfMargin, kTopOfFrame, kTopOfInset } RelativeOption;

		/**
			Set the flag that determining if we use custom baseline grid or not.
			@param flag IN either set as kTrue or kFalse.
		*/
		virtual void SetUseCustomBaselineGridFlag(const bool16& flag) = 0;

		/**
			Get the flag that determining if we use custom baseline grid or not.
			@return bool16 kTrue indicates that text frame has a grid of its own, otherwise kFalse.
		*/
		virtual bool16 GetUseCustomBaselineGridFlag() const = 0;

		/**
			Set the distance between the starting point and its relative(e.g., top of page). Default is 0.
			@param startOffset IN the distance.
		*/
		virtual void SetStartingOffset(const PMReal& startingOffset) = 0;

		/**
			Get the distance between the starting point and its relative(e.g., top of page).
			@return PMReal the distance.
		*/
		virtual PMReal GetStartingOffset() const = 0;

		/**
			Set the relative type defined as above such as kTopOfPage(top of page). Default is kTopOfInset.
			@param relativeType IN the type of relative to.
		*/
		virtual void SetRelativeOption(IBaselineFrameGridData::RelativeOption& relativeOption) = 0;

		/**
			Get the relative type defined as above such as kTopOfPage(top of page).
			@return RelativeType the type of relative to.
		*/
		virtual IBaselineFrameGridData::RelativeOption GetRelativeOption() const = 0;

		/**
			Set the distance between grid lines. Default is 12pts(0.1667 in).
			@param increment IN the distance.
		*/
		virtual void SetIncrement(const PMReal& increment) = 0;

		/**
			Get the distance between grid lines.
			@return PMReal the distance.
		*/
		virtual PMReal GetIncrement() const = 0;

		/**
			Get the show/hide flag of baseline frame grid from document preference.
			@return bool16 kTrue indicates show the baseline frame grid, otherwise kFalse.
		*/
		virtual bool16 GetBaselineFrameGridShown() const = 0;

		/**
			Get the color of baseline frame grid from document preference.
			@return UIDRef the swatch to draw the baseline frame grid.
		*/
		virtual UIDRef GetBaselineFrameGridColor() = 0;

		/**
			Set the drawing color for baseline frame grid. 
			@param colorUID IN the new color.
		*/
		virtual void SetBaselineFrameGridColor(const UID& colorUID) = 0;

		/**
			Get the view limit of baseline frame grid from document preference. 
			Under this view threshold, baseline frame grid will be invisible.
			@return PMReal the view threshold.
		*/
		virtual PMReal GetBaselineFrameGridViewThreshold() const = 0;

		/**
			Turns on the bit to let the command know to set this value in the IBaselineFrameGridData
			@param val IN what baselinegrid value we are setting
		*/
		enum SetValueID{ kSetNone = 0,
					   kSetUseBaselineGrid = 1,
					   kSetStartingOffset = 2, 
					   kSetRelativeOption = 4, 
					   kSetIncrement = 8, 
					   kSetBaselineFrameGridColor = 16 };
		
		virtual void SetValue(const IBaselineFrameGridData::SetValueID& val) = 0;
		/**
			Clears the flags currently set
		*/
		virtual void ClearSetValues() = 0;
		
		/**
			Is this value set?  Should the command apply it
		*/
		virtual bool16 ApplyValue(const IBaselineFrameGridData::SetValueID& val) const = 0;

};

#endif

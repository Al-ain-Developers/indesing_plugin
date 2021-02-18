//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IGridRelatedStyle.h $
//  
//  Owner: Shinji Hiramatsu
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
#ifndef __IGridRelatedStyle__
#define __IGridRelatedStyle__


#include "IPMUnknown.h"

#include "CJKID.h"
#include "CTextEnum.h"

 
class IGridRelatedStyle : public IPMUnknown
{
	public:

		enum { kDefaultIID = IID_IGRIDRELATEDSTYLE };

		//
		// Character attributes...
		//
		// Jidori
		/**  Jidori (CJKGrid-based range tracking), controls how many grid squares the text should occupy.
		@param num IN new value for this attribute
		*/
		virtual void SetNumOfJidori(int16 num) = 0;

		/**  Jidori (CJKGrid-based range tracking), controls how many grid squares the text should occupy.
		@return how many grid squares the text should occupy
		*/
		virtual int16 GetNumOfJidori() const = 0;
		
		//
		// Paragraph attributes...
		//
		// Gyoudori for line
		/**  Gyoudori (CJKGrid-based hard line height), controls how many grid lines the text line should occupy.
		@param num IN new value for this attribute
		*/
		virtual void SetNumOfGyoudori(int16 num) = 0;

		/**  Gyoudori (CJKGrid-based hard line height), controls how many grid lines the text should occupy.
		@return how many grid lines the text should occupy
		*/
		virtual int16 GetNumOfGyoudori() const = 0;

		// Paragraph Gyoudori
		/**  Gyoudori (CJKGrid-based hard paragraph height), controls if the gyoudori setting is for single lines (kFalse) or whole paragraphs (kTrue).
		@param val IN new value for this attribute
		*/
		virtual void SetIsParaGyoudori(bool16 val) = 0;

		/**  Paragraph Gyoudori (CJKGrid-based hard paragraph height), controls if the gyoudori setting is for single lines (kFalse) or whole paragraphs (kTrue).
		@return if the gyoudori setting is for single lines (kFalse) or whole paragraphs (kTrue)
		*/
		virtual bool16 GetIsParaGyoudori() const = 0;
		
		// Grid alignment
		/**  Grid alignment metric, controls which pt in the line should align to that pt in the grid line.
		@param where IN new value for this attribute
		*/
		virtual void SetGridAlignmentMetric(Text::GridAlignmentMetric where) = 0;
		
		/**  Grid alignment metric, controls which pt in the line should align to that pt in the grid line.
		@return which pt in the line should align to that pt in the grid line.
		*/
		virtual Text::GridAlignmentMetric GetGridAlignmentMetric() const = 0;

		// First line only
		/**  Grid alignment SetAlignOnlyFirstLine, controls whether or not only the first line in the paragraph should align to the grid.
		@param val IN new value for this attribute
		*/
		virtual void SetAlignOnlyFirstLine(bool16 val) = 0;

		/**  Grid alignment SetAlignOnlyFirstLine, controls whether or not only the first line in the paragraph should align to the grid.
		@return whether or not only the first line in the paragraph should align to the grid.
		*/
		virtual bool16 GetAlignOnlyFirstLine() const = 0;

		/**  Controls whether or not scale effects line height (which is how the grid scales).
		@param val IN new value for this attribute, kTrue means scale does effect line height.
		*/
		virtual void SetScaleAffectsLineHeight(bool16 val) = 0;
		
		/**  Returns whether or not scale effects line height (which is how the grid scales).
			@return kTrue means scale does effect line height.
		*/
		virtual bool16 GetScaleAffectsLineHeight() const = 0;
			
		/**  Controls whether or not tracking set in CJK grid should affect non-Roman char spacing and aki.
		@param val IN new value for this attribute, kTrue means CJK tracking is ON.
		*/
		virtual void SetCJKGridTracking(bool16 val) = 0;

		/**  Returns whether or not tracking set in CJK grid should affect non-Roman char spacing and aki.
			@return kTrue means CJK tracking is ON.
		*/
		virtual bool16 GetCJKGridTracking() const = 0;
};


#endif
		// __IGridRelatedStyle__

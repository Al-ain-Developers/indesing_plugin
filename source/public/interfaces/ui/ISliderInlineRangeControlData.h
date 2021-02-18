//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ISliderInlineRangeControlData.h $
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

#ifndef __ISliderInlineRangeControlData__
#define __ISliderInlineRangeControlData__


#include "widgetid.h"

/** Range control data interface for slider inline widget.
    This data interface is used to get/set the min/max/default/increment for 
	both the scrubber and the edit box.
*/
class ISliderInlineRangeControlData : public IPMUnknown
{
	public:
		/** Default IID to be used by UseDefaultIID() 
		*/
		enum { kDefaultIID = IID_ISLIDERINLINERANGECONTROLDATA };

		/** Enum values for update method.
		*/
		typedef enum { kUnknown = 0, kIncrement, kDecrement, kIncrementMultiple, kDecrementMultiple } UpdateMethod;

		/** Get the minimum value of the scrubber.
			@return int16 the minimum value.
		*/
		virtual PMReal 		GetScrubberMin() const = 0;

		/** Set the minimum value of the scrubber.
			@param value --- the minimum value.
		*/
		virtual void		SetScrubberMin(PMReal const &value) = 0;

		/** Get the maximum value of the scrubber.
			@return int16 the maximum value.
		*/	
		virtual PMReal 		GetScrubberMax() const = 0;

		/** Set the maximum value of the scrubber.
			@param value --- the maximum value.
		*/
		virtual void 		SetScrubberMax(PMReal const &value) = 0;

		/** Get the default value of the scrubber.
			@return int16 the default value.
		*/	
		virtual PMReal 		GetScrubberDefault() const = 0;

		/** Set the default value of the scrubber.
			@param value --- the default value.
		*/
		virtual void 		SetScrubberDefault(PMReal const &value) = 0;

		/** Get the increment value of the scrubber.
			@return int16 the increment value.
		*/	
		virtual PMReal 		GetScrubberIncrement() const = 0;

		/** Set the increment value of the scrubber.
			@param value --- the increment value.
		*/
		virtual void 		SetScrubberIncrement(PMReal const &value) = 0;

		/** Get the increment multiple value of the scrubber (e.g., used for KBSC)
			@return int16 the increment multiple value.
		*/	
		virtual PMReal 		GetScrubberIncrementMultiple() const = 0;

		/** Set the increment multiple value of the scrubber (e.g., used for KBSC)
			@param value --- the increment multiple value.
		*/
		virtual void 		SetScrubberIncrementMultiple(PMReal const &value) = 0;

		/** Get the minimum value of the edit box.
			@return int16 the minimum value.
		*/
		virtual PMReal 		GetEditBoxMin() const = 0;

		/** Set the minimum value of the edit box.
			@param value --- the minimum value.
		*/
		virtual void		SetEditBoxMin(PMReal const &value) = 0;

		/** Get the maximum value of the edit box.
			@return int16 the maximum value.
		*/
		virtual PMReal 		GetEditBoxMax() const = 0;

		/** Set the maximum value of the edit box.
			@param value --- the maximum value.
		*/
		virtual void 		SetEditBoxMax(PMReal const &value) = 0;

		/** Get the default value of the edit box.
			@return int16 the default value.
		*/	
		virtual PMReal 		GetEditBoxDefault() const = 0;

		/** Set the default value of the edit box.
			@param value --- the default value.
		*/
		virtual void 		SetEditBoxDefault(PMReal const &value) = 0;

		/** Get the increment multiple value of the edit box (e.g., used for KBSC)
			@return int16 the increment multiple value.
		*/	
		virtual PMReal 		GetEditBoxIncrement() const = 0;

		/** Set the increment value of the edit box.
			@param value --- the increment value.
		*/
		virtual void 		SetEditBoxIncrement(PMReal const &value) = 0;

		/** Get the increment multiple value of the edit box (e.g., used for KBSC)
			@return int16 the increment multiple value.
		*/
		virtual PMReal 		GetEditBoxIncrementMultiple() const = 0;

		/** Set the increment multiple value of the edit box (e.g., used for KBSC)
			@param value --- the increment multiple value.
		*/
		virtual void 		SetEditBoxIncrementMultiple(PMReal const &value) = 0;

		/** Get the data update method (e.g., increment or decrement)
			@return DataUpdateMethod update method.
		*/
		virtual ISliderInlineRangeControlData::UpdateMethod  GetUpdateMethod() const = 0;

		/** Set the data update method (e.g., increment or decrement)
			@param value --- data update method.
		*/
		virtual void 		SetUpdateMethod(ISliderInlineRangeControlData::UpdateMethod const &value) = 0;
};

#endif

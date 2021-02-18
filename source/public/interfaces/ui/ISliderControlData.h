//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ISliderControlData.h $
//  
//  Owner: SusanCL
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
#ifndef __ISliderControlData__
#define __ISliderControlData__

#include "widgetid.h"
#include "PMReal.h"

/**
   This is a data interface for a slider widget.
   @ingroup ui_dialog
   @see IObserver
   @see widgetid.h
*/

class ISliderControlData : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_ISLIDERCONTROLDATA};

	/**	Sets slider value.
		@param value the value to set.
		@param invalidate specifies whether the slider should be redrawn.
		@param notifyOfChange specifies whether observers on the control data should be notified of the change.
		If so, the message broadcast is kRealChangeStateMessage and the protocol is IID_ISLIDERCONTROLDATA.
	*/
	virtual void		SetValue(const PMReal& value, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/**	Returns the current slider value.
		@return the current slider value.
	*/
	virtual PMReal		GetValue() const = 0;
	/**	Returns the current maximum slider value.
		@return the current maximum slider value.
	*/
	virtual PMReal		GetMaxValue() const = 0;
	/**	Returns the current minimum slider value.
		@return the current minimum slider value.
	*/
	virtual PMReal		GetMinValue() const = 0;

	/**	Sets the new slider minimum value.
		@param value the new minimum value to set.
		@param invalidate specifies whether the slider should be redrawn.
		@param notifyOfChange specifies whether observers on the control data should be notified of the change. 
		If so, the message broadcast is kRealChangeStateMessage and the protocol is IID_ISLIDERCONTROLDATA.
	*/
	virtual void SetMinValue(const PMReal &value, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;
	/**	Sets the new slider maximum value.
		@param value the new maximum value to set.
		@param invalidate specifies whether the slider should be redrawn.
		@param notifyOfChange specifies whether observers on the control data should be notified of the change. 
		If so, the message broadcast is kRealChangeStateMessage and the protocol is IID_ISLIDERCONTROLDATA.
	*/
	virtual void SetMaxValue(const PMReal &value, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;
};

#endif

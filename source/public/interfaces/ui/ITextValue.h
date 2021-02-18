//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ITextValue.h $
//  
//  Owner: lance bushore
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
#ifndef __ITextValue__
#define __ITextValue__

#include "IPMUnknown.h"
#include "widgetid.h"

class ITextValue : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ITEXTVALUE };

	typedef enum { 
		kNormal = 0,		// normal state						(usually reads 'value')
	 	kUnknown,			// unknown or mixed state			(usually blank)
	  	kCalculated,		// calculated value state			(usually reads '(value)')
	   	kMixedCalculated	// calculated, but mixed values 	(usually reads 'Auto')
	    } TextControlState;
	    
	typedef enum { 
		kAbsolute = 0,		// User typed in a number (or a formula)
	 	kDelta,				// User typed in addition/subtraction
	  	kProportional		// User typed in a percent or mult/div
	    } TextControlChange;
	 

	// gets the text from the control, converts it to an appropriate value, and returns it.
	// i.e. for measurement editboxes, returns value in points, or for percentage editboxes,
	// returns percentage as a real. Sets errorOut to true if error in conversion.
	virtual PMReal GetTextAsValue(bool16 *errorOut = nil,bool16 *blankEntry = nil) = 0;

	// sets the text for the control,given an appropriate value
	// i.e. for measurement editboxes, takes value in points and converts to current
	// measurement system string like 4p5, or for percentage editboxes, converts 45.0 to 45 %
	virtual void SetTextFromValue(const PMReal& valueIn, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	// gets the text for the control, formats it nicely, and resets it.
	// i.e. converts '10' to '10 %' or 'Auto' to '(14 pt)'
	// this is generally called when the user changes the text, by typing and hitting return or
	// selecting a new item from a popup.
	virtual void ReformatText(bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	// call this if you are unable to display values for multiple
	// selected items. Calling SetTextFromValue will clear it.
	virtual void SetControlState(TextControlState newState, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;
	virtual TextControlState GetControlState() const = 0;
	virtual TextControlChange GetLastControlChange(PMReal* value) const = 0;
};	



#endif // __ITextValue__

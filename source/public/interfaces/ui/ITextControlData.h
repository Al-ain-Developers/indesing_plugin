//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ITextControlData.h $
//  
//  Owner: Frits Habermann
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
//  Purpose: ITextControlData provides an interface for storing text along with an object, typically a widget. The interface
//  is meant to be farily straightforward, with various "Set" methods for different kinds of strings (like numbers
//  vs. text), and the ability to retreive the string. 
//  
//========================================================================================

#pragma once
#ifndef __ITEXTCONTROLDATA__
#define __ITEXTCONTROLDATA__

#include "PMTypes.h"
#include "PMString.h"
#include "widgetid.h"

class ITextControlData : public IPMUnknown
{
	public:
	enum { kDefaultIID = IID_ITEXTCONTROLDATA };
		
	/** Used after setting the string data
	*/
    enum	TextControlDataState { kDirty = 1 };

	/** Method to set the string on interface.
		@param newString string to set
		@param invalidate specifies whether the control should be redrawn
		@param notifyOfChange specifies whether observers on the control data should be notified of the change.
		@param isGoodString specifies whether newString is a valid string. Currently it is only used in 
				EditboxTextControlData. If true, the last good text will be set automatically.
	*/
	virtual void SetString(const PMString& newString, bool16 invalidate = kTrue, 
							bool16 notifyOfChange = kTrue, bool16 isGoodString = kTrue) = 0;
	
	/** Get the value of the string
		@return PMString of current string on interface.
	*/
	virtual const PMString& GetString() const = 0;
};

#endif

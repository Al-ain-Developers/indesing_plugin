//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ITextUIDListValue.h $
//  
//  Owner: ???
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
//  [f************************************************************************
//  ITextUIDListValue.h	 		
//  
//  f]**********************************************************************
//  
//========================================================================================

#pragma once
#ifndef __ITextUIDListValue__
#define __ITextUIDListValue__

#include "IPMUnknown.h"
#include "UIDList.h"
#include "ITextDataValidation.h"

/** Data interface to convert string to UIDList and vice versa.
	This interface usually lives on the UI controls like edit box.
*/

class ITextUIDListValue : public IPMUnknown
{
public:	
	/** Convert the string text getting from the control to a UIDList.
		For example, for page range editboxes, it gets page range string 
		and convert to a UIDList of pages.
		Error will be set if there is error in conversion.
		@param valueOut [OUT]: the converted UIDList.
		@param pnError [OUT]: the error that happens in conversion, see also @ITextDataValidation.
	*/
	virtual void GetTextAsValue(UIDList& valueOut, ITextDataValidation::RangeError* pnError = nil) = 0;

	/** Convert the given UIDList to string text and set it in the control.
		For example, for page range editboxes, it will take UIDList and convert it to
		page range string like "1-5, 7, 9, 10-12".
		@param valueIn [IN]: the given UIDList.
		@param invalidate [IN]: boolean flag indicates if we should do invalidation the control or not when we set the string value in the control, default value is kTrue.
		@param notifyOfChange [IN]: boolean flag indicates if we should do notification or not when we set the string value in the control, default value is kTrue.
	*/
	virtual void SetTextFromValue(UIDList& valueIn, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/** Reset the string of the control with the string passed in through ITextControlData.
		This intends to be called when the user changes the text, by typing and hitting return or
		selecting a new item from a popup. 
		@param invalidate [IN]: boolean flag indicates if we should do invalidation the control or not when we set the string value in the control, default value is kTrue.
		@param notifyOfChange [IN]: boolean flag indicates if we should do notification or not when we set the string value in the control, default value is kTrue.
	*/
	virtual void ReformatText(bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;
};	



#endif // __ITextUIDListValue__

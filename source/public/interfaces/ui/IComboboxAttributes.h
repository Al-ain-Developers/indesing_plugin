//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IComboboxAttributes.h $
//  
//  Owner: Lance Bushore
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
#ifndef __IComboboxAttributes__
#define __IComboboxAttributes__

#include "IPMUnknown.h"
#include "widgetid.h"

/**	InDesign's combobox widgets are really compound widgets, made up of a dropdown subwidget and an editbox subwidget.
	This interface tells the combobox it's on which boss to use for the dropdown subwidget and editbox subwidget
	note:  this interface can't read data from resource files because of where it is used(readwrite of a controlview)
*/
class  IComboboxAttributes : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOMBOBOXATTRIBUTES };

	/**	Get the ClassID that we should create for the dropdown subwidget
		@return boss to create
	*/
	virtual ClassID GetDropDownClassID() const = 0;

	/**	Get the ClassID that we should create for the editbox subwidget
		@return boss to create
	*/
	virtual ClassID GetEditboxClassID() const = 0;
};	

#endif // __IComboboxAttributes__

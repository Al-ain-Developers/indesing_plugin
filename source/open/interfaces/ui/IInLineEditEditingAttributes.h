//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/ui/IInLineEditEditingAttributes.h $
//  
//  Owner:
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
#ifndef __IInLineEditEditingAttributes__
#define __IInLineEditEditingAttributes__

#include "WidgetDefs.h"
#include "widgetid.h"

/**   
	InLineEdit widget normally displayed as static text. Under certain event 
	(e.g. double click), static text can be changed on the spot. This interface 
	controls the behavior of InLineEdit widget.
*/
class IInLineEditEditingAttributes : public IPMUnknown
{
public:

	enum { kDefaultIID = IID_IINLINEEDITEDITINGATTRIBUTES };

	/**
		Return the type of widget for editing current static text. Currently only 
		support editbox, combobox, and dropdown (popup) widget.
		@return either (kEditbox, kCombobox, or kDropdown)
	*/
	virtual InLineEditWidgetType GetEditWidgetType() const = 0;

	/**
		Enable or disable in line editing.  A disabled widget cannot enter editing mode. 
		@param state kTrue to enable, kFalse to disable
	*/
	virtual void		SetIsEditable(bool16 isEditable) = 0;

	/**
		Return kTrue if can be edited, kFalse otherwise
		@return kTrue if can be edited, kFalse otherwise
	*/
	virtual bool16 		IsEditable() const = 0;

	/**
		This flag control if InLineEdit widget can take keyboard focus. If set to kTrue,
		InLineEdit will be able to take tab key focus stop
		@param keyFocus. Can take focus if set to kTrue, kFalse otherwise
	*/
	virtual void		SetTakeKeyboardFocus(bool16 keyFocus) = 0;

	/**
		Return kTrue if can have key focus, kFalse otherwise
		@return kTrue if can have key focus, kFalse otherwise
	*/
	virtual bool16 		GetTakeKeyboardFocus() const = 0;

	/**
		This is used only with click-pause-click event handler. The first click select item 
		and the second click enter editing mode. Client has to override the function to get
		correct behavior. Default impl always return kFalse.
		@return kTrue if selected, kFalse otherwise
	*/
	virtual bool16 		IsSelected() const = 0;

	/**
		If to change the length of editbox to current text. This imply dyanmic resizing of
		editbox during editing. Only used with TextInLineEditWidget
		@param state kTrue to enable, kFalse to disable
	*/
	virtual void		SetFitEditBoxtoText(bool16 fitText) = 0;

	/**
		Return kTrue if fix editbox to text, kFalse otherwise
		@return kTrue if fix editbox to text, kFalse otherwise
	*/
	virtual bool16 		GetFitEditBoxtoText() const = 0;
};

#endif

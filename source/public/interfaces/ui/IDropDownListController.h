//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDropDownListController.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IDropDownListController_h__
#define __IDropDownListController_h__

#include "widgetid.h"

//========================================================================================
// CLASS TEMPLATE IDropDownListController
//========================================================================================

class IDropDownListController : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IDROPDOWNLISTCONTROLLER };
	enum { kBeginning = 0, kNoSelection = -1, kEnd = -2, kDefaultSelection = -3 };

	// Selection	
	/** Select the element at the given position in the list.	
		@return none
	*/

	virtual void		Select(int32 index, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;
	/** Deselect the element selected. No selection.	
		@return none
	*/

	virtual void		Deselect(bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;
	/** Is the given element selected?
		@return kTrue if selected, kFalse otherwise
	*/

	virtual bool16		IsSelected(int32 index) const = 0;
	/** Get index of the currently selected element.
		@return the index of selected item, kNoSelection if no item selected
	*/
	virtual int32		GetSelected() const = 0;
	/** Set index of the element that should be selected when kDefaultSelection
		is passed into Select.
		@return none
	*/
	virtual void		SetDefaultSelection(int32 index) = 0;


	// Enable/Disable	
	/** Enable the element at the given position in the list.	
		@return none
	*/
	virtual void		Enable(int32 index, bool16 doEnable = kTrue, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/** Disable the element at the given position in the list.
		@return none
	*/
	virtual void		Disable(int32 index, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;
								
	/** Is the given element enabled?
		@return kTrue if enabled, kFalse otherwise
	*/
	virtual bool16		IsEnabled(int32 index) const = 0;


	//Utility
	/** Try to determine if dropdowm menu is open.
		@return kTrue if dropdown menu is currently open, kFalse otherwise
	*/
	virtual bool16		IsDropDownOpen() const = 0;
};

#endif
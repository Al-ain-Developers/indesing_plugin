//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IUIColorDDList.h $
//  
//  Owner: Michele Goodwin
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IUIColorDDList__
#define __IUIColorDDList__

#include "IPMUnknown.h"
#include "IInterfaceColors.h"
#include "InCopySharedUIID.h"

class IInCopyUIColors;

/** 
	Interface used in InCopy to initialize, set, and get entries for an owner draw dropdown list of colors swatches and names. 

	@see kUIColorsDDListBoss
	@see IInCopyUIColors
	@see RealAGMColor
	@see PMString
 */

class IUIColorDDList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IUICOLORDDLIST };

	/**
		InitDropDownList - Initializes the UI color dropdown list with the items in the IInCopyUIColors list passed in. Always clears the dropdown before adding entries.
	
		@param IN	uiColors - List used to populate the UI color dropdown list.
		@see IInCopyUIColors
	*/
	virtual void InitDropDownList(IInCopyUIColors* uiColors) = 0;

	/**
		SetSelection - Set the selection in the dropdown list using color name. Assumes that names in the dropdown list are unique, so
		would always find first entry if name is in list more than once.
	
		@param IN	color -Name of color used to set the selection.
		@param IN	bInvalidate - kTrue == invalidate the dropdown list; kFalse == don't
		@param IN	bNotifyOfChange - kTrue == notify observers of the change; kFalse == don't
		@return int32 index of the item selected. Returns -1 if nothing is selected (which can happen if an invalid name is passed in).
	*/
	virtual int32 SetSelection(const PMString &color, bool16 bInvalidate = kTrue, bool16 bNotifyOfChange = kTrue) = 0;

	/**
 		SetSelection - Set the selection in the dropdown list using color value. Assumes that color values in the dropdown list are unique, so
		would always find first entry if value is in list more than once.
	
		@param IN	colorVal -RealAGMColor value used to set the selection.
		@param IN	bInvalidate - kTrue == invalidate the dropdown list; kFalse == don't
		@param IN	bNotifyOfChange - kTrue == notify observers of the change; kFalse == don't
		@return int32 index of the item selected. Returns -1 if nothing is selected (which can happen if an invalid color value is passed in).
	*/
	virtual int32 SetSelection(const RealAGMColor &colorVal, bool16 bInvalidate = kTrue, bool16 bNotifyOfChange = kTrue) = 0;

	/**
		SetSelection - Set the selection in the dropdown list using index of list entry.
	
		@param IN	index -Index into dropdown list used to set the selection.
		@param IN	bInvalidate - kTrue == invalidate the dropdown list; kFalse == don't
		@param IN	bNotifyOfChange - kTrue == notify observers of the change; kFalse == don't
		@return int32 index of the item selected. Returns -1 if nothing is selected (which can happen if an invalid index is passed in).
	*/
	virtual int32 SetSelection(const int32 index, bool16 bInvalidate = kTrue, bool16 bNotifyOfChange = kTrue) = 0;


	/**
		GetSelectionIndex - Returns the index of currently selected item in the dropdown.
	
		@return int32 index of the item currently selected in the dropdown.
	*/
	virtual int32 GetSelectionIndex() = 0;

	/**
		GetSelectionColorName - Returns the color name of currently selected item in the dropdown.
	
		@return PMString color name of item currently selected in the dropdown.
	*/
	virtual PMString GetSelectionColorName() = 0;

	/**
		GetSelectionColorValue - Returns the color value of currently selected item in the dropdown.
	
		@return RealAGMColor color value of the item scurrently elected in the dropdown.
	*/
	virtual RealAGMColor GetSelectionColorValue() = 0;
};

#endif // __IUIColorDDList__

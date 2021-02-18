//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/pdfvtui/IDropDownListSelection.h $
//
//  Owner: Adobe Developer Technologies
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

#ifndef __IDROPDOWNLISTSELECTION_H
#define __IDROPDOWNLISTSELECTION_H

#include "IPMUnknown.h"

#include "PDFVTUIID.h"

/** Interface to store the selections the user made to
	DropDown lists on the dialog.

	@ingroup pdfvtui
*/
class IDropDownListSelection : public IPMUnknown
{
public:

	enum { kDefaultIID = IID_IPDFVTUIDROPDOWNLISTSELECTION };		

	/** Sets the selected index for the given dropdown list widget.
			@param dropDownList IN Id of the dropdown list.
			@param index IN selected index.
	*/
	virtual void SetSelection(int32 dropDownList, int32 index) = 0;

	/** Gets the selected index for the given dropdown list widget.
			@param dropDownList IN Dd of the dropdown list.
			@return index of the selected item.
	*/
	virtual int32 GetSelection(int32 dropDownList) const = 0;

	/** Re-Initializes selections to 0 for all the dropdown lists.
	*/
	virtual void Init(void) = 0;
};
#endif
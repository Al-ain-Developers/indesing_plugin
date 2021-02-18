//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/pdfvtui/DropDownListSelection.cpp $
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

#include "VCPlugInHeaders.h"

#include "IPMStream.h"

#include <map>

#include "IDropDownListSelection.h"

using namespace std;

/** Stores the current selected index for all the dropdown lists on the
	dialog.

	@ingroup pdfvtui
*/
class DropDownListSelection : public CPMUnknown<IDropDownListSelection>
{
public:
	/** Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	DropDownListSelection(IPMUnknown* boss);

	/** Sets the selection of given dropdown list to the specified
		value.
			@param dropDownList id of the dropdown list.
			@param index selected index.
	*/
	virtual void SetSelection(int32 dropDownList, int32 index);

	/** Gets the selection of given dropdown list.
			@param dropDownList id of the dropdown list.
			@return selected index.
	*/
	virtual int32 GetSelection(int32 dropDownList) const;

	/** Re-initialize the selection for all the dropdown lists to 0.
	*/
	virtual void Init(void);

private:

	/** Re-initialize the selection for all the dropdown lists to 0.
	*/
	void Reset(void);

private:

	/** Stores the selections for each dropdown list widget.
	*/
	map<int32, int32> fSelections;

};

CREATE_PMINTERFACE(DropDownListSelection, kPDFVTUIDropDownListSelectionImpl)

DropDownListSelection::DropDownListSelection(IPMUnknown* boss) : CPMUnknown<IDropDownListSelection>(boss)
{
	Reset();
}

void DropDownListSelection::SetSelection(int32 dropDownList, int32 index)
{
	if (fSelections.find(dropDownList) != fSelections.end())
	{
		fSelections[dropDownList] = index;
	}
}

int32 DropDownListSelection::GetSelection(int32 dropDownList) const
{
	map<int32, int32>::const_iterator it = fSelections.find(dropDownList);
	if (it != fSelections.end())
	{
		return it->second;
	}
	return 0;
}

void DropDownListSelection::Init(void)
{
	Reset();
}

void DropDownListSelection::Reset(void)
{
	fSelections[kPDFVTUIFirstNameDropDownListWidgetID] = 0;
	fSelections[kPDFVTUILastNameDropDownListWidgetID] = 0;
	fSelections[kPDFVTUICityDropDownListWidgetID] = 0;
	fSelections[kPDFVTUIPostalCodeDropDownListWidgetID] = 0;
	fSelections[kPDFVTUICountryDropDownListWidgetID] = 0;
}
//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextFrameDialogUtils.h $
//  
//  Owner: Tetsuya Araki
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
#ifndef __ITextFrameDialogUtils__
#define __ITextFrameDialogUtils__

#include "IPMUnknown.h"
#include "IReferencePointData.h"
#include "IVerticalColumnRuleData.h"
#include "Utils.h"
#include "TextID.h"

#include "CTextEnum.h"
class UIDList;
class IDialogController;
class ITextFrameOptionsData;

/**
	Utility class used primarily for the TextFrameOptions dialog.

	NOTE: requires the use of ITextFrameOptionsData
 */
class ITextFrameDialogUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTFRAMEDIALOGUTILS };

	/** Invoke the dialog
	*/
	virtual void ActivateTextFrameDialog(bool16 fromMenu, WidgetID dialogPanelID) = 0;
	/** Same as DisplayTextFrameDialog, but only invokes the dialog if the current selection supports Text Frame Options operations.
	*/
	virtual void DisplayTextFrameDialog(bool16 fromMenu, WidgetID dialogPanelID) = 0;  			// Checks selection before activating dialog

	/** Handle dialog changes affecting the MCF (multi-column frames) associated with the selection for VJOptions

		This  should be called when the user changes any of the corresponding attributes.
	*/
	virtual void SetTFODialogVJOptions(IDialogController* controller, const ITextFrameOptionsData* tfoData) const = 0;

	/** Handle dialog changes affecting the MCF (multi-column frames) associated with the selection for fixed and range columns

		This  should be called when the user changes any of the corresponding attributes.
	*/
	virtual void SetTFODialogFixedAndFlexibleOptions(IDialogController* controller, const ITextFrameOptionsData* tfoData) const = 0;

	/** Put focus into column number, column width, or max column width widgets when user
		changes the column resizing method.

		This  should be called when the user changes any of the corresponding attributes.
	*/
	virtual void SetTFODialogColumnResizingFocus(IDialogController* controller, const ITextFrameOptionsData* tfoData) const = 0;

	/** Constants for the resizing dropdown list
	*/
	enum ColumnResizingMethod {
		kFixedNumberResizing = 0,		/** Maps to fixed width off and flexible width off */
		kFixedWidthResizing = 1,		/** Maps to fixed width on (and flexible width off) */
		kFlexibleWidthResizing = 2,		/** Maps to flexible width on (and fixed width off) */
		kIgnoreResizing = 3,			/** Maps to column resizing not set, used in Object Styles */
		kFixedWidthOffResizing = 4,		/** Maps to fixed width off attribute, used in F/C */
		kFlexibleWidthOffResizing = 5,	/** Maps to flexible width off attribute, used in F/C */
	};

	/** Return the method for column resizing from the dialog set in the kResizingDropDownWidgetID dropdown
	*/
	virtual ColumnResizingMethod GetColumnResizingMethod(IPMUnknown* dialogUnknown) const = 0;

	/** Return the method for column resizing from dialog data
	*/
	virtual ColumnResizingMethod GetColumnResizingMethod(ITextFrameOptionsData* tfo) const = 0;

	/** Set method to choose correct string in kResizingDropDownWidgetID dropdown
	*/
	virtual void SetColumnResizingMethod(IPMUnknown* dialogUnknown, ColumnResizingMethod method) const = 0;

	/** Handle dialog changes affecting the MCF (multi-column frames) associated with the selection for Auto Size

		This  should be called when the user changes any of the corresponding attributes.
	*/
	virtual void SetTFDlgAutoSizeOptions(IDialogController* controller, const ITextFrameOptionsData* tfoData) const = 0;

	/** Set method to set the correct value of Auto Size dimension in the associated drop down, 
		and controls enable/disable of dependent controls
	*/
	virtual void SetTFDlgAutoSizeDimension(IDialogController* controller, const ITextFrameOptionsData* tfo) const = 0;

	/** Set method to set Auto size minimum height check-box state and controls enable/disable of associated edit field.
	*/
	virtual void SetTFDlgAutoSizeHasMinHeight(IDialogController* controller, const ITextFrameOptionsData* tfo) const = 0;

	/** Set method to set Auto size minimum width check-box state and controls enable/disable of associated edit field.
	*/
	virtual void SetTFDlgAutoSizeHasMinWidth(IDialogController* controller, const ITextFrameOptionsData* tfo) const = 0;

	/** Set method to set Auto size dimension and reference point for the Auto-sizing panel.
	*/
	virtual void SetTFOAutoSizeDimensionWithReference(IPMUnknown* panelData, 
													Text::AutoSizeDimension asDimension, 
													IReferencePointData::ReferencePointPosition refPoint) const = 0;

	/** Method to enable and disable the auto sizing min height edit box based on the state of associated check-box.
	*/
	virtual void EnableTFOAutoSizeMinHeight(IPMUnknown* panelData)const = 0 ;

	/** Method to enable and disable the auto sizing min width edit box based on the state of associated check-box.
	*/
	virtual void EnableTFOAutoSizeMinWidth(IPMUnknown* panelData)const = 0 ;


	/** Gets the auto size widget ID from the given reference point
	*/
	virtual WidgetID GetAutoSizeWidgetIDFromRefPoint(IReferencePointData::ReferencePointPosition refPoint)const = 0;

	/** Gets the reference point position from the given auto size proxy widget ID
	*/
	virtual IReferencePointData::ReferencePointPosition GetAutoSizeRefPointFromWidgetID(WidgetID widgetID)const = 0;

	/** Handle dialog changes affecting the Vertical Column rule

	This  should be called when the user changes any of the corresponding attributes.
	*/
	virtual void SetTFOVerticalRuleOptions(IActiveContext* ac, IDialogController* controller, const ITextFrameOptionsData* tfoData) const = 0;

	/** Gets the desired vertical rule height mode
	*/
	virtual IVerticalColumnRuleData::VerticalRuleHeightMode GetDesiredVerticalRuleHeightMode()const = 0;

	/** Gets the top delta from ascent to embox and bottom delta from descent to embox.
	*/
	virtual void GetTopAndBottomDeltaFromAscentDescentToEmbox(PMReal& topDeltaFromEmboxToAscent, PMReal& bottomDeltaFromEmboxToAscent)const = 0;
};

#endif // __ITextFrameDialogUtils__

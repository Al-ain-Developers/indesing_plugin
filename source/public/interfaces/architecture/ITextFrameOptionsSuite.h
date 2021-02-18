//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ITextFrameOptionsSuite.h $
//  
//  Owner: rkamicar
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
//  Note:
//  
//========================================================================================

#pragma once
#ifndef _ITextFrameOptionsSuite_
#define _ITextFrameOptionsSuite_

#include "IPMUnknown.h"

class IBaselineFrameGridData;
class ITextFrameOptionsData;

/** ITextFrameOptionsSuite
*/
class ITextFrameOptionsSuite : public IPMUnknown
{
//____________________________________________________________________________________________
//	Data Types
//____________________________________________________________________________________________
public:
	enum { kDefaultIID = IID_ITEXTFRAMEOPTIONS_ISUITE };
//____________________________________________________________________________________________
//	Member functions
//____________________________________________________________________________________________
public:

	/**  FreezeSelectionForModalDialog is used to freeze the selection when a modal dialog is about to be invoked.
	This allows the modal dialog to operate on the same items regardless of how the changes affect the selection over time.
	(For example, if you have a caret and increase the columns, such that the caret moves to the next frame, the dialog will still
	operate on the original text frame).
	THIS CALL MUST BE PAIRED WITH A CALL TO ThawSelectionForModalDialog()
	*/
	virtual void	FreezeSelectionForModalDialog() = 0;

	/**  ThawSelectionForModalDialog is used to thaw the selection when a modal dialog has been closed.
	see FreezeSelectionForModalDialog for mor details.
	THIS CALL MUST BE PAIRED WITH A CALL TO FreezeSelectionForModalDialog()
	*/
	virtual void	ThawSelectionForModalDialog() = 0;

	/**  CanApplyTextFrameOptions is used to determine if text frame options can be displayed for the current target.
	@return kTrue if text frame options can be displayed.
	*/
	virtual bool16	CanApplyTextFrameOptions (void) const = 0;

	/**  GetColumnsAndGutter is used to retrieve the number of columns and gutter width for items in selection.
	@param numberOfColumnsVector OUT The vector for adding column widths to.
	@param gutterWidthVector OUT The vector for adding gutter widths to.
	@param  sortedAndUnique IN If kTrue the vectors will be sorted and duplicates will be removed.
	*/
	virtual void	GetColumnsAndGutter(K2Vector<int32> & numberOfColumnsVector, K2Vector<PMReal> & gutterWidthVector, bool16 sortedAndUnique ) const = 0;

	/** GetTextFrameOptionsData - Perform the Text Frame Options dialog. Returns kTrue if current target
		supports this operation, kFalse otherwise.
	*/
	virtual bool16	GetTextFrameOptionsData(ITextFrameOptionsData* tfoData) const = 0;

	/** setTextFrameOptionsData - Sets the Text Frame Options to the given data
	*/
	virtual void	SetTextFrameOptionsData(ITextFrameOptionsData* tfoData) = 0;

	/** SetTFO* - Process an action from the Text Frame Options dialog
	*/
	virtual void	SetTFOWidthOptions(ITextFrameOptionsData* tfoData) const = 0;
	virtual void	SetTFOInsetOptions(ITextFrameOptionsData* tfoData) const = 0;
	virtual void	SetTFOColumns(ITextFrameOptionsData* tfoData) const = 0;
	virtual void	SetTFOGutterWidth(ITextFrameOptionsData* tfoData) const = 0;
	virtual void	SetTFOIgnoreWrap(ITextFrameOptionsData* tfoData) const = 0;
	virtual void	SetTFOFirstLineOffsetMetric(ITextFrameOptionsData* tfoData) const = 0;
	virtual void	SetTFOMinFirstLineOffset(ITextFrameOptionsData* tfoData) const = 0;
	virtual void	SetTFOVerticalJustify(ITextFrameOptionsData* tfoData) const = 0;
	virtual void	SetTFOMaxVJInterParaSpace(ITextFrameOptionsData* tfoData) const = 0;
	virtual void	SetTFOVJBalanceColumns(ITextFrameOptionsData* tfoData) const = 0;

	/** GetBaselineFrameGridData - Get the baseline frame grid data for the current selection.
		@bool	convertColorUIDToLayerColor	true if you want the actually color that will be displayed, false means if you are using the layer color it will return kInvalidUID
	*/
	virtual void	GetBaselineFrameGridData(ITextFrameOptionsData* tfoData, bool16 convertColorUIDToLayerColor = kTrue) const = 0;

	/** SetBaselineFrameGridData - Sets the baseline frame grid data to the given data
	*/
	virtual void	SetBaselineFrameGridData(ITextFrameOptionsData* tfoData) = 0;

	/** Set baseline frame grid data* - Process an action from the Text Frame Options dialog
	*/
	virtual void SetUseCustomBaselineGridFlag(ITextFrameOptionsData* tfoData) const = 0;
	virtual void SetStartingOffset(ITextFrameOptionsData* tfoData) const = 0;
	virtual void SetRelativeOption(ITextFrameOptionsData* tfoData) const = 0;
	virtual void SetIncrement(ITextFrameOptionsData* tfoData) const = 0;
	virtual void SetBaselineFrameGridColor(ITextFrameOptionsData* tfoData) const = 0;

	/** Set Auto Size text frame options data* - Process an action from the Text Frame Options dialog
	*/
	virtual void SetAutoSizeDimension(ITextFrameOptionsData* tfoData) const =0;
	virtual void SetAutoSizeRefPoint(ITextFrameOptionsData* tfoData) const =0;
	virtual void SetAutoSizeHasMinHeight(ITextFrameOptionsData* tfoData) const =0;
	virtual void SetAutoSizeMinHeightValue(ITextFrameOptionsData* tfoData) const =0;
	virtual void SetAutoSizeHasMinWidth(ITextFrameOptionsData* tfoData) const =0;
	virtual void SetAutoSizeMinWidthValue(ITextFrameOptionsData* tfoData) const =0;
	virtual void SetAutoSizeNoLineBreak(ITextFrameOptionsData* tfoData) const =0;

	/** GetTextFrameFootnoteOptions - Get the text frame footnote options for the given data.
	*/
	virtual void GetTextFrameFootnoteOptions(ITextFrameOptionsData* tfoData) const = 0;

	/** SetTextFrameFootnoteOptions - Sets the text frame footnote options to the given data
	*/
	virtual void SetTextFrameFootnoteOptions(ITextFrameOptionsData* tfoData) = 0;

	/** Set Footnote Options text frame options data* -  Process an action from the Text Frame Options dialog
	*/
	virtual void SetFootnoteOptionsHasEnableOverrides(ITextFrameOptionsData* tfoData) const = 0;
	virtual void SetFootnoteOptionsHasSpanFootnotesAcross(ITextFrameOptionsData* tfoData) const = 0;
	virtual void SetFootnoteOptionsMinimumSpacingValue(ITextFrameOptionsData* tfoData) const = 0;
	virtual void SetFootnoteOptionsSpaceBetweenFootnotesValue(ITextFrameOptionsData* tfoData) const = 0;

	/** GetTextFrameVerticalRuleOptions - Get the text frame column rule options for the given data.
	*/
	virtual void GetTextFrameVerticalRuleOptions(ITextFrameOptionsData* tfoData) const = 0;

	/** SetTextFrameVerticalRuleOptions - Set the text frame column rule options for the given data.
	*/
	virtual void SetTextFrameVerticalRuleOptions(ITextFrameOptionsData* tfoData) const = 0;

	/** Set Column Rule Options text frame options data* -  Process an action from the Text Frame Options dialog
	*/
	virtual void SetUseVerticalRule(ITextFrameOptionsData* tfoData) const = 0;
	virtual void SetVerticalRuleOffset(ITextFrameOptionsData* tfoData) const = 0;
	virtual void SetVerticalRuleTopInset(ITextFrameOptionsData* tfoData)const = 0;
	virtual void SetVerticalRuleInsetChain(ITextFrameOptionsData* tfoData) const = 0;
	virtual void SetVerticalRuleBottomInset(ITextFrameOptionsData* tfoData) const = 0;
	virtual void SetVerticalRuleStrokeWidth(ITextFrameOptionsData* tfoData)const = 0;
	virtual void SetVerticalRuleStrokeColor(ITextFrameOptionsData* tfoData) const = 0;
	virtual void SetVerticalRuleStrokeType(ITextFrameOptionsData* tfoData) const = 0;
	virtual void SetVerticalRuleTint(ITextFrameOptionsData* tfoData) const = 0;
	virtual void SetVerticalRuleOverprint(ITextFrameOptionsData* tfoData) const = 0;
};

#endif // _ITextFrameOptionsSuite_

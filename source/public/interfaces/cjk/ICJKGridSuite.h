//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ICJKGridSuite.h $
//  
//  Owner: Heath Lynn
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
#ifndef __ICJKGridSuite__
#define __ICJKGridSuite__

#include "IPMUnknown.h"
#include "IFilteredCJKGridCmdData.h"
#include "ICJKCharCountOptions.h"
#include "ICJKFrameGridDefaults.h"

#include "CJKGridID.h"
#include "PMRect.h"
#include "K2Vector.h"


//========================================================================================
// Forward declarations
//========================================================================================
class ICJKGridData;
class IFilteredCJKGridCmdData;
class CJKGridData;

//========================================================================================
// CLASS ICJKGriSuite
//========================================================================================

/** ICJKGridSuite 
*/
class ICJKGridSuite : public IPMUnknown
{

public:

	typedef struct
	{
		bool16 applyNumOfLines; 
		int32 numOfLines;
		bool16 applyCharsPerLine;
		int32 charsPerLine;
		bool16 applyNumOfColumns;
		int32 numOfColumns;
		bool16 applyColumnGutter;
		PMReal columnGutter;

	} ApplyData;


	enum { kDefaultIID = IID_ICJKGRIDSUITE };

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
	
	/**  CanApplyCJKGrid is used to determine if an ICJKGrid can be applied in current context.
		@return kTrue if an ICJKGrid can be applied.
	*/
	virtual bool16 CanApplyCJKGrid( ) const = 0;
	
	/**  ApplyCJKGrid applies the story's ICJKGrid to the selected text.
		@precondition DESCRIPTION
		@return kSuccess on success or applicable ErrorCode on failure.
	*/
	virtual ErrorCode ApplyCJKGrid( ) = 0;

	/**  GetFrameGridView is used to determine the ICJKFrameGridDefaults::View for the current frame grids.
		@param frameGridViewVector OUT The vector for adding view values to.
		@param  sortedAndUnique IN If kTrue the vectors will be sorted and duplicates will be removed.
	*/
	virtual void GetFrameGridView(K2Vector<ICJKFrameGridDefaults::View> & frameGridViewVector, bool16 sortedAndUnique = kFalse ) const = 0;
	
	/**  SetFrameGridView sets the frame grid view for the selected frame grids.
		@param frameGridViewVector IN The new ICJKFrameGridDefaults::View.
	*/
	virtual ErrorCode SetFrameGridView( ICJKFrameGridDefaults::View view ) = 0;

	/**  Returns the location of the selected character counts or defaults if no selection.  
		@return Will return ICJKCharCountOptions::kMixed in mixed mode
	*/
	virtual ICJKCharCountOptions::Location GetCharCountLocation() const = 0;
	
	/**  Returns the size of the selected character counts or defaults if no selection.  
		@return Will return a negative value in mixed mode
	*/
	virtual PMReal GetCharacterCountSize() const =0;
	
	/**  Sets the character count location and size for the current selection.
		@param  location IN The new location of the character counts.  Pass kMixed to leave items unchanged (as in mixed mode).
		@param size IN The new size of the character count for the current selection.   Pass a negative value to leave it unchanged.
	*/
	virtual ErrorCode SetCharacterCountOptions(ICJKCharCountOptions::Location location , const PMReal & size ) = 0;

	/**  ShouldEnablePasteWithoutCJKGrid is used to determine if it is applicable to paste without a CJKGrid applied to the text.
		@return kTrue if the context is correct for pasting without a CJKGrid
	*/
	virtual bool16 ShouldEnablePasteWithoutCJKGrid( ) const = 0;

	/**  GetActiveNamedGrid is used to determine the current named grid.
		@return A valid UID if and only if there is exactly one named grid selected.
	*/
	virtual UID GetActiveNamedGrid() const = 0;
	
	/**  ApplyNamedGrid applies the designated namedGrid to the current selection.
		@param namedGrid IN The new named grid.
		@return kSuccess on success or applicable ErrorCode on failure.
	*/
	virtual ErrorCode ApplyNamedGrid(UID namedGrid) = 0;

	/**  ShouldEnableFrameGrid is used to determine if frame grid settings can be modified in the current context
		@return kTrue if applicable
	*/
	virtual bool16 ShouldEnableFrameGrid( ) const = 0;
	
	/**  IsFrameGridDefaults is used to determine if we are operating in defaults mode.
		@return kTrue if this is defaults mode.
	*/
	virtual bool16 IsFrameGridDefaults( ) const = 0;
	
	/**  GetFilteredGridData is used to gather the ICJKGridData for the current selection.  Mixed fields are set invalid.
		@param  filteredGridData OUT The resulting grid data.
	*/
	virtual void GetFilteredGridData( IFilteredCJKGridCmdData * filteredGridData ) const = 0;
	
	/**  GetLinesAndCharsPerLine is used to get ICJKGrid line and character counts for current selection.
		@param numberOfLinesVector OUT The vector to add the number of lines for each selected item.
		@param charsPerLineVector INOUT The vector to add the chars per line for each selected item.
		@param  sortedAndUnique IN If kTrue the vectors will be sorted and duplicates will be removed.
	*/
	virtual void GetLinesAndCharsPerLine(K2Vector<int32> & numberOfLinesVector, K2Vector<int32> & charsPerLineVector, bool16 sortedAndUnique = kFalse ) const = 0;
	
	/**  ApplyFrameGrid is used to apply settings to currently selected frame grids.
		@param filteredGridData IN The IFilteredCJKGridCmdData to apply to frame grids.
		@param applyData IN Structure containing flags and values for the different areas you can apply.
		@param applyGridView IN kTrue if you want to apply gridView.
		@param gridView IN The ICJKFrameGridDefaults::View to apply to the selection.
		@param charCountLocation IN The ICJKCharCountOptions::Location to apply to the selection.  Pass in ICJKCharCountOptions::kMixed to leave the item unchanged.
		@param charCountSize IN The new size of the character count.  Pass in a number <= 0 leaves the item unchanged.
		@return ErrorCode from resulting commands.  kSuccess on success.
	*/
	virtual ErrorCode ApplyFrameGrid	(IFilteredCJKGridCmdData * filteredGridData, 
										ApplyData applyData, 
										bool16 applyGridView, 
										ICJKFrameGridDefaults::View gridView,
										ICJKCharCountOptions::Location charCountLocation,
										const PMReal & charCountSize
										) = 0;
	
	/**  GetFrameSizeInfo is used to get the frame grid size info for the current selection when the
		 if the modifications in filteredGridData and applyData are made.
		@param outString OUT The resulting size info is saved here.
		@param filteredGridData IN The IFilteredCJKGridCmdData to apply to frame grids.
		@param applyData IN Structure containing flags and values for the different areas you can apply.
	*/
	virtual void GetFrameSizeInfo	( PMString & outString,
									IFilteredCJKGridCmdData * filteredGridData, 
									ApplyData applyData
									) = 0;

};

#endif

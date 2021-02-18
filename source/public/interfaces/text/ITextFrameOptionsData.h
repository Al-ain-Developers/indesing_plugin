//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextFrameOptionsData.h $
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
#ifndef __ITextFrameOptionsData__
#define __ITextFrameOptionsData__

#include "IPMUnknown.h"
#include "Utils.h"

#include "TextID.h"		// IID_ITEXTFRAMEDIALOGOPTIONSDATA
#include "ITextInset.h"		// bits
#include "CTextEnum.h"
#include "IBaselineFrameGridData.h"
#include "ICompositionStyle.h"
#include "IReferencePointData.h"
#include "IVerticalColumnRuleData.h"

class PMRect;
class UIDList;
class ITextInset;

/**
	Usage:
		This object works off a state variable.  The states are as follows:
			unInitialized -> add-in -> update

			unInitialized is the state between construction and the first item being incorporated
			add-in is the state when items are being incorporated
			update is the state after all items have been incorporated (and the dialog is shown).

		Basically, when initializing the dialog, use the AddInXXX methods
					when the dialog is open, use the UpdateXXX methods

	Dialog constructed:
		When initializing (the dialog), the caller should call the InitXXX methods.
			Not only does this set the value of that option, but it also sets internal state for later on.

	SelectionSuite processing:
		When incorporating the selection, each (applicable) selected item is incorporated into the object.

	Dialog open:
		When the user updates a field in the dialog, the handler should call the UpdateXXX methods.
			Not only does this set the value of that option, but it also updates internal state.

	@note unInitialized is private - it should never been seen by clients
 */
class ITextFrameOptionsData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTFRAMEDIALOGOPTIONSDATA };

	/** Call this to initialize the data from the list of objects (the selection).
	* Return kTrue if any multicolumn objects are in the list, kFalse otherwise.
	*/
	virtual bool16	ProcessTextFrameOptions(UIDList& mcfList) = 0;

	/** Call this when the dialog is created (before anything else).
	*/
	virtual void Reset() = 0;

	/** Resets the data to match anothers.
	*/
	virtual void ResetToOther(ITextFrameOptionsData *other) = 0;

	/** Some fields depend on other fields and for auto-calculation, we need to know if preview is on or not.
	*/
	virtual bool16	GetPreviewMode() const = 0;
	/** Some fields depend on other fields and for auto-calculation, we need to know if preview is on or not.
	*/
	virtual void	SetPreviewMode(bool16 newState) = 0;

	/** Prior to Basil we always fired the equivalent command for every change
		even though the change itself might be the same as the targets. This
		had the undesirable side effect for things such as ObjectStyles which
		might have had the the same values but firing the underlying command
		would create an unwanted override if it was an overriden masterpage
		item.
		@note work in progress, only insets and column width, gutter and fixed support this.
		@return kTrue if the underlying commands should be fired for targets which already have the desired values, kFalse otherwise.
	*/
	virtual bool16	GetForceRedundant() const = 0;

	/** SelectionTypes: the entire selection can be composed of differing objects.  All we care about is whether anything is selected
			and, if so, are they homogenous or not and if the former, the type.
	*/
	enum SelectionTypes { allRectangles, allNonRectangles, mixedOrUnsupported, nothing };

	/** OptionState: The state of a option. Values are as follows:
			unInitialized:	no value set - invalid (clients should treat as opaque)
			mixedValues:	due to the selection, this option does not have a value that can be displayed.
				This is the default state, so if you forget to call an Init method, you cannot set that value.
			unChanged:		the value in the dialog has never been changed - it still matches the selection, no matter how the dialog is closed/used.
			changed:		the value in the dialog was at one time changed.
		The attribute values should not be accessed if the state is "unInitialized" or "mixedValues"
		@note The "unInitialized" state should never be seen once all the selected objects have been incorporated into the data.
	 */
	enum OptionState { unInitialized, mixedValues, unChanged, changed };

	/** EachInsetState: The location of the state bits for the individual inset values.
	 */
	enum EachInsetState {
			LeftInvalid = ITextInset::kLeft,
			TopInvalid = ITextInset::kTop,
			RightInvalid = ITextInset::kRight,
			BottomInvalid = ITextInset::kBottom,
			LeftChanged = ITextInset::kLeft<<4,
			TopChanged = ITextInset::kTop<<4,
			RightChanged = ITextInset::kRight<<4,
			BottomChanged = ITextInset::kBottom<<4
	};

	// Columns
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetNumberOfColumnsState() const = 0;
	/** Call this method to determine whether or not the Column Width can be displayed in the UI.

			@note This check is in addition to the state check. The state can be valid, but not displayable.
	*/
	virtual bool16	GetColumnWidthIsDisplayable() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual int32			GetNumberOfColumns() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInNumberOfColumns(int32 numberOfColumns) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateNumberOfColumns(int32 numberOfColumns) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetUseFixedWidthColumnsState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual bool16			GetUseFixedWidthColumns() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInUseFixedWidthColumns(bool16 useFixedWidthColumns) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateUseFixedWidthColumns(bool16 useFixedWidthColumns) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetColumnWidthState() const = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual PMReal		GetColumnWidth() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInColumnWidth(PMReal columnWidth) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateColumnWidth(PMReal columnWidth) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetUseFlexibleWidthColumnsState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual bool16			GetUseFlexibleWidthColumns() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInUseFlexibleWidthColumns(bool16 useFlexibleWidthColumns) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateUseFlexibleWidthColumns(bool16 useFlexibleWidthColumns) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetFlexibleColumnWidthMaxState() const = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual PMReal		GetFlexibleColumnWidthMax() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInFlexibleColumnWidthMax(PMReal flexibleColumnWidthMax) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateFlexibleColumnWidthMax(PMReal flexibleColumnWidthMax) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetGutterWidthState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual PMReal		GetGutterWidth() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInGutterWidth(PMReal gutterWidth) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateGutterWidth(PMReal gutterWidth) = 0;

	// VJ
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetVerticalJustifyState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual Text::VerticalJustification	GetVerticalJustify() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInVerticalJustify(Text::VerticalJustification verticalJustify) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateVerticalJustify(Text::VerticalJustification verticalJustify) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetMaxVJInterParaSpaceState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual PMReal		GetMaxVJInterParaSpace() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInMaxVJInterParaSpace(PMReal maxVJInterParaSpace) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateMaxVJInterParaSpace(PMReal maxVJInterParaSpace) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetVJBalanceColumnsState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual bool16		GetVJBalanceColumns() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInVJBalanceColumns(bool16 vjBalanceColumns) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateVJBalanceColumns(bool16 vjBalanceColumns) = 0;

	// FLO
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetFirstLineOffsetState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual Text::FirstLineOffsetMetric	GetFirstLineOffset() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInFirstLineOffset(Text::FirstLineOffsetMetric firstLineOffset) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateFirstLineOffset(Text::FirstLineOffsetMetric firstLineOffset) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetMinFirstLineOffsetState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual PMReal		GetMinFirstLineOffset() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInMinFirstLineOffset(PMReal minFirstLineOffset) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateMinFirstLineOffset(PMReal minFirstLineOffset) = 0;

	// Misc
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState		GetIgnoreWrapState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual bool16				GetIgnoreWrap() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void				AddInIgnoreWrap(bool16 ignoreWrap) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void				UpdateIgnoreWrap(bool16 ignoreWrap) = 0;

	/**
		There are 3 cases for insets:
		1) If no selection or the selection is all rectangles, then each side
				of the rectangle can have a seperate inset.  In this case, the PMRect reflects accordingly.
		2) If the selection is all (or a single) non-rectangles, then only a single inset applies to all sides. In this case,
				the Top() value of the PMRect is valid (although all the fields are == Top, for convenience).
				@note The GetIndividualInsetsInvalidity() does not treat the other fields as valid - only the Top is valid for it.
		3) If the selection is mixed rectangles and not, then all fields are invalid.

		The above 3 states are represented by GetSelectionType();

	 	Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".

		@param eachInset:  if non-nil, the bits within will indicate whether each inset is valid/invalid, or changed/unChanged.
			Treat the same as if Get*State was called for each inset.  See EachInsetState for bit locations.
	*/
	virtual OptionState	GetInsetsState(int32 *eachInset = nil) const = 0;
	/**
		There are 3 cases for insets:
		1) If no selection or the selection is all rectangles, then each side
				of the rectangle can have a seperate inset.  In this case, the PMRect reflects accordingly.
		2) If the selection is all (or a single) non-rectangles, then only a single inset applies to all sides. In this case,
				the Top() value of the PMRect is valid (although all the fields are == Top, for convenience).
				@note The GetIndividualInsetsInvalidity() does not treat the other fields as valid - only the Top is valid for it.
		3) If the selection is mixed rectangles and not, then all fields are invalid.

		The above 3 states are represented by GetSelectionType();

		The Get* methods return the current value of the attribute.
	*/
	virtual PMRect		GetInsets() const = 0;
	/**
		There are 3 cases for insets:
		1) If no selection or the selection is all rectangles, then each side
				of the rectangle can have a seperate inset.  In this case, the PMRect reflects accordingly.
		2) If the selection is all (or a single) non-rectangles, then only a single inset applies to all sides. In this case,
				the Top() value of the PMRect is valid (although all the fields are == Top, for convenience).
				@note The GetIndividualInsetsInvalidity() does not treat the other fields as valid - only the Top is valid for it.
		3) If the selection is mixed rectangles and not, then all fields are invalid.

		The above 3 states are represented by GetSelectionType();

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInInsets(PMRect insets) = 0;
	/**
		There are 3 cases for insets:
		1) If no selection or the selection is all rectangles, then each side
				of the rectangle can have a seperate inset.  In this case, the PMRect reflects accordingly.
		2) If the selection is all (or a single) non-rectangles, then only a single inset applies to all sides. In this case,
				the Top() value of the PMRect is valid (although all the fields are == Top, for convenience).
				@note The GetIndividualInsetsInvalidity() does not treat the other fields as valid - only the Top is valid for it.
		3) If the selection is mixed rectangles and not, then all fields are invalid.

		The above 3 states are represented by GetSelectionType();

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateInsetLeft(PMReal left) = 0;
	/**
		There are 3 cases for insets:
		1) If no selection or the selection is all rectangles, then each side
				of the rectangle can have a seperate inset.  In this case, the PMRect reflects accordingly.
		2) If the selection is all (or a single) non-rectangles, then only a single inset applies to all sides. In this case,
				the Top() value of the PMRect is valid (although all the fields are == Top, for convenience).
				@note The GetIndividualInsetsInvalidity() does not treat the other fields as valid - only the Top is valid for it.
		3) If the selection is mixed rectangles and not, then all fields are invalid.

		The above 3 states are represented by GetSelectionType();

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateInsetTop(PMReal top) = 0;
	/**
		There are 3 cases for insets:
		1) If no selection or the selection is all rectangles, then each side
				of the rectangle can have a seperate inset.  In this case, the PMRect reflects accordingly.
		2) If the selection is all (or a single) non-rectangles, then only a single inset applies to all sides. In this case,
				the Top() value of the PMRect is valid (although all the fields are == Top, for convenience).
				@note The GetIndividualInsetsInvalidity() does not treat the other fields as valid - only the Top is valid for it.
		3) If the selection is mixed rectangles and not, then all fields are invalid.

		The above 3 states are represented by GetSelectionType();

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateInsetRight(PMReal right) = 0;
	/**
		There are 3 cases for insets:
		1) If no selection or the selection is all rectangles, then each side
				of the rectangle can have a seperate inset.  In this case, the PMRect reflects accordingly.
		2) If the selection is all (or a single) non-rectangles, then only a single inset applies to all sides. In this case,
				the Top() value of the PMRect is valid (although all the fields are == Top, for convenience).
				@note The GetIndividualInsetsInvalidity() does not treat the other fields as valid - only the Top is valid for it.
		3) If the selection is mixed rectangles and not, then all fields are invalid.

		The above 3 states are represented by GetSelectionType();

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateInsetBottom(PMReal bottom) = 0;
	/**
		There are 3 cases for insets:
		1) If no selection or the selection is all rectangles, then each side
				of the rectangle can have a seperate inset.  In this case, the PMRect reflects accordingly.
		2) If the selection is all (or a single) non-rectangles, then only a single inset applies to all sides. In this case,
				the Top() value of the PMRect is valid (although all the fields are == Top, for convenience).
				@note The GetIndividualInsetsInvalidity() does not treat the other fields as valid - only the Top is valid for it.
		3) If the selection is mixed rectangles and not, then all fields are invalid.

		The above 3 states are represented by GetSelectionType();

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateInsets(PMRect insets) = 0;

	/**
		Return which insets are NOT valid.
		e.g. returns ITextInset::kLeft | kTop | kRight | kBottom  if all of those fields are mixedValues or otherwise invalid.
	*/
	virtual int32			GetIndividualInsetsInvalidity() const = 0;

	/**
		Internal state - used only by active dialog

		This method is used by the dialog when the user changes the (column) width attribute.
	*/
	virtual bool16			UserChangedWidth() const = 0;
	/**
		Internal state - used only by active dialog

		This method is used by the dialog when the user changes the (column) width attribute.
	*/
	virtual void			SetUserChangedWidth(bool16 changed) = 0;

	/**
		Internal state - not used by active dialog

		This method is used during dialog set up to determine the VJ and selection states.
	*/
	virtual SelectionTypes	GetSelectionType() const = 0;
	/**
		Internal state - not used by active dialog

		This method is used during dialog set up to determine the VJ and selection states.
	*/
	virtual void				AddInSelectionType(SelectionTypes selectionType) = 0;

	//**************************
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetUseCustomBaselineGridFlagState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual bool16		GetUseCustomBaselineGridFlag() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInUseCustomBaselineGridFlag(bool16 flag) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateUseCustomBaselineGridFlag(bool16 flag) = 0;

	// FLO
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetRelativeOptionState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual IBaselineFrameGridData::RelativeOption	GetRelativeOption() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInRelativeOption(IBaselineFrameGridData::RelativeOption relativeOption) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateRelativeOption(IBaselineFrameGridData::RelativeOption relativeOption) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetStartingOffsetState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual PMReal		GetStartingOffset() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInStartingOffset(PMReal staringOffset) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateStartingOffset(PMReal staringOffset) = 0;

	// Misc
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState		GetIncrementState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual PMReal				GetIncrement() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void				AddInIncrement(PMReal increment) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void				UpdateIncrement(PMReal increment) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState		GetBaselineFrameGridColorState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual UID				GetBaselineFrameGridColor() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void				AddInBaselineFrameGridColor(UID colorUID) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void				UpdateBaselineFrameGridColor(UID colorUID) = 0;

	/** Call this to initialize the data from the list of objects (the selection).
	* Return kTrue if any multicolumn objects are in the list, kFalse otherwise.
	  @bool	convertColorUIDToLayerColor	true if you want the actualy color that will be displayed, false means if you are using the layer color it will return kInvalidUID
	*/
	virtual bool16	ProcessBaselineFrameGridOptions(UIDList& mcfList, bool16 convertColorUIDToLayerColor) = 0;

	// AS
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetAutoSizeDimensionState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual Text::AutoSizeDimension	GetAutoSizeDimension() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInAutoSizeDimension(Text::AutoSizeDimension autoSizeDimension) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateAutoSizeDimension(Text::AutoSizeDimension autoSizeDimension) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetAutoSizeRefPointState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual IReferencePointData::ReferencePointPosition	GetAutoSizeRefPoint() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInAutoSizeRefPoint(IReferencePointData::ReferencePointPosition autoSizeRefPoint) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateAutoSizeRefPoint(IReferencePointData::ReferencePointPosition autoSizeRefPoint) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetAutoSizeHasMinHeightState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual bool16	GetAutoSizeHasMinHeight() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInAutoSizeHasMinHeight(bool16 autoSizeHasMinHeight) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateAutoSizeHasMinHeight(bool16 autoSizeHasMinHeight) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetAutoSizeMinHeightValueState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual PMReal	GetAutoSizeMinHeightValue() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInAutoSizeMinHeightValue(PMReal autoSizeMinHeightValue) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateAutoSizeMinHeightValue(PMReal autoSizeMinHeightValue) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState		GetAutoSizeHasMinWidthState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual bool16			GetAutoSizeHasMinWidth() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInAutoSizeHasMinWidth(bool16 autoSizeHasMinWidth) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateAutoSizeHasMinWidth(bool16 autoSizeHasMinWidth) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState		GetAutoSizeMinWidthValueState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual PMReal			GetAutoSizeMinWidthValue() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInAutoSizeMinWidthValue(PMReal autoSizeMinWidthValue) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateAutoSizeMinWidthValue(PMReal autoSizeMinWidthValue) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.
		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetAutoSizeNoLineBreakState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual bool16	GetAutoSizeNoLineBreak() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInAutoSizeNoLineBreak(bool16 autoSizeNoLineBreak) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateAutoSizeNoLineBreak(bool16 autoSizeNoLineBreak) = 0;
	// Text Frame Footnotes section

	/** Call this method when the dialog is created (before anything else) for the  attribute.
		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetFootnoteOptionsHasEnableOverridesState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual bool16	GetFootnoteOptionsHasEnableOverrides() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void AddInFootnoteOptionsHasEnableOverrides(bool16 enableOverrides) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void UpdateFootnoteOptionsHasEnableOverrides(bool16 enableOverrides) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.
		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetFootnoteOptionsHasSpanFootnotesAcrossState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual bool16	GetFootnoteOptionsHasSpanFootnotesAcross() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void AddInFootnoteOptionsHasSpanFootnotesAcross(bool16 spanFootnotesAcross) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void UpdateFootnoteOptionsHasSpanFootnotesAcross(bool16 spanFootnotesAcross) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.
		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetFootnoteOptionsMinimumSpacingValueState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual PMReal	GetFootnoteOptionsMinimumSpacingValue() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void AddInFootnoteOptionsMinimumSpacingValue(PMReal minimumSpacing) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void UpdateFootnoteOptionsMinimumSpacingValue(PMReal minimumSpacing) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.
		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetFootnoteOptionsSpaceBetweenFootnotesValueState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual PMReal GetFootnoteOptionsSpaceBetweenFootnotesValue() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void AddInFootnoteOptionsSpaceBetweenFootnotesValue(PMReal spaceBetweenFootnotes) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void UpdateFootnoteOptionsSpaceBetweenFootnotesValue(PMReal spaceBetweenFootnotes) = 0;
	/** Call this to initialize the data from the list of objects (the selection).
	* Return kTrue if any multicolumn objects are in the list, kFalse otherwise.
	*/
	virtual bool16	ProcessTextFrameFootnoteOptions(UIDList& mcfList) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetUseVerticalRuleState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual bool16			GetUseVerticalRule() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInUseVerticalRule(bool16 useVerticalRule) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateUseVerticalRule(bool16 useVerticalRule) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetVerticalRuleOffsetState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual PMReal			GetVerticalRuleOffset() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInVerticalRuleOffset(PMReal verticalRuleOffset) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateVerticalRuleOffset(PMReal verticalRuleOffset) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetVerticalRuleTopInsetState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual PMReal			GetVerticalRuleTopInset() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInVerticalRuleTopInset(PMReal verticalRuleTopInset) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateVerticalRuleTopInset(PMReal verticalRuleTopInset) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual OptionState			GetVerticalRuleInsetChainState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInVerticalRuleInsetChain(bool16 isChained) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateVerticalRuleInsetChain(bool16 isChained) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual bool16			GetVerticalRuleInsetChain() const = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
	@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetVerticalRuleBottomInsetState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual PMReal			GetVerticalRuleBottomInset() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInVerticalRuleBottomInset(PMReal verticalRuleBottomInset) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateVerticalRuleBottomInset(PMReal verticalRuleBottomInset) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
	@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetVerticalRuleStrokeWidthState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual PMReal			GetVerticalRuleStrokeWidth() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInVerticalRuleStrokeWidth(PMReal verticalRuleStrokeWidth) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateVerticalRuleStrokeWidth(PMReal verticalRuleStrokeWidth) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get*State method is used to determine whether the other methods can be called - @see OptionState
			@note for convenience, if the state is "unInitialized" the method returns "mixedValues".
	*/
	virtual OptionState	GetVerticalRuleStrokeColorState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual UID			GetVerticalRuleStrokeColor() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInVerticalRuleStrokeColor(UID verticalRuleStrokeColorUID) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateVerticalRuleStrokeColor(UID verticalRuleStrokeColorUID) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual OptionState			GetVerticalRuleStrokeTypeState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInVerticalRuleStrokeType(ICompositionStyle::StrokeType verticalRuleStrokeType) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateVerticalRuleStrokeType(ICompositionStyle::StrokeType verticalRuleStrokeType) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual ICompositionStyle::StrokeType			GetVerticalRuleStrokeType() const = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual OptionState			GetVerticalRuleTintState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInVerticalRuleTint(PMReal tint) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateVerticalRuleTint(PMReal tint) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual PMReal			GetVerticalRuleTint() const = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual OptionState			GetVerticalRuleOverprintState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInVerticalRuleOverprint(bool16 isOverprint) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateVerticalRuleOverprint(bool16 isOverprint) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual bool16			GetVerticalRuleOverprint() const = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual OptionState			GetVerticalRuleHeightModeState() const = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The AddIn* method is used during dialog set up to add that attribute to the accumulated state for each object selected.
	*/
	virtual void			AddInVerticalRuleHeightMode(IVerticalColumnRuleData::VerticalRuleHeightMode verticalRuleHeightMode) = 0;
	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Update* method is used during dialog activation to indicate the user has updated that attribute.
	*/
	virtual void			UpdateVerticalRuleHeightMode(IVerticalColumnRuleData::VerticalRuleHeightMode verticalRuleHeightMode) = 0;

	/** Call this method when the dialog is created (before anything else) for the  attribute.

		The Get* methods return the current value of the attribute.
	*/
	virtual IVerticalColumnRuleData::VerticalRuleHeightMode			GetVerticalRuleHeightMode() const = 0;

	/** Call this to initialize the data from the list of objects (the selection)
	Return kTrue if any multicolumn objects are in the list, kFalse otherwise.
	*/
	virtual bool16			ProcessTextFrameVerticalRuleOptions(UIDList& mcfList) = 0;


};

#endif // __ITextFrameOptionsData__

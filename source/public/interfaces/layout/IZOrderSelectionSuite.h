//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IZOrderSelectionSuite.h $
//  
//  Owner: Michael Martz
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
	#ifndef _IZORDERSELECTIONSUITE_
	#define _IZORDERSELECTIONSUITE_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	#include "ShuksanID.h"
	#include "IPMUnknown.h"
	#include "PMRect.h"
	#include "PMTypes.h"
	#include "ISelectionMessages.h"
	#include "IActionManager.h"	// For kInvalidMousePoint

class IControlView;

/** Enum values for SelectSibling below */
typedef enum { 
		/** Select left one item in a group (will wrap around when beginning of group is reached) */
		kLeftDirection = 0, 
		/** Select right one item in a group (will wrap around when end of group is reached) */
		kRightDirection = 1,
		/** Select left five items in a group. Used when Shift key is pressed. */
		kLeftDirectionx5 = 2,
		/** Select right five items in a group. Used when Shift key is pressed. */
		kRightDirectionx5 = 3,
		/** Select extreme right group item (item index numGroupItems - 1). Used when Command/Ctrl key is pressed. */
		kExtremeLeftDirection = 4, 
		/** Select extreme left group item (item index 0). Used when Command/Ctrl key is pressed. */
		kExtremeRightDirection = 5 } 
	SelectDirection;

//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________

/** Suite interface for working with z-ordering of page items.
	@ingroup layout_suite
*/
class IZOrderSelectionSuite : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IZORDERSELECTIONSUITE };

		/**	Can we  select forward an item based on current item(s) selection?
			@param view - Control View that the point and rect are in 
			@param replaceOrAdd - Selection::kReplace or Selection::kAddTo
			@param thePoint - point in pasteboard coordinates to use for selecting, kInvalidPoint to ignore
			@param rect - rect in pb coordinates to use for selecting, kEmptyRect to ignore
			@return bool16 - kTrue if action is enabled, kFalse if disabled
		 */
		virtual bool16 CanSelectForward(IControlView* view, Selection::Action replaceOrAdd, const PMPoint& point, const PMRect& rect = kEmptyRect) const = 0;

		/**	Can we select backward an item based on current item(s) selection?
			@param view - Control View that the point and rect are in 
			@param replaceOrAdd - Selection::kReplace or Selection::kAddTo
			@param thePoint - point in pasteboard coordinates to use for selecting, kInvalidPoint to ignore
			@param rect - rect in pb coordinates to use for selecting, kEmptyRect to ignore
			@return bool16 - kTrue if action is enabled, kFalse if disabled
		 */
		virtual bool16	CanSelectBackward(IControlView* view, Selection::Action replaceOrAdd, const PMPoint& point, const PMRect& rect = kEmptyRect) const = 0;

		/**	Can we select frontmost item item based on current item(s) selection?
			@param view - Control View that the point and rect are in 
			@param replaceOrAdd - Selection::kReplace or Selection::kAddTo
			@param thePoint - point in pasteboard coordinates to use for selecting, kInvalidPoint to ignore
			@param rect - rect in pb coordinates to use for selecting, kEmptyRect to ignore
			@return bool16 - kTrue if action is enabled, kFalse if disabled
		 */
		virtual bool16	CanSelectFront(IControlView* view, Selection::Action replaceOrAdd, const PMPoint& point, const PMRect& rect = kEmptyRect) const = 0;

		/**	Can we select backmost item item based on current item(s) selection?
			@param view - Control View that the point and rect are in 
			@param replaceOrAdd - Selection::kReplace or Selection::kAddTo
			@param thePoint - point in pasteboard coordinates to use for selecting, kInvalidPoint to ignore
			@param rect - rect in pb coordinates to use for selecting, kEmptyRect to ignore
			@return bool16 - kTrue if action is enabled, kFalse if disabled
		 */
		virtual bool16	CanSelectBack(IControlView* view, Selection::Action replaceOrAdd, const PMPoint& point, const PMRect& rect = kEmptyRect) const = 0;

		/**	Can we select parent based on current item(s) selection?
			@param view - Control View to use
			@return bool16 - kTrue if action is enabled, kFalse if disabled
		 */
		virtual bool16	CanSelectParent(IControlView* view) const = 0;

		/**	Can we select child content based on current item(s) selection?
			@param view - Control View to use
			@return bool16 - kTrue if action is enabled, kFalse if disabled
		 */
		virtual bool16	CanSelectChild(IControlView* view) const = 0;

		/**	Can we select a sibling item based on current item selection? (selection of length 0 or 1). This is a select next/previous operation at a particular level of the hierarchy.
			@param view - Control View to use
			@param direction - Select either to the left or the right of current selection.
			@return bool16 - kTrue if action is enabled, kFalse if disabled
		 */
		virtual bool16	CanSelectSibling(IControlView* view, SelectDirection direction) const = 0;

		/**	Select forward an item based on current item(s) selection. If no items selected, select frontmost item in hierarchy.
			If the point is not kInvalidMousePoint, use only selected items intesecting this point, not all selected items.
			@param view - Control View that the point and rect are in 
			@param replaceOrAdd - Selection::kReplace or Selection::kAddTo
			@param thePoint - point in pasteboard coordinates to use for selecting, kInvalidPoint to ignore
			@param rect - rect in pb coordinates to use for selecting, kEmptyRect to ignore
			@return ErrorCode - Did this succeed?
		 */
		virtual ErrorCode	SelectForward(IControlView* view, Selection::Action replaceOrAdd, const PMPoint& point, const PMRect& rect = kEmptyRect) const = 0;

		/**	Select backward an item based on current item(s) selection. If no items selected, select backmost item in hierarchy.
			If the point is not kInvalidMousePoint, use only selected items intesecting this point, not all selected items.
			@param view - Control View that the point and rect are in 
			@param replaceOrAdd - Selection::kReplace or Selection::kAddTo
			@param thePoint - point in pasteboard coordinates to use for selecting, kInvalidPoint to ignore
			@param rect - rect in pb coordinates to use for selecting, kEmptyRect to ignore
			@return ErrorCode - Did this succeed?
		 */
		virtual ErrorCode	SelectBackward(IControlView* view, Selection::Action replaceOrAdd, const PMPoint& point, const PMRect& rect = kEmptyRect) const = 0;

		/**	Select frontmost item item based on current item(s) selection. If no items selected, select frontmost item in hierarchy.
			If the point is not kInvalidMousePoint, use only selected items intesecting this point, not all selected items.
			@param view - Control View that the point and rect are in 
			@param replaceOrAdd - Selection::kReplace or Selection::kAddTo
			@param thePoint - point in pasteboard coordinates to use for selecting, kInvalidPoint to ignore
			@param rect - rect in pb coordinates to use for selecting, kEmptyRect to ignore
			@return ErrorCode - Did this succeed?
		 */
		virtual ErrorCode	SelectFront(IControlView* view, Selection::Action replaceOrAdd, const PMPoint& point, const PMRect& rect = kEmptyRect) const = 0;

		/**	Select backmost item item based on current item(s) selection. If no items selected, select backmost item in hierarchy.
			If the point is not kInvalidMousePoint, use only selected items intesecting this point, not all selected items.
			@param view - Control View that the point and rect are in 
			@param replaceOrAdd - Selection::kReplace or Selection::kAddTo
			@param thePoint - point in pasteboard coordinates to use for selecting, kInvalidPoint to ignore
			@param rect - rect in pb coordinates to use for selecting, kEmptyRect to ignore
			@return ErrorCode - Did this succeed?
		 */
		virtual ErrorCode	SelectBack(IControlView* view, Selection::Action replaceOrAdd, const PMPoint& point, const PMRect& rect = kEmptyRect) const = 0;

		/**	Select parent of selection. Always does a Selection::kReplace.
			@param view - Control View that the point and rect are in 
			@return ErrorCode - Did this succeed?
		 */
		virtual ErrorCode	SelectParent(IControlView* view) const = 0;

		/**	Select child content of selection. Always does a Selection::kReplace.
			@param view - Control View that the point and rect are in 
			@return ErrorCode - Did this succeed?
		 */
		virtual ErrorCode	SelectChild(IControlView* view) const = 0;

		/**	Select a sibling item of current selection (of length 0 or 1). This is a select next/previous operation at a particular level of the hierarchy.
			@param view - Control View to use
			@param direction - Select either to the left or the right of current selection.
			@return ErrorCode - Did this succeed?
			@see SelectDirection enum
		 */
		virtual ErrorCode	SelectSibling(IControlView* view, SelectDirection direction) const = 0;
	};

#endif // _IZORDERSELECTIONSUITE_

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILayoutSelectionSuite.h $
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
//========================================================================================

#pragma once
	#ifndef _ILayoutSelectionSuite_
	#define _ILayoutSelectionSuite_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	#include "ShuksanID.h"
	#include "IPMUnknown.h"
	#include "ISelectionMessages.h"
//================================================================================================
//________________________________________________________________________________________________
//	CLASS FORWARDS
//________________________________________________________________________________________________
	class IHierarchy;
	class IControlView;
	
//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________
/** Suite interface for layout-related selections.
*/
class ILayoutSelectionSuite : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_ILAYOUTSELECTION_ISUITE };

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		/** @name Extending */
		//@{
		//	Methods for extending the selection

		/**	Select the specified item using the selectionMode.
			@param newItem the item to select.
			@param selectionMode how to select the item.
			@param doScroll how to scroll after the selection action.
		 */
//		virtual void 		SelectOne ( UID newItem, Selection::Action selectionMode, Selection::LayoutScrollChoice doScroll) = 0;

		/**	Select the list of specified items using the selectionMode.
			@param newItems the list of items to select.
			@param selectionMode how to select the items.
			@param doScroll how to scroll after the selection action.
		 */
		virtual void 		SelectPageItems (const UIDList& newItems, Selection::Action selectionMode, Selection::LayoutScrollChoice doScroll) = 0;

		/**	Select the specified items using the selectionMode and the targetting boss
			items from the targeting boss will be removed.
			@param targetingBoss the targetting boss containing IID_ILAYOUTTARGET
			@param selectionMode how to select the item.
			@param doScroll how to scroll after the selection action.
		 */
		virtual void 		SelectInTarget (IPMUnknown* targetingBoss, Selection::Action selectionMode, Selection::LayoutScrollChoice doScroll) = 0;

		/**	Select the specified items within the rectangle using the selectionMode.
			@param controlView the control view to do the selection in.
			@param rect the rect (in pasteboard coordinates) 
			@param selectionMode how to select the item.
			@param selectionType Specify the selection type (kSelect, kDirectSelect, etc.) to use when marquee selecting 
			@param deselectSelected Do we need to deselect the page items that are already selected?
			@param doScroll how to scroll after the selection action.
		 */
		virtual void 		SelectInView (IControlView* controlView, const PMRect& rect, Selection::Action selectionMode, int32 selectionType, bool16 deselectSelected, Selection::LayoutScrollChoice doScroll) = 0;

		/**	Select all the items in the given hierarchy.
			@param spreadHierarchy The top level of the hierarchy to determine where to start selecting from.
			@param specificLayerUID Filter items to a particular layer if not kInvalidUID 
			@param doScroll how to scroll after the selection action.
		 */
		virtual void 		SelectAllPageItems (IHierarchy* spreadHierarchy, UID specificLayerUID, Selection::LayoutScrollChoice doScroll) = 0;

		/**	Set the key object in the selection.
			@param keyObject The UIDRef of the object to serve as the key. This object must already be selected (unless clearing). Pass kInvalidUIDRef to clear key object.
		 */
		virtual void		SelectKeyObject(const UIDRef& keyObject) = 0;

		//@}

		/** @name Shrinking */
		//@{
		//  Methods for shrinking the selection

		/**	Deselect the specified items.
			@param itemsToDeselect 
		 */
		virtual void 		DeselectPageItems (const UIDList& itemsToDeselect) = 0;

		/**	Deselect any items in the selection which do not support the specified IID.
			@param id the PMIID of the items to keep in the selection
		 */
		virtual void 		DeselectPageItemsNotSupporting (const PMIID& id) = 0;

		/**	Deselect everything in the selection except the specified item.
			@param UID& 
		 */
		virtual void		DeselectAllExceptThisPageItem (const UID&) = 0;

		/**	Deselect everything in the selection.
			@param void 
		 */
		virtual void 		DeselectAllPageItems (void) = 0;

		//@}
	
		/**	@name Utilities
		 */

		//@{
		/**	Is the selection empty?
			@param void 
			@return bool16 return kTrue if selection is empty, kFalse otherwise.
		 */
		virtual bool16 		IsLayoutSelectionEmpty (void) const = 0;

		/**	Determine if a particular UID is contained in the current selection.
			@param UID& the UID of the item to look for in the selection.
			@return bool16 kTrue if this item is in the selection, kFalse otherwise.
		 */
		virtual bool16 		IsPageItemSelected (const UID&) const = 0;

		//@}
		virtual void 		SelectPageItemsInternal (const UIDList& newItems, Selection::Action selectionMode, Selection::LayoutScrollChoice doScroll, bool16) = 0;

	};


/**
*/
class ILayoutSelectionSuiteMsgData INHERITFROM
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum ActionType { kDeselectAll};
	
		/**	Return the action type for the message.
			@return ActionType 
		 */
		virtual ActionType	GetActionType (void) const = 0;

		/**	Return the draw it type for the message.
			@return  bool16
		 */
		virtual bool16	 	GetDrawIt (void) const = 0;
	};
	
#endif // _ILayoutSelectionSuite_
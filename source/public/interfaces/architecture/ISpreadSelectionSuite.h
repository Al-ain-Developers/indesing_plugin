//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISpreadSelectionSuite.h $
//  
//  Owner: ???
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#ifndef _ISpreadSelectionSuite_
#define _ISpreadSelectionSuite_

#include "ILayoutObject.h"
#include "IPMUnknown.h"
#include "ISelectionMessages.h"

#include "LayoutUIID.h"
#include "ShuksanID.h"

class IHierarchy;
class ISpread;
class IControlView;
	

class ISpreadSelectionSuite : public IPMUnknown
{

public:
	enum { kDefaultIID = IID_ISPREADSELECTION_ISUITE };


public:

	/**	Select the list of specified items using the selectionMode.
		@param newItems the list of items to select.
		@param selectionMode how to select the items.
		@param doScroll how to scroll after the selection action.
	 */
	virtual void SelectSpreadItems( const UIDList& newItems, Selection::Action selectionMode, Selection::LayoutScrollChoice doScroll) = 0;
//	virtual void SelectDocumentPages( page numbers, Selection::Action selectionMode, Selection::LayoutScrollChoice doScroll) = 0;
//	virtual void SelectSpreadPages( UIDRef spread, page indices, Selection::Action selectionMode, Selection::LayoutScrollChoice doScroll) = 0;
//	virtual void SelectDocumentSpreads( spread numbers, Selection::Action selectionMode, Selection::LayoutScrollChoice doScroll) = 0;

	/**	Select the specified items using the selectionMode and the targetting boss
		items from the targeting boss will be removed.
		@param targetingBoss the targetting boss containing IID_ILAYOUTTARGET
		@param selectionMode how to select the item.
		@param doScroll how to scroll after the selection action.
	 */
	virtual void SelectInTarget( IPMUnknown* targetingBoss, Selection::Action selectionMode, Selection::LayoutScrollChoice doScroll) = 0;

	/**	Select the specified items within the rectangle using the selectionMode.
		@param controlView the control view to do the selection in.
		@param rect the rect (in pasteboard coordinates) 
		@param selectionMode how to select the item.
		@param selectionType Specify the selection type (kSelect, kDirectSelect, etc.) to use when marquee selecting 
		@param deselectSelected Do we need to deselect the page items that are already selected?
		@param doScroll how to scroll after the selection action.
	 */
	virtual void SelectInView( IControlView* controlView, const PMRect& rect, Selection::Action selectionMode, int32 selectionType, bool16 deselectSelected, Selection::LayoutScrollChoice doScroll) = 0;

	/**	Select all the items in the given hierarchy.
		@param spreadHierarchy The top level of the hierarchy to determine where to start selecting from.
		@param specificLayerUID Filter items to a particular layer if not kInvalidUID 
		@param doScroll how to scroll after the selection action.
	 */
	virtual void SelectAllPages( ISpread* spread, Selection::LayoutScrollChoice doScroll) = 0;
	virtual void SelectAllSpreads( Selection::LayoutScrollChoice doScroll) = 0;


	/**	Set the key object in the selection.
	 @param keyObject The UIDRef of the object to serve as the key. This object must already be selected (unless clearing). Pass kInvalidUIDRef to clear key object.
	 */
	virtual void SelectKeyObject(const UIDRef& keyObject) = 0;

	/** Return a UIDRef for the key object in the selection. May return kInvalidUIDRef if there isn't one.
		@return UIDRef of the key object.
	 */
	virtual UIDRef GetSelectedKeyObject() const = 0;

	/**	Determine if a particular UID is set as the key object.
	 @param uidRef& the UIDRef of the key object in question.
	 @return bool16 kTrue if this item is the key object, kFalse otherwise.
	 */
	virtual bool16 IsKeyObjectSelected( const UIDRef& uidRef) const = 0;

	/**	Deselect the specified items.
		@param itemsToDeselect 
	 */
	virtual void DeselectSpreadItems( const UIDList& itemsToDeselect) = 0;


	/**	Deselect everything in the selection except the specified item.
		@param UID& 
	 */
	virtual void DeselectAllExceptThisSpreadItem( const UID&) = 0;

	/**	Deselect everything in the selection.
		@param void 
	 */
	virtual void DeselectAllSpreadItems() = 0;


	/**	Is the selection empty?
		@return bool16 return kTrue if selection is empty, kFalse otherwise.
	 */
	virtual bool16 IsSpreadSelectionEmpty() const = 0;

	/**	Determine if a particular UID is contained in the current selection.
		@param UID& the UID of the item to look for in the selection.
		@return bool16 kTrue if this item is in the selection, kFalse otherwise.
	 */
	virtual bool16 IsSpreadItemSelected( const UID&) const = 0;

	/** Return whether or not the current page selection has layout policies that allow the object constraints
		on the key object selection to be displayed.
	 */
	virtual bool32 CanShowObjectConstraints() const = 0;

	virtual UIDList GetSelectedItems() const = 0;
};


/**
*/
class ISpreadSelectionSuiteMsgData INHERITFROM
{
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
	
#endif // _ISpreadSelectionSuite_


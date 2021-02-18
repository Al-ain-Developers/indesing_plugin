//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISpreadDynamicContentMgr.h $
//  
//  Owner: SusanCL
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
#ifndef __ISpreadDynamicContentMgr__
#define __ISpreadDynamicContentMgr__

#include "DynamicDocumentsID.h"
#include "IPMUnknown.h"
#include "AnimationTypes.h"
#include "vector"

/**
	This is a persistent data interface to track InDesign dynamic content on the spread. 
	This interface sits on the spread boss. 
	Dynamic contents are page item with animation, media page items, button page items, and
	children of multi-state object page items. The media page items include movies, sound, and SWF's.

*/
class ISpreadDynamicContentMgr : public IPMUnknown
{	
public:

	enum { kDefaultIID = IID_ISPREADDYNAMICCONTENTMGR };

	/** This enum defines the types of dynamic content tracked here. */
	enum DynamicContentType {
		/** Indicate an invalid content type. */
		kInvalidContentType = 0,
		/** Indicate an animation item type. */
		kAnimationItemType,
		/** Indicate an sound item type. */
		kSoundItemType,
		/** Indicate an sound item type. */
		kMovieItemType,
		/** Indicate an multi-state item type. */
		kMultiStateItemType,
		/** Indicate an buttom item type. */
		kButtonItemType 
	};

	/** Returns the number of dynamic items on the spread.
		@return The number of dynamic items on the spread.
	*/
	virtual uint32 GetNumTargets() const = 0;

	/** Return true if page item is an dynamic content we care about and if this
		page item is on the spread.
		Currently we keep track of page item with animation, mso items, all media items (movies, swf, sounds, etc.)
		@param pageItemUID is the page item interested
		@return true if page item is an interactive content.
	*/
	virtual bool CanAddTarget (UID pageItemUID) = 0;

	/** Add this dynamic content item to be tracked for this spread.
		@param pageItemUID is the page item to track.
		@return true if successful; otherwise returns false.
	*/
	virtual bool AddTarget (UID pageItemUID) = 0;

	/** Remove the specified item from being tracked.
		@param pageItemUID is the page item to remove.
		@return true if successful; otherwise returns false.
	*/
	virtual bool RemoveTarget (UID pageItemUID) = 0;

	/** Returns the index of the pageItemUID in this list.
		@param pageItemUID is the UID of the target we are looking for.
		@return the index of the specified target UID in this list.
			index is set to -1 if pageItemUID is not in the list.
	*/
	virtual int32 FindTarget (UID pageItemUID) const = 0;

	/** Returns the nth dynamic target item.
		@param index is the index of the dynamic item being tracked for this spread.
		@return the item UID.
	*/
	virtual UID GetNthTarget (uint32 index) const = 0;

	/** Returns the nth dynamic target item's name.
		@param index is the index of the dynamic item being tracked for this spread.
		@param targetType is the target's type.
		@return true if successful; otherwise returns false.
	*/
	virtual DynamicContentType GetNthTargetType (uint32 index) const = 0;

	/** Returns true if nth target is also animated.
		@param index is the index of the dynamic item being tracked for this spread.
		@return true if target is also animated.
	*/
	virtual bool NthTargetIsAnimated (uint32 index) const = 0;

	/** Returns the nth dynamic target item's name.
		@param index is the index of the dynamic item being tracked for this spread.
		@param name is the target's name.
		@return true if successful; otherwise returns false.
	*/
	virtual bool GetNthTargetName (uint32 index, PMString& name) const = 0;

	/** Returns the all the items that are specified target type.
		@param targetType is the target type.
		@param itemList is the list of items of this type.
	*/
	virtual void GetItemsByTargetType (const DynamicContentType& targetType, std::vector<UID>& itemList) const = 0;
	
	/**	Buttons on this spread.
	*/

	/** Returns the number of buttons on the spread.
		@return The number of buttons on the spread.
	*/
	virtual uint32 GetNumButtons () const = 0;

	/** Add this button on the spread
		@param buttonUID is button to add.
		@return true if successful, otherwise false.
	*/
	virtual bool AddButton (UID buttonUID) = 0;

	/** Remove the nth button from the spread.
	*/
	virtual bool RemoveButton (UID buttonUID) = 0;

	/** Find the button index for the given button UID.
		@param buttonUID is the button UID.
		@return the button index. Returns -1 if this button UID is not in the list.
	*/
	virtual int32 FindButton (UID buttonUID) const = 0;

	/** Returns the nth button.
		@param index is the index of the button on the spread interested.
		@return the button UID for this index.
	*/
	virtual UID GetNthButton (uint32 index) const = 0;

	/** Returns the buttons on this spread.
		@param buttonList contains the buttons on the spread.
	*/
	virtual void GetButtons (std::vector<UID>& buttonList) const = 0;

	/** Returns a list of animated targets that are not assigned a trigger event.
		@param targetList contains the unassigned animated targets on the spread.
	*/
	virtual void GetUnassignedTargets (std::vector<UID>& targetList) const = 0;
};

#endif // __ISpreadDynamicContentMgr__

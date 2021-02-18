//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPlaceBehavior.h $
//  
//  Owner: 
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
#ifndef __IPlaceBehavior__
#define __IPlaceBehavior__

#include "IPMUnknown.h"

#include "ICursorMgr.h"
#include "IItemsToPlaceData.h"
#include "GenericID.h"
#include "PMPoint.h"
#include "ScriptData.h"

class ISpread;
class IControlView;

/** Interface used to determine how a place operation behaves over a particular target.
	Both the source (the content being placed) and the target (where the place occurs) 
	can implement their own behaviors.

	A base implementation is defined in CGraphicPlaceBehavior; most subclassers should start there.

	@see IPlaceBehaviorUI, CGraphicPlaceBehavior
*/
class IPlaceBehavior : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IPLACEBEHAVIOR};

	//----------------------------------------------------------------------------------------------
	// Source content methods
	//----------------------------------------------------------------------------------------------

	/** Optional actions to perform after the place completes. */ 
	enum eAfterPlace {
		/**  */
		kOldBehavior, 
		/**  */
		kLeaveAsIs, 
		/**  */
		kClearPlaceGun, 
		/**  */
		kAbortPlaceGun
	};

	/** Types of place given various UI gestures */
	enum ePlaceType {
		/**  */
		kPlaceSingle, 
		/**  */
		kPlaceCascade, 
		/**  */
		kPlaceMultiple
	};


	/** Perform a Place operation
		@param targetItem IN target for the place
		@param parent IN parent of the placed object(s)
		@param points IN location of the place
		@param finalModifiers IN modifier key state
		@param startingModifiers IN modifier key state
		@param spread IN spread where place is to occur
		@param afterPlace INOUT what should happen after the place (optional)
		@return UIDList of placed objects
	*/
	virtual UIDList		ProcessPlace(IPlaceBehavior* targetItem,  const UIDRef& parent, const PMPointList& points, 
										ICursorMgr::eCursorModifierState finalModifiers,
										ICursorMgr::eCursorModifierState startingModifiers,
										const ISpread* spread, eAfterPlace *afterPlace = nil,
										IItemsToPlaceData::ePlaceFrom placeFrom = IItemsToPlaceData::kPlaceGun) = 0;

	/** ProcessReplacePreserveState gives this a chance to set itself and srcRoot to values from target.
			Note: newItem may or may not be the same item as "this" interface.  
		@param newItem IN the source's place behavior
		@param target IN the target's place behavior
	*/
	virtual void 		ProcessReplacePreserveState(IPlaceBehavior* newItem, IPlaceBehavior* target) = 0;

	/** Append a list of script objects corresponding to the source content. If this content can be
		loaded into the place gun, these script objects will be considered children of the place gun.
		@param the list to which to append the script objects INOUT
	*/
	virtual void		AppendScriptObjects( ScriptList& objectList ) = 0 ;

	//----------------------------------------------------------------------------------------------
	// Target content methods
	//----------------------------------------------------------------------------------------------

	/** Types of content involved in place operations */
	enum eFrameKind { 
		/**  */
		kTextFrameKind, 
		/**  */
		kGraphicFrameKind, 
		/**  */
		kInteractiveFrameKind, 
		/**  */
		kContainerFrameKind,
		/**Not really a Frame, per se, but a TextFocus into a story somewhere */
		kTextInsertionKind,
		/** */
		kUnknownFrameKind 
	};

	/** Perform a Replace operation (new item replaces an existing one)
		@param placedItem IN new item
		@param oldItem IN exiting item
		@param useClippingFrame IN retain the clipping frame
		@param afterPlace INOUT what should happen after the replace 
		@return newly placed object
	*/
	virtual UID			ProcessReplace(const UIDRef& placedItem, const UIDRef& oldItem, bool16 useClippingFrame, IPlaceBehavior::eAfterPlace *afterPlace= nil, IItemsToPlaceData::ePlaceFrom placeFrom = IItemsToPlaceData::kPlaceGun) = 0;	

	/** Can the source item be placed into "this" object
		@param sourceItem IN the place behavior of the object being placed
		@param spread IN the destination spread (used for master spread relationship)
		@return true if "this" could accept the place
	*/
	virtual bool16		CanPlaceInto(const IPlaceBehavior& sourceItem, const ISpread* spread) const = 0;	

	/** Can a source item of a given type be placed into "this" object
		@param newPageItemKind IN the type of the source item
		@return true if "this" could accept the place
	*/
	virtual bool16		CanPlaceInto(eFrameKind newPageItemKind) const = 0;

	/** Can "this" item be replaced
		@return true if "this" item can be replaced
	*/
	virtual bool16		CanReplace() const = 0;

	/** Can the frame corresponding to "this" object be converted to a new type.
		@param newPageItemKind IN the new type
		@return true if "this" item can be converted to the new type
	*/
	virtual bool16		CanConvertTo(eFrameKind newPageItemKind) const = 0;

	/** Perform a ConvertTo operation.
		@param newPageItemKind IN which frame kind should the object be converted to
		@param controlView IN controlView parameter can be used by implementation if selection changes need to be made.
		@return result of the operation, kSuccess or an error code.
	*/
	virtual ErrorCode	ProcessConvertTo(eFrameKind newPageItemKind, IControlView* controlView) = 0;

	/** Is the frame corresponding to "this" object empty? */
	virtual bool16		IsEmpty() const = 0;

	// Target helper methods

	/** Utility routine to replace the target object (Me)
		@param placedItem IN item to be placed
		@param oldItem IN item to replace
		@param usePlaceGunFrame IN use or strip off the frame around the item from the place gun
		@param afterPlace INOUT what should happen after the replace 
		@return newly placed object
	*/
	virtual UID			ProcessReplaceMe(const UIDRef& placedItem, const UIDRef& oldItem, bool16 usePlaceGunFrame, IPlaceBehavior::eAfterPlace *afterPlace, IItemsToPlaceData::ePlaceFrom placeFrom = IItemsToPlaceData::kPlaceGun) = 0;

	/** Utility routine to replace the children of the target object (Me)
		@param placedItem IN item to be placed
		@param oldItem IN item to replace
		@param usePlaceGunFrame IN use or strip off the frame around the item from the place gun
		@param afterPlace INOUT what should happen after the replace 
		@return newly placed object
	*/
	virtual UID			ProcessReplaceChildren(const UIDRef& placedItem, const UIDRef& oldItem, bool16 usePlaceGunFrame, IPlaceBehavior::eAfterPlace *afterPlace) = 0;
	
	/** Get the frame kind of "this" content. */
	virtual eFrameKind 	GetFrameKind() const = 0;

	/** Is targetHier from a different spread (thus from a master spread)?
		@param targetHier IN the target item's hierarchy (might be a master page item)
		@param targetSpread IN target spread
		@return true if from a master spread.
	*/
	virtual bool16		IsFromMaster(const IHierarchy* targetHier, const ISpread* targetSpread) const = 0; 
};

#endif //__IPlaceBehavior__

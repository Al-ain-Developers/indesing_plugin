//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CGraphicPlaceBehavior.h $
//  
//  Owner: Mat Marcus
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
#ifndef __CGraphicPlaceBehavior__
#define __CGraphicPlaceBehavior__

#include "IPlaceBehavior.h"
#include "IReferencePointData.h"
#include "IDatabase.h"

class IPersistUIDData ;

class PUBLIC_DECL CGraphicPlaceBehavior : public CPMUnknown<IPlaceBehavior>
{
public:	
	CGraphicPlaceBehavior(IPMUnknown *boss);
	virtual ~CGraphicPlaceBehavior();

// source 
	virtual UIDList		ProcessPlace(IPlaceBehavior* targetItem,  const UIDRef& parent, const PMPointList& points, 
									ICursorMgr::eCursorModifierState finalModifiers, ICursorMgr::eCursorModifierState startingModifiers,
									const ISpread* spread, IPlaceBehavior::eAfterPlace *afterPlace,
									IItemsToPlaceData::ePlaceFrom placeFrom = IItemsToPlaceData::kPlaceGun);
	virtual void 		ProcessReplacePreserveState(IPlaceBehavior* srcRoot, IPlaceBehavior* target);
	virtual void		AppendScriptObjects( ScriptList& objectList ) ;

// target
	virtual UID 		ProcessReplace(const UIDRef& placedItem, const UIDRef& oldItem, bool16 useClippingFrame, IPlaceBehavior::eAfterPlace *afterPlace, IItemsToPlaceData::ePlaceFrom placeFrom = IItemsToPlaceData::kPlaceGun);
	virtual bool16		CanPlaceInto(eFrameKind newPageItemKind) const;
	virtual bool16		CanPlaceInto(const IPlaceBehavior& sourceItem, const ISpread* spread) const;
	virtual bool16		CanReplace() const;
	virtual bool16		CanConvertTo(eFrameKind newPageItemKind) const;
	virtual ErrorCode	ProcessConvertTo(eFrameKind newPageItemKind, IControlView* view);
	virtual bool16		IsEmpty() const;
	virtual bool16		IsFromMaster(const IHierarchy* targetHier, const ISpread* targetSpread) const; // Is targetHier from a different spread?
	
protected:
/// helpers
	// Am I a page item from master and overrideable?
	virtual bool16 			IsItemMasterNotOverrideable(const IHierarchy* hier, const ISpread* spread) const;

	// Am I the "Outermost" graphicFrame of this page item
	virtual bool16 			IsItemRoot() const;

	// override this for different frame kinds
	virtual eFrameKind 		GetFrameKind() const;
	
	// Query the "Outermost" graphicFrame of this page item
	virtual IPlaceBehavior* QueryItemRoot();


	virtual UIDList			ProcessDoPlace(const UIDRef& parent, const PMPointList& points, IItemsToPlaceData::ePlaceFrom placeFrom  = IItemsToPlaceData::kPlaceGun);
	virtual UIDList			ProcessDoPlaceInto(IPlaceBehavior* targetItem, const PMPointList& points,	IPlaceBehavior::eAfterPlace &whatToDoAfter,IItemsToPlaceData::ePlaceFrom placeFrom = IItemsToPlaceData::kPlaceGun);

	virtual UID				ProcessReplaceMe(const UIDRef& placedItem, const UIDRef& oldItem, bool16 usePlaceGunFrame, IPlaceBehavior::eAfterPlace *afterPlace, IItemsToPlaceData::ePlaceFrom placeFrom);
	virtual UID				ProcessReplaceChildren(const UIDRef& placedItem, const UIDRef& oldItem, bool16 usePlaceGunFrame, IPlaceBehavior::eAfterPlace *afterPlace);
	
	virtual void			HandleXMPRotation(IPersistUIDData* uidData, bool16 modifyFrame);


	// methods to access PlaceGun(or PlaceHead).	
	virtual bool16			IsPlaceLoaded(IDataBase* db, IItemsToPlaceData::ePlaceFrom placeFrom) const;
	virtual UID				GetFirstItemToPlaceUID(IDataBase* db, IItemsToPlaceData::ePlaceFrom placeFrom) const;
	virtual ErrorCode		ClearFirstItemToPlace(IDataBase* db, IItemsToPlaceData::ePlaceFrom placeFrom) const;
	virtual ErrorCode		AbortFirstItemToPlace(IDataBase* db, IItemsToPlaceData::ePlaceFrom placeFrom) const;
	virtual ErrorCode		AbortAllItemsToPlace(IDataBase* db, IItemsToPlaceData::ePlaceFrom placeFrom) const;

	// method to map a reference point position to the value required by interface IAlignContentInFrameCmdData	
	virtual int32			RefPointPositionToAlignContentInFrame(IReferencePointData::ReferencePointPosition pos) const;

};

#endif //__CGraphicPlaceBehavior__

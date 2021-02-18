//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/pageitems/basicinterfaces/CGraphicPlaceBehavior.cpp $
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

#include "VCPublicHeaders.h"

// ----- Interfaces -----
#include "ITransform.h"
#include "ITransformFacade.h"
#include "IAlignContentInFrameCmdData.h"
#include "IControlView.h"
#include "IDataExchangeController.h"
#include "IEPSAttributes.h"
#include "IEPSTagTable.h"
#include "IFrameContentFacade.h"
#include "IGraphicAttributeUtils.h"
#include "IGraphicFrameData.h"
#include "IGraphicStyleDescriptor.h"
#include "IHierarchy.h"
#include "IHierarchyCmdData.h"
#include "IImageAttributes.h"
#include "IImageDataAccess.h"
#include "IImageFormatAccess.h"
#include "IImageIOPreferences.h"
#include "IImageUtils.h"
#include "IImportExportFacade.h"
#include "IImportProviderUtils.h"
#include "IInCopyFileInfo.h"
#include "IIntData.h"
#include "ILink.h"
#include "ILinkFacade.h"
#include "ILinkManager.h"
#include "ILinkResource.h"
#include "ILinkUtils.h"
#include "ILockPosition.h"
#include "IMasterOverrideable.h"
#include "IPMMatrixListData.h"
#include "IPageItemTypeUtils.h"
#include "IPathGeometry.h"
#include "IPhotoshopClippingPath.h"
#include "IPlaceGun.h"
#include "IPlaceGunUtils.h"
#include "IUIDRefListData.h"
#include "IPlacePIData.h"
#include "IPMUnknownData.h"
#include "IReferencePointData.h"
#include "IRelinkPreferences.h"
#include "IScrapImageList.h"
#include "IScrapItem.h"
#include "IScriptUtils.h"
#include "ISetClipValuesCmdData.h"
#include "ISetDrawOptionOverrideCmdData.h"
#include "ISpread.h"
#include "IStandOffData.h"
#include "IStandOffItemData.h"
#include "ITextWrapFacade.h"
#include "IUIDData.h"
#include "IXPAttributeUtils.h"
#include "IGraphicStateIsApplicable.h"
#include "IGraphicAttributeInfo.h"
#include "IGraphicStateUtils.h"
#include "IPlaceBehaviorUI.h"
#include "IActiveContext.h"
#include "ILayoutControlData.h"
#include "IItemLockData.h"
#include "ILayoutUtils.h"
#include "IPersistUIDData.h"
#include "IDocument.h"
#include "IGfxLayoutAttributeOptions.h"

// ----- Includes -----

#include "CGraphicPlaceBehavior.h"
#include "ConvertPSResourcesToPMTags.h"
#include "IDTime.h"
#include "LocaleSetting.h"
#include "ObjAttributeBossList.h"
#include "PathOutlineInfo.h"
#include "PMFailure.h"
#include "PreserveXMLElement.h"
#include "LinkQuery.h"

// ----- Utility files -----

#include "MemUtils.h"
#include "IFrameContentUtils.h"
#include "IPageItemUtils.h"
#include "PreferenceUtils.h"
#include "TransformUtilsPrivate.h"
#include "TransformUtils.h"

// ----- ID.h files -----

#include "ClippingDlgID.h"
#include "ContentDropperID.h"
#include "EPSID.h"
#include "JPEGFilterID.h"
#include "MetaDataID.h"
#include "PageItemScrapID.h"
#include "PSFilterID.h"
#include "SplineID.h"
#include "DragDropID.h"

// BP 05/03/01: moved to  .../source/components/public/PublicImpl.cpp
// CREATE_PMINTERFACE(CGraphicPlaceBehavior, kCGraphicPlaceBehaviorImpl);

const int32 kFirstPSPathID = 2000;

#pragma exceptions on

static uint32 GetAlphaCount(IPMUnknown* graphic);
static uint32 GetClipCount(IPMUnknown* graphic);

static InterfacePtr<IGraphicAttributeInfo> ScaleXPAttribute(IGraphicAttributeInfo *attr, PMMatrix const &m, IGraphicStyleAttributeBossList const *attrs);
static void LineUpTopLeftCorners(const IPMUnknown *oldGeo, const IPMUnknown *newGeo, const Transform::CoordinateSpace& coordinateSpace);
static ErrorCode MoveWrapFromFrameToGraphic(const UIDRef& itemToPlaceInto, const UIDRef& content);

CGraphicPlaceBehavior::CGraphicPlaceBehavior(IPMUnknown *boss) :
CPMUnknown<IPlaceBehavior>(boss)
{
}

CGraphicPlaceBehavior::~CGraphicPlaceBehavior()
{
}

// source 
UIDList CGraphicPlaceBehavior::ProcessDoPlaceInto(IPlaceBehavior* targetItem, const PMPointList& points, IPlaceBehavior::eAfterPlace &whatToDoAfter, IItemsToPlaceData::ePlaceFrom placeFrom)
{
	UIDList result ;

	// We can't use the above variant of IPlacePIData (which uses contents of place gun)
	// since it will try to place the enclosing graphic frame. Instead we strip it off ourself
	// and then set placeData to the contents. 

	InterfacePtr<IHierarchy> contentHier(this, UseDefaultIID());
	InterfacePtr<IHierarchy> placedItemHier(contentHier->QueryParent());
	InterfacePtr<IPlaceBehavior> placeBehav(placedItemHier,UseDefaultIID());
	UIDRef content = ::GetUIDRef(this);

	//place gun not have empty frames loaded. But CntentDropper can have. So, we cannot assume parent to be a page item.
	//Thus, to avoid cases where non - page items are parent we consider parents only if they have IPlaceBehavior on them.
	UIDRef placedItem = ::GetUIDRef(placeBehav);
	UIDRef itemToPlaceInto = ::GetUIDRef(targetItem);

	if(placeBehav)
		ASSERT_MSG(placedItemHier->GetChildCount() == 1, "CGraphicPlaceBehavior::DoPlaceInto: Place gun item must have 1 child");

	CmdUtils::SequenceContext	sequence;
	try {
		IDataBase* db = content.GetDataBase();

		// The scope here is important because destructor of PreserveXMLElement
		// calls a command that could fail.
		{
			// Preserve XML tagging	
			PreserveXMLElement preserveElement(targetItem);

			// If the wrap on the frame is "Wrap Around Object Shape" and we are placing a graphic into the frame,
			// move the wrap to the graphic.
			if ( Utils<IPageItemTypeUtils>()->IsGraphic(content) )
			{
				MoveWrapFromFrameToGraphic(itemToPlaceInto, content);
			}

			// Destroy children if any.  This will most likely be placeholder content
			InterfacePtr<IHierarchy> targetHierarchy(targetItem, UseDefaultIID());
			int32 count = targetHierarchy->GetChildCount();
			while(--count >= 0) {
				InterfacePtr<IHierarchy> child(targetHierarchy->QueryChild(count));
				if (child)
				{
					InterfacePtr<IScrapItem> childScrap(child, IID_ISCRAPITEM);
					InterfacePtr<ICommand> deleteChildCmd (childScrap->GetDeleteCmd());
					PM::FailErrorCode(CmdUtils::ProcessCommand(deleteChildCmd));
				}
				else
				{
					// If the content of the frame is a missing plugin we don't want to leave
					// any dangling UID here.  Since we don't have a scrap interface to work with
					// we just remove it directly.  We don't care about fixing it up in the case of undo
					// or dropping the UID on the floor either.
					InterfacePtr<ICommand> deleteChildCmd(CmdUtils::CreateCommand(kRemoveFromHierarchyCmdBoss));
					deleteChildCmd->SetItemList(UIDList(db, targetHierarchy->GetChildUID(count)));
					PM::FailErrorCode(CmdUtils::ProcessCommand(deleteChildCmd));
				}
			}

			// Detach the imported content from the created frame
			InterfacePtr<ICommand> detachContentCmd ( CmdUtils::CreateCommand(kRemoveFromHierarchyCmdBoss));
			detachContentCmd->SetItemList(  UIDList(content));
			PM::FailErrorCode(CmdUtils::ProcessCommand(detachContentCmd));

			// Clear the place gun since we are about to delete the UID that it is holding
			whatToDoAfter = IPlaceBehavior::kLeaveAsIs;

			//InterfacePtr<IPlaceGun> placeGun(db, db->GetRootUID(), UseDefaultIID());
			//PM::FailErrorCode(Utils<Facade::IImportExportFacade>()->ClearPlaceGun( placeGun, Facade::IImportExportFacade::kFirstItem ));
			PM::FailErrorCode(ClearFirstItemToPlace(db, placeFrom));

			// Delete the placed frame
			if(placedItem.GetUID() != kInvalidUID)
			{
				InterfacePtr<IScrapItem> placedItemScrap(placedItem, IID_ISCRAPITEM);
				InterfacePtr<ICommand> deleteGFCmd ( placedItemScrap->GetDeleteCmd());
				PM::FailErrorCode(CmdUtils::ProcessCommand(deleteGFCmd));
			}

			// Attach the content to the existing frame
			InterfacePtr<ICommand> attachNewItemCmd ( CmdUtils::CreateCommand(kAddToHierarchyCmdBoss));
			InterfacePtr<IHierarchyCmdData> addData(attachNewItemCmd, IID_IHIERARCHYCMDDATA);
			addData->SetParent(itemToPlaceInto);

			K2Vector<int32> indexList;
			indexList.push_back (0);

			addData->SetIndexInParent(indexList);
			attachNewItemCmd->SetItemList(  UIDList(content));
			PM::FailErrorCode(CmdUtils::ProcessCommand(attachNewItemCmd));

			// Move the content so it appears at the top left of the frame
			// If no Frame Fitting Options have been applied to frame we want image in this position.
			// If Frame Fitting Options have been applied, this align is blown away when ApplyFittingOptionsToContent, see CGraphicPlaceBehavior::ProcessPlace.
			InterfacePtr<ICommand> alignCmd(CmdUtils::CreateCommand(kAlignContentInFrameCmdBoss));
			alignCmd->SetItemList(  UIDList(content));
			InterfacePtr<IAlignContentInFrameCmdData> alignData(alignCmd, IID_IALIGNCONTENTINFRAMECMDDATA);
			alignData->Set(IAlignContentInFrameCmdData::kAlignLeftTop);
			PM::FailErrorCode(CmdUtils::ProcessCommand(alignCmd));

			// set the content for XML preservation
			preserveElement.SetFrame(content);
		}

		PM::FailErrorCode();
		result = UIDList(itemToPlaceInto);
	}

	catch (ErrorCode&) {
	}

	return result;
}


UIDList CGraphicPlaceBehavior::ProcessDoPlace(const UIDRef& parent, const PMPointList& points, IItemsToPlaceData::ePlaceFrom placeFrom)
{
	UIDList result ;
	IDataBase* db = parent.GetDataBase();
	if ( db == nil || !parent.ExistsInDB() )	//#2401055
		return result ;
	//InterfacePtr<IPlaceGun> placeGun(parent.GetDataBase(), parent.GetDataBase()->GetRootUID(), UseDefaultIID());
	//if ( placeGun == nil || !placeGun->IsLoaded() )		//#2467578
	if(!IsPlaceLoaded(db, placeFrom))	
		return result ;

	InterfacePtr<ICommand> newPI ( CmdUtils::CreateCommand(kPlacePICmdBoss));
	InterfacePtr<IPlacePIData>	cmddata(newPI, IID_IPLACEPIDATA);

	// If both the start and end points are the same, only pass the first point
	PMPointList cmdPtList;
	if ( points[0] == points[1] )
		cmdPtList.push_back (points[0]);
	else
		cmdPtList = points;

	// Passing kTrue makes the command use the content of the place gun
	if(placeFrom == IItemsToPlaceData::kPlaceGun)
	{	
		cmddata->Set(parent, &cmdPtList, kTrue );
	}
	else if(placeFrom == IItemsToPlaceData::kPlaceHead)
	{
		newPI->SetItemList(UIDList(db,GetFirstItemToPlaceUID(db,placeFrom)));
		cmddata->Set(parent, &cmdPtList, kFalse );
	}


	ErrorCode errorResult = CmdUtils::ProcessCommand(newPI);
	if (errorResult == kSuccess)
		result = newPI->GetItemListReference();

	//someone else must setup and append: Utils<Facade::IImportExportFacade>()->ClearPlaceGun( placeGun );
	return result;
}

int32 CGraphicPlaceBehavior::RefPointPositionToAlignContentInFrame(IReferencePointData::ReferencePointPosition pos) const
{
	switch(pos)
	{
	case IReferencePointData::kTopLeftReferencePoint :
		return IAlignContentInFrameCmdData::kAlignLeftTop;

	case IReferencePointData::kTopCenterReferencePoint :
		return IAlignContentInFrameCmdData::kAlignTopCenter ;

	case IReferencePointData::kTopRightReferencePoint :
		return IAlignContentInFrameCmdData::kAlignRightTop ;

	case IReferencePointData::kLeftCenterReferencePoint :
		return IAlignContentInFrameCmdData::kAlignLeftCenter ;

	case IReferencePointData::kCenterReferencePoint :
		return IAlignContentInFrameCmdData::kAlignCenter ;

	case IReferencePointData::kRightCenterReferencePoint :
		return IAlignContentInFrameCmdData::kAlignRightCenter ;

	case IReferencePointData::kBottomLeftReferencePoint :
		return IAlignContentInFrameCmdData::kAlignLeftBottom ;

	case IReferencePointData::kBottomCenterReferencePoint :
		return IAlignContentInFrameCmdData::kAlignBottomCenter ;

	case IReferencePointData::kBottomRightReferencePoint :
		return IAlignContentInFrameCmdData::kAlignRightBottom ;

	default:
		return IAlignContentInFrameCmdData::kAlignLeftTop ;
	}
}

UIDList CGraphicPlaceBehavior::ProcessPlace(IPlaceBehavior* targetItem,  const UIDRef& parent, const PMPointList& points, 
											ICursorMgr::eCursorModifierState finalModifiers, ICursorMgr::eCursorModifierState startingModifiers,
											const ISpread* spread, IPlaceBehavior::eAfterPlace *afterPlace,
											IItemsToPlaceData::ePlaceFrom placeFrom)
{
	IPlaceBehavior::eAfterPlace whatToDoAfter =  IPlaceBehavior::kOldBehavior;
	UIDList result;
	PMString name("Place");
	CmdUtils::SequenceContext sequence(&name);

	ErrorCode err = Utils<IImportProviderUtils>()->SendPlaceReplaceSignal( kBeforePlaceSignalResponderService, this, targetItem, result ) ;
	if ( err != kSuccess ) return result ;

	try {							
		bool	bCheckXMPRotation(true);
		bool16	modifyFrame = kFalse;

		bool16 isInCopy = LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS);

		// CASE 1: Drag place (except InCopy, which doesn't support drag place.
		// If the mouse has moved, we're doing a drag place.
		if (points[0] != points[1] && !isInCopy) {
			result = ProcessDoPlace(parent, points, placeFrom);
			PM::FailErrorCode();
		} else {
			// CASE 2: Place into an existing frame
			// generate a command to place into targetUID
			if(targetItem && targetItem->CanPlaceInto(*this, spread)){
				InterfacePtr<const IHierarchy> targetHier(targetItem, UseDefaultIID());
				InterfacePtr<IPlaceBehavior> realTarget;
				if (IsFromMaster(targetHier, spread))
				{
					InterfacePtr<IPlaceBehaviorUI> behaviorUI(this, UseDefaultIID());
					if (behaviorUI)
						realTarget.reset(behaviorUI->QueryPlaceBehaviorAt(points[0]));
					else
						ASSERT_FAIL("Bishop Assert: There is no way to figure out the correct target. [LDM]");					
				}
				else
					realTarget.reset(InterfacePtr<IPlaceBehavior>(targetItem, UseDefaultIID()).forget()); // yes I'm intentionally using same interface

				if(realTarget){
					// place into
					ErrorCode err = realTarget->ProcessConvertTo(GetFrameKind(), nil);
					ASSERT_MSG(kSuccess == err, "CGraphicPlaceBehavior::Place: can't convert target to graphic frame");

					if(kSuccess == err) {
						result = ProcessDoPlaceInto(realTarget, points,whatToDoAfter, placeFrom);
					}
				}
			} 
			else if (isInCopy)
			{
				// CASE 3: Abort the place, didn't hit an existing frame and InCopy can't place graphics independently.
				// Kill the leftover husk in the place gun
				IDataBase *db = ::GetUIDRef(this).GetDataBase();
				//InterfacePtr<IPlaceGun> placeGun(db, db->GetRootUID(), UseDefaultIID());
				bCheckXMPRotation = false;
				//PM::FailErrorCode(Utils<Facade::IImportExportFacade>()->AbortPlaceGun( placeGun, Facade::IImportExportFacade::kAllItems ));
				PM::FailErrorCode(AbortAllItemsToPlace(db, placeFrom));
			}
			else {
				// CASE 4: Create a new frame, place into it.
				result = ProcessDoPlace(parent, points, placeFrom);

				modifyFrame = kTrue;

				UIDRef frame = result.GetRef(0);
				InterfacePtr<IPersistUIDData> iPersistObjectStyleData(frame, IID_IPERSISTOBJECTSTYLEDATA);
				if (iPersistObjectStyleData)
				{
					UID styleUID = iPersistObjectStyleData->GetUID();
					InterfacePtr<IGfxLayoutAttributeOptions> styleAttributes(frame.GetDataBase(), styleUID, UseDefaultIID());
					bool16 isHeightDefined = styleAttributes->GetIsAttrDefinedByStyle(IGfxLayoutAttributeOptions::kLayoutAttribute_HEIGHT);
					bool16 isWidthDefined = styleAttributes->GetIsAttrDefinedByStyle(IGfxLayoutAttributeOptions::kLayoutAttribute_WIDTH);
					if (isHeightDefined || isWidthDefined)
					{
						modifyFrame = kFalse;
					}
				}
				
			}
		}

		if (result.size() > 0 && IItemsToPlaceData::kPlaceHead != placeFrom)
		{
			if ( bCheckXMPRotation )
			{
				// if we placed the image, deal with the XMP rotation, if it exists
				InterfacePtr<IPersistUIDData> uidData(this, IID_IMETADATAUIDDATA);
				HandleXMPRotation(uidData, modifyFrame);
			}

			// Apply fitting options
			Utils<Facade::IFrameContentFacade> iFrameContentFacade;
			if ( iFrameContentFacade && iFrameContentFacade->CanFitContentToFrame (result) )
			{
				UIDList frameList(result);
				IReferencePointData::ReferencePointPosition refPosition = IReferencePointData::kUninitializedReferencePointPosition;
				IFrameContentSuite::PersistentFitOptions fitting = IFrameContentSuite::kNoFitting; 
				iFrameContentFacade->GetFittingOptions(frameList, &refPosition, nil, &fitting, nil); 
				
				if (fitting != IFrameContentSuite::kNoFitting) 
				{
					GlobalErrorStatePreserver errorStatePreserve;
					iFrameContentFacade->ApplyFittingOptionsToContent(frameList);
				}
				else
				{
					InterfacePtr<ICommand> alignCmd(CmdUtils::CreateCommand(kAlignContentInFrameCmdBoss));
					alignCmd->SetItemList(  UIDList(::GetUIDRef(this)));
					InterfacePtr<IAlignContentInFrameCmdData> alignData(alignCmd, IID_IALIGNCONTENTINFRAMECMDDATA);
					alignData->Set(RefPointPositionToAlignContentInFrame(refPosition));
					PM::FailErrorCode(CmdUtils::ProcessCommand(alignCmd));
				}
			}
		}		
	}

	catch (ErrorCode&) {
	}

	if (afterPlace)
		*afterPlace =whatToDoAfter;

	if ( ErrorUtils::PMGetGlobalErrorCode() == kSuccess )
		Utils<IImportProviderUtils>()->SendPlaceReplaceSignal( kAfterPlaceSignalResponderService, this, targetItem, result ) ;

	return result;
}




// target //

UID CGraphicPlaceBehavior::ProcessReplace(const UIDRef& placedItem, const UIDRef& oldItem, bool16 useClippingFrame, IPlaceBehavior::eAfterPlace *afterPlace, IItemsToPlaceData::ePlaceFrom placeFrom)
{
	UID	result = kInvalidUID;
	InterfacePtr<IPlaceBehavior> placeGunBehavior(placedItem, UseDefaultIID());
	ErrorCode err = Utils<IImportProviderUtils>()->SendPlaceReplaceSignal( kBeforeReplaceSignalResponderService, placeGunBehavior, this, UIDRef( ::GetDataBase(this), result ) ) ;
	if ( err != kSuccess ) return result ;

	// generate a command to replace targetUID:
	IPlaceBehavior::eAfterPlace whatToDoAfter = IPlaceBehavior::kOldBehavior;
	if (afterPlace)
		*afterPlace = whatToDoAfter;
	InterfacePtr<IHierarchy> hier(this, UseDefaultIID());
	InterfacePtr<IGraphicFrameData> frameData(hier, UseDefaultIID());
	ASSERT_MSG(frameData == nil, "CGraphicPlaceBehavior::Replace: called on Graphic Frame");

	InterfacePtr<IHierarchy> parent(hier->QueryParent());
	InterfacePtr<IGraphicFrameData> parentFrameData(parent, UseDefaultIID());
	if(parentFrameData == nil)
	{
		// parent is not a graphic frame
		result = ProcessReplaceMe(placedItem, oldItem, kTrue,afterPlace,placeFrom);
	}
	else
	{
		// parent is a GF
		eFrameKind placeGunFrameKind = placeGunBehavior->GetFrameKind();
		if(placeGunFrameKind == kTextFrameKind) {
			InterfacePtr<IPlaceBehavior> parentBehavior(parentFrameData, UseDefaultIID());
			result = parentBehavior->ProcessReplaceChildren(placedItem, oldItem, kFalse, afterPlace);
		}else{
			result = ProcessReplaceMe(placedItem, oldItem, kFalse, afterPlace, placeFrom);
		}
	}

	// Moving to ProcessReplacePreserveState such that the rotation is applied before we attempt to reposition or apply
	// transforms from the graphic we are replacing. [dstephens 10/17/2007]
	/*
	if (result != kInvalidUID)
	{
	// if the image was replaced, deal with the XMP rotation, if it exists
	InterfacePtr<IPersistUIDData> uidData3(placedItem.GetDataBase(), result, IID_IMETADATAUIDDATA);
	HandleXMPRotation(uidData3, kFalse);
	}*/

	if ( ErrorUtils::PMGetGlobalErrorCode() == kSuccess )
		Utils<IImportProviderUtils>()->SendPlaceReplaceSignal( kAfterReplaceSignalResponderService, placeGunBehavior, this, UIDRef( ::GetDataBase(this), result ) ) ;

	return result;
}

static uint32 CheckJPEGExifResolutionHeuristic(const IImageAttributes *iImageAttributes)
{
	const int32 kMagicImageDimension = 700;
	uint32 intScale = 1;

	if ( iImageAttributes && iImageAttributes->TagExists(IImageAttributes::kPMTagJPEG_EXIF_Resolution) )
	{
		Fixed res;
		iImageAttributes->GetTag (IImageAttributes::kPMTagXResolution, &res);

		// only apply the heuristic if the current resolution is 72 and the exif resolution is 72
		if ( res == (72 << 16) )
		{
			Fixed exif_res;
			iImageAttributes->GetTag (IImageAttributes::kPMTagJPEG_EXIF_Resolution, &exif_res);

			if ( exif_res == (72 << 16) )
			{
				// resolution calculation heuristic
				// find an integer scale that evenly divides the width and height such that
				// the resulting width and height is less than some magical dimension that 
				// I believe will nicely fit on a page.

				uint32 width, height;

				iImageAttributes->GetTag (IImageAttributes::kPMTagImageWidth, &width);
				iImageAttributes->GetTag (IImageAttributes::kPMTagImageHeight, &height);

				uint32 dim = width;
				if ( dim < height )
					dim = height;
				if ( dim > kMagicImageDimension )
				{
					intScale = (dim/kMagicImageDimension) + 1;
					while (intScale > 1)
					{
						if ( width % intScale == 0 && height % intScale == 0 )
							break;

						--intScale;
					}
				}
			}
		}
	}

	return intScale;
}

//----------------------------

static ILink* QueryLink(const UIDRef& pageItem)
{
	IDataBase *db = pageItem.GetDataBase();
	InterfacePtr<ILinkManager> iLinkManager(db, db->GetRootUID(), UseDefaultIID());
	if ( iLinkManager )
	{
		ILinkManager::QueryResult result;
		if ( iLinkManager->QueryLinksByObjectUID(pageItem.GetUID(), result) )
		{
			InterfacePtr<ILink> iLink(db, *result.begin(), UseDefaultIID());
			if ( iLink )
				return iLink.forget();
		}
	}

	return nil;
}

//----------------------------
// Move newGeo such that its topleft has the same offset from its parent as oldGeo does from its parent.

void LineUpTopLeftCorners(const IPMUnknown *oldGeo, const IPMUnknown *newGeo, const Transform::CoordinateSpace& coordinateSpace)
{
	K2Vector<PMPoint> referencePoints;
	Transform::TransformOrigin topLeftRelative(Transform::BoundsLocation( coordinateSpace, Geometry::OuterStrokeBounds(), 0.0, 0.0));

	UIDList original(oldGeo);
	::ResolveLocation(&original, coordinateSpace, topLeftRelative, &referencePoints);
	PMPoint oldTopLeft = referencePoints[0];

	referencePoints.clear();
	UIDList newList(newGeo);
	::ResolveLocation(&newList, coordinateSpace, topLeftRelative, &referencePoints);
	PMPoint newTopLeft = referencePoints[0];

	if ( oldTopLeft != newTopLeft )
	{
		PMPoint delta = oldTopLeft - newTopLeft;
		Utils<Facade::ITransformFacade>()->TransformItems(newList,
			coordinateSpace,
			Transform::CurrentOrigin(),
			Transform::TranslateBy( delta.X(), delta.Y()));
	}
}

//----------------------------

void  CGraphicPlaceBehavior::ProcessReplacePreserveState(IPlaceBehavior* srcRoot, IPlaceBehavior* target)
{
	ASSERT_MSG(srcRoot != nil, "CGraphicPlaceBehavior::ProcessReplacePreserveState nil root");

	UID thisUID = ::GetUID(this);
	UID srcUID  = ::GetUID(srcRoot);
	IDataBase* db = ::GetDataBase(this);

	PMReal oldXMPRotation(0.0);
	PMReal newXMPRotation(0.0);
	int16 metaDataOrient(0);

	// Apply new XMP rotation, if it exists
	// Skip if we're inx, though, as the rotation has already been applied to the pageitem in the stream (bug 1861456, richg)
	bool16 bIsXMP = Utils<IScriptUtils>()->IsINX();
	if ( !bIsXMP && Utils<IImageUtils>()->GetMetaDataOrientation(::GetUIDRef(srcRoot), &metaDataOrient) == kSuccess )
		newXMPRotation = metaDataOrient;

	metaDataOrient = 0;
	bool bHaveOldXMPRotation = (Utils<IImageUtils>()->GetMetaDataOrientation(::GetUIDRef(target), &metaDataOrient) == kSuccess);
	oldXMPRotation = metaDataOrient;

	InterfacePtr<IPersistUIDData> uidData3(db, srcUID, IID_IMETADATAUIDDATA);
	if ( uidData3 )
		HandleXMPRotation(uidData3, kFalse);

	UIDList matUIDList(db);

	InterfacePtr<ICommand> setMatrixCmd ( CmdUtils::CreateCommand(kSetPMMatrixCmdBoss));
	InterfacePtr<IPMMatrixListData> matrixList(setMatrixCmd, IID_IPMMATRIXLISTDATA);
	PMMatrixCollection matCollection;

	PMMatrix itemMat, xpAttrMatrix, clipMatrix;
	if ( newXMPRotation != 0.0 )
		itemMat.Rotate(newXMPRotation);

	InterfacePtr<IGeometry>  iNewGeo(srcRoot, IID_IGEOMETRY);
	InterfacePtr<IGeometry>  iOriginalGeo (target, IID_IGEOMETRY);

	// Apply any necessary scale and rotation transforms based on Re-Import preferences, XMP settings on the item being replaced,
	// and on whether or not EXIF meta data triggers scaling to occur.
	{
		PMRect newBBox = iNewGeo->GetStrokeBoundingBox();
		itemMat.Transform(&newBBox);

		InterfacePtr<ITransform> iOriginalTransform (target, IID_ITRANSFORM);
		InterfacePtr<const ITransform> newITransform(srcRoot, UseDefaultIID());

		PMRect originalBBox = iOriginalGeo->GetStrokeBoundingBox();
		if ( bHaveOldXMPRotation )
		{
			PMMatrix originalXMPMatrix;
			originalXMPMatrix.Rotate(oldXMPRotation);
			originalXMPMatrix.Transform(&originalBBox);
		}

		if ( originalBBox.Width() != newBBox.Width()  )
		{
			InterfacePtr<IRelinkPreferences> iRelinkPreferences((IRelinkPreferences*)::QuerySessionPreferences(IRelinkPreferences::kDefaultIID));
			bool bPreserveDimensions = (iRelinkPreferences && iRelinkPreferences->GetPreserveBoundsOnRelink());
			if ( bPreserveDimensions )
			{
				PMReal xScale(originalBBox.Width()/newBBox.Width());
				itemMat.Scale(xScale, xScale);
			}
			else if ( Utils<IImageUtils>()->IsRasterImage(iNewGeo)
				&& Utils<IImageUtils>()->IsRasterImage(iOriginalGeo) )
			{
				// JPEGs produced from digital cameras sometimes include EXIF meta data which describes, among other things,
				// the resolution of the image.  Prior to Firedrake, InDesign did not read the EXIF structure and assumed
				// a resolution of 72ppi for these image.  Hence, when these documents were opened in Firedrake and the images
				// were updated/relinked, the resolution suddenly changed causing the geometry of the image to change.  The
				// following code fixes this problem by scaling the new image by the ratio of the old bounds to the new bounds.
				// However, this fix will only kick in if:
				//	1. the old and new links are both JPEGs
				//	2. the page item bbox width of the new image is larger than that of the originally placed one
				//	3. the ratio of the pixel width to pixel height of the new image is the same as that of the original
				//	4. the pixel width of the original is less than or equal to that of the new image
				//
				InterfacePtr<const IImageAttributes> newAttributes(srcRoot, UseDefaultIID());
				InterfacePtr<const IImageAttributes> originalAttributes(target, UseDefaultIID());

				InterfacePtr<const IImageFormatAccess> newReadFormat(srcRoot, UseDefaultIID());
				if ( newReadFormat && newReadFormat->GetFormatClassID() == kJPEGImageReadFormatBoss
					&& originalBBox.Width() < newBBox.Width() )
				{
					if ( newAttributes && originalAttributes )
					{
						Fixed fixedNewWidth, fixedNewHeight;
						Fixed fixedOriginalWidth, fixedOriginalHeight;

						newAttributes->GetTag(IImageAttributes::kPMTagImageWidth, &fixedNewWidth);
						newAttributes->GetTag(IImageAttributes::kPMTagImageHeight, &fixedNewHeight);
						originalAttributes->GetTag(IImageAttributes::kPMTagImageWidth, &fixedOriginalWidth);
						originalAttributes->GetTag(IImageAttributes::kPMTagImageHeight, &fixedOriginalHeight);

						if ( fixedNewWidth == fixedOriginalWidth && fixedNewHeight == fixedOriginalHeight )
						{
							InterfacePtr<ILink> srcLink(QueryLink(::GetUIDRef(srcRoot)));
							InterfacePtr<ILink> targetLink(QueryLink(::GetUIDRef(target)));

							if ( srcLink && targetLink && srcLink->GetImportModTime() == targetLink->GetImportModTime() )
							{
								InterfacePtr<ILinkResource> srcLinkResource(::GetDataBase(srcRoot), srcLink->GetResource(), UseDefaultIID());
								InterfacePtr<ILinkResource> targetLinkResource(::GetDataBase(target), targetLink->GetResource(), UseDefaultIID());
								if ( srcLinkResource && targetLinkResource
									&& srcLinkResource->GetShortName(false) == targetLinkResource->GetShortName(false) )
								{							
									PMReal xScale(originalBBox.Width()/newBBox.Width());
									itemMat.Scale(xScale, xScale);
								}
							}
						}
					}
				}

				if ( itemMat.IsIdentity() )
				{
					// In Cobalt, we've changed the handling of JPEG images with a bad EXIF resolution.  Instead
					// of applying a scale to the actual resolution, we apply the scale to the page item and set
					// the resolution to 72ppi.  So, consider the case where a scale of 25% is applied to an imported
					// JPEG and then the user relinks to an image with no EXIF.  The new image is going to be scaled
					// by 25%.  To avoid this problem, we will attempt to factor out the scale that was applied to
					// the original image.
					uint32 oldEXIFScale = CheckJPEGExifResolutionHeuristic(originalAttributes);
					if (  oldEXIFScale > 1 )
					{
						PMReal scale(oldEXIFScale);
						itemMat.Scale(scale, scale);
					}

					// don't lose any scaling that we've already applied to our new image
					if ( newITransform )
						itemMat.Scale(newITransform->GetItemScaleX(), newITransform->GetItemScaleY());
				}
			}
		}

		xpAttrMatrix = itemMat.Inverse();

		clipMatrix = PMMatrix(1.0/itemMat.GetXScale(), 0.0, 0.0, 1.0/itemMat.GetYScale(), 0.0, 0.0);
		itemMat.PostConcat (iOriginalTransform->GetInnerToParentMatrix());

		// remove effects of old xmp rotation
		if ( bHaveOldXMPRotation )
		{
			itemMat.Rotate(-oldXMPRotation);
		}
	}

	matUIDList.Append (thisUID);

	if ( thisUID == srcUID )
	{
		// In this case we know that target is the child of some other item.
		// Set our bounds and transform to be that of the target
	}
	else
	{
		// In this case the target is getting replaced with srcRoot.  Make sure srcRoot
		// bounds and transform is the same as target

		matUIDList.Append (srcUID);
		matCollection.push_back (PMMatrix());

	}
	matCollection.push_back(itemMat);

	setMatrixCmd->SetItemList (matUIDList);

	matrixList->Set(matCollection);

	{
		// hkhalfal: (NACSR) No abortable command sequence is used
		// errors occurring in this scope will not revert the changes
		GlobalErrorStatePreserver errorStatePreserve;
		CmdUtils::ProcessCommand(setMatrixCmd);
	}

	// Make sure top-left corners are coincident since one item is replacing another.
	LineUpTopLeftCorners(iOriginalGeo, iNewGeo, Transform::ParentCoordinates());

	// Preserve local display settings if old image had a local override
	InterfacePtr<IDrawOptionOverrides const> displayOverrides(target, IID_IDRAWOPTIONOVERRIDE);
	if (displayOverrides && displayOverrides->GetDrawOptionGroup() != IDrawOptions::kUseDefault ) 
	{
		InterfacePtr<ICommand> setDisplaySettingCmd(CmdUtils::CreateCommand(kSetDrawOptionOverrideCmdBoss));
		InterfacePtr<ISetDrawOptionOverrideCmdData> iCmdData(setDisplaySettingCmd, IID_ISETDRAWOPTIONOVERRIDECMDDATA);

		iCmdData->SetDisplayOption(displayOverrides->GetDrawOptionGroup());
		setDisplaySettingCmd->SetItemList(UIDList(db, srcUID));

		CmdUtils::ProcessCommand(setDisplaySettingCmd);
	}

	// Preserve clip settings
	InterfacePtr<IClipSettings> iOldClipSettings(target, IID_ICLIPSETTINGS);
	uint32 alphaCount = 0;
	uint32 clipCount = 0;
	bool8 bCopyOldClip = kTrue;
	bool8 bUpdateClip = kFalse;
	IClipSettings::ClipType clipType = IClipSettings::kClipNone;

	if ( iOldClipSettings )
		clipType = iOldClipSettings->GetClipType();

	if ( clipType != IClipSettings::kClipNone ) 
	{
		int16 pathOrAlphaIndex = IClipSettings::kDefaultClipIndex;

		InterfacePtr<ICommand> settingsCmd(CmdUtils::CreateCommand(kSetClipValuesCmdBoss));
		InterfacePtr<ISetClipValuesCmdData> clipSettingsData(settingsCmd, IID_ISETCLIPVALUESCMDDATA);

		if (clipSettingsData) 
		{
			// Decide which cliptype to use and make sure the old settings
			// for the cliptype are still valid for the new image.
			switch (clipType) 
			{
			case IClipSettings::kClipEmbeddedPath: 
				{
					pathOrAlphaIndex = iOldClipSettings->GetEmbeddedPathIndex();

					// Make sure new image has a clipping path
					InterfacePtr<IImageIOPreferences> newImageIOPrefs( srcRoot, UseDefaultIID() );
					if ( !newImageIOPrefs || newImageIOPrefs->GetCreateClippingFrame() )
						clipCount = GetClipCount(srcRoot);

					if (!Utils<IScriptUtils>()->IsINX())
						bCopyOldClip = kFalse;
					bUpdateClip = kTrue;

					if ( !clipCount ) {
						pathOrAlphaIndex = IClipSettings::kDefaultClipIndex;
						clipType = IClipSettings::kClipNone;
						bUpdateClip = kFalse;
					}
					else if ( clipCount <= pathOrAlphaIndex ) {
						pathOrAlphaIndex = IClipSettings::kDefaultClipIndex;

						// Update the clipping
					}
					break;
				}

			case IClipSettings::kClipAlpha: 
				{
					pathOrAlphaIndex = iOldClipSettings->GetAlphaIndex();

					// If the old setting is Alpha, make sure the new graphic supports the alpha settings.
					alphaCount = GetAlphaCount(srcRoot);

					if ( !alphaCount ) {
						pathOrAlphaIndex = IClipSettings::kDefaultClipIndex;
						clipType = IClipSettings::kClipUserPath;
					}
					else if ( alphaCount <= pathOrAlphaIndex ) {
						pathOrAlphaIndex = 0;
					}

					break;
				}
			default:
				break;
			}

			{
				// hkhalfal: (NACSR) No abortable command sequence is used
				// errors occurring in this scope will not revert the changes
				GlobalErrorStatePreserver errorStatePreserve;

				clipSettingsData->SetImageItem(db, srcUID);

				clipSettingsData->Set (clipType, 
					pathOrAlphaIndex,
					iOldClipSettings->GetTolerance(), 
					iOldClipSettings->GetInset(),
					iOldClipSettings->GetThreshold(),
					iOldClipSettings->GetInvert(),
					iOldClipSettings->GetUseHighRes(),
					iOldClipSettings->GetAllowHoles(),
					iOldClipSettings->GetRestrictToFrame());

				if ( CmdUtils::ProcessCommand(settingsCmd) != kSuccess)
				{
					// Error Handling goes here.
				}
			}
		}

		// Now either copy over the old path (if it was user modified or not an Embedded path)
		// or update from the '8BIM' resource.
		InterfacePtr<IPathGeometry> iOldClip(target, IID_IPATHGEOMETRY);
		if ( (bCopyOldClip || bUpdateClip) && iOldClip && iOldClip->GetNumPaths() != 0 ) {
			InterfacePtr<ICommand> setFrameCmd(CmdUtils::CreateCommand(kSetSplineFramePointsCmdBoss));

			setFrameCmd->SetItemList(UIDList(db, srcUID));
			InterfacePtr<IPathGeometry> iNewClip(setFrameCmd, IID_IPATHGEOMETRY);

			if ( bCopyOldClip )
			{
				iNewClip->CopyPath(iOldClip);

				// transform the path by the inverse of the matrix we applied to the new image to
				// compensate for any scaling we applied to preserve dimensions.
				if ( !clipMatrix.IsIdentity() )
					iNewClip->TransformPath(clipMatrix);
			}
			else {
				// Regenerate the clipping from the 8BIM resource
				InterfacePtr<IEPSTagTable> iEPSTagTable(srcRoot, IID_IEPSTAGTABLE);
				std::string dataString;
				uint32 count;
				if ( iEPSTagTable && iEPSTagTable->GetPhotoShopClipData(0, &dataString, &count) == kSuccess)
				{
					// We have a display list item with a clipping path included
					int32 width, height;
					PMRect bbox;

					InterfacePtr<IImageAttributes> tempAttributes((IImageAttributes*) CreateObject(kImageObject, IID_IIMAGEATTRIBUTES));
					InterfacePtr<IEPSAttributes> epsAttribs(srcRoot, IID_IEPSATTRIBUTES);
					bbox = epsAttribs->GetBoundingBox();
					width = ::ToInt32(bbox.Width());
					height = ::ToInt32(bbox.Height());
					tempAttributes->SetTag(IImageAttributes::kPMTagImageWidth,4,&width);
					tempAttributes->SetTag(IImageAttributes::kPMTagImageHeight,4,&height);

					if ( pathOrAlphaIndex == IClipSettings::kDefaultClipIndex )
						ConvertPSResourcesToPMTags ((char*)dataString.c_str(),count,tempAttributes);
					else
						ConvertPSResourcesToPMTags ((char*)dataString.c_str(),count,tempAttributes, nil, kFirstPSPathID + pathOrAlphaIndex);

					if ( tempAttributes->TagExists (IImageAttributes::kPMTagTIFFClipPath) )
					{					
						//PMReal imTop = bbox.Top();
						//PMReal imLeft = bbox.Left();

						uint32 tagSize = tempAttributes->GetTagSize (IImageAttributes::kPMTagTIFFClipPath);
						uint8* pPathData = new uint8[tagSize];

						tempAttributes->GetTag (IImageAttributes::kPMTagTIFFClipPath, pPathData);

						PMReal xScale = bbox.Width()/(256<<16);
						PMReal yScale = bbox.Height()/(256<<16);

						PathOutlineInfo pathOutline(iNewClip);
						InterfacePtr<IPhotoshopClippingPath> clipPath((IPhotoshopClippingPath*) ::CreateObject(kPhotoshopClippingPathBoss, IID_IPHOTOSHOPCLIPPINGPATH));
						clipPath->Parse(pPathData, tagSize, &pathOutline, xScale, yScale, 0.0, 0.0);
						delete [] pPathData;

					}
				}
				else {
					// We will either grab a particular path from the 8BIM collection of paths or
					// use the path already stored in the IImageAttributes
					InterfacePtr<IImageAttributes> iImageAttributes(srcRoot, IID_IIMAGEATTRIBUTES);

					IImageAttributes *pImageAttributes = iImageAttributes;
					if ( iImageAttributes->TagExists (IImageAttributes::kPMTagPhotoshop8BIM) )
					{						
						// Create some temporary image attributes to hold the selected path data
						pImageAttributes = (IImageAttributes*) CreateObject(kImageObject, IID_IIMAGEATTRIBUTES);

						uint32 tagSize = iImageAttributes->GetTagSize(IImageAttributes::kPMTagPhotoshop8BIM);
						char* tagData = new char[tagSize];
						iImageAttributes->GetTag(IImageAttributes::kPMTagPhotoshop8BIM, tagData);

						if ( pathOrAlphaIndex == IClipSettings::kDefaultClipIndex )
							ConvertPSResourcesToPMTags (tagData,tagSize,pImageAttributes);
						else
							ConvertPSResourcesToPMTags (tagData,tagSize,pImageAttributes, nil, kFirstPSPathID + pathOrAlphaIndex);

						delete [] tagData;					
					}


					// Check the IImageAttributes for the embedded path
					if ( pImageAttributes->TagExists (IImageAttributes::kPMTagTIFFClipPath) )
					{
						uint32 xClipPathUnits, yClipPathUnits;

						uint32 ImWidth, ImHeight;
						uint32 tagSize = pImageAttributes->GetTagSize (IImageAttributes::kPMTagTIFFClipPath);
						uint8* pPathData = new uint8[tagSize];

						pImageAttributes->GetTag (IImageAttributes::kPMTagTIFFClipPath, pPathData);
						pImageAttributes->GetTag (IImageAttributes::kPMTagTIFFXClipPathUnits, &xClipPathUnits);
						pImageAttributes->GetTag (IImageAttributes::kPMTagTIFFYClipPathUnits, &yClipPathUnits);

						// Make sure we get the image height and width from the source image attributes and not the temp attributes
						iImageAttributes->GetTag (IImageAttributes::kPMTagImageWidth, &ImWidth);
						iImageAttributes->GetTag (IImageAttributes::kPMTagImageHeight, &ImHeight);

						PMReal xScale = (PMReal)ImWidth / (PMReal) xClipPathUnits;
						PMReal yScale = (PMReal)ImHeight / (PMReal) yClipPathUnits;

						InterfacePtr<IGeometry> geometry(srcRoot, IID_IGEOMETRY);
						PMRect imageBounds = geometry->GetPathBoundingBox();

						xScale *= (imageBounds.Right() - imageBounds.Left()) / (PMReal)ImWidth;
						yScale *= (imageBounds.Bottom() - imageBounds.Top()) / (PMReal)ImHeight;

						PathOutlineInfo pathOutline(iNewClip);
						InterfacePtr<IPhotoshopClippingPath> clipPath((IPhotoshopClippingPath*) ::CreateObject(kPhotoshopClippingPathBoss, IID_IPHOTOSHOPCLIPPINGPATH));
						clipPath->Parse(pPathData, tagSize, &pathOutline, xScale, yScale, 0.0, 0.0);
						delete [] pPathData;
					}

					if ( pImageAttributes != iImageAttributes )
						pImageAttributes->Release();
				}

				// Preserve the "Invert" setting
				// Fixes bug #474572 - "invert checkbox in clipping path dialog is ignored when refreshing link"
				if ( iNewClip && iNewClip->GetNumPaths() && iOldClipSettings->GetInvert() )
				{
					// Use the bounds of the image as the outermost path
					InterfacePtr<IGeometry> geometry(srcRoot, IID_IGEOMETRY);
					PMRect imageBounds = geometry->GetPathBoundingBox(PMMatrix());

					iNewClip->InsertNewPath(0);

					iNewClip->AddPoint(0, imageBounds.LeftTop());
					iNewClip->AddPoint(0, imageBounds.RightTop());
					iNewClip->AddPoint(0, imageBounds.RightBottom());
					iNewClip->AddPoint(0, imageBounds.LeftBottom());
					iNewClip->AddPoint(0, imageBounds.LeftTop());

					iNewClip->ClosePath(0);
				}
			}
			CmdUtils::ProcessCommand (setFrameCmd);
		}
	}

	// Preserve text wrap
	Utils<Facade::ITextWrapFacade>()->CopyTextWrap(::GetUIDRef(target), ::GetUIDRef(srcRoot));

	InterfacePtr<IGraphicStyleAttributeBossList>    oldAttributeBossList (target, IID_IGRAPHICSTYLE_OVERRIDES);

	Utils<IXPAttributeUtils> xpAttributeUtils;

	if (oldAttributeBossList)
	{
		// Preserve relevant graphic attributes
		InterfacePtr<IGraphicStateIsApplicable>		iGfxIsApplicable (srcRoot, UseDefaultIID ());
		int32										attrCount = oldAttributeBossList->GetAttributeCount ();
		int32										actualCount = 0;
		K2::scoped_array<ClassID>					pClassList(new ClassID [attrCount]);
		IGraphicStyleAttributeBossList* iXPAttrs = nil;

		ASSERT (pClassList.get() != nil);
		for (uint16 index = 0; index < attrCount; index++) 
		{
			InterfacePtr<IGraphicAttributeInfo>		iAttrInfo (static_cast<IGraphicAttributeInfo*> (oldAttributeBossList->QueryAttributeN (index, IID_IGRAPHICATTR_INFO)));
			ClassID			attrClass = iAttrInfo->GetClass ();
			if (xpAttributeUtils->IsAttributeTransparencyAttribute (attrClass))
			{
				if (!iXPAttrs)
				{
					iXPAttrs = new ObjAttributeBossList();
					iXPAttrs->AddRef();
				}

				if (iXPAttrs) iXPAttrs->AddAttribute(::ScaleXPAttribute(iAttrInfo, xpAttrMatrix, oldAttributeBossList));
			}
			else if (iGfxIsApplicable && iGfxIsApplicable->IsAttributeApplicable (attrClass))
			{
				pClassList [actualCount] = attrClass;
				actualCount++;
			}
		}

		if (iXPAttrs)
		{
			UIDList pageItemList(srcRoot);
			xpAttributeUtils->ApplyAttributesToPageItems(iXPAttrs, pageItemList);
			iXPAttrs->Release();
		}

		if (actualCount > 0)
		{
			UIDList		pageItemList (srcRoot);
			Utils<IGraphicStateUtils> ()->ProcessApplyTargetAttributesToPageItems (oldAttributeBossList, pClassList.get (), actualCount, pageItemList, kTrue, kTrue);
		}
	}
}

bool16 CGraphicPlaceBehavior::CanPlaceInto(eFrameKind newPageItemKind) const
{
	return kFalse;
}

bool16 CGraphicPlaceBehavior::CanPlaceInto(const IPlaceBehavior& sourceItem, const ISpread* spread) const
{
	return kFalse;
}

bool16 CGraphicPlaceBehavior::CanReplace() const
{
	// Don't allow replace unless frame is checked out (use by InCopy).
	InterfacePtr<IHierarchy> hierarchy(this, UseDefaultIID());
	InterfacePtr<IItemLockData> itemLockData((IItemLockData*)Utils<ILayoutUtils>()->QueryOutermostParentFor(hierarchy, IID_IITEMLOCKDATA));
	if (itemLockData && itemLockData->GetInsertLock())
		return kFalse;

	return kTrue;
}

bool16 CGraphicPlaceBehavior::CanConvertTo(eFrameKind newPageItemKind) const
{
	// don't allow converting locked frames
	InterfacePtr<IItemLockData> itemLock(::GetUIDRef(this), UseDefaultIID());
	if (itemLock && itemLock->GetInsertLock())
		return kFalse;

	if (newPageItemKind == kGraphicFrameKind)
		return kTrue;

	// The object which is directly placed in table, can't be converted into text frames.
	if( (newPageItemKind == kTextFrameKind) && !Utils<IPageItemTypeUtils>()->IsPlacedInTable(::GetUIDRef(this)) )
		return kTrue;


	return kFalse;
}


ErrorCode CGraphicPlaceBehavior::ProcessConvertTo(eFrameKind newPageItemKind, IControlView* controlView)
{
	// return a command to turn me into a graphic frame of newPageItemKind
	ErrorCode	result = kFailure;
	switch(newPageItemKind)
	{
	case kUnknownFrameKind :
	case kGraphicFrameKind:
	case kInteractiveFrameKind:
		{
			// This will take care of insets and other housekeeping
			InterfacePtr<ICommand> command ( CmdUtils::CreateCommand(kConvertItemToFrameCmdBoss));
			command->SetItemList(  UIDList(this));
			result =  CmdUtils::ProcessCommand(command);
		} 
		break;
	case kTextFrameKind:
		{
			// This will take care of insets and other housekeeping
			InterfacePtr<ICommand> command ( CmdUtils::CreateCommand(kConvertItemToTextCmdBoss));
			command->SetItemList(  UIDList(this));
			InterfacePtr<IPMUnknownData> activateViewData(command, IID_IACTIVATETEXTEDITOR);
			activateViewData->SetPMUnknown(controlView);
			result =  CmdUtils::ProcessCommand(command);			
		} 
		break;
	default: 
		break;
	}
	return result;
}


UID CGraphicPlaceBehavior::ProcessReplaceMe(const UIDRef& placeGunItem, const UIDRef& oldItem, bool16 usePlaceGunFrame, IPlaceBehavior::eAfterPlace *afterPlace,IItemsToPlaceData::ePlaceFrom placeFrom)
{
	bool16 bClearedPlaceGun = kFalse;
	UID pageItemUID = kInvalidUID;
	CmdUtils::SequenceContext	sequence;
	try
	{
		bool16 bInCopyGraphicStory = kFalse;

		UIDRef itemToReplace(::GetUIDRef(this));
		IDataBase *db = itemToReplace.GetDataBase();

		// Save off pasteboard location and z-order location of item being replaced
		int32 replaceAt = 0;
		InterfacePtr<IHierarchy> itemToReplaceHier(this, UseDefaultIID());
		InterfacePtr<IHierarchy> parentHier(itemToReplaceHier->QueryParent());
		if (parentHier)
		{
			replaceAt = parentHier->GetChildIndex(itemToReplaceHier);
		}
		else if ( ::GetUID( itemToReplaceHier ) != itemToReplaceHier->GetRootUID() )	//#2419984
		{
			ErrorUtils::PMSetGlobalErrorCode(kMissingPluginPageItem);
			PM::FailErrorCode(kMissingPluginPageItem);
		}

		// Preserve XML tagging	
		PreserveXMLElement preserveElement(itemToReplace);

		// Strip the frame off of the place gun item if necessary
		UIDRef content = placeGunItem;

		if(!usePlaceGunFrame)
		{
			// need to strip place gun frame
			InterfacePtr<IHierarchy> placedItemHier(placeGunItem, UseDefaultIID());
			if (placedItemHier->GetChildCount() == 1)
			{
				content = UIDRef(db, placedItemHier->GetChildUID(0));

				// Detach the imported content from the created frame
				InterfacePtr<ICommand> detachContentCmd ( CmdUtils::CreateCommand(kRemoveFromHierarchyCmdBoss));
				detachContentCmd->SetItemList(  UIDList(content));
				PM::FailErrorCode(CmdUtils::ProcessCommand(detachContentCmd));

				// Clear the place gun since we are about to delete the UID that it is holding
				//InterfacePtr<IPlaceGun> placeGun(db, db->GetRootUID(), UseDefaultIID());
				//PM::FailErrorCode(Utils<Facade::IImportExportFacade>()->ClearPlaceGun( placeGun, Facade::IImportExportFacade::kFirstItem ));
				PM::FailErrorCode(ClearFirstItemToPlace(db, placeFrom));
				bClearedPlaceGun = kTrue;

				// Add to cache for objects that have been imported but not (yet) loaded into
				// the place gun or placed onto a spread. Enables these objects to be
				// exposed to scripting for purposes of attachability.
				Utils<IPlaceGunUtils>()->AppendToTemporaryImportCache( content ) ;	//#2419984

				// Clear preserve state flag if this is an incopy graphic story
				InterfacePtr<IInCopyFileInfo> icFileInfo(placeGunItem, UseDefaultIID());
				if (icFileInfo)
					bInCopyGraphicStory = icFileInfo->FileType() == IInCopyFileInfo::kTypeInCopyInterchangeGraphicStory;

				// Delete the placed frame
				InterfacePtr<IScrapItem> placedItemScrap(placeGunItem, IID_ISCRAPITEM);
				InterfacePtr<ICommand>  deleteGFCmd ( placedItemScrap->GetDeleteCmd());
				PM::FailErrorCode(CmdUtils::ProcessCommand(deleteGFCmd));
			}
		}

		if (!bInCopyGraphicStory)
		{
			InterfacePtr<IPlaceBehavior> contentPlaceBehavior(content, UseDefaultIID());
			contentPlaceBehavior->ProcessReplacePreserveState(contentPlaceBehavior, this);
			PM::FailErrorCode();
		}
		else
		{
			// Incopy graphic story, do not preserve state since these settings
			// are inherited from the incx.
			//
			// Except, if not preserving object-level display settings then we
			// do need to transfer the local display setting on the old image
			// (the one being replaced) to the new content; see bug 1064800.
			//
			InterfacePtr<IDrawOptions> iPerfPrefs((IDrawOptions*)::QuerySessionPreferences(IID_IDRAWOPTIONS));
			if (iPerfPrefs && !iPerfPrefs->GetSaveLocalOverrides())
			{
				InterfacePtr<IDrawOptionOverrides const> displayOverrides(this, IID_IDRAWOPTIONOVERRIDE);
				if (displayOverrides) 
				{
					InterfacePtr<ICommand> setDisplaySettingCmd(CmdUtils::CreateCommand(kSetDrawOptionOverrideCmdBoss));
					InterfacePtr<ISetDrawOptionOverrideCmdData> iCmdData(setDisplaySettingCmd, IID_ISETDRAWOPTIONOVERRIDECMDDATA);

					iCmdData->SetDisplayOption(displayOverrides->GetDrawOptionGroup());
					setDisplaySettingCmd->SetItemList(content);

					CmdUtils::ProcessCommand(setDisplaySettingCmd);
				}
			}
		}

		/*
		 Here, we have an issue. We relinked the image and it got it's new Low Res proxy created which is not going to be right if we
		 ever want to use that. This means that we should be copying the old proxy UID and update the XRef mapping to respresent correct UID after relink happens.
		 */
		UID oldImageLowResUID = kInvalidUID;
		bool16 oldImageDataExists = kFalse;
		{
			// See if we can get old image low res proxy UID.
			InterfacePtr<IImageDataAccess> oldImageDataAccess(itemToReplaceHier, UseDefaultIID());
			if (oldImageDataAccess)
				oldImageDataExists = kTrue;
			
			// Now, Only if old image data exists, we do anything about remapping the UID reference.
			if (oldImageDataExists)
				oldImageLowResUID = oldImageDataAccess->GetLowResImageUID();
		}
		
		// Lets see what happens when we update the link. Does it change the UID ??
		UID linkUIDBeforeDelete = Utils<ILinkUtils>()->GetLink(::GetUIDRef(itemToReplaceHier));
		
		InterfacePtr<ILink> link(::GetDataBase(itemToReplaceHier), linkUIDBeforeDelete, UseDefaultIID());
		ILinkResource::ResourceId linkURI;
		if (link && oldImageDataExists) {
			InterfacePtr<ILinkResource> linkResource(::GetDataBase(link), link->GetResource(), UseDefaultIID());
			linkURI = linkResource->GetId();
		}
		
		bool16 bItemToReplaceIsLocked = kFalse;
		{	// do it the right way
			InterfacePtr<ICommand>	deleteItemCmd(CmdUtils::CreateCommand(kDeleteCmdBoss));
			deleteItemCmd->SetItemList( UIDList( itemToReplaceHier) );

			// Save the lock status of itemToReplace before deletion.
			InterfacePtr<ILockPosition> itemToReplaceLock(itemToReplace, UseDefaultIID());
			if (itemToReplaceLock && itemToReplaceLock->IsLocked())
				bItemToReplaceIsLocked = kTrue;

			// [RCR] 6/25/99 #310635 & #310416
			InterfacePtr<IIntData> preserveGroups(deleteItemCmd, UseDefaultIID());
			ASSERT_MSG(preserveGroups != nil, "Missing private IntData on delete command");

			// Tell the delete command not to remove groups
			// 0 - Delete empty groups, Preserve 1 item groups (Default)
			// 1 - Delete empty groups, Ungroup 1 item groups
			// 2 - Preserve empty groups, Preserve 1 item groups
			preserveGroups->Set(2);

			PM::FailErrorCode(CmdUtils::ProcessCommand(deleteItemCmd));
		}
		

		if ( parentHier )
		{
			// Attach new item in hierarchy in old one's spot in the z-order
			InterfacePtr<ICommand> attachNewItemCmd ( CmdUtils::CreateCommand(kAddToHierarchyCmdBoss));
			InterfacePtr<IHierarchyCmdData>pCmdData(attachNewItemCmd, UseDefaultIID());
			pCmdData->SetParent(::GetUIDRef(parentHier));
			K2Vector<int32> indexList;
			indexList.push_back (replaceAt);
			pCmdData->SetIndexInParent(indexList);
			attachNewItemCmd->SetItemList(UIDList(content));
			PM::FailErrorCode(CmdUtils::ProcessCommand(attachNewItemCmd));
		}
		
		UID linkAfterReparent = Utils<ILinkUtils>()->GetLink(content);
		
		
		// Content is the new image that has been imported on updating the image by "Edit with... workflow".
		UID newImageLowResUID = kInvalidUID;
		if (oldImageDataExists && link)
		{
			InterfacePtr<IImageDataAccess> newImageDataAccess(content, UseDefaultIID());
			newImageLowResUID = newImageDataAccess ? newImageDataAccess->GetLowResImageUID() : kInvalidUID;
			
			// Now, if we have both old and new image proxy UIDs, we should update the XRef Table so that when we are pasting the image copied before update, we will get right UID after update.
			if (newImageLowResUID != kInvalidUID && oldImageLowResUID != kInvalidUID)
			{
				InterfacePtr<IDataExchangeController> deController( GetExecutionContextSession(), IID_ICLIPBOARDCONTROLLER);
				IDataBase* scrapDB = deController->GetScrapDataBase();
				
				InterfacePtr<ILinkManager> linkMgr(scrapDB, scrapDB->GetRootUID(), UseDefaultIID());
				UIDList allLinks(scrapDB);
				LinkQuery query;
				linkMgr->QueryLinks(query, kIDLinkClientID, allLinks);
				for (int32 i =0; i < allLinks.Length(); ++i)
				{
					InterfacePtr<ILink> scrapLink(scrapDB, allLinks.At(i), UseDefaultIID());
					InterfacePtr<ILinkResource> scrapLinkResource(scrapDB, scrapLink->GetResource(), UseDefaultIID());
					if (linkURI == scrapLinkResource->GetId())
					{
						Utils<Facade::ILinkFacade>()->SetLinkResourceModStates(UIDList(scrapDB, allLinks.At(i)), ILink::kResourceModified);
					}
				}
				
 			}
		}

		//	clear place gun (if loaded and not an INX operation) after the replace
		//  We don't want to clear the placegun in INX because in those situations,
		//  then we really don't use the placegun, and clearing might mess up a
		//  snippet import if there's multiple embedded snippet files being imported at once. (richg)
		if (!bClearedPlaceGun && !Utils<IScriptUtils>()->IsINX())
		{
			InterfacePtr<IDocument> doc(db, db->GetRootUID(), UseDefaultIID());
			//InterfacePtr<IPlaceGun> placeGun(doc, UseDefaultIID());
			//PM::FailErrorCode(Utils<Facade::IImportExportFacade>()->ClearPlaceGun( placeGun, Facade::IImportExportFacade::kFirstItem ));
			PM::FailErrorCode(ClearFirstItemToPlace(db, placeFrom));
			bClearedPlaceGun = kTrue;
		}

		// If itemToReplace is locked before deletion, we should keep the newItem locked too.
		// This fixed bug #434063. - Yeming Liu(05/31/2001)
		if (bItemToReplaceIsLocked)
		{
			InterfacePtr<ILockPosition> newItemLock(content, UseDefaultIID());
			if (newItemLock && newItemLock->IsUnlocked())
			{
				InterfacePtr<ICommand> lockCmd(CmdUtils::CreateCommand(kSetLockPositionCmdBoss));
				UIDList itemList(content);
				lockCmd->SetItemList(itemList);
				InterfacePtr<IIntData> intData(lockCmd, UseDefaultIID());
				intData->Set(ILockPosition::kLock);
				PM::FailErrorCode(CmdUtils::ProcessCommand(lockCmd));
			}
		}

		pageItemUID = content.GetUID();

		// set the new content for XML preservation
		preserveElement.SetFrame(content);
	}
	catch (ErrorCode&) {
	}

	if (afterPlace)
		*afterPlace = bClearedPlaceGun ? IPlaceBehavior::kLeaveAsIs : IPlaceBehavior::kOldBehavior;

	return pageItemUID;
}


UID CGraphicPlaceBehavior::ProcessReplaceChildren(const UIDRef& placeGunItem, const UIDRef& oldItem, bool16 usePlaceGunFrame, IPlaceBehavior::eAfterPlace *afterPlace)
{
	ASSERT_FAIL("CGraphicPlaceBehavior::ReplaceChildren: should never reach here. Use SplineBehavior instead.");
	return kInvalidUID;
}

// helpers //

IPlaceBehavior::eFrameKind CGraphicPlaceBehavior::GetFrameKind() const
{
	return kGraphicFrameKind;
}

bool16 CGraphicPlaceBehavior::IsEmpty() const
{
	return kFalse;
}

bool16 CGraphicPlaceBehavior::IsFromMaster(const IHierarchy* hier, const ISpread* spread) const
{
	UID activeSpreadUID = kInvalidUID;

	if (spread == nil)
	{
		// RichG modified next lines to not use LayoutControlData, which isn't available if structure view active
		IDocument *frontDoc = GetExecutionContextSession()->GetActiveContext()->GetContextDocument();
		InterfacePtr<IPersistUIDData> curSpread(frontDoc, IID_ICURRENTSPREAD);
		activeSpreadUID = curSpread->GetUID();
	}
	else
		activeSpreadUID = ::GetUID(spread);

	// get item's spread
	if (hier)
	{
		UID	mySpreadUID = hier->GetSpreadUID();
		return (mySpreadUID != activeSpreadUID) && (mySpreadUID != kInvalidUID);
	}

	return kFalse;
}

bool16 CGraphicPlaceBehavior::IsItemMasterNotOverrideable(const IHierarchy* hier, const ISpread* spread) const
{
	if(this->IsFromMaster(hier, spread))
	{
		InterfacePtr<IMasterOverrideable> masterOverrideable(hier, IID_IMASTEROVERRIDEABLE ) ; 
		if (masterOverrideable && masterOverrideable->IsMasterNotOverrideable())
		{
			return kTrue;
		}
	}
	return kFalse;
}

bool16 CGraphicPlaceBehavior::IsItemRoot() const
{
	InterfacePtr<IHierarchy> hier(const_cast<CGraphicPlaceBehavior*>(this), UseDefaultIID());
	InterfacePtr<IHierarchy> parent(hier->QueryParent());
	InterfacePtr<IPlaceBehavior> parentBehavior(parent, UseDefaultIID());
	return parentBehavior == nil;
}

IPlaceBehavior* CGraphicPlaceBehavior::QueryItemRoot()
{
	ASSERT_FAIL("CGraphicPlaceBehavior::QueryItemRoot: Not Yet Implemented");
	IPlaceBehavior* current = this;
#if 0
	current->AddRef();
	IPlaceBehavior* parentBehavior = nil;
	do{
		InterfacePtr<IHierarchy> hier(current, UseDefaultIID());
		InterfacePtr<IHierarchy> parent(hier->QueryParent());
		IPlaceBehavior* parentBehavior = parent->QueryInterface(IID_IPLACEBEHAVIOR);
		if(parentBehavior){
			current->Release();
			current = parentBehavior;
		}
	}while(parentBehavior);
#endif
	return current;
}


static uint32 GetAlphaCount(IPMUnknown* graphic)
{
	uint32 count = 0;

	InterfacePtr<IImageAttributes> iImageAttributes(graphic, IID_IIMAGEATTRIBUTES);

	if ( iImageAttributes ) {
		uint32 samplesPerPixel(0), colorSamples(0);
		iImageAttributes->GetTag (IImageAttributes::kPMTagChannelsPerPixel, &samplesPerPixel);

		if ( iImageAttributes->TagExists (IImageAttributes::kPMTagColorMap) )
			colorSamples = 1;
		else {
			uint32 colorSpace;

			iImageAttributes->GetTag (IImageAttributes::kPMTagColorSpace, &colorSpace);
			switch (colorSpace)
			{
			case kPMGrayColorSpace:
				colorSamples = 1;
				break;

			case kPMRGBColorSpace:
			case kPMICCLabColorSpace:
				colorSamples = 3;
				break;

			case kPMCMYKColorSpace:
				colorSamples = 4;
				break;
				//TODO: What about other image color spaces as per ImageTypes.h. Also similar code exists inside the TextWrapFacade.cpp and is a candidate for consolidation.
			}
		}

		if ( samplesPerPixel > colorSamples ) {
			count = samplesPerPixel - colorSamples;
		}
	}

	return count;
}

static uint32 GetClipCount(IPMUnknown* graphic)
{
	uint32 clipCount = 0;

	InterfacePtr<IImageAttributes> iImageAttributes(graphic, IID_IIMAGEATTRIBUTES);

	if ( iImageAttributes ) {
		// The new image is raster so look in its tags for a clip path.
		if ( iImageAttributes->TagExists (IImageAttributes::kPMTagTIFFClipPath)
			|| iImageAttributes->TagExists (IImageAttributes::kPMTagPhotoshop8BIM) )
		{
			uint32 imageResourceSize = iImageAttributes->GetTagSize (IImageAttributes::kPMTagPhotoshop8BIM);
			char *resourceData = new char [imageResourceSize];
			if ( resourceData ) {
				iImageAttributes->GetTag (IImageAttributes::kPMTagPhotoshop8BIM, resourceData);

				PMString clipName;
				clipCount = GetPSEmbeddedPathNames(resourceData,
					imageResourceSize,
					nil,
					clipName);

				delete [] resourceData;
			}
		}
	}
	else {
		// The new image is not raster so check for an EPS.  If it is an EPS
		// then look in its tag table for the data which may contain the clip path
		// and try to extract it.
		InterfacePtr<IEPSTagTable> iEPSTagTable(graphic, IID_IEPSTAGTABLE);
		std::string data;
		uint32 count;
		if ( iEPSTagTable && iEPSTagTable->GetPhotoShopClipData(0, &data, &count) == kSuccess)
		{
			// So we have a photoshop EPS.  Now look within the data for a clip path.
			PMString clipName;
			clipCount = GetPSEmbeddedPathNames(data.c_str(),
				count,
				nil,
				clipName);
		}
	}

	return clipCount;
}

void CGraphicPlaceBehavior::HandleXMPRotation(IPersistUIDData* uidData, bool16 modifyFrame)
{
	if (uidData)
	{
		UIDRef uidRef(::GetUIDRef(uidData));

		int16 metaDataOrient = 0;
		// see if there is rotation defined in the meta data (i.e. rotated in Bridge)
		if (Utils<IImageUtils>()->GetMetaDataOrientation(uidRef, &metaDataOrient) == kSuccess)
		{
			PMReal angle(metaDataOrient);
			if (angle != 90 && angle != -90)
				modifyFrame = kFalse;

			// we only have to do something if there is an angle other than zero
			if (angle != 0)
			{
				// get some interfaces off of the image
				InterfacePtr<ITransform> iTransform(uidData, UseDefaultIID());
				InterfacePtr<IGeometry> iGeometry(uidData, UseDefaultIID());
				if (iTransform && iGeometry)
				{
					// get the current transform
					PMMatrix ctm = iTransform->GetInnerToParentMatrix();
					// get the bounding box
					PMRect bbox = iGeometry->GetPathBoundingBox(ctm);
					// determine the top left of the image
					PMPoint topLeft = bbox.LeftTop();
					// rotate the matrix by the angle
					ctm.Rotate(angle);
					// get the rotated bounding box
					PMRect rotBBox = iGeometry->GetPathBoundingBox(ctm);
					// get the top left of the rotated bounding box
					PMPoint rotTopLeft = rotBBox.LeftTop();
					// determine how far we have to move to line up the top left corner
					// of the rotated BBox to where the original top left was 
					PMPoint delta = topLeft - rotTopLeft;
					// move that far via transform
					ctm.Translate(delta.X(), delta.Y());
					// set the new matrix into the ITransform
					iTransform->SetInnerToParentMatrix(ctm);
				}
			}
		}

		if (modifyFrame)
		{
			// if this is the first placement, we fit the frame to the content
			Utils<Facade::IFrameContentFacade> iFrameContentFacade;
			ASSERT (iFrameContentFacade != nil);
			UIDList itemList(::GetDataBase(uidData), ::GetUID(uidData));
			if (iFrameContentFacade && iFrameContentFacade->CanFitFrameToContent (itemList))
			{
				ErrorCode err = iFrameContentFacade->FitFrameToContent(itemList);
				ASSERT_MSG (err == kSuccess, "CGraphicPlaceBehavior::HandleXMPRotation, Can't get CanFitFrameToContent graphic.");
			}
		}
	}
}

double GetAngleInRadians(IGraphicStyleAttributeBossList const *attrs, IXPAttributeSuite::AttributeType type)
{
	Utils<IXPAttributeUtils> utils;
	InterfacePtr<IGraphicAttributeInfo> angleAttr(static_cast<IGraphicAttributeInfo *>(attrs->QueryAttribute(utils->GetAttributeClassID(type), IGraphicAttributeInfo::kDefaultIID)));
	IXPAttributeSuite::AttributeValue value;

	if (angleAttr && utils->GetAttributeValue(type, value, angleAttr) == kSuccess)
	{
		return ::ToDouble(value.GetReal() * kPMPi / 180.);
	}

	return 0.;
}

InterfacePtr<IGraphicAttributeInfo> ScaleXPAttribute(IGraphicAttributeInfo *attr, PMMatrix const &m, IGraphicStyleAttributeBossList const *attrs)
{
	InterfacePtr<IGraphicAttributeInfo> scaledAttr(attr, UseDefaultIID());

	if (!m.IsIdentity())
	{
		Utils<IXPAttributeUtils> utils;
		IXPAttributeSuite::AttributeType type = utils->GetAttributeFromClassID(attr->GetClass());		

		switch (type)
		{
		case IXPAttributeSuite::kGradientFeatherCenter:
		case IXPAttributeSuite::kGradientFeatherLength:
		case IXPAttributeSuite::kGradientFeatherHiliteLength:
			{
				IXPAttributeSuite::AttributeValue value;

				if (utils->GetAttributeValue(type, value, attr) == kSuccess)
				{
					if (type == IXPAttributeSuite::kGradientFeatherCenter)
					{
						PMPoint point = value.GetPMPoint();
						m.Transform(&point);

						value = IXPAttributeSuite::AttributeValue(point);
					}
					else
					{
						PMMatrix temp(m);
						temp.TranslateTo(0, 0);

						double angle = ::GetAngleInRadians(attrs, type == IXPAttributeSuite::kGradientFeatherLength ? IXPAttributeSuite::kGradientFeatherAngle : IXPAttributeSuite::kGradientFeatherHiliteAngle);
						PMReal length = value.GetReal();
						PMReal x = length * std::cos(angle);
						PMReal y = length * std::sin(angle);

						temp.Transform(&x, &y);
						length = ::hypot(::ToDouble(x), ::ToDouble(y));

						value = IXPAttributeSuite::AttributeValue(length);
					}

					InterfacePtr<IPMUnknown> newAttr(utils->CreateAttribute(type, value));

					scaledAttr = InterfacePtr<IGraphicAttributeInfo>(newAttr, UseDefaultIID());
				}
			}
			break;

		default:
			break;
		}
	}

	return scaledAttr;
}

// if we are placing a graphic into a frame and the frame has a "wrap around object shape"
// text wrap, move the wrap to the graphic.
ErrorCode MoveWrapFromFrameToGraphic(const UIDRef& itemToPlaceInto, const UIDRef& content)
{
	// grab text wrap info of frame and graphic
	Facade::ITextWrapFacade* iTextWrapFacade = Utils<Facade::ITextWrapFacade>();
	IStandOff::mode frameMode = iTextWrapFacade->GetMode(itemToPlaceInto);

	if ( frameMode == IStandOff::kManualContour
		&& iTextWrapFacade->GetMode(content) == IStandOff::kNone 
		&& !iTextWrapFacade->GetUserModified(itemToPlaceInto) )
	{
		// apply the standoff to the content.
		Utils<Facade::ITextWrapFacade>()->CopyTextWrap(itemToPlaceInto, content);
		Utils<Facade::ITextWrapFacade>()->SetMode(itemToPlaceInto, IStandOff::kNone, kFalse);
	}

	return kSuccess;
}

//Return a list of script objects corresponding to the source content
void CGraphicPlaceBehavior::AppendScriptObjects( ScriptList& objectList )
{
	objectList.push_back( InterfacePtr<IScript>( this, UseDefaultIID() ) ) ;
}



// methods to access PlaceGun(or PlaceHead).	
bool16 CGraphicPlaceBehavior::IsPlaceLoaded(IDataBase* db, IItemsToPlaceData::ePlaceFrom placeFrom) const
{
	if (placeFrom == IItemsToPlaceData::kPlaceGun)
	{
		InterfacePtr<IPlaceGun> iPlaceGun(db, db->GetRootUID(), UseDefaultIID());
		ASSERT_MSG(iPlaceGun != nil, "Missing PlaceGun on Document");
		return iPlaceGun->IsLoaded();
	}
	
	InterfacePtr<IUIDRefListData> iPlaceHead (db, db->GetRootUID(), IID_IPLACEHEAD);
	ASSERT_MSG(iPlaceHead != nil, "Missing PlaceHead on Document");
	return (iPlaceHead->size() > 0);
}
UID CGraphicPlaceBehavior::GetFirstItemToPlaceUID(IDataBase* db, IItemsToPlaceData::ePlaceFrom placeFrom) const
{
	if (placeFrom == IItemsToPlaceData::kPlaceGun)
	{
		InterfacePtr<IPlaceGun> iPlaceGun(db, db->GetRootUID(), UseDefaultIID());
		ASSERT_MSG(iPlaceGun != nil, "Missing PlaceGun on Document");
		return iPlaceGun->GetFirstPlaceGunItemUID();
	}

	InterfacePtr<IUIDRefListData> iPlaceHead (db, db->GetRootUID(), IID_IPLACEHEAD);
	ASSERT_MSG(iPlaceHead != nil, "Missing PlaceHead on Document");	
	if(iPlaceHead->size() > 0)
	{
		return (iPlaceHead->at(0)).GetUID();
	}
	else 
	{
		return kInvalidUID;
	}
}

ErrorCode CGraphicPlaceBehavior::ClearFirstItemToPlace(IDataBase* db, IItemsToPlaceData::ePlaceFrom placeFrom) const
{
	if (placeFrom == IItemsToPlaceData::kPlaceGun)
	{
		InterfacePtr<IPlaceGun> iPlaceGun(db, db->GetRootUID(), UseDefaultIID());
		ASSERT_MSG(iPlaceGun != nil, "Missing PlaceGun on Document");
		return Utils<Facade::IImportExportFacade>()->ClearPlaceGun( iPlaceGun, Facade::IImportExportFacade::kFirstItem );
	}

	InterfacePtr<IUIDRefListData> iPlaceHead (db, db->GetRootUID(), IID_IPLACEHEAD);
	ASSERT_MSG(iPlaceHead != nil, "Missing PlaceHead on Document");
	if(iPlaceHead->size() > 0)
		iPlaceHead->Remove(0);
	return kSuccess;
}

ErrorCode CGraphicPlaceBehavior::AbortFirstItemToPlace(IDataBase* db, IItemsToPlaceData::ePlaceFrom placeFrom) const
{
	if (placeFrom == IItemsToPlaceData::kPlaceGun)
	{
		InterfacePtr<IPlaceGun> iPlaceGun(db, db->GetRootUID(), UseDefaultIID());
		ASSERT_MSG(iPlaceGun != nil, "Missing PlaceGun on Document");
		return Utils<Facade::IImportExportFacade>()->AbortPlaceGun( iPlaceGun, Facade::IImportExportFacade::kFirstItem );
	}

	InterfacePtr<IUIDRefListData> iPlaceHead (db, db->GetRootUID(), IID_IPLACEHEAD);
	ASSERT_MSG(iPlaceHead != nil, "Missing PlaceHead on Document");
	return (kSuccess);


}
ErrorCode CGraphicPlaceBehavior::AbortAllItemsToPlace(IDataBase* db, IItemsToPlaceData::ePlaceFrom placeFrom) const
{
	if (placeFrom == IItemsToPlaceData::kPlaceGun)
	{
		InterfacePtr<IPlaceGun> iPlaceGun(db, db->GetRootUID(), UseDefaultIID());
		ASSERT_MSG(iPlaceGun != nil, "Missing PlaceGun on Document");
		return Utils<Facade::IImportExportFacade>()->AbortPlaceGun( iPlaceGun, Facade::IImportExportFacade::kAllItems );
	}

	InterfacePtr<IUIDRefListData> iPlaceHead (db, db->GetRootUID(), IID_IPLACEHEAD);
	ASSERT_MSG(iPlaceHead != nil, "Missing PlaceHead on Document");
	return (kSuccess);

}

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/components/adaptive/CPageItemAdaptiveTransform.cpp $
//  
//  Owner: Sachin Singhal
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
//  Copyright 1997-2018 Adobe Systems Incorporated. All rights reserved.
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

#include "VCPublicHeaders.h"

#include "IAdaptiveHelper.h"
#include "IBoolData.h"
#include "IBoundsData.h"
#include "IHierarchy.h"
#include "IIntData.h"
#include "ILockPosition.h"
#include "IMainItemTOPData.h"
#include "IPageSetupPrefs.h"
#include "IPathGeometry.h"
#include "IResizeItemsCmdData.h"
#include "ISpreadLayer.h"

#include "IPathUtils.h"
#include "IPageItemTypeUtils.h"
#include "IPageItemVisibilityFacade.h"
#include "ILayoutUtils.h"
#include "ITransformFacade.h"
#include "IAdaptiveLayoutUtils.h"

#include "CPageItemAdaptiveTransform.h"
#include "PreferenceUtils.h"
#include "IPathTypeUtils.h"
#include "TransformUtils.h"


CPageItemAdaptiveTransform::CPageItemAdaptiveTransform(IPMUnknown *boss) :
	CPMUnknown<IAdaptiveTransform>(boss), fData(NULL)
{
}

/*
void CPageItemAdaptiveTransform::SetInitialBounds(PMRect bounds)
{
    InterfacePtr<IAdaptiveData> adaptiveData(this, UseDefaultIID());
    if (adaptiveData)
        adaptiveData->SetInitialBounds(bounds);
}*/

/*
void CPageItemAdaptiveTransform::SetFinalBounds(PMRect bounds)
{
    InterfacePtr<IAdaptiveData> adaptiveData(this, UseDefaultIID());
    if (adaptiveData)
        adaptiveData->SetFinalBounds(bounds);
}*/

UIDList CPageItemAdaptiveTransform::CollectDependents()
{
	if (!fData->fDependentsInitialised)
	{
		UIDList dependents(::GetDataBase(this));
		InterfacePtr<IHierarchy> hierarchy(this, IID_IHIERARCHY);
		if (hierarchy)
		{
			for (int16 childIndex = 0; childIndex < hierarchy->GetChildCount(); childIndex++)
			{
				InterfacePtr<IHierarchy> childHier(hierarchy->QueryChild(childIndex));
				dependents.push_back(::GetUID(childHier));
			}
		}

		// Collect TOP item, if any
		InterfacePtr<IMainItemTOPData> iTOPData(this, IID_IMAINITEMTOPDATA);
		InterfacePtr<IPathGeometry>mainPathGeometry(this, IID_IPATHGEOMETRY);
		if (mainPathGeometry && mainPathGeometry->GetNumPaths() > 0)
		{
			InterfacePtr<IMainItemTOPData> mainItemTOPData(mainPathGeometry, IID_IMAINITEMTOPDATA);
			if (mainItemTOPData)
			{
				fData->fTOPUID = mainItemTOPData->GetTOPSplineItemUID();
				if (fData->fTOPUID != kInvalidUID)
					dependents.push_back(fData->fTOPUID);
			}
		}
		fData->fDependents = dependents;
		fData->fDependentsInitialised = kTrue;
	}
	return fData->fDependents;
}

ErrorCode CPageItemAdaptiveTransform::ProcessDependents(CPageItemAdaptiveTransform::STAGE stage)
{
	// Iterate over children
	ErrorCode err = kSuccess;
	if(!fData->fDependentsInitialised)
		CollectDependents();
	for (int16 index = 0; index < fData->fDependents.Length(); index++)
	{
		InterfacePtr<IAdaptiveTransform> adaptiveTransform(fData->fDependents.GetRef(index), UseDefaultIID());
		if (adaptiveTransform)
		{
			switch (stage)
			{
			case PREPROCESS:
                err = adaptiveTransform->PreProcess();
				break;
			case PROCESS:
				err = adaptiveTransform->Process();
				break;
			case POSTPROCESS:
				err = adaptiveTransform->PostProcess();
				break;
			case FINISH:
				adaptiveTransform->Finish();
				break;
			}
		}
		else
		{
			IDataBase* db = ::GetDataBase(this);
			UID dependentUID = fData->fDependents.GetRef(index).GetUID();
		}
		if (err != kSuccess)
			return err;
	}

	return err;
}

ErrorCode CPageItemAdaptiveTransform::PreProcess()
{
    UIDRef pageItemRef(::GetUIDRef(this));

	InterfacePtr<IAdaptiveTransientData> adaptiveTransientData(::GetExecutionContextSession(), IID_IADAPTIVETRANSIENTDATA);
	fData = adaptiveTransientData->GetData(pageItemRef.GetUID());
    
	ErrorCode err = PreProcessThis();
	HANDLE_ADAPTIVE_ERR(err, "Error during PreProcessing.");
	err = ProcessDependents(PREPROCESS);
	HANDLE_ADAPTIVE_ERR(err, "Error during PreProcessing dependents.");
	return kSuccess;
}

ErrorCode CPageItemAdaptiveTransform::Process()
{
	ErrorCode err = kSuccess;
	if (ShouldProcessThis())
	{
		if (!fData)
		{
			UIDRef pageItemRef(::GetUIDRef(this));
			InterfacePtr<IAdaptiveTransientData> adaptiveTransientData(::GetExecutionContextSession(), IID_IADAPTIVETRANSIENTDATA);
			fData = adaptiveTransientData->GetData(pageItemRef.GetUID());
		}
		UnlockIfNeeded();
		err = ProcessThis();
		HANDLE_ADAPTIVE_ERR(err, "Error during Processing.");
		if (err != kSuccess)
			return err;

		// Now adjust the children.
		err = ProcessDependents(PROCESS);
		HANDLE_ADAPTIVE_ERR(err, "Error during Processing dependents.");
	}

	return kSuccess;
}

ErrorCode CPageItemAdaptiveTransform::PreProcessThis()
{
	fData->fInitialBounds = Utils<Facade::IGeometryFacade>()->GetItemBounds(::GetUIDRef(this), Transform::SpreadCoordinates(), Geometry::OuterStrokeBounds());
    
	// Binding information.
	fData->fLeftToRightBinding = true;
	InterfacePtr<IPageSetupPrefs> iPagePrefs((IPageSetupPrefs*)::QueryPreferences(IID_IPAGEPREFERENCES, GetExecutionContextSession()->GetActiveContext()));
	if (iPagePrefs)
		fData->fLeftToRightBinding = iPagePrefs->GetPageBindingPref() == kLeftToRightBinding;

	UIDRef mainSplineUIDRef = ::GetUIDRef(this);
	Utils<IPathTypeUtils>()->GetStartPoint(mainSplineUIDRef, fData->fStartPoint);
	Utils<IPathTypeUtils>()->GetEndPoint(mainSplineUIDRef, fData->fEndPoint);

	InterfacePtr<IPathGeometry>  pathGeometry(mainSplineUIDRef, IID_IPATHGEOMETRY);
    ::TransformInnerPointToSpread(pathGeometry, &fData->fStartPoint);
    ::TransformInnerPointToSpread(pathGeometry, &fData->fEndPoint);

	return kSuccess;
}

bool16 CPageItemAdaptiveTransform::ShouldProcessThis()
{
	if (!ShouldHandleLocked())
	{
		if (IsCurrentItemLocked())
			return kFalse;
	}

	// Add any new checks here.

	//Always keep at end of checks.
	if (!ShouldHandleHidden())
	{
		if (IsCurrentItemHidden())
		{
			InterfacePtr<IBoolData> adaptiveHiddenItemFound(::GetExecutionContextSession(), IID_IADAPTIVEHIDDENITEMFOUND);
			if (adaptiveHiddenItemFound)
				adaptiveHiddenItemFound->Set(kTrue);
			return kFalse;
		}
	}
	return kTrue;
}

bool16 CPageItemAdaptiveTransform::IsCurrentItemLocked()
{
	UIDRef pageItemRef = ::GetUIDRef(this);

	InterfacePtr<ILockPosition> lock(pageItemRef, IID_ILOCKPOSITION);
	if (lock && lock->IsPageItemLocked(kFalse))
		return kTrue;

	InterfacePtr<IHierarchy> hierarchy(pageItemRef, UseDefaultIID());
	if (hierarchy)
	{
		InterfacePtr<const ISpreadLayer> spreadLayer(pageItemRef.GetDataBase(), hierarchy->GetLayerUID(), UseDefaultIID());
		if (spreadLayer && spreadLayer->IsLocked())
			return kTrue;
	}

	return kFalse;
}

bool16 CPageItemAdaptiveTransform::IsCurrentItemHidden()
{
	UIDRef pageItemRef = ::GetUIDRef(this);

	Utils<Facade::IPageItemVisibilityFacade> pageItemVisibilityFacade;
	ASSERT_MSG(pageItemVisibilityFacade, "Could not obtain IPageItemVisibilityFacade.");

	if (pageItemVisibilityFacade->IsHidden(pageItemRef))
		return kTrue;

	InterfacePtr<IHierarchy> hierarchy(pageItemRef, UseDefaultIID());
	if (hierarchy)
	{
		InterfacePtr<const ISpreadLayer> spreadLayer(pageItemRef.GetDataBase(), hierarchy->GetLayerUID(), UseDefaultIID());
		if (spreadLayer && !spreadLayer->IsVisible())
			return kTrue;
	}

	return kFalse;
}

ErrorCode CPageItemAdaptiveTransform::Resize()
{
	ErrorCode err = kSuccess;
	UIDRef pageItemRef = ::GetUIDRef(this);
	UIDList pageItemList(pageItemRef);
	IDataBase* db = pageItemRef.GetDataBase();

	InterfacePtr<IAdaptiveHelper> adaptiveHelper(db, db->GetRootUID(), UseDefaultIID());
	PMPoint itemMinSize = adaptiveHelper->GetMinSizeOfObject(pageItemRef);

	// If the object's final size is less than its minimum size, set its final size to its minimum size 
	if (fData->fFinalBounds.Width() < itemMinSize.X())
		fData->fFinalBounds.SetWidth(itemMinSize.X());

	if (fData->fFinalBounds.Height() < itemMinSize.Y())
		fData->fFinalBounds.SetHeight(itemMinSize.Y());

	// See if the item's height and width can be changed or not. If not reset it to the previous value.
	Utils<Facade::IGeometryFacade> geometryFacade;
	if (fData->fFinalBounds.Height() != fData->fInitialBounds.Height())
	{
		if (!geometryFacade->CanChangeItemsHeight(pageItemList, Transform::SpreadCoordinates()))
			fData->fFinalBounds.SetHeight(fData->fInitialBounds.Height());
	}
	if (fData->fFinalBounds.Width() != fData->fInitialBounds.Width())
	{
		if (!geometryFacade->CanChangeItemsWidth(pageItemList, Transform::SpreadCoordinates()))
		{
			if(fData->fLeftToRightBinding)
				fData->fFinalBounds.SetWidth(fData->fInitialBounds.Width());
			else
			{
				fData->fFinalBounds.Left(fData->fFinalBounds.Right() - (fData->fInitialBounds.Right() - fData->fInitialBounds.Left()));
			}
		}
	}

	// Adjust this page item.
	InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kResizeItemsCmdBoss));

	if (cmd)
	{
		InterfacePtr<IResizeItemsCmdData> data(cmd, IID_IRESIZEITEMSCMDDATA);
		InterfacePtr<IBoundsData> boundsData(cmd, UseDefaultIID());
		if (boundsData) 
			boundsData->SetNoBoundsChecking();
				
		cmd->SetItemList(UIDList(pageItemList));
		data->SetResizeData(Transform::SpreadCoordinates(), Geometry::OuterStrokeBounds(), Transform::SpreadLocation(PMPoint(0,0)), Geometry::ResizeTo(fData->fFinalBounds.Width(), fData->fFinalBounds.Height()));
		err = CmdUtils::ProcessCommand(cmd);
        
		HANDLE_ADAPTIVE_ERR(err, "error in processing IResizeItemsCmdData");
	}

	return err;
}

ErrorCode CPageItemAdaptiveTransform::Reposition()
{
	ErrorCode err = kSuccess;
	UIDRef pageItemRef = ::GetUIDRef(this);
	UIDList pageItemList(pageItemRef);

    //Generic repositioning to be used for every page item
    //if (pageItemUtils->IsDirectInlineItem(item))
    Utils<IPageItemTypeUtils> pageItemUtils;
    if (pageItemUtils->IsInline(pageItemRef))
    {
        UIDRef pageItemRef = ::GetUIDRef(this);
        InterfacePtr<IHierarchy> iPageItemHierarchy (pageItemRef, IID_IHIERARCHY);
        InterfacePtr<IHierarchy> iHierarchyRoot(iPageItemHierarchy ? (iPageItemHierarchy)->QueryRoot() : nil);
        InterfacePtr<IAnchoredObjectData> anchoredObjectData(iHierarchyRoot, UseDefaultIID());
		UIDRef anchoredItemRef(::GetUIDRef(anchoredObjectData));

		InterfacePtr<IAdaptiveTransientData> adaptiveTransientData(::GetExecutionContextSession(), IID_IADAPTIVETRANSIENTDATA);
		AdapativePageItemData *data = adaptiveTransientData->GetData(anchoredItemRef.GetUID());

        if (data)
			data->SetRecommendedBounds(fData->fFinalBounds);
        return err;
    }
	
	PMRect currentBounds = Utils<Facade::IGeometryFacade>()->GetItemBounds(pageItemRef, Transform::SpreadCoordinates(), Geometry::OuterStrokeBounds());
	PMPoint translateBy;
	
	if (fData->fLeftToRightBinding)		//align Top left
		translateBy = PMPoint(fData->fFinalBounds.Left() - currentBounds.Left(), fData->fFinalBounds.Top() - currentBounds.Top());
	else					//align Top Right
		translateBy = PMPoint(fData->fFinalBounds.Right() - currentBounds.Right(), fData->fFinalBounds.Top() - currentBounds.Top());
	
	Utils<IAdaptiveLayoutUtils> adaptiveLayoutUtils;
	err = adaptiveLayoutUtils->TransformItems(pageItemList, Transform::SpreadCoordinates(), Transform::CurrentOrigin(),
										  Transform::TranslateBy(translateBy), Transform::UseLensScaling());
	HANDLE_ADAPTIVE_ERR(err, "error in repositioning");

    // if it contains TOP, it's abscissas needs to be updated to start at new start point and end point.
    if (fData->fTOPUID != kInvalidUID)
        Utils<IPathTypeUtils>()->UpdateAbscissa(pageItemRef, fData->fFinalStartPoint, fData->fFinalEndPoint);

    return err;
}

ErrorCode CPageItemAdaptiveTransform::ProcessThis()
{
	ErrorCode err = kSuccess;
	
	UIDRef pageItemRef = ::GetUIDRef(this);
	UIDList pageItemList(pageItemRef);

	//First retrieve the final bound for this one by sending flags for aspect ratio, binding.
	IDataBase* db = pageItemRef.GetDataBase();
	InterfacePtr<IAdaptiveHelper> adaptiveHelper(db, db->GetRootUID(), UseDefaultIID());
	fData->fFinalBounds = adaptiveHelper->GetFinalBoundsForPageItem(pageItemRef, fData->fInitialBounds);
    
	MaintainAspectRatioIfNeeded();
	AdaptTextOnPath();

	err = Resize();
	if (err == kSuccess)
    {
		err = ResizeXPEffects();
    }

	InterfacePtr<IAdaptiveTransientData> adaptiveTransientData(::GetExecutionContextSession(), IID_IADAPTIVETRANSIENTDATA);
    for (int i = 0; i < fData->fDependents.size(); ++i) {
        UID uid = fData->fDependents.At(i);
        UIDRef uidRef(db, uid);
        
		if (adaptiveTransientData)
        {
			AdapativePageItemData *data = adaptiveTransientData->GetData(uid);
			if (data)
			{
				PMRect finalBounds = adaptiveHelper->GetRelativeFinalBounds(data->fInitialBounds, fData->fInitialBounds, fData->fFinalBounds);
				data->SetRecommendedBounds(finalBounds);
			}
        }
    }

	return err;
}

ErrorCode CPageItemAdaptiveTransform::UnlockIfNeeded()
{
	UIDRef pageItemRef = ::GetUIDRef(this);
	ErrorCode err = kSuccess;
	InterfacePtr<ILockPosition> lock(pageItemRef, IID_ILOCKPOSITION);
	if (lock && lock->IsPageItemLocked(kFalse))
	{
		if (!ShouldHandleLocked())
			return kSuccess;

		//Locked items should be unlocked if they are to be handled. If a page item wants to handle by itself, it can capture the state in PreProcess()
		// and do the processing accordingly.
		UIDList pageItemList(pageItemRef);
		InterfacePtr<ICommand> unlockItemCmd(CmdUtils::CreateCommand(kSetLockPositionCmdBoss));
		InterfacePtr<IIntData> shouldLock(unlockItemCmd, IID_IINTDATA);
		shouldLock->Set(ILockPosition::kUnlock);
		unlockItemCmd->SetItemList(pageItemList);
		err = CmdUtils::ProcessCommand(unlockItemCmd);
		ASSERT(err == kSuccess);
		fData->fUnlockThis = kTrue;
	}
	return err;
}

ErrorCode CPageItemAdaptiveTransform::LockIfNeeded()
{
	if (fData->fUnlockThis)
	{
		UIDRef pageItemRef = ::GetUIDRef(this);
		UIDList pageItemList(pageItemRef);
		InterfacePtr<ICommand> unlockItemCmd(CmdUtils::CreateCommand(kSetLockPositionCmdBoss));
		InterfacePtr<IIntData> shouldLock(unlockItemCmd, IID_IINTDATA);
		shouldLock->Set(ILockPosition::kLock);
		unlockItemCmd->SetItemList(pageItemList);
		return CmdUtils::ProcessCommand(unlockItemCmd);
	}
	return kSuccess;
}

ErrorCode CPageItemAdaptiveTransform::PostProcessThis()
{
	return kSuccess;
}

void CPageItemAdaptiveTransform::FinishThis()
{
	/*if (!fData)
	{
		InterfacePtr<IAdaptiveTransientData> adaptiveTransientData(::GetExecutionContextSession(), IID_IADAPTIVETRANSIENTDATA);
		fData = adaptiveTransientData->GetData(pageItemRef.GetUID());
	}

	fData->fInitialBounds = fData->fFinalBounds = PMRect();
	fData->fDependentsInitialised = kFalse;
	fData->fUnlockThis = kFalse;
	fData->fLeftToRightBinding = kTrue;
	fTOPUID = kInvalidUID;
	fData->fDependents.Clear();*/
}

ErrorCode CPageItemAdaptiveTransform::PostProcess()
{
    if (ShouldProcessThis())
    {
		if (!fData)
		{
			UIDRef pageItemRef(::GetUIDRef(this));
			InterfacePtr<IAdaptiveTransientData> adaptiveTransientData(::GetExecutionContextSession(), IID_IADAPTIVETRANSIENTDATA);
			fData = adaptiveTransientData->GetData(pageItemRef.GetUID());
		}
        ErrorCode err = PostProcessThis();
        HANDLE_ADAPTIVE_ERR(err, "Error during PostProcessing.");
        err = ProcessDependents(POSTPROCESS);
        HANDLE_ADAPTIVE_ERR(err, "Error during PostProcessing dependents.");
        LockIfNeeded();
    }
    return kSuccess;
}

void CPageItemAdaptiveTransform::Finish()
{
	//Cleanup
	if (!fData)
	{
		UIDRef pageItemRef(::GetUIDRef(this));
		InterfacePtr<IAdaptiveTransientData> adaptiveTransientData(::GetExecutionContextSession(), IID_IADAPTIVETRANSIENTDATA);
		fData = adaptiveTransientData->GetData(pageItemRef.GetUID());
	}
	ProcessDependents(FINISH);
	FinishThis();
}

bool16 CPageItemAdaptiveTransform::ShouldHandleHidden()
{
	IDataBase *db = ::GetDataBase(this);
	InterfacePtr<IAdaptiveHelper> adaptiveHelper(db, db->GetRootUID(), UseDefaultIID());
	return adaptiveHelper->ShouldHandleHidden();
}

bool16 CPageItemAdaptiveTransform::ShouldHandleLocked()
{
	IDataBase *db = ::GetDataBase(this);
	InterfacePtr<IAdaptiveHelper> adaptiveHelper(db, db->GetRootUID(), UseDefaultIID());
	return adaptiveHelper->ShouldHandleLocked();
}

bool16 CPageItemAdaptiveTransform::ShouldHandleText()
{
	IDataBase *db = ::GetDataBase(this);
	InterfacePtr<IAdaptiveHelper> adaptiveHelper(db, db->GetRootUID(), UseDefaultIID());
	return adaptiveHelper->ShouldHandleText();
}

bool16 CPageItemAdaptiveTransform::ShouldMaintainAspectRatioForNonRectangularPI()
{
	IDataBase *db = ::GetDataBase(this);
	InterfacePtr<IAdaptiveHelper> adaptiveHelper(db, db->GetRootUID(), UseDefaultIID());
	return adaptiveHelper->ShouldMaintainAspectRatioForNonRectangularPI();
}

bool16 CPageItemAdaptiveTransform::ShouldMaintainAspectRatioForThis()
{
	IDataBase *db = ::GetDataBase(this);
	InterfacePtr<IAdaptiveHelper> adaptiveHelper(db, db->GetRootUID(), UseDefaultIID());
	return adaptiveHelper->ShouldMaintainAspectRatioForPI(::GetUIDRef(this));
}

void CPageItemAdaptiveTransform::MaintainAspectRatioIfNeeded()
{
	if (ShouldMaintainAspectRatioForThis())
	{
		//Generic scaling to be used for every page item
		PMReal horizontalScale = 1.0, verticalScale = 1.0;
		if (fData->fInitialBounds.Width() != 0.0 && fData->fInitialBounds.Height() != 0.0)
		{
			// Binding information.
			bool leftToRight = true;
			InterfacePtr<IPageSetupPrefs> iPagePrefs((IPageSetupPrefs*)::QueryPreferences(IID_IPAGEPREFERENCES, GetExecutionContextSession()->GetActiveContext()));
			if (iPagePrefs)
				leftToRight = iPagePrefs->GetPageBindingPref() == kLeftToRightBinding;

			horizontalScale = fData->fFinalBounds.Width() / fData->fInitialBounds.Width();
			verticalScale = fData->fFinalBounds.Height() / fData->fInitialBounds.Height();
			if (horizontalScale > verticalScale)
			{
				PMReal newWidth = fData->fInitialBounds.Width() * verticalScale;
				if (leftToRight)
					fData->fFinalBounds.SetWidth(newWidth);
				else
				{
					fData->fFinalBounds.Left(fData->fFinalBounds.Right() - newWidth);
				}
			}
			else
			{
				PMReal newHeight = fData->fInitialBounds.Height() * horizontalScale;
				fData->fFinalBounds.SetHeight(newHeight);
			}
		}
	}
}

ErrorCode CPageItemAdaptiveTransform::ResizeXPEffects()
{
	ErrorCode err = kSuccess;

	UIDRef pageItemRef = ::GetUIDRef(this);
	UIDList pageItemList(pageItemRef);

	IDataBase* db = pageItemRef.GetDataBase();
	InterfacePtr<IAdaptiveHelper> adaptiveHelper(db, db->GetRootUID(), UseDefaultIID());
	adaptiveHelper->AdjustEffects(pageItemList, fData->fInitialBounds, fData->fFinalBounds);
	return err;
}

void CPageItemAdaptiveTransform::AdaptTextOnPath()
{
	if (fData->fTOPUID == kInvalidUID)
		return;

	UIDRef mainSplineUIDRef = ::GetUIDRef(this);
	PMRect startRect(fData->fStartPoint, fData->fStartPoint);
	PMRect endRect(fData->fEndPoint, fData->fEndPoint);

	IDataBase* db = ::GetDataBase(this);
	InterfacePtr<IAdaptiveHelper> adaptiveHelper(db, db->GetRootUID(), UseDefaultIID());
	PMRect startBounds = adaptiveHelper->GetRelativeFinalBounds(startRect, fData->fInitialBounds, fData->fFinalBounds);
	PMRect endBounds = adaptiveHelper->GetRelativeFinalBounds(endRect, fData->fInitialBounds, fData->fFinalBounds);

    fData->fFinalStartPoint = PMPoint(startBounds.Left(), startBounds.Top());
	fData->fFinalEndPoint = PMPoint(endBounds.Right(), endBounds.Bottom());
    
	InterfacePtr<IAdaptiveTransientData> adaptiveTransientData(::GetExecutionContextSession(), IID_IADAPTIVETRANSIENTDATA);
	AdapativePageItemData *data = adaptiveTransientData->GetData(mainSplineUIDRef.GetUID());
	if (data)
		data->SetStartAndEndPointForTOP(fData->fFinalStartPoint, fData->fFinalEndPoint);
}

CPageItemAdaptiveTransform::~CPageItemAdaptiveTransform()
{
}

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/motion/AnimationUIPresetPopupMenuAction.cpp $
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
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IActionIDToUIDData.h"
#include "IActionManager.h"
#include "IActionStateList.h"
#include "IActiveContext.h"
#include "IAnimationAttributeSuite.h"
#include "IApplication.h"
#include "IMotionFacade.h"
#include "IMotionPresetData.h"
#include "IMotionPresetMgr.h"
#include "ISelectionManager.h"
#include "ITextControlData.h"
#include "ISelectionUtils.h"

// ----- Includes -----

#include "CActionComponent.h"
#include "CoreResTypes.h"
#include "DynamicDocumentsUIDefs.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"
#include "UIDList.h"

// ----- Utility files -----

#include "IMotionPresetUtils.h"
#include "IWidgetUtils.h"
#include "DynamicDocumentsUIUtils.h"

// ----- ID.h files -----

#include "DynamicDocumentsUIID.h"
#include "DynamicDocumentsID.h"

 
class AnimationUIPresetPopupMenuAction : public CActionComponent
{
	typedef CActionComponent inherited;

public:
	AnimationUIPresetPopupMenuAction(IPMUnknown *boss) : CActionComponent (boss) {}

	virtual void UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);
	virtual void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
};

// =============================================================================
// *** AnimationUIPresetPopupMenuAction impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(AnimationUIPresetPopupMenuAction, kAnimationUIPresetPopupMenuActionImpl) 

// -----------------------------------------------------------------------------

void AnimationUIPresetPopupMenuAction::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint, IPMUnknown* widget)
{
	InterfacePtr<IActionIDToUIDData> idToUIDData(this,UseDefaultIID());
	InterfacePtr<IMotionPresetMgr>	presetMgr(Utils<IMotionPresetUtils> ()->QueryMotionPresetManager());
	ASSERT (idToUIDData->Length() == presetMgr->GetNumPresets() + 1 /* None */);

	InterfacePtr<IAnimationAttributeSuite> animationAttrSuite(ac->GetContextSelection(), UseDefaultIID());
	ddui_utils::UpdateAnimationItemName (animationAttrSuite, widget);

	PMString appliedPresetName;
	InterfacePtr<ITextControlData> textData(static_cast<ITextControlData*>(Utils<IWidgetUtils>()->QueryRelatedWidget(widget, kAnimationUIPresetStaticTextWID, IID_ITEXTCONTROLDATA)));	
	if (textData)
		appliedPresetName = textData->GetString();

	int32 count = listToUpdate->Length(); 
	for (int32 i=0; i < count; i++) 
	{ 
		ActionID action = listToUpdate->GetNthAction(i); 
		UID presetUID = idToUIDData->GetUID(action);
		if (presetUID != kInvalidUID)
		{
			// Enable the preset and if it is applied give it a check mark
			InterfacePtr<IMotionPresetData> presetData(::GetDataBase(presetMgr), presetUID, UseDefaultIID());
			if (!presetData) continue;
			PMString presetName(presetData->GetName());
			presetName.Translate();

			int16 actionState = kEnabledAction;
			if (presetName == appliedPresetName)
				actionState |= kSelectedAction;

			listToUpdate->SetNthActionState (i, actionState); 
		}
		else if (action == kAnimationUIAction_FirstPresetDynamicActionID)
		{
			// Set the name and enablement for the first action: "None" or "Choose"
			if (animationAttrSuite && animationAttrSuite->HasAnimationApplied())
			{
				// Enable "None" so preset will be removed if chosen.
				listToUpdate->SetNthActionName(i,"kAnimationUINone");
				listToUpdate->SetNthActionState(i, kEnabledAction); 
			}
			else
			{
				// Disable "Choose" so user doesn't think choosing it will do anything.
				listToUpdate->SetNthActionName(i,"kAnimationUIChoose");
				listToUpdate->SetNthActionState(i, kDisabled_Unselected); 
			}
		}
		else
		{
			ASSERT_FAIL(FORMAT_ARGS("AnimationUIPresetPopupMenuAction::UpdateActionStates:- Unknown action ID: %x", action.Get())); 
		} 
	} 
} // end UpdateActionStates()

// -----------------------------------------------------------------------------

void AnimationUIPresetPopupMenuAction::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint, IPMUnknown* widget)
{
	ASSERT_MSG(actionID >= kAnimationUIAction_FirstPresetDynamicActionID && actionID <= kAnimationUIAction_LastPresetDynamicActionID, "Unexpected Animation Preset ActionID");
	if (actionID < kAnimationUIAction_FirstPresetDynamicActionID || actionID > kAnimationUIAction_LastPresetDynamicActionID)
		return;

	InterfacePtr<IAnimationAttributeSuite> animationAttrSuite(ac->GetContextSelection(), UseDefaultIID());

	InterfacePtr<IActionIDToUIDData> idToUIDData(this, UseDefaultIID());
	UID	presetUID = idToUIDData->GetUID(actionID);

	if (presetUID != kInvalidUID)
	{
		// Apply the animation
		InterfacePtr<IMotionPresetMgr> presetMgr(Utils<IMotionPresetUtils>()->QueryMotionPresetManager());
		IDataBase *db = ::GetDataBase(presetMgr);
		if (db->GetClass(presetUID) != kInvalidClass)
		{
			InterfacePtr<ITextControlData> textData(static_cast<ITextControlData*>(Utils<IWidgetUtils>()->QueryRelatedWidget(widget, kAnimationUIPresetStaticTextWID, IID_ITEXTCONTROLDATA)));	
			if (textData)
			{
				InterfacePtr<IMotionPresetData> presetData(db, presetUID, UseDefaultIID());
				textData->SetString(presetData->GetName());
			}

			animationAttrSuite->ApplyMotionPreset(UIDRef(db, presetUID));
		}
		else
		{
			ASSERT_FAIL(FORMAT_ARGS("AnimationUIPresetPopupMenuAction::DoAction:- presetUID (%x) is not valid!", presetUID.Get()));
		}
	}
	else
	{
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		InterfacePtr<IActionManager> actionMgr(app->QueryActionManager());
		 if (actionMgr->GetActionName(actionID) == "kAnimationUINone")
		 {
			// Remove the applied animation
			animationAttrSuite->ApplyMotionPreset(UIDRef::gNull);
		 }
		 else
		 {
			ASSERT_MSG(actionMgr->GetActionName(actionID) != "kAnimationUIChoose", FORMAT_ARGS("AnimationUIPresetPopupMenuAction::DoAction:- presetUID (%x) is not valid!", presetUID.Get()));
		 }
	}
} // end DoAction()

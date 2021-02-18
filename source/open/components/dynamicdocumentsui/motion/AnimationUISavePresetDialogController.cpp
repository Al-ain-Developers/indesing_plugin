//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/motion/AnimationUISavePresetDialogController.cpp $
//  
//  Owner: Yeming Liu
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

// ----- Interface files -----

#include "IActiveContext.h"
#include "IAnimationAttributeSuite.h"
#include "IMotionPresetMgr.h"
#include "IPanelControlData.h"
#include "ISelectionManager.h"
#include "IStringData.h"
#include "IStringListControlData.h"
#include "IUIDData.h"

// ----- Include files -----

#include "CDialogController.h"
#include "CAlert.h"

// ----- Utility files -----

#include "IMotionFacade.h"
#include "IMotionPresetUtils.h"

// ----- ID files -----

#include "DynamicDocumentsUIID.h"

class AnimationUISavePresetDialogController : public CDialogController
{
	public:
		AnimationUISavePresetDialogController(IPMUnknown *boss) : CDialogController(boss) 
			{}
		
		virtual void InitializeDialogFields( IActiveContext* dlgContext);
		virtual WidgetID ValidateDialogFields( IActiveContext* dlgContext);

		virtual void ApplyDialogFields( IActiveContext* dlgContext, const WidgetID& widgetId);
};

CREATE_PMINTERFACE(AnimationUISavePresetDialogController, kAnimationUISavePresetDialogControllerImpl)

void AnimationUISavePresetDialogController::InitializeDialogFields( IActiveContext* dlgContext)
{	
	InterfacePtr<IMotionPresetMgr> iAppPresetMgr (Utils<IMotionPresetUtils> ()->QueryMotionPresetManager ());

	//
	// Get the default custom preset name
	//
	PMString customPresetName(kNullString);
 
 	InterfacePtr<IStringData> iStringData(this, UseDefaultIID());
 	if (iStringData && !iStringData->GetString().empty())
 	{
 		customPresetName = iStringData->GetString();
		customPresetName = iAppPresetMgr->GetUniquePresetName (customPresetName, PMString(), true);
 	}
 	else
 	{
 		customPresetName = PMString("kCustomPresetName", PMString::kTranslateDuringCall);
		customPresetName = iAppPresetMgr->GetUniquePresetName (customPresetName);
 	}

	SetTextControlData (kAnimationUISavePresetNameWID, customPresetName);
}

WidgetID AnimationUISavePresetDialogController::ValidateDialogFields( IActiveContext* dlgContext)
{
	InterfacePtr<IPanelControlData> iPanelControlData (this, UseDefaultIID());          
	PMString customPresetName = GetTextControlData(kAnimationUISavePresetNameWID, iPanelControlData); 

	InterfacePtr<IMotionPresetMgr> iAppPresetMgr (Utils<IMotionPresetUtils> ()->QueryMotionPresetManager ());
	ErrorCode errCode = Utils<IMotionPresetUtils> ()->ValidatePresetName (iAppPresetMgr, customPresetName);
	if (errCode != kSuccess)
	{
		int16 returnAsError = true;
		switch (errCode)
		{
			case kMotion_PresetNameEmptyError:
				CAlert::WarningAlert ("kMotion_PresetNameEmptyError");
				break;
			case kMotion_PresetNameAlreadyExistsError:
				CAlert::WarningAlert ("kMotion_PresetNameAlreadyExistsError");
				break;
			case kMotion_CustomPresetNameAlreadyExistsError:
				{
					int16 kDefaultButton = 2;
					if (CAlert::ModalAlert ("kMotion_CustomPresetNameAlreadyExistsError", kOKString, kCancelString, kNullString, kDefaultButton, CAlert::eWarningIcon) != kDefaultButton)
					{
						returnAsError = false;
					}
				}
				break;
			case kMotion_PresetNameInvalidError:
				CAlert::WarningAlert ("kMotion_PresetNameInvalidError");
				break;
		}
		return (returnAsError ? kAnimationUISavePresetNameWID : kNoInvalidWidgets); 
	}
	return kNoInvalidWidgets; 
}

void AnimationUISavePresetDialogController::ApplyDialogFields( IActiveContext* dlgContext, const WidgetID& widgetId)
{
	//
	// Get the name from the combo box and strip all leading and trailing white spaces!
	//
	InterfacePtr<IPanelControlData> iPanelControlData (this, UseDefaultIID());          
	PMString customPresetName = GetTextControlData(kAnimationUISavePresetNameWID, iPanelControlData);
	customPresetName.StripWhiteSpace (PMString::kLeadingAndTrailingWhiteSpace);
	customPresetName.SetTranslatable (kFalse);

	//
	// Save it in the model.
	//		
	InterfacePtr<IUIDData> iPresetToDuplicate(this, UseDefaultIID());
	if (iPresetToDuplicate && iPresetToDuplicate->GetItemDataBase() != nil && iPresetToDuplicate->GetItemUID() != kInvalidUID)
	{
		UID newPresetUID = kInvalidUID;
		ErrorCode result = Utils<Facade::IMotionFacade> ()->DuplicateMotionPreset(iPresetToDuplicate->GetRef(), customPresetName, newPresetUID);

		iPresetToDuplicate->Set(iPresetToDuplicate->GetItemDataBase(), newPresetUID);
	}
	else
	{
		ISelectionManager* iSelectionMgr = dlgContext->GetContextSelection();
		InterfacePtr<IAnimationAttributeSuite> iAttrSuite (iSelectionMgr, UseDefaultIID ());
		iAttrSuite->SaveAnimationSettings (customPresetName);
	}
}

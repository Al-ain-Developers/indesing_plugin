//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/motion/AnimationUIPanelMenuAction.cpp $
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

// ----- Interface files -----

#include "IActiveContext.h"
#include "IActionStateList.h"
#include "IAnimationAttributeSuite.h"
#include "IApplication.h"
#include "IDialog.h"
#include "IDialogMgr.h"
#include "IMotionFacade.h"
#include "IMotionPresetData.h"
#include "IMotionPresetMgr.h"
#include "IOpenFileDialog.h"
#include "ISaveFileDialog.h"
#include "ISelectionManager.h"

// ----- Include files -----

#include "CActionComponent.h"
#include "CoreResTypes.h"
#include "DynamicDocumentsUIDefs.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"
#include "SysFileList.h"

// ----- Utility files -----

#include "DynamicDocumentsUIUtils.h"
#include "ErrorUtils.h"
#include "FileTypeRegistry.h"
#include "FileUtility.h"
#include "IMotionPresetUtils.h"

// ----- ID files -----

#include "DynamicDocumentsID.h"
#include "DynamicDocumentsUIID.h"
#include "GenericID.h"

static bool GetSaveAsFile (IDFile& saveAsPresetFile, PMString& defaultFileName);
static bool PickPresetFile (std::vector<IDFile>& presetFiles);
 
class AnimationUIPanelMenuAction : public CActionComponent
{
	typedef CActionComponent inherited;

public:
	AnimationUIPanelMenuAction(IPMUnknown *boss) : CActionComponent (boss) {}

	virtual void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
	{
		ISelectionManager* iSelectionMgr = ac->GetContextSelection ();
		IDataBase* db = iSelectionMgr->GetDataBase();

		InterfacePtr<IAnimationAttributeSuite> iAttrSuite (iSelectionMgr, UseDefaultIID ());

		switch (actionID.Get ())
		{	
			case kAnimationUIAction_SavePresetID:
			{
				if (iAttrSuite)
				{
					UID presetUID = kInvalidUID;
					if (iAttrSuite && iAttrSuite->CanSaveAnimationSettings ())
					{
						//
						// Bring up Save dialog
						//
						InterfacePtr<IApplication> iApp (GetExecutionContextSession()->QueryApplication());
						InterfacePtr<IDialogMgr> iDialogMgr (iApp, UseDefaultIID());	
						IDialog* iDialog = iDialogMgr->CreateNewDialog(RsrcSpec(LocaleSetting::GetLocale(), kDynamicDocumentsUIPluginID, 
							                                           kViewRsrcType, kAnimationUISavePresetRsrcID), IDialog::kMovableModal);

						iDialog->Open();
						iDialog->WaitForDialog();
					}
				}
				break;
			}

			case kAnimationUIAction_SaveAsPresetID:
			{
				if (iAttrSuite)
				{
					UID presetUID = kInvalidUID;
					if (iAttrSuite && iAttrSuite->CanSaveACopyAnimationSettings ())
					{
						IDFile saveAsPresetFile;
						PMString defaultFileName ("kNewMotionPresetName");
						defaultFileName.Translate ();
						
						iAttrSuite->GetMotionPresetApplied (presetUID);
						if (presetUID != kInvalidUID)
						{
							InterfacePtr<IMotionPresetData>	iPresetData (iSelectionMgr->GetDataBase (), presetUID, UseDefaultIID ());
							if (iPresetData && iPresetData->GetName ().CharCount () > 0)
							{
								defaultFileName = iPresetData->GetName ();
								defaultFileName.SetTranslatable (kFalse);
							}
						}

						defaultFileName.Append (".xml");
						if (GetSaveAsFile (saveAsPresetFile, defaultFileName))
						{
							iAttrSuite->SaveACopyAnimationSettings (saveAsPresetFile);
							ASSERT (ErrorUtils::PMGetGlobalErrorCode () == kSuccess);
						}
					}
				}
				break;
			}

			case kAnimationUIAction_DeletePresetID:
			{
				if (iAttrSuite)
				{
					iAttrSuite->RemoveAnimationPreset();
					ASSERT (ErrorUtils::PMGetGlobalErrorCode () == kSuccess);
				}

				break;
			}

			case kAnimationUIAction_LoadPresetID:
			{
				std::vector<IDFile> presetFiles;
				if (PickPresetFile (presetFiles))
				{
					ASSERT(presetFiles.size() > 0);
					UID newPresetUID = kInvalidUID;
					Utils<Facade::IMotionFacade> ()->LoadPresetFromFile (presetFiles, newPresetUID, kTrue);
				}
				break;
			}
			case kAnimationUIAction_ManagePresetID:
			{
				//
				// Bring up Manage Preset dialog
				//
				InterfacePtr<IApplication> iApp (GetExecutionContextSession()->QueryApplication());
				InterfacePtr<IDialogMgr> iDialogMgr (iApp, IID_IDIALOGMGR);	
				IDialog* iDialog = iDialogMgr->CreateNewDialog(RsrcSpec(LocaleSetting::GetLocale(), kDynamicDocumentsUIPluginID, 
					                                           kViewRsrcType, kAnimationUIManagePresetsDialogRsrcID), IDialog::kMovableModal);

				iDialog->Open();

				break;
			}
			case kAnimationUIAction_ConvertToMotionPathActionID:
			{
				if ((iAttrSuite != nil) && iAttrSuite->CanSetAnimationMotionPathFromSelection())
					iAttrSuite->SetAnimationMotionPathFromSelection();
				break;
			}

			default:
				break;

		}
	}

	virtual void UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
	{
		ISelectionManager* iSelectionMgr = ac->GetContextSelection ();
		IDataBase* db = iSelectionMgr->GetDataBase();
		InterfacePtr<IAnimationAttributeSuite> iAttrSuite (iSelectionMgr, UseDefaultIID ());
		
		for(int32 i = 0; i < listToUpdate->Length(); i++)
		{
			ActionID	action = listToUpdate->GetNthAction(i);
			switch (action.Get ())
			{
				case kAnimationUIAction_SavePresetID:
				{
					if ((iAttrSuite != nil) && iAttrSuite->CanSaveAnimationSettings())
						listToUpdate->SetNthActionState (i, kEnabledAction); 
					else
						listToUpdate->SetNthActionState (i, kDisabled_Unselected); 
					
					break;
				}
				case kAnimationUIAction_SaveAsPresetID:
				{
					if ((iAttrSuite != nil) && iAttrSuite->CanSaveACopyAnimationSettings())
						listToUpdate->SetNthActionState (i, kEnabledAction); 
					else
						listToUpdate->SetNthActionState (i, kDisabled_Unselected); 

					break;
				}
	
				case kAnimationUIAction_DeletePresetID:
				{			
					if ((iAttrSuite != nil) && iAttrSuite->CanRemoveAnimationPreset())
						listToUpdate->SetNthActionState (i, kEnabledAction); 
					else
						listToUpdate->SetNthActionState (i, kDisabled_Unselected); 
					
					break;
				}

				case kAnimationUIAction_LoadPresetID:
				{
					listToUpdate->SetNthActionState (i, kEnabledAction); 
					break;
				}

				case kAnimationUIAction_ConvertToMotionPathActionID:
				{
					if ((iAttrSuite != nil) && iAttrSuite->CanSetAnimationMotionPathFromSelection())
						listToUpdate->SetNthActionState (i, kEnabledAction); 
					else
						listToUpdate->SetNthActionState (i, kDisabled_Unselected); 
					break;
				}

				default:
					break;
			}
		}
	}
};

CREATE_PMINTERFACE(AnimationUIPanelMenuAction, kAnimationUIPanelMenuActionImpl)


bool PickPresetFile (std::vector<IDFile>& presetFiles)
{
	InterfacePtr<IOpenFileDialog> openDlg((IOpenFileDialog*)::CreateObject(kOpenDocDialogBoss, IID_IOPENFILEDIALOG));
	// Add PC file extensions
	PMString allFiles("All Readable Files");
	allFiles.Translate();

	FileTypeRegistry::FileExtensionList extList;
	FileTypeRegistry::GetAllFileExtension(kXMLFileTypeInfoID, extList, kTrue);

	FileTypeRegistry::FileExtensionList::iterator eItr = extList.begin();
	while (eItr != extList.end())
	{
		openDlg->AddExtension(&allFiles, eItr);
		++eItr;
	}
			
	SysFileList k2Files;
	bool16	okToImport = openDlg->DoDialog (nil, k2Files, kTrue/*allow you to select multiple files*/);
	if (okToImport)
	{
		// check if document is opened, otherwise open the document with no window
		int32 numFiles = k2Files.GetFileCount();
		ASSERT(numFiles > 0);
		for (int32 i = 0; i < numFiles; ++i)
		{
			FileUtility nthFileUtil(*(k2Files.GetNthFile(i)));
			presetFiles.push_back(nthFileUtil.GetSysFile());		
		}
	}

	return okToImport;
}

//	Enable when menu item is added.
bool GetSaveAsFile (IDFile& saveAsPresetFile, PMString& defaultFileName)
{
    InterfacePtr<ISaveFileDialog>	iSaveDlg (::CreateObject2<ISaveFileDialog>(kSaveFileDialogBoss, IID_ISAVEFILEDIALOG)); 

    PMString exten("xml"); 
    iSaveDlg->AddFileTypeInfo(exten, exten); 
     
#ifdef WINDOWS 
    iSaveDlg->SetAdditionalFOSFlags(FOS_OVERWRITEPROMPT | FOS_NOREADONLYRETURN); 
#endif 

    // Set the default name to use. 
    IDFile defaultFile; 
    defaultFileName.SetTranslatable (kFalse); 
    defaultFile.SetFileName(defaultFileName); 
     
    PMString dialogTitle = "kAnimationUISaveAsPresetTitle"; 
    dialogTitle.Translate(); 

    int32* pSelectedIndex = nil; 
    bool16 useSystemDefaultDir = kFalse; 
    bool16 showTypeMenu = kTrue; 

    // Show the dialog. 
    return iSaveDlg->DoDialog (&defaultFile, &saveAsPresetFile, pSelectedIndex, useSystemDefaultDir, showTypeMenu, &dialogTitle); 
}





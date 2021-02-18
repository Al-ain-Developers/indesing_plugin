//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/motion/AnimationUIManagePresetsDialogObserver.cpp $
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

#include "IApplication.h"
#include "IBoolData.h"
#include "IControlView.h"
#include "IDialogMgr.h"
#include "IIntData.h"
#include "IListBoxAttributes.h"
#include "IListBoxController.h"
#include "IMotionPresetMgr.h"
#include "IOpenFileDialog.h"
#include "IPanelControlData.h"
#include "ISaveFileDialog.h"
#include "IStringData.h"
#include "IStringListBoxControlData.h"
#include "ISubject.h"
#include "IUIDData.h"

// ----- Include files -----

#include "CDialogObserver.h"
#include "CoreResTypes.h"
#include "DynamicDocumentsUIDefs.h"
#include "FileTypeRegistry.h"
#include "SysFileList.h"

// ----- Utility files -----

#include "DynamicDocumentsUIUtils.h"
#include "FileUtility.h"
#include "IMotionFacade.h"
#include "IMotionPresetUtils.h"

// ----- ID files -----

#include "DynamicDocumentsUIID.h"

static bool GetSaveAsFile (IDFile& saveAsPresetFile, PMString& defaultFileName);
static bool PickPresetFile (std::vector<IDFile>& presetFiles);

//====================================================================================================================
// Class AnimationUIManagePresetsDialogObserver
//====================================================================================================================
class AnimationUIManagePresetsDialogObserver : public CDialogObserver
{
		typedef CDialogObserver inherited;

		class PresetNamePair
		{
			typedef object_type data_type; 

			public:
				PMString fOriginalName;
				PMString fTranslatedName;
				
				PresetNamePair(PMString const &originalName, PMString const &translatedName) : 
					fOriginalName(originalName),
					fTranslatedName(translatedName) 
				{
				}

				bool16 operator<(const PresetNamePair& other) const 
				{ 
					if (fTranslatedName < other.fTranslatedName)
						return kTrue;

					return kFalse; 
				} 
		};

		typedef std::vector<PresetNamePair> PresetList;
		PresetList fCustomPresetList;	
		PresetList fDefaultPresetList;	

		void AttachDetachWidget(WidgetID const &widgetID, PMIID const &protocolID, bool16 const &bAttach);
		void UpdateAllWidgets();
		void UpdateButtons();
		void DeletePresets();
		void DuplicatePresets();
		void LoadPresets();
		void SaveAsPresets();
		void GetSelectedPresets(std::vector<UID> &presetUIDList, std::vector<PMString> &presetNameList);
		void BuildAnimationPresetList();


	public:
		AnimationUIManagePresetsDialogObserver(IPMUnknown* boss) : inherited(boss) { }
		virtual ~AnimationUIManagePresetsDialogObserver() { }

		virtual void AutoAttach();
		virtual void AutoDetach();
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
};

CREATE_PMINTERFACE(AnimationUIManagePresetsDialogObserver, kAnimationUIManagePresetsDialogObserverImpl)

//--------------------------------------------------------------------------------------------------------------------
// AutoAttach
//--------------------------------------------------------------------------------------------------------------------
void AnimationUIManagePresetsDialogObserver::AutoAttach() 
{
	inherited::AutoAttach();
	
	this->AttachDetachWidget(kAnimationUIManagePresetsListBoxWidgetID, IID_ILISTCONTROLDATA, true/*attach*/);

	this->AttachDetachWidget(kAnimationUIManagePresetsDoneButtonWidgetID, IID_IBOOLEANCONTROLDATA, true/*attach*/);
	this->AttachDetachWidget(kAnimationUIManagePresetsDeleteButtonWidgetID, IID_IBOOLEANCONTROLDATA, true/*attach*/);
	this->AttachDetachWidget(kAnimationUIManagePresetsDuplicateButtonWidgetID, IID_IBOOLEANCONTROLDATA, true/*attach*/);
	this->AttachDetachWidget(kAnimationUIManagePresetsLoadButtonWidgetID, IID_IBOOLEANCONTROLDATA, true/*attach*/);
	this->AttachDetachWidget(kAnimationUIManagePresetsSaveAsButtonWidgetID, IID_IBOOLEANCONTROLDATA, true/*attach*/);

	this->UpdateAllWidgets();
}


//--------------------------------------------------------------------------------------------------------------------
// AutoDetach
//--------------------------------------------------------------------------------------------------------------------
void AnimationUIManagePresetsDialogObserver::AutoDetach() 
{
	this->AttachDetachWidget(kAnimationUIManagePresetsListBoxWidgetID, IID_ILISTCONTROLDATA, false/*attach*/);

	this->AttachDetachWidget(kAnimationUIManagePresetsDoneButtonWidgetID, IID_IBOOLEANCONTROLDATA, false/*attach*/);
	this->AttachDetachWidget(kAnimationUIManagePresetsDeleteButtonWidgetID, IID_IBOOLEANCONTROLDATA, false/*attach*/);
	this->AttachDetachWidget(kAnimationUIManagePresetsDuplicateButtonWidgetID, IID_IBOOLEANCONTROLDATA, false/*attach*/);
	this->AttachDetachWidget(kAnimationUIManagePresetsLoadButtonWidgetID, IID_IBOOLEANCONTROLDATA, false/*attach*/);
	this->AttachDetachWidget(kAnimationUIManagePresetsSaveAsButtonWidgetID, IID_IBOOLEANCONTROLDATA, false/*attach*/);
	
	inherited::AutoDetach();
}

//--------------------------------------------------------------------------------------------------------------------
// UpdateAllWidgets
//--------------------------------------------------------------------------------------------------------------------
void AnimationUIManagePresetsDialogObserver::UpdateAllWidgets()
{
	//
	// Build preset list.
	//	
	this->BuildAnimationPresetList();

	//
	// Disable delete, dudplicate and save as button since nothing is selected when open the dialog;
	// other buttons should be enabled all the time.
	//	
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());

	IControlView* iDeleteButtonView = iPanelControlData->FindWidget(kAnimationUIManagePresetsDeleteButtonWidgetID);
	iDeleteButtonView->Disable();

	IControlView* iDuplicateButtonView = iPanelControlData->FindWidget(kAnimationUIManagePresetsDuplicateButtonWidgetID);
	iDuplicateButtonView->Disable();

	IControlView* iSaveAsButtonView = iPanelControlData->FindWidget(kAnimationUIManagePresetsSaveAsButtonWidgetID);
	iSaveAsButtonView->Disable();
	
	IControlView* iDoneButtonView = iPanelControlData->FindWidget(kOKButtonWidgetID);
	iDoneButtonView->Hilite();
}

//--------------------------------------------------------------------------------------------------------------------
// Update
//--------------------------------------------------------------------------------------------------------------------
void AnimationUIManagePresetsDialogObserver::Update(const ClassID& theChange, ISubject* iSubject, const PMIID& protocolId, void* changedBy)
{
	InterfacePtr<IControlView> iControlView(iSubject, UseDefaultIID());
	WidgetID widgetID = iControlView->GetWidgetID();

	if ((protocolId.Get() == IID_IBOOLEANCONTROLDATA) && (theChange == kTrueStateMessage))
	{
		switch (widgetID.Get())
		{	
			case kOKButtonWidgetID:	// close dialog
			{
				inherited::Update(theChange, iSubject, protocolId, changedBy);
				break;
			}
			case kAnimationUIManagePresetsDeleteButtonWidgetID:	   // delete selected presets
			{
				this->DeletePresets();
				break;
			}
			case kAnimationUIManagePresetsDuplicateButtonWidgetID: // duplicate selected presets
			{
				this->DuplicatePresets();
				break;
			}
			case kAnimationUIManagePresetsLoadButtonWidgetID:	// load presets
			{
				this->LoadPresets();
				break;
			}
			case kAnimationUIManagePresetsSaveAsButtonWidgetID:	// save as presets
			{
				this->SaveAsPresets();
				break;
			}
			default:
				break;
		}
	}
	else if ((protocolId == IID_ILISTCONTROLDATA) && (widgetID.Get() == kAnimationUIManagePresetsListBoxWidgetID))
	{
		if (theChange == kListSelectionChangedMessage || theChange == kListSelectionChangedByUserMessage)
		{
			this->UpdateButtons();
		}
	}
	else
	{
		inherited::Update(theChange, iSubject, protocolId, changedBy);
	}
}

void AnimationUIManagePresetsDialogObserver::AttachDetachWidget(WidgetID const &widgetID, PMIID const &protocolID, bool16 const &bAttach)
{		
	InterfacePtr<IPanelControlData>	iPanelControlData(this, UseDefaultIID());
	InterfacePtr<IControlView> iControlView(iPanelControlData->FindWidget(widgetID), UseDefaultIID());

	InterfacePtr<ISubject> iSubject(iControlView, IID_ISUBJECT);
	if (iSubject)
	{	
		if (bAttach && !iSubject->IsAttached( this, protocolID, IID_IOBSERVER))
			iSubject->AttachObserver( this, protocolID, IID_IOBSERVER);
		else if (!bAttach && iSubject->IsAttached( this, protocolID, IID_IOBSERVER))
			iSubject->DetachObserver( this, protocolID, IID_IOBSERVER);
	}
}

void AnimationUIManagePresetsDialogObserver::UpdateButtons()
{	
	InterfacePtr<IPanelControlData>	iPanelControlData(this, UseDefaultIID());
	IControlView* iListView = iPanelControlData->FindWidget(kAnimationUIManagePresetsListBoxWidgetID);

	InterfacePtr<IStringListBoxControlData> iListCtrlData(iListView, IID_ILISTCONTROLDATA );
	InterfacePtr<IListBoxController> iListController(iListView, UseDefaultIID());

	K2Vector<int32> selectionList;		
	iListController->GetSelected(selectionList);

	//
	// If there is one of the selected presets can not be deleted, 
	// we will disable the delete button.
	//		
	InterfacePtr<IMotionPresetMgr> iAppPresetMgr(Utils<IMotionPresetUtils>()->QueryMotionPresetManager ()); 
	int32 numPresets = iAppPresetMgr->GetNumPresets();

	bool bEnableDeleteButton = (selectionList.size() > 0);
	for(int32 i = 0; bEnableDeleteButton && (i < selectionList.size()); ++i)
	{
		int32 selectedIndex = selectionList[i];
		PMString presetName = (*iListCtrlData)[selectedIndex];
		int32 presetIndex = iAppPresetMgr->FindPreset(presetName);

		// If 1) we select the separator or other cases that fail to get the preset index OR 
		//    2) selected preset can not be deleted;
		// we should disable the delete button.
		if (presetIndex < 0 || presetIndex >= numPresets)
			bEnableDeleteButton = false;
		else if (!iAppPresetMgr->CanDeleteNthPreset(presetIndex))
			bEnableDeleteButton = false;		
	}

	//
	// Update delete button.
	//
	IControlView* iDeleteButtonView = iPanelControlData->FindWidget(kAnimationUIManagePresetsDeleteButtonWidgetID);
	if (bEnableDeleteButton)
		iDeleteButtonView->Enable();
	else
		iDeleteButtonView->Disable();

	//
	// For duplicate/save as button, if there is only one preset is selected, enable it; otherwise gray out.
	//
	bool bEnableDuplicateSaveAsButton = false;
	if (selectionList.size() == 1)
	{
		int32 selectedIndex = selectionList[0];
		PMString presetName = (*iListCtrlData)[selectedIndex];

		CharCounter prefixIndex = presetName.IndexOfCharacter('[');
		CharCounter suffixIndex = presetName.LastIndexOfCharacter(']');
		if ((prefixIndex >= 0) && (suffixIndex >= 0))
		{
			presetName.Remove(0);
            presetName.Truncate(); 
        } 
        
		int32 presetIndex = iAppPresetMgr->FindPreset(presetName);
		if ((presetIndex >= 0) && (presetIndex < numPresets))
			bEnableDuplicateSaveAsButton = true;
	}

	IControlView* iDuplicateButtonView = iPanelControlData->FindWidget(kAnimationUIManagePresetsDuplicateButtonWidgetID);
	IControlView* iSaveAsButtonView = iPanelControlData->FindWidget(kAnimationUIManagePresetsSaveAsButtonWidgetID);
	if (bEnableDuplicateSaveAsButton)
	{
		iDuplicateButtonView->Enable();
		iSaveAsButtonView->Enable();
	}
	else
	{
		iDuplicateButtonView->Disable();
		iSaveAsButtonView->Disable();
	}
}

void AnimationUIManagePresetsDialogObserver::GetSelectedPresets(std::vector<UID> &presetUIDList, std::vector<PMString> &presetNameList)
{
	InterfacePtr<IPanelControlData>	iPanelControlData(this, UseDefaultIID());
	InterfacePtr<IControlView> iListView(iPanelControlData->FindWidget(kAnimationUIManagePresetsListBoxWidgetID), UseDefaultIID());

	InterfacePtr<IStringListBoxControlData> iListCtrlData(iListView, IID_ILISTCONTROLDATA );
	InterfacePtr<IListBoxController> iListController(iListView, UseDefaultIID());

	K2Vector<int32> selectionList;		
	iListController->GetSelected(selectionList);

	//
	// If there is one of the selected presets can not be deleted, 
	// we will disable the delete button.
	//	
    InterfacePtr<IMotionPresetMgr> iAppPresetMgr (Utils<IMotionPresetUtils> ()->QueryMotionPresetManager ()); 
	int32 numPresets = iAppPresetMgr->GetNumPresets();

	for(int32 i = 0; i < selectionList.size(); ++i)
	{
		int32 selectedIndex = selectionList[i];

		PMString presetName = (*iListCtrlData)[selectedIndex];
		int32 presetIndex = iAppPresetMgr->FindPreset(presetName);
		if (presetIndex >= 0 && presetIndex < numPresets)
		{
			UID presetUID = iAppPresetMgr->GetNthPresetUID(presetIndex);

			presetUIDList.push_back(presetUID);

			PMString rawName(kNullString);
			iAppPresetMgr->GetNthPresetName(presetIndex, rawName);
			presetNameList.push_back(rawName);
		}
	}
}

void AnimationUIManagePresetsDialogObserver::DeletePresets()
{
	//
	// Get selected presets in the list box.
	//
	std::vector<UID> presetUIDList;
	std::vector<PMString> presetNameList;
	this->GetSelectedPresets(presetUIDList, presetNameList);

    InterfacePtr<IMotionPresetMgr> iAppPresetMgr (Utils<IMotionPresetUtils> ()->QueryMotionPresetManager ()); 
	IDataBase* db = ::GetDataBase(iAppPresetMgr);

	//
	// Go through each preset and delete it.
	//
	ICommandSequence* iDeleteCmdSequence = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
	ASSERT (iDeleteCmdSequence != nil);

	for (std::vector<UID>::const_iterator iter = presetUIDList.begin(); iter != presetUIDList.end(); ++iter)
	{
		int32 index = iAppPresetMgr->FindPreset(*iter); 
		if (index >= 0) 
		{ 
			ErrorCode errCode = Utils<Facade::IMotionFacade> ()->DeleteMotionPreset(UIDRef(db, *iter)); 
			ASSERT ((errCode == kSuccess) || (errCode == kCancel)); 
		} 
	}

	ErrorCode result = CmdUtils::EndCommandSequence(iDeleteCmdSequence);
	ASSERT(result == kSuccess);

	if (result == kSuccess)
	{
		this->BuildAnimationPresetList();

		this->UpdateButtons();
	}
}

void AnimationUIManagePresetsDialogObserver::DuplicatePresets()
{	
	//
	// Get current selected preset.
	//
	std::vector<UID> presetUIDList;
	std::vector<PMString> presetNameList;
	this->GetSelectedPresets(presetUIDList, presetNameList);
	ASSERT(presetUIDList.size() == 1 && presetNameList.size() == 1);

	//
	// Bring up Save dialog
	//
	InterfacePtr<IApplication> iApp (GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IDialogMgr> iDialogMgr (iApp, UseDefaultIID());	
	IDialog* iDialog = iDialogMgr->CreateNewDialog(RsrcSpec(LocaleSetting::GetLocale(), kDynamicDocumentsUIPluginID, 
		                                           kViewRsrcType, kAnimationUISavePresetRsrcID), IDialog::kMovableModal);

	IControlView* iDialogView = iDialog->GetDialogPanel(); 

	InterfacePtr<IMotionPresetMgr> iAppPresetMgr(Utils<IMotionPresetUtils>()->QueryMotionPresetManager ()); 
	InterfacePtr<IUIDData> iPresetToDuplicate(iDialogView, UseDefaultIID());
	iPresetToDuplicate->Set(::GetDataBase(iAppPresetMgr), presetUIDList[0]);

	InterfacePtr<IStringData> iDuplicatePresetName(iDialogView, UseDefaultIID());
	iDuplicatePresetName->Set(presetNameList[0]);

	iDialog->Open();
	iDialog->WaitForDialog();
	
    if (iPresetToDuplicate->GetItemUID() != kInvalidUID)
	{
		this->BuildAnimationPresetList();

		this->UpdateButtons();

		// Clear the cached data for duplciate case.
		iPresetToDuplicate->Set(nil, kInvalidUID);
		iDuplicatePresetName->Set(kNullString);
	}
}

void AnimationUIManagePresetsDialogObserver::LoadPresets()
{
	std::vector<IDFile> presetFiles;
	if (PickPresetFile (presetFiles))
	{
		ASSERT(presetFiles.size() > 0);
		UID newPresetUID = kInvalidUID;
		ErrorCode result = Utils<Facade::IMotionFacade> ()->LoadPresetFromFile (presetFiles, newPresetUID, kTrue);

		if (result == kSuccess)
		{
			this->BuildAnimationPresetList();

			this->UpdateButtons();
		}
	}
}

void AnimationUIManagePresetsDialogObserver::SaveAsPresets()
{
	std::vector<UID> presetUIDList;
	std::vector<PMString> presetNameList;
	this->GetSelectedPresets(presetUIDList, presetNameList);
	ASSERT(presetUIDList.size() == 1 && presetNameList.size() == 1);

	PMString defaultFileName (presetNameList [0]);
	defaultFileName.Translate ();
	
	IDFile saveAsPresetFile;
	if (GetSaveAsFile (saveAsPresetFile, defaultFileName))
	{
		InterfacePtr<IMotionPresetMgr> iAppPresetMgr (Utils<IMotionPresetUtils> ()->QueryMotionPresetManager ());
		ErrorCode result = Utils<Facade::IMotionFacade> ()->SavePresetToFile (UIDRef (::GetDataBase (iAppPresetMgr), presetUIDList[0]), saveAsPresetFile);

		if (result == kSuccess)
		{
			this->BuildAnimationPresetList();

			this->UpdateButtons();
		}
	}
}

void AnimationUIManagePresetsDialogObserver::BuildAnimationPresetList()
{
	fCustomPresetList.clear();
	fDefaultPresetList.clear();

	InterfacePtr<IMotionPresetMgr> iAppPresetMgr (Utils<IMotionPresetUtils>()->QueryMotionPresetManager ()); 
	int32 numPresets = iAppPresetMgr->GetNumPresets();
	
	int32 nonDefaultCount = 0;
	for(int32 i = 0; i < numPresets; ++i)
	{
		PMString presetName(kNullString);
		ErrorCode result = iAppPresetMgr->GetNthPresetName(i, presetName);

		if (result == kSuccess)
		{
			PMString translatedName = presetName;
			translatedName.Translate();

			PresetNamePair namePair(presetName, translatedName);

			if (!iAppPresetMgr->IsDefaultPreset(i))
				fCustomPresetList.push_back(namePair);
			else
			{
				fDefaultPresetList.push_back(namePair);
			}
		}
	}

	std::sort(fCustomPresetList.begin(), fCustomPresetList.end());
	std::sort(fDefaultPresetList.begin(), fDefaultPresetList.end());

	//
	// Add the presets to the list box.
	//
	InterfacePtr<IPanelControlData>	iPanelControlData(this, UseDefaultIID());
	IControlView* iPresetListView = iPanelControlData->FindWidget(kAnimationUIManagePresetsListBoxWidgetID);
	if (!iPresetListView)
		return;

	InterfacePtr<IStringListBoxControlData> iPresetListCtrlData(iPresetListView, IID_ILISTCONTROLDATA );
	iPresetListCtrlData->Clear( kFalse, kFalse );

	InterfacePtr<IListBoxAttributes> iListAttr(iPresetListView, UseDefaultIID());
	InterfacePtr<IListBoxController> iListController(iPresetListView, UseDefaultIID());

	iListAttr->MuteDrawing(kTrue);

	for(PresetList::const_iterator customIter = fCustomPresetList.begin(); customIter != fCustomPresetList.end(); ++customIter)
	{
		PMString itemString(customIter->fOriginalName);
		itemString.SetTranslatable(kFalse);
		iPresetListCtrlData->Add(itemString);
	}

	for(PresetList::const_iterator defaultIter = fDefaultPresetList.begin(); defaultIter != fDefaultPresetList.end(); ++defaultIter)
	{
		PMString itemString(defaultIter->fOriginalName);
		itemString.SetTranslatable(kFalse);
		iPresetListCtrlData->Add(itemString);
	}

	iListAttr->MuteDrawing(kFalse);
	
	iPresetListCtrlData->Refresh();

	iPresetListView->Invalidate();

	// 
	// Cache the last custom preset node index.
	//
	InterfacePtr<IIntData> iLastCustomPresetIndex(iPresetListView, IID_ILASTCUSTOMPRESETINDEX);
	int32 lastIndex = static_cast<int32>(fCustomPresetList.size());
	iLastCustomPresetIndex->Set(lastIndex-1);

}

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


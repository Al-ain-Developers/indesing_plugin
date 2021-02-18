//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyfileactionsui/InCopyFileActionsComponent.cpp $
//  
//  Owner: Robin_Briggs
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
//  
//  NOTE: This plugin and all of its code was given to System Integraters 
//  as a part of Denali. To do this we needed to make sure that no
//  headers from private were included anywhere in this project. This
//  forced us to move FileUtils.h to public. To merge this code with Dragontail
//  if have re-added private access paths to this project. At some point
//  in the future FileUtils.h will need to be made public or another solution 
//  is needed for Mont Blanc. --cparrish 06.24.02
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "CActionComponent.h"

//----- ID
#include "ShuksanID.h"
#include "DocumentID.h"
#include "LayoutUIID.h"

#include "InCopySharedID.h"
#include "OpenPlaceID.h"
#include "DocSetupID.h"
#include "InCopyFileActionsUIDefs.h"
#include "InCopyFileActionsUIID.h"

//----- Util
#include "CmdUtils.h"
#include "CoreResTypes.h"
#include "ErrorUtils.h"
#include "FileUtils.h"
#include "ILayoutUIUtils.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"
#include "Utils.h"
#include "IWindowUtils.h"
#include "ISelectionUtils.h"

//----- Impl
#include "CAlert.h"
#include "SysFileList.h"
#include "UIDList.h"
#include "IBoolData.h"

//----- Interface
#include "IActionStateList.h"
#include "IApplication.h"
#include "ICommand.h"
#include "IDialog.h"
#include "IDialogMgr.h"
#include "IDocFileHandler.h"
#include "IDocFileType.h"
#include "IDocument.h"
#include "IDocumentUtils.h"
#include "IDocumentUIUtils.h"
#include "IGalleyUtils.h"
#include "IInCopyDocUtils.h"
#include "IIntData.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILayoutUtils.h"
#include "IOpenFileCmdData.h"
#include "IOpenManager.h"
#include "IPMUnknown.h"
#include "ITriStateData.h"
#include "IUIDData.h"
#include "IInCopyStoryList.h"
#include "ISelectionManager.h"
#include "ITextEditSuite.h"
#include "IActiveContext.h"
#include "IInCopyFileActionsSuite.h"

//========================================================================================
// CLASS : InCopyFileActionsComponent
//========================================================================================

class InCopyFileActionsComponent : public CActionComponent
{
public:
	InCopyFileActionsComponent(IPMUnknown *boss) : CActionComponent(boss) {}

	virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
	virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);

};


CREATE_PMINTERFACE(InCopyFileActionsComponent, kInCopyFileActionsComponentImpl)

//-----------------------------------------------------------------------------------------
#pragma mark-


//-----
// DoActions()

void InCopyFileActionsComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
//	ErrorCode err = kSuccess;
	
	switch (actionID.Get())
	{
		case kNewActionID:
		{
			
			InterfacePtr<ICommand> iDocSetupDialogCmd(CmdUtils::CreateCommand(kICDocSetupDialogCmdBoss));
			InterfacePtr<IIntData> iIntData(iDocSetupDialogCmd, UseDefaultIID() );
			InterfacePtr<IBoolData> okData(iDocSetupDialogCmd, IID_IDIALOGWASCANCELLED );
			iIntData->Set(kDoingNewDocument);

            // If we fail to bring up the dialog, then we create a default document
            if (iDocSetupDialogCmd != nil)
			{
				CmdUtils::ProcessCommand(iDocSetupDialogCmd);
				if (!okData->GetBool())
					break;		// cancel new doc dialog
				else
				{
					// Window activation calls for WritingModeControlView is responsible for setting the focus on the writing mode widget
					// It gets called from the GalleyOpenLayoutWinResp, but eventually the focus transfer call fails since the dialog is still open.
					// That's why I need to forcefully tell the active presentation to activate itself.
					IDocumentPresentation* activePresentation = Utils<IDocumentUIUtils>()->GetActiveDocumentPresentation();
					if (activePresentation)
					{
						InterfacePtr<IControlView> presentationView(activePresentation, UseDefaultIID());
						if (presentationView)
						{
							// Bug# 3739619: The text frame doesn't get focus if we are in the layout view and we just call 
							// WindowActivated(). This is because we try to give the page item focus by calling 
							// FrameViewFocus::ResumePageItemFocus(). Since the focus for the page item had never been 
							// suspended, we return prematurely from FrameViewFocus::ResumePageItemFocus(). Hence, after 
							// calling WindowActivated(), the focus ends up with the layout widget. A simple solution here is 
							// to just call WindowDeactivated() just before calling WindowActivated().
							if( Utils<IGalleyUtils>()->GetViewMode(activePresentation) == IInCopyViewPrefs::kLayout)
								presentationView->WindowDeactivated();
							presentationView->WindowActivated();
						}
					}
				}
			}			
		}
		break;

		case kInCopyNewButtonActionID:
			Utils<IInCopyDocUtils>()->DoNew();
			break;
			
		case kNewWindowActionID:
		{	
			IDocument*	doc = Utils<ILayoutUIUtils>()->GetFrontDocument();
			Utils<IInCopyDocUtils>()->DoNewWindow(::GetUIDRef(doc));
		}
		break;
	
		case kOpenActionID:
		{

			//----- Use the open manager to display the open dialog...
			InterfacePtr<IK2ServiceRegistry>		registry(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
			InterfacePtr<IK2ServiceProvider>	openMgrService(registry->QueryDefaultServiceProvider(kOpenManagerService));
			InterfacePtr<IOpenManager>		openMgr(openMgrService, IID_IOPENMANAGER);
			InterfacePtr<ITriStateData> openMgrOptions(openMgr, IID_ITRISTATEDATA);		
			
			SysFileList filesToOpen;
			if(openMgr->DoOpenDialog(filesToOpen, kTrue))
			{
				IOpenFileCmdData::OpenFlags flags = openMgrOptions->IsUnknown() ? IOpenFileCmdData::kOpenDefault : openMgrOptions->IsSelected() ?
												IOpenFileCmdData::kOpenOriginal : IOpenFileCmdData::kOpenCopy;

				ErrorCode err = kSuccess;
				
				for (int32 i = 0;  (i < filesToOpen.GetFileCount()) && (err == kSuccess); i++)
				{
					const IDFile *ithFile = filesToOpen.GetNthFile(i);

					UIDRef newDocRef = Utils<IInCopyDocUtils>()->DoOpen(*ithFile, flags);

					err = ErrorUtils::PMGetGlobalErrorCode();

					if (err == kSuccess && newDocRef != UIDRef::gNull)
					{
						bool16 incopyPackageFile(kFalse);
						{	// scope so we can update design
							InterfacePtr<IDocFileType> docType(newDocRef, UseDefaultIID());
							incopyPackageFile = docType && docType->GetDocFileType() == kInCopyPackageFileTypeInfoID;
						}

						if (incopyPackageFile && Utils<IInCopyDocUtils>()->CanDoUpdateDesign(newDocRef))
						{
							PMString message("Package_Assignment_Already_Open_Update", PMString::kTranslateDuringCall);
							int16 button = CAlert::ModalAlert(message, kYesString, kNoString, kNullString, 1, CAlert::eInformationIcon);
							if (button == 1)
							{
								Utils<IInCopyDocUtils>()->DoUpdateDesign(newDocRef);
							}
						}
					}
				}
			}
		}
		break;
		
		case kBrowseActionID:
		case kBrowseNewWindowActionID:
		{
			// Issue the BrowseTo command to the Bridge
			ErrorCode browseErr = FileUtils::BrowseToFile(nil, ((actionID.Get() == kBrowseNewWindowActionID) ? FileUtils::kOpenNewWindow : FileUtils::kNormal));
			
			// Report any errors to the user
			if ( browseErr ) {
				PMString errString("BrowseFailed");
				CAlert::ErrorAlert(errString);
			}
		}
		break;
	
		case kSaveAsActionID:
		{
			Utils<IInCopyDocUtils>()->DoSaveAs(::GetUIDRef(Utils<ILayoutUIUtils>()->GetFrontDocument()));
		}
		break;
	
		case kSaveAllStoriesActionID:
		{
			Utils<IInCopyDocUtils>()->DoSaveAll(::GetUIDRef(Utils<ILayoutUIUtils>()->GetFrontDocument()));
		}
		break;
	
		case kSaveActionID:
		{
			InterfacePtr<IInCopyFileActionsSuite> icSuite(ac->GetContextSelection(), UseDefaultIID());
			if (icSuite)
				icSuite->DoSaveStory();
		}
		break;

		case kSaveACopyActionID:
		{
			Utils<IInCopyDocUtils>()->DoSaveAs(::GetUIDRef(Utils<ILayoutUIUtils>()->GetFrontDocument()), kTrue);
		}
		break;
			
		case kRevertActionID:	
		{
			Utils<IInCopyDocUtils>()->DoRevert(::GetUIDRef(Utils<ILayoutUIUtils>()->GetFrontDocument()));
		}
		break;
			
		case kRevertStoryActionID:	
		{
			InterfacePtr<IInCopyFileActionsSuite> icSuite(ac->GetContextSelection(), UseDefaultIID());
			if (icSuite)
				icSuite->DoRevertStory();
		}
		break;
			
		case kCloseActionID:
		{	
			// Close the frontmost document window
			// The document closed message is scheduled for the last window on a document.
			
			Utils<IDocumentUIUtils>()->CloseActivePresentation();
		}
		break;
		
		case kUpdateDesignActionID:
		{
			Utils<IInCopyDocUtils>()->DoUpdateDesign(::GetUIDRef(Utils<ILayoutUIUtils>()->GetFrontDocument()));
		}
		break;
		
		//------------------------------------------------------------------
		// TEMP : Old Open and Save actions
		//        Keep in place until new doc format conversion is complete
		//------------------------------------------------------------------
			
		//case kSaveOldActionID:		// Save the document associated with the frontmost doc win into a file
		//{
		//	{
		//		InterfacePtr<IDocumentUtils> docUtils ( (IDocumentUtils*)GetExecutionContextSession()->QueryInterface(IID_IDOCUMENTUTILS));
		//		ASSERT_MSG(docUtils != nil, "docUtils != nil");
		//		docUtils->DoSave(Utils<ILayoutUIUtils>()->GetFrontDocument());
		//	}			

		//}
		//break;
		
		//------------------------------------------------------------------
		// TEMP
		//------------------------------------------------------------------		
				
		default:
		{
			ASSERT_FAIL("InCopyFileActionsComponent :: HandleMenu got bad ID");
		}
		break;
	}
}


//------
// UpdateActionsStates()

void InCopyFileActionsComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
	UIDRef		doc(::GetUIDRef(Utils<ILayoutUIUtils>()->GetFrontDocument()));
	int32		count = listToUpdate->Length();
	
	// try to find a responsible doc file handler
	InterfacePtr<IDocFileHandler> docFileHandler(Utils<IDocumentUtils>()->QueryDocFileHandler(doc));				
	
	while (count--)
	{
		ActionID actionID = listToUpdate->GetNthAction(count);
		int16 state = kDisabled_Unselected;
		switch (actionID.Get())
		{												
			case kSaveAsActionID:
				{
					if(docFileHandler) {
						if (docFileHandler->CanSaveAs(doc)) {
							InterfacePtr<IDocFileType> dType(doc, UseDefaultIID());
							PMString menuName;
							FileTypeInfoID fileInfoID = dType->GetDocFileType();
							if ( fileInfoID == kTEXTFileTypeInfoID || fileInfoID == kRTFFileTypeInfoID)
								menuName = "Save &As...";
							else
								menuName = "Save Story &As...";
						
							listToUpdate->SetNthActionName(count, menuName);

							state = kEnabledAction;
						}
					}
				}
				break;
					
			case kSaveActionID:
				{
					InterfacePtr<IInCopyFileActionsSuite> icSuite(ac->GetContextSelection(), UseDefaultIID());
					if (icSuite && icSuite->CanSaveStory())	
					{
						InterfacePtr<IDocFileType> dType(doc, UseDefaultIID());
						PMString menuName;
						FileTypeInfoID fileInfoID = dType->GetDocFileType();
						if ( fileInfoID == kTEXTFileTypeInfoID || fileInfoID == kRTFFileTypeInfoID)
							menuName = "&Save";
						else
							menuName = "&Save Story";
					
						listToUpdate->SetNthActionName(count, menuName);
						state = kEnabledAction;
					}
				}
				break;
				
			case kSaveAllStoriesActionID:
				{
					if (Utils<IInCopyDocUtils>()->CanDoSaveAll(doc))
						state = kEnabledAction;
				}
				break;
				
			case kSaveACopyActionID:
				{
					if(docFileHandler) {
						if (docFileHandler->CanSaveACopy(doc)) {
										InterfacePtr<IDocFileType> dType(doc, UseDefaultIID());
						PMString menuName;
						FileTypeInfoID fileInfoID = dType->GetDocFileType();
						if ( fileInfoID == kTEXTFileTypeInfoID || fileInfoID == kRTFFileTypeInfoID)
							menuName = "Save a Copy...";
						else
							menuName = "Save Story Copy...";
					
						listToUpdate->SetNthActionName(count, menuName);
						state = kEnabledAction;
						}
					}
				}
				break;

			case kRevertActionID:
				{
					if (Utils<IInCopyDocUtils>()->CanDoRevert(doc))	
						state = kEnabledAction;
				}
				break;

			case kRevertStoryActionID:
				{
					InterfacePtr<IInCopyFileActionsSuite> icSuite(ac->GetContextSelection(), UseDefaultIID());
					if (icSuite && icSuite->CanRevertStory())	
						state = kEnabledAction;
				}
				break;

			case kCloseActionID:
				{
				// mClose, mCloseDoc, mCloseAll - enabled if a window is open
				if(Utils<IDocumentUIUtils>()->GetActiveDocumentPresentation() != nil) //SEIssue <sheridan>
					state = kEnabledAction;
				break;
				}
				
			case kUpdateDesignActionID:
				{
					if (Utils<IInCopyDocUtils>()->CanDoUpdateDesign(doc))
						state = kEnabledAction;
				}
				break;

			//case kSaveOldActionID:
			//	{
			//		if(docFileHandler)
			//			if (docFileHandler->CanSave(doc)) {
			//				state = kEnabledAction;
			//			}
			//	}
			//	break;

			default:
				ASSERT_FAIL("InCopyFileActionsComponent :: UpdateActionStates - why did I get called?");
				break;
		}
		listToUpdate->SetNthActionState(count, state);
	}
}

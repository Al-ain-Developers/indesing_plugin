//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/gotoanchor/GoToAnchorPanelObserver.cpp $
//  
//  Owner: Mark VerMurlen
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

// ----- Interface Includes -----

#include "IAnchorTypeListData.h"
#include "IApplication.h"
#include "IBehaviorData.h"
#include "IControlView.h"
#include "IDocument.h"
#include "IDocumentCommands.h"
#include "IDocumentList.h"
#include "IDropDownListController.h"
#include "IFormFieldSuite.h"
#include "IGotoAnchorBehaviorData.h"
#include "ILayoutUIUtils.h"
#include "IListControlDataOf.h"
#include "IOpenFileCmdData.h"
#include "IPubFile.h"
#include "IStringData.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "IUIDData.h"
#include "IWidgetParent.h"
#include "IWidgetUtils.h"

#include "IAnchorFileListData.h"

// ----- Implementation Includes -----

#include "CBehaviorPanelObserver.h"
#include "K2Pair.h"

#include "BehaviorUIDefs.h"
#include "ErrorUtils.h"
#include "FormFieldUIUtils.h"
#include "Utils.h"

#include "BehaviorUIID.h"
#include "OpenPlaceID.h"
#include "widgetid.h"

//========================================================================================
// CLASS GoToAnchorPanelObserver
//========================================================================================

class GoToAnchorPanelObserver : public CBehaviorPanelObserver
{
public:
	GoToAnchorPanelObserver(IPMUnknown *boss);
	virtual ~GoToAnchorPanelObserver();

	virtual void 	AutoAttach();
	virtual void 	AutoDetach();

protected:
	virtual void HandleSelectionUpdate
		(
		const ClassID&	inBossClassID, 
		ISubject* inSubject, 
		const PMIID& 	inProtocol,
		void* 			inMessage
		);
	virtual void	InitializeFieldsFromActionData(const IBehaviorData* inActionData);
	virtual bool	ApplyFieldsToActionData(IBehaviorData* inActionData);

private:
	void			LoadZoomChoices(IListControlDataOf< K2Pair<PMString, int32> >* movieOpData);
	void			InitializeZoomChoice(const IBehaviorData* inActionData);
	void			InitializeDocumentChoice(const IBehaviorData* inActionData);
	IDocument*		FindDocInDocList( IDFile &theSysFile );
	
	bool	isAttached;
};

//========================================================================================
// METHODS GoToAnchorPanelObserver
//========================================================================================

CREATE_PMINTERFACE(GoToAnchorPanelObserver, kGoToAnchorPanelObserverImpl)

//----------------------------------------------------------------------------------------
// GoToAnchorPanelObserver constructor 
//----------------------------------------------------------------------------------------

GoToAnchorPanelObserver::GoToAnchorPanelObserver(IPMUnknown *boss) :
	CBehaviorPanelObserver(boss),
	isAttached(false)
{
}


//----------------------------------------------------------------------------------------
// GoToAnchorPanelObserver::~GoToAnchorPanelObserver
//----------------------------------------------------------------------------------------

GoToAnchorPanelObserver::~GoToAnchorPanelObserver()
{
}

//----------------------------------------------------------------------------------------
// GoToAnchorPanelObserver::AutoAttach
//----------------------------------------------------------------------------------------

void GoToAnchorPanelObserver::AutoAttach()
{
	if ( ! isAttached ) {
		
		CBehaviorPanelObserver::AutoAttach();
		
		AttachToWidget(kAnchorDocumentChoicesWidgetID, IID_ISTRINGLISTCONTROLDATA);
		AttachToWidget(kAnchorChoicesWidgetID, IID_ISTRINGLISTCONTROLDATA);
		AttachToWidget(kZoomWidgetID, IID_ISTRINGLISTCONTROLDATA);
		
		isAttached = true;
		
#if 0
		InterfacePtr<IControlView> addUpdateButtonView((IControlView *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kAddBehaviorButtonWidgetID, IID_ICONTROLVIEW));
		
		if ( ! addUpdateButtonView->IsEnabled() )
			addUpdateButtonView->Enable();
#endif

	}
}

//----------------------------------------------------------------------------------------
// GoToAnchorPanelObserver::AutoDetach
//----------------------------------------------------------------------------------------

void GoToAnchorPanelObserver::AutoDetach()
{
	if ( isAttached ) {
		
		CBehaviorPanelObserver::AutoDetach();
		
		DetachFromWidget(kAnchorDocumentChoicesWidgetID, IID_ISTRINGLISTCONTROLDATA);
		DetachFromWidget(kAnchorChoicesWidgetID, IID_ISTRINGLISTCONTROLDATA);
		DetachFromWidget(kZoomWidgetID, IID_ISTRINGLISTCONTROLDATA);
		
		isAttached = false;
	}
}

//----------------------------------------------------------------------------------------
// GoToAnchorPanelObserver::HandleSelectionUpdate
//----------------------------------------------------------------------------------------

void GoToAnchorPanelObserver::HandleSelectionUpdate
	(
	const ClassID&	inBossClassID, 
	ISubject* inSubject, 
	const PMIID& 	inProtocol,
	void* 			inMessage
	)
{
	InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
	
	if ( iFormSuite && !iFormSuite->IsDefaultSelection() && iFormSuite->IsFieldSelection() )
	{
		if ( inProtocol == IID_ISTRINGLISTCONTROLDATA )
		{
			CBehaviorPanelObserver::HandleSelectionUpdate(inBossClassID, inSubject, inProtocol, inMessage);
		}
		else
		{
			InitializeFieldsFromActionData(nil);
		}
		return;
	}

	ActiveSelectionObserver::HandleSelectionUpdate(inBossClassID, inSubject, inProtocol, inMessage);
}

//----------------------------------------------------------------------------------------
// GoToAnchorPanelObserver::InitializeFieldsFromActionData
//----------------------------------------------------------------------------------------

void GoToAnchorPanelObserver::InitializeFieldsFromActionData(const IBehaviorData* inActionData)
{
	if ( inActionData )
	{
		InitializeZoomChoice(inActionData);
		InitializeDocumentChoice(inActionData);
	}
	else
	{
		InterfacePtr<IUIDData> activeBehavior(FormFieldUIUtils::QueryActiveBehavior());
		if ( activeBehavior )
		{
			InterfacePtr<IBehaviorData> iBehaviorData(activeBehavior->GetRef(), UseDefaultIID());
			if ( iBehaviorData )
				InitializeFieldsFromActionData(iBehaviorData);
		}
	}
}

//----------------------------------------------------------------------------------------
// GoToAnchorPanelObserver::InitializeFieldsFromActionData
//----------------------------------------------------------------------------------------

bool GoToAnchorPanelObserver::ApplyFieldsToActionData(IBehaviorData* inActionData)
{
	IGoToAnchorBehaviorData* actionData = static_cast<IGoToAnchorBehaviorData*>(inActionData);

		// Find the associated data list for the document choice drop down
	InterfacePtr<IDropDownListController> documentChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kAnchorDocumentChoicesWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr<IAnchorFileListData> anchorFileData(documentChoice, IID_IANCHORFILEDATA);
	K2Vector<IAnchorFileListData::AnchorFileData> theAnchorFileList = anchorFileData->GetAnchorFileData();
		
	int32 iDocChoice = documentChoice->GetSelected();
	if ( iDocChoice < 0 )
		return false;

	bool bChanged = false;

		// Find the associated data list for the zoom choice drop down
	InterfacePtr<IDropDownListController> zoomChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kZoomWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr< IListControlDataOf< K2Pair<PMString, int32> > > zoomData(zoomChoice, IID_ILISTCONTROLDATA);
	
		// Get the zoom choice and save in the action data
	if ( actionData->GetZoom() != (IGoToAnchorBehaviorData::Zoom) (*zoomData)[zoomChoice->GetSelected()].second)
	{
		bChanged = true;
		actionData->SetZoom((IGoToAnchorBehaviorData::Zoom) (*zoomData)[zoomChoice->GetSelected()].second);
	}

		// Get the IDFile string representation from the data list and save in action data
	PMString selectedSysFile = theAnchorFileList[iDocChoice].GetSysFile();
	if ( actionData->GetAnchorFile() != selectedSysFile )
	{
		actionData->SetAnchorFile( selectedSysFile );
		bChanged = true;
	}

		// Find the associated data list for the anchor choices drop down
	InterfacePtr<IDropDownListController> anchorChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kAnchorChoicesWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr<IAnchorTypeListData> anchorTypeData(anchorChoice, IID_IANCHORTYPEDATA);
	K2Vector<IAnchorTypeListData::AnchorTypeData> theAnchorTypeList = anchorTypeData->GetAnchorTypeData();

		// If nothing selected, then don't save any action.
	if ( anchorChoice->GetSelected() < 0 )
	{
		return false;
	}
		// Get the anchor display name from the data list and save in the action data
	PMString selectedAnchorName = theAnchorTypeList[ anchorChoice->GetSelected()].GetAnchorName();

		// Get the anchor UID from the data list and save in the action data
	UID selectedAnchorUID = theAnchorTypeList[ anchorChoice->GetSelected()].GetAnchorUID();
	if ( actionData->GetAnchorUID() != selectedAnchorUID )
	{
		bChanged = true;
		actionData->SetAnchorUID( selectedAnchorUID );
	}
	
	return bChanged;
}

//----------------------------------------------------------------------------------------
// GoToAnchorPanelObserver::LoadZoomChoices
//----------------------------------------------------------------------------------------

void GoToAnchorPanelObserver::LoadZoomChoices(IListControlDataOf< K2Pair<PMString, int32> >* gotoData)
{
	if ( gotoData->Length() != 5 )
	{
		gotoData->Clear();

		gotoData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/GoToView/Inherit Zoom", IGoToAnchorBehaviorData::kInherit));
		gotoData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/GoToView/Actual Size", IGoToAnchorBehaviorData::kActualSize));
		gotoData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/GoToView/Fit In Window", IGoToAnchorBehaviorData::kFitInWindow));
		gotoData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/GoToView/Fit Width", IGoToAnchorBehaviorData::kFitWidth));
		gotoData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/GoToView/Fit Visible", IGoToAnchorBehaviorData::kFitVisible));
	}	
}

//----------------------------------------------------------------------------------------
// GoToAnchorPanelObserver::InitializeZoomChoice
//----------------------------------------------------------------------------------------

void GoToAnchorPanelObserver::InitializeZoomChoice(const IBehaviorData* inActionData)
{
	InterfacePtr<IDropDownListController> zoomChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kZoomWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr< IListControlDataOf< K2Pair<PMString, int32> > > zoomData(zoomChoice, IID_ILISTCONTROLDATA);

	LoadZoomChoices(zoomData);

	//zoomChoice->Deselect(kTrue, kFalse);

	if (inActionData == 0)
		zoomChoice->Select(0, kTrue, kFalse);
	else
	{
		bool bFound = false;
		InterfacePtr<IGoToAnchorBehaviorData> actionData(inActionData, UseDefaultIID());
		for (int32 i = 0; i < zoomData->Length(); i++)
			if ((*zoomData)[i].second == actionData->GetZoom())
			{
				bFound = true;
				if ( !zoomChoice->IsSelected(i) )
					zoomChoice->Select(i, kTrue, kFalse);
				break;
			}

		if ( !bFound )
			zoomChoice->Deselect(kTrue, kFalse);
	}

	ASSERT(zoomChoice->GetSelected() != IDropDownListController::kNoSelection);
}

//----------------------------------------------------------------------------------------
// GoToAnchorPanelObserver::InitializeDocumentChoice
//----------------------------------------------------------------------------------------

void GoToAnchorPanelObserver::InitializeDocumentChoice(const IBehaviorData* inActionData)
{
		// Get access to the open document list
    InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
    InterfacePtr<IDocumentList> docList(app->QueryDocumentList());
	
		// Get access to the drop down list
	InterfacePtr<IDropDownListController> documentChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kAnchorDocumentChoicesWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr<IStringListControlData> openDocData(documentChoice, IID_ISTRINGLISTCONTROLDATA);

		// Get the associated data list for the document choice drop down
	InterfacePtr<IAnchorFileListData> anchorFileData(documentChoice, IID_IANCHORFILEDATA);
    K2Vector<IAnchorFileListData::AnchorFileData> theAnchorFileList = anchorFileData->GetAnchorFileData();

		// used to set the anchor name for this controller, so it can be used
		// by the dropdown list initialize function.
	InterfacePtr<IStringData> actionType(this, UseDefaultIID());
	
		// Make sure the list is cleared first.
	openDocData->Clear();
	theAnchorFileList.clear();
	int32 selectMe = 0;
#if 0
// use a separate button for the "Browse..." operation.
#if MACINTOSH
	PMString choose("$$$/Dialog/Behaviors/Choose...");
#else
	PMString choose("$$$/Dialog/Behaviors/Browse...");
#endif
	openDocData->AddString(choose);
#endif

	PMString frontDocName("");

		// Get the front document, so we can set the drop down list to this
		// entry
	if (inActionData == 0)
	{
		IDocument* frontDoc = Utils<ILayoutUIUtils>()->GetFrontDocument();
		frontDoc->GetName( frontDocName );
		actionType->Set("");
	}
	else
	{	
		InterfacePtr<IGoToAnchorBehaviorData> actionData(inActionData, UseDefaultIID());
		
		PMString behaviorFile = actionData->GetAnchorFile();
		IDFile behaviorSysFile( behaviorFile );
		
		// Check if the file still exists
		if ( FileUtils::DoesFileExist(behaviorSysFile) ) {
			
			IDocument* behaviorDoc = FindDocInDocList( behaviorSysFile );
			if ( !behaviorDoc )
			{
				GlobalErrorStatePreserver errorPreserver;
				InterfacePtr<ICommand> openDocCmd(Utils<IDocumentCommands>()->CreateOpenCommand(behaviorSysFile, kSuppressUI, IOpenFileCmdData::kOpenOriginal, IOpenFileCmdData::kUseLockFile, kFalse));
				
				CmdUtils::ProcessCommand(openDocCmd);
				if (ErrorUtils::PMGetGlobalErrorCode() == kSuccess)
				{
					behaviorDoc = docList->FindDoc( behaviorSysFile );
					if ( behaviorDoc )
						behaviorDoc->GetName(frontDocName);
				}
			}
			else
			{
				behaviorDoc->GetName(frontDocName);
			}
		}

		actionType->Set(actionData->GetAnchorName() );
	}

		// For all entries in the list of documents, add the string into
		// the drop down list.
    if ( docList )
    {
    	int32 docCount = 0;
        for (int32 i = 0; i < docList->GetDocCount(); i++ )
		{
			IDocument* doc = docList->GetNthDoc(i);
			
			PMString addName("");
			doc->GetName(addName);

				// If the front document is that same as this entry in the 
				// open doc list, mark this as the one to select
			if ( frontDocName == addName )
			{
				selectMe = docCount;
			}
			else
			{
				// Make sure that the document is saved before adding it to the list
				if ( ! doc->IsSaved() ) continue;
			}

				// Store away the other relevant information for use later
			const IDFile* docSysFile = doc->GetDocWorkSpace().GetDataBase()->GetSysFile();
			if ( !docSysFile )
			{
				docSysFile = doc->GetDocWorkSpace().GetDataBase()->GetPubFile()->GetTempFile();
			}
			theAnchorFileList.push_back(IAnchorFileListData::AnchorFileData( FileUtils::SysFileToPMString( *docSysFile ), addName)); 

				// Add the display string to the drop down
			openDocData->AddString( addName );
			
			docCount++;
		}

			// Put the associated data list back
		anchorFileData->SetAnchorFileData( theAnchorFileList);

			// Select the front document
		documentChoice->Select(selectMe, kTrue, kFalse);
	}

}

//------------------------------------------------------------
// GoToAnchorPanelObserver::FindDocInDocList
//------------------------------------------------------------
IDocument* GoToAnchorPanelObserver::FindDocInDocList(IDFile &theSysFile)
{
	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IDocumentList> docList(app->QueryDocumentList());
	
	IDocument* thisDoc = nil;
	if ( docList )
	{
		for (int i = 0; i < docList->GetDocCount(); i++)
		{
			IDocument* iterDoc = docList->GetNthDoc(i);
			const IDFile *openfile = ::GetDataBase(docList->GetNthDoc(i))->GetSysFile();
			if(openfile != nil)
			{
				if (FileUtils::IsEqual(*openfile, theSysFile))
				{
					thisDoc = docList->GetNthDoc(i);
				}
			}
			else
			{
				const IDFile *openfile2 = (::GetDataBase(docList->GetNthDoc(i))->GetPubFile())->GetTempFile();
				if (openfile2 != nil )
				{
					if (FileUtils::IsEqual(*openfile2, theSysFile ))
					{
						thisDoc = docList->GetNthDoc(i);
					}
				}
			}
		}
	}

	return thisDoc;
}


//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/gotoanchor/GoToAnchorDocumentObserver.cpp $
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

#include "IAnchorFileListData.h"
#include "IApplication.h"
#include "IBehaviorSuite.h"
#include "IBookMarkData.h"
#include "IControlView.h"
#include "IDialogMgr.h"
#include "IDialog.h"
#include "IDocument.h"
#include "IDocumentCommands.h"
#include "IDocumentList.h"
#include "IDropDownListController.h"
#include "IHyperlinkTable.h"
#include "IHyperlinkDestination.h"
#include "IIntData.h"
#include "IOpenFileCmdData.h"
#include "IOpenFileDialog.h"
#include "ISession.h"
#include "IStringListControlData.h"
#include "IStringData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "IUIDData.h"
#include "IWidgetUtils.h"
#include "IWidgetParent.h"
#include "IWindow.h"
#include "IHyperlinkTextDestinationData.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "OpenPlaceID.h"
#include "widgetid.h"
#include "BehaviorUIDefs.h"
#include "CActiveSelectionObserver.h"
#include "RsrcSpec.h"
#include "LocaleSetting.h"
#include "CoreResTypes.h"
#include "SelectionUtils.h"
#include "SysFileList.h"

#include "CmdUtils.h"
#include "ErrorUtils.h"
#include "FileUtility.h"

#include "IAnchorTypeListData.h"

//========================================================================================
// CLASS GoToAnchorDocumentObserver
//========================================================================================

class GoToAnchorDocumentObserver : public CActiveSelectionObserver
{
public:
	GoToAnchorDocumentObserver(IPMUnknown *boss);
	virtual ~GoToAnchorDocumentObserver();
	
	virtual void 	AutoAttach();
	virtual void 	AutoDetach();
	virtual void 	Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
	
protected:
	virtual void	HandleSelectionChanged(const ISelectionMessage*);
	virtual void	SetAnchorChoice();

private:
	//void			ChooseDocument(IDropDownListController *documentChoice, IStringListControlData *openDocData) const;
	bool			GetFileToImportFromUser(IDFile& sysFile) const;
	void			LoadFromUserPlatformSettings(IOpenFileDialog* dialog) const;

private:
	OSType			fCreator;
	OSType			fType;

};

//========================================================================================
// METHODS GoToAnchorDocumentObserver
//========================================================================================

CREATE_PMINTERFACE(GoToAnchorDocumentObserver, kAnchorDocumentDDLObserverImpl)

//----------------------------------------------------------------------------------------
// GoToAnchorDocumentObserver constructor 
//----------------------------------------------------------------------------------------

GoToAnchorDocumentObserver::GoToAnchorDocumentObserver(IPMUnknown *boss) :
	CActiveSelectionObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// GoToAnchorDocumentObserver::~GoToAnchorDocumentObserver
//----------------------------------------------------------------------------------------

GoToAnchorDocumentObserver::~GoToAnchorDocumentObserver()
{
}

//----------------------------------------------------------------------------------------
// GoToAnchorDocumentObserver::AutoAttach
//----------------------------------------------------------------------------------------

void GoToAnchorDocumentObserver::AutoAttach()
{
	CActiveSelectionObserver::AutoAttach();

        // Make to sure to attach to yourself
    InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
    if (subject)
        subject->AttachObserver(this, IID_ISTRINGLISTCONTROLDATA);
		
	SetAnchorChoice();
}

//----------------------------------------------------------------------------------------
// GoToAnchorDocumentObserver::AutoDetach
//----------------------------------------------------------------------------------------

void GoToAnchorDocumentObserver::AutoDetach()
{
	CActiveSelectionObserver::AutoDetach();

		// Make to sure to detach from yourself
    InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
    if (subject)
        subject->DetachObserver(this, IID_ISTRINGLISTCONTROLDATA);
}

//----------------------------------------------------------------------------------------
// GoToAnchorDocumentObserver::Update
//----------------------------------------------------------------------------------------

void GoToAnchorDocumentObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	if ( theChange == kPopupChangeStateMessage )
	{
		SetAnchorChoice();
	}
	else
		CActiveSelectionObserver::Update(theChange, theSubject, protocol, changedBy);
}

//----------------------------------------------------------------------------------------
// GoToAnchorDocumentObserver::HandleSelectionChanged
//----------------------------------------------------------------------------------------

void GoToAnchorDocumentObserver::HandleSelectionChanged(const ISelectionMessage*)
{
	InterfacePtr<IBehaviorSuite> actionSuite (SelectionUtils::QuerySuite<IBehaviorSuite>());
	InterfacePtr<IControlView> view(this, UseDefaultIID());
	view->Enable(actionSuite && actionSuite->CanApplyActions());
}

//----------------------------------------------------------------------------------------
// GoToAnchorDocumentObserver::ChooseDocument
//----------------------------------------------------------------------------------------
#if 0
// Used if "Browse..." is part of the documents dropdown instead of a separate button.
void GoToAnchorDocumentObserver::ChooseDocument(IDropDownListController *documentChoice, IStringListControlData *openDocData) const
{
	IDFile file;
	
	if (GetFileToImportFromUser(file))
	{
		FileUtility fileUtility(file);
		
		InterfacePtr<ICommand> openDocCmd(Utils<IDocumentCommands>()->CreateOpenCommand(file, kSuppressUI, IOpenFileCmdData::kOpenOriginal, IOpenFileCmdData::kUseLockFile, kFalse));

		CmdUtils::ProcessCommand(openDocCmd);

		if (ErrorUtils::PMGetGlobalErrorCode() == kSuccess)
		{
				// Get the associated data list for the document choice drop down
			InterfacePtr<IAnchorFileListData> anchorFileData(documentChoice, IID_IANCHORFILEDATA);
			K2Vector<IAnchorFileListData::AnchorFileData> theAnchorFileList = anchorFileData->GetAnchorFileData();

			const UIDList* cmdList = openDocCmd->GetItemList();
			IDataBase* docDB = cmdList->GetDataBase();
			if (docDB != nil)
			{
				InterfacePtr<IDocument> thisDoc((IDocument*)docDB->Instantiate(cmdList->First(), IID_IDOCUMENT));
				PMString addName("");
				thisDoc->GetName(addName);

					// Store away the other relevant information for use later
				const IDFile* docSysFile = thisDoc->GetDocWorkSpace().GetDataBase()->GetSysFile();
				if ( !docSysFile )
				{
					docSysFile = thisDoc->GetDocWorkSpace().GetDataBase()->GetPubFile()->GetTempFile();
				}
				theAnchorFileList.push_back(IAnchorFileListData::AnchorFileData( FileUtils::SysFileToPMString( *docSysFile ), addName)); 
				anchorFileData->SetAnchorFileData( theAnchorFileList);

					// Add the display string to the drop down
				openDocData->AddString( addName );
				int32 selectMe = openDocData->GetIndex( addName );
				documentChoice->Select( selectMe );
				return;
			}
		}
	}
	
	documentChoice->Select(0);
}
#endif

//----------------------------------------------------------------------------------------
// GoToAnchorDocumentObserver::SetAnchorChoice
//----------------------------------------------------------------------------------------

void GoToAnchorDocumentObserver::SetAnchorChoice()
{
	InterfacePtr<IWidgetParent> parentPtr(this, UseDefaultIID());
	InterfacePtr<IStringData> anchorName((IStringData*) parentPtr->QueryParentFor(IID_ISTRINGDATA));
	PMString anchorNameStr = anchorName->Get();

		// Figure out what document is selected in the document drop down list
	InterfacePtr<IDropDownListController> documentChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kAnchorDocumentChoicesWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr<IStringListControlData> openDocData(documentChoice, IID_ISTRINGLISTCONTROLDATA);
	
	//if ( documentChoice->GetSelected() == IDropDownListController::kBeginning )
	//{
	//	ChooseDocument(documentChoice.get(), openDocData.get());
	//}
	
	int32 docIndex = documentChoice->GetSelected();
	if ( docIndex < 0 || docIndex >= openDocData->Length() )
		return;
		
	PMString selectedDocName = openDocData->GetString( docIndex );

		// Get the list of open documents 
    InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
    InterfacePtr<IDocumentList> docList(app->QueryDocumentList());

		// Get access to this drop down list and clear it
	InterfacePtr<IDropDownListController> anchorChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kAnchorChoicesWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr<IControlView> anchorChoiceView( anchorChoice, IID_ICONTROLVIEW );
	
		// Get the associated data list for the anchor choices drop down list
	InterfacePtr<IAnchorTypeListData> anchorTypeData(anchorChoice, IID_IANCHORTYPEDATA);
	K2Vector<IAnchorTypeListData::AnchorTypeData> theAnchorTypeList = anchorTypeData->GetAnchorTypeData();
	theAnchorTypeList.clear();
	
	InterfacePtr<IStringListControlData> anchorData(anchorChoice, IID_ISTRINGLISTCONTROLDATA);
	anchorData->Clear();
	
		// For all entries in the list of documents, check to see if the
		// selected document matches. If so add all text anchors from that
		// file to the drop down list.
    if ( docList )
    {
        for (int32 i = 0; i < docList->GetDocCount(); i++ )
		{
			PMString listName("");
			docList->GetNthDoc(i)->GetName(listName);
			if ( selectedDocName == listName )
			{
					// Get the database for this doc
				IDocument* theDoc = docList->GetNthDoc(i);
				IDataBase* db = theDoc->GetDocWorkSpace().GetDataBase();

					// Get the Hyperlink table for this doc
				InterfacePtr<IHyperlinkTable> docHyperlinkTable(db, db->GetRootUID(), IID_IHYPERLINKTABLE);
				
					// Walk through all the destinations in this document and 
					// check for Text anchor types.
				for (UniqueKeyToUIDMap::const_iterator iter = docHyperlinkTable->GetDestinationKeyToUIDMapBeginIter(); 
					iter != docHyperlinkTable->GetDestinationKeyToUIDMapEndIter(); ++iter)
				{
					UID destUID = iter->second;
					InterfacePtr<IHyperlinkDestination> thisHyperlinkDestination(db, destUID, IID_IHYPERLINKDESTINATION);

						// Set the anchor type static text widget
					PMString destType("");
					thisHyperlinkDestination->GetType( &destType );

					// Only show text anchor and page types for the Go To Anchor behavior
					if ( destType == "Text anchor") 
					{
						// we don't care about paragraph destination
						InterfacePtr<IHyperlinkTextDestinationData> destData(db, destUID, UseDefaultIID());
						if (!destData || destData->IsParagraphDestination())
							continue;
					}
					else if (destType != "Page")
					{
						continue;
					}
					
					PMString displayName("");
					PMString orgAnchorName("");
					thisHyperlinkDestination->GetName( &displayName );
					orgAnchorName = displayName;
					
					// A hyperlink destination could also be a bookmark in which case it will have a weird name.
					// So search to check if this hyperlink is really a bookmark and if so grab the display name
					// from the bookmark.
					bool hasBookmarkName = false;
					for (int32 n = 0; n < docHyperlinkTable->GetBookmarkCount(); ++n)
					{
						InterfacePtr<IBookMarkData> bookmark( db, docHyperlinkTable->GetNthBookmark(n), UseDefaultIID() ) ;
						if ( bookmark->GetDestinationUID() == destUID )
						{
							displayName = bookmark->GetName();
							destType = PMString("$$$/Dialog/Behaviors/GoToView/Bookmark");
							hasBookmarkName = true;
							break;
						}
					}
					
						// Don't show archors that are supposed to be hidden and don't have a Bookmark Name
					if ( thisHyperlinkDestination->IsHidden() && hasBookmarkName == false ) 
						continue;

						// Store away the other relevant information for use later
					bool inserted = false;
					for ( int32 j = 0; j< theAnchorTypeList.size() && !inserted; j++ ) {
						if ( displayName < theAnchorTypeList[j].GetDisplayName() ) {
							theAnchorTypeList.insert(theAnchorTypeList.begin() + j, IAnchorTypeListData::AnchorTypeData(destUID, displayName, orgAnchorName, destType));
							inserted = true;
						}
					}
					if ( !inserted )
						theAnchorTypeList.push_back(IAnchorTypeListData::AnchorTypeData(destUID, displayName, orgAnchorName, destType));

				}

			}

		}

			// And select the first entry so there is an indication to 
			// the user that the list has entries.
		if ( theAnchorTypeList.size() > 0 ) {
			
			int32 anchorSelect = 0;
			//PMString anchorSelectType(theAnchorTypeList[0].GetAnchorType());
			
			// Loop to copy the sorted anchor list into the
			for ( int32 k = 0; k< theAnchorTypeList.size(); k++ ) {
				anchorData->AddString( theAnchorTypeList[k].GetDisplayName() );
				if ( anchorNameStr == theAnchorTypeList[k].GetDisplayName() ) {
					anchorSelect = k;
					//anchorSelectType = theAnchorTypeList[k].GetAnchorType();
				}
			}
			
				// Put the associated data list back
			anchorTypeData->SetAnchorTypeData( theAnchorTypeList );
			anchorChoice->Select(anchorSelect);
			anchorChoiceView->Enable();
			//anchorType->SetString( anchorSelectType );
		}
		else {
			PMString none("$$$/Dialog/Behaviors/GoToView/None");
			anchorData->AddString( none );
			theAnchorTypeList.push_back(IAnchorTypeListData::AnchorTypeData( kInvalidUID, none, none, PMString("") ));
				
				// Put the associated data list back
			anchorTypeData->SetAnchorTypeData( theAnchorTypeList );
			
			anchorChoice->Select(0, true, false);
			anchorChoiceView->Disable();
			//anchorType->SetString( PMString("") );
		}
	}
}

//----------------------------------------------------------------------------------------
// GoToAnchorDocumentObserver::GetFileToImportFromUser
//----------------------------------------------------------------------------------------

bool GoToAnchorDocumentObserver::GetFileToImportFromUser(IDFile& sysFile) const
{
	InterfacePtr<IOpenFileDialog> openFileDialog((IOpenFileDialog*)::CreateObject(kOpenFileDialogBoss, IID_IOPENFILEDIALOG));

	PMString title("$$$/Dialog/Behaviors/GoToAnchor/InDesign Format File"); 
	title.Translate();
	
	PMString family = "$$$/Dialog/Behaviors/GoToAnchor/InDesign Format File"; family.Translate();
	PMString ext("indd");
	openFileDialog->AddExtension(&family, &ext);

	LoadFromUserPlatformSettings(openFileDialog);
	
	SysFileList files;
	bool filePicked = false;
			
	if (openFileDialog->DoDialog(nil, files, kFalse, &title))
	{
		sysFile = *files.GetNthFile(0);
		filePicked = true;
	}
	
	return filePicked;
}


//----------------------------------------------------------------------------------------
// GoToAnchorDocumentObserver::LoadFromUserPlatformSettings
//----------------------------------------------------------------------------------------
void GoToAnchorDocumentObserver::LoadFromUserPlatformSettings(IOpenFileDialog* dialog) const
{
#if defined MACINTOSH
	dialog->AddType(fType);
#endif
}

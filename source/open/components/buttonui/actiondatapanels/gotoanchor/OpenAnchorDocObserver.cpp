//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/gotoanchor/OpenAnchorDocObserver.cpp $
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

#include "IApplication.h"
#include "ICommand.h"
#include "IControlView.h"
#include "IDocument.h"
#include "IDocumentCommands.h"
#include "IDocumentList.h"
#include "IDocumentUtils.h"
#include "IDropDownListController.h"
#include "IOpenFileCmdData.h"
#include "IOpenFileDialog.h"
#include "IPMStream.h"
#include "IRecoveryList.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "ISysFileData.h"
#include "IUIFlagData.h"
#include "IWidgetUtils.h"


#include "IAnchorFileListData.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "BehaviorUIDefs.h"
#include "CmdUtils.h"
#include "CreateObject.h"
#include "CWidgetObserver.h"
#include "ErrorUtils.h"
#include "FileUtility.h"
#include "FileUtils.h"
#include "OpenPlaceID.h"
#include "SysFileList.h"
#include "Utils.h"
#include "UIDList.h"
#include "widgetid.h"

//========================================================================================
// CLASS OpenAnchorDocObserver
//========================================================================================

class OpenAnchorDocObserver : public CWidgetObserver
{
public:
	OpenAnchorDocObserver(IPMUnknown *boss);
	virtual ~OpenAnchorDocObserver();
	
	virtual void	ReadWrite(IPMStream* s, ImplementationID prop);

	virtual void 	AutoAttach();
	virtual void 	AutoDetach();
	virtual void 	Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);

private:
	bool			GetFileToImportFromUser(IDFile& sysFile) const;
	void			LoadFromUserPlatformSettings(IOpenFileDialog* dialog) const;

private:
	OSType			fCreator;
	OSType			fType;
};

//========================================================================================
// METHODS OpenAnchorDocObserver
//========================================================================================

CREATE_PERSIST_PMINTERFACE(OpenAnchorDocObserver, kOpenAnchorDocObserverImpl)

//----------------------------------------------------------------------------------------
// SelectFileObserver constructor 
//----------------------------------------------------------------------------------------

OpenAnchorDocObserver::OpenAnchorDocObserver(IPMUnknown *boss) :
	CWidgetObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// OpenAnchorDocObserver::~OpenAnchorDocObserver
//----------------------------------------------------------------------------------------

OpenAnchorDocObserver::~OpenAnchorDocObserver()
{
}

//----------------------------------------------------------------------------------------
// OpenAnchorDocObserver::AutoAttach
//----------------------------------------------------------------------------------------

void OpenAnchorDocObserver::AutoAttach()
{
	CWidgetObserver::AutoAttach();
	AttachToWidget(kSelectFileIconWidgetID, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// OpenAnchorDocObserver::AutoDetach
//----------------------------------------------------------------------------------------

void OpenAnchorDocObserver::AutoDetach()
{
	CWidgetObserver::AutoDetach();
	DetachFromWidget(kSelectFileIconWidgetID, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// OpenAnchorDocObserver::ReadWrite
//----------------------------------------------------------------------------------------

void OpenAnchorDocObserver::ReadWrite(IPMStream* s, ImplementationID prop)
{
	s->XferInt32((int32&) fCreator);
	s->XferInt32((int32&) fType);
}

//----------------------------------------------------------------------------------------
// OpenAnchorDocObserver::Update
//----------------------------------------------------------------------------------------

void OpenAnchorDocObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	if (theChange == kTrueStateMessage)	
	{
		IDFile file;
		
		if (GetFileToImportFromUser(file))
		{
			//FileUtility fileUtility(file);
			
				// Get access to the open document list
			InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
			InterfacePtr<IDocumentList> docList(app->QueryDocumentList());
			
				// Get access to the drop down list
			InterfacePtr<IDropDownListController> documentChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kAnchorDocumentChoicesWidgetID, IID_IDROPDOWNLISTCONTROLLER));
			InterfacePtr<IStringListControlData> openDocData(documentChoice, IID_ISTRINGLISTCONTROLDATA);
			
				// Get the associated data list for the document choice drop down
			InterfacePtr<IAnchorFileListData> anchorFileData(documentChoice, IID_IANCHORFILEDATA);
			K2Vector<IAnchorFileListData::AnchorFileData> theAnchorFileList = anchorFileData->GetAnchorFileData();
			
			PMString path(FileUtils::SysFileToPMString( file ));
			
			int32 fileIndex = 0L;
			for ( K2Vector<IAnchorFileListData::AnchorFileData>::const_iterator iter = theAnchorFileList.begin(); iter != theAnchorFileList.end(); ++iter )
			{
				if ( iter->GetSysFile() == path )
				{
					documentChoice->Select( fileIndex );
					return;
				}
				++fileIndex;
			}
			
			InterfacePtr<ICommand> openDocCmd(Utils<IDocumentCommands>()->CreateOpenCommand(file, kSuppressUI, IOpenFileCmdData::kOpenOriginal, IOpenFileCmdData::kUseLockFile, kFalse));

			CmdUtils::ProcessCommand(openDocCmd);

			if (ErrorUtils::PMGetGlobalErrorCode() == kSuccess)
			{
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
						// File was converted. Tell user to open doc and save it in order to use it.
						if ( Utils<IDocumentUtils>()->DoSaveAs(thisDoc) == kSuccess )
						{
							docSysFile = thisDoc->GetDocWorkSpace().GetDataBase()->GetSysFile();
							thisDoc->GetName(addName);
						}
					}

					if ( !docSysFile )
					{
						InterfacePtr<ICommand> closeDocCmd(Utils<IDocumentCommands>()->CreateCloseCommand(cmdList->GetRef(0), kSuppressUI));
						CmdUtils::ScheduleCommand(closeDocCmd);
						return;
					}
						
					// remove the document from the recovery list
					InterfacePtr<IRecoveryList> recList(GetExecutionContextSession(), IID_IRECOVERYLIST);
					if ( recList )
						recList->RemoveDocument(thisDoc);

					theAnchorFileList.push_back(IAnchorFileListData::AnchorFileData( FileUtils::SysFileToPMString( *docSysFile ), addName)); 
					anchorFileData->SetAnchorFileData( theAnchorFileList);

						// Add the display string to the drop down
					openDocData->AddString( addName );
					int32 selectMe = openDocData->GetIndex( addName );
					documentChoice->Select( selectMe );
				}

			}
		}
	}
}

//----------------------------------------------------------------------------------------
// OpenAnchorDocObserver::GetFileToImportFromUser
//----------------------------------------------------------------------------------------

bool OpenAnchorDocObserver::GetFileToImportFromUser(IDFile& sysFile) const
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
// OpenAnchorDocObserver::LoadFromUserPlatformSettings
//----------------------------------------------------------------------------------------
void OpenAnchorDocObserver::LoadFromUserPlatformSettings(IOpenFileDialog* dialog) const
{
#if defined MACINTOSH
	dialog->AddType(fType);
#endif
}

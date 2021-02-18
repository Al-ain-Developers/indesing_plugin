//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/openfile/OpenFileBrowseObserver.cpp $
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

#include "IOpenFileDialog.h"
#include "IPMStream.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "widgetid.h"
#include "BehaviorUIDefs.h"
#include "CWidgetObserver.h"
#include "CreateObject.h"
#include "SysFileList.h"
#include "FileUtility.h"
#include "FileTypeRegistry.h"

//========================================================================================
// CLASS OpenFileBrowseObserver
//========================================================================================

class OpenFileBrowseObserver : public CWidgetObserver
{
public:
	OpenFileBrowseObserver(IPMUnknown *boss);
	virtual ~OpenFileBrowseObserver();
	
	virtual void 		ReadWrite(IPMStream* s, ImplementationID prop);
	
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
// METHODS SelectFileObserver
//========================================================================================

CREATE_PERSIST_PMINTERFACE(OpenFileBrowseObserver, kOpenFileBrowseObserverImpl)

//----------------------------------------------------------------------------------------
// OpenFileBrowseObserver constructor 
//----------------------------------------------------------------------------------------

OpenFileBrowseObserver::OpenFileBrowseObserver(IPMUnknown *boss) :
	CWidgetObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// OpenFileBrowseObserver::~OpenFileBrowseObserver
//----------------------------------------------------------------------------------------

OpenFileBrowseObserver::~OpenFileBrowseObserver()
{
}

//----------------------------------------------------------------------------------------
// OpenFileBrowseObserver::ReadWrite
//----------------------------------------------------------------------------------------

void OpenFileBrowseObserver::ReadWrite(IPMStream* s, ImplementationID prop)
{
	s->XferInt32((int32&) fCreator);
	s->XferInt32((int32&) fType);
}

//----------------------------------------------------------------------------------------
// OpenFileBrowseObserver::AutoAttach
//----------------------------------------------------------------------------------------

void OpenFileBrowseObserver::AutoAttach()
{
	CWidgetObserver::AutoAttach();
	AttachToWidget(kSelectFileIconWidgetID, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// OpenFileBrowseObserver::AutoDetach
//----------------------------------------------------------------------------------------

void OpenFileBrowseObserver::AutoDetach()
{
	CWidgetObserver::AutoDetach();
	DetachFromWidget(kSelectFileIconWidgetID, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// OpenFileBrowseObserver::Update
//----------------------------------------------------------------------------------------

void OpenFileBrowseObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	if (theChange == kTrueStateMessage)	
	{
		IDFile file;
		
		if (GetFileToImportFromUser(file))
		{
			FileUtility fileUtility(file);
			
			PMString pathName;
			fileUtility.GetPathName(&pathName);
			SetTextControlData(kSelectFileWidgetID, pathName);
		}
	}
}

//----------------------------------------------------------------------------------------
// OpenFileBrowseObserver::GetFileToLoadFromUser
//----------------------------------------------------------------------------------------

bool OpenFileBrowseObserver::GetFileToImportFromUser(IDFile& sysFile) const
{
	InterfacePtr<IOpenFileDialog> openFileDialog((IOpenFileDialog*)::CreateObject(kOpenFileDialogBoss, IID_IOPENFILEDIALOG));

	PMString title("$$$/Dialog/Behaviors/OpenFile/Select File to be Opened"); 
	title.Translate();
	
	//PMString family = "$$$/Dialog/Behaviors/OpenFile/Acrobat Format File"; family.Translate();
	//PMString ext("pdf");
	//openFileDialog->AddExtension(&family, &ext);

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

#if defined MACINTOSH
//----------------------------------------------------------------------------------------
// OpenFileBrowseObserver::LoadFromUserPlatformSettings
//----------------------------------------------------------------------------------------

void OpenFileBrowseObserver::LoadFromUserPlatformSettings(IOpenFileDialog* dialog) const
{
	dialog->AddType(fType);

	PMString pdfDocuments("$$$/Dialog/Behaviors/OpenFile/Acrobat Format File"); pdfDocuments.Translate();
	dialog->AddCustomMenu(pdfDocuments, fType);
	PMString readableDocuments("All Documents"); readableDocuments.Translate();
	dialog->AddCustomMenu(readableDocuments, kAllFileTypes);
}
#endif

#if defined WINDOWS
//----------------------------------------------------------------------------------------
// OpenFileBrowseObserver::LoadFromUserPlatformSettings
//----------------------------------------------------------------------------------------

void OpenFileBrowseObserver::LoadFromUserPlatformSettings(IOpenFileDialog* dialog) const
{
	dialog->AppendAllFilesToFilterList();
}
#endif

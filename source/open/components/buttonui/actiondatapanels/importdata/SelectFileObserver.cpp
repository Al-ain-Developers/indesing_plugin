//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/importdata/SelectFileObserver.cpp $
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

//========================================================================================
// CLASS SelectFileObserver
//========================================================================================

class SelectFileObserver : public CWidgetObserver
{
public:
	SelectFileObserver(IPMUnknown *boss);
	virtual ~SelectFileObserver();
	
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

CREATE_PERSIST_PMINTERFACE(SelectFileObserver, kSelectFileObserverImpl)

//----------------------------------------------------------------------------------------
// SelectFileObserver constructor 
//----------------------------------------------------------------------------------------

SelectFileObserver::SelectFileObserver(IPMUnknown *boss) :
	CWidgetObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// SelectFileObserver::~SelectFileObserver
//----------------------------------------------------------------------------------------

SelectFileObserver::~SelectFileObserver()
{
}

//----------------------------------------------------------------------------------------
// SelectFileObserver::ReadWrite
//----------------------------------------------------------------------------------------

void SelectFileObserver::ReadWrite(IPMStream* s, ImplementationID prop)
{
	s->XferInt32((int32&) fCreator);
	s->XferInt32((int32&) fType);
}

//----------------------------------------------------------------------------------------
// SelectFileObserver::AutoAttach
//----------------------------------------------------------------------------------------

void SelectFileObserver::AutoAttach()
{
	CWidgetObserver::AutoAttach();
	AttachToWidget(kSelectFileIconWidgetID, IID_IBOOLEANCONTROLDATA);
}

//----------------------------------------------------------------------------------------
// SelectFileObserver::AutoDetach
//----------------------------------------------------------------------------------------

void SelectFileObserver::AutoDetach()
{
	CWidgetObserver::AutoDetach();
	DetachFromWidget(kSelectFileIconWidgetID, IID_IBOOLEANCONTROLDATA);
}

//----------------------------------------------------------------------------------------
// SelectFileObserver::Update
//----------------------------------------------------------------------------------------

void SelectFileObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
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
// SelectFileObserver::GetFileToLoadFromUser
//----------------------------------------------------------------------------------------

bool SelectFileObserver::GetFileToImportFromUser(IDFile& sysFile) const
{
	InterfacePtr<IOpenFileDialog> openFileDialog((IOpenFileDialog*)::CreateObject(kOpenFileDialogBoss, IID_IOPENFILEDIALOG));

	PMString title("$$$/Dialog/Behaviors/ImportData/Acrobat Format File"); 
	title.Translate();
	
	PMString family = "$$$/Dialog/Behaviors/ImportData/Acrobat Format File"; family.Translate();
	PMString ext("pdf");
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

#if defined MACINTOSH
//----------------------------------------------------------------------------------------
// SelectFileObserver::LoadFromUserPlatformSettings
//----------------------------------------------------------------------------------------

void SelectFileObserver::LoadFromUserPlatformSettings(IOpenFileDialog* dialog) const
{
	dialog->AddType(fType);
	dialog->SetNavDlgOpFlags(kNavDontAddTranslateItems | kNavDontAutoTranslate);
}
#endif

#if defined WINDOWS
//----------------------------------------------------------------------------------------
// SelectFileObserver::LoadFromUserPlatformSettings
//----------------------------------------------------------------------------------------

void SelectFileObserver::LoadFromUserPlatformSettings(IOpenFileDialog* dialog) const
{
	dialog->SetAdditionalOFNFlags(OFN_HIDEREADONLY);
}
#endif

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/OpenProblemLinksDialogCmd.cpp $
//  
//  Owner: lance bushore
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
#include "IDialogMgr.h"
#include "IDocument.h"
#include "IIntData.h"
#include "IPanelMgr.h"
#include "ISession.h"
#include "IUIDData.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "Command.h"
#include "CoreResTypes.h"
#include "LocaleSetting.h"

#include "RsrcSpec.h"
#include "DBUtils.h"
// ----- Utility files -----

#include "ILayoutUIUtils.h"

// ----- ID.h files -----

#include "LinksUIID.h"

class OpenProblemLinksDialogCmd : public Command
{
	public:
		OpenProblemLinksDialogCmd(IPMUnknown *boss) : Command(boss)
			{
			SetTarget(kSessionTarget);
			SetUndoability(ICommand::kAutoUndo); 
			}

		virtual void Do();
};



CREATE_PMINTERFACE(OpenProblemLinksDialogCmd, kOpenProblemLinksDialogCmdImpl)


void OpenProblemLinksDialogCmd::Do()
{
	// This command is scheduled and it is possible that the problem document was never
	// completely opened (cancel from color profile dialog).  
	// Check that the document is open and if not, we are done.
	InterfacePtr<IUIDData> docRef(this, IID_IUIDDATA);
	if (!docRef)
		return;
		
	// this command gets scheduled at doc open time. If the user cancels the open after this cmd gets scheduled, 
	// we'll still get called to run, even though the DB we care about is gone.	
	if(!DBUtils::IsValidDataBase(docRef->GetItemDataBase()))
	{
		TRACE("OpenProblemLinksDialogCmd bailing - my DB seems to be gone\n");
		return; 
	}
	
	InterfacePtr<IDocument> document(docRef->GetRef(), IID_IDOCUMENT);
	if (!document)
		return;

#if 0
	// The document interface will exist even when the open has been canceled because
	// the close is scheduled to happen soon.  We look to see whether there are any open
	// views on the document to see whether it has really been open.
	InterfacePtr<IPresentationList> docPList (document, UseDefaultIID());
	if (docPList->size() == 0)
		return;

	// Only show the dialog for the front document.
	IDocument *frontDocument = Utils<ILayoutUIUtils>()->GetFrontDocument();
	if (frontDocument != document)
		return;
#endif

	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IDialogMgr> dm(app, IID_IDIALOGMGR);
	
	IDialog* dialog = dm->CreateNewDialog(RsrcSpec(LocaleSetting::GetLocale(), 
		kLinksUIPluginID, kViewRsrcType, kProblemLinksDialogResID), IDialog::kMovableModal);
	IControlView* dialogView = dialog->GetDialogPanel();

	// Copy settings from command to dialog so it can use them.
	InterfacePtr<IIntData> missingCount(this, IID_IMISSINGCOUNT);
	InterfacePtr<IIntData> outofdateCount(this, IID_IOUTOFDATECOUNT);
	InterfacePtr<IIntData> inaccessibleCount(this, IID_IINACCESSIBLECOUNT);
	InterfacePtr<IBoolData> isHTTPLink(this, IID_IHTTPLINKS);
	
	InterfacePtr<IIntData> missing(dialogView, IID_IMISSINGCOUNT);
	missing->Set(missingCount->GetInt());
	InterfacePtr<IIntData> outofdate(dialogView, IID_IOUTOFDATECOUNT);
	outofdate->Set(outofdateCount->GetInt());
	InterfacePtr<IIntData> inaccessible(dialogView, IID_IINACCESSIBLECOUNT);
	inaccessible->Set(inaccessibleCount->GetInt());
	InterfacePtr<IBoolData> isHTTP(dialogView, IID_IHTTPLINKS);
	isHTTP->Set(isHTTPLink->GetBool());

	// Only display the Links panel automatically if there are links out of date
	// If there are missing links, then the user can
	// click on the "Fix Links..." button and the Links panel will then open.
	if ( outofdateCount->GetInt() != 0 || inaccessibleCount->GetInt() != 0)
	{
		InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
		InterfacePtr<IPanelMgr>	panelMgr( theApp->QueryPanelManager() );
		panelMgr->ShowPanelByWidgetID(kLinksUIPanelWidgetID);
	}

	dialog->Open();

	// See ProblemLinksDialogObserver.cpp for the dialog processing code.

	// BP 02/26/03: #579130 Package for web fails to warn the user when there are broken links.
	// 		Package4WebUtils::CheckAndFixLinks() uses this command too. But it needs 
	//		OpenProblemLinksDialogCmd to wait for the dialog.
	InterfacePtr<IBoolData>waitForDialog( this, UseDefaultIID() );
	if( waitForDialog && waitForDialog->Get() )
		dialog->WaitForDialog();

	InterfacePtr<IBoolData> fixLinksSelected(dialogView, IID_IFIXLINKSSELECTED);
	InterfacePtr<IBoolData> fixLinks(this, IID_IFIXLINKS);
	fixLinks->Set(fixLinksSelected->Get());
}

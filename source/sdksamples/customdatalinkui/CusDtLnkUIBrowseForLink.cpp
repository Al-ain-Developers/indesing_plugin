//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalinkui/CusDtLnkUIBrowseForLink.cpp $
//  
//  Owner: Adobe Developer Technologies
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

// Interface includes:
#include "ISession.h"
#include "IApplication.h"
#include "IDialogMgr.h"
#include "IDialog.h"

#include "IStringData.h"
#include "IBrowseForLink.h"
#include "ICusDtLnkFacade.h"
#include "IDatalink.h"
#include "IWorkspace.h"

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"
#include "CoreResTypes.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"
#include "SDKFileHelper.h"
#include "NAMEINFO.H"
#include "Utils.h"
// Proj
#include "CusDtLnkUIID.h"

/** Implementation of IBrowseForLink.

*/
class CusDtLnkUIBrowseForLink: public CPMUnknown<IBrowseForLink> 
{
public:
	/** Constructor 
		@param boss object on which this impl aggregated
	*/
	CusDtLnkUIBrowseForLink(IPMUnknown* boss);
	/** Destructor */
	virtual ~CusDtLnkUIBrowseForLink();

	/** @see IBrowseForLink::Browse */
	virtual IDataLink *  Browse (IDataLink *dl, bool16 bShowRelinkAll = kFalse);

private:
	IDataLink* doCustomBrowseDialog(IDataLink* dl);

};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(CusDtLnkUIBrowseForLink, kCusDtLnkUIBrowseForLinkImpl)
/* Constructor
*/
CusDtLnkUIBrowseForLink::CusDtLnkUIBrowseForLink(IPMUnknown* boss) : 
	CPMUnknown<IBrowseForLink>(boss)
{
}



	
/* Destructor
*/
CusDtLnkUIBrowseForLink::~CusDtLnkUIBrowseForLink()
{
}


IDataLink *  CusDtLnkUIBrowseForLink::Browse (IDataLink *dl, bool16 bShowRelinkAll)
{
	// Always show dialog. We could try to use the information 
	// in the datalink passed in, but that's left for later.
	IDataLink* retval =  this->doCustomBrowseDialog(dl);
	
	return retval;
}

/* 
*/
IDataLink* CusDtLnkUIBrowseForLink::doCustomBrowseDialog(IDataLink* dl)
{
	IDataLink* retval = nil;
	do
	{
		ASSERT(dl);
		if(!dl) {
			break;
		}
		NameInfo ni;
		PMString formatName;
		uint32 filetype;

		// Create a filename from the link. {
		if (dl->GetNameInfo(&ni, &formatName, &filetype)) {
			break; // Unable to get name info.
		}

		InterfacePtr<IApplication> application(GetExecutionContextSession()->QueryApplication());
		InterfacePtr<IDialogMgr> dialogMgr(application, UseDefaultIID());
		ASSERT(dialogMgr);
		if (!dialogMgr) { 
			break;
		}
		PMLocaleId nLocale = LocaleSetting::GetLocale();
		RsrcSpec dialogSpec
		(
			nLocale,					// Locale index from PMLocaleIDs.h. 
			kCusDtLnkUIPluginID,			// Our Plug-in ID from BasicDialogID.h. 
			kViewRsrcType,				// This is the kViewRsrcType.
			kCusDtLnkUIBrowsDialogResourceID,	// Resource ID for our dialog.
			kTrue						// Initially visible.
		);

		IDialog* dialog = dialogMgr->CreateNewDialog(dialogSpec, IDialog::kMovableModal);
		ASSERT(dialog);
		if (!dialog) { 
			break;
		}
		dialog->Open(); 
		// BLOCK till dialog done
		dialog->WaitForDialog();
	
		Utils<ICusDtLnkFacade> facade;
		ASSERT(facade);
		if(!facade) {
			break;
		}

		IDataBase* db = ::GetDataBase(dl);
		InterfacePtr<IDocument> doc(db, db->GetRootUID(), UseDefaultIID());
		InterfacePtr<IWorkspace> ws(doc->GetDocWorkSpace(), UseDefaultIID());

		PMString uniqueAssetKey = facade->GetCurrentlyChosenUniqueAssetKey(ws);
		IDFile localFile = facade->GetLocalFileFromAssetIdentifier(ws, uniqueAssetKey);
		SDKFileHelper fileHelper(localFile);
		if(!fileHelper.IsExisting()) {
			break;
		}
		
		
		InterfacePtr<IDataLink> tempDataLink( 
				::CreateObject2<IDataLink>(kCusDtLnkAliasedDataLinkBoss) );
		if (!tempDataLink) {
			break;
		}
		// Create one of our custom datalinks
		ErrorCode err = facade->InitializeDataLink(ws, tempDataLink, 
												localFile, 
												formatName, 
												uniqueAssetKey);
		ASSERT(err == kSuccess);
		retval = tempDataLink.forget();
		PMString emptyStr("");
		facade->SetCurrentlyChosenUniqueAssetKey(ws, emptyStr);
	} while (false);	

	return retval;
}



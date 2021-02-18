//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyfileactions/FileActionsOpenDocResponder.cpp $
//  
//  Owner: cparrish
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
//  A responder to handle special actions when a doc is opened in InCopy
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

// ----- Interfaces -----

#include "IApplication.h"
#include "IBoolData.h"
#include "IClassIDData.h"
#include "IDocument.h"
#include "IDocumentCommands.h"
#include "IDocumentList.h"
#include "IDocumentSignalData.h"
#include "IInCopyImportOptions.h"
#include "IINXManager.h"
#include "IObserver.h"
#include "IOpenFileCmdData.h"
#include "isignalmgr.h"
#include "IStandAloneDoc.h"
#include "IStringData.h"
#include "IStoryList.h"
#include "ITextModel.h"
#include "IUsedFontList.h"

// ----- Includes -----

#include "CAlert.h"
#include "CResponder.h"
#include "FileTypeRegistry.h"
#include "OpenPlaceID.h"
#include "UIDList.h"

// ----- Utils -----

#include "FileUtils.h"
#include "IINXInfo.h"
#include "IInCopyDocUtils.h"
#include "ITLAdornmentUtils.h"
#include "Utils.h"

// ----- ID.h files -----

#include "InCopyFileActionsID.h"
#include "GenericID.h"
#include "XPID.h"


//======================================================================================
// CLASS : FileActionsOpenDocResponder
//======================================================================================

class FileActionsOpenDocResponder : public CResponder
{
	public:
	
		FileActionsOpenDocResponder(IPMUnknown *boss) :
			CResponder(boss) {}

		virtual void Respond(ISignalMgr* signalMgr);
};

CREATE_PMINTERFACE(FileActionsOpenDocResponder, kFileActionsOpenDocResponderImpl)

//-------------------------------------------------------------------------------------

void FileActionsOpenDocResponder::Respond(ISignalMgr* signalMgr)
{
	InterfacePtr<IDocumentSignalData> data(signalMgr, UseDefaultIID());
	if ( Utils<IINXInfo>()->IsINXContextActive() || data->GetDocumentClone() )
	{
		// INX is active, don't allow update of InCopy stories at this time as it would cause
		// re-entry in the INX core and would fail, bug 1439986.
		return;
	}

	IAbortableCmdSeq *seq = CMDUTILS_BEGINABORTABLECMDSEQ(__FILE__,__LINE__);

	InterfacePtr<IDocument>	doc(data->GetDocument(), IID_IDOCUMENT);
	IDFile whatFile = data->GetFile();
	
	IDataBase* db = ::GetDataBase(doc);
	bool16 wasModified = db->IsModified();
	
	//----- Install our doc file handler
	InterfacePtr<IClassIDData> docFileHandlerData(doc, IID_ICLASSIDDATA);
	docFileHandlerData->Set(kInCopyDocFileHandlerBoss);
	
	//----- Make sure that the WFOpenDocResponder gets a chance to go first.
//	signalMgr->SignalResponder(kWFOpenDocResponderBoss);
		
	//----- Handle importing linked incopy stories
	
	//----- Only care about InDesign or Design docs, ie not stand alone
	//      and only if the doc is not recovered. We don't want to blow
	//      away recovered data with a reimport.
	InterfacePtr<IStandAloneDoc> standAlone(doc, IID_ISTANDALONEDOC);
	ICommand* whichCmd = data->GetCommand();
	if (standAlone && !Utils<IDocumentCommands>()->IsRecoverCommand(::GetClass(whichCmd))) {
		if (!standAlone->IsStandAloneDoc()) {
			// Hook up the transparency observer - it is possible that the InDesign pub's
			// transparency cache is out of date compared to the InCopy story; normally this
			// observer is attached on notification of open but that is too late to notice
			// hierarchy changes due to importing of InCopy stories which happens via this
			// responder.  Hooking up the observer now will allow these changes to be processed
			// and the cache brought up to date.
			InterfacePtr<IApplication>	theApp(GetExecutionContextSession()->QueryApplication());
			InterfacePtr<IObserver> xpObserver(theApp, IID_IXPDOCOBSERVER);
			if (xpObserver)
				xpObserver->AutoAttach();

			/* Set the import to import the style table and swatch list just in case they are more recent than the pub. */
			InterfacePtr<IInCopyImportOptions> options(
				(IInCopyImportOptions*)::CreateObject(kInCopyImportOptionsBoss, IID_IINCOPYIMPORTOPTIONS)
				);
			options->Set(kTrue, kTrue);

			// Tell INX Manager that the import is happening because of open operation so
			// it will pay attention to the user preference for Find Missing Links Before 
			// Opening Document for the import of InCopy linked stories.
			InterfacePtr<IINXManager> iINXManager(GetExecutionContextSession()->QueryINXManager());
			InterfacePtr<IBoolData> importIsFromOpen(iINXManager, UseDefaultIID());
			if (importIsFromOpen) importIsFromOpen->Set(kTrue);

			FileTypeInfoID fileTypeInfo = FileTypeRegistry::GetFileTypeInfoIDForFile(whatFile);
			Utils<IInCopyDocUtils>()->ImportAllLinkedStories(doc, fileTypeInfo, options);

			if (importIsFromOpen) importIsFromOpen->Set(kFalse);

			if (ErrorUtils::PMGetGlobalErrorCode() == kCancel)
			{
				// User cancelled so abort the open operation.
				CmdUtils::AbortCommandSequence(seq);

				//----- We clear the pub modified flag here so the imports above do 
				//      not leave the doc modified, only if the pub was not modified before
				//      we were called
				if (!wasModified)
					db->SetModified(kFalse);
				return;
			}

			/** 
			BP 06/18/03: #617292 ALPHABLOCKER: No Local Replica Created for Linked InCopy Stories Within InDesign Files Upon Checkout
			IInCopyDocUtils::ImportAllLinkedStories() doesn't return an error code but it sets the global error state.
			Errors can occur if the file is missing:
			InCopyDocUtils::ImportAllLinkedStories()
			InCopyDocUtils::ImportLinkedStory()
			InCopy::InCopyWorkflow::ImportStory()
			InCopy::Workflow::_ImportStory()
			Sets global error state because IPMStream is nil
			It seems like the rest of the code is robust enough to handle this problem.
			Resetting the error state to kSuccess should be fine.
			*/
			if( ErrorUtils::PMGetGlobalErrorCode() != kSuccess )
			{
				// hkhalfal: (NACSR) No abortable command sequence is used
				// changes will not be reverted in case of error
				ErrorUtils::PMSetGlobalErrorCode( kSuccess );
			}
		}
	}
	
	//----- Lock the non-incopy stories
	Utils<IInCopyDocUtils>()->LockNonInCopyStories(::GetUIDRef(doc));

	//----- Force an update of the missing fonts so that locked stories are excluded from the 
	//      the check for misisng fonts.
	InterfacePtr<IUsedFontList>	fonts(doc, IID_IUSEDFONTLIST);
	fonts->ForceRecalculateAll();

	//----- End and commit the abortable command sequence.
	CmdUtils::EndCommandSequence(seq);
	
	//----- We clear the pub modified flag here so the imports above do 
	//      not leave the doc modified, only if the pub was not modified before
	//      we were called
	if (!wasModified)
		db->SetModified(kFalse);
		
}
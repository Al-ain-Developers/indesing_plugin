//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/DynamicSpellCheckObserver.cpp $
//  
//  Owner: heath horton
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

#include "IApplication.h"
#include "ICommand.h"
#include "IDocument.h"
#include "IDocumentSignalData.h"
#include "IDynamicSpellCheckCache.h"
#include "IEventWatcher.h"
#include "IGalleyUtils.h"
#include "IGlobalTextAdornment.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILayoutController.h"
#include "IPanelControlData.h"
#include "isignalmgr.h"
#include "ISpellingPrefs.h"
#include "ISpellingUtils.h"
#include "IPrivateSpellingUtils.h"
#include "ISubject.h"
#include "ITextLines.h"
#include "ITextEditor.h"
#include "IDocumentPresentation.h"
#include "IWorkspace.h"
#include "IFrameList.h"
#include "ITextModel.h"
#include "IWaxIterator.h"
#include "IWaxLine.h"
#include "IWaxRun.h"
#include "IWaxRunIterator.h"
#include "IWaxStrand.h"

#include "K2SmartPtr.h"
#include "CObserver.h"
#include "CResponder.h"
#include "PreferenceUtils.h"
#include "PMTextUtils.h"
#include "SpellPanelID.h"
#include "TextID.h"
#include "Utils.h"
#include "WritingModeID.h"

	// from SpellIgnoreObserver.cpp
ITextEditor* QueryTextEditor( IDocumentPresentation *pWindow );



class DynamicSpellCheckObserver : public CObserver
{
public:
	DynamicSpellCheckObserver(IPMUnknown *boss);
	
	virtual void AutoAttach();
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy) {};
	virtual void LazyUpdate(ISubject* theSubject, const PMIID& protocol, const LazyNotificationData* );

private:
	IEventWatcher* fKeyEventWatcher;
};

CREATE_PMINTERFACE(DynamicSpellCheckObserver, kDynamicSpellCheckObserverImpl)

DynamicSpellCheckObserver::DynamicSpellCheckObserver(IPMUnknown *boss) :
	CObserver(boss),
		fKeyEventWatcher(nil)
{
	TRACEFLOW_OBSOLETE("DSC", "DynamicSpellCheckObserver::DynamicSpellCheckObserver\n");
}

void DynamicSpellCheckObserver::AutoAttach()
{
	// spelling prefs (dsc really)
	InterfacePtr<IWorkspace> appWorkSpace(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<ISubject> appSubject(appWorkSpace, IID_ISUBJECT);
	if (appSubject && !appSubject->IsAttached(ISubject::kLazyAttachment,this, IID_ISPELLINGPREFS, IID_IOBSERVER))
		appSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_ISPELLINGPREFS, IID_IOBSERVER);
	
	if (appSubject && !appSubject->IsAttached(ISubject::kLazyAttachment,this, IID_ISPELLPANELOPTIONS, IID_IOBSERVER))
		appSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_ISPELLPANELOPTIONS, IID_IOBSERVER);
		
	/* create the event watcher */
	InterfacePtr<ISpellingPrefs> spellingPrefs((ISpellingPrefs*)::QuerySessionPreferences(IID_ISPELLINGPREFS));
	if (spellingPrefs)
	{
		bool16 dsc = spellingPrefs->GetDynamicSpellCheck();

		/* tell the event watcher on the spellcheck adorment to start/stop watching */
		//InterfacePtr<IEventWatcher> keyEventWatcher(this, UseDefaultIID());
		fKeyEventWatcher = ::CreateObject2<IEventWatcher>(kDynamicSpellCheckThreadBoss);
		TRACEFLOW_OBSOLETE("DSC", "Creating EventWatcher\n");
		
		if (fKeyEventWatcher)
		{
			if (dsc)
				fKeyEventWatcher->StartWatching();
			else
				fKeyEventWatcher->StopWatching();
		}
	}

}

void DynamicSpellCheckObserver::AutoDetach()
{
	InterfacePtr<IWorkspace> appWorkSpace(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<ISubject> appSubject(appWorkSpace, IID_ISUBJECT);
	if (appSubject && appSubject->IsAttached(ISubject::kLazyAttachment,this, IID_ISPELLINGPREFS, IID_IOBSERVER))
		appSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_ISPELLINGPREFS, IID_IOBSERVER);
	
	if (appSubject && appSubject->IsAttached(ISubject::kLazyAttachment,this, IID_ISPELLPANELOPTIONS, IID_IOBSERVER))
		appSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_ISPELLPANELOPTIONS, IID_IOBSERVER);

	if (fKeyEventWatcher)
	{
		fKeyEventWatcher->Release();
		fKeyEventWatcher = nil;
	}
}

void DynamicSpellCheckObserver::LazyUpdate(ISubject* theSubject, const PMIID& protocol, const LazyNotificationData* )
{
	switch(protocol.Get())
	{
		case IID_ISPELLPANELOPTIONS:
		{
			/* we modified the "ignored" list, got to inval the world currently */
			InterfacePtr<ISpellingPrefs> spellingPrefs((ISpellingPrefs*)::QuerySessionPreferences(IID_ISPELLINGPREFS));
			if (spellingPrefs)
			{
				bool16 dsc = spellingPrefs->GetDynamicSpellCheck();
				if (dsc)
					Utils<IPrivateSpellingUtils>()->DeleteCacheAndInvalAllDocWindows(kTrue);
			}
		}
		break;

		case IID_ISPELLINGPREFS:
		{
			InterfacePtr<ISpellingPrefs> spellingPrefs((ISpellingPrefs*)::QuerySessionPreferences(IID_ISPELLINGPREFS));	
			if( !spellingPrefs )
				return;
	
			bool16 dsc = spellingPrefs->GetDynamicSpellCheck();
			/* tell the event watcher to start/stop watching */
			//InterfacePtr<IEventWatcher> eventWatcher(this, UseDefaultIID());
			if (fKeyEventWatcher)
			{
				if (dsc)
					fKeyEventWatcher->StartWatching();
				else
					fKeyEventWatcher->StopWatching();
			}
			
			bool16 recheckAll = kFalse;
			if (dsc)
				recheckAll = kTrue;

			Utils<IPrivateSpellingUtils>()->DeleteCacheAndInvalAllDocWindows(recheckAll);	

		}
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

class DocumentDynamicSpellCheckObserver : public CObserver
{
public:
	DocumentDynamicSpellCheckObserver(IPMUnknown *boss);
	
	virtual void AutoAttach();
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
};

CREATE_PMINTERFACE(DocumentDynamicSpellCheckObserver, kDocumentDynamicSpellCheckObserverImpl)

DocumentDynamicSpellCheckObserver::DocumentDynamicSpellCheckObserver(IPMUnknown *boss) :
	CObserver(boss)
{
	TRACEFLOW_OBSOLETE("DSC", "DocumentDynamicSpellCheckObserver::DocumentDynamicSpellCheckObserver\n");
}

void DocumentDynamicSpellCheckObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	if (theChange == kSetHyphExceptionListCmdBoss || theChange == kSetHyphExceptionByLanguageCmdBoss)
	{
		/* we changed the hyphenation exceptions, inval all stories and views for the document */
		InterfacePtr<ISpellingPrefs> spellingPrefs((ISpellingPrefs*)::QuerySessionPreferences(IID_ISPELLINGPREFS));
		if (spellingPrefs)
		{
			bool16 dsc = spellingPrefs->GetDynamicSpellCheck();
			if (dsc)
			{
				InterfacePtr<IDocument>	document(theSubject, UseDefaultIID());
				if (document)
					Utils<IPrivateSpellingUtils>()->DeleteCacheAndInvalDocWindows(document, kTrue);
			}
		}
	}
}

void DocumentDynamicSpellCheckObserver::AutoAttach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject)
	{
		/* could get a new and open signal */
		if (!subject->IsAttached(this, IID_IHYPHENATIONEXCEPTIONS, IID_IDOCUMENTDSCOBSERVER))
			subject->AttachObserver(this, IID_IHYPHENATIONEXCEPTIONS, IID_IDOCUMENTDSCOBSERVER);
	}
}

void DocumentDynamicSpellCheckObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject)
		subject->DetachObserver(this, IID_IHYPHENATIONEXCEPTIONS, IID_IDOCUMENTDSCOBSERVER);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

class DynamicSpellCheckDocResponder : public CResponder
{
typedef CResponder inherited;

public:
    DynamicSpellCheckDocResponder(IPMUnknown *boss);

public:
    virtual void Respond(ISignalMgr *signalMgr);
};

CREATE_PMINTERFACE(DynamicSpellCheckDocResponder, kDynamicSpellCheckDocResponderImpl)

DynamicSpellCheckDocResponder::DynamicSpellCheckDocResponder(IPMUnknown *boss) :
    inherited(boss)
{
}

void DynamicSpellCheckDocResponder::Respond(ISignalMgr *signalMgr)
{
	ServiceID serviceID = signalMgr->GetServiceID();
	
	switch (serviceID.Get())
    {
        case kAfterNewDocSignalResponderService:
        case kAfterOpenDocSignalResponderService:
        case kBeforeCloseDocSignalResponderService:
		{
			InterfacePtr<IDocumentSignalData> signalData(signalMgr, UseDefaultIID());
			if (signalData == nil)
			{
				ASSERT_FAIL("Invalid IDocumentSignalData* - DynamicSpellCheckDocResponder::Respond");
				return;
			}
			UIDRef docRef = signalData->GetDocument();
			InterfacePtr<IObserver> docObserver(docRef, IID_IDOCUMENTDSCOBSERVER);
			if (docObserver != nil)
			{
				if (serviceID.Get() == kAfterNewDocSignalResponderService || serviceID.Get() == kAfterOpenDocSignalResponderService)
					docObserver->AutoAttach();
				else
					docObserver->AutoDetach();
            }
            break;
        }
    }
}

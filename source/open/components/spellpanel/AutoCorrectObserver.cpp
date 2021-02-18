//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectObserver.cpp $
//  
//  Owner: Heath Horton
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
#include "IAutoCorrectPrefs.h"
#include "IAutoCorrectUtils.h"
#include "ICommand.h"
#include "IEventWatcher.h"
#include "IGalleyUtils.h"
#include "IGlobalTextAdornment.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILayoutController.h"
#include "ILanguage.h"
#include "ILanguageList.h"
#include "IPanelControlData.h"
#include "ISpellingUtils.h"
#include "ISession.h"
#include "ISubject.h"
#include "ITextLines.h"
#include "ITextEditor.h"
#include "IWorkspace.h"
#include "IFrameList.h"
#include "ITextModel.h"
#include "IWaxIterator.h"
#include "IWaxLine.h"
#include "IWaxRun.h"
#include "IWaxRunIterator.h"
#include "IWaxStrand.h"
#include "IDocumentPresentation.h"

#include "FileUtility.h"
#include "K2SmartPtr.h"
#include "CObserver.h"
#include "PreferenceUtils.h"
#include "PMTextUtils.h"
#include "SpellPanelID.h"
#include "TextID.h"
#include "Utils.h"
#include "WritingModeID.h"


	// from SpellIgnoreObserver.cpp
ITextEditor* QueryTextEditor( IDocumentPresentation *pWindow );



class AutoCorrectObserver : public CObserver
{
public:
	AutoCorrectObserver(IPMUnknown *boss);
	
	virtual void AutoAttach();
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy){};
	virtual void LazyUpdate(ISubject* theSubject, const PMIID& protocol, const LazyNotificationData* );

private:
	IEventWatcher* fKeyEventWatcher;

			void ImportAllAutoCorrectFiles();

};

CREATE_PMINTERFACE(AutoCorrectObserver, kAutoCorrectObserverImpl)

AutoCorrectObserver::AutoCorrectObserver(IPMUnknown *boss) :
	CObserver(boss),
		fKeyEventWatcher(nil)
{
	TRACEFLOW("Autocorrect", "AutoCorrectObserver::AutoCorrectObserver\n");
}


void AutoCorrectObserver::AutoAttach()
{
	// spelling prefs (dcs really)
	InterfacePtr<IWorkspace> appWorkSpace(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<ISubject> appSubject(appWorkSpace, IID_ISUBJECT);
	if (appSubject && !appSubject->IsAttached(ISubject::kLazyAttachment,this, IID_IAUTOCORRECTPREFS, IID_IOBSERVER))
		appSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_IAUTOCORRECTPREFS, IID_IOBSERVER);

	/* create the event watcher */
	InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences(IID_IAUTOCORRECTPREFS));
	if (autoCorrectPrefs)
	{
		bool16 autoCorrect = autoCorrectPrefs->GetAutoCorrect();

		/* tell the event watcher on the spellcheck adorment to start/stop watching */
		//InterfacePtr<IEventWatcher> keyEventWatcher(this, UseDefaultIID());
		fKeyEventWatcher = ::CreateObject2<IEventWatcher>(kAutoCorrectTypingBoss);
		TRACEFLOW_OBSOLETE("AutoCorrect", "Creating EventWatcher\n");
		
		if (fKeyEventWatcher)
		{
			if (autoCorrect)
			{
				// will most likely make this an idle task which loads all the auto correct files, right now it hits startup time.
				//ImportAllAutoCorrectFiles();
				fKeyEventWatcher->StartWatching();
			}
			else
			{
				fKeyEventWatcher->StopWatching();
			}
		}
	}

}

void AutoCorrectObserver::AutoDetach()
{
	InterfacePtr<IWorkspace> appWorkSpace(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<ISubject> appSubject(appWorkSpace, IID_ISUBJECT);
	if (appSubject && appSubject->IsAttached(ISubject::kLazyAttachment,this, IID_IAUTOCORRECTPREFS, IID_IOBSERVER))
		appSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_IAUTOCORRECTPREFS, IID_IOBSERVER);
		
	if (fKeyEventWatcher)
	{
		fKeyEventWatcher->Release();
		fKeyEventWatcher = nil;
	}
}

void AutoCorrectObserver::LazyUpdate(ISubject* theSubject, const PMIID& protocol, const LazyNotificationData* )
{
	switch(protocol.Get())
	{
		case IID_IAUTOCORRECTPREFS:
		{
			InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences(IID_IAUTOCORRECTPREFS));	
			if( !autoCorrectPrefs )
				return;
	
			bool16 autoCorrect = autoCorrectPrefs->GetAutoCorrect();

			/* tell the event watcher to start/stop watching */
			//InterfacePtr<IEventWatcher> eventWatcher(this, UseDefaultIID());
			if (fKeyEventWatcher)
			{
				if (autoCorrect)
				{
					//ImportAllAutoCorrectFiles();
					fKeyEventWatcher->StartWatching();
				}
				else
				{
					fKeyEventWatcher->StopWatching();
				}
			}
		}
		break;
	}
}

void AutoCorrectObserver::ImportAllAutoCorrectFiles()
{
	Utils<IAutoCorrectUtils>()->ImportAllAutoCorrectFiles();
}


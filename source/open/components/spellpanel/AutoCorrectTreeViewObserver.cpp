//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectTreeViewObserver.cpp $
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

#include "IAutoCorrectPrefs.h"
#include "IAutoCorrectUtils.h"
#include "ILanguage.h"
#include "ISession.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITreeViewMgr.h"
#include "ITriStateControlData.h"
#include "IStringData.h"

#include "AutoCorrectTreeViewObserver.h"

#include "PreferenceUtils.h"
#include "Utils.h"

#include "SpellPanelID.h"
#include "SpellingServiceID.h"


CREATE_PMINTERFACE(AutoCorrectTreeViewObserver, kAutoCorrectTreeViewObserverImpl)

#define INHERITED 		AutoCorrectPanelObserver
//#define CONTROL_PMIID	IID_IBOOLEANCONTROLDATA

AutoCorrectTreeViewObserver::AutoCorrectTreeViewObserver(IPMUnknown *boss) :
	INHERITED(boss)
{
	//this->SetControlID( CONTROL_PMIID );
	//this->SetReset( kTrue );
}

bool16 AutoCorrectTreeViewObserver::SetupWidget()
{
	if( !INHERITED::SetupWidget() )
		return kFalse;

    InterfacePtr<ITreeViewMgr> treeMgr(this, UseDefaultIID());
    if (treeMgr)
	{
		treeMgr->ClearTree(kTrue);     
		treeMgr->ChangeRoot();
	}

	return kTrue;
}


bool16 AutoCorrectTreeViewObserver::AddEntry()
{
	K2Vector<PMString> misspelledItems;
	const bool16 bFound = this->GetAutoCorrectList(misspelledItems);

	return bFound;
}


bool16 AutoCorrectTreeViewObserver::RemoveEntry()
{
	return kTrue;
}


void	AutoCorrectTreeViewObserver::Update( const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy )
{
	if (theChange == kAutoCorrectPrefsCmdBoss || theChange == kAutoCorrectEditorMsgLanguageHasChanged)
	{
		this->SetupWidget();
		return;
	}

	INHERITED::Update( theChange, theSubject, protocol, changedBy );
}

bool16 AutoCorrectTreeViewObserver::GetAutoCorrectList( K2Vector<PMString>& misspelledItems )
{
	misspelledItems.clear();

	InterfacePtr<const ILanguage> pLanguage(this->QueryLanguage());
	if (!pLanguage)
		return kFalse;

	AutoCorrectList autoCorrectList;
	InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences(IID_IAUTOCORRECTPREFS));
	if (autoCorrectPrefs)
		autoCorrectList = autoCorrectPrefs->GetAutoCorrectList();

	// if we do not have an auto-correct list, try importing the auto-correct dictionaries
	if ( autoCorrectPrefs && autoCorrectPrefs->GetAutoCorrect() && autoCorrectList.Length() == 0 )
	{
		Utils<IAutoCorrectUtils>()->ImportAllAutoCorrectFiles();
		autoCorrectList = autoCorrectPrefs->GetAutoCorrectList();
	}

	if (autoCorrectList.Length() > 0)
	{
		LanguageID langID = pLanguage->GetLanguageID();
		AutoCorrectItem* autoCorrectItem = nil;
		bool16 foundLang(kFalse);

		for (int32 j = 0; j < autoCorrectList.Length(); ++j)
		{
			if (autoCorrectList[j].fLanguageID == langID)
			{
				foundLang = kTrue;
				autoCorrectItem = &(autoCorrectList[j]);
				break;
			}
		}

		if (foundLang && autoCorrectItem)
		{
			/* sort - UserDictWordList already sorted */
			for (int32 i = 0; i < autoCorrectItem->fAutoStringPair.Length(); ++i)
			{
				//const WideString &rAlternative = autoCorrectItem->fAutoStringPair[i].Key();
				const WideString &rAlternative = autoCorrectItem->fAutoStringPair.Key(i);
				PMString aString(rAlternative);
				misspelledItems.push_back(aString.SetTranslatable(kFalse));
			}
		}
	}

	return kTrue;
}

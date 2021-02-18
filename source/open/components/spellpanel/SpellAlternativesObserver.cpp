//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellAlternativesObserver.cpp $
//  
//  Owner: Bernd Paradies
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

#include "IBoolData.h"
#include "IDocument.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILanguage.h"
#include "ILinguisticMgr.h"
#include "ILinguisticServiceData.h"
#include "IListControlDataOf.h"
#include "IListBoxAttributes.h"
#include "IListBoxController.h"
#include "ISession.h"
#include "ISpellCheckWalkerData.h"
#include "ISpellingMgr.h"
#include "ISpellingService.h"
#include "ISpellPanelOptions.h"
#include "IStringData.h"
#include "ISubject.h"
#include "ITreeViewWidgetMgr.h"
#include "ITextControlData.h"
#include "IUIFontSpec.h"

#include "LinguisticID.h"
#include "K2Vector.h"
#include "PMString.h"
#include "PreferenceUtils.h"
#include "K2Vector.h"
#include "SpellPanelID.h"
#include "SpellPanelObserver.h"
#include "TextChar.h"
#include "TextPanelID.h"
#include "Trace.h"
#include "UnicodeClass.h"
#include "WideString.h"
#include "widgetid.h"

// ICU includes 
#include "unicode/unistr.h" 
#include "unicode/brkiter.h" 
#include "unicode/dbbi.h" 
#include "unicode/stsearch.h" 
#include "unicode/uloc.h" 
#include "unicode/ucol.h" 
#include "unicode/coll.h" 

typedef K2Vector<PMString*> StringPtrList;

//----------------------------------------------------------------------------------------
// Class SpellAlternativesObserver
//----------------------------------------------------------------------------------------

class SpellAlternativesObserver : public SpellPanelObserver
{
public:
						SpellAlternativesObserver(IPMUnknown *boss);

		virtual	void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

		// SpellPanelObserver: override
		virtual	bool16	ApplyToWidget();
		virtual	bool16	ApplyToFocus();

		virtual	bool16	SetupWidget();



private:
		ISpellingService::SpellResult 	fResult;

		void				NotifySpellCorrect( bool16 bCorrect );
		void				NotifyListBoxSelectionChanged();
		void				NotifySelectedItemHasChanged( const PMString *pText );
		void				OnSelectNextAlternative(  bool16 bNext  );
		void				OnFindAlternatives();
		//bool16				SetupWidgetAndSelectFirstWord();

		bool16			GetAlternatives( const PMString &rWord, const ILanguage *pLanguage, K2Vector<PMString>& items, bool16 bSpell  );
};


#define UNCLEAR 		""
#define RESET			"???"

#define CONTROL_PMIID		IID_ILISTCONTROLDATA


//===============================================================
// CLASS SpellAlternativesObserver
//===============================================================

CREATE_PMINTERFACE(SpellAlternativesObserver, kSpellAlternativesObserver)
#define INHERITED 	SpellPanelObserver

//---------------------------------------------------------------
// SpellAlternativesObserver constructor
//---------------------------------------------------------------

SpellAlternativesObserver::SpellAlternativesObserver(IPMUnknown *boss) :
	INHERITED(boss),
	fResult( ISpellingService::kCorrect )
{
	this->SetControlID( CONTROL_PMIID );
	this->SetReset( kTrue );
}

//---------------------------------------------------------------
// SpellAlternativesObserver::ApplyToWidget
//---------------------------------------------------------------

bool16 SpellAlternativesObserver::ApplyToWidget()
{
	InterfacePtr< IListControlDataOf<PMString> > pData( this, IID_ILISTCONTROLDATA );
	if( !pData )
		return kFalse;

	bool16 	bFound = kFalse;
	return bFound;
}

//---------------------------------------------------------------
// SpellAlternativesObserver::ApplyToFocus
//---------------------------------------------------------------

bool16 SpellAlternativesObserver::ApplyToFocus()
{
	return kTrue;
}

//---------------------------------------------------------------
// SpellAlternativesObserver::SetupWidget
//---------------------------------------------------------------

bool16 SpellAlternativesObserver::SetupWidget()
{
	if( !INHERITED::SetupWidget() )
		return kFalse;

	InterfacePtr< IListControlDataOf<PMString> > pData( this, IID_ILISTCONTROLDATA );
	InterfacePtr<IListBoxController> controller(this, IID_ILISTBOXCONTROLLER);

	const SpellPanelObserverMuter aMuter( this );

	controller->DeselectAll(kFalse, kFalse);

	const PMString &rWord = this->GetUserCorrectedWord();

	//InterfacePtr<IStringData>pWordToSpell( pMisspelledWord, IID_IWORDTOSPELL );	
	//const PMString &rWord = pWordToSpell->GetString();

	InterfacePtr<const ILanguage>pLanguage( this->QueryCurrentLanguage() );

	// no word, no alternatives
	if( rWord.IsEmpty() || !pLanguage )
	{
		pData->Clear(kTrue, kFalse);
		return kTrue;
	}

	bool16 useLargeRows = kFalse;

	LanguageID primaryLangID = GetPrimaryLanguageID(pLanguage->GetLanguageID());
	if (primaryLangID == kLanguageUseICULocale)
	{
		U_ICU_NAMESPACE::Locale locale = pLanguage->GetICULocale(); 
		const char *icuLangCode = locale.getLanguage();
		if (	(strncmp(icuLangCode, "bn", 2) == 0) //Bengali 
			||	(strncmp(icuLangCode, "gu", 2) == 0) //Gujarati 
			||	(strncmp(icuLangCode, "hi", 2) == 0) //Hindi 
			||	(strncmp(icuLangCode, "kn", 2) == 0) //Kannada 
			||	(strncmp(icuLangCode, "ml", 2) == 0) //Malayalam 
			||	(strncmp(icuLangCode, "mr", 2) == 0) //Marathi 
			||	(strncmp(icuLangCode, "or", 2) == 0) //Oriya 
			||	(strncmp(icuLangCode, "pa", 2) == 0) //Punjabi 
			||	(strncmp(icuLangCode, "ta", 2) == 0) //Tamil 
			||	(strncmp(icuLangCode, "te", 2) == 0) //Telugu 
			)
		{
			useLargeRows = kTrue;
		}
	}

	InterfacePtr<ITreeViewWidgetMgr> iTreeViewWidgetMgr(this, UseDefaultIID()); 

	if (useLargeRows && iTreeViewWidgetMgr->GetStyle() != kLargePaletteRowsTreeStyle)
		iTreeViewWidgetMgr->SetStyle(kLargePaletteRowsTreeStyle);
	else if (!useLargeRows && iTreeViewWidgetMgr->GetStyle() != kSmallPaletteRowsTreeStyle)
		iTreeViewWidgetMgr->SetStyle(kSmallPaletteRowsTreeStyle);

	// use AddElementCollection instead of Clear()/AddElement because of the optimizations in StringListBoxControlData
	K2Vector<PMString> aAlternatives;

	// bSpell = kTrue
	const bool16 bFound = this->GetAlternatives( rWord, pLanguage, aAlternatives, kTrue );
	if( aAlternatives.size() > 0 )
	{
		// TODO: this clear is a workaround because AddElementCollection() doesn't invalidate properly.
		pData->Clear(kTrue, kFalse);
		pData->Add(aAlternatives, kTrue, kFalse );
	}
	else
		pData->Clear(kTrue, kFalse);

	this->NotifySpellCorrect( bFound );

	return bFound;
}

//bool16 SpellAlternativesObserver::SetupWidgetAndSelectFirstWord()
//{
//	bool16 found = SetupWidget();
//	if(!found)
//	{
//		InterfacePtr< IListControlDataOf<PMString> > pData( this, IID_ILISTCONTROLDATA );
//		InterfacePtr<IListBoxController> controller(this, IID_ILISTBOXCONTROLLER); 
//		if(pData->Length() > 0 && controller->GetSelected() < 0)
//		{
//			controller->Select(0);
//			this->NotifyListBoxSelectionChanged();
//		}
//	}
//	return found;
//}

//---------------------------------------------------------------
// SpellAlternativesObserver::Update
//---------------------------------------------------------------

void	SpellAlternativesObserver::Update( const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy )
{
	// ==> Please update GetObserverInfo()  <==
	if( fInUpdate || this->IsMuted() )
		return;

	if( protocol == IID_ISPELLPANELMSG )
	{
		// sent by SpellWordObserver::NotifySpellWordObserver and SpellWordEventHandler::NotifySpellWordObserver on word changes
		if( theChange == kSpellPanelMsgWordHasChanged || theChange == kSpellPanelMsgSelectedItemHasChanged)
		{
			this->SetupWidget();
			return;
		}

		//if( theChange == kSpellPanelMsgStartCorrect  || theChange == kSpellPanelMsgSelectedItemHasChanged )
		//{
		//	this->Mute(kTrue);
		//	this->SetupWidgetAndSelectFirstWord();
		//	this->Mute(kFalse);
		//	return;
		//}

		// sent by SpellWordObserver::NotifySpellWordObserver on grammar changes.
		if( theChange == kSpellPanelMsgGrammarOfText )
		{
			const ISpellingService::SpellResult *pResult = (const ISpellingService::SpellResult *)changedBy;
			if( *pResult != fResult )
			{
				fResult = *pResult;
				this->SetupWidget();
				//this->SetupWidgetAndSelectFirstWord();
			}
			return;
		}

		// sent by SpellWordEventHandler::NotifySpellNextAlternative on arrow key hit.
		if( theChange == kSpellPanelMsgSelectNextItem ||   theChange == kSpellPanelMsgSelectPrevItem )
		{
			const bool16 bNext = theChange == kSpellPanelMsgSelectNextItem;
			this->OnSelectNextAlternative( bNext );
			return;
		}

		// sent by SpellWordEventHandler::NotifySpellFindAlternatives on space hit.
		if( theChange == kSpellPanelMsgFindAlternatives  )
		{
			this->OnFindAlternatives();
			return;
		}

		// sent by SpellWordEH on SpellWordEH::GetFocus().
		if( theChange == kSpellPanelMsgWordGetsFocus )
		{
			InterfacePtr<IListBoxController> controller( this, IID_ILISTBOXCONTROLLER );

			const SpellPanelObserverMuter aMuter( this );
			controller->DeselectAll( kTrue, kFalse );
			return;
		}
	}

	// sent by our ListBox on selection changes
	if( theChange == kListSelectionChangedMessage || theChange == kListSelectionChangedByUserMessage )
	{
		this->NotifyListBoxSelectionChanged();
		return;
	}

	// sent by our ListBox on selection changes
	if( protocol == this->GetControlID() )
	{
		this->NotifyListBoxSelectionChanged();
		return;
	}

	// hkhalfallah: Oct 09 2000
	// This will attach/detach the terminator and save restore the selections.

	INHERITED::Update( theChange, theSubject, protocol, changedBy );
}

//---------------------------------------------------------------
// SpellAlternativesObserver::NotifyListBoxSelectionChanged
//---------------------------------------------------------------

void	SpellAlternativesObserver::NotifyListBoxSelectionChanged()
{
	const SpellPanelObserverMuter aMuter( this );

	InterfacePtr< IListControlDataOf<PMString> > pData( this, IID_ILISTCONTROLDATA );
	InterfacePtr<IListBoxController> controller( this, IID_ILISTBOXCONTROLLER );

	PMString selectedString(kNullString);

	const int32 nSelected = controller->GetSelected();
	if( nSelected >= 0 )
		selectedString = (*pData)[ nSelected ];

	this->NotifySelectedItemHasChanged(&selectedString);
}

//---------------------------------------------------------------
// SpellAlternativesObserver::NotifySelectedItemHasChanged
//---------------------------------------------------------------

void	SpellAlternativesObserver::NotifySelectedItemHasChanged( const PMString *pText )
{
	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
	if( pPanel )
	{
		const SpellPanelObserverMuter aMuter( this );

		InterfacePtr<IStringData>pStringData( this, IID_ISTRINGDATA );
		ASSERT_MSG( pStringData != nil, "SpellAlternativesObserver - missing IID_ISTRINGDATA" );
		pStringData->Set( *pText );
		pPanel->Change( kSpellPanelMsgSelectedItemHasChanged, IID_ISPELLPANELMSG, this );
	}
}

//---------------------------------------------------------------
// SpellAlternativesObserver::NotifySpellCorrect
//---------------------------------------------------------------

void	SpellAlternativesObserver::NotifySpellCorrect( bool16 bCorrect )
{
	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
	if( !pPanel )
		return;

	InterfacePtr<IStringData>pStringData( this, IID_ISTRINGDATA );
	ASSERT_MSG( pStringData != nil, "SpellAlternativesObserver - missing IID_ISTRINGDATA" );

	InterfacePtr<IBoolData>pBoolData( this, IID_IBOOLDATA );
	ASSERT_MSG( pBoolData != nil, "SpellAlternativesObserver - missing IID_IBOOLDATA" );

	InterfacePtr< IListControlDataOf<PMString> >pData( this, IID_ILISTCONTROLDATA );
	ASSERT_MSG( pData != nil, "SpellAlternativesObserver - missing IID_ILISTCONTROLDATA" );

	InterfacePtr<IListBoxController> controller( this, IID_ILISTBOXCONTROLLER );

	if( !pStringData || !pBoolData || !pData )
		return;

	const SpellPanelObserverMuter aMuter( this );
	PMString aAlternative;
	const int32 nEntries = pData ? pData->Length() : 0;

	// if the word is correct, the string is empty.
	if( !bCorrect )
	{
		if( nEntries > 0 )
		{
			// grab the first entry
			int32 nSelected = controller->GetSelected();
			if( nSelected < 0 )
				nSelected = 0;

			aAlternative = (*pData)[ nSelected ];
		}
		else
		{
			// no entry? - set the mispelled word.
			aAlternative = this->GetUserCorrectedWord();
		}
	}

	// set the data
	pStringData->Set( aAlternative );
	pBoolData->Set( bCorrect );

	pPanel->Change( kSpellPanelMsgWordHasBeenCorrected, IID_ISPELLPANELMSG, this );
}

//---------------------------------------------------------------
// SpellAlternativesObserver::OnFindAlternatives
//---------------------------------------------------------------

void	SpellAlternativesObserver::OnFindAlternatives()
{
	InterfacePtr< IListControlDataOf<PMString> >pData( this, IID_ILISTCONTROLDATA );
	ASSERT_MSG( pData != nil, "SpellAlternativesObserver - missing IID_ILISTCONTROLDATA" );

	const PMString &rWord = this->GetUserCorrectedWord();

	InterfacePtr<const ILanguage>pLanguage( this->QueryCurrentLanguage() );

	// BP 3/11/97: if the word is correct the list is empty, but if the user presses blank or
	// 		arrow down, i will give him/her some alternatives anyway.
	if( pData->Length() == 0 && !rWord.IsEmpty() && pLanguage )
	{
		const SpellPanelObserverMuter aMuter( this );

		// use AddElementCollection instead of Clear()/AddElement because of the optimizations in StringListBoxControlData
		K2Vector<PMString> aAlternatives;

		// bSpell = kFalse, do only FindAlternatives
		const bool16 bFound = this->GetAlternatives( rWord, pLanguage, aAlternatives, kFalse );
		if( aAlternatives.size() > 0 )
			pData->Add(aAlternatives, kTrue, kFalse );
	}
}

//---------------------------------------------------------------
// SpellAlternativesObserver::OnSelectNextAlternative
//---------------------------------------------------------------

void	SpellAlternativesObserver::OnSelectNextAlternative( bool16 bNext )
{
	InterfacePtr< IListControlDataOf<PMString> >pData( this, IID_ILISTCONTROLDATA );
	ASSERT_MSG( pData != nil, "SpellAlternativesObserver - missing IID_ILISTCONTROLDATA" );

	InterfacePtr<IListBoxController> controller( this, IID_ILISTBOXCONTROLLER );

	// just to ensure that our list is filled
	this->OnFindAlternatives();

	// don't mute ourself!
	const int32 nSelected = controller->GetSelected();
	int32 nNewSelect = nSelected;

	if( bNext )
	{
		if( nNewSelect < 0 )
			nNewSelect = 0;
		else
			++nNewSelect;

		if( nNewSelect >= pData->Length() )
			return;
	}
	else
	{
		--nNewSelect;
		if( nNewSelect < 0  )
			return;
	}

	InterfacePtr<ISubject>pDataSubj( pData, IID_ISUBJECT );
	pDataSubj->Mute( kTrue );
	controller->DeselectAll(kFalse, kFalse);
	pDataSubj->Mute( kFalse );

	controller->Select( nNewSelect, kFalse, kTrue );
}


//---------------------------------------------------------------
// SpellAlternativesObserver::GetAlternatives
//---------------------------------------------------------------

bool16 SpellAlternativesObserver::GetAlternatives( const PMString &rWord, const ILanguage *pLanguage, K2Vector<PMString>& items, bool16 bSpell )
{
	items.clear();

	InterfacePtr<IStringData> pWordToSpell( this->QueryWordToSpell() );
	InterfacePtr<ISpellCheckWalkerData>pData( pWordToSpell, UseDefaultIID() );
	if( !pData )
		return kFalse;

	// BP 09/29/98: don't check on/with grammar
	//HH 2/25/99 I changed this somewhat to fix bug 293765, as Bernd and I discussed.
	if( bSpell /* && pData->GetSpellResult() != ISpellingService::kCorrect */ )
	{
		/* if the user is typing in the change to box we auto spell check their entry and provide alternatives */
		const WideString aText( rWord);
		if( pData->GetText() != aText )
		{
			ISpellingService::SpellResult originalResult = pData->GetSpellResult();
			pData->CheckText( aText, pLanguage, kFalse );
			pData->SetSpellResult(originalResult);	/* HH 3/30/99 Hack to restore the original result code */
		}
	}

	const bool16 bCorrect = pData->IsCorrect();
	if( bCorrect && bSpell )
	{
		TRACEFLOW_OBSOLETE("Old:SpellPanel", "This word is correct: '%s'\n",  rWord.GetUTF8String().c_str() );
		return bCorrect;
	}

	const WideStringList &rAlternatives = pData->GetAlternatives();
	const int32 nMax = rAlternatives.size();
	for( int32 i = 0; i < nMax; ++i )
	{
		const WideString &rAlternative = rAlternatives[i];
		PMString word;
		rAlternative.GetSystemString(&word.SetTranslatable(kFalse));
		items.push_back( word );
	}

	return bCorrect;
}





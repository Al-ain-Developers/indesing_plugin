//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellWordObserver.cpp $
//  
//  Owner:
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
#include "IBoolData.h"
#include "ICmdCollection.h"
#include "ICommand.h"
#include "IComposeScanner.h"
#include "IControlView.h"
#include "IDocument.h"
#include "IEventHandler.h"
#include "IKeyBoard.h"
#include "ILanguage.h"
#include "IListControlDataOf.h"
#include "IListBoxController.h"
#include "IPageItemFocus.h"
#include "ISession.h"
#include "ISpellCheckWalkerData.h"
#include "ISpellingService.h"
#include "ISpellingUtils.h"
#include "IStringData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITextFocusData.h"
#include "ITextModel.h"
#include "ITextModelCmds.h"
#include "ITextWalker.h"
#include "ITextWalkerSelectionUtils.h"
#include "IWidgetParent.h"
#include "ITextTarget.h"
#include "IGalleyUtils.h"
#include "IPanelControlData.h"
#include "ITextLines.h"
#include "IInCopySharedUtils.h"
#include "IItemLockData.h"

#include "CmdUtils.h"
#include "ILayoutUIUtils.h"
#include "ISelectionUtils.h"
#include "SpellPanelObserver.h"
#include "TextChar.h"

#include "CommandID.h"
#include "ConditionalTextID.h"
#include "CursorID.h"
#include "LinguisticID.h"
#include "SpellPanelID.h"
#include "TextPanelID.h"
#include "TextEditorID.h"
#include "TextID.h"
#include "widgetid.h"
#include "ITextWalkerScope.h"
#include "WritingModeUIID2.h"
#include "NoteID.h"
#include "InCopySharedID.h"

//----------------------------------------------------------------------------------------
// Class SpellWordObserver
//----------------------------------------------------------------------------------------

class SpellWordObserver : public SpellPanelObserver
{
public:
						SpellWordObserver(IPMUnknown *boss);

		virtual	void		AutoAttach();
		virtual	void		AutoDetach();

		virtual	void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

		// SpellWordObserver: override
		virtual	bool16		ApplyToWidget();
		virtual	bool16		ApplyToFocus();



private:
		typedef			SpellPanelObserver	Inherited;


		void				NotifyObserver( const ClassID &rID );

		void				NotifySpellWordObserver();
		void				NotifyMsgDone();


		bool16			SetString( const PMString &rText, bool16 bInvalidate );
		bool16			ApplyToWidget( const WideString &rWord, ISpellingService::SpellResult nResult );
		void				SetNewWordToSpell( const PMString &rNew );
		TextIndex			GetFocusWord( WideString *pWord, ITextFocus* pFocus ) const;
		int32			CountWordSpaces( const IComposeScanner *pScanner, TextIndex nPos );

};



//===============================================================
// CLASS SpellWordObserver
//===============================================================

CREATE_PMINTERFACE(SpellWordObserver, kSpellWordObserver);

//---------------------------------------------------------------
// SpellWordObserver constructor
//---------------------------------------------------------------

SpellWordObserver::SpellWordObserver(IPMUnknown *boss) :
	Inherited(boss)
{
	this->SetControlID( IID_ITEXTCONTROLDATA );
}

void SpellWordObserver::AutoAttach()
{
   InterfacePtr<ISubject> subject(this, IID_ISUBJECT); 
   if (subject && !subject->IsAttached( this, IID_ITEXTCONTROLDATA ) ) 
        subject->AttachObserver(this, IID_ITEXTCONTROLDATA);

   SpellPanelObserver::AutoAttach(); 
}

//---------------------------------------------------------------
// SpellChangeAllObserver::AutoDetach:
//---------------------------------------------------------------

void SpellWordObserver::AutoDetach()
{
    SpellPanelObserver::AutoDetach(); 

   InterfacePtr<ISubject> subject(this, IID_ISUBJECT); 
   if (subject && subject->IsAttached( this, IID_ITEXTCONTROLDATA ) ) 
        subject->DetachObserver(this, IID_ITEXTCONTROLDATA); 
}

//---------------------------------------------------------------
// SpellWordObserver::SetString
//---------------------------------------------------------------

bool16	SpellWordObserver::SetString( const PMString &rText, bool16 bInvalidate )
{
	InterfacePtr<ITextControlData>pTextData( this, IID_ITEXTCONTROLDATA );

	if( rText == pTextData->GetString()  )
		return kFalse;

	pTextData->SetString( rText, bInvalidate, kFalse );

	this->SetupWidget();
	this->NotifySpellWordObserver();

	// why does ITextControlData not invalidate?
	InterfacePtr<IControlView>pView( this, IID_ICONTROLVIEW );
	pView->Invalidate();

	return kTrue;
}

//---------------------------------------------------------------
// SpellWordObserver::ApplyToWidget
//---------------------------------------------------------------

bool16 SpellWordObserver::ApplyToWidget()
{
	return Inherited::ApplyToWidget();
}

//---------------------------------------------------------------
// SpellWordObserver::ApplyToWidget
//---------------------------------------------------------------

bool16 SpellWordObserver::ApplyToWidget( const WideString &rWord, ISpellingService::SpellResult nResult )
{
	InterfacePtr<ITextControlData> pData( this, IID_ITEXTCONTROLDATA );
	if( !pData )
		return kFalse;

	PMString aString;
	aString.SetTranslatable( kFalse );
#if 0
	if( rWord.Length() > 0 )
	{
		WideString aWord = rWord;
		::StripDiscrHyphens( &aWord );
		aWord.GetSystemString( &aString );
	}
#else
	rWord.GetSystemString(&aString);
#endif

	this->SetNewWordToSpell( aString );

	if( pData->GetString() == aString )
		return kFalse;

	pData->SetString( aString, kTrue );
	this->NotifySpellWordObserver();

	return kTrue;
}

//---------------------------------------------------------------
// SpellWordObserver::ApplyToFocus
//---------------------------------------------------------------

// BP 5/5/97: #205682 Using the spelling palette to correct a misspelling leaves the corrected word selected.
// BP 04/24/98: 251194 Shuksan Open ToFix  Text Spelling Deleting word from "Change To", does not delete it from the text

bool16 SpellWordObserver::ApplyToFocus()
{
	InterfacePtr<ITextWalker> pWalker(this->QueryTextWalker());
	ITextFocus* pFocus = pWalker->GetClientSelection(nil, nil);

	if( !pFocus || !pFocus->IsRange() )
		return kFalse;

	// new word is empty?
	InterfacePtr<ITextControlData> pData( this, IID_ITEXTCONTROLDATA );
	if( !pData )
		return kFalse;

	boost::shared_ptr<WideString> aNewWord( new WideString(pData->GetString() ));
	const int32 nNewLength = aNewWord->Length();

	WideString aWord;
	TextIndex nWordOfStart = this->GetFocusWord( &aWord, pFocus );			// allow change
	if(  nWordOfStart == kInvalidTextIndex || !aWord.Length() )
		return kFalse;

	// same word as selection?
	if( aWord == *aNewWord )
		return kFalse;

	// set the new focus and send the command
	InterfacePtr<ITextModel>pModel( pFocus->QueryModel() );

	InterfacePtr<IItemLockData> itemLockData(pModel, IID_IITEMLOCKDATA);
	if (itemLockData && itemLockData->GetInsertLock())
	{
		// can't change the model so we are done.
		return kFalse;
	}

	int32 originalWordLength = aWord.Length();
	if (nNewLength == 0)
	{
		//HH 03/02/99 If the newLength == 0 we are essentially doing a delete, so we want to remove any white space.
		InterfacePtr<IComposeScanner>pScanner( pModel, IID_ICOMPOSESCANNER );
		originalWordLength = aWord.Length() + CountWordSpaces(pScanner, nWordOfStart + aWord.Length()); ;
	}

	/* HH 3/8/99 */
	TextIndex walkerPosition = pWalker->GetWalkerPosition(); //returns the last index of the current selection

	ICommandSequence* sequence = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
	sequence->SetName("Replace Text");

	TextIndex newStart;
	int32 newLength = originalWordLength;
	K2Vector<ClassID> moveOwnedItemClasses;
	moveOwnedItemClasses.push_back(kNoteDataBoss);
	moveOwnedItemClasses.push_back(kHiddenTextBoss);
	bool16 gotMoved = Utils<IInCopySharedUtils>()->MoveOwnedItem(pModel, nWordOfStart, originalWordLength, newStart, newLength, moveOwnedItemClasses);
	if (gotMoved)
		{
		nWordOfStart = newStart;
		originalWordLength = newLength;
		}

	// BP 04/27/98:
	InterfacePtr<ITextModelCmds>modelCmds(pModel, UseDefaultIID());
	InterfacePtr<ICommand>	pReplace(modelCmds->ReplaceCmd( nWordOfStart,  newLength/*originalWordLength*/, aNewWord));
	ErrorCode err = CmdUtils::ProcessCommand( pReplace );
	if (err != kSuccess)
	{
		CmdUtils::EndCommandSequence(sequence);
		return kFalse;
	}
	CmdUtils::EndCommandSequence(sequence);

	/* HH 3/8/99 reset walker to beginning of insertion - this will allow the speller engine to verify whatever was entered */
	{
		InterfacePtr<ITextWalkerScope>pScope(pWalker->QueryScope());
		if (pScope)
		{
			bool16 searchBackwards = kFalse;
			InterfacePtr<const ISpellCheckWalkerData> spellWalkerData(pWalker, UseDefaultIID());
			if (spellWalkerData)
				searchBackwards = (spellWalkerData->GetDirection());

			TextIndex newPos;
			if(searchBackwards)
				newPos = walkerPosition + aWord.Length(); // we need to move back in spell backwards case and go to the end of word.
			else
				newPos = walkerPosition - aWord.Length();

			ITextFocus* pRange = pScope->GetCursorRange(pWalker->GetCursorToken(), nil, nil);
			if (pRange)
			{
				TextIndex startRange = pRange->GetCurrentRange().Start(nil);
				int32 rangeLen = pRange->GetCurrentRange().Length( );

				bool16 moveToNewPos = kFalse;
				if (searchBackwards)
					moveToNewPos = (newPos <= startRange + rangeLen && newPos > startRange) ? kTrue : kFalse;
				else
					moveToNewPos = (newPos >= startRange && newPos < startRange + rangeLen) ? kTrue : kFalse;

				if (moveToNewPos)
					pWalker->MoveTo(newPos);
			}
		}
	}

	if (aWord.Length() != nNewLength)
	{
	    UIDRef storyRef = ::GetUIDRef(pModel); 
		InterfacePtr<ITextWalkerSelectionUtils>twSelectUtils(pWalker, IID_ITEXTWALKERSELECTIONUTILS);
		twSelectUtils->SelectText(storyRef, nWordOfStart, nNewLength);
	}
	this->NotifyObserver( kSpellPanelMsgResumeChecking );

	return kTrue;
}

int32 SpellWordObserver::CountWordSpaces( const IComposeScanner *pScanner, TextIndex nPos )
{
	if( !pScanner || nPos == kInvalidTextIndex )
		return 0;

	int32 nBlanks = 0;
	WideString aNextWord;
	const int32 kChunkSize = 10;
	pScanner->CopyText( nPos, kChunkSize, &aNextWord );
	while( kTrue )
	{
		const int32 nMax = aNextWord.Length();
		for( int32 i = 0; i < nMax; ++i )
		{
			UTF32TextChar	c = aNextWord.GetChar(i);
			if (c == kTextChar_CR || c == kTextChar_Tab || !UnicodeClass::IsWhiteSpace(c))
				return nBlanks;
			++nBlanks;
		}

		// last portion?
		if( nMax != kChunkSize )
			return nBlanks;

		nPos += kChunkSize;
		pScanner->CopyText( nPos, kChunkSize, &aNextWord );
	}
	return nBlanks;
}

//---------------------------------------------------------------
// SpellWordObserver::Update
//---------------------------------------------------------------

// kSpellPanelMsgDelayThread: is sent by SpellWordEventHandler::NotifySpellNextAlternative every kSleepMilliseconds (500) milliseconds.
// kSpellPanelMsgApplyToText: is sent by SpellWordEventHandler and  SpellWordCorrectObserver when the word should be applied.
// BP 4/9/97: #203493 Spelling performs inconsistently depending on how a word is type or selected.

void	SpellWordObserver::Update( const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy )
{
	if( this->IsMuted() )
		return;

	if (protocol == IID_ITEXTCONTROLDATA && (theChange.Get() == kEditBoxKeyStrokeMessage))
	{
        InterfacePtr<ITextControlData> correctedWord(this, IID_ITEXTCONTROLDATA); 
		InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() ); 
		if( pPanel ) 
			pPanel->Change( kSpellPanelMsgWordHasChanged, IID_ISPELLPANELMSG, this );
		InterfacePtr<IStringData>pMisspelledModelWord( this->QueryWordToSpell() );
		const bool16 bSameAsOriginalIncorrectWord = correctedWord && pMisspelledModelWord->GetString() == correctedWord->GetString();     
		if (bSameAsOriginalIncorrectWord)
			pPanel->Change( kSpellPanelMsgChangeDisabled, IID_ISPELLPANELMSG, this );
		else
			pPanel->Change( kSpellPanelMsgChangeEnabled, IID_ISPELLPANELMSG, this );
	}

	if( theChange == kSpellPanelMsgApplyToText )
	{
		this->ApplyToFocus();
		this->NotifySpellWordObserver();
		this->NotifyMsgDone();
		return;
	}

	// sent by SpellListBoxEH on SpellListBoxEH::ButtonDblClk().
	if( theChange == kSpellPanelMsgItemExecuted )
	{
		// see DictWordObserver::Update()
		InterfacePtr< IListControlDataOf<PMString> >pList( (IPMUnknown*)changedBy, IID_ILISTCONTROLDATA );
		InterfacePtr<IListBoxController> controller( pList, IID_ILISTBOXCONTROLLER );
		if( controller->GetSelected() >= 0 )
		{
			PMString pListWord = (*pList)[ controller->GetSelected() ];
			if( pListWord != "" )
			{
				this->SetNewWordToSpell( pListWord );
				this->SetString( pListWord, kTrue );
				this->ApplyToFocus();
			}
		}
		return;
	}


	// sent by HYPLanguageObserver::NotifyFlagObserver on language changes
	if( protocol == IID_ITALANGUAGEOBSERVER )
	{
		const ILanguage *pLanguage = (const ILanguage *)changedBy;
		if( pLanguage )
		{
			InterfacePtr<ILanguage>pPanelLanguage( this->QueryCurrentLanguage() );
			if( pPanelLanguage )
				pPanelLanguage->CopyFrom( pLanguage );
		}
		return;
	}

	// sent by SpellCheckWalkerClient::NotifyDoSuspend()
	if( theChange == kSpellPanelMsgStartCorrect )
	{
		// BP 03/31/98: flag that toggles background spelling
		const IPMUnknown *pSpellCheckWalker = static_cast<const IPMUnknown*>(changedBy);
		InterfacePtr<const ILanguage>pLanguage( pSpellCheckWalker, IID_ILANGUAGE );
		if( pLanguage )
		{
			InterfacePtr<ILanguage>pPanelLanguage( this->QueryCurrentLanguage() );
			if( pPanelLanguage )
				pPanelLanguage->CopyFrom( pLanguage );
		}
		InterfacePtr<const ISpellCheckWalkerData>pWalkerData( pSpellCheckWalker, UseDefaultIID() );
		if( !pWalkerData )
			this->ApplyToWidget();
		else
			this->ApplyToWidget( pWalkerData->GetText(), pWalkerData->GetSpellResult() );

		// BP 08/26/98:  word edit box is only enabled during spell checking.
		InterfacePtr<IControlView>pView( this, IID_ICONTROLVIEW );
		if( pView && !pView->IsEnabled() )
			pView->Enable( kTrue );

		// BP 09/30/98: #273935 [Win Only] Tabbing in Spelling dialog deletes text
		InterfacePtr<IEventHandler>pHandler( this, IID_IEVENTHANDLER );
		InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
		InterfacePtr<IKeyBoard> theKeyBoard(theApp, IID_IKEYBOARD);
		theKeyBoard->AcquireKeyFocus(pHandler);

		return;
	}


	// BP 10/02/97: #230404 Incorrect word flagging
	//	The muter has to be after theChange == kSpellPanelMsgApplyToText.
	// 	NotifyMsgDone -> ... TextWalker::SelectText() -> SelectTextRange() with the next word -> SpellWordObserver::Update()
	const SpellPanelObserverMuter aMuter( this );

	if( protocol == IID_ISPELLPANELMSG )
	{
		// sent by SpellCheckWalkerClient::NotifyDoHalt()
		if( theChange == kSpellPanelMsgEndCorrect )
		{
			this->SetNewWordToSpell( kNullString );
			this->SetString( kNullString, kTrue );
			return;
		}

		// sent by SpellChangeObserver::NotifyObserver() on SetMode( kStart ).
		if( theChange == kSpellPanelMsgReadyToStart || theChange == kSpellPanelMsgFinished )
		{
			InterfacePtr<IStringData> pWordToSpell( this->QueryWordToSpell() );
			InterfacePtr<ISpellCheckWalkerData>pWalkerData( pWordToSpell, UseDefaultIID() );
			if( pWalkerData )
				pWalkerData->Reset();

			this->SetNewWordToSpell( kNullString );
			this->SetString( kNullString, kTrue );

			// BP 08/26/98:  word edit box is only enabled during spell checking.
			InterfacePtr<IControlView>pView( this, IID_ICONTROLVIEW );
			if( pView && pView->IsEnabled() )
				pView->Enable( kFalse );

			return;
		}

		// sent by SpellMisspelledEH::NotifySpellWordObserver() on button down.
		if( theChange == kSpellPanelMsgResetToMisspelledWord )
		{
			InterfacePtr<IStringData>pWordToSpell( this->QueryWordToSpell() );
			if( pWordToSpell )
				this->SetString( pWordToSpell->GetString(), kTrue );
			return;
		}

		// sent by SpellAlternativesObserver::NotifyListBoxSelectionChanged on selection changes
		if( theChange == kSpellPanelMsgSelectedItemHasChanged  )
		{
			// BP 03/17/98: 'Misspelled Word' is only a StaticTextWidget and doesn't change on listbox selection changes.
			InterfacePtr<IStringData>pStringData( (IPMUnknown*)changedBy, IID_ISTRINGDATA );
			if( pStringData )
				this->SetString( pStringData->GetString(), kTrue );
			return;
		}

		// sent by SpellListBoxEH on SpellListBoxEH::ButtonDblClk().
		if( theChange == kSpellPanelMsgItemSelected )
		{
			// EditBoxEH::SuspendKeyFocus() doesn't do anything

			InterfacePtr<const IEventHandler>pHandler( this, IID_IEVENTHANDLER );
			InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
			InterfacePtr<IKeyBoard> theKeyBoard(theApp, IID_IKEYBOARD);
			if (theKeyBoard && theKeyBoard->GetKeyFocus() == pHandler)
				theKeyBoard->RelinquishKeyFocus();

			return;
		}


		return;
	}

	// hkhalfallah: Oct 09 2000
	// This will attach/detach the terminator and save restore the selections.

	Inherited::Update( theChange, theSubject, protocol, changedBy );
}

//---------------------------------------------------------------
// SpellWordObserver::NotifyObserver
//---------------------------------------------------------------

void	SpellWordObserver::NotifyObserver( const ClassID &rID )
{
	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
	if( pPanel )
		pPanel->Change( rID, IID_ISPELLPANELMSG, this );
}

//---------------------------------------------------------------
// SpellWordObserver::NotifySpellWordObserver
//---------------------------------------------------------------

void	SpellWordObserver::NotifySpellWordObserver()
{
	this->NotifyObserver( kSpellPanelMsgWordHasChanged );
}

//---------------------------------------------------------------
// SpellWordObserver::NotifyMsgDone
//---------------------------------------------------------------

void	SpellWordObserver::NotifyMsgDone()
{
	this->NotifyObserver( kSpellPanelMsgDone );
}

//---------------------------------------------------------------
// SpellWordObserver::SetNewWordToSpell
//---------------------------------------------------------------

void	SpellWordObserver::SetNewWordToSpell( const PMString &rNew )
{
	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
	InterfacePtr<IStringData> pWordToSpell( this->QueryWordToSpell() );
	if( !pPanel || !pWordToSpell )
		return;

	WideString aWord( rNew);
	Utils<ISpellingUtils>()->StripIgnorablesForSpelling( aWord );

	PMString rNewStripped;
	rNewStripped.SetTranslatable(kFalse);
	aWord.GetSystemString( &rNewStripped );

	if( pWordToSpell->GetString() == rNewStripped )
		return;

	pWordToSpell->Set( rNewStripped );
	pPanel->Change( kSpellPanelMsgNewWordToSpell, IID_ISPELLPANELMSG, this );
}


//---------------------------------------------------------------
// SpellWordObserver::GetFocusWord
//---------------------------------------------------------------

TextIndex	SpellWordObserver::GetFocusWord( WideString *pWord, ITextFocus* pFocus) const
{
	if( !pFocus || !pFocus->IsRange())
		return kInvalidTextIndex;

	// now do the 'old' stuff...
	// ambigious selection?
	pWord->Clear();
	InterfacePtr<ITextModel>		pModel( pFocus->QueryModel() );
	InterfacePtr<IComposeScanner>	pScanner( pModel, UseDefaultIID() );

	TextIndex nWordOfStart = pScanner->CopyText( pFocus->GetCurrentRange(), pWord );
	if( nWordOfStart == kInvalidTextIndex || pWord->Length() == 0 )
		return kInvalidTextIndex;

	return nWordOfStart;
}





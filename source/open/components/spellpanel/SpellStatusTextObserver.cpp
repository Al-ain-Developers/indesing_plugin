//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellStatusTextObserver.cpp $
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

#include "SpellPanelObserver.h"
#include "widgetid.h"

#include "ITextControlData.h"	
#include "ISpellCheckWalkerData.h"
#include "IStringData.h"
#include "ITextWalker.h"

// SpellStatusTextObserver::IsFocusInOverset
#include "TextID.h"
#include "ILayoutUIUtils.h"
#include "ISelectionUtils.h"
#include "ITextFocus.h"
#include "ITextModel.h"
#include "ITextParcelList.h"
#include "ITextMiscellanySuite.h"
#include "ITextWalkerSelectionUtils.h"
#include "TextPanelID.h"
#include "IControlView.h"

#include "LocaleSetting.h"
#include "ITrackChangeUtils.h"

//----------------------------------------------------------------------------------------
// Class SpellStatusTextObserver
//----------------------------------------------------------------------------------------

class SpellStatusTextObserver : public SpellPanelObserver
{
public:
						SpellStatusTextObserver(IPMUnknown *boss);

		// SpellPanelObserver: override 
		virtual	bool16	ApplyToFocus();
		virtual	void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);
		virtual	void		AutoAttach();
		


private:

		bool16			IsFocusInDeletion() const;
		PMString 		DetermineStatusText(const ISpellCheckWalkerData * pWalkerData);
		void 			SetStatusTextDisplay(PMString aText);

		int			fWordMode;
};

enum { kOverset, kInTable, kDeletedText, kVisibleText, kHiddenLayer };

#define kReadyToSpellCheck 	"Ready to Spell Check:"
#define kFinishedSpellCheck 	"Spell Check Complete:"

//---------------------------------------------------------------
// static functions
//---------------------------------------------------------------

//===============================================================
// CLASS SpellStatusTextObserver
//===============================================================

CREATE_PMINTERFACE(SpellStatusTextObserver, kSpellStatusTextObserverImpl)
#define INHERITED 	SpellPanelObserver

//---------------------------------------------------------------
// SpellStatusTextObserver constructor 
//---------------------------------------------------------------

SpellStatusTextObserver::SpellStatusTextObserver(IPMUnknown *boss) :
	INHERITED(boss)
{
	this->SetControlID( IID_ITEXTCONTROLDATA );
	this->SetReset( kTrue );
	fWordMode = -1;
}

//---------------------------------------------------------------
// SpellStatusTextObserver::ApplyToFocus
//---------------------------------------------------------------

bool16 SpellStatusTextObserver::ApplyToFocus()
{
	return kFalse;
}

PMString SpellStatusTextObserver::DetermineStatusText(const ISpellCheckWalkerData * pWalkerData)
{
	PMString aText;
	InterfacePtr<const ITextWalker>pWalker( this->QueryTextWalker() );
	if( !pWalker || !pWalkerData )
	{
		return aText;
	}
		
	if( !pWalker->IsWalking() || pWalkerData->IsCorrect() )
	{
		aText.SetKey( kReadyToSpellCheck ); 
	}
	else
	{
		const ISpellingService::SpellResult nResult = pWalkerData->GetSpellResult();
		switch( nResult )
		{
			case ISpellingService::kIncorrectWord: 
				{
					if( pWalkerData->GetAlternatives().size() == 0 )
						aText.SetKey( "Unknown Word - No Suggestions" ); 
					else
						aText.SetKey( "Not in Dictionary" ); 
				}
				break;
			
			case ISpellingService::kRepeatedWord: 
				aText.SetKey( "Repeated Word" );
				break;

			case ISpellingService::kUncapitalizedWord: 
				aText.SetKey( "Uncapitalized Word" ); 
				break;
			case ISpellingService::kUncapitalizedStartOfSentence: 
				aText.SetKey( "Uncapitalized Sentence" ); 
				break;

			case ISpellingService::kSpellError: 
			case ISpellingService::kGrammarError: 
				{
					ASSERT_MSG( kFalse, "SpellStatusTextObserver - don't use kSpellError and kGrammarError" );
					aText.SetKey( "Not in Dictionary" );
				}
				break;

			case ISpellingService::kCorrect: 
				{
					ASSERT_MSG( kFalse, "SpellStatusTextObserver - kCorrect != pWalkerData->IsCorrect()" );
					aText.SetKey( kReadyToSpellCheck ); 
					return aText;
				}
				break;
					
			default:
				{
					aText = ErrorUtils::PMGetErrorString((ErrorCode)nResult);
					std::string keyString = aText.GetPlatformString();
					if ( this->IsFocusInDeletion() )
							keyString.append( "DeletedText" );
					else
					{
						switch (fWordMode)
						{
						case kHiddenLayer:
							keyString.append( "HiddenLayer" );
							break;
						case kOverset:
							keyString.append( "OversetText" );
							break;
						case kInTable:
							keyString.append( "InTable");
							break;
						case kDeletedText:
							keyString.append( "DeletedText" );
							break;
						default:
							keyString.append( "StaticText" );
						}
					}

					aText.SetKey(keyString.c_str());
					return aText;
				}
		}	

		if ( this->IsFocusInDeletion() )
		{
				aText.Append( " (Deleted Text):" );
		}
		else
		{
			switch (fWordMode)
			{
			case kHiddenLayer:
				aText.Append( " (Hidden):" );
				break;
			case kOverset:
				aText.Append( " (Overset):" );
				break;
			case kInTable:
				aText.Append( " (In Table):");
				break;
			case kDeletedText:
				aText.Append( " (Deleted Text):" );
				break;
			default:
				aText.Append( ":" );
			}
		}
	}
	return aText;
}

void SpellStatusTextObserver::SetStatusTextDisplay(PMString aText)
{
	InterfacePtr<ITextControlData>pData( this, IID_ITEXTCONTROLDATA );
	if( pData && pData->GetString() != aText )
	{
		pData->SetString( aText, kTrue, kFalse );
	}
}
//---------------------------------------------------------------
// SpellStatusTextObserver::Update
//---------------------------------------------------------------

void	SpellStatusTextObserver::Update( const ClassID& theChange, ISubject*theSubject, const PMIID &protocol, void* changedBy )
{
	// ==> Please update GetObserverInfo()  <==
	if( this->IsMuted() )
		return;

	if( theChange == kSpellPanelMsgReadyToStart || theChange == kSpellPanelMsgFinished)
	{
		PMString aText(theChange == kSpellPanelMsgFinished ? kFinishedSpellCheck : kReadyToSpellCheck);
		InterfacePtr<ITextControlData>pData( this, IID_ITEXTCONTROLDATA );
		if( pData && pData->GetString() != aText )
		{
			pData->SetString( aText, kTrue, kFalse );
		}

		return;
	}

	if (protocol == IID_ITEXTWALKERMSG)
	{
		if (theChange == kWalkHiddenLayerText)
		{
			fWordMode = kHiddenLayer;
		}
		else if (theChange == kWalkOverSetText)
		{
			fWordMode = kOverset;
		}
		else if (theChange == kWalkTextInTable)
		{
			fWordMode = kInTable;
		}
		else if (theChange == kWalkText || theChange == kTextWalkerOnHaltMessage)
		{
			fWordMode = kVisibleText;
		}
	}

	if (theChange == kWalkHiddenLayerText ||
		theChange == kWalkOverSetText ||
		theChange ==kWalkTextInTable ||
		theChange == kWalkText ||
		theChange == kTextWalkerOnHaltMessage ||
		theChange == kSpellPanelMsgStartCorrect ||
		theChange == kSpellPanelMsgReadyToStart)
	{
		const IPMUnknown *pSpellCheckWalker = static_cast<const IPMUnknown*>(changedBy);
		InterfacePtr<const ISpellCheckWalkerData>pWalkerData( pSpellCheckWalker, UseDefaultIID() );

		PMString aText;
		aText = DetermineStatusText(pWalkerData);
		SetStatusTextDisplay(aText);
	}
	
	if (protocol == IID_ITEXTWALKERMSG	&& theChange ==  kTextWalkerOnEndMessage) 
	{
		InterfacePtr<IControlView>pView( this, IID_ICONTROLVIEW );
		pView->Enable( kTrue);
	}
	INHERITED::Update(theChange, theSubject, protocol, changedBy );
}



//---------------------------------------------------------------
// SpellStatusTextObserver::IsFocusInDeletion
//---------------------------------------------------------------

bool16 SpellStatusTextObserver::IsFocusInDeletion() const
{
	if (!LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS))
		return kFalse;

	//if (Utils<ITrackChangeUtils>() && Utils<ITrackChangeUtils>()->MarkDeleteChanges())
	//	return kFalse;

	InterfacePtr<ISelectionManager> selectionManager(Utils<ISelectionUtils>()->QueryActiveSelection());
	InterfacePtr<ITextMiscellanySuite> textMiscellanySuite(static_cast<ITextMiscellanySuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_ITEXTMISCELLANYSUITE, selectionManager)));
	if (textMiscellanySuite)
	{
		bool16 selectionIsInDeletedText = kFalse;
		textMiscellanySuite->IsSelectionInDeletedText(selectionIsInDeletedText);
		return selectionIsInDeletedText;
	}

	return kFalse;
}

//---------------------------------------------------------------
// SpellStatusTextObserver::AutoAttach: 
//---------------------------------------------------------------

void SpellStatusTextObserver::AutoAttach()
{
	if( !fAttached )
	{
		INHERITED::AutoAttach();

		// UI compensation: if you open a dialog twice you get old values...
		const PMString aText( kReadyToSpellCheck );
		InterfacePtr<ITextControlData>pData( this, IID_ITEXTCONTROLDATA );
		if( pData && pData->GetString() != aText )
		{
			pData->SetString( aText, kTrue, kFalse );
		}

		this->AutoAttachToTextWalker();
	}
}



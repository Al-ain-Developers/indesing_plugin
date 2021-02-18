//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellMisspelledObserver.cpp $
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
#include "SpellPanelObserver.h"

#include "IStringData.h"
#include "ITextControlData.h"
#include "ISpellCheckWalkerData.h"
#include "ITextWalkerSelectionUtils.h"
#include "IControlView.h"
#include "ISpellingUtils.h"
#include "Utils.h"

#include "CursorID.h"
#include "widgetid.h"
#include "TextWalkerServiceProviderID.h"

//----------------------------------------------------------------------------------------
// Class SpellMisspelledObserver
//----------------------------------------------------------------------------------------

class SpellMisspelledObserver : public SpellPanelObserver
{
public:
						SpellMisspelledObserver(IPMUnknown *boss);

		// SpellPanelObserver: override
		virtual	bool16	ApplyToFocus();
		virtual	void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);
		virtual	void		AutoAttach();



private:

		bool16 		IsEditBox() const;
		void			SetString( const PMString &rText );
};


//===============================================================
// CLASS SpellMisspelledObserver
//===============================================================

CREATE_PMINTERFACE(SpellMisspelledObserver, kSpellMisspelledObserver);
#define INHERITED 	SpellPanelObserver

//---------------------------------------------------------------
// SpellMisspelledObserver constructor
//---------------------------------------------------------------

SpellMisspelledObserver::SpellMisspelledObserver(IPMUnknown *boss) :
	INHERITED(boss)
{
	this->SetControlID( IID_ITEXTCONTROLDATA );
	this->SetReset( kTrue );
}

//---------------------------------------------------------------
// SpellMisspelledObserver::ApplyToFocus
//---------------------------------------------------------------

bool16 SpellMisspelledObserver::ApplyToFocus()
{
	return kFalse;
}

//---------------------------------------------------------------
// SpellMisspelledObserver::Update
//---------------------------------------------------------------

void	SpellMisspelledObserver::Update( const ClassID& theChange, ISubject*theSubject, const PMIID &protocol, void* changedBy )
{
	// ==> Please update GetObserverInfo()  <==
	if( this->IsMuted() )
		return;

	if( protocol == IID_ISPELLPANELMSG && this->IsEditBox() )
	{
		if( theChange == kSpellPanelMsgReadyToStart )
		{
			this->SetString( kNullString );
			return;
		}

		// sent by SpellWordObserver::SetNewWordToSpell
		if( theChange == kSpellPanelMsgNewWordToSpell )
		{
			InterfacePtr<IStringData>pWordToSpell( this->QueryWordToSpell() );
			if( pWordToSpell )
				this->SetString( pWordToSpell->GetString() );
			return;
		}
	}

	if (protocol == IID_ITEXTWALKERMSG	&& theChange ==  kTextWalkerOnEndMessage)
	{
		InterfacePtr<IControlView>pView( this, IID_ICONTROLVIEW );
		pView->Enable( kFalse );
	}
	INHERITED::Update(theChange, theSubject, protocol, changedBy );
}

//---------------------------------------------------------------
// SpellMisspelledObserver::IsEditBox
//---------------------------------------------------------------

bool16 SpellMisspelledObserver::IsEditBox() const
{
	InterfacePtr<const IPMUnknown>pTestForEditBox( this,  IID_ICURSORREGION );
	return pTestForEditBox != nil;
}

//---------------------------------------------------------------
// SpellMisspelledObserver::AutoAttach:
//---------------------------------------------------------------

void SpellMisspelledObserver::AutoAttach()
{
	if( !fAttached )
	{
		INHERITED::AutoAttach();

		// UI compensation: if you open a dialog twice you get old values...
		if( this->IsEditBox() )
		{
			const SpellPanelObserverMuter aMuter( this );
			InterfacePtr<ITextControlData>pTextData( this, IID_ITEXTCONTROLDATA );
			if( pTextData && !pTextData->GetString().IsEmpty() )
				pTextData->SetString( kNullString );
		}
	}
}


//---------------------------------------------------------------
// SpellMisspelledObserver::SetString:
//---------------------------------------------------------------

void SpellMisspelledObserver::SetString( const PMString &rText )
{
	if( this->IsEditBox() )
	{
		InterfacePtr<ITextControlData>	pTextData( this, IID_ITEXTCONTROLDATA );
		if( pTextData && pTextData->GetString() != rText )
		{
			if (rText == kNullString)
				pTextData->SetString( rText );
			else
			{
				PMString rNewStripped;
				rNewStripped.SetTranslatable(kFalse);
				WideString aText (rText);
				Utils<ISpellingUtils>()->StripIgnorablesForSpelling(aText);
				aText.GetSystemString( &rNewStripped);
				pTextData->SetString( rNewStripped);
			}
		}
	}
}


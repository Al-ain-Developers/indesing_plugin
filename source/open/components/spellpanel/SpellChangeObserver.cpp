//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellChangeObserver.cpp $
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

#include "IControlView.h"
#include "ITriStateControlData.h"	
#include "ISelectionManager.h"
#include "ISubject.h"
#include "ITextWalker.h"
#include "ITextWalkerSelectionUtils.h"
#include "ITextEditSuite.h"
#include "ISelectionUtils.h"

#include "Utils.h"

#include "SpellPanelID.h"
#include "widgetid.h"
#include "TextPanelID.h"


//----------------------------------------------------------------------------------------
// Class SpellChangeObserver
//----------------------------------------------------------------------------------------

class SpellChangeObserver : public SpellPanelObserver
{
public:
						SpellChangeObserver(IPMUnknown *boss);

		// SpellPanelObserver: override 
		virtual	bool16	ApplyToFocus();
		virtual	void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);
		virtual	void		AutoAttach();
		virtual	void		AutoDetach();



private:
			void			NotifyObserver( ClassID nMsg );

			bool16		IsSelected() const;
			void			Deselect();
};


//---------------------------------------------------------------
// static functions
//---------------------------------------------------------------

//===============================================================
// CLASS SpellChangeObserver
//===============================================================

CREATE_PMINTERFACE(SpellChangeObserver, kSpellChangeObserver)
#define INHERITED 	SpellPanelObserver

//---------------------------------------------------------------
// SpellChangeObserver constructor 
//---------------------------------------------------------------

SpellChangeObserver::SpellChangeObserver(IPMUnknown *boss) :
	INHERITED(boss)
{
	InterfacePtr<const ITriStateControlData>pTriData( this, IID_ITRISTATECONTROLDATA );	
	this->SetControlID( pTriData != nil ? IID_ITRISTATECONTROLDATA : IID_IBOOLEANCONTROLDATA );
	this->SetReset( kTrue );
}

//---------------------------------------------------------------
// SpellChangeObserver::AutoAttach: 
//---------------------------------------------------------------

void SpellChangeObserver::AutoAttach()
{
	if( !fAttached )
	{
		INHERITED::AutoAttach();
		this->AutoAttachToTextWalker();
	}
}

//---------------------------------------------------------------
// SpellChangeObserver::AutoDetach: 
//---------------------------------------------------------------

void SpellChangeObserver::AutoDetach()
{
	if( fAttached )
	{
		this->AutoDetachFromTextWalker();
		INHERITED::AutoDetach();
	}
}

//---------------------------------------------------------------
// SpellChangeObserver::ApplyToFocus
//---------------------------------------------------------------

bool16 SpellChangeObserver::ApplyToFocus()
{
	if( this->IsControlSelected() )
	{
		InterfacePtr<ITextWalker>pWalker( this->QueryTextWalker() );
		if( pWalker )
		{
			// if the dialog opens with a misspelled word we want to be in Change mode, after that we will be in kStart.
			if( pWalker &&  pWalker->IsWalking()  )
			{
				this->NotifyObserver( kSpellPanelMsgApplyToText );
// done in SpellWordObserver::ApplyFocus()				this->NotifyObserver( kSpellPanelMsgResumeChecking );
			}
			else
				this->NotifyObserver( kSpellPanelMsgSetToStart );
		}
		this->DeselectControl();
	}
	return kTrue;
}

//---------------------------------------------------------------
// SpellChangeObserver::Update
//---------------------------------------------------------------

void	SpellChangeObserver::Update( const ClassID& theChange, ISubject*theSubject, const PMIID &protocol, void* changedBy )
{
	// ==> Please update GetObserverInfo()  <==
	if( this->IsMuted() )
		return;

	if( protocol == IID_ITEXTWALKERMSG  )
	{
		const SpellPanelObserverMuter aMuter( this );

		// sent by SpellCheckWalkerClient::NotifyDoSuspend()
		if( theChange == kTextWalkerOnHaltMessage || theChange == kTextWalkerOnSuspendMessage )
		{
			// if the word is in the selection, there is no change
			InterfacePtr<IControlView>pView( this, IID_ICONTROLVIEW );
			if( pView )
			{
				const bool16 bEnable = theChange == kTextWalkerOnSuspendMessage;
				if( pView->IsEnabled() !=  bEnable )
					pView->Enable( bEnable );
			}
			return;
		}
	}

	if( protocol == IID_ISPELLPANELMSG  )
	{
		const SpellPanelObserverMuter aMuter( this );

		// sent by SpellChangeObserver::SetMode()
		if( theChange == kSpellPanelMsgReadyToChange || theChange == kSpellPanelMsgReadyToStart )
		{
			// if the word is in the selection, there is no change
			InterfacePtr<IControlView>pView( this, IID_ICONTROLVIEW );
			if( pView )
			{
				const bool16 bEnable = theChange == kSpellPanelMsgReadyToChange;
				if( pView->IsEnabled() !=  bEnable )
					pView->Enable( bEnable );
			}
			return;
		}

		// sent by SpellSkipObserver::SetMode()
		if( theChange == kSpellPanelMsgChangeEnabled || theChange == kSpellPanelMsgChangeDisabled )
		{
			// if the word is in the selection, there is no change
			InterfacePtr<IControlView>pView( this, IID_ICONTROLVIEW );
			if( pView )
			{
				bool16 bEnable = theChange == kSpellPanelMsgChangeEnabled;

				// One last check - we have to make sure the selection isn't locked.  If is is, we
				// always disable
				InterfacePtr<ISelectionManager> selMgr ((ISelectionManager*)Utils<ISelectionUtils>()->QueryActiveSelection());
				InterfacePtr<ITextEditSuite> editSuite (selMgr, UseDefaultIID());
				bool16 storyLocked = (editSuite && !editSuite->CanEditText());
				
				if (storyLocked) bEnable = kFalse;
				
				if( pView->IsEnabled() !=  bEnable )
					pView->Enable( bEnable );
			}
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
// SpellChangeObserver::NotifyObserver
//---------------------------------------------------------------

// see SpellWordObserver::NotifyObserver

void	SpellChangeObserver::NotifyObserver( ClassID nMsg )
{
	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
	if( pPanel )
		pPanel->Change( nMsg, IID_ISPELLPANELMSG, this );
}



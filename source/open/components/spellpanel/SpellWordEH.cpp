//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellWordEH.cpp $
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

// ----- Interfaces -----

#include "IEvent.h"
#include "IKeyBoard.h"
#include "IStringData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "IWidgetParent.h"

// ----- Includes -----

#include "keyboarddefs.h"	// kc*
#include "CIDEditBoxEventHandler.h"
#include "Trace.h"

// ----- Utility files -----

#include "EventUtilities.h"

// ----- ID.h files -----

#include "LayoutUIID.h"
#include "SpellPanelID.h"
#include "widgetid.h"


//----------------------------------------------------------------------------------------
// Class SpellWordEventHandler
//----------------------------------------------------------------------------------------

class SpellWordEventHandler : public CIDEditBoxEventHandler
{
	typedef CIDEditBoxEventHandler inherited;
public:
					SpellWordEventHandler(IPMUnknown *boss);

	virtual	bool16	KeyDown( IEvent *e  );

private:
	void			NotifyApplyToText();
	
	ISubject *			QueryPanelSubject();
};

//========================================================================================
// CLASS SpellWordEventHandler
//========================================================================================

CREATE_PMINTERFACE(SpellWordEventHandler, kSpellWordEventHandler)

//---------------------------------------------------------------
// SpellWordEventHandler constructor 
//---------------------------------------------------------------

SpellWordEventHandler::SpellWordEventHandler(IPMUnknown *boss) :
	inherited(boss)
{
}


//----------------------------------------------------------------------------------------
// SpellWordEventHandler::KeyDown
//----------------------------------------------------------------------------------------
// see TextEditor.cpp, TEKeyHandler

bool16 SpellWordEventHandler::KeyDown(IEvent* e )
{
	ASSERT_MSG(e != nil, "e != nil");

	bool16 ret = inherited::KeyDown( e );

	VirtualKey virtualKey = e->GetVirtualKey();
	if (virtualKey == kVirtualReturnKey || virtualKey == kVirtualEnterKey)
	{
		this->NotifyApplyToText();

		ret = kTrue;
	}

	return ret;
}

//---------------------------------------------------------------
// SpellWordEventHandler::NotifyApplyToText
//---------------------------------------------------------------

void	SpellWordEventHandler::NotifyApplyToText()
{
	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
	if( pPanel )
		pPanel->Change( kSpellPanelMsgApplyToText, IID_ISPELLPANELMSG );
}

//---------------------------------------------------------------
// SpellWordEventHandler::QueryPanelSubject
//---------------------------------------------------------------

// see SpellPanelObserver::QueryPanelSubject

ISubject *SpellWordEventHandler::QueryPanelSubject()
{
	InterfacePtr<IWidgetParent>pParent( this, IID_IWIDGETPARENT );	
	if( !pParent )
		return 0;

	InterfacePtr<IPMUnknown>pPanel( pParent->QueryParentFor( IID_IPANELCONTROLDATA ) ); 	
	if( !pPanel )
		return 0;
	
	return (ISubject*)pPanel->QueryInterface( IID_ISUBJECT );
}
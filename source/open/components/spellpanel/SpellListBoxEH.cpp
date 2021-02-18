//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellListBoxEH.cpp $
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

#include "DVListBoxEventHandler.h"
#include "IBoolData.h"	
#include "IListBoxController.h"
#include "IListControlDataOf.h"
#include "IObserver.h"
#include "IStringData.h"
#include "ISubject.h"
#include "ITextControlData.h"	
#include "IWidgetParent.h"
#include "keyboarddefs.h"
#include "EventUtilities.h"
#include "CursorID.h"
#include "SpellPanelID.h"
#include "TextPanelID.h"
#include "widgetid.h"


//----------------------------------------------------------------------------------------
// Class SpellListBoxEH
//----------------------------------------------------------------------------------------

class SpellListBoxEH : public DVListBoxEventHandler
{
	typedef DVListBoxEventHandler inherited;
	
public:
				 SpellListBoxEH(IPMUnknown *boss) : inherited(boss) { ; }
		virtual ~SpellListBoxEH() { ; }

		virtual bool16 		ButtonDblClk(IEvent* e); 
		virtual bool16 		ButtonTrplClk(IEvent* e);
		virtual bool16 		ButtonQuadClk(IEvent* e);
		virtual bool16 		ButtonQuintClk(IEvent* e);
		virtual bool16 		LButtonDn(IEvent* e); 
		virtual bool16		KeyDown(IEvent* e); 

private:
		ISubject *			QueryPanelSubject();
		bool16				Notify( ClassID nMsg );
		
		SpellListBoxEH();
};

//===============================================================
// CLASS SpellListBoxEH
//===============================================================
#pragma mark SpellListBoxEH implementation

CREATE_PMINTERFACE(SpellListBoxEH, kSpellListBoxEH)

//---------------------------------------------------------------
// SpellListBoxEH::LButtonDn
//---------------------------------------------------------------

bool16 SpellListBoxEH::LButtonDn(IEvent* e)
{
	ASSERT_MSG(e != nil, "e != nil");

	bool16 bRet = inherited::LButtonDn( e );
	if (bRet)
		this->Notify( kSpellPanelMsgItemSelected );
	
	return bRet;
}

//---------------------------------------------------------------
// SpellListBoxEH::ButtonDblClk
//---------------------------------------------------------------
// HH 2/23/99	We no longer call the inherited ButtonDblClk and
//				we return true because we have handled the event
// HH 3/15/99	Now call the inherited LButtonDn and check to see 
//				if the double click was in the list rather than
//				on the scroll bar
bool16 SpellListBoxEH::ButtonDblClk(IEvent* e)
{
	bool16 bRet = inherited::LButtonDn( e );
	if (bRet)
		this->Notify( kSpellPanelMsgItemExecuted );
	
	return kTrue;	/* indicate we've handled the event */
}

bool16 SpellListBoxEH::ButtonTrplClk(IEvent* e)
{
	return kTrue;	/* indicate we've handled the event */
}

bool16 SpellListBoxEH::ButtonQuadClk(IEvent* e)
{
	return kTrue;	/* indicate we've handled the event */
}

bool16 SpellListBoxEH::ButtonQuintClk(IEvent* e)
{
	return kTrue;	/* indicate we've handled the event */
}

//---------------------------------------------------------------
// SpellListBoxEH::KeyDown
//---------------------------------------------------------------
bool16 SpellListBoxEH::KeyDown(IEvent* e)
{
	bool16 result = kFalse;

	VirtualKey virtualKey = e->GetVirtualKey();
	if (virtualKey == kVirtualReturnKey || virtualKey == kVirtualEnterKey)
	{
		// Prevent following KeyCmd event in case alert comes up.
		::RemoveNextKeyCmd(e);

		// don't pass the Return key on to the edit control's WNDPROC or else it'll beep 
		e->SetSystemHandledState(IEvent::kDontCall);	

		this->Notify( kSpellPanelMsgItemExecuted );
		return kTrue;
	}

	return inherited::KeyDown(e);
}

//---------------------------------------------------------------
// SpellListBoxEH::QueryPanelSubject
//---------------------------------------------------------------

// see SpellPanelObserver::QueryPanelSubject

ISubject *SpellListBoxEH::QueryPanelSubject()
{
	InterfacePtr<IPMUnknown>pThisPanel( this, IID_ITEXTTARGETSERVER ); 	
	if( pThisPanel )
		return (ISubject*)this->QueryInterface( IID_ISUBJECT );

	InterfacePtr<IWidgetParent>pParent( this, IID_IWIDGETPARENT );	
	if( !pParent )
		return nil;

	InterfacePtr<IPMUnknown>pPanel( pParent->QueryParentFor( IID_IPANELCONTROLDATA ) ); 	
	if( !pPanel )
		return nil;
	
	return (ISubject*)pPanel->QueryInterface( IID_ISUBJECT );
}

//---------------------------------------------------------------
// SpellListBoxEH::Notify
//---------------------------------------------------------------

bool16 SpellListBoxEH::Notify( ClassID nMsg )
{
	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
	InterfacePtr< IListControlDataOf<PMString> >pData( this, IID_ILISTCONTROLDATA );
	InterfacePtr<IListBoxController> controller( this, IID_ILISTBOXCONTROLLER );
	InterfacePtr<IObserver>pObserver( this, IID_IOBSERVER );

	if( !pPanel || !pObserver || !pData || pData->Length() == 0 || controller->GetSelected() < 0 )
		return kFalse;
			
	pObserver->Update( kListSelectionChangedByUserMessage, nil, IID_ILISTCONTROLDATA, this );
	pPanel->Change( nMsg, IID_ISPELLPANELMSG, this );

	return kTrue;
}

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellMisspelledEH.cpp $
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

#include "ISubject.h"
#include "IWidgetParent.h"

#include "CIDEditBoxEventHandler.h"
#include "SpellPanelID.h"
#include "widgetid.h"
#include "TextPanelID.h"

//----------------------------------------------------------------------------------------
// Class SpellMisspelledEH
//----------------------------------------------------------------------------------------

class SpellMisspelledEH : public CIDEditBoxEventHandler
{
	typedef CIDEditBoxEventHandler inherited;
public:
					SpellMisspelledEH(IPMUnknown *boss);

// FIXME_DV: EditBoxEventHandlers don't receive mouse events (they go directly to the platform editboxes)
#if FIXME_DV
	virtual	bool16	LButtonDn( IEvent *pEvent  );
#endif // FIXME_DV

	virtual	bool16	CanHaveKeyFocus() const;

private:
			ISubject *QueryPanelSubject();
			void		NotifySpellWordObserver();
};

//---------------------------------------------------------------
// static functions
//---------------------------------------------------------------

//========================================================================================
// CLASS SpellMisspelledEH
//========================================================================================

CREATE_PMINTERFACE(SpellMisspelledEH, kSpellMisspelledEH)

//---------------------------------------------------------------
// SpellMisspelledEH constructor 
//---------------------------------------------------------------

SpellMisspelledEH::SpellMisspelledEH(IPMUnknown *boss) :
	inherited(boss)
{
}

//----------------------------------------------------------------------------------------
// SpellMisspelledEH::LButtonDn
//----------------------------------------------------------------------------------------
	
// FIXME_DV: EditBoxEventHandlers don't receive mouse events (they go directly to the platform editboxes)
//	Need to determine: 
//		1) Is this behavior really necessary?
//		2) If necessary, could it be implemented some other way, perhaps by watching when the widget gains focus
//
#if FIXME_DV
bool16 SpellMisspelledEH::LButtonDn(IEvent* pEvent )
{
	ASSERT_MSG(pEvent != nil, "pEvent != nil");

	this->NotifySpellWordObserver();
	return inherited::KeyDown( pEvent ); // DV_Note: really? calling inherited::KeyDown? I think this will crash now.
}
#endif // FIXME_DV

//---------------------------------------------------------------
// SpellMisspelledEH::NotifySpellWordObserver
//---------------------------------------------------------------

// see SpellWordObserver::NotifySpellWordObserver

void	SpellMisspelledEH::NotifySpellWordObserver()
{
	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
	if( pPanel )
		pPanel->Change( kSpellPanelMsgResetToMisspelledWord, IID_ISPELLPANELMSG, this );
}


//---------------------------------------------------------------
// SpellMisspelledEH::QueryPanelSubject
//---------------------------------------------------------------

// see SpellPanelObserver::QueryPanelSubject

ISubject *SpellMisspelledEH::QueryPanelSubject()
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
// SpellMisspelledEH::CanHaveKeyFocus
//---------------------------------------------------------------

bool16 SpellMisspelledEH::CanHaveKeyFocus() const
{
	return kFalse;
}

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellTargetServer.cpp $
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

#include "IControlView.h"
#include "IDialog.h"
#include "IDocument.h"

#include "CTextTargetServer.h"
#include "ILayoutUIUtils.h"
#include "SpellPanelID.h"


//----------------------------------------------------------------------------------------
// Class SpellTargetServer
//----------------------------------------------------------------------------------------

class SpellTargetServer : public CTextTargetServer
{
public:
		SpellTargetServer(IPMUnknown *boss  );


protected:
		virtual	bool16 		EnableWidget();
		virtual	bool16 		DisableWidget();
		virtual	void		OnDocumentChange();
};

//========================================================================================
// CLASS SpellTargetServer
//========================================================================================

CREATE_PMINTERFACE(SpellTargetServer, kSpellTargetServer)
#define INHERITED 	CTextTargetServer

//---------------------------------------------------------------
// SpellTargetServer constructor 
//---------------------------------------------------------------

SpellTargetServer::SpellTargetServer(IPMUnknown *boss ) :
	INHERITED(boss)
{
}

//---------------------------------------------------------------
// SpellTargetServer::EnableWidget
//---------------------------------------------------------------

bool16 SpellTargetServer::EnableWidget()
{
	const IDocument *pDoc = Utils<ILayoutUIUtils>()->GetFrontDocument();
	const bool16 bEnable = pDoc != nil;
	if( !bEnable )
		return kFalse;

	return INHERITED::EnableWidget();
}

//---------------------------------------------------------------
// SpellTargetServer::DisableWidget
//---------------------------------------------------------------

bool16 SpellTargetServer::DisableWidget()
{
	// see CTargetServer::EnableWidget(), don't call pView->Enable();

/* HH 6/29/99 removed this call, let the individual observer enable/disable buttons */
//	this->Notify( kMsgDisableWidgetImpl );
	return kFalse;
}

//---------------------------------------------------------------
// SpellTargetServer::OnDocumentChange
//---------------------------------------------------------------

void SpellTargetServer::OnDocumentChange()
{
	INHERITED::OnDocumentChange();
	
	const IDocument *pDoc = Utils<ILayoutUIUtils>()->GetFrontDocument();
	const bool16 bEnable = pDoc != nil;

	InterfacePtr<IControlView>pView( this, IID_ICONTROLVIEW );
	if( pView && pView->IsEnabled() != bEnable )
	{
		if( bEnable )
			INHERITED::EnableWidget();
		else
			INHERITED::DisableWidget();
	}
}

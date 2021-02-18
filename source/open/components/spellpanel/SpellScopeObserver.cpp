//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellScopeObserver.cpp $
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
#include "CWalkerScopeObserver.h"
#include "SpellPanelID.h"

#include "ITextWalker.h"
#include "TextPanelID.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "ISession.h"
#include "TextWalkerServiceProviderID.h"
#include "TextEditorID.h"


#include "IWidgetParent.h"
#include "ISubject.h"
#include "widgetid.h"
#include "ISpellPanelOptions.h"
#include "PreferenceUtils.h"

#include "CmdUtils.h"
#include "ICommand.h"

#include "IDropDownListController.h"
#include "INoteFindChangeSpelling.h"


//----------------------------------------------------------------------------------------
// Class SpellScopeObserver
//----------------------------------------------------------------------------------------

class SpellScopeObserver : public CWalkerScopeObserver
{
public:
		SpellScopeObserver(IPMUnknown *boss  );

protected:	
		virtual	ITextWalker *	QueryTextWalker();
		virtual bool16			UpdateWidget();
		virtual bool16			ChangeWidget();

private:
		ITextWalker *			QueryPanelTextWalker();
		ITextWalker *			QuerySessionTextWalker();		
		ISubject *				QueryPanelSubject();
		ISpellPanelOptions *		QuerySpellPanelOptions();
		bool16				ApplyScopeToWorkSpace( IWalkerScopeFactoryUtils::WalkScopeType nScope );
		void					Update(const ClassID& theChange, ISubject*theSubject, const PMIID &protocol, void* changedBy);
		void					AutoAttach();
		void					AutoDetach();
};

//========================================================================================
// CLASS SpellScopeObserver
//========================================================================================

CREATE_PMINTERFACE(SpellScopeObserver, kSpellScopeObserver)
#define INHERITED 	CWalkerScopeObserver

//---------------------------------------------------------------
// SpellScopeObserver constructor 
//---------------------------------------------------------------

SpellScopeObserver::SpellScopeObserver(IPMUnknown *boss ) :
	INHERITED(boss)
{
}


//---------------------------------------------------------------
// SpellScopeObserver::QuerySessionTextWalker
//---------------------------------------------------------------

ITextWalker *	SpellScopeObserver::QuerySessionTextWalker()
{
	ISession* session = GetExecutionContextSession();
	if( !session )
		return nil;
		
	InterfacePtr<IK2ServiceRegistry>	serviceRegistry(session, IID_IK2SERVICEREGISTRY);
	if( !serviceRegistry )
		return nil;
		
	InterfacePtr<IK2ServiceProvider>serviceProvider(serviceRegistry->QueryServiceProviderByClassID(kTextWalkerService, kTextWalkerServiceProviderBoss));
	if( !serviceProvider )
		return nil;
			
	return (ITextWalker*)serviceProvider->QueryInterface( IID_ITEXTWALKER );
}

//---------------------------------------------------------------
// SpellScopeObserver::QueryPanelTextWalker
//---------------------------------------------------------------

ITextWalker *	SpellScopeObserver::QueryPanelTextWalker()
{
	InterfacePtr<ISubject>pPanel( this->QueryPanelSubject() );
	if( !pPanel )
		return nil;
	return (ITextWalker*)pPanel->QueryInterface( IID_ITEXTWALKER );
}
	
//---------------------------------------------------------------
// SpellScopeObserver::QueryTextWalker
//---------------------------------------------------------------

ITextWalker *	SpellScopeObserver::QueryTextWalker()
{
	ITextWalker *pWalker = this->QueryPanelTextWalker();
	if( !pWalker )
		pWalker = this->QuerySessionTextWalker();
	return pWalker;
}

//---------------------------------------------------------------
// SpellScopeObserver::QueryPanelSubject
//---------------------------------------------------------------

ISubject *SpellScopeObserver::QueryPanelSubject()
{
	InterfacePtr<IWidgetParent>pParent( this, IID_IWIDGETPARENT );	
	if( !pParent )
		return 0;

	InterfacePtr<IPMUnknown> pPanel(pParent->QueryParentFor(IID_ITEXTTARGETSERVER));
	if( !pPanel )
		return 0;
	
	return (ISubject*)pPanel->QueryInterface( IID_ISUBJECT );
}

//---------------------------------------------------------------
// SpellScopeObserver::AutoAttach
//---------------------------------------------------------------

void	SpellScopeObserver::AutoAttach()
{
	InterfacePtr<ISubject> subject(this->QueryPanelSubject());
	if (subject)
	{
		const PMIID nControlID = IID_ISPELLPANELMSG;
		if (!subject->IsAttached(this, nControlID))
			subject->AttachObserver(this, nControlID);

	}
	INHERITED::AutoAttach();
}

//---------------------------------------------------------------
// SpellScopeObserver::AutoDetach
//---------------------------------------------------------------

void	SpellScopeObserver::AutoDetach()
{
	INHERITED::AutoDetach();

	InterfacePtr<ISubject> subject(this->QueryPanelSubject());
	if (subject)
	{
		const PMIID nControlID = IID_ISPELLPANELMSG;
		if (subject->IsAttached(this, nControlID))
		{
			subject->DetachObserver(this, nControlID);
		}
	}
}

//---------------------------------------------------------------
// SpellScopeObserver::Update
//---------------------------------------------------------------

void	SpellScopeObserver::Update(const ClassID& theChange, ISubject*theSubject, const PMIID &protocol, void* changedBy)
{
	if (protocol == IID_ISPELLPANELMSG && theChange == kSpellPanelMsgDirectionHasChanged)
	{
		InterfacePtr<IDropDownListController> listController(this, IID_IDROPDOWNLISTCONTROLLER);
		const int32 listBoxIndex = listController->GetSelected();
		// Change To End of Story to To Beginning of Story & vice-versa.
		this->UpdateWidget();
		if (listBoxIndex < 0)
			listController->Deselect();
		else
			listController->Select(listBoxIndex);
	}
	HandleSelectionUpdate(theChange, theSubject, protocol, changedBy);
}

//---------------------------------------------------------------
// SpellScopeObserver::QuerySpellPanelOptions
//---------------------------------------------------------------

ISpellPanelOptions *	SpellScopeObserver::QuerySpellPanelOptions()
{
	return (ISpellPanelOptions*)::QuerySessionPreferences( IID_ISPELLPANELOPTIONS );
}

//---------------------------------------------------------------
// SpellScopeObserver::ApplyScopeToWorkSpace
//---------------------------------------------------------------

bool16 SpellScopeObserver::ApplyScopeToWorkSpace( IWalkerScopeFactoryUtils::WalkScopeType nScope )
{
	InterfacePtr<ISpellPanelOptions> pSpellPanelOptions( this->QuerySpellPanelOptions() );	
	if( !pSpellPanelOptions || pSpellPanelOptions->GetFindChangeScope() == nScope )
		return kFalse;

	InterfacePtr<ICommand>pApplyOptionsCmd( CmdUtils::CreateCommand( kApplySpellPanelOptionsCmdBoss ) );
	InterfacePtr<ISpellPanelOptions>pCmdData( pApplyOptionsCmd, IID_ISPELLPANELOPTIONS );
	if( !pApplyOptionsCmd || !pCmdData )
		return kFalse;

	pCmdData->CopyFrom( pSpellPanelOptions );
	pCmdData->SetFindChangeScope( nScope );
	
	CmdUtils::ExecuteCommand( pApplyOptionsCmd );

	return kTrue;
}


//---------------------------------------------------------------
// SpellScopeObserver::UpdateWidget
//---------------------------------------------------------------

bool16 SpellScopeObserver::UpdateWidget()
{
	InterfacePtr<INoteFindChangeSpelling> fcs(GetExecutionContextSession(), UseDefaultIID());
	ASSERT(fcs!=nil);

	// used when determining if Selection scope should be allowed for deleted text and inline notes
	fcs->SetScopeWidgetToUpdate(INoteFindChangeSpelling::kSpellingScopeWidget);

	if( !INHERITED::UpdateWidget() )
	{
		fcs->SetScopeWidgetToUpdate(INoteFindChangeSpelling::kInvalidScopeWidget);
		return kFalse;
	}
	
	InterfacePtr<const IDropDownListController> listController(this, IID_IDROPDOWNLISTCONTROLLER);
	const int32 listBoxIndex = listController->GetSelected();
	const IWalkerScopeFactoryUtils::WalkScopeType nScope = this->IndexToScope( listBoxIndex );

	this->ApplyScopeToWorkSpace( nScope );

	fcs->SetScopeWidgetToUpdate(INoteFindChangeSpelling::kInvalidScopeWidget);
	return kTrue;
}

//---------------------------------------------------------------
// SpellScopeObserver::ChangeWidget
//---------------------------------------------------------------

bool16 SpellScopeObserver::ChangeWidget()
{
	if( !INHERITED::ChangeWidget() )
		return kFalse;
	
	InterfacePtr<const IDropDownListController> listController(this, IID_IDROPDOWNLISTCONTROLLER);
	const int32 listBoxIndex = listController->GetSelected();
	const IWalkerScopeFactoryUtils::WalkScopeType nScope = this->IndexToScope( listBoxIndex );

	this->ApplyScopeToWorkSpace( nScope );
	
	return kTrue;
}


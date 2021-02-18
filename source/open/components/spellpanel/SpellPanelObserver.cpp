//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellPanelObserver.cpp $
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
//  
//  see TextWidgetObserver and StandOffWidgetObserver
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IActiveContext.h"
#include "IApplication.h"
#include "IBooleanControlData.h"
#include "IComposeScanner.h"
#include "IControlView.h"
#include "IDocument.h"
#include "IDocumentLayer.h"
#include "IDocumentList.h"
#include "IEditBoxAttributes.h"
#include "IEventHandler.h"
#include "IFrameList.h"
#include "IGeometry.h"
#include "IGraphicFrameData.h"
#include "IHierarchy.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "IKeyBoard.h"
#include "ILanguage.h"
#include "ILayoutCmdData.h"
#include "ILayoutControlData.h"
#include "ILinguisticMgr.h"
#include "IObserver.h"
#include "IPanelControlData.h"
#include "IPMUnknown.h"
#include "IPMUnknownData.h"
#include "ISpellCheckWalkerData.h"
#include "ISpread.h"
#include "IStoryList.h"
#include "IStringData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITextEditor.h"
#include "ITextFocusManager.h"
#include "ITextModel.h"
#include "ITextTarget.h"
#include "ITextWalker.h"
#include "ITool.h"
#include "ITriStateControlData.h"
#include "IWidgetCreator.h"
#include "IWidgetParent.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "SpellPanelObserver.h"
#include "TextWalkerObserver.h"
#include "WideString.h"
#include "WritingModeUIID2.h"

// ----- Utility files -----

#include "ITextWalkerSelectionUtils.h"
#include "ILayoutUIUtils.h"		// for queryselection
#include "PreferenceUtils.h"
#include "ISelectionUtils.h"
#include "Utils.h"

// ----- ID.h files -----

#include "LayoutUIID.h"
#include "LinguisticID.h"
#include "SpellPanelID.h"
#include "TextWalkerServiceProviderID.h"
#include "widgetid.h"


//---------------------------------------------------------------
// class LockUpdate
//---------------------------------------------------------------

class LockUpdate
{
public:
	inline	LockUpdate( bool16 *pInUpdate )  { fInUpdate = pInUpdate; *fInUpdate = kTrue; }
	inline	~LockUpdate()  { *fInUpdate = kFalse; }

private:
	bool16		*fInUpdate;
};

//========================================================================================
// CLASS SpellPanelObserverData
//========================================================================================

//---------------------------------------------------------------
// SpellPanelObserverData constructor
//---------------------------------------------------------------

SpellPanelObserverData::SpellPanelObserverData(IPMUnknown *boss) :
	CObserver(boss)
{
}

//========================================================================================
// CLASS SpellPanelObserver
//========================================================================================

// CREATE_PMINTERFACE(SpellPanelObserver, kSpellPanelObserver)
#define INHERITED 	SpellPanelObserverData

//---------------------------------------------------------------
// SpellPanelObserver constructor
//---------------------------------------------------------------

SpellPanelObserver::SpellPanelObserver(IPMUnknown *boss) :
	INHERITED(boss),
	fMute( 0 )
{
	fAttached = fInUpdate = fInApplyToWidget = kFalse;
}

//---------------------------------------------------------------
// SpellPanelObserver destructor
//---------------------------------------------------------------

SpellPanelObserver::~SpellPanelObserver()
{
	ASSERT_MSG( fAttached == 0, "Observer still attached." );
	ASSERT_MSG( fMute == 0, "SpellPanelObserver - unbalanced mute." );

}

//---------------------------------------------------------------
// SpellPanelObserver::AutoAttachToTextWalker
//---------------------------------------------------------------

void SpellPanelObserver::AutoAttachToTextWalker()
{
	InterfacePtr<ITextWalker>pWalker( this->QueryTextWalker() );
	if( pWalker )
	{
		InterfacePtr<ISubject> pWalkerSubject( pWalker, IID_ISUBJECT );
		if( pWalkerSubject && !pWalkerSubject->IsAttached( this, IID_ITEXTWALKERMSG ) )
			pWalkerSubject->AttachObserver( this, IID_ITEXTWALKERMSG );
	}
}

//---------------------------------------------------------------
// SpellPanelObserver::AutoDetachFromTextWalker
//---------------------------------------------------------------

void SpellPanelObserver::AutoDetachFromTextWalker()
{
	InterfacePtr<ITextWalker>pWalker( this->QueryTextWalker() );
	if( pWalker )
	{
		InterfacePtr<ISubject> pWalkerSubject( pWalker, IID_ISUBJECT );
		if( pWalkerSubject && pWalkerSubject->IsAttached( this, IID_ITEXTWALKERMSG ) )
			pWalkerSubject->DetachObserver( this, IID_ITEXTWALKERMSG );
	}
}

//---------------------------------------------------------------
// SpellPanelObserver::QuerySessionTextWalker
//---------------------------------------------------------------

ITextWalker *	SpellPanelObserver::QuerySessionTextWalker()
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
// SpellPanelObserver::QueryPanelTextWalker
//---------------------------------------------------------------

ITextWalker *	SpellPanelObserver::QueryPanelTextWalker()
{
	InterfacePtr<ISubject>pPanel( this->QueryPanelSubject() );
	if( !pPanel )
		return nil;
	return (ITextWalker*)pPanel->QueryInterface( IID_ITEXTWALKER );
}

//---------------------------------------------------------------
// SpellPanelObserver::QueryTextWalker
//---------------------------------------------------------------

ITextWalker *	SpellPanelObserver::QueryTextWalker()
{
	ITextWalker *pWalker = this->QueryPanelTextWalker();
	if( !pWalker )
		pWalker = this->QuerySessionTextWalker();
	return pWalker;
}


//---------------------------------------------------------------
// SpellPanelObserver::QueryLinguisticMgr
//---------------------------------------------------------------

ILinguisticMgr *SpellPanelObserver::QueryLinguisticMgr()
{
	InterfacePtr<IK2ServiceRegistry>	pServices(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
	InterfacePtr<IK2ServiceProvider>pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
	if( !pLinguMgrService )
		return nil;

	return (ILinguisticMgr*)pLinguMgrService->QueryInterface( IID_ILINGUISTICMGR );
}

//---------------------------------------------------------------
// SpellPanelObserver::QuerySpellPanelOptions
//---------------------------------------------------------------

ISpellPanelOptions *	SpellPanelObserver::QuerySpellPanelOptions()
{
	return (ISpellPanelOptions*)::QuerySessionPreferences( IID_ISPELLPANELOPTIONS );
}

//---------------------------------------------------------------
// SpellPanelObserver::AutoAttach:
//---------------------------------------------------------------

void SpellPanelObserver::AutoAttach()
{
	if( fAttached )
		return;
	fAttached = kTrue;

	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if( subject )
	{
		const PMIID nControlID = this->GetControlID();
		if( !subject->IsAttached( this, nControlID ) )
			subject->AttachObserver(this, nControlID );

	}

	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
	if( pPanel && !pPanel->IsAttached( this, IID_ISPELLPANELMSG ) )
		pPanel->AttachObserver( this, IID_ISPELLPANELMSG );

	const SpellPanelObserverMuter aMuter( this );

	this->SetupWidget();

	INHERITED::AutoAttach();
}


//---------------------------------------------------------------
// SpellPanelObserver::AutoDetach:
//---------------------------------------------------------------

void SpellPanelObserver::AutoDetach()
{
	if( !fAttached )
		return;
	fAttached = kFalse;

	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
	if( pPanel && pPanel->IsAttached( this, IID_ISPELLPANELMSG ) )
		pPanel->DetachObserver( this, IID_ISPELLPANELMSG );

	INHERITED::AutoDetach();

	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
	{
		const PMIID nControlID = this->GetControlID();
		if( subject->IsAttached( this, nControlID ) )
		{
			subject->DetachObserver(this, nControlID );
		}
	}

}

//---------------------------------------------------------------
// SpellPanelObserver::Update:
//---------------------------------------------------------------

void SpellPanelObserver::Update(const ClassID& theChange, ISubject*, const PMIID& protocol, void* changedBy)
{
	// ==> Please update GetObserverInfo()  <==

	if( fInUpdate || this->IsMuted() )
		return;

	LockUpdate aLock( &fInUpdate );

	if (protocol == IID_ITEXTWALKERMSG)
	{
		switch( theChange.Get() )
		{
			//hkhalfal Oct 09 2000: Initialization and termination of the text walker
			// terminator will happen on start/end of walker. Ditto saving the selections.
			case  kTextWalkerOnStartMessage:
			{
				ITextWalker *pWalker = (ITextWalker *)changedBy;
				if (pWalker)
				{
					InterfacePtr<ITextWalkerSelectionUtils>twSelectUtils(pWalker, IID_ITEXTWALKERSELECTIONUTILS);
					twSelectUtils->InitTextWalkerTerminator();
					twSelectUtils->SwitchToTextSelection ();	// from FindPanelObserver.cpp
//					twSelectUtils->SaveSelectionsSnapshot ();
				}
				break;
			}
			case  kTextWalkerOnEndMessage:
			{
				ITextWalker *pWalker = (ITextWalker *)changedBy;
				if (pWalker)
				{
					InterfacePtr<ITextWalkerSelectionUtils>twSelectUtils(pWalker, IID_ITEXTWALKERSELECTIONUTILS);
					twSelectUtils->RetainLastWindow();
					twSelectUtils->TerminateTextWalkerTerminator();
//					twSelectUtils->RestoreSelectionsSnapshot ();
				}
				break;
			}
			default:
				break;
		}

		return;
	}

	if( protocol != this->GetControlID() )
	{
		// INHERITED::Update(theChange, theSubject, protocol, changedBy);
		return;
	}

	if( theChange == kMsgSpellSetupWidget )
	{
		this->SetupWidget();
		return;
	}


/* TODO:
	if( theChange == kMsgSpellUpdateWidget )
	{
		this->DoApplyToWidget(  (IFocusCache*)changedBy  );
		return;
	}
*/

	this->DoApplyToFocus();
}

//---------------------------------------------------------------
// SpellPanelObserver::SetupWidget
//---------------------------------------------------------------

bool16 SpellPanelObserver::SetupWidget()
{
	this->SetReset( kTrue );
	return kTrue;
}

//---------------------------------------------------------------
// SpellPanelObserver::ApplyToWidget
//---------------------------------------------------------------

bool16 SpellPanelObserver::ApplyToWidget()
{
	bool16 bChanged = kFalse;
	return bChanged;
}

//---------------------------------------------------------------
// SpellPanelObserver::ApplyToFocus
//---------------------------------------------------------------

bool16 SpellPanelObserver::ApplyToFocus()
{
	ASSERT_MSG( kFalse, "Please override SpellPanelObserver::ApplyToFocus()" );
	return kFalse;
}

//---------------------------------------------------------------
// SpellPanelObserver::DoApplyToWidget
//---------------------------------------------------------------

bool16	SpellPanelObserver::DoApplyToWidget()
{
	ASSERT_MSG( !fInApplyToWidget, "SpellPanelObserver - recursive ApplyToWidget?" );

	const SpellPanelObserverMuter aMuter( this );
	fInApplyToWidget = kTrue;
	const bool16 bRet = this->ApplyToWidget();
	if( bRet )
	{
		InterfacePtr<IControlView> pView( this, IID_ICONTROLVIEW );
		if( pView )
			pView->ShowView();
	}
	fInApplyToWidget = kFalse;
	return bRet;
}

//---------------------------------------------------------------
// SpellPanelObserver::DoApplyToFocus
//---------------------------------------------------------------

bool16	SpellPanelObserver::DoApplyToFocus()
{
	if( fInApplyToWidget )
		return kFalse;

/*
	TODO:

	// call the ApplyToFocus() of derived class
	InterfacePtr<IWidgetParent>		parent(this, IID_IWIDGETPARENT);
	InterfacePtr<ITextFocusData>	focusData((ITextFocusData*)parent->QueryParentFor(IID_ITEXTFOCUSDATA));
	ITextFocus	*focus = (ITextFocus*)focusData->GetFocus();
	if (!focus)
	{
		InterfacePtr<IWorkspace>pWorkSpace( Utils<ILayoutUIUtils>()->QueryActiveWorkspace() );
		if( !pWorkSpace )
			return kFalse;

		return this->ApplyToPreferences( pWorkSpace );
	}
*/

	return this->ApplyToFocus();
}

//---------------------------------------------------------------
// SpellPanelObserver::QueryPanelSubject
//---------------------------------------------------------------

ISubject *SpellPanelObserver::QueryPanelSubject() const
{
	InterfacePtr<IPMUnknown>pThisPanel( this, IID_ITEXTTARGETSERVER );
	if( pThisPanel )
		return (ISubject*)this->QueryInterface( IID_ISUBJECT );

	InterfacePtr<IWidgetParent>pParent( this, IID_IWIDGETPARENT );
	if( !pParent )
		return nil;

	InterfacePtr<IPMUnknown>pPanel( pParent->QueryParentFor( IID_ITEXTTARGETSERVER ) );
	if( !pPanel )
		return nil;

	return (ISubject*)pPanel->QueryInterface( IID_ISUBJECT );
}

//---------------------------------------------------------------
// SpellPanelObserver::ApplyToPreferences
//---------------------------------------------------------------

bool16 SpellPanelObserver::ApplyToPreferences()
{
	return kFalse;
}

//---------------------------------------------------------------
// SpellPanelObserver::Mute
//---------------------------------------------------------------

void SpellPanelObserver::Mute( bool16 bOn )
{
	if( bOn )
		++fMute;
	else
	{
		if( fMute > 0 )
			--fMute;
		else
			ASSERT_MSG( kFalse, "SpellPanelObserver - this has not been muted." );
	}
}

//---------------------------------------------------------------
// SpellPanelObserver::IsMuted
//---------------------------------------------------------------

bool16 SpellPanelObserver::IsMuted() const
{
	return fMute > 0;
}

//---------------------------------------------------------------
// SpellPanelObserver::IsControlSelected
//---------------------------------------------------------------

bool16 SpellPanelObserver::IsControlSelected() const
{
	// WidgetBin doesn't support const programming.
	SpellPanelObserver *pThis = (SpellPanelObserver*)this;

	InterfacePtr<ITriStateControlData>pTriData( pThis, IID_ITRISTATECONTROLDATA );
	if( pTriData )
		return pTriData->IsSelected();

	InterfacePtr<IBooleanControlData>pBoolData( pThis, IID_IBOOLEANCONTROLDATA );
	if( pBoolData )
		return pBoolData->IsSelected();

	return kFalse;
}

//---------------------------------------------------------------
// SpellPanelObserver::DeselectControl
//---------------------------------------------------------------

void	SpellPanelObserver::DeselectControl()
{
	bool16 bSelected = kFalse;
	InterfacePtr<ITriStateControlData>pTriData( this, IID_ITRISTATECONTROLDATA );
	if( pTriData )
	{
		if( pTriData->IsSelected()  )
			pTriData->Deselect();
		return;
	}

	InterfacePtr<IBooleanControlData>pBoolData( this, IID_IBOOLEANCONTROLDATA );
	if( pBoolData )
	{
		if(  pBoolData->IsSelected() )
			pBoolData->Deselect();
	}
}

//---------------------------------------------------------------
// SpellPanelObserver::QueryWordToSpell
//---------------------------------------------------------------

IStringData *SpellPanelObserver::QueryWordToSpell()
{
	InterfacePtr<ISubject>pPanel( this->QueryPanelSubject() );
	if( !pPanel )
		return nil;

	IStringData *pWord = pPanel ? (IStringData *)pPanel->QueryInterface( IID_IWORDTOSPELL ) : nil;
	ASSERT_MSG( pWord != nil, "SpellPanelObserver - missing IID_IWORDTOSPELL at panel boss." );
	return pWord;
}

const PMString &	SpellPanelObserver::GetUserCorrectedWord() const
{
	InterfacePtr<ISubject>pPanel( this->QueryPanelSubject() );
	if( !pPanel )
		return kNullString;

	InterfacePtr<IPanelControlData>    iPanelData (pPanel, UseDefaultIID()); 
	IControlView*    theControl = iPanelData->FindWidget (kSpellAlternativeEditBoxID);         
	InterfacePtr<ITextControlData> correctedWord(theControl, IID_ITEXTCONTROLDATA); 
	return correctedWord->GetString();
}

//---------------------------------------------------------------
// SpellPanelObserver::QueryCurrentLanguage
//---------------------------------------------------------------

ILanguage *SpellPanelObserver::QueryCurrentLanguage()
{
	InterfacePtr<ISubject>pPanel( this->QueryPanelSubject() );
	if( !pPanel )
		return nil;

	ILanguage *pLanguage = (ILanguage *)pPanel->QueryInterface( IID_ILANGUAGE );
	ASSERT_MSG( pLanguage != nil, "SpellPanelObserver - missing IID_ILANGUAGE at panel boss." );
	return pLanguage;
}

//---------------------------------------------------------------
// SpellPanelObserver::GetTarget()
//---------------------------------------------------------------

IPMUnknown* SpellPanelObserver::GetTarget()
{
	InterfacePtr<ISubject>pPanel( this->QueryPanelSubject() );
	if( !pPanel )
		return nil;

    InterfacePtr<IPMUnknownData> pmUnknownData(pPanel, IID_IPMUNKNOWNDATA);
    IPMUnknown* theObject = pmUnknownData->GetPMUnknown();

	return theObject;
}

//---------------------------------------------------------------
// SpellPanelObserver::SetTarget
//---------------------------------------------------------------

void SpellPanelObserver::SetTarget(IPMUnknown *target)
{
 	InterfacePtr<ISubject>pPanel( this->QueryPanelSubject() );
	if( !pPanel )
		return;

    InterfacePtr<IPMUnknownData> pmUnknownData(pPanel, IID_IPMUNKNOWNDATA);
    pmUnknownData->SetPMUnknown(target);
}

IUserDictService* SpellPanelObserver::QueryUserDictService(void)
{
	InterfacePtr<const ISubject>pPanel(this->QueryPanelSubject() );
	InterfacePtr<const ISpellCheckWalkerData>pWalkerData( pPanel, UseDefaultIID() );
	InterfacePtr<const ILanguage>pLanguage( pWalkerData, IID_ILANGUAGE );
	InterfacePtr<ILinguisticMgr>pLinguMgr( this->QueryLinguisticMgr() );
	if( !pLinguMgr || !pLanguage )
		return nil;
	return pLinguMgr->QueryUserDictService(pLanguage);
}




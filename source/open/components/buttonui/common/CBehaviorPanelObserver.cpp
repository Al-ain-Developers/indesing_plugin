//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/common/CBehaviorPanelObserver.cpp $
//  
//  Owner: Mark VerMurlen
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

// ----- Interface Includes -----

#include "IAppearanceSuite.h"
#include "IApplication.h"
#include "IBehaviorData.h"
#include "IBehaviorSuite.h"
#include "ICommandSequence.h"
#include "IFormFieldSuite.h"
#include "IIntData.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "IPanelMgr.h"
#include "ISubject.h"
#include "IUIDData.h"


// ----- Implementation Includes -----
#include "CBehaviorPanelObserver.h"

#include "FormFieldUIUtils.h"
#include "SelectionUtils.h"

#include "BehaviorID.h"
#include "FormFieldUIID.h"

//========================================================================================
// METHODS CBehaviorPanelObserver
//========================================================================================

//----------------------------------------------------------------------------------------
// CBehaviorPanelObserver constructor 
//----------------------------------------------------------------------------------------

CBehaviorPanelObserver::CBehaviorPanelObserver(IPMUnknown *boss) : 
	CActiveSelectionObserver(boss),
	isAttached(false),
	isInitialized(false)
{
}
	
//----------------------------------------------------------------------------------------
// CBehaviorPanelObserver::~CBehaviorPanelObserver
//----------------------------------------------------------------------------------------

CBehaviorPanelObserver::~CBehaviorPanelObserver()
{
}

//----------------------------------------------------------------------------------------
// CBehaviorPanelObserver::AutoAttach
//----------------------------------------------------------------------------------------

void CBehaviorPanelObserver::AutoAttach()
{
	CActiveSelectionObserver::AutoAttach();
	
	InterfacePtr<IUIDData> activeBehavior(FormFieldUIUtils::QueryActiveBehavior());
	if ( activeBehavior )
	{
		InterfacePtr<IBehaviorData> iBehaviorData(activeBehavior->GetRef(), UseDefaultIID());
		if ( iBehaviorData )
		{
			InitializeFieldsFromActionData(iBehaviorData);
			isInitialized = true;
		}
	}
}

//----------------------------------------------------------------------------------------
// CBehaviorPanelObserver::AutoDetach
//----------------------------------------------------------------------------------------

void CBehaviorPanelObserver::AutoDetach()
{
	CActiveSelectionObserver::AutoDetach();
}

//----------------------------------------------------------------------------------------
// CBehaviorPanelObserver::HandleSelectionChanged
//----------------------------------------------------------------------------------------

void CBehaviorPanelObserver::HandleSelectionChanged (const ISelectionMessage* inSelMsg)
{
	CActiveSelectionObserver::HandleSelectionChanged(inSelMsg);
}

//----------------------------------------------------------------------------------------
// CBehaviorPanelObserver::HandleSelectionAttributeChanged
//----------------------------------------------------------------------------------------

void CBehaviorPanelObserver::HandleSelectionAttributeChanged (const ISelectionMessage* inSelMsg)
{
	CActiveSelectionObserver::HandleSelectionChanged(inSelMsg);
}

//----------------------------------------------------------------------------------------
// CBehaviorPanelObserver::HandleSelectionUpdate
//----------------------------------------------------------------------------------------

void CBehaviorPanelObserver::HandleSelectionUpdate
	(
	const ClassID&	inBossClassID, 
	ISubject* inSubject, 
	const PMIID& 	inProtocol,
	void* 			inMessage
	)
{
	static bool bUpdating = false;

	InterfacePtr<const IApplication> theApp (GetExecutionContextSession()->QueryApplication ());
	InterfacePtr<const IPanelMgr> panelMgr( theApp->QueryPanelManager() );
	bool16 isPanelVisible = panelMgr->IsPanelWithWidgetIDShown(kAppearanceParentWidgetId);
	
	// Bug# 3649906: Update only if the panel is still visible.
	if ( isInitialized && !bUpdating && isPanelVisible )
	{
		bUpdating = true;

		InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
		InterfacePtr<IAppearanceSuite> iAppearanceSuite( FormFieldUIUtils::QueryAppearanceSuite() );
		InterfacePtr<IBehaviorSuite> actionSuite( SelectionUtils::QuerySuite<IBehaviorSuite>() );
		
		if (iFormSuite && iFormSuite->IsFieldSelection() && !iFormSuite->IsFieldSelectionOfType(kMultiStateObjectItemBoss) && actionSuite )
		{
			InterfacePtr<IUIDData> activeBehavior(FormFieldUIUtils::QueryActiveBehavior());
			InterfacePtr<IIntData> behaviorTypeIntData(activeBehavior, UseDefaultIID());
			InterfacePtr<IBehaviorData> iBehaviorData(activeBehavior->GetRef(), UseDefaultIID());
			if ( iBehaviorData )
			{
				//int32 actionType =  behaviorTypeIntData->GetInt();
				int32 actionType = iBehaviorData->GetAction();
				
				InterfacePtr<IK2ServiceRegistry> servReg(GetExecutionContextSession(), UseDefaultIID());
				int32 serviceCount = servReg->GetServiceProviderCount(kBehaviorService);
				
				for(int32 serviceIndex = 0; serviceIndex < serviceCount; serviceIndex++)
				{
					InterfacePtr<IK2ServiceProvider> provider(servReg->QueryNthServiceProvider(kBehaviorService, serviceIndex));
					InterfacePtr<IBehaviorData> actionData(provider, UseDefaultIID());
					if (actionData && actionData->GetAction() == actionType)
					{
						ASSERT(iBehaviorData->GetAction() == actionType);
						actionData->Enable(iBehaviorData->IsEnabled());
						actionData->SetOwner(iBehaviorData->GetOwner());
						actionData->Copy(iBehaviorData);
						ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__) ; 
						if ( ApplyFieldsToActionData(actionData) )
							actionSuite->ReplaceAction(FormFieldUIUtils::GetSelectedEvent(this), activeBehavior->GetRef().GetUID(), actionData);
						CmdUtils::EndCommandSequence(cmdSeq); 

						break;
					}
				}
			}
		}
			
		bUpdating = false;
		return;
	}
	
	ActiveSelectionObserver::HandleSelectionUpdate(inBossClassID, inSubject, inProtocol, inMessage);
}


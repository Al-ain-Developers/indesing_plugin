//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/LiquidLayoutPanelMenuComponent.cpp $
//  
//  Owner: Dave Stephens
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

// ----- Interface files -----
#include "IApplication.h"
#include "IActionComponent.h"
#include "IActionManager.h"
#include "IActionStateList.h"
#include "IActiveContext.h"
#include "IControlView.h"
#include "IDialog.h"
#include "IDialogCreator.h"
#include "IDialogMgr.h"
#include "IDocument.h"
#include "IDocumentPresentation.h"
#include "IGalleyUtils.h"
#include "IPanelMgr.h"
#include "ITool.h"
#include "IToolBoxUtils.h"
#include "IWidgetParent.h"

// ----- Include files -----
#include "CActionComponent.h"
#include "CoreResTypes.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"

// ----- Utility files -----
#include "Utils.h"

// ----- ID files -----
#include "AutoLayoutPanelID.h"
#include "DynamicDocumentsUIID.h"
#include "SpreadUIID.h"

//========================================================================================
// CLASS LiquidLayoutPanelMenuComponent
//========================================================================================
class LiquidLayoutPanelMenuComponent : public CActionComponent
{
	public:
		LiquidLayoutPanelMenuComponent(IPMUnknown *boss);
		
		virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);
		virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
};

CREATE_PMINTERFACE(LiquidLayoutPanelMenuComponent, kLiquidLayoutPanelMenuComponentImpl)

//---------------------------------------------------------------
// Constructor
//---------------------------------------------------------------
LiquidLayoutPanelMenuComponent::LiquidLayoutPanelMenuComponent(IPMUnknown *boss) :
	CActionComponent(boss)
{
}

//---------------------------------------------------------------
// LiquidLayoutPanelMenuComponent::UpdateActionStates()
//---------------------------------------------------------------
void LiquidLayoutPanelMenuComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{		
	int32 count = listToUpdate->Length();

	for (int32 i = 0; i < count; ++i)
	{
		ActionID nthActionID = listToUpdate->GetNthAction(i);
		switch (nthActionID.Get())
		{
			case kLiquidLayoutActionID:
			{
				break;
			}
			default:
			{
				ASSERT("Unknown action!");
				break;
			}
		}
	}
}

//---------------------------------------------------------------
// LiquidLayoutPanelMenuComponent::DoAction()
//---------------------------------------------------------------
void LiquidLayoutPanelMenuComponent::DoAction(IActiveContext* ac, ActionID id, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (id.Get()) 
	{
		case kLiquidLayoutActionID:
		{
			InterfacePtr<IApplication> iApplication(GetExecutionContextSession()->QueryApplication());
			InterfacePtr<IPanelMgr> iPanelMgr(iApplication->QueryPanelManager());
			
			if ( iPanelMgr )
				iPanelMgr->ShowPanelByWidgetID(kLiquidLayoutPanelWidgetID);
			
			// Select the Page Tool
			Utils<IToolBoxUtils> iToolBoxUtils;
			InterfacePtr<ITool> currentTool(iToolBoxUtils->QueryActiveTool());
			InterfacePtr<ITool> pageTool(iToolBoxUtils->QueryTool(kPageToolBoss));
			if ( pageTool && pageTool != currentTool )
				iToolBoxUtils->SetActiveTool(pageTool, pageTool->GetToolType());
			break;
		}
		default:
			ASSERT_FAIL("Asked to do unknown action");
			break;
	}
}


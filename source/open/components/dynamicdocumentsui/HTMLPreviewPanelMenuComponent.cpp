//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/HTMLPreviewPanelMenuComponent.cpp $
//  
//  Owner: Ankur Mathur
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

#include "IActionStateList.h"
#include "IActiveContext.h"
#include "IApplication.h"
#include "ICSXSPlugPlugExtensions.h"
#include "IPanelMgr.h"

// ----- Include files -----
#include "CActionComponent.h"
#include "LocaleSetting.h"

// ----- ID files -----
#include "DynamicDocumentsUIID.h"
#include "IBoolData.h"
#include "IPanelControlData.h"
#include "Utils.h"
#include "IPalettePanelUtils.h"
#include "PaletteRefUtils.h"

static const char* kHTMLPreviewExtensionID = "com.adobe.indesign.HTMLPreview.html.extension";

//========================================================================================
// CLASS HTMLFXLPreviewPanelMenuComponent
//========================================================================================
class HTMLFXLPreviewPanelMenuComponent : public CActionComponent
{
public:
	HTMLFXLPreviewPanelMenuComponent(IPMUnknown *boss);

	virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);
	virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
};

CREATE_PMINTERFACE(HTMLFXLPreviewPanelMenuComponent, kHTMLFXLPreviewPanelMenuComponentImpl)

	//---------------------------------------------------------------
	// Constructor
	//---------------------------------------------------------------
HTMLFXLPreviewPanelMenuComponent::HTMLFXLPreviewPanelMenuComponent(IPMUnknown *boss) :
	CActionComponent(boss)
{
}

//---------------------------------------------------------------
// HTMLFXLPreviewPanelMenuComponent::UpdateActionStates()
//---------------------------------------------------------------
void HTMLFXLPreviewPanelMenuComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *updateList, GSysPoint mousePoint, IPMUnknown* widget)
{		
	int32 count = updateList->Length();

	for (int32 i = 0; i < count; ++i)
	{
		ActionID nthActionID = updateList->GetNthAction(i);
		switch (nthActionID.Get())
		{		
			case kHTMLFXLPreviewActionID:
			{
				updateList->SetNthActionState(i, kEnabledAction);
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
// HTMLFXLPreviewPanelMenuComponent::DoAction()
//---------------------------------------------------------------
void HTMLFXLPreviewPanelMenuComponent::DoAction(IActiveContext* ac, ActionID id, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (id.Get()) 
	{
		case kHTMLFXLPreviewActionID:
		{
			InterfacePtr<ICSXSPlugPlugExtensions> plugPlug(GetExecutionContextSession(), UseDefaultIID());
			if (plugPlug)
			{
				ActionID actionID = plugPlug->GetExtensionActionID(kHTMLPreviewExtensionID);
				ASSERT_MSG(actionID != kInvalidActionID, "HTMLPreview invalid action id");
				if (actionID == kInvalidActionID)
					return;

				InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
				InterfacePtr<IPanelMgr>	panelMgr(theApp->QueryPanelManager());
				if (panelMgr->IsPanelWithMenuIDShown(actionID))
				{
					// Extension is already visible.
					// Send event to extension to show the current spread.
					ICSXSPlugPlugEventHandler::CSXSEvent idCSXSEvent;
					if(id.Get() == kHTMLFXLPreviewActionID)
						idCSXSEvent.type = "com.adobe.indesign.events.DoSpreadPreview";
					else
						idCSXSEvent.type = "com.adobe.indesign.events.DoDocumentPreview";

					idCSXSEvent.scope = ICSXSPlugPlugEventHandler::kEventScope_Application; // not sending outside of app
					idCSXSEvent.extensionId = nil;
					idCSXSEvent.data = nil;
					if (LocaleSetting::GetLocale().IsProductFS( kInDesignProductFS))
						idCSXSEvent.appId = kIDEnigmaCode;
					else
						idCSXSEvent.appId = kICEnigmaCode;
					plugPlug->DispatchPlugPlugEvent(&idCSXSEvent);


					WidgetID widgetID = plugPlug->GetExtensionWidgetID(kHTMLPreviewExtensionID);
					if(widgetID != kInvalidWidgetID)
					{
						InterfacePtr<IPanelControlData>iHTMLPreviewExtension(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(widgetID)); 
						InterfacePtr<IControlView> iHTMLPreviewPanelView(iHTMLPreviewExtension, UseDefaultIID());
						PaletteRefUtils::BringPaletteToFront(panelMgr->GetPaletteRefContainingPanel(iHTMLPreviewPanelView));
					}
				}
				else
				{
					InterfacePtr<IActionManager> actionMgr(theApp->QueryActionManager()); 
					if (actionID != kInvalidActionID)
						actionMgr->PerformAction(GetExecutionContextSession()->GetActiveContext(), actionID);
					
					InterfacePtr<IBoolData> isManualLaunch(GetExecutionContextSession(), IID_IHTMLFXLPREVIEWMANUALLAUNCHBOOLDATA);
					isManualLaunch->Set(kTrue);
				}
			}
			break;
		}
		default:
			ASSERT_FAIL("Asked to do unknown action");
			break;
	}
}

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelTreeViewNodeEH.cpp $
//  
//  Owner: Michele Stutzman
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

#include "IActionManager.h"
#include "IAppearanceSuite.h"
#include "IApplication.h"
#include "IMenuManager.h"
#include "ITreeNodeIDData.h"
#include "IWidgetParent.h"
#include "IEvent.h"

// ----- Includes -----

#include "MSOStateNodeID.h"
#include "TreeNodeEventHandler.h"

// ----- Utility files -----

#include "FormFieldUIUtils.h"
#include "MSOPanelUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"


class MSOPanelTreeViewNodeEH : public TreeNodeEventHandler
{
public:
	MSOPanelTreeViewNodeEH(IPMUnknown *boss);
	virtual ~MSOPanelTreeViewNodeEH();

	virtual bool16 ButtonDblClk(IEvent* e);
	virtual bool16 RButtonDn(IEvent* e);
	virtual bool16 LButtonDn(IEvent* e);
};

// =============================================================================
// *** MSOPanelTreeViewNodeEH impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(MSOPanelTreeViewNodeEH, kMSOPanelTreeViewNodeEHImpl)

MSOPanelTreeViewNodeEH::MSOPanelTreeViewNodeEH(IPMUnknown *boss) : TreeNodeEventHandler(boss)
{
} // end constructor

MSOPanelTreeViewNodeEH::~MSOPanelTreeViewNodeEH()
{
} // end destructor

// -----------------------------------------------------------------------------

bool16 MSOPanelTreeViewNodeEH::ButtonDblClk(IEvent* e)
{
	// TBD - select on double-click, see LayoutSelectionSuite
	return TreeNodeEventHandler::ButtonDblClk(e);
} // end ButtonDblClk()

// -----------------------------------------------------------------------------

bool16 MSOPanelTreeViewNodeEH::RButtonDn(IEvent* e)
{
	//
    // Bring up the context menu.
	//
    InterfacePtr<IApplication> iApp(GetExecutionContextSession()->QueryApplication());
    InterfacePtr<IActionManager> iActionMgr(iApp->QueryActionManager());
    InterfacePtr<IMenuManager> iMenuMgr(iActionMgr, UseDefaultIID());

    iMenuMgr->HandlePopupMenu("$$$/Menu/MSOPanel/ContextMenu", e->GlobalWhere(), e->GlobalWhere(), kTrue, this);

    return kTrue;
} // end RButtonDn()

// -----------------------------------------------------------------------------

bool16 MSOPanelTreeViewNodeEH::LButtonDn(IEvent* e)
{
	InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
	if (iAppearanceSuite)
	{
		InterfacePtr<IWidgetParent>	wp( this, UseDefaultIID());		
		InterfacePtr<ITreeNodeIDData> nodeData(wp, UseDefaultIID());
		if (nodeData)
		{
			TreeNodePtr<const MSOStateNodeID> msoStateNode(nodeData->Get());
			if (msoStateNode->GetAppearance() == iAppearanceSuite->GetActiveState())
			{
				MSOPanelUtils::AcceptMSONameIfNeeded(iAppearanceSuite);

				// Make sure the state not the MSO is selected.
				iAppearanceSuite->SelectActiveState();
			}
		}
	}

	return TreeNodeEventHandler::LButtonDn(e);
}
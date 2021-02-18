//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionalTextUIUtils.cpp $
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

#include "IActiveContext.h"
#include "IConditionTagList.h"
#include "IConditionTagSuite.h"
#include "IControlView.h"
#include "IPanelControlData.h"
#include "ISelectionManager.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITreeViewMgr.h"
#include "ITreeViewWidgetMgr.h"
#include "IUIDData.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "ConditionalTextUIDefs.h"
#include "IconRsrcDefs.h"
#include "SysControlIds.h"
#include "UIDList.h"
#include "UIDNodeID.h"

// ----- Utility files -----

#include "IConditionalTextFacade.h"
#include "ConditionalTextUIUtils.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"


// =============================================================================
// *** ConditionalTextUIUtils impl ***
// -----------------------------------------------------------------------------

void ConditionalTextUIUtils::ApplyAppliedIconToWidget(const ITreeViewWidgetMgr *widgetMgr, const NodeID& node, IControlView* widget)
{
	InterfacePtr<IPanelControlData>	widgetsChildren(widget, UseDefaultIID());
	IControlView* appliedIcon = widgetsChildren->FindWidget(kConditionTagAppliedStateWidgetId);
	ASSERT(appliedIcon != nil);
	if (!appliedIcon) return;

	// Get information about the applied conditions.
	UIDList toAllChars;
	UIDList toSomeChars;
	bool16 rangeHasUnconditionalChars(kTrue);
	IActiveContext* ac = GetExecutionContextSession()->GetActiveContext();
	ISelectionManager* selMgr = ac->GetContextSelection();
	InterfacePtr<IConditionTagSuite> conditionsSuite(static_cast<IConditionTagSuite*>(selMgr->QueryIntegratorSuite(IID_ICONDITIONTAGSUITE, ISelectionManager::kEnabledInterface)));
	if (conditionsSuite)
		conditionsSuite->GetAppliedConditionTags(toAllChars, toSomeChars, &rangeHasUnconditionalChars);

	RsrcID	iconRsrcID = kNoIcon;
	PluginID pluginID = kApplicationRsrcPluginID;

	if (conditionsSuite)
	{
		InterfacePtr<ITreeViewHierarchyAdapter> adapter(widgetMgr, UseDefaultIID());
		if (adapter && node == adapter->GetRootNode())
		{
			// Applied icon for the "[Unconditional]" item

			if (toAllChars.size() == 0 && toSomeChars.size() == 0)
			{
				// All characters are unconditional.
				iconRsrcID = kAppliedToAllCharactersIndicatorRsrcID;
				pluginID = kConditionalTextUIPluginID;
			}
			else if (toSomeChars.size() > 0)
			{
				// Some characters are unconditional.
				iconRsrcID = rangeHasUnconditionalChars ? kAppliedToSomeCharactersIndicatorRsrcID : kNoIcon;
				pluginID = kConditionalTextUIPluginID;
			}
		}
		else
		{
			// Applied icon for normal condition items
			InterfacePtr<IUIDData> dbData(widgetMgr, UseDefaultIID());
			TreeNodePtr<UIDNodeID>	uidNode(node);
			InterfacePtr<IConditionTag> tag(dbData->GetItemDataBase(), uidNode->GetUID(), UseDefaultIID());
			if (tag)
			{
				if (K2find(toAllChars, ::GetUID(tag)) != toAllChars.end())
				{
					iconRsrcID = kAppliedToAllCharactersIndicatorRsrcID;
					pluginID = kConditionalTextUIPluginID;
				}
				else if (K2find(toSomeChars, ::GetUID(tag)) != toSomeChars.end())
				{
					iconRsrcID = kAppliedToSomeCharactersIndicatorRsrcID;
					pluginID = kConditionalTextUIPluginID;
				}
			}
		}
	}

	if (appliedIcon->GetRsrcPluginID() != pluginID || appliedIcon->GetRsrcID() != iconRsrcID)
	{
		appliedIcon->SetRsrcPluginID(pluginID);
		appliedIcon->SetRsrcID(iconRsrcID);
		appliedIcon->Invalidate();
	}
} // end ApplyAppliedIconToWidget()
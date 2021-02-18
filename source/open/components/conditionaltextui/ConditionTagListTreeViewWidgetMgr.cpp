//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionTagListTreeViewWidgetMgr.cpp $
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

#include "IConditionTag.h"
#include "IPanelControlData.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITriStateControlData.h"
#include "IUIDData.h"

// ----- Includes -----

#include "ConditionalTextUIDefs.h"
#include "CoreResTypes.h"
#include "CTreeViewWidgetMgr.h"
#include "LocaleSetting.h"
#include "UIDNodeID.h"

// ----- Utility files -----

#include "ConditionalTextUIUtils.h"
#include "Utils.h"

// ----- ID files -----

#include "ConditionalTextUIID.h"


class ConditionTagListTreeViewWidgetMgr : public CTreeViewWidgetMgr
{
public:
	ConditionTagListTreeViewWidgetMgr(IPMUnknown *boss);
	~ConditionTagListTreeViewWidgetMgr();
	
	virtual bool16				ApplyNodeIDToWidget(const NodeID& node, IControlView* widget, int32) const;
	IControlView*				CreateWidgetForNode(const NodeID& node) const;

private:
	IDataBase*	GetDataBase() const;
};

// =============================================================================
// *** ConditionTagListTreeViewWidgetMgr impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(ConditionTagListTreeViewWidgetMgr, kConditionTagListTreeViewWidgetMgrImpl)

ConditionTagListTreeViewWidgetMgr::ConditionTagListTreeViewWidgetMgr(IPMUnknown *boss) :
	CTreeViewWidgetMgr(boss)
{
} // end constructor

ConditionTagListTreeViewWidgetMgr::~ConditionTagListTreeViewWidgetMgr()
{
} // end desctructor

// -----------------------------------------------------------------------------

bool16 ConditionTagListTreeViewWidgetMgr::ApplyNodeIDToWidget(const NodeID& node, IControlView* widget, int32) const
{	
	CTreeViewWidgetMgr::ApplyNodeIDToWidget(node, widget);

	// Set the node name and visibility icon.
	IDataBase *db = this->GetDataBase();
	TreeNodePtr<UIDNodeID>	uidNode(node);

	InterfacePtr<IPanelControlData>	widgetsChildren(widget, UseDefaultIID());
	InterfacePtr<ITreeViewHierarchyAdapter> adapter(this, UseDefaultIID());
	if (adapter && node == adapter->GetRootNode())
	{
		// Fill in the widget for the "[Unconditional]" item
		PMString unconditionalName("#ConditionTag_Unconditional", PMString::kTranslateDuringCall);
		SetNodeName(widgetsChildren, unconditionalName);
	}
	else 
	{
		// Normal condition node; fill in name and visiblity.
		InterfacePtr<IConditionTag> tag(db, uidNode->GetUID(), UseDefaultIID());
		if (tag)
		{
			// Name
			SetNodeName(widgetsChildren, tag->GetName());

			// Visibility
			IControlView* eyeballView = widgetsChildren->FindWidget(kConditionTagEyeballWidgetID);
			InterfacePtr<ITriStateControlData> eyeballData(eyeballView, UseDefaultIID());
			eyeballData->SetState(tag->IsVisible() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected, kTrue, kFalse);
		}
	}
	
	// Applied icon
	ConditionalTextUIUtils::ApplyAppliedIconToWidget(this, node, widget);

	return kTrue;
} // end ApplyNodeIDToWidget()

// -----------------------------------------------------------------------------

IControlView* ConditionTagListTreeViewWidgetMgr::CreateWidgetForNode(const NodeID& node) const
{
	bool16 bUseNoConditionWidget = kFalse;
	InterfacePtr<ITreeViewHierarchyAdapter> adapter(this, IID_ITREEVIEWHIERARCHYADAPTER);
	if (adapter && node == adapter->GetRootNode())
		bUseNoConditionWidget = kTrue;

	return (IControlView*)::CreateObject(::GetDataBase(this),
				RsrcSpec(LocaleSetting::GetLocale(), kConditionalTextUIPluginID, kViewRsrcType, 
				bUseNoConditionWidget ? kNoConditionTagTreeViewNodeRsrcID : kConditionTagTreeViewNodeRsrcID),IID_ICONTROLVIEW);
}

// -----------------------------------------------------------------------------

IDataBase* ConditionTagListTreeViewWidgetMgr::GetDataBase() const
{
	InterfacePtr<const IUIDData>	data(this, IID_IUIDDATA);
	return data->GetItemDataBase();
} // end GetDataBase()

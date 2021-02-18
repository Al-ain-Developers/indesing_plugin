//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actionpanel/BehaviorsTreeViewMgr.cpp $
//  
//  Owner: Michael Burbidge
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

#include "IBehaviorData.h"
#include "IControlView.h"
#include "ITextControlData.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITriStateControlData.h"
#include "ISelectionUtils.h"
#include "IUIDData.h"
#include "IWidgetUtils.h"

// ----- Implementation Includes -----

#include "FormFieldUIDefs.h"
#include "CTreeViewWidgetMgr.h"
#include "UIDNodeID.h"
#include "CreateObject.h"
#include "LocaleSetting.h"
#include "CoreResTypes.h"
#include "FormFieldUIUtils.h"
#include "RsrcSpec.h"
#include "Utils.h"

#include "BehaviorUIID.h"
#include "FormFieldUIID.h"

//========================================================================================
// CLASS BehaviorsTreeViewMgr
//========================================================================================

class BehaviorsTreeViewMgr : public CTreeViewWidgetMgr
{
public:
	BehaviorsTreeViewMgr(IPMUnknown *boss);
	~BehaviorsTreeViewMgr();
	
	virtual	IControlView*		CreateWidgetForNode(const NodeID& node) const;
	virtual	bool16				ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 message) const;
	
private:
	ITriStateControlData::TriState GetBehaviorEnabledState(const UIDRef& behaviorRef) const;
};

CREATE_PMINTERFACE(BehaviorsTreeViewMgr, kBehaviorsTreeViewMgrImpl)

//----------------------------------------------------------------------------------------
// BehaviorsTreeViewMgr constructor
//----------------------------------------------------------------------------------------

BehaviorsTreeViewMgr::BehaviorsTreeViewMgr(IPMUnknown *boss) 
	: CTreeViewWidgetMgr(boss)
{
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeViewMgr::~BehaviorsTreeViewMgr 
//----------------------------------------------------------------------------------------

BehaviorsTreeViewMgr::~BehaviorsTreeViewMgr()
{
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeViewMgr::ApplyNodeIDToWidget
//----------------------------------------------------------------------------------------

bool16 BehaviorsTreeViewMgr::ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 message ) const
{	
	CTreeViewWidgetMgr::ApplyNodeIDToWidget( node, widget );
	
	TreeNodePtr<UIDNodeID>	behaviorNode(node);
	InterfacePtr<ITreeViewHierarchyAdapter> viewAdapter(this, UseDefaultIID());
	
	ASSERT(node != viewAdapter->GetRootNode());

	IDataBase *db = Utils<ISelectionUtils>()->GetActiveSelection()->GetDataBase();

	if(db->IsValidUID(behaviorNode->GetUID()))
	{
		// Name
		InterfacePtr<ITextControlData> behaviorTitle((ITextControlData *) Utils<IWidgetUtils>()->QueryRelatedWidget((IControlView*) widget, kBehaviorTitleWidgetId, IID_ITEXTCONTROLDATA));
		behaviorTitle->SetString(FormFieldUIUtils::GetBehaviorName(UIDRef(db, behaviorNode->GetUID())), kFalse, kFalse);

		// Enabled
		InterfacePtr<ITriStateControlData> eventEnable((ITriStateControlData *) Utils<IWidgetUtils>()->QueryRelatedWidget((IControlView*) widget, kBehaviorOnOffButtonWidgetID, IID_ITRISTATECONTROLDATA));
		eventEnable->SetState(GetBehaviorEnabledState(UIDRef(db, behaviorNode->GetUID())), kFalse, kFalse);
	}

	return kTrue;
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeViewMgr::CreateWidgetForNode
//----------------------------------------------------------------------------------------

IControlView* BehaviorsTreeViewMgr::CreateWidgetForNode(const NodeID& node) const
{
	InterfacePtr<ITreeViewHierarchyAdapter> viewAdapter(this, UseDefaultIID());
	ASSERT(node != viewAdapter->GetRootNode());

	return (IControlView*)::CreateObject(::GetDataBase(this),
				RsrcSpec(LocaleSetting::GetLocale(), kFormFieldUIPluginID, kViewRsrcType, 
				kBehaviorsActionNodeWidgetRsrcID),IID_ICONTROLVIEW);
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeViewMgr::GetBehaviorEnabledState
//----------------------------------------------------------------------------------------

ITriStateControlData::TriState BehaviorsTreeViewMgr::GetBehaviorEnabledState(const UIDRef& behaviorRef) const
{
	InterfacePtr<IBehaviorData> data(behaviorRef, UseDefaultIID());

	return (data && data->IsEnabled()) ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected;
}

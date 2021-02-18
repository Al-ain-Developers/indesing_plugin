//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/TimingPanelTreeViewWidgetMgr.cpp $
//  
//  Owner: Yeming Liu
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

#include "IDynamicTargetsFacade.h"
#include "ISelectionManager.h"
#include "ITextControlData.h"
#include "ITreeViewHierarchyAdapter.h"

// ----- Includes -----

#include "CoreResTypes.h"
#include "CTreeViewWidgetMgr.h"
#include "DynamicDocumentsUIDefs.h"
#include "LocaleSetting.h"
#include "TimingPanelTreeNodeID.h"

// ----- Utils -----

#include "ISelectionUtils.h"
#include "IWidgetUtils.h"

// ----- ID.h files -----

#include "DynamicDocumentsUIID.h"

#define INHERITED	CTreeViewWidgetMgr

//----------------------------------------------------------------------------------------
// TimingPanelTreeViewWidgetMgr constructor
//----------------------------------------------------------------------------------------
class TimingPanelTreeViewWidgetMgr : public INHERITED
{
	public:
		TimingPanelTreeViewWidgetMgr(IPMUnknown *boss);
		~TimingPanelTreeViewWidgetMgr();
		
		virtual	IControlView*		CreateWidgetForNode(const NodeID& node) const;
		virtual	WidgetID			GetWidgetTypeForNode(const NodeID& node) const;
		virtual	bool16				ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 message ) const;
};

CREATE_PMINTERFACE(TimingPanelTreeViewWidgetMgr, kTimingPanelTreeViewWidgetMgrImpl)

//----------------------------------------------------------------------------------------
// TimingPanelTreeViewWidgetMgr constructor
//----------------------------------------------------------------------------------------
TimingPanelTreeViewWidgetMgr::TimingPanelTreeViewWidgetMgr(IPMUnknown *boss) :
	INHERITED(boss)
{
}


//----------------------------------------------------------------------------------------
// TimingPanelTreeViewWidgetMgr::~TimingPanelTreeViewWidgetMgr 
//----------------------------------------------------------------------------------------
TimingPanelTreeViewWidgetMgr::~TimingPanelTreeViewWidgetMgr()
{
}

//----------------------------------------------------------------------------------------
// TimingPanelTreeViewWidgetMgr::ApplyNodeIDToWidget
//----------------------------------------------------------------------------------------
bool16 TimingPanelTreeViewWidgetMgr::ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 ) const
{	
    TreeNodePtr<TimingPanelTreeNodeID> itemNode(node); 

    InterfacePtr<IPanelControlData> iPanelControlData(widget, UseDefaultIID()); 
    InterfacePtr<ITreeViewHierarchyAdapter> iTreeViewHierarchyAdapter(this, UseDefaultIID()); 
    if (iTreeViewHierarchyAdapter)
    { 
		//
		// Set item name.
		//
        UID itemUID = itemNode->GetUID();

		InterfacePtr<ISelectionManager> iSelectionMgr(Utils<ISelectionUtils>()->QueryActiveSelection ()); 
		IDataBase* db = iSelectionMgr->GetDataBase();

		PMString itemName = Utils<Facade::IDynamicTargetsFacade>()->GetTargetName(UIDRef(db, itemUID));
	
        InterfacePtr<ITextControlData> iItemNameControlData((ITextControlData*)Utils<IWidgetUtils>()->QueryRelatedWidget((IControlView*)widget, kTimingItemElementItemNameWidgetID, IID_ITEXTCONTROLDATA)); 
		iItemNameControlData->SetString(itemName, kTrue, kFalse);
    } 
     
	//Call base class for hilite selection
	INHERITED::ApplyNodeIDToWidget( node, widget );
		
	return kTrue;
}


//----------------------------------------------------------------------------------------
// TimingPanelTreeViewWidgetMgr::CreateWidgetForNode
//----------------------------------------------------------------------------------------
IControlView* TimingPanelTreeViewWidgetMgr::CreateWidgetForNode(const NodeID& node) const
{
	RsrcID rsrcID = kTimingPanelTreeNodeRsrcID;

	IControlView* iNodePanel = static_cast<IControlView *>(::CreateObject(
									::GetDataBase(this), 
									RsrcSpec(LocaleSetting::GetLocale(), kDynamicDocumentsUIPluginID, kViewRsrcType, rsrcID),
									IID_ICONTROLVIEW));

	return iNodePanel;
}

//----------------------------------------------------------------------------------------
// TimingPanelTreeViewWidgetMgr::GetWidgetTypeForNode
//----------------------------------------------------------------------------------------
WidgetID TimingPanelTreeViewWidgetMgr::GetWidgetTypeForNode(const NodeID& node) const
{	
	return kTimingPanelElementWidgetID;
}


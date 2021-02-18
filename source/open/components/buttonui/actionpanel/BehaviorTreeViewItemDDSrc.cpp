//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actionpanel/BehaviorTreeViewItemDDSrc.cpp $
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

#include "IBehaviorDragDropData.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewController.h"
#include "ITreeViewHierarchyAdapter.h"
#include "IWidgetUtils.h"
#include "IBehaviorSuite.h"
#include "ISelectionUtils.h"
#include "FormFieldUIUtils.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "CDragDropSource.h"
#include "UIDNodeID.h"
#include "Utils.h"
#include "SelectionUtils.h"
#include "BehaviorFlavorTypes.h"

//========================================================================================
// CLASS BehaviorTreeViewItemDDSource
//========================================================================================

class BehaviorTreeViewItemDDSource : public CDragDropSource
{
public:
	BehaviorTreeViewItemDDSource(IPMUnknown *boss);
	virtual ~BehaviorTreeViewItemDDSource();

	virtual bool16		DoAddDragContent(IDragDropController*);
	virtual	CursorSpec 	GetDragCursor(DragDrop::eTargetResponse dropEffect, bool16 isDragLocal) const;
};

//========================================================================================
// METHODS BehaviorTreeViewItemDDSource
//========================================================================================

CREATE_PMINTERFACE(BehaviorTreeViewItemDDSource, kBehaviorTreeViewItemDDSourceImpl)

//----------------------------------------------------------------------------------------
// BehaviorTreeViewItemDDSource constructor 
//----------------------------------------------------------------------------------------

BehaviorTreeViewItemDDSource::BehaviorTreeViewItemDDSource(IPMUnknown *boss) :
	CDragDropSource(boss)
{
}

//----------------------------------------------------------------------------------------
// BehaviorTreeViewItemDDSource::~BehaviorTreeViewItemDDSource
//----------------------------------------------------------------------------------------

BehaviorTreeViewItemDDSource::~BehaviorTreeViewItemDDSource()
{
}

//--------------------------------------------------------------------------------------
// BehaviorTreeViewItemDDSource::DoAddDragContent
//--------------------------------------------------------------------------------------

bool16 BehaviorTreeViewItemDDSource::DoAddDragContent(IDragDropController* controller)
{
	InterfacePtr<IDataExchangeHandler> ourHandler(controller->QueryHandler(kBehaviorDragDropFlavor));
	
	if (!ourHandler)
		return kFalse;
	
	InterfacePtr<IBehaviorDragDropData> data(ourHandler, UseDefaultIID());
	if (data)
	{
		InterfacePtr<IBehaviorSuite> actionSuite (SelectionUtils::QuerySuite<IBehaviorSuite>());
		if (actionSuite)
		{
			InterfacePtr<ITreeViewController> behaviorsCntlr((ITreeViewController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kBehaviorsTreeWidgetID, IID_ITREEVIEWCONTROLLER));
			InterfacePtr<ITreeViewHierarchyAdapter> behaviorsAdapter(behaviorsCntlr, UseDefaultIID());

			InterfacePtr<ITreeNodeIDData> treeNodeData(this, UseDefaultIID());
			TreeNodePtr<UIDNodeID>	behaviorNode(treeNodeData->Get());
			
			std::vector< std::pair<ActionEvent, UID> > behaviors;
			
			// ---- Dragging a behavior.
			behaviors.push_back(std::pair<ActionEvent, UID>(FormFieldUIUtils::GetSelectedEvent(this), behaviorNode->GetUID()));
			
			data->Set(Utils<ISelectionUtils>()->GetActiveSelection()->GetDataBase(), behaviors);
		}
	}
	
	// ---- Install our handler so we can fulfill promises we make below
	
	controller->SetSourceHandler(ourHandler) ;
	
	// ---- Add a data item and promise the appropriate data flavors. Note that in this
	//		case we promise only one since the internal flavor and external flavor are the same.
	
	InterfacePtr<IPMDataObject> item(controller->AddDragItem(1));
	PMFlavorFlags flavorFlags = 0;
	item->PromiseFlavor(kBehaviorDragDropFlavor, flavorFlags);

	return kTrue;
}

//--------------------------------------------------------------------------------------
// BehaviorTreeViewItemDDSource::GetDragCursor
//--------------------------------------------------------------------------------------

CursorSpec 	BehaviorTreeViewItemDDSource::GetDragCursor(DragDrop::eTargetResponse dropEffect, bool16 isDragLocal) const
{
	return (dropEffect == DragDrop::kWontAcceptDrop) ? CursorSpec((CursorID) DragDrop::kDefaultDragCursors) : CursorSpec((CursorID) kCrsrClosedHand );
}

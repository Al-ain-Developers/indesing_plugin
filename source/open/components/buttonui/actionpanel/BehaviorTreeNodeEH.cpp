//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actionpanel/BehaviorTreeNodeEH.cpp $
//  
//  Owner: Matt Joss
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
//  Copyright 1998
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interface Includes -----

#include "IBehaviorSuite.h"
#include "IWidgetUtils.h"
#include "ITreeViewController.h"
#include "ITreeViewHierarchyAdapter.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "K2Vector.tpp"	// ...Mac Release complains otherwise
#include "TreeNodeEventHandler.h"
#include "IMoveBehaviorData.h"
#include "Utils.h"
#include "SelectionUtils.h"

//========================================================================================
// CLASS BehaviorTreeNodeEH
//========================================================================================

class BehaviorTreeNodeEH : public TreeNodeEventHandler
{
public:
	BehaviorTreeNodeEH(IPMUnknown *boss);
	virtual ~BehaviorTreeNodeEH();

	virtual bool16 LButtonDn(IEvent* e);
};

//========================================================================================
// CLASS BehaviorTreeNodeEH
//========================================================================================

CREATE_PMINTERFACE(BehaviorTreeNodeEH, kBehaviorTreeNodeEHImpl)

//----------------------------------------------------------------------------------------
// BehaviorTreeNodeEH::BehaviorTreeNodeEH
//----------------------------------------------------------------------------------------

BehaviorTreeNodeEH::BehaviorTreeNodeEH(IPMUnknown *boss) :
	TreeNodeEventHandler(boss)
{
}

//----------------------------------------------------------------------------------------
// BehaviorTreeNodeEH::~BehaviorTreeNodeEH
//----------------------------------------------------------------------------------------

BehaviorTreeNodeEH::~BehaviorTreeNodeEH()
{
}

//----------------------------------------------------------------------------------------
// BehaviorTreeNodeEH::LButtonDn
//----------------------------------------------------------------------------------------
bool16 BehaviorTreeNodeEH::LButtonDn(IEvent* e)
{
	InterfacePtr<ITreeViewController> tvController((ITreeViewController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kBehaviorsTreeWidgetID, IID_ITREEVIEWCONTROLLER));

	if (TreeNodeEventHandler::LButtonDn(e))
	{
		InterfacePtr<IMoveBehaviorData> data(tvController, UseDefaultIID());

		if (data->GetDataBase() != nil)
		{
			InterfacePtr<IBehaviorSuite> actionSuite( SelectionUtils::QuerySuite<IBehaviorSuite>() );
			
			IDataBase* db = data->GetDataBase();
			std::vector< std::pair<ActionEvent, UID> > behaviors = data->GetBehaviors();
			ActionEvent event = data->GetEvent();
			int32 position = data->GetPosition();

			NodeIDList selection;
			tvController->GetSelectedItems(selection);
			if ( selection.size() )
			{
				// Nothing to do if the position is the same.
				InterfacePtr<ITreeViewHierarchyAdapter> tvAdapter(tvController, UseDefaultIID());

				if (position == tvAdapter->GetChildIndex(tvAdapter->GetRootNode(), selection[0])) return kTrue;
			}
			
			for (std::vector< std::pair<ActionEvent, UID> >::iterator i = behaviors.begin(); i != behaviors.end(); i++)
			{
				if (actionSuite->MoveAction((*i).second, event, position) != kSuccess)
					break;
				position++;
			}
		}
		
		data->Clear();
	}

	return kTrue;
}


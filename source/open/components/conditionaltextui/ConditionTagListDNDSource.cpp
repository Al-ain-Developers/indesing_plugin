//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionTagListDNDSource.cpp $
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
#include "K2Vector.tpp"

// ----- Interfaces -----

#include "IActiveContext.h"
#include "IConditionTagList.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITreeViewController.h"
#include "IUIDListData.h"
#include "IWidgetParent.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "CDragDropSource.h"
#include "UIDList.h"
#include "UIDNodeID.h"

// ----- Utility files -----

#include "IConditionalTextFacade.h"
#include "IInCopySharedUtils.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"


class ConditionTagListDNDSource : public CDragDropSource
{
public:
	ConditionTagListDNDSource(IPMUnknown *boss);
	virtual ~ConditionTagListDNDSource();

	virtual bool16		DoAddDragContent(IDragDropController*);
};

// =============================================================================
// *** ConditionTagListDNDSource impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(ConditionTagListDNDSource, kConditionTagListDNDSourceImpl)

ConditionTagListDNDSource::ConditionTagListDNDSource(IPMUnknown *boss)  :
	CDragDropSource(boss)
{
} // end constructor

ConditionTagListDNDSource::~ConditionTagListDNDSource()
{
} // end destructor

// -----------------------------------------------------------------------------

bool16 ConditionTagListDNDSource::DoAddDragContent(IDragDropController* controller)
{
	// Obtain a handler for our internal data flavor
	InterfacePtr<IDataExchangeHandler> ourHandler(controller->QueryHandler(kPMConditionTagListFlavor));
	
	// Don't promise anything if we couldn't get a handler
	if (!ourHandler)
		return kFalse;
	
	// Don't promise anything if it is managed incopy story
	IDataBase* db = ::GetDataBase(GetExecutionContextSession()->GetActiveContext()->GetContextWorkspace());
	if(!Utils<IInCopySharedUtils>()->StylesEditable(db))
    {
        return kFalse;
    }
	
	// Place the appropriate data or data reference into the handler
	InterfacePtr<IUIDListData> data(ourHandler, UseDefaultIID());
	if (data)
	{
		IActiveContext* ac = GetExecutionContextSession()->GetActiveContext();
		InterfacePtr<IConditionTagList>	tagList(Utils<Facade::IConditionalTextFacade>()->QueryActiveConditionList(ac));
		InterfacePtr<IWidgetParent>	parent(this, UseDefaultIID());
		InterfacePtr<ITreeViewController> tvController((ITreeViewController*) parent->QueryParentFor(IID_ITREEVIEWCONTROLLER));
		InterfacePtr<ITreeViewHierarchyAdapter> tvAdapter(tvController, UseDefaultIID());
	
		NodeIDList selNodes;
		tvController->GetSelectedItems(selNodes);
		int32 i = 0;
		UIDList* selTagList = new UIDList(::GetDataBase(tagList));
		for(i = 0; i < selNodes.size(); i++)
		{
			TreeNodePtr<UIDNodeID> uidNodeID(selNodes[i]);
			if (selNodes[i] == tvAdapter->GetRootNode())
				continue;	// can't delete [Unconditional]
			selTagList->Append(uidNodeID->GetUID());
		}
		data->Set(selTagList);
	}
	
	// Install our handler so we can fulfill promises we make below
	controller->SetSourceHandler(ourHandler);
	
	// Add a data item and promise the appropriate data flavors
	//	Note that in this case we promise only one since the internal flavor and external flavor are the same.
	InterfacePtr<IPMDataObject> item(controller->AddDragItem(1));
	PMFlavorFlags flavorFlags = 0;
	item->PromiseFlavor(kPMConditionTagListFlavor, flavorFlags);

	return kTrue;
} // end DoAddDragContent()
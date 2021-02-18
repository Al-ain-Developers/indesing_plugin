//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelStateDNDSource.cpp $
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

#include "ITreeViewController.h"
#include "IStateData.h"
#include "IWidgetParent.h"

// ----- Includes -----

#include "CDragDropSource.h"
#include "MSOStateNodeID.h"

// ----- Utility files -----


// ----- ID.h files -----

#include "FormFieldUIID.h"


class MSOPanelStateDNDSource : public CDragDropSource
{
public:
	MSOPanelStateDNDSource(IPMUnknown *boss);
	virtual ~MSOPanelStateDNDSource();

	virtual bool16		DoAddDragContent(IDragDropController*);
};

// =============================================================================
// *** MSOPanelStateDNDSource impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(MSOPanelStateDNDSource, kMSOPanelStateDNDSourceImpl)

MSOPanelStateDNDSource::MSOPanelStateDNDSource(IPMUnknown *boss)  :
	CDragDropSource(boss)
{
} // end constructor

MSOPanelStateDNDSource::~MSOPanelStateDNDSource()
{
} // end destructor

// -----------------------------------------------------------------------------

bool16 MSOPanelStateDNDSource::DoAddDragContent(IDragDropController* controller)
{
	// Obtain a handler for our internal data flavor
	InterfacePtr<IDataExchangeHandler> ourHandler(controller->QueryHandler(kMSOStateDragDropFlavor));
	
	// Don't promise anything if we couldn't get a handler
	if (!ourHandler)
		return kFalse;
	
	// Place the appropriate data into the handler
	InterfacePtr<IStateData> data(ourHandler, UseDefaultIID());
	if (data)
	{
		InterfacePtr<IWidgetParent>	parent(this, UseDefaultIID());
		InterfacePtr<ITreeViewController> tvController((ITreeViewController*) parent->QueryParentFor(IID_ITREEVIEWCONTROLLER));
	
		NodeIDList selNodes;
		tvController->GetSelectedItems(selNodes);
		ASSERT(selNodes.size() == 1);

		TreeNodePtr<MSOStateNodeID> msoStateNodeID(selNodes[0]);
		data->Set(msoStateNodeID->GetAppearance());
	}
	
	// Install our handler so we can fulfill promises we make below
	controller->SetSourceHandler(ourHandler);
	
	// Add a data item and promise the appropriate data flavors
	//	Note that in this case we promise only one since the internal flavor and external flavor are the same.
	InterfacePtr<IPMDataObject> item(controller->AddDragItem(1));
	PMFlavorFlags flavorFlags = 0;
	item->PromiseFlavor(kMSOStateDragDropFlavor, flavorFlags);

	return kTrue;
} // end DoAddDragContent()
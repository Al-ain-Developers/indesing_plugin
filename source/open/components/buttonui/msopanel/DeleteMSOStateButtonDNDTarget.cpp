//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/DeleteMSOStateButtonDNDTarget.cpp $
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

#include "IControlView.h"
#include "IStateData.h"

// ----- Includes -----

#include "CButtonDragDropTarget.h"

// ----- Utility files -----

#include "MSOPanelUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"
#include "DragDropID.h"


class DeleteMSOStateButtonDNDTarget : public CButtonDragDropTarget
{
public:
	DeleteMSOStateButtonDNDTarget(IPMUnknown *boss);
	virtual	~DeleteMSOStateButtonDNDTarget();
		
	virtual DragDrop::TargetResponse CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;
	virtual ErrorCode		ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);
};

// =============================================================================
// *** DeleteMSOStateButtonDNDTarget impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(DeleteMSOStateButtonDNDTarget, kDeleteMSOStateButtonDNDTargetImpl)

DeleteMSOStateButtonDNDTarget::DeleteMSOStateButtonDNDTarget(IPMUnknown *boss) :
	CButtonDragDropTarget(boss)
{
} // end constructor

DeleteMSOStateButtonDNDTarget::~DeleteMSOStateButtonDNDTarget()
{
} // end destructor

// -----------------------------------------------------------------------------

DragDrop::TargetResponse DeleteMSOStateButtonDNDTarget::CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* fromSource, const IDragDropController* controller) const
{
	// Check the available external flavors to see if we can handle any of them
	if (dataIter)
	{
		// Make sure we don't accept drops from other palettes
		DataExchangeResponse response = dataIter->FlavorExistsWithPriorityInAllObjects(kMSOStateDragDropFlavor);
		if (!response.CanDo())
			return DragDrop::kWontAcceptTargetResponse;
		
		return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy);	// Always copy in the drag and drop sense
	}
	
	return DragDrop::kWontAcceptTargetResponse;
} // end CouldAcceptTypes()

// -----------------------------------------------------------------------------

ErrorCode DeleteMSOStateButtonDNDTarget::ProcessDragDropCommand(IDragDropController* controller, DragDrop::eCommandType type)
{
	InterfacePtr<IDataExchangeHandler> handler(controller->QuerySourceHandler());
	InterfacePtr<IStateData>	data(handler, UseDefaultIID());
	if(data)
		MSOPanelUtils::DeleteState(data->Get());

	return kSuccess;
} // end ProcessDragDropCommand()

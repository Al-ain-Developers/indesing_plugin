//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actionpanel/BehaviorDragDropDEHandler.cpp $
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
//  Implementation for a simple XML Element exchange handler
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interface Includes -----

#include "IBehaviorDragDropData.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "BehaviorFlavorTypes.h"
#include "CDataExchangeHandlerFor.h"

//========================================================================
// Class BehaviorDragDropDEHandler
//========================================================================

class BehaviorDragDropDEHandler : public CDataExchangeHandlerFor
{
	public:
		BehaviorDragDropDEHandler(IPMUnknown *boss) : CDataExchangeHandlerFor(boss) {}
		virtual	~BehaviorDragDropDEHandler() {}

		virtual	PMFlavor 	GetFlavor() const { return kBehaviorDragDropFlavor; }

		virtual void		Clear();
		virtual bool16		IsEmpty() const;
		
		virtual ErrorCode	Externalize(IPMDataObject* whichItem, ExternalPMFlavor toWhichFlavor, IPMStream* s);
};

//========================================================================================
// Implementation BehaviorDragDropDEHandler
//========================================================================================

CREATE_PMINTERFACE(BehaviorDragDropDEHandler, kBehaviorDragDropDEHandlerImpl)

//--------------------------------------------------------------------------------------
// Clear
//--------------------------------------------------------------------------------------
void BehaviorDragDropDEHandler::Clear()
{
	InterfacePtr<IBehaviorDragDropData> data(this, UseDefaultIID());
	data->Clear();
}

//--------------------------------------------------------------------------------------
// IsEmpty
//--------------------------------------------------------------------------------------
bool16 BehaviorDragDropDEHandler::IsEmpty() const
{
	InterfacePtr<IBehaviorDragDropData> data(this, UseDefaultIID());
	return data->IsEmpty();
}


//--------------------------------------------------------------------------------------
// Externalize
//--------------------------------------------------------------------------------------
ErrorCode BehaviorDragDropDEHandler::Externalize(IPMDataObject* whichItem, ExternalPMFlavor toWhichFlavor, IPMStream* s)
{
	return kFailure;
}
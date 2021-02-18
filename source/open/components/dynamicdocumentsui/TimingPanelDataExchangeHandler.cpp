//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/TimingPanelDataExchangeHandler.cpp $
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
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Comments: Implementation for object style z-order exchange handler
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interface files -----

// ----- Include files -----

#include "CDataExchangeHandlerFor.h"

// ----- Utilitity files -----

// ----- ID files -----

#include "DynamicDocumentsUIID.h"

//========================================================================
// Class TimingPanelDataExchangeHandler
//========================================================================

class TimingPanelDataExchangeHandler : public CDataExchangeHandlerFor
{
	public:
				TimingPanelDataExchangeHandler(IPMUnknown *boss) : CDataExchangeHandlerFor(boss) {}
		virtual	~TimingPanelDataExchangeHandler() {}

		virtual	PMFlavor 	GetFlavor() const { return kPMTimingPanelDragDropFlavor; }
};

CREATE_PMINTERFACE(TimingPanelDataExchangeHandler, kTimingPanelDataExchangeHandlerImpl)

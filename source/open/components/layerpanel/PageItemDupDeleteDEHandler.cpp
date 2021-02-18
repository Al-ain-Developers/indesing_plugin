//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/PageItemDupDeleteDEHandler.cpp $
//  
//  Owner: lance bushore
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
//  Implementation for a simple layer pencil exchange handler
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "LayerPanelID.h"

#include "CDataExchangeHandlerFor.h"

//========================================================================
// Class PageItemDupDeleteDEHandler
//========================================================================

class PageItemDupDeleteDEHandler : public CDataExchangeHandlerFor
{
	public:
		PageItemDupDeleteDEHandler(IPMUnknown *boss) : CDataExchangeHandlerFor(boss) {}
		virtual	~PageItemDupDeleteDEHandler() {}

		virtual	PMFlavor 	GetFlavor() const { return kPMLayerPageItemDupDeleteFlavor; }
};

CREATE_PMINTERFACE(PageItemDupDeleteDEHandler, kPageItemDupDeleteDEHandlerImpl)

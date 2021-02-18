//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayersPanelSAXHandler.cpp $
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
//========================================================================================

#include "VCPlugInHeaders.h"

#include "BasePanelSAXHandler.h"
#include "ISAXServices.h"
#include "IPanelControlData.h"
#include "IBoolData.h"

// ----- Implementation Includes -----

#include "LayerPanelID.h"
#include "LayersPanelWorkspaceDefs.h"
#include "LayerPanelUtils.h"

//========================================================================================
// ClassLayersPanelSAXHandler
//========================================================================================

class LayersPanelSAXHandler : public BasePanelSAXHandler
{
	typedef BasePanelSAXHandler inherited;
	
public:
	LayersPanelSAXHandler(IPMUnknown *boss);
	virtual ~LayersPanelSAXHandler();

	virtual void Register(ISAXServices* saxServices, IPMUnknown *importer);
	virtual void StartElement(const WideString& uri, const WideString& localname, const WideString& qname, ISAXAttributes* attrs);
	virtual void EndElement(const WideString& uri, const WideString& localname, const WideString& qname);
			
};


//========================================================================================
// METHODSLayersPanelSAXHandler
//========================================================================================
CREATE_PMINTERFACE(LayersPanelSAXHandler, kLayersPanelSAXHandlerImpl)

LayersPanelSAXHandler::LayersPanelSAXHandler(IPMUnknown *boss) :
	inherited(boss)
{
}

LayersPanelSAXHandler::~LayersPanelSAXHandler()
{
}

//----------------------------------------------------------------------------------------
// Register
//----------------------------------------------------------------------------------------
void LayersPanelSAXHandler::Register(ISAXServices* saxServices, IPMUnknown *importer)
{
	saxServices->RegisterElementHandler( WideString(""), WideString(LayersPanelWorkspaceDefs::kLayersPanelOptionsXMLTag), this );

	inherited::Register(saxServices, importer);
}

//----------------------------------------------------------------------------------------
// StartElement
//----------------------------------------------------------------------------------------
void LayersPanelSAXHandler::StartElement(const WideString& uri, const WideString& localname, const WideString& qname, ISAXAttributes* attrs)
{
	#pragma unused(uri,localname)
	if (qname == WideString(LayersPanelWorkspaceDefs::kLayersPanelOptionsXMLTag))
	{//
		InterfacePtr<const IPanelControlData> panelData(this, UseDefaultIID());
		const IControlView* treeView = panelData->FindWidget(kLayerPanelTreeWidgetID);
		InterfacePtr<IBoolData> rowSizeBool(treeView, IID_ISMALLPALETTEROWSBOOLDATA);
		bool16 currentSmallRow = rowSizeBool->Get();
		bool16 newSmallRow = GetAttributeBool( attrs,LayersPanelWorkspaceDefs::kLayersPanelSmallRowsXMLTag, currentSmallRow);
		LayerPanelUtils::SetSmallRow(rowSizeBool,newSmallRow);
	}
	else
		ASSERT_FAIL("LayersPanelSAXHandler called for an element it didn't register to receive");
}

void LayersPanelSAXHandler::EndElement(const WideString& uri, const WideString& localname, const WideString& qname)
{
	#pragma unused(uri,localname,qname)
}


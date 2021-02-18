//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/ActiveLayerWidgetTip.cpp $
//  
//  Owner: Paul Sorrick
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
//  Contains the main implementation of the ITip interface for widgets
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IActiveContext.h"
#include "IDocument.h"
#include "IDocumentLayer.h"
#include "IPanelControlData.h"
#include "AbstractTip.h"
#include "IWidgetParent.h"
#include "ITreeNodeIDData.h"

// ----- Includes -----

#include "HelperInterface.h"
#include "PMString.h"
#include "LayerTreeUIDNodeID.h"

// ----- Utility files -----

#include "ILayerUIUtils.h"
#include "LayerPanelUtils.h"

// ----- ID.h files -----

#include "LayerPanelID.h"


class ActiveLayerWidgetTip : public AbstractTip
{			
public:
	ActiveLayerWidgetTip( IPMUnknown *boss );
	virtual ~ActiveLayerWidgetTip();

	virtual PMString  GetTipText(const PMPoint& mouseLocation);
	
};

CREATE_PMINTERFACE( ActiveLayerWidgetTip, kActiveLayerWidgetTipImpl )


ActiveLayerWidgetTip::ActiveLayerWidgetTip(IPMUnknown *boss) :
	AbstractTip( boss )
{
}

ActiveLayerWidgetTip::~ActiveLayerWidgetTip()
{
}

PMString ActiveLayerWidgetTip::GetTipText(const PMPoint&)
{
	PMString activeTip = "";

	NodeID treeNode(LayerPanelUtils::GetLayerTreeNodeFromSubwidget(this)); // this looks like it could be combined with the next line, but doing so creates a memory leak.
	TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(treeNode);
	
	IActiveContext* context = GetExecutionContextSession()->GetActiveContext();
	InterfacePtr<IDocumentLayer> activeLayer(Utils<ILayerUIUtils>()->QueryContextActiveLayer(context));
	InterfacePtr<IDocumentLayer> docLayer(::GetDataBase(activeLayer),uidNode->GetUID(), IID_IDOCUMENTLAYER);

	// Only make a string for the tip if the active layer icon is visible for this layer.
	if (docLayer == activeLayer)
		activeTip = "ActiveTip";

	return activeTip;
} 


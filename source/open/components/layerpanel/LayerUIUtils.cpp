//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerUIUtils.cpp $
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
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IActiveContext.h"
#include "IControlView.h"
#include "IDocument.h"
#include "IDocumentLayer.h"
#include "ILayerList.h"
#include "ILayoutControlData.h"
#include "IPersistUIDData.h"

// ----- Includes -----

#include "CPMUnknown.h"

// ----- Utility files -----

#include "ILayerUtils.h"
#include "ILayerUIUtils.h"

// ----- ID.h files -----

#include "LayerPanelID.h"

class LayerUIUtils : public CPMUnknown<ILayerUIUtils>
{
public:
	LayerUIUtils(IPMUnknown *boss);
	
	virtual IDocumentLayer* QueryContextActiveLayer(IActiveContext* context);
	virtual IDocumentLayer* QueryNthUILayer(const ILayerList* list, int32 nth);
	virtual int32 GetUILayerIndex(const ILayerList* list, UID docUILayerUID);

};
	
CREATE_PMINTERFACE(LayerUIUtils, kLayerUIUtilsImpl)

LayerUIUtils::LayerUIUtils(IPMUnknown *boss) :
	CPMUnknown<ILayerUIUtils>(boss)
{
}

//
// LayerUIUtils::QueryContextActiveLayer
//
// Return the active layer for the context.
//
IDocumentLayer* LayerUIUtils::QueryContextActiveLayer(IActiveContext* context)
{
	IDocumentLayer* activeLayer = nil;

	// Get the layer for the context view if there is one. Each view can have it's own active layer.
	IControlView* activeView = context->GetContextView();
	InterfacePtr<ILayoutControlData> layoutData( activeView, UseDefaultIID());
	if (layoutData)
		activeLayer = layoutData->QueryActiveDocLayer();

	// If no layout view, use document where active layer is stored.
	if (!activeLayer)
	{
		IDocument* document = context->GetContextDocument();
		activeLayer = Utils<ILayerUtils>()->QueryDocumentActiveLayer(document);
	}

	return activeLayer;
}

IDocumentLayer* LayerUIUtils::QueryNthUILayer(const ILayerList* layerList, int32 nth)
{
	int32 nLayers = layerList->GetCount();
	int32 uiLayerCount = 0;
	for (int32 layerIndex = nLayers - 1; layerIndex >= 0; layerIndex--)
	{
		InterfacePtr<const IDocumentLayer> thisLayer(layerList->QueryLayer(layerIndex));

		ASSERT_MSG(thisLayer != nil,"Null layer in the layer list!!?!");
		if (thisLayer->IsUILayer())
		{
			if(uiLayerCount == nth)
				return layerList->QueryLayer(layerIndex);
			++uiLayerCount;
		}
		
	}
	return nil;
}

int32 LayerUIUtils::GetUILayerIndex(const ILayerList* layerList, UID docUILayerUID)
{
	int32 nLayers = layerList->GetCount();
	int32 uiLayerCount = 0;
	for (int32 layerIndex = nLayers - 1; layerIndex >= 0; layerIndex--)
	{
		InterfacePtr<const IDocumentLayer> thisLayer(layerList->QueryLayer(layerIndex));

		ASSERT_MSG(thisLayer != nil,"Null layer in the layer list!!?!");
		if (thisLayer->IsUILayer())
		{
			if(::GetUID(thisLayer) == docUILayerUID)
				return uiLayerCount;
			++uiLayerCount;
		}
	}
	return -1;
}


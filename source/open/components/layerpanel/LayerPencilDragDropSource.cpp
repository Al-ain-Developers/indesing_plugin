//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPencilDragDropSource.cpp $
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
//  Drag source for layer panel pencil widget.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IBoolData.h"
#include "IDocument.h"
#include "IDocumentLayer.h"
#include "IUIDData.h"
#include "IWidgetParent.h"
#include "ITreeNodeIDData.h"
#include "IPageItemLockFacade.h"

// ----- Includes -----

#include "CDragDropSource.h"
#include "HelperInterface.h"
#include "LayerPanelDefs.h"
#include "LayerTreeUIDNodeID.h"
#include "LayerPanelUtils.h"
#include "UIDList.h"

// ----- Utility files -----

#include "CmdUtils.h"
#include "Utils.h"
// ----- ID.h files -----

#include "AppUIID.h"
#include "LayerPanelID.h"
#include "widgetid.h"

// Note that this DragDropSource is used for both layers and hierarchy items in the layers panel

class LayerPencilDragDropSource : public CDragDropSource
{
public:
	LayerPencilDragDropSource(IPMUnknown *boss);
	virtual ~LayerPencilDragDropSource();

	virtual bool16		DoAddDragContent(IDragDropController*);

	virtual CursorSpec 	GetDragCursor(DragDrop::eTargetResponse, bool16 isDragLocal) const;
	virtual SysWireframe		DoMakeDragOutlineRegion() const	{ return nil; }
		// No drag outline region needed for pencil

		DECLARE_HELPER_METHODS()
};


CREATE_PMINTERFACE(LayerPencilDragDropSource, kLayerPencilDragDropSourceImpl)
DEFINE_HELPER_METHODS(LayerPencilDragDropSource)

LayerPencilDragDropSource::LayerPencilDragDropSource(IPMUnknown *boss)  :
	CDragDropSource(boss),
	HELPER_METHODS_INIT(boss)
{
}


LayerPencilDragDropSource::~LayerPencilDragDropSource()
{
}

//--------------------------------------------------------------------------------------
// DoAddDragContent
//--------------------------------------------------------------------------------------
bool16 LayerPencilDragDropSource::DoAddDragContent(IDragDropController* controller)
{
	// Obtain a handler for our internal data flavor
	InterfacePtr<IDataExchangeHandler> ourHandler(controller->QueryHandler(kPMLayerPencilFlavor));
	
	// Don't promise anything if we couldn't get a handler
	if (!ourHandler)
		return kFalse;
	
	// Place the appropriate data or data reference into the handler
	InterfacePtr<IUIDData> data(ourHandler, IID_IUIDDATA);
	if (data)
	{
		// Get the layer UID ref for this item/layer, store it
		NodeID treeNode(LayerPanelUtils::GetLayerTreeNodeFromSubwidget(this)); // this looks like it could be combined with the next line, but doing so creates a memory leak.
		TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(treeNode);

		UIDRef itemUIDRef = UIDRef(LayerPanelUtils::GetCurrentLayerPanelDB(this),uidNode->GetUID());
		InterfacePtr<const IDocumentLayer> docLayer(itemUIDRef,UseDefaultIID());
		bool isLocked = false;
		if(docLayer)
			isLocked = docLayer->IsLocked();
		else
		{
			UIDList itemUIDs(itemUIDRef);
			isLocked = Utils<Facade::IPageItemLockFacade>()->CanUnlock(itemUIDs);
		}
		data->Set(itemUIDRef);	
		
		// Place the appropriate data or data reference into the handler
		InterfacePtr<IBoolData> boolData(ourHandler, IID_IBOOLDATA);
		if (boolData)
		{
			boolData->Set(isLocked);
		}
	}

	// Install our handler so we can fulfill promises we make below
	controller->SetSourceHandler(ourHandler) ;
	
	// Add a data item and promise the appropriate data flavors
	//	Note that in this case we promise only one since the internal flavor and external flavor are the same.
	InterfacePtr<IPMDataObject> item(controller->AddDragItem(1));
	PMFlavorFlags flavorFlags = 0;
	item->PromiseFlavor(kPMLayerPencilFlavor, flavorFlags);

	return kTrue;
}

//--------------------------------------------------------------------------------------
// GetDragCursor
//--------------------------------------------------------------------------------------
CursorSpec 	LayerPencilDragDropSource::GetDragCursor(DragDrop::eTargetResponse, bool16 ) const
{
	return CursorSpec(kAppUIPluginID,kCrsrPointyHand);
}

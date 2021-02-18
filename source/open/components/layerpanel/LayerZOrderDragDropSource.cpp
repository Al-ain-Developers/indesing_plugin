//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerZOrderDragDropSource.cpp $
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
//  Drag source for z-order reordering
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "CDragDropSource.h"
#define INHERITED CDragDropSource

#include "LayerPanelID.h"
#include "AppUIID.h"
#include "DragDropID.h"
#include "LayerPanelDefs.h"
#include "ITreeNodeIDData.h"
#include "LayerTreeUIDNodeID.h"
#include "IUIDData.h"
#include "IDocument.h"
#include "KeyStates.h"
#include "IWidgetParent.h"
#include "LayerPanelUtils.h"
#include "LocaleSetting.h"

class LayerZOrderDragDropSource : public INHERITED
{
public:
	LayerZOrderDragDropSource(IPMUnknown *boss);
	virtual ~LayerZOrderDragDropSource();

	virtual bool16		DoAddDragContent(IDragDropController*);
	virtual CursorSpec 	GetDragCursor(DragDrop::eTargetResponse, bool16 isDragLocal) const;

private:
	ITreeNodeIDData* QueryTreeNodeData() const;

		DECLARE_HELPER_METHODS()
};


//========================================================================
// Class LayerZOrderDragDropSource
//========================================================================
CREATE_PMINTERFACE(LayerZOrderDragDropSource, kLayerZOrderDragDropSourceImpl)
DEFINE_HELPER_METHODS(LayerZOrderDragDropSource)

LayerZOrderDragDropSource::LayerZOrderDragDropSource(IPMUnknown *boss) :
	INHERITED(boss),
	HELPER_METHODS_INIT(boss)
{
}

LayerZOrderDragDropSource::~LayerZOrderDragDropSource()
{
}

bool16 LayerZOrderDragDropSource::DoAddDragContent(IDragDropController* controller)
{
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS))
		return kFalse;
	// Obtain a handler for our internal data flavor
	NodeID treeNode(LayerPanelUtils::GetLayerTreeNodeFromSubwidget(this)); // this looks like it could be combined with the next line, but doing so creates a memory leak.
	TreeNodePtr<const LayerTreeUIDNodeID>	sourceNodeID(treeNode);

	if(sourceNodeID->IsLayerEntry())
	{
		InterfacePtr<IDataExchangeHandler> ourHandler(controller->QueryHandler(kPMLayerZOrderFlavor));
		
		// Don't promise anything if we couldn't get a handler
		if (!ourHandler)
			return kFalse;
			
		// Install our handler so we can fulfill promises we make below
		controller->SetSourceHandler(ourHandler) ;

		UID dragSourceUID = sourceNodeID->GetUID();
		InterfacePtr<IUIDData> uidData(ourHandler,UseDefaultIID());
		uidData->Set(UIDRef(LayerPanelUtils::GetCurrentLayerPanelDB(this),dragSourceUID));
		
		// Add a data item and promise the appropriate data flavors
		//	Note that in this case we promise only one since the internal flavor and external flavor are the same.
		InterfacePtr<IPMDataObject> item(controller->AddDragItem(1));
		PMFlavorFlags flavorFlags = 0;
		item->PromiseFlavor(kPMLayerZOrderFlavor, flavorFlags);

		return kTrue;
	}
	else
	{
		UIDRef itemUIDRef = UIDRef(LayerPanelUtils::GetCurrentLayerPanelDB(this),sourceNodeID->GetUID());
		bool canChangeZOrder = !LayerPanelUtils::IsItemOrAncestorLockedOrHidden(itemUIDRef);
		
		ExternalPMFlavor whichFlavor = kNoExternalFlavor;
		if(canChangeZOrder)
		{
			whichFlavor = kPMLayerPageItemZOrderFlavor;
		}
		else
		{
			whichFlavor = kPMLayerPageItemDupDeleteFlavor;			
		}

		InterfacePtr<IDataExchangeHandler> deHandler(controller->QueryHandler(whichFlavor));
		
		// Don't promise anything if we couldn't get a handler
		if (!deHandler)
			return kFalse;
		
		// Place the appropriate data or data reference into the handler
		InterfacePtr<IUIDData> data(deHandler, IID_IUIDDATA);
		if (data)
		{
			data->Set(itemUIDRef);	
		}
		
		// Install our handler so we can fulfill promises we make below
		controller->SetSourceHandler(deHandler) ;

		
		// Add a data item and promise the appropriate data flavors
		//	Note that in this case we promise only one since the internal flavor and external flavor are the same.
		InterfacePtr<IPMDataObject> item(controller->AddDragItem(1));
		PMFlavorFlags flavorFlags = 0;
		item->PromiseFlavor(whichFlavor, flavorFlags);

		return kTrue;
	}
}


CursorSpec 	LayerZOrderDragDropSource::GetDragCursor(DragDrop::eTargetResponse dropEffect, bool16 ) const
{
	if((dropEffect == DragDrop::kWontAcceptDrop))
		return CursorSpec((CursorID) DragDrop::kDefaultDragCursors);
	bool16 optionKeyDown = ::IsOptionAltKeyPressed();
	return CursorSpec(kAppUIPluginID, optionKeyDown ? kCrsrClosedHandCopy : kCrsrClosedHand);
}





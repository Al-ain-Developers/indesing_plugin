//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/ProxyViewDragDropSource.cpp $
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
//  Drag source for layer panel proxy widget.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IDocument.h"
#include "IUIDData.h"
#include "IDocumentLayer.h"
#include "LayerPanelUtils.h"

// ----- Includes -----

#include "CDragDropSource.h"
#include "HelperInterface.h"
#include "LayerPanelDefs.h"
#include "LocaleSetting.h"

// ----- Utility files -----

#include "CmdUtils.h"
#include "EventUtilities.h"

// ----- ID.h files -----

#include "AppUIID.h"
#include "LayerPanelID.h"
#include "widgetid.h"



class ProxyViewDragDropSource : public CDragDropSource
{
public:
	ProxyViewDragDropSource(IPMUnknown *boss);
	virtual ~ProxyViewDragDropSource();

	virtual bool16		DoAddDragContent(IDragDropController*);

	virtual CursorSpec 	GetDragCursor(DragDrop::eTargetResponse, bool16 isDragLocal) const;
	virtual SysWireframe		DoMakeDragOutlineRegion() const	{ return nil; }
		// No drag outline region needed for proxy

		DECLARE_HELPER_METHODS()
};


CREATE_PMINTERFACE(ProxyViewDragDropSource, kProxyViewDragDropSourceImpl)
DEFINE_HELPER_METHODS(ProxyViewDragDropSource)

ProxyViewDragDropSource::ProxyViewDragDropSource(IPMUnknown *boss)  :
	CDragDropSource(boss),
	HELPER_METHODS_INIT(boss)
{
	TRACEFLOW("LayerPanel","ProxyViewDragDropSource constructed at 0x%x\n",this);
}


ProxyViewDragDropSource::~ProxyViewDragDropSource()
{
	TRACEFLOW("LayerPanel","ProxyViewDragDropSource destructed at 0x%x\n",this);
}

//--------------------------------------------------------------------------------------
// DoAddDragContent
//--------------------------------------------------------------------------------------
bool16 ProxyViewDragDropSource::DoAddDragContent(IDragDropController* controller)
{
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS))
		return kFalse;

	// Obtain a handler for our internal data flavor
	InterfacePtr<IDataExchangeHandler> ourHandler(controller->QueryHandler(kPMLayerProxyFlavor));
	
	// Don't promise anything if we couldn't get a handler
	if (!ourHandler)
		return kFalse;
	
	// Place the appropriate data or data reference into the handler
	InterfacePtr<IUIDData> data(ourHandler, IID_IUIDDATA);
	if (data)
	{
		// Get the layer UID ref for this layer, store it
		InterfacePtr<const IDocumentLayer> docLayer(LayerPanelUtils::QueryLayerFromPanelWidget(this));
		data->Set(docLayer);
	}
	
	// Install our handler so we can fulfill promises we make below
	controller->SetSourceHandler(ourHandler) ;
	
	// Add a data item and promise the appropriate data flavors
	//	Note that in this case we promise only one since the internal flavor and external flavor are the same.
	InterfacePtr<IPMDataObject> item(controller->AddDragItem(1));
	PMFlavorFlags flavorFlags = 0;
	item->PromiseFlavor(kPMLayerProxyFlavor, flavorFlags);

	return kTrue;
}

//--------------------------------------------------------------------------------------
// GetDragCursor
//--------------------------------------------------------------------------------------
CursorSpec 	ProxyViewDragDropSource::GetDragCursor(DragDrop::eTargetResponse, bool16 ) const
{
	bool16 optionKeyDown = ::IsOptionAltKeyPressed();
	return CursorSpec(kAppUIPluginID, optionKeyDown ? kCrsrPointyHandCopy : kCrsrPointyHand);
}

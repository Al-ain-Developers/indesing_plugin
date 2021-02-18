//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/ProxyViewDragDropSource.cpp $
//  
//  Owner: Tim Wright
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
//  Based on ProxyViewDragDropSource.cpp in Layer Panel Project
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interface Includes -----
#include "IControlView.h"
#include "IDocument.h"
#include "IListBoxController.h"
#include "IListControlDataOf.h"
#include "IPanelControlData.h"
#include "IStateData.h"
#include "ITransform.h"
#include "IUIDData.h"
#include "IWidgetParent.h"

// ----- Implementation Includes -----

#include "CDragDropSource.h"
#include "widgetid.h"

#include "HelperInterface.h"
#include "CmdUtils.h"
#include "ILayoutUIUtils.h"
#include "EventUtilities.h"

#include "FormFieldUIID.h"
#include "FormFieldUIDefs.h"
#include "PMFlavorTypes.h"
#include "SystemUtils.h"



class ProxyViewDragDropSource : public CDragDropSource
{
public:
	ProxyViewDragDropSource(IPMUnknown *boss);
	virtual ~ProxyViewDragDropSource();

	virtual bool16		DoAddDragContent(IDragDropController*);
	
	virtual SysWireframe 		DoMakeDragOutlineRegion() const;

	DECLARE_HELPER_METHODS()
};


CREATE_PMINTERFACE(ProxyViewDragDropSource, kAPProxyViewDragDropSourceImpl)
DEFINE_HELPER_METHODS(ProxyViewDragDropSource)

ProxyViewDragDropSource::ProxyViewDragDropSource(IPMUnknown *boss)  :
	CDragDropSource(boss),
	HELPER_METHODS_INIT(boss)
{
}


ProxyViewDragDropSource::~ProxyViewDragDropSource()
{
}

//--------------------------------------------------------------------------------------
// DoAddDragContent
//--------------------------------------------------------------------------------------
bool16 ProxyViewDragDropSource::DoAddDragContent(IDragDropController* controller)
{
	// Obtain a handler for our internal data flavor
	InterfacePtr<IDataExchangeHandler> ourHandler(controller->QueryHandler(kPMStateProxyFlavor));
	
	// Don't promise anything if we couldn't get a handler
	if (!ourHandler)
		return kFalse;
	
	// Place the appropriate data or data reference into the handler
	InterfacePtr<IStateData> data(ourHandler, IID_ISTATEDATA);
	if (data)
	{
		// Get the currently selected state and store it
		InterfacePtr<IListBoxController> listBoxCtlr(this, IID_ILISTBOXCONTROLLER);
		int32 stateIndex = listBoxCtlr->GetSelected();
		InterfacePtr< IListControlDataOf<IControlView*> > listData(this, IID_ILISTCONTROLDATA);
		InterfacePtr<IStateData> listElementStateData((*listData)[stateIndex], IID_ISTATEDATA);
		Form::AppearanceState state = listElementStateData->GetState();
		data->Set(state);
	}
	
	// Install our handler so we can fulfill promises we make below
	controller->SetSourceHandler(ourHandler) ;
	
	// Add a data item and promise the appropriate data flavors
	//	Note that in this case we promise only one since the internal flavor and external flavor are the same.
	InterfacePtr<IPMDataObject> item(controller->AddDragItem(1));
	PMFlavorFlags flavorFlags = 0;
	item->PromiseFlavor(kPMStateProxyFlavor, flavorFlags);

	return kTrue;
}


//--------------------------------------------------------------------------------------
// DoMakeDragOutlineRegion
//--------------------------------------------------------------------------------------
SysWireframe ProxyViewDragDropSource::DoMakeDragOutlineRegion() const
{
	// Get the currently selected state
	InterfacePtr<IListBoxController> listBoxCtlr(this, IID_ILISTBOXCONTROLLER);
	int32 stateIndex = listBoxCtlr->GetSelected();
	
	// Get the bounds of the selected state
	PMRect bbox;
	listBoxCtlr->GetVisibleItemBounds(stateIndex, bbox);
	
	// Translate from internal to window coords
	InterfacePtr<IControlView> iPanelView(this, IID_ICONTROLVIEW);
	iPanelView->ContentToWindowTransform(&bbox);
	SysRect dragRect(::ToSys(bbox));
	
	// The bounding box is in local coords, but the draggable region has
	// to be in global coords.
	dragRect = ::ToSys(iPanelView->WindowToGlobal(dragRect));
	
	// Build the outline region
	SysWireframe rectRgn = (SysWireframe) DragDrop::kDefaultDragOutline;
	rectRgn = ::CreateRectSysWireframe(dragRect);

	::InsetSysRect(dragRect, 1, 1);
	SysWireframe insideRgn = ::CreateRectSysWireframe(dragRect);

	::DiffSysWireframe(rectRgn, insideRgn, rectRgn);
	::DeleteSysWireframe(insideRgn);
	
	return rectRgn;
}

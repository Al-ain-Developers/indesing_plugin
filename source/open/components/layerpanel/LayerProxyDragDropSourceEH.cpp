//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerProxyDragDropSourceEH.cpp $
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
//  Implementation of event handler that detects drag operations
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IActionManager.h"
#include "IApplication.h"
#include "IBoolData.h"
#include "IDocument.h"
#include "IDocumentLayer.h"
#include "IDragDropController.h"
#include "IDragDropSource.h"
#include "IEvent.h"
#include "ILayerList.h"
#include "IMenuManager.h"
#include "IPanelControlData.h"
#include "ISession.h"
#include "ITextControlData.h"
#include "IWidgetParent.h"
#include "ITreeNodeIDData.h"
#include "ILayoutSelectionSuite.h"
#include "ISelectionProxyDrawData.h"
#include "ITreeNodeIDData.h"
#include "IEventDispatcher.h"
#include "IEventUtils.h"

// ----- Includes -----

#include "LayerTreeUIDNodeID.h"


// ----- Utility files -----

#include "CmdUtils.h"
#include "EventUtilities.h"
#include "LayerPanelUtils.h"
#include "IPalettePanelUtils.h"
#include "GenericID.h"

// ----- ID.h files -----

#include "DragDropID.h"
#include "LayerPanelID.h"
#include "widgetid.h"

#include "DVHostedWidgetEH.h"

class LayerProxyDragDropSourceEH : public DVHostedWidgetEH
{
	typedef DVHostedWidgetEH inherited;

	public:
						LayerProxyDragDropSourceEH(IPMUnknown *boss);
		virtual 		~LayerProxyDragDropSourceEH();
			
		virtual bool16 LButtonDn(IEvent* e); 
		virtual bool16 LButtonUp(IEvent* e); 
		virtual bool16 RButtonDn(IEvent* e);
		virtual bool16 ButtonDblClk(IEvent* e);
		
	private:
		bool fGotMouseDown;
		DECLARE_HELPER_METHODS()
};

//========================================================================
// Class LayerProxyDragDropSourceEH
//========================================================================
#pragma mark LayerProxyDragDropSourceEH implementation

CREATE_PMINTERFACE(LayerProxyDragDropSourceEH, kLayerProxyDragDropSourceEHImpl)
DEFINE_HELPER_METHODS(LayerProxyDragDropSourceEH)

LayerProxyDragDropSourceEH::LayerProxyDragDropSourceEH(IPMUnknown *boss) :  inherited(boss),
																			HELPER_METHODS_INIT(boss),fGotMouseDown(false)
{
}

LayerProxyDragDropSourceEH::~LayerProxyDragDropSourceEH()
{
}
	

//--------------------------------------------------------------------------------------
// LButtonDn
//--------------------------------------------------------------------------------------
bool16 LayerProxyDragDropSourceEH::LButtonDn(IEvent* e)
{
	// Bool value will be true if items on this layer are selected
	InterfacePtr<const ISelectionProxyDrawData> drawData(this, UseDefaultIID());
	if (drawData->GetDrawingMode() == ISelectionProxyDrawData::kSelected)
	{
		InterfacePtr<IDragDropSource> dragSource(this, IID_IDRAGDROPSOURCE);
		if (dragSource && dragSource->WillDrag(e))
		{
			
			// Check to see if user is trying to start a drag
			bool16 isPatientUser;
			if (::IsUserStartingDrag(e, isPatientUser))
			{
				InterfacePtr<IDragDropController> ddController(GetExecutionContextSession(), IID_IDRAGDROPCONTROLLER);
				if (ddController)
				{
					ddController->StartDrag(dragSource, e);	
					e->SetSystemHandledState(IEvent::kDontCall);
					return kTrue; // Make up for the fact that StartDrag will swallow the mouse up
				}
			}
		}
	}
	InterfacePtr<const IControlView> myView(this, UseDefaultIID());
	if(!myView->IsEnabled())
		return kFalse;

	fGotMouseDown = true;
	// push our EH onto the stack, and capture the mouse, so we are sure to get mouse up events
	InterfacePtr<const IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IEventDispatcher> dispatcher(theApp, IID_IEVENTDISPATCHER);
	dispatcher->Push(this);

#ifdef WINDOWS
	// Capture the mouse so that mouse events will come back to this window even
	// when the mouse goes outside the window. [amb]
	InterfacePtr<IControlView> capView(this, UseDefaultIID());
	
	(Utils<IEventUtils>())->PMCaptureMouse(capView);
#endif

	return kTrue;
}

bool16 LayerProxyDragDropSourceEH::LButtonUp(IEvent* e)
{
	//Release the captured mouse and pop this event handler so it no longer responds to mouse events outside it's bounds.

	if(fGotMouseDown)
	{
		fGotMouseDown = false;
		(Utils<IEventUtils>())->PMReleaseMouse();

		InterfacePtr<const IApplication> theApp(GetExecutionContextSession()->QueryApplication());
		InterfacePtr<IEventDispatcher> dispatcher(theApp, IID_IEVENTDISPATCHER);
		dispatcher->Remove(this);

		InterfacePtr<IControlView> myView(this, UseDefaultIID());
		
		if(!myView->IsEnabled())
			return kFalse;

		SysPoint localWhere = ::ToSys(myView->GlobalToWindow(e->GlobalWhere()));
		if(myView->HitTest(localWhere)) 
		{
			if(LayerPanelUtils::SelectAssociatedItemsInLayout(this,e->ShiftKeyDown(),e->OptionAltKeyDown(),e->CmdKeyDown()))
				return kTrue;
			return inherited::LButtonDn(e);
		}
	}
	return kFalse;
}

//---------------------------------------------------------------
// LayerProxyDragDropSourceEH::RButtonDn
//---------------------------------------------------------------

bool16 LayerProxyDragDropSourceEH::RButtonDn(IEvent* e)
{
	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IActionManager> actionMgr(theApp->QueryActionManager());
	InterfacePtr<IMenuManager> menuMgr(actionMgr, UseDefaultIID());
	
	menuMgr->HandlePopupMenu("RtMenuLayerPanelItem", e->GlobalWhere(), e->GlobalWhere(), kTrue, this);
	
	return kTrue;
}

//---------------------------------------------------------------
// LayerProxyDragDropSourceEH::ButtonDblClk
//---------------------------------------------------------------

bool16 LayerProxyDragDropSourceEH::ButtonDblClk(IEvent* ) 
{
	bool16 handled = kTrue;

	InterfacePtr<const IWidgetParent>	widgetParent(this, UseDefaultIID());
	InterfacePtr<const ITreeNodeIDData>	nodeData((ITreeNodeIDData*)widgetParent->QueryParentFor(IID_ITREENODEIDDATA));
	if(nodeData)
	{
		TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(nodeData->Get());
		if(uidNode->IsLayerEntry())
		{
			// Get the IPanelControlData for the layer panel itself
			InterfacePtr<IPanelControlData> layerPanelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kLayerParentWidgetId));

			LayerPanelUtils::InvokeLayerDialog(LayerPanelUtils::kLayerOptionsDialog, LayerPanelUtils::kAboveActive, layerPanelData, nil);
		}
	}
	
	return handled;
}

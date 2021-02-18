//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerSelectionObserver.cpp $
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
//  Purpose:	Observes the selection in order to change the active layer.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IControlView.h"
#include "IDocument.h"
#include "IDocumentLayer.h"
#include "IHierarchy.h"
#include "ILayerList.h"
#include "ILayerSuite.h"
#include "ILayoutCmdData.h"
#include "ILayoutControlData.h"
#include "ILayoutTarget.h"
#include "IPanelControlData.h"
#include "ISelectionManager.h"
#include "ISpreadLayer.h"
#include "ISubject.h"
#include "IWidgetParent.h"
#include "IWindow.h"

// ----- Includes -----

#include "SelectionObserver.h"
#include "UIDList.h"

// ----- Utility files -----

#include "CmdUtils.h"
#include "ILayoutUIUtils.h"
#include "IPageItemUtils.h"
#include "ISelectionUtils.h"
#include "LayerPanelUtils.h"
// ----- ID.h files -----

#include "LayerPanelID.h"

//========================================================================================
// class LayerSelectionObserver
//========================================================================================

class LayerSelectionObserver : public ActiveSelectionObserver
{
	public:
		LayerSelectionObserver(IPMUnknown *boss);
		virtual ~LayerSelectionObserver();

	protected:
		//________________________________________________________________________________________
		//  DESCR:      Everything relating to the selection should update.
		//
		//              Either  (a) there is a new active selection
		//              or      (b) the items in the selection has changed
		//________________________________________________________________________________________
		virtual void    HandleSelectionChanged (const ISelectionMessage*);
		
		virtual void    HandleSelectionAttributeChanged(const ISelectionMessage *msg);
		
};


CREATE_PMINTERFACE(LayerSelectionObserver, kLayerSelectionObserverImpl)

//----------------------------------------------------------------------------------------
// LayerSelectionObserver::LayerSelectionObserver
//----------------------------------------------------------------------------------------

LayerSelectionObserver::LayerSelectionObserver(IPMUnknown *boss) :
	ActiveSelectionObserver(boss, IID_ILAYERSELECTIONOBSERVER)
{
}

//----------------------------------------------------------------------------------------
// LayerSelectionObserver::~LayerSelectionObserver
//----------------------------------------------------------------------------------------

LayerSelectionObserver::~LayerSelectionObserver()
{
}

//----------------------------------------------------------------------------------------
// LayerSelectionObserver::HandleSelectionChanged
//
// Watch the selection to see if we need to change the active layer.
// As the user clicks on objects on different layers, active layer changes to match.
//----------------------------------------------------------------------------------------

void LayerSelectionObserver::HandleSelectionChanged(const ISelectionMessage*)
{
	if (fCurrentSelection && fCurrentSelection->IsInterfaceEnabled (IID_ILAYERSUITE))
	{
		InterfacePtr<ILayerSuite>    iLayerSuite ( static_cast<ILayerSuite*>(QueryAbstractSelection(IID_ILAYERSUITE)));

		ASSERT_MSG (iLayerSuite != nil, "LayerSelectionObserver::HandleSelectionChanged, ILayerSuite is nil.");

		// Get list of document layers for items in selection
		IDataBase* db = fCurrentSelection->GetDataBase();
		UIDList docLayerList(db);
		iLayerSuite->GetSelectedLayers(docLayerList);

		// Get the active layer for this layout view
		// rgano: It seems like there should be a better way to get the window we are working on.
		InterfacePtr<IWidgetParent> widgetParent(fCurrentSelection->GetSelectionsOwner(), UseDefaultIID());
		InterfacePtr<IWindow> window(static_cast<IWindow*>(widgetParent ? widgetParent->QueryParentFor(IID_IWINDOW) : nil));
		InterfacePtr<ILayoutControlData> layoutData(window ? Utils<ILayoutUIUtils>()->QueryLayoutData(window) : nil);
			
		if (layoutData)
			{
				UID	activeLayerUID = layoutData->GetActiveDocLayerUID();
				InterfacePtr<IDocument>	document(db, db->GetRootUID(), IID_IDOCUMENT);
				InterfacePtr<ILayerList> layerList(document, IID_ILAYERLIST);

				// See if any items in selection are on active layer.
				int32 index = -1;
				int32 numLayers = docLayerList.Length();
				for (int32 i = 0; i < numLayers && index == -1; i++)
				{
					index = docLayerList.Location(activeLayerUID);
				}

				// If none of the objects in the current selection is
				// on the current active layer, we change the active layer.
				if (index == -1 && docLayerList.Length())
				{
					LayerPanelUtils::DoSetActiveLayer(docLayerList.GetRef(0),layoutData);
				}
			}
	}
}

//----------------------------------------------------------------------------------------
// LayerSelectionObserver::HandleSelectionChanged:
//----------------------------------------------------------------------------------------

void LayerSelectionObserver::HandleSelectionAttributeChanged(const ISelectionMessage *msg)
{
	// Make sure that the attribute that changed is one we care about
	if (msg && msg->WasSuiteAffected(IID_ILAYERSUITE))
	{
		// Selection doesn't actually change when items move to a new layer, but
		// the "what layer am I on" attribute does. Handle as if selection changed
		// so that the active layer will update if selected items are moved to a new layer.
		HandleSelectionChanged(nil);
	}
}

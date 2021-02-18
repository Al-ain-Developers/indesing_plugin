//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/dialogs/ListBoxListZOrderDDSource.cpp $
//  
//  Owner: SusanCL
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
//  Drag source for z-order reordering of the swatches "name view" panel
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IIntData.h"
#include "IListBoxController.h"
#include "IListControlDataOf.h"
#include "IPanelControlData.h"
#include "IRenderingObject.h"
#include "ITriStateControlData.h"
#include "IWidgetParent.h"

// ----- Includes -----

#include "CDragDropSource.h"
#include "CursorDefs.h"
#include "FormFieldUIDefs.h"
#include "PMFlavorTypes.h"

// ----- ID.h files -----

#include "AppUIID.h"
#include "DragDropID.h"
#include "FormFieldUIID.h"
#include "widgetid.h"

//========================================================================================

class ListBoxListZOrderDDSource : public CDragDropSource
{
public:
	ListBoxListZOrderDDSource(IPMUnknown *boss);
	virtual ~ListBoxListZOrderDDSource();

	virtual bool16		DoAddDragContent(IDragDropController*);
	virtual	CursorSpec 	GetDragCursor(DragDrop::eTargetResponse dropEffect, bool16 isDragLocal) const;

private:
	DECLARE_HELPER_METHODS()
};


//______________________________________________________________________________________
// Class ListBoxListZOrderDDSource
//______________________________________________________________________________________

CREATE_PMINTERFACE(ListBoxListZOrderDDSource, kListBoxListZOrderDDSourceImpl)
DEFINE_HELPER_METHODS(ListBoxListZOrderDDSource)

ListBoxListZOrderDDSource::ListBoxListZOrderDDSource(IPMUnknown *boss) :
	CDragDropSource(boss),
	HELPER_METHODS_INIT(boss)
{
}

ListBoxListZOrderDDSource::~ListBoxListZOrderDDSource()
{
}

//______________________________________________________________________________________
// DoAddDragContent
//______________________________________________________________________________________

bool16 ListBoxListZOrderDDSource::DoAddDragContent(IDragDropController* controller)
{
	//Look at (optional) sort check box.  If checked, disallow dragging
	//That is, don't let the list become unsorted.

	InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
	InterfacePtr<IPanelControlData> panelData((IPanelControlData*) parentHolder->QueryParentFor(IID_IPANELCONTROLDATA));

	IControlView* iSortCheckView = panelData->FindWidget(kListBoxSortItemsWID);
	if (iSortCheckView)
	{
		InterfacePtr<ITriStateControlData> iSortCheck( iSortCheckView, IID_ITRISTATECONTROLDATA );
		
		if ( iSortCheck && !iSortCheck->IsDeselected() ) //disallow if sort is selected, unknown...
			return kFalse;
	}

	//Its okay to drag, so provide drag content consisting of the index of the selected item
	//(so we can move it within the list later on in the DragDropTarget...)


	// Obtain a handler for our internal data flavor
	InterfacePtr<IDataExchangeHandler> ourHandler(controller->QueryHandler(kPMListBoxZOrderFlavor));
	
	// Don't promise anything if we couldn't get a handler
	if (!ourHandler)
		return kFalse;
	
	// Place the appropriate data or data reference into the handler
	// In this case, its just the list index to drag....

	InterfacePtr<IListBoxController> listController(this, IID_ILISTBOXCONTROLLER);
	int32 selectedIndex = listController->GetSelected();
	
	InterfacePtr<IIntData> data(ourHandler, IID_IINTDATA);
	if (data) {
		data->Set(selectedIndex);
	}
	
	// Install our handler so we can fulfill promises we make below
	controller->SetSourceHandler(ourHandler) ;
	
	// Add a data item and promise the appropriate data flavors
	//	Note that in this casewe promise only one since the internal flavor and external flavor are the same.
	InterfacePtr<IPMDataObject> item(controller->AddDragItem(1));
	PMFlavorFlags flavorFlags = 0;
	item->PromiseFlavor(kPMListBoxZOrderFlavor, flavorFlags);

	return kTrue;
}

//______________________________________________________________________________________
// GetDragCursor
//______________________________________________________________________________________

CursorSpec 	ListBoxListZOrderDDSource::GetDragCursor(DragDrop::eTargetResponse dropEffect, bool16 isDragLocal) const
{
	return CursorSpec(kAppUIPluginID, kCrsrClosedHand);
}
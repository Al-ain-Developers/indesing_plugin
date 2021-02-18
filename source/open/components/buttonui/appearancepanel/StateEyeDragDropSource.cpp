//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/StateEyeDragDropSource.cpp $
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
//  Based on LayerEyeDragDropSource.cpp in Layer Panel Project
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IAppearanceSuite.h"
#include "IBoolData.h"
#include "IDocument.h"
#include "IDocumentLayer.h"
#include "IStateData.h"
#include "IWidgetParent.h"

// ----- Includes -----

#include "CDragDropSource.h"
#include "FormFieldUIDefs.h"
#include "PMFlavorTypes.h"
#include "HelperInterface.h"

// ----- Utility files -----

#include "CmdUtils.h"
#include "FormFieldUIUtils.h"
#include "ILayoutUIUtils.h"

// ----- ID.h files -----

#include "AppUIID.h"
#include "FormFieldUIID.h"
#include "widgetid.h"

class StateEyeDragDropSource : public CDragDropSource
{
public:
	StateEyeDragDropSource(IPMUnknown *boss);
	virtual ~StateEyeDragDropSource();

	virtual SysWireframe		DoMakeDragOutlineRegion() const	{ return nil; }
		// No drag outline region needed for eye

	virtual bool16		DoAddDragContent(IDragDropController*);
	virtual CursorSpec 	GetDragCursor(DragDrop::eTargetResponse, bool16 isDragLocal) const;

		DECLARE_HELPER_METHODS()
};


CREATE_PMINTERFACE(StateEyeDragDropSource, kStateEyeDragDropSourceImpl)
DEFINE_HELPER_METHODS(StateEyeDragDropSource)

StateEyeDragDropSource::StateEyeDragDropSource(IPMUnknown *boss)  :
	CDragDropSource(boss),
	HELPER_METHODS_INIT(boss)
{
}


StateEyeDragDropSource::~StateEyeDragDropSource()
{
}

//--------------------------------------------------------------------------------------
// DoAddDragContent
//--------------------------------------------------------------------------------------
bool16 StateEyeDragDropSource::DoAddDragContent(IDragDropController* controller)
{
	// Obtain a handler for our internal data flavor
	InterfacePtr<IDataExchangeHandler> ourHandler(controller->QueryHandler(kPMStateEyeFlavor));
	
	// Don't promise anything if we couldn't get a handler
	if (!ourHandler)
		return kFalse;
	
	// Place the appropriate data or data reference into the handler
	InterfacePtr<IStateData> data(ourHandler, IID_ISTATEDATA);
	if (data)
	{
		// Get the layer UID ref for this layer, store it
		InterfacePtr<IWidgetParent>	widgetParent(this, IID_IWIDGETPARENT);
		InterfacePtr<IStateData>	listElementStateData(widgetParent->GetParent(), IID_ISTATEDATA);
		data->Set(listElementStateData->Get());

		// Place the appropriate data or data reference into the handler
		InterfacePtr<IBoolData> boolData(ourHandler, IID_IBOOLDATA);
		if (boolData)
		{
			InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
			Form::Appearance appearance;
			if (iAppearanceSuite && iAppearanceSuite->GetAppearance( listElementStateData->Get(), &appearance ))
			{
				boolData->Set(appearance.fEnabled);
			}
		}
	}
	
	// Install our handler so we can fulfill promises we make below
	controller->SetSourceHandler(ourHandler) ;
	
	// Add a data item and promise the appropriate data flavors
	//	Note that in this case we promise only one since the internal flavor and external flavor are the same.
	InterfacePtr<IPMDataObject> item(controller->AddDragItem(1));
	PMFlavorFlags flavorFlags = 0;
	item->PromiseFlavor(kPMStateEyeFlavor, flavorFlags);

	return kTrue;
}

//--------------------------------------------------------------------------------------
// GetDragCursor
//--------------------------------------------------------------------------------------
CursorSpec 	StateEyeDragDropSource::GetDragCursor(DragDrop::eTargetResponse, bool16 isDragLocal) const
{
	return CursorSpec(kAppUIPluginID, kCrsrPointyHand);
}


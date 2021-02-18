//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerListLayoutAction.cpp $
//  
//  Owner: Robin Briggs
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
//  An interface off the document, manages the list of document-wide layers.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IActiveContext.h"
#include "IApplication.h"
#include "IDocument.h"
#include "ILayerList.h"
#include "ILayoutAction.h"
#include "ILayoutControlData.h"
#include "IObserver.h"
#include "ISession.h"
#include "ISubject.h"
#include "IToolManager.h"

// ----- Includes -----

#include "HelperInterface.h"

// ----- ID.h files -----

#include "LayerPanelID.h"

class LayerListLayoutAction : public ILayoutAction
{
public:
	LayerListLayoutAction(IPMUnknown *boss);
	
	void SetSpread(ILayoutControlData *, const UIDRef& )
		{}
	void RemoveSpread(ILayoutControlData *, const UIDRef& )
		{}
	void SetDocument(ILayoutControlData *, const UIDRef& );

	void RemoveDocument(ILayoutControlData *, const UIDRef& );
	
DECLARE_HELPER_METHODS()
};

DEFINE_HELPER_METHODS(LayerListLayoutAction)
CREATE_PMINTERFACE(LayerListLayoutAction, kLayerListLayoutActionImpl)

LayerListLayoutAction::LayerListLayoutAction(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss)
{
}


void LayerListLayoutAction::SetDocument(ILayoutControlData *layout, const UIDRef& docInWindow)
{
	InterfacePtr<ISubject> documentSubject(docInWindow, IID_ISUBJECT);
	InterfacePtr<IObserver> layerListObserver(layout, IID_ILAYOUTLAYERLISTOBSERVER);

	// Attach observer to get LayerList messages
	if (documentSubject)
		documentSubject->AttachObserver(ISubject::kBothAttachments,layerListObserver, IID_ILAYERLIST, IID_ILAYOUTLAYERLISTOBSERVER);
	
	// Attach to layout control data.
	// Each layout control data has its own active layer, so the lock cursor could change.
	InterfacePtr<ISubject> lcdSubject(layout, IID_ISUBJECT);
	if (lcdSubject)
	{
		// Do only observer. We now snapshot the state of the cursor manager.
		// We therefore need not update after the active layer changed at undo.
		lcdSubject->AttachObserver(ISubject::kRegularAttachment,layerListObserver, IID_IACTIVELAYER, IID_ILAYOUTLAYERLISTOBSERVER);
	}

	// Attach to active context (for IID_ICONTROLVIEW changes)
	IActiveContext* activeContext = GetExecutionContextSession()->GetActiveContext();
	InterfacePtr<ISubject> contextSubject(activeContext, IID_ISUBJECT);
	if (contextSubject)
		contextSubject->AttachObserver(ISubject::kRegularAttachment,layerListObserver, IID_IACTIVECONTEXT,IID_ILAYOUTLAYERLISTOBSERVER);

	// The layer list observer needs to be informed of tool changes so that it can update the mouse cursor
	// when the active layer is locked.
	// this should move to a better place. Only need to attach to the app once, not once per doc change.
	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IToolManager> toolMgr(app->QueryToolManager());
	InterfacePtr<ISubject> toolMgrSubject( toolMgr, IID_ISUBJECT);
	if( toolMgrSubject )
		toolMgrSubject->AttachObserver(ISubject::kRegularAttachment,layerListObserver, IID_ITOOLMANAGER,IID_ILAYOUTLAYERLISTOBSERVER);
}


void LayerListLayoutAction::RemoveDocument(ILayoutControlData *layout, const UIDRef& docInWindow)
{
	InterfacePtr<ISubject> documentSubject(docInWindow, IID_ISUBJECT);

	InterfacePtr<IObserver> layerListObserver(layout, IID_ILAYOUTLAYERLISTOBSERVER);

	if (documentSubject)
		documentSubject->DetachObserver(ISubject::kBothAttachments,layerListObserver, IID_ILAYERLIST, IID_ILAYOUTLAYERLISTOBSERVER);

	InterfacePtr<ISubject> lcdSubject(layout, IID_ISUBJECT);
	if (lcdSubject)
	{
		lcdSubject->DetachObserver(ISubject::kRegularAttachment,layerListObserver, IID_IACTIVELAYER, IID_ILAYOUTLAYERLISTOBSERVER);
	}

	IActiveContext* activeContext = GetExecutionContextSession()->GetActiveContext();
	InterfacePtr<ISubject> contextSubject(activeContext, IID_ISUBJECT);
	if (contextSubject)
		contextSubject->DetachObserver(ISubject::kRegularAttachment,layerListObserver, IID_IACTIVECONTEXT,IID_ILAYOUTLAYERLISTOBSERVER);

	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IToolManager> toolMgr(app->QueryToolManager());
	InterfacePtr<ISubject> toolMgrSubject( toolMgr, IID_ISUBJECT);
	if( toolMgrSubject )
		toolMgrSubject->DetachObserver(ISubject::kRegularAttachment,layerListObserver, IID_ITOOLMANAGER, IID_ILAYOUTLAYERLISTOBSERVER);
}



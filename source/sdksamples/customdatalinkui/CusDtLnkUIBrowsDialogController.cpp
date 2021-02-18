//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalinkui/CusDtLnkUIBrowsDialogController.cpp $
//  
//  Owner: Adobe Developer Technologies
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

// Interface includes:
#include "IWidgetParent.h"
#include "IPanelControlData.h"
#include "ITreeViewController.h"
#include "IDocument.h"
#include "IIntData.h"
#include "IUIDData.h"
#include "ILinkFacade.h"

// General includes:
#include "CDialogController.h"
#include "ILayoutUIUtils.h"
#include "URI.h"


// Project includes:
#include "CusDtLnkUIFileNodeID.h"
#include "CusDtLnkUITreeDataNode.h"
#include "ICusDtLnkUITreeDataModel.h"
#include "ICusDtLnkFacade.h"
#include "CusDtLnkUIID.h"
#include "K2Vector.tpp"

/** Implements IDialogController for the browse-for-link
	
	@ingroup customdatalinkui
	
*/
class CusDtLnkUIBrowsDialogController : public CDialogController
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	CusDtLnkUIBrowsDialogController(IPMUnknown* boss) : CDialogController(boss) {}

	/**
		Initializes each widget in the dialog with its default value.
		Called when the dialog is opened.
		@param dlgContext
	*/
	virtual void InitializeDialogFields( IActiveContext* dlgContext);

	/**
		Validate the values in the widgets. 
		By default, the widget with ID kOKButtonWidgetID causes 
		this method to be called. When all widgets are valid, 
		ApplyFields will be called.		
		@param myContext
		@return kDefaultWidgetId if all widget values are valid, WidgetID of the widget to select otherwise.

	*/
	virtual WidgetID ValidateDialogFields( IActiveContext* myContext);

	/**
		Retrieve the values from the widgets and act on them.
		@param myContext
		@param widgetId identifies the widget on which to act.
	*/
	virtual void ApplyDialogFields( IActiveContext* myContext, const WidgetID& widgetId);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(CusDtLnkUIBrowsDialogController, kCusDtLnkUIBrowsDialogControllerImpl)

/* ApplyFields
*/
void CusDtLnkUIBrowsDialogController::InitializeDialogFields( IActiveContext* dlgContext) 
{
	// Put code to initialize widget values here.
}

/* ValidateFields
*/
WidgetID CusDtLnkUIBrowsDialogController::ValidateDialogFields( IActiveContext* myContext) 
{
	WidgetID result = kNoInvalidWidgets;

	// Put code to validate widget values here.

	return result;
}

/* ApplyFields
*/
void CusDtLnkUIBrowsDialogController::ApplyDialogFields( IActiveContext* myContext, const WidgetID& widgetId) 
{
	do
	{
        InterfacePtr<IWidgetParent> widgetParent(this,UseDefaultIID());
        if (!widgetParent)
			break;

        InterfacePtr<IPanelControlData> panelData((IPanelControlData*)widgetParent->QueryParentFor(IID_IPANELCONTROLDATA));
  
		//get selected value on the panel and insert into the document
        IControlView* treeWidget = panelData->FindWidget(kCusDtLnkUITreeViewWidgetID);
        ASSERT(treeWidget);
        if(!treeWidget) {
            break;
        }

        InterfacePtr<ITreeViewController>     controller(treeWidget, UseDefaultIID());
        ASSERT(controller);
        if(!controller)
        {
            break;
        }

        NodeIDList selectedItems;
        controller->GetSelectedItems(selectedItems);
		TreeNodePtr<CusDtLnkUIFileNodeID> nodeID(selectedItems[0]);
		ASSERT(nodeID);
		if(!nodeID) {
			break;
		}
		PMString uk(nodeID->GetUniqueKey());

		InterfacePtr<ICusDtLnkUITreeDataModel> model(controller, UseDefaultIID());
		ASSERT(model);
		if(!model) {
			break;
		}
		CusDtLnkUITreeDataNode* dataNode = model->GetNode(uk);
		ASSERT(dataNode);
		if(!dataNode) {
			break;
		}
		// If an asset, think about loading place gun
		if(dataNode->GetNodeType() == CusDtLnkUITreeDataNode::eAssetType) {
			URI uri = dataNode->GetURIFromNode();
			if(uri.VerifyURI()) {
				InterfacePtr<IIntData> whichDialog(this, UseDefaultIID());
				if (whichDialog->GetInt() == kRelinkDialog)
				{
					InterfacePtr<IUIDData> linkRef(this, UseDefaultIID());
					if (linkRef)
					{
						UID newLinkUID;
						Utils<Facade::ILinkFacade>()->RelinkLink(linkRef->GetRef(), uri, kMinimalUI, newLinkUID);
					}
				}
				else
				{
					IDocument* doc = Utils<ILayoutUIUtils>()->GetFrontDocument();
					if(doc) {
						UIDRef docUIDRef = ::GetUIDRef(doc);
						UIDRef loadedImage = 
							Utils<ICusDtLnkFacade>()->ImportImageAndLoadPlaceGun(docUIDRef,
							uri);
					}
				}
			}
		}
	} while (kFalse);
}

// End, CusDtLnkUIBrowsDialogController.cpp.




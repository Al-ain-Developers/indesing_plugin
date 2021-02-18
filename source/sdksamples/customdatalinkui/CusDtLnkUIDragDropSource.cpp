//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalinkui/CusDtLnkUIDragDropSource.cpp $
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
#include "ITreeNodeIDData.h"
#include "IDragDropController.h"
#include "IDataExchangeHandler.h"
#include "IStringData.h"
#include "IPMDataObject.h"
#include "ICusDtLnkFacade.h"
#include "IWidgetParent.h"
#include "ICusDtLnkUITreeDataModel.h"
// General includes:
#include "CDragDropSource.h"
#include "SDKFileHelper.h"
#include "DocumentID.h"
#include "Utils.h"

// Project includes:
#include "CusDtLnkUIID.h"
#include "CusDtLnkUIFileNodeID.h"
#include "CusDtLnkUITreeDataNode.h"

/** Provides the node with drag source capabilit
	@ingroup customdatalinkui
	
*/
class CusDtLnkUIDragDropSource : public CDragDropSource
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	CusDtLnkUIDragDropSource(IPMUnknown* boss);

	/**
		Destructor.
	*/
	~CusDtLnkUIDragDropSource();

	/** Returns kTrue if a unique key is associated with the widget.
		@param event [IN] that signifies the drag.
		@return kTrue if a drag can be initiated, otherwise kFalse.
	*/
	bool16 WillDrag(IEvent* event) const;

	/** Adds the unique key to the drag.
		@param controller [IN] in charge of this widget's DND capabilities.
		@return kTrue if valid content has been added to the drag, kFalse otherwise.
	*/
	bool16 DoAddDragContent(IDragDropController* controller);

private:
	/** Gets the unique key associated with this widget.
		@param outUK [OUT] specifies unique key.
		@return kTrue if can do, kFalse otherwise.
	 */
	bool16 getContentAssetUniqueKey(PMString& outUK) const;

	/** Gets the URI associated with this widget.
		@param outContentAssetURI [OUT] specifies URI.
		@return kTrue if can do, kFalse otherwise.
	 */
	bool16 getContentAssetURI(URI& outContentAssetURI) const;


	/** Adds  data to the drag 
		@param controller [IN] in charge of this widget's DND capabilities.
		@return kTrue if valid content has been added to the drag, 
			kFalse otherwise.
	 */
	bool16 doAddMyDragContent(IDragDropController* controller);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(CusDtLnkUIDragDropSource, kCusDtLnkUIDragDropSourceImpl)

/* Constructor
*/
CusDtLnkUIDragDropSource::CusDtLnkUIDragDropSource(IPMUnknown* boss)
: CDragDropSource(boss)
{
}


/* Destructor
*/
CusDtLnkUIDragDropSource::~CusDtLnkUIDragDropSource()
{
}


/* WillDrag
*/
bool16 CusDtLnkUIDragDropSource::WillDrag(IEvent* event) const
{
	
	URI uri;
	return this->getContentAssetURI(uri);
	
}


/* DoAddDragContent
*/
bool16 CusDtLnkUIDragDropSource::DoAddDragContent(
	IDragDropController* controller)
{
	return this->doAddMyDragContent(controller);
}

/* getContentAssetURI
*/
bool16 CusDtLnkUIDragDropSource::getContentAssetURI(
	URI& outContentAssetURI) const
{
	bool16 result = kFalse;
	do {
		PMString uk;
		if (this->getContentAssetUniqueKey(uk) == kFalse) {
			break;
		}
	
		InterfacePtr<IWidgetParent> widgetParent(this, UseDefaultIID());
		ASSERT(widgetParent);
		if(!widgetParent) {
			break;
		}
		InterfacePtr<ICusDtLnkUITreeDataModel> model(
			static_cast<ICusDtLnkUITreeDataModel* >
				(widgetParent->QueryParentFor(ICusDtLnkUITreeDataModel::kDefaultIID)));
		ASSERT(model);
		if(!model) {
			break;
		}
		CusDtLnkUITreeDataNode* dataNode = model->GetNode(uk);
		ASSERT(dataNode);
		if(!dataNode) {
			break;
		}
		if(dataNode->GetNodeType() == CusDtLnkUITreeDataNode::eAssetType) {
			outContentAssetURI = dataNode->GetURIFromNode();
			if(outContentAssetURI.VerifyURI())
				result = kTrue;
		}
	} while(false);
	return result;
}


/* getContentAssetUniqueKey
*/
bool16 CusDtLnkUIDragDropSource::getContentAssetUniqueKey(
	PMString& outContentAssetUK) const
{
	bool16 result = kFalse;
	do {
		InterfacePtr<ITreeNodeIDData> 
			nodeData(this, UseDefaultIID());
		ASSERT(nodeData);
		if(!nodeData) {
			break;
		}
		TreeNodePtr<CusDtLnkUIFileNodeID> nodeID(nodeData->Get());
		ASSERT(nodeID);
		if(!nodeID) {
			break;
		}
		PMString uniqueAssetKey(nodeID->GetUniqueKey());
	
		InterfacePtr<IWidgetParent> widgetParent(this, UseDefaultIID());
		ASSERT(widgetParent);
		if(!widgetParent) {
			break;
		}
		InterfacePtr<ICusDtLnkUITreeDataModel> model(
			static_cast<ICusDtLnkUITreeDataModel* >
				(widgetParent->QueryParentFor(ICusDtLnkUITreeDataModel::kDefaultIID)));
		ASSERT(model);
		if(!model) {
			break;
		}
		CusDtLnkUITreeDataNode* dataNode = model->GetNode(uniqueAssetKey);
		ASSERT(dataNode);
		if(!dataNode) {
			break;
		}
		// If an asset, then we should be able to drag
		if(dataNode->GetNodeType() == CusDtLnkUITreeDataNode::eAssetType) {

			outContentAssetUK = uniqueAssetKey; 
			result = kTrue;

		}
	} while(false);
	return result;
}

/* doAddMyDragContent
*/
bool16 CusDtLnkUIDragDropSource::doAddMyDragContent(
	IDragDropController* controller)
{
	bool16 result = kFalse;

	do
	{
		// Stop if we can't determine the asset we are associated with.
		URI uri;
		if (this->getContentAssetURI(uri) == kFalse) {
			break;
		}

		// Point the controller at the handler.
		InterfacePtr<IDataExchangeHandler> 
			dataExchangeHandler(controller->QueryHandler(kCusDtLnkUIDragDropCustomFlavor));
		ASSERT(dataExchangeHandler);
		if (!dataExchangeHandler) {
			break;
		}
		if (dataExchangeHandler->IsEmpty() == kFalse) {
			dataExchangeHandler->Clear();
		}
		controller->SetSourceHandler(dataExchangeHandler);

		// Add the unique key for asset to be dragged.
		InterfacePtr<IStringData> 
			uniqueKeyStrungData(dataExchangeHandler, IID_ICUSDTLNKUIUNIQUEKEYSTRINGDATA);
		ASSERT(uniqueKeyStrungData);
		if (!uniqueKeyStrungData)
		{
			break;
		}
		PMString	uriStr(uri.GetURI().c_str());
		uniqueKeyStrungData->Set(uriStr);
			
		// Indicate the flavour in the drag object. 
		InterfacePtr<IPMDataObject>
			pmDataObject(controller->AddDragItem(1));
		ASSERT(pmDataObject);
		// no flavor flags	
		PMFlavorFlags flavorFlags = 0;
		
		// Set the type (flavour) in the drag object 
		pmDataObject->PromiseFlavor(kCusDtLnkUIDragDropCustomFlavor, flavorFlags);

		result = kTrue;

	} while(false);

	return result; 
}

// End, CusDtLnkUIDragDropSource.cpp.

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvDragDropSource.cpp $
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
#include "ISysFileListData.h"
#include "IPMDataObject.h"

// General includes:
#include "CDragDropSource.h"
#include "SDKFileHelper.h"
#include "DocumentID.h"

// Project includes:
#include "PnlTrvID.h"
#include "PnlTrvFileNodeID.h"

/** Provides the node with drag source capability for the IDFile
	(kPMSysFileFlavor) associated with the widget. This allows the
	IDFile selected in a tree view node to be dragged from the
	panel onto a drop target that accepts a IDFile. For example
	a layout view on a document.

	@ingroup paneltreeview
	
*/
class PnlTrvDragDropSource : public CDragDropSource
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	PnlTrvDragDropSource(IPMUnknown* boss);

	/**
		Destructor.
	*/
	~PnlTrvDragDropSource();

	/** Returns kTrue if a IDFile is associated with the widget.
		@param event [IN] that signifies the drag.
		@return kTrue if a drag can be initiated, otherwise kFalse.
	*/
	bool16 WillDrag(IEvent* event) const;

	/** Adds the IDFile to the drag.
		@param controller [IN] in charge of this widget's DND capabilities.
		@return kTrue if valid content has been added to the drag, kFalse otherwise.
	*/
	bool16 DoAddDragContent(IDragDropController* controller);

private:
	/** Gets the IDFile associated with this widget.
		@param contentFile [OUT] specifies associated IDFile.
		@return kTrue if a draggable IDFile can be identified, kFalse otherwise.
	 */
	bool16 getContentFile(IDFile& contentFile) const;


	/** Adds kPMSysFileFlavor data to the drag describing the IDFile associated
		with this widget.
		@param controller [IN] in charge of this widget's DND capabilities.
		@return kTrue if valid content has been added to the drag, kFalse otherwise.
	 */
	bool16 doAddSysFileDragContent(IDragDropController* controller);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(PnlTrvDragDropSource, kPnlTrvDragDropSourceImpl)

/* Constructor
*/
PnlTrvDragDropSource::PnlTrvDragDropSource(IPMUnknown* boss)
: CDragDropSource(boss)
{
}


/* Destructor
*/
PnlTrvDragDropSource::~PnlTrvDragDropSource()
{
}


/* WillDrag
*/
bool16 PnlTrvDragDropSource::WillDrag(IEvent* event) const
{
	IDFile contentFile;
	return this->getContentFile(contentFile);
}


/* DoAddDragContent
*/
bool16 PnlTrvDragDropSource::DoAddDragContent(
	IDragDropController* controller)
{
	return this->doAddSysFileDragContent(controller);
}


/* getContentFile
*/
bool16 PnlTrvDragDropSource::getContentFile(
	IDFile& contentFile) const
{
	bool16 result = kFalse;
	do {
		InterfacePtr<ITreeNodeIDData> 
			nodeData(this, UseDefaultIID());
		ASSERT(nodeData);
		if(!nodeData)
		{
			break;
		}
		TreeNodePtr<PnlTrvFileNodeID> nodeID(nodeData->Get());
		ASSERT(nodeID);
		if(!nodeID)
		{
			break;
		}
		PMString fromPath(nodeID->GetPath());
		SDKFileHelper fileHelper(fromPath);
		if(!fileHelper.IsExisting())
		{
			break;
		}
		contentFile = fileHelper.GetIDFile();	
		result = kTrue;
	} while(false);
	return result;
}

/* doAddSysFileDragContent
*/
bool16 PnlTrvDragDropSource::doAddSysFileDragContent(
	IDragDropController* controller)
{
	bool16 result = kFalse;

	do
	{
		// Stop if we can't determine the IDFile we are associated with.
		IDFile contentFile;
		if (this->getContentFile(contentFile) == kFalse)
		{
			break;
		}

		// Point the controller at the handler.
		InterfacePtr<IDataExchangeHandler> 
			dataExchangeHandler(controller->QueryHandler(kPMSysFileFlavor));
		ASSERT(dataExchangeHandler);
		if (!dataExchangeHandler)
		{
			break;
		}
		if (dataExchangeHandler->IsEmpty() == kFalse)
		{
			dataExchangeHandler->Clear();
		}
		controller->SetSourceHandler(dataExchangeHandler);

		// Add the IDFile to be dragged.
		InterfacePtr<ISysFileListData> 
			sysFileListData(dataExchangeHandler, IID_ISYSFILELISTDATA);
		ASSERT(sysFileListData);
		if (!sysFileListData)
		{
			break;
		}
		sysFileListData->Append(contentFile);
			
		// Indicate the flavour in the drag object. 
		InterfacePtr<IPMDataObject>
			pmDataObject(controller->AddDragItem(1));
		ASSERT(pmDataObject);
		PMFlavorFlags flavorFlags = kNormalFlavorFlag;
		pmDataObject->PromiseFlavor(kPMSysFileFlavor, flavorFlags);

		result = kTrue;

	} while(false);

	return result; 
}

// End, PnlTrvDragDropSource.cpp.

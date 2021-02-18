//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicdragdrop/BscDNDCustomDEHandler.cpp $
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
#include "IDataExchangeHandler.h"
#include "ICommand.h"
#include "IDocument.h"
#include "INewPageItemCmdData.h"
#include "IPMDataObject.h"
#include "IPageItemScrapData.h"
#include "IPageItemLayerData.h"

// General includes:
#include "PMPoint.h"
#include "UIDList.h"
#include "CActionComponent.h"
#include "CAlert.h"
#include "CmdUtils.h"
#include "PageItemScrapID.h"
#include "CDataExchangeHandlerFor.h"

// Project includes:
#include "BscDNDID.h"


/** BscDNDCustomDEHandler
	is responsible for keeping track of the data during an exchange operation such as drag'n'drop.

	BscDNDCustomDEHandler implements based on the partial implementation of CDataExchangeHandlerFor.

	@ingroup BasicDragDrop
	
*/
class BscDNDCustomDEHandler : public CDataExchangeHandlerFor
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		BscDNDCustomDEHandler(IPMUnknown* boss) : CDataExchangeHandlerFor(boss) {}
		/**
			Destructor.
		*/
		virtual	~BscDNDCustomDEHandler() {}

		/**
			creates storage for the scrap.
		*/
		virtual void CreateScrapStorage();

		/**
			indicates the type of object this data exchange handler can deal with.
			@return the flavor supported by the handler
		*/
		virtual	PMFlavor GetFlavor() const { return customFlavor; }

		/**
			clears the scrap.
		*/
		virtual void				Clear();
		/**
			reports whether the scrap is empty or not.
			@return kTrue if the scrap is empty, kFalse otherwise.
		*/
		virtual bool16			IsEmpty() const;
			
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(BscDNDCustomDEHandler, kBscDNDCustomDEHandlerImpl)

// creates storage for the scrap.
void 
BscDNDCustomDEHandler::CreateScrapStorage()
{
	// Get the IDocument, which is located on the scrap databases root boss
	IDataBase* db = ::GetDataBase(this);
	InterfacePtr<IDocument> doc(db, db->GetRootUID(), IID_IDOCUMENT);

	// Create a new page item, which will be the root node for the scrap.
	// Page items that get copied into the scrap will be children of this node.
	InterfacePtr<ICommand> createRootPageItem(CmdUtils::CreateCommand(kNewPageItemCmdBoss));
	if(createRootPageItem!=nil)
	{
		InterfacePtr<INewPageItemCmdData> cmdData(createRootPageItem, UseDefaultIID());
		PMPointList ptList;
		ptList.push_back(PMPoint(0, 0));
		ptList.push_back(PMPoint(0, 0));
		cmdData->Set(db, kPageItemScrapRootBoss, ptList);
		CmdUtils::ProcessCommand(createRootPageItem);
		const UIDList *newItem = createRootPageItem->GetItemList();
		InterfacePtr<IPageItemScrapData> scrapData(this, UseDefaultIID());
		scrapData->SetRootNode(newItem->GetRef(0));
	}
}


//	clears the scrap.
void 
BscDNDCustomDEHandler::Clear()
{
	InterfacePtr<IPageItemScrapData> data(this, UseDefaultIID());
	data->Clear();
	InterfacePtr<IPageItemLayerData> layerData(this, IID_IPAGEITEMLAYERDATA);
	layerData->Clear();
}

//	reports whether the scrap is empty or not.
bool16 
BscDNDCustomDEHandler::IsEmpty() const
{
	InterfacePtr<IPageItemScrapData> data(this, UseDefaultIID());
	return data->IsEmpty();
}

// End, BscDNDCustomDEHandler.cpp.

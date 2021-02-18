//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicdragdrop/BscDNDCustomDragSource.cpp $
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
#include "IPageItemScrapData.h"
#include "IPageItemLayerData.h"
#include "IPathUtils.h"
#include "IPMDataObject.h"
#include "IDragDropController.h"
#include "IGraphicAttributeUtils.h"
#include "IGraphicAttributeSuite.h"
#include "ISwatchUtils.h"
#include "ISwatchList.h"
#include "ILayoutUIUtils.h"
#include "IGeometry.h"

// General includes:
#include "CAlert.h"
#include "CDragDropSource.h"
#include "UIDList.h"
#include "CmdUtils.h"
#include "UIDRef.h"
#include "K2Vector.h"
#include "CmdUtils.h"
#include "SplineID.h"
#include "PMFlavorTypes.h"
#include "PMRect.h"
#include "SystemUtils.h"

// Project includes:
#include "BscDNDID.h"



/** 
	a basic dragdrop source implementation. Most of the functionality is implemented in the 
	parent (helper) implementation class.

	@ingroup basicdragdrop
	
*/
class BscDNDCustomDragSource : public CDragDropSource
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		BscDNDCustomDragSource(IPMUnknown* boss);
		/**
			we will only allow the drag if there is an existing document. We faux the creation of a page item,
			this simplifies the database requirements.
			@param e IN the event signifying the start of the drag.
			@return kTrue if we will drag from this location, otherwise kFalse.
		*/
		bool16 			WillDrag(IEvent* e) const;
		/**
			we override this method to add the content we want to drag from this widget.
			@param DNDController IN the controller in charge of this widget's DND capabilities.
			@return kTrue if valid content has been added to the drag
		*/
		bool16			DoAddDragContent(IDragDropController* DNDController);

	private:
		/**
			this method just creates a spline
			@param newPageItem OUT the UIDRef for the created page item.
			@param parent IN the UIDRef for the parent that the new item should be attached to.
			@param points IN the pair of points that define the spline.
			@param strokeWeight IN the initial stroke applied to the path for the new page item.
			@return kSuccess if the page item is created without error, kFailure otherwise.
		*/
		ErrorCode CreatePageItem(UIDRef& newPageItem,UIDRef parent,PMPointList points,PMReal strokeWeight);
		
		/** Cache the page item */
		UIDRef fPageItem;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(BscDNDCustomDragSource, kBscDNDCustomDragSourceImpl)

/* BscDNDCustomDragSource Constructor
*/
BscDNDCustomDragSource::BscDNDCustomDragSource(IPMUnknown* boss)
: CDragDropSource(boss)
{
}

/*
	We indicate we are only interested in dragging if there is a document open. This is making the assumption that we
	want to drag the item onto the layout widget, but also allows us to create the page item within the context of that document.
*/
bool16
BscDNDCustomDragSource::WillDrag(IEvent* e) const
{
	IDocument* theFrontDoc = Utils<ILayoutUIUtils>()->GetFrontDocument();
	if (theFrontDoc == nil)
		return kFalse;
	return kTrue;
}

/*
	We override the DoAddDragContent method to define the content for the drag, 
	in this case a simple spline item is added. Note, this is just a simple 
	implementation for demonstration purposes. 
*/
bool16
BscDNDCustomDragSource::DoAddDragContent(IDragDropController* DNDController)
{
	bool16 result = kFalse;
	// do while(false) loop for error control
	do 
	{
		// Get the dataexchangehandler for the flavor we want to add 
		// The method QueryHandler is on the dataexchangecontroller, which adds extra functionality
		// to the dragdropcontroller. I am assuming we drag from our custom source to custom target
		// via the layout widget, if we attempt to go directly, the handler will be nil.
		InterfacePtr<IDataExchangeHandler> ourHandler(DNDController->QueryHandler(customFlavor));
		// if we cannot get the handler for our flavor, we are dead in the water.
		// The handler gives us the scrap to store our content on...
		if (ourHandler==nil)
		{
			ASSERT_FAIL("Handler nil for our flavor?");
			break;
		}	
		// we need to place our content onto the scrap
		InterfacePtr<IPageItemScrapData> scrapData(ourHandler, UseDefaultIID());
		if (scrapData == nil)
		{
			ASSERT_FAIL("No scrap data for DEHandler?");
			break;
		}
		
		// get the root of the scrap	
		UIDRef scrapRoot = scrapData->GetRootNode();
		
		// new page item
		UIDRef newPageItem;
		// set up a list of points for the page item
		PMPointList points;
		// define the text bounding box using two pmpoints
		PMPoint startPoint(0,0);
		PMPoint endPoint(100,100);
		points.push_back( startPoint );
		points.push_back( endPoint );
		PMReal strokeWeight(2.0);
		if (CreatePageItem(newPageItem,scrapRoot,points,strokeWeight)==kFailure)
		{
			ASSERT_FAIL("Failed to create page item?");
			break;
		}
		
		// Must manually clear the handler before adding any data...
		ourHandler->Clear();
		
		// we call replace to define the DB the item exists in. We add our new item to the scrap
		scrapData->Replace(UIDList(newPageItem));
		// Update the cached variable
		fPageItem = newPageItem;
		InterfacePtr<IPageItemLayerData> layerData(scrapData,IID_IPAGEITEMLAYERDATA);
		// I faux the layer the item is on.
		K2Vector<int32> layerIndexList;
		layerIndexList.push_back(0);

		// Make a list of the layer names.
		K2Vector<PMString> layerNameList;
		layerNameList.reserve(1);
		PMString layerName("Untitled");
		layerNameList.push_back(layerName);
 
		layerData->SetPageItemList(UIDList(newPageItem));
		layerData->SetLayerNameList(layerNameList);
		layerData->SetLayerIndexList(layerIndexList);
		layerData->SetIsGuideLayer(kFalse);

		
		// we point the controller at the pageitem handler 
		DNDController->SetSourceHandler(ourHandler) ;
			
		// we get the data object that represents the drag
		InterfacePtr<IPMDataObject> item(DNDController->AddDragItem(1));

		// no flavor flags	
		PMFlavorFlags flavorFlags = 0;
		
		// we set the type (flavour) in the drag object 
		item->PromiseFlavor(customFlavor, flavorFlags);
		
 		result = kTrue;
	} while (false);
	return result; 
}

/* this method takes in a points list, stroke weight and parent UIDRef and creates a spline with those points, the stroke weight
	and attaches it to the parent.
*/
ErrorCode 
BscDNDCustomDragSource::CreatePageItem(UIDRef& newPageItem,UIDRef parent,PMPointList points,PMReal strokeWeight)
{
	ErrorCode returnValue = kFailure;
	do 
	{
		// wrap the commands in a sequence
		ICommandSequence *sequence = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
		if (sequence == nil)
		{
			ASSERT_FAIL("Cannot create command sequence?");
			break;
		}

		// create the page item
		UIDRef newSplineItem = Utils<IPathUtils>()->CreateLineSpline(parent, points, INewPageItemCmdData::kDefaultGraphicAttributes);
		
		// put the new item into a splinelist
		const UIDList splineItemList(newSplineItem);

		// we apply the stroke to our item
		InterfacePtr<ICommand> strokeSplineCmd (Utils<IGraphicAttributeUtils>()->CreateStrokeWeightCommand(strokeWeight,&splineItemList,kTrue,kTrue));
		if(strokeSplineCmd==nil)
		{
			ASSERT_FAIL("Cannot create the command to stroke the spline?");
			break;
		}
				
		if(CmdUtils::ProcessCommand(strokeSplineCmd)==kFailure)
		{
			ASSERT_FAIL("Failed to stroke the spline?");
			break;
		}

		// we want to apply the stroke, color it black. We need to get the black swatch...
		InterfacePtr<ISwatchList> iSwatchList (Utils<ISwatchUtils>()->QuerySwatchList(splineItemList.GetDataBase()));
		if(iSwatchList==nil)
		{
			ASSERT_FAIL("Cannot get swatch list?");
			break;
		}
		UID blackUID = iSwatchList->GetBlackSwatchUID();
		
		// Now get the command to apply the stroke...
		InterfacePtr<ICommand> applyStrokeCmd(Utils<IGraphicAttributeUtils>()->CreateStrokeRenderingCommand(blackUID,&splineItemList,kTrue,kTrue));
		if(applyStrokeCmd==nil)
		{
			ASSERT_FAIL("Cannot create the command to render the stroke?");
			break;
		}

		if(CmdUtils::ProcessCommand(applyStrokeCmd)!=kSuccess)
		{
			ASSERT_FAIL("Failed to render the stroke?");
			break;
		}
		
		// now we can end the command sequence, we are done.
		CmdUtils::EndCommandSequence(sequence);
		newPageItem = newSplineItem;
		returnValue=kSuccess;
	} while(false);
	return returnValue;
}

// End, BscDNDCustomDragSource.cpp.

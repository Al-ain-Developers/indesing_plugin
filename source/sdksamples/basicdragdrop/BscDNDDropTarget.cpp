//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicdragdrop/BscDNDDropTarget.cpp $
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
#include "IPathGeometry.h"
#include "ITextControlData.h"
#include "IPanelControlData.h"
#include "IPageItemTypeUtils.h"
#include "IGraphicFrameData.h"

// General includes:
#include "CDragDropTarget.h"
#include "CAlert.h"
#include "PMFlavorTypes.h"
#include "DataObjectIterator.h"
#include "UIDList.h"
#include "IPathUtils.h"
#include "PMString.h"
#include "IHierarchy.h"

// Project includes:
#include "BscDNDID.h"

/** the flavour our target will handle */
#define dropTgtFlavor PMFlavor(kPageItemFlavor)

/** BscDNDDropTarget
	Provides the drop behaviour. Our drag and drop target accepts page items and reasons about their shape. 
	We override the DoDragWithin method to replace the custom cursor behaviour (open hand rather than copy).
	This drag and drop target is bound to a panel...
	
	@ingroup basicdragdrop
	
*/
class BscDNDDropTarget : public CDragDropTarget
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		BscDNDDropTarget(IPMUnknown* boss);
		/**
			when we enter the panel, we change the cursor to be an open hand. If we had some dynamic cursor behaviour
			(the cursor changing dependent on where the mouse is within the panel), we would provide this behaviour in
			the DoDragWithin method.
		*/
		void DoDragEnter();
		/**
			this method defines the target response to the drag. It is called when the mouse enters the panel. We
			inidcate we can accept drags with a kPageItem flavor, that we do not want the default cursor and we do
			want the default panel highlight behaviour.

			@param dataIter IN iterator providing access to the data objects within the drag.
			@param fromSource IN the source of the drag.
			@param controller IN the drag drop controller mediating the drag.
			@return a target response (either won't accept or drop will copy).

			@see DragDrop::TargetResponse
		*/
		DragDrop::TargetResponse CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* fromSource, const IDragDropController* controller) const;
		/**
			When the drop is performed, this method is called. We get the data item from the scrap and test its shape.
			We then change the static text widget associated with the panel to reflect the shape of this widget.
			@param controller IN the drag drop controller mediating the drag.
			@param type IN drag and drop command type
			@see DragDrop::eCommandType
		*/
		ErrorCode	ProcessDragDropCommand(IDragDropController* controller, DragDrop::eCommandType type);
		
	private:
		/**
			Determine the type of page item.
			@param pageItemUIDRef IN reference to page item to be typed.
			@param pageItemType OUT a string that describes the type of item e.g. "Group", GraphicFrame".
		*/
		void GetPageItemType(const UIDRef& pageItemUIDRef, PMString& pageItemType) const;
		/**
		Determine the shape of a given path page item.
		@param pageItemUIDRef IN reference to page item looked at.
		@param shape OUT a string that describes the shape e.g. "Line", "Circle", etc.
		@return kTrue if the item is a spline, kFalse otherwise.
		*/
		bool16 IsSplineShape(const UIDRef& itemUIDRef, PMString& shape) const;

		/**
			@return kTrue if the given item is a group, kFalse otherwise.
		*/
		bool16 IsGroup(const UIDRef& pageItemUIDRef) const;

		/**
			@return kTrue if the given item is an empty graphic frame, kFalse otherwise.
		*/
		bool16 IsEmptyGraphicFrame(const UIDRef& pageItemUIDRef) const;
		
		/**
			@return kTrue if the given item is an empty spline, kFalse otherwise.
		*/
		bool16 IsSpline(const UIDRef& pageItemUIDRef) const;


};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(BscDNDDropTarget, kBscDNDDropTargetImpl)

/* BscDNDDropTarget Constructor
*/
BscDNDDropTarget::BscDNDDropTarget(IPMUnknown* boss)
: CDragDropTarget(boss)
{
}

/* DoDragEnter. The drag enters the panel.
*/
void BscDNDDropTarget::DoDragEnter()
{
	InterfacePtr<IDragDropController> ddController(GetExecutionContextSession(), IID_IDRAGDROPCONTROLLER);
	ddController->SetTrackingCursorFeedback(CursorSpec(kCrsrOpenHand));		
}

DragDrop::TargetResponse 
BscDNDDropTarget::CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* fromSource, const IDragDropController*) const
{
	DataExchangeResponse response;
	response = dataIter->FlavorExistsWithPriorityInAllObjects(dropTgtFlavor);
	if(response.CanDo())
		{
 			return DragDrop::TargetResponse( response, DragDrop::kDropWillCopy,
					 DragDrop::kUseDefaultTrackingFeedback,
					 DragDrop::kTargetWillProvideCursorFeedback);

		}
	return DragDrop::kWontAcceptTargetResponse;
}

/*
	the drop has occured, we need to handle it.
*/
ErrorCode	
BscDNDDropTarget::ProcessDragDropCommand(IDragDropController* controller,DragDrop::eCommandType type)
{
	bool16 returnCode = kFailure;
	
	do
	{
		// we should ensure the drag has been internalized, if we are coming from a 
		// custom source, the handler may not be initialised
		if (controller->InternalizeDrag(dropTgtFlavor, dropTgtFlavor) != kSuccess)	
		{
			ASSERT_FAIL("Can't internalize drag?");
			break;
		}

		// get the data exchnage handler for this object...
		InterfacePtr<IDataExchangeHandler> handler(controller->QueryTargetHandler());
		if (handler == nil)
		{
			ASSERT_FAIL("Data exchange handler is nil?");
			break;
		}
		
		// the item that is being dragged is on the scrap
		InterfacePtr<IPageItemScrapData> data(handler,UseDefaultIID());
		if (data == nil)
		{
			ASSERT_FAIL("Page item scrap data is nil?");
			break;
		}
		
		// Find the text widget to update
		InterfacePtr<IPanelControlData> thisWidget(this,UseDefaultIID());
		if (thisWidget == nil)
		{
			ASSERT_FAIL("Panel control data is nil?");
			break;
		}
		IControlView*	textWid = thisWidget->FindWidget(kBscDNDTargetStaticTextWidgetID);
		if (textWid == nil)
		{
			ASSERT_FAIL("Control view for text widget is nil?");
			break;
		}
		InterfacePtr<ITextControlData> theText(textWid,UseDefaultIID());
		if (theText == nil)
		{
			ASSERT_FAIL("No text control data interface for widget?");
			break;
		}

		// we capture the shape as a string
		PMString shape;
		
		// get the list of objects captured by the drag
		UIDList*	theUIDs = data->CreateUIDList();
		// we are only interested in the first object dragged.
		UIDRef primaryObject = theUIDs->GetRef(0);

		this->GetPageItemType(primaryObject,shape);

		// we are not going to localise the possible values.
		shape.SetTranslatable(kFalse);

		theText->SetString(shape);
		delete theUIDs;
		returnCode = kSuccess;
	}while(false);
	return returnCode;
}

/* GetPageItemType
*/
void 
BscDNDDropTarget::GetPageItemType(const UIDRef& pageItemUIDRef, PMString& pageItemType) const
{
	do
	{
		if (Utils<IPageItemTypeUtils>()->IsGraphicFrame(pageItemUIDRef) == kTrue)
		{
			pageItemType = "GraphicFrame";
		}
		else if (this->IsEmptyGraphicFrame(pageItemUIDRef) == kTrue )
		{
			pageItemType = "EmptyGraphicFrame";
		}
		else if (Utils<IPageItemTypeUtils>()->IsTextFrame(pageItemUIDRef) == kTrue)
		{
			pageItemType = "TextFrame";
		}
		else if (this->IsGroup(pageItemUIDRef) == kTrue)
		{
			pageItemType = "Group";
		}
		else if (Utils<IPageItemTypeUtils>()->IsInline(pageItemUIDRef) == kTrue)
		{
			pageItemType = "Inline";
		}
		else if (Utils<IPageItemTypeUtils>()->IsGraphic(pageItemUIDRef) == kTrue)
		{
			pageItemType = "Graphic";
		}
		else if (Utils<IPageItemTypeUtils>()->IsTextOnAPath(pageItemUIDRef) == kTrue)
		{
			pageItemType = "TextOnAPath";
		}
		else if (Utils<IPageItemTypeUtils>()->IsStandOff(pageItemUIDRef) == kTrue)
		{
			pageItemType = "StandOff";
		}
		else if (Utils<IPageItemTypeUtils>()->IsGuide(pageItemUIDRef) == kTrue)
		{
			pageItemType = "Guide";
		}
		else if (this->IsSplineShape(pageItemUIDRef, pageItemType) == kTrue)
		{
			// see if we can determine if it is a spline, and what shape it is...
			// we know it is a spline...
			pageItemType.Append(" spline");
		}
		else
		{
			pageItemType = "Unknown";
		}
	} while (false);
}

/* GetShape
*/
bool16 
BscDNDDropTarget::IsSplineShape(const UIDRef& itemUIDRef, PMString& shape) const
{
	bool16 result = kFalse;
	InterfacePtr<IPathGeometry> pathGeometry(itemUIDRef,UseDefaultIID());
	if (pathGeometry != nil)
	{
		result = kTrue;
		PMPageItemType pathType = Utils<IPathUtils>()->WhichKindOfPageItem(pathGeometry);
		switch (pathType)
		{
		case kIsPoint:
			shape = "Point";
			break;
		case kIsLine:
			shape = "Line";
			break;
		case kIsSquare:
			shape = "Square";
			break;
		case kIsRectangle:
			shape = "Rectangle";
			break;
		case kIsCircle:
			shape = "Circle";
			break;
		case kIsOval:
			shape = "Oval";
			break;
		case kIsPoly:
			shape = "Poly";
			break;
		case kIsPath:
			shape = "Path";
			break;
		case kIsCompoundPath:
			shape = "Compound Path";
			break;
		default:
			shape = "Unknown";
			break;
		}
	}
	return result;
}

/* IsGroup
*/
bool16 
BscDNDDropTarget::IsGroup(const UIDRef& itemUIDRef) const
{
	bool16 result = kFalse;
	do
	{
		// Groups have a hierarchy.
		InterfacePtr<IHierarchy> hierarchy(itemUIDRef, UseDefaultIID());
		if (hierarchy == nil)
			break;

		// Groups don't have an IGraphicFrameData
		InterfacePtr<IGraphicFrameData> graphicFrameData(hierarchy, UseDefaultIID());
		if (graphicFrameData != nil)
			break;

		// Groups have more than one child.
		if (hierarchy->GetChildCount() <= 1)
			break;

		// OK it's a group.
		result = kTrue;
	} while (false);
	return result;
}

/* IsEmptyGraphicFrame
*/
bool16 
BscDNDDropTarget::IsEmptyGraphicFrame(const UIDRef& itemUIDRef) const
{
	bool16 result = kFalse;
	do
	{
		// Graphic frames have an IGraphicFrameData.
		InterfacePtr<IGraphicFrameData> graphicFrameData(itemUIDRef, UseDefaultIID());
		if (graphicFrameData == nil)
			break;
		if (graphicFrameData->IsGraphicFrame() != kTrue)
			break;

		// Empty graphic frames don't have content.
		if (graphicFrameData->HasContent() == kTrue)
			break;

		// OK it's an empty graphic frame.
		result = kTrue;
	} while (false);
	return result;
}


// End, BscDNDDropTarget.cpp.







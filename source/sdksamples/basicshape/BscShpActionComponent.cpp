//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicshape/BscShpActionComponent.cpp $
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
#include "IActiveContext.h"
#include "IDocument.h"
#include "ISpread.h"
#include "ISpreadList.h"
#include "IHierarchy.h"
#include "IGeometry.h"
#include "IGraphicStyleAttrBossList.h"
#include "IPathUtils.h"
#include "IGraphicAttributeUtils.h"
#include "IPMUnknownData.h"
#include "IApplyAttributeCmdData.h"
#include "IGraphicAttrRealNumber.h"
#include "ISwatchList.h"
#include "ISwatchUtils.h"
#include "ILayerUtils.h"
#include "IDocumentLayer.h"
#include "ISpreadLayer.h"
#include "ILayoutControlData.h"
#include "IControlView.h"
#include "IBoolData.h"

// General includes:
#include "CAlert.h"
#include "CActionComponent.h"
#include "ILayoutUIUtils.h"
#include "TransformUtils.h"
#include "GraphicStylesID.h"
#include "ErrorUtils.h"

// Project includes:
#include "BscShpID.h"
#include "BscShpUtils.h"

/** BscShpActionComponent
	implements the actions that are executed when the plug-in's
	menu items are selected.

	BscShpActionComponent implements IActionComponent based on
	the partial implementation CActionComponent.


	@ingroup basicshape
	
*/
class BscShpActionComponent : public CActionComponent
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		BscShpActionComponent(IPMUnknown* boss);

		/**
			The action component should do the requested action.
			This is where the menu item's action is taken.
			When an action is activated, the Action Manager determines
			which plug-in is responsible for it, and calls its DoAction
			with the ID for the menu item chosen.
			@param ac The IActiveContext, passed from Action Manager.
		 	@param actionID identifies which action this action component should perform
			@param mousePoint contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not known or relevant.
			@param widget contains the widget that invoked this action. May be nil. e.g. Useful to use as a basis for Utils<IWidgetUtils>()->QueryRelatedWidget(...) to find widgets in a panel after its popup menu is hit.
		 */
		virtual void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil);

	private:
		/** Encapsulates functionality for the about menu item. */
		void DoAbout();

		/** 
			Add as BscShpPageItem on the 1st content layer of the 1st spread.  Location
			and size of the item are hard-wired in this routine.
			@param ac IN The IActiveContext, passed from Action Manager.
		*/
		void DoPlace_PageItem(IActiveContext* ac);

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(BscShpActionComponent, kBscShpActionComponentImpl)


/* BscShpActionComponent Constructor
*/
BscShpActionComponent::BscShpActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}


/* DoAction
*/
void BscShpActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kBscShpAboutActionID:
		{
			this->DoAbout();
			break;
		}

		case kBscShpPlace_PageItemActionID:
		{
			if ( ac == nil ) 
			{
				ASSERT_FAIL("Nil IActiveContext* - BscShpActionComponent::DoAction");
			}
			else
			{
				this->DoPlace_PageItem(ac);
			}
			break;
		}

		default:
		{
			break;
		}
	}
}

/* DoAbout
*/
void BscShpActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
	   kBscShpAboutBoxStringKey,						// Alert string
	   kOKString, 							// OK button
	   kNullString, 						// No second button
	   kNullString, 						// No third button
	   1,									// Set OK button to default
	   CAlert::eInformationIcon				// Information icon.
	);
}

/* DoPlace_PageItem
*/
void BscShpActionComponent::DoPlace_PageItem(IActiveContext* ac)
{
	ICommandSequence* sequence = nil;
	ErrorCode seqStatus = kSuccess;
	do 
	{
		// check for front document
		IDocument* fntDoc = ac->GetContextDocument();
		if ( fntDoc == nil )
		{
			// ActionDef disables this menu item is no front layout view, so nil IDoc is error.
			ASSERT_FAIL("Nil IDocument* - BscShpActionComponent::DoPlace_PageItem");
			break;
		}

		// Get the active spread.  That's where we'll put the new page item.
		InterfacePtr<ILayoutControlData> layoutData(ac->GetContextView(),UseDefaultIID() );
		InterfacePtr<ISpread> spread(layoutData->GetSpreadRef(), IID_ISPREAD);
		if (spread==nil) 
		{
			ASSERT_FAIL("nil ISpread* or IHierarchy*");
			break;
		}

		// The code below should not be necessary when we implement UpdateActionStates() to let the action only be enabled 
		// if its precondictions are met. 
        InterfacePtr<IDocumentLayer> activeLayer(Utils<ILayerUtils>()->QueryDocumentActiveLayer(fntDoc));
		ErrorCode unlock = kSuccess;
		int16 resultButton = 1;
		if (activeLayer->IsLocked()) 		
		{
            resultButton = CAlert::ModalAlert(PMString(kLockedLayerAlertMessage),
                             kYesString,
                             kNoString,
                             kNullString,
                             1,            // pass in 1, 2, or 3 to make that button the default button or 0 for no default
                             CAlert::eWarningIcon);    // icon to display in CAlert, use eAlertIcon or resource id of other icon
			if (resultButton == 2)
			{
				ASSERT_FAIL("Can not place item because active layer is locked");
				break;
			}
			else
			{
				InterfacePtr<ICommand> unlockLayerCmd ( CmdUtils::CreateCommand(kLockLayerCmdBoss));
				unlockLayerCmd->SetItemList(UIDList(activeLayer));
				InterfacePtr<IBoolData> data(unlockLayerCmd, IID_IBOOLDATA);
				data->Set(kFalse);
				unlock = CmdUtils::ProcessCommand(unlockLayerCmd);
				if (unlock != kSuccess)
				{
					ASSERT_FAIL("Can not unlock active layer");
					break;
				}
			}
		}


        InterfacePtr<ISpreadLayer> spreadLayer(spread->QueryLayer(activeLayer));
		UIDRef layerRef = ::GetUIDRef(spreadLayer);

		// Get visible page of this spread
        InterfacePtr<IGeometry> pageGeo(layerRef.GetDataBase(), layoutData->GetPage(), UseDefaultIID());
		if (pageGeo == nil )
		{
			ASSERT_FAIL("nil IGeometry* for page");
			break;
		}

		// Create the geometry for the new page item.
		// The geometry is first specified in inner (page item) coordinates.
		PMPoint startPoint(0,396);		// Upper Left in Page Coords
		PMPoint endPoint(300,300);		// Size of rectangle
		endPoint+=startPoint;

		// Now transform the description from inner coordinates to pasteboard coordinates.  (Pasteboard
		// coords are the same as the spread.)
		::TransformInnerPointToPasteboard(pageGeo,&endPoint);
		::TransformInnerPointToPasteboard(pageGeo,&startPoint);
		PMRect bbox(startPoint, endPoint);

		// wrap the commands in a sequence
		sequence = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
		if (sequence == nil)
		{
			ASSERT_FAIL("Cannot create command sequence?");
			break;
		}
		seqStatus = kFailure;

		// Create the basic shape page item and add it to the layer
		BscShpUtils bscShpUtils;
		UIDRef newSplineItem = bscShpUtils.CreateBasicShape(layerRef, bbox);
		if (newSplineItem.ExistsInDB() != kTrue)
		{
			seqStatus = kFailure;
			ASSERT_FAIL("Could not create kBscShpPageItemBoss");
			break;
		}

		// The following code is necessary to force an ink usage to be registered in the page item's IInkResources
		// interface.  If that interface doesn't recognize ink usage, the print plug-in will think the page is
		// blank.  So even though the IShape interface for this page item doesn't draw from the graphic attributes,
		// without ink resource usage it won't be called to draw during printing.

		// Apply a 1.0 pt stroke to the new spline item.
		UIDList newSplineItemList(newSplineItem);
		InterfacePtr<ICommand> strokeSplineCmd (Utils<IGraphicAttributeUtils>()->CreateStrokeWeightCommand(PMReal(1.0),&newSplineItemList,kTrue,kTrue));
		if(strokeSplineCmd==nil)
		{
			seqStatus = kFailure;
			ASSERT_FAIL("cannot create the command to apply stroke");
			break;
		}
		seqStatus = CmdUtils::ProcessCommand(strokeSplineCmd);
		if (seqStatus ==kFailure)
		{
			ASSERT_FAIL("error when processing command to apply stroke");
			break;
		}

		// Color the stroke using the black swatch
		InterfacePtr<ISwatchList> iSwatchList (Utils<ISwatchUtils>()->QueryActiveSwatchList());
		if(iSwatchList==nil)
		{
			seqStatus = kFailure;
			ASSERT_FAIL("nil ISwatchList*");
			break;
		}
		UID blackUID = iSwatchList->GetBlackSwatchUID();
		
		// Create the command to apply the stroke
		InterfacePtr<ICommand> applyStrokeCmd(Utils<IGraphicAttributeUtils>()->CreateStrokeRenderingCommand(blackUID,&newSplineItemList,kTrue,kTrue));
		if(applyStrokeCmd==nil)
		{
			seqStatus = kFailure;
			ASSERT_FAIL("Cannot create the command to apply stroke color");
			break;
		}
		seqStatus = CmdUtils::ProcessCommand(applyStrokeCmd);
		if (seqStatus != kSuccess)
		{
			ASSERT_FAIL("error when processing command to color the stroke");
			break;
		}
		
		// now we can end the command sequence, we are done.
		CmdUtils::EndCommandSequence(sequence);
	} 
	while (false);

	if (seqStatus == kFailure)
	{
		// Abort the command sequence
		ErrorUtils::PMSetGlobalErrorCode(seqStatus);
		CmdUtils::EndCommandSequence(sequence);
	}
}

//  Generated by Dolly build 17: template "IfPanelMenu".
// End, BscShpActionComponent.cpp.







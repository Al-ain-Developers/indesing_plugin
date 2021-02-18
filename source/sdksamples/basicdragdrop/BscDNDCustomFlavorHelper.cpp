//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicdragdrop/BscDNDCustomFlavorHelper.cpp $
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

//Interface includes:
#include "CDragDropTargetFlavorHelper.h"
#include "IControlView.h"
#include "ILayoutUIUtils.h"
#include "ILayoutControlData.h"
#include "ICommand.h"
#include "IDataExchangeHandler.h"
#include "IGeometry.h"
#include "IPageItemLayerData.h"
#include "IPageItemScrapUtils.h"
#include "IPasteboardUtils.h"
#include "IDocument.h"
#include "IPageItemScrapData.h"
#include "ISpread.h"
#include "IGeometryFacade.h"
#include "ITransformCmdData.h"
#include "ILayoutCmdData.h"
#include "ICopyCmdData.h"

// General includes:
#include "PersistUtils.h"
#include "ErrorUtils.h"
#include "Utils.h"
#include "DataObjectIterator.h"
#include "CmdUtils.h"
#include "LayerID.h"

// Project includes:
#include "BscDNDID.h"

/** Extends the DND target capabilities of the layout widget to
	accept our custom flavor object.

	@ingroup basicdragdrop
	
*/
class BscDNDCustomFlavorHelper : public CDragDropTargetFlavorHelper
{
public:
	/**
		Constructor.
		@param boss IN the boss class the interface is aggregated onto.
	*/
	BscDNDCustomFlavorHelper(IPMUnknown* boss);
	/**
		Destructor.
	*/
	virtual	~BscDNDCustomFlavorHelper();

	/**
		Determines whether we can handle the flavors in the drag.
		@param target IN the target the mouse is currently over.
		@param dataIter IN iterator providing access to the data objects within the drag.
		@param fromSource IN the source of the drag.
		@param controller IN the drag drop controller mediating the drag.
		@return a target response (either won't accept or drop will copy).

		@see DragDrop::TargetResponse
	*/
	virtual DragDrop::TargetResponse	
						CouldAcceptTypes(const IDragDropTarget* target, DataObjectIterator* dataIter, const IDragDropSource* fromSource, const IDragDropController* controller) const;

	/**
		performs the actual drag. Because we know that our custom flavor is masquerading and is 
		really a page item we must take a copy of the page item, then move this copy to the drop zone.
		We know we have been dropped on a widget (because we are called as part of that widget responding to
		a drop of the custom flavor).
		@param target IN the target for this drop.
		@param controller IN the drag drop controller that is mediating the drag.
		@param action IN what the drop means (i.e. copy, move etc)
		@return kSuccess if the drop is executed without error, kFailure, otherwise.
	*/
	virtual ErrorCode		ProcessDragDropCommand(IDragDropTarget*, IDragDropController*, DragDrop::eCommandType);

	DECLARE_HELPER_METHODS()
};


//--------------------------------------------------------------------------------------
// Class LayoutDDTargetFileFlavorHelper
//--------------------------------------------------------------------------------------
CREATE_PMINTERFACE(BscDNDCustomFlavorHelper, kBscDNDCustomFlavorHelperImpl)
DEFINE_HELPER_METHODS(BscDNDCustomFlavorHelper)

BscDNDCustomFlavorHelper::BscDNDCustomFlavorHelper(IPMUnknown* boss) :
	CDragDropTargetFlavorHelper(boss), HELPER_METHODS_INIT(boss)
{
}

BscDNDCustomFlavorHelper::~BscDNDCustomFlavorHelper()
{
}

/* Determine if we can handle the drop type */
DragDrop::TargetResponse 
BscDNDCustomFlavorHelper::CouldAcceptTypes(const IDragDropTarget* target, DataObjectIterator* dataIter, const IDragDropSource* fromSource, const IDragDropController* controller) const
{
	// Check the available external flavors to see if we can handle any of them
	if (dataIter != nil)
	{
		// Test for swatches in the drag
		DataExchangeResponse response;
		
		response = dataIter->FlavorExistsWithPriorityInAllObjects(customFlavor);
		if (response.CanDo())
			return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy);
	}
	return DragDrop::kWontAcceptTargetResponse;
}

/* process the drop, this method called if CouldAcceptTypes returns valid response */
ErrorCode	
BscDNDCustomFlavorHelper::ProcessDragDropCommand
	(
	IDragDropTarget* 			target, 
	IDragDropController* 		controller,
	DragDrop::eCommandType		action
	)
{	
	ErrorCode stat = kFailure;
	ICommandSequence* sequence = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
	if (sequence == nil)
	{
		ASSERT_FAIL("Cannot create command sequence?");
		return stat;
	}
	sequence->SetName(PMString("ProcessDragDropCommand", PMString::kUnknownEncoding));

	do
	{
		if (action != DragDrop::kDropCommand) {
			break;
		}

		// Find the target view for the drop and the mouse position.
		InterfacePtr<IControlView> layoutView(target, UseDefaultIID());
		ASSERT(layoutView);
		if (!layoutView) {
			break;
		}
		InterfacePtr<ILayoutControlData> layoutData(target, UseDefaultIID());
		ASSERT(layoutData);
		if (!layoutData) {
			break;
		}
		GSysPoint where = controller->GetDragMouseLocation();
		PMPoint currentPoint = Utils<ILayoutUIUtils>()->GlobalToPasteboard(layoutView, where);

		// Determine the target spread to drop the items into.
		InterfacePtr<ISpread> targetSpread(Utils<IPasteboardUtils>()->QueryNearestSpread(layoutView, currentPoint));
		ASSERT(targetSpread);
		if (!targetSpread) {
			break;
		}
		UIDRef targetSpreadUIDRef = ::GetUIDRef(targetSpread);

		// Change spread if necessary.
		if (targetSpreadUIDRef != layoutData->GetSpreadRef()) {
			InterfacePtr<ICommand> setSpreadCmd(CmdUtils::CreateCommand(kSetSpreadCmdBoss));
			ASSERT(setSpreadCmd);
			if (!setSpreadCmd) {
				break;
			}
			InterfacePtr<ILayoutCmdData> setSpreadLayoutCmdData(setSpreadCmd, UseDefaultIID());
			ASSERT(setSpreadLayoutCmdData);
			if (!setSpreadLayoutCmdData) {
				break;
			}
			setSpreadLayoutCmdData->Set(::GetUIDRef(layoutData->GetDocument()), layoutData);
			setSpreadCmd->SetItemList(UIDList(targetSpreadUIDRef));
			stat = CmdUtils::ProcessCommand(setSpreadCmd);
			ASSERT_MSG(stat == kSuccess, "Failed to change spread");
		}

		// Get a list of the page items in the drag.
		stat = controller->InternalizeDrag(kNoExternalFlavor, customFlavor);
		ASSERT_MSG(stat == kSuccess, "Cannot internalize the dragged item?\n");
		if (stat != kSuccess) {
			break;
		}
		InterfacePtr<IDataExchangeHandler> handler(controller->QueryTargetHandler());
		ASSERT(handler);
		if (!handler) {
			stat = kFailure;
			break;
		}
		InterfacePtr<IPageItemScrapData> pageItemData(handler, UseDefaultIID());
		ASSERT(pageItemData);
		if (!pageItemData) {
			stat = kFailure;
			break;
		}
		InterfacePtr<IPageItemLayerData> layerData(handler, IID_IPAGEITEMLAYERDATA);
		ASSERT(layerData);
		if (!layerData) {
			stat = kFailure;
			break;
		}
		UIDList* draggedItemList = pageItemData->CreateUIDList();		

		// Duplicate the drag content in the target spread.
		// Parent the duplicated page item in the active spread layer.
		UIDRef parent(targetSpreadUIDRef.GetDataBase(), layoutData->GetActiveLayerUID());
		// See IPageItemLayerData if you want to maintain layer information across the drop.
		InterfacePtr<ICommand>	duplicateCmd( CmdUtils::CreateCommand(kDuplicateCmdBoss));	
		ASSERT(duplicateCmd);
		if (!duplicateCmd) {
			delete draggedItemList;
			stat = kFailure;
			break;
		}

		InterfacePtr<ICopyCmdData> cmdData(duplicateCmd, IID_ICOPYCMDDATA);
		// Put items on designated parent layer.
		cmdData->Set(duplicateCmd, draggedItemList, parent);
		cmdData->SetOffset( PMPoint(0,0));

		stat = CmdUtils::ProcessCommand(duplicateCmd);
		const UIDList* copiedItemList = duplicateCmd->GetItemList();
		ASSERT_MSG(stat == kSuccess && copiedItemList != nil, "Failed to duplicate dropped item");
		if (stat != kSuccess) {
			break;
		}

		// Position the dropped items on the spread at the mouse position.
		// Calculate the bounds of the items so we can center them on the cursor.
		// You might want to extend the code below to constrain the dropped items
		// position to intersect the bounds of the spread.
		PMRect itemsBoundingBox = Utils<Facade::IGeometryFacade>()->GetItemsBounds(*copiedItemList, Transform::PasteboardCoordinates(), Geometry::OuterStrokeBounds());
		PMPoint itemsBoundsCenter = itemsBoundingBox.GetCenter();
		InterfacePtr<ICommand> moveRelativeCmd(CmdUtils::CreateCommand(kTransformPageItemsCmdBoss));
		ASSERT(moveRelativeCmd);
		if (!moveRelativeCmd) {
			stat = kFailure;
			break;
		}
		InterfacePtr<ITransformCmdData> moveRelativeCmdData(moveRelativeCmd, UseDefaultIID());
		ASSERT(moveRelativeCmdData);
		if (!moveRelativeCmdData) {
			stat = kFailure;
			break;
		}
		PMPoint delta = currentPoint - itemsBoundsCenter;
		moveRelativeCmdData->SetTransformData( Transform::PasteboardCoordinates(), Transform::CurrentOrigin(), Transform::TranslateBy(delta.X(), delta.Y()));
		moveRelativeCmd->SetItemList(UIDList(*copiedItemList));
		stat = CmdUtils::ProcessCommand(moveRelativeCmd);
		ASSERT_MSG(stat == kSuccess, "Failed to position dropped items");
		if (stat != kSuccess) {
			break;
		}

	} while(false);

	if (stat == kSuccess) 
	{
		// Everything completed so end the command sequence
		CmdUtils::EndCommandSequence(sequence);
		
	} else
	{
		// Abort the sequence and roll back the changes.
		ErrorUtils::PMSetGlobalErrorCode(stat);
		CmdUtils::EndCommandSequence(sequence);
	}

	return stat;
}

// End, BscDNDCustomFlavorHelper.cpp.


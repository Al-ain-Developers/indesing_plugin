//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalinkui/CusDtLnkUIDDTargetFlavorHelper.cpp $
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


// TODO filter out unwanted includes

// Interface includes:
#include "ICommand.h"
#include "IControlView.h"
#include "ICusDtLnkFacade.h"
#include "IDataExchangeHandler.h"
#include "IDocument.h"
#include "IGeometry.h"
#include "IImportExportFacade.h"
#include "ILayoutCmdData.h"
#include "ILayoutControlData.h"
#include "ILayoutControlViewHelper.h"
#include "ILayoutUIUtils.h"
#include "IMultiColumnTextFrame.h"
#include "IOwnedItemIBeamData.h"
#include "IPageItemLayerData.h"
#include "IPageItemScrapData.h"
#include "IPageItemScrapUtils.h"
#include "IPasteboardUtils.h"
#include "IPlaceBehavior.h"
#include "IPlaceGun.h"
#include "ISpread.h"
#include "IStringData.h"
#include "ITextFrameColumn.h"
#include "IUIDData.h"
#include "IWorkspace.h"

// General includes:
#include "CDragDropTargetFlavorHelper.h"
#include "CmdUtils.h"
#include "DataObjectIterator.h"
#include "ErrorUtils.h"
#include "LayerID.h"
#include "PersistUtils.h"
#include "SDKFileHelper.h"
#include "Utils.h"


// Project includes:
#include "CusDtLnkUIID.h"

/** Implementation of IDragDropTargetFlavorHelper that extends the DND target capabilities of the layout widget to
	accept our custom flavor object.

	@ingroup basicdragdrop
	
*/
class CusDtLnkUIDDTargetFlavorHelper : public CDragDropTargetFlavorHelper
{
public:
	/**
		Constructor.
		@param boss IN the boss class the interface is aggregated onto.
	*/
	CusDtLnkUIDDTargetFlavorHelper(IPMUnknown* boss);
	/**
		Destructor.
	*/
	virtual	~CusDtLnkUIDDTargetFlavorHelper();

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
		@param target IN the target for this drop.
		@param controller IN the drag drop controller that is mediating the drag.
		@param action IN what the drop means (i.e. copy, move etc)
		@return kSuccess if the drop is executed without error, kFailure, otherwise.
	*/
	virtual ErrorCode		ProcessDragDropCommand(IDragDropTarget*, IDragDropController*, DragDrop::eCommandType);

	DECLARE_HELPER_METHODS()
};


CREATE_PMINTERFACE(CusDtLnkUIDDTargetFlavorHelper, kCusDtLnkUIDDTargetFlavorHelperImpl)
DEFINE_HELPER_METHODS(CusDtLnkUIDDTargetFlavorHelper)

CusDtLnkUIDDTargetFlavorHelper::CusDtLnkUIDDTargetFlavorHelper(IPMUnknown* boss) :
	CDragDropTargetFlavorHelper(boss), HELPER_METHODS_INIT(boss)
{
}

CusDtLnkUIDDTargetFlavorHelper::~CusDtLnkUIDDTargetFlavorHelper()
{
}

/* Determine if we can handle the drop type */
DragDrop::TargetResponse 
CusDtLnkUIDDTargetFlavorHelper::CouldAcceptTypes(const IDragDropTarget* target, DataObjectIterator* dataIter, const IDragDropSource* fromSource, const IDragDropController* controller) const
{
	// Check the available external flavors to see if we can handle any of them
	if (dataIter != nil)
	{
		// Test for swatches in the drag
		DataExchangeResponse response;
		
		response = dataIter->FlavorExistsWithPriorityInAllObjects(kCusDtLnkUIDragDropCustomFlavor);
		if (response.CanDo()) {
			return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy);
		}
	}
	return DragDrop::kWontAcceptTargetResponse;
}

/* process the drop, this method called if CouldAcceptTypes returns valid response */
ErrorCode	
CusDtLnkUIDDTargetFlavorHelper::ProcessDragDropCommand
	(
	IDragDropTarget* 			target, 
	IDragDropController* 		controller,
	DragDrop::eCommandType		action
	)
{	
	ErrorCode stat = kFailure;
	CmdUtils::SequencePtr sequence;

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


		// Find the spread of the target
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
			ASSERT(stat == kSuccess);
		}


		stat = controller->InternalizeDrag(kNoExternalFlavor, kCusDtLnkUIDragDropCustomFlavor);
		ASSERT(stat == kSuccess);
		if (stat != kSuccess) {
			break;
		}
		// Get what is being dragged
		InterfacePtr<IDataExchangeHandler> handler(controller->QueryTargetHandler());
		ASSERT(handler);
		if (!handler) {
			stat = kFailure;
			break;
		}
		// It happens to be a unique key for an asset
		InterfacePtr<IStringData> 
			uniqueKeyStrungData(handler, IID_ICUSDTLNKUIUNIQUEKEYSTRINGDATA);
		ASSERT(uniqueKeyStrungData);
		if (!uniqueKeyStrungData) {
			break;
		}
		PMString uk = uniqueKeyStrungData->GetString();
		TRACEFLOW(kCusDtLnkUIPluginName, 
			"CusDtLnkUIDDTargetFlavorHelper::ProcessDragDropCommand\n\t\tDragged UK=%s\n",
				uk.GetPlatformString().c_str());

		URI	uri(uk.GetPlatformString().c_str());
		Utils<ICusDtLnkFacade> facade;
		ASSERT(facade);
		if(!facade) {
			break;
		}
		
		IDataBase* database = ::GetDataBase(targetSpread);
		UIDRef docUIDRef(database, database->GetRootUID());
		UIDRef loadedImage = 
				Utils<ICusDtLnkFacade>()->ImportImageAndLoadPlaceGun(docUIDRef, uri);
		// Code based on combination of LayoutDDTargetFileHelper and
		// DropDesktopFileCommand
		UIDRef parent(targetSpreadUIDRef.GetDataBase(), layoutData->GetActiveLayerUID());
	
		PMPointList points;
		points.push_back(currentPoint);
		points.push_back(currentPoint);

		// TODO figure out how to place a bit more correctly, e.g. replace
		// doesn't work quite right here
		InterfacePtr<IPlaceGun> placeGun(docUIDRef, UseDefaultIID());
		ASSERT(placeGun);
		if(!placeGun) {
			break;
		}
		InterfacePtr<IPlaceBehavior> sourceBehavior(docUIDRef.GetDataBase(), 
				placeGun->GetFirstPlaceGunItemUID(), 
					UseDefaultIID());
		ASSERT(sourceBehavior);
		if(!sourceBehavior) {
			break;
		}
		ICursorMgr::eCursorModifierState cursorModState = 
			(ICursorMgr::eCursorModifierState) ICursorMgr::kNoModifiers;

		InterfacePtr<ILayoutControlViewHelper> layoutControlViewHelper(layoutView, UseDefaultIID());// IID_ILAYOUTCONTROLVIEWHELPER);
		ASSERT(layoutControlViewHelper);
		if(!layoutControlViewHelper){
			break;
		}
			
		// As of Rocket, kSolidTOPMPHitTestHandlerBoss might return an object
		// which does NOT have IPlaceBehavior interface on it if the hit point
		// maps to a Table cell. This changes the behavior vs Basil in that
		// before you would get the MultiColumnTextFrame containing the Table
		// 
		InterfacePtr<IPMUnknown> targetUnknown(layoutControlViewHelper->QueryHitTestPageItemNew(currentPoint, kSolidTOPMPHitTestHandlerBoss, IID_IUNKNOWN));

		InterfacePtr<IPlaceBehavior> targetBehavior(targetUnknown, UseDefaultIID());

		if ((targetBehavior) && (targetUnknown))
		{
			// If the returned object has an IOwnedItemIBeamData interface you
			// can query for a IPlaceBehavior from it using the same
			// 'currentPoint' and 'layoutControlViewHelper'.
			//
			// The returned IPlaceBehavior object, if found, can be an
			// kTextFocusBoss and the Text insertion point could be inside a
			// Table Cell.
			//
			InterfacePtr<IOwnedItemIBeamData> oiibd(targetUnknown, UseDefaultIID());
			if (oiibd)
			{
				//
				// ...but we maintain the original behavior of this function by
				// simply finding the MCF containing the insertion point.
				//
				InterfacePtr<ITextFrameColumn> tfc(oiibd->QueryContainingFrame());
				InterfacePtr<IMultiColumnTextFrame> mcf(tfc ? tfc->QueryMultiColumnTextFrame() : nil);
				targetBehavior.reset((IPlaceBehavior*)(mcf ? mcf->QueryInterface(IPlaceBehavior::kDefaultIID) : nil));
			}
		}
		
		UIDList placedItem = sourceBehavior->ProcessPlace(targetBehavior, 
				parent, points, cursorModState, cursorModState, targetSpread); 

		if (placedItem.size() > 0)
		{
			ASSERT( placedItem.size() == 1 ) ;
			stat = Utils<Facade::IImportExportFacade>()->ClearPlaceGun( placeGun, Facade::IImportExportFacade::kFirstItem );
			ASSERT(stat == kSuccess);
		}
	
	} while(false);

	// This'll rollback if stat != kSuccess
	if (stat != kSuccess)
		ErrorUtils::PMSetGlobalErrorCode(stat);

	return stat;
}

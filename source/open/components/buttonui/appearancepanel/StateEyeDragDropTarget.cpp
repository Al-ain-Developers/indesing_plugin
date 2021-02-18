//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/StateEyeDragDropTarget.cpp $
//  
//  Owner: Tim Wright
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
//  Implementation of a Drag and Drop target for appearance panel eye
//  
//  Based on LayerEyeDragDropTarget.cpp in Layer Panel Project
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "IDragDropController.h"
#include "IControlView.h"
#include "IWidgetParent.h"
#include "IBoolData.h"
#include "IViewListBoxControlData.h"
#include "IPanelControlData.h"

#include "CDragDropTarget.h"
#include "PMFlavorTypes.h"
#include "DataObjectIterator.h"

#include "IStateData.h"
#include "IAppearanceSuite.h"
#include "FormFieldUIID.h"
#include "FormFieldUIDefs.h"
#include "PMFlavorTypes.h"
#include "FormFieldTypes.h"
#include "IFormFieldUtils.h"
#include "FormFieldUIUtils.h"

class StateEyeDragDropTarget : public CDragDropTarget
{
	public:
									StateEyeDragDropTarget(IPMUnknown *boss);
		virtual						~StateEyeDragDropTarget();
		
		virtual DragDrop::TargetResponse		CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;
			// Can the target accept the data being dragged?
			//	(Drag source is provided to determine if data should be moved, copied or linked.)

		virtual void				DoDragEnter();
		virtual void				DoDragWithin(const PMPoint& localPt);
		virtual void				DoDragLeave();
			// Tracking the drag as it enters, drags, and leaves this target

		virtual SysWireframe				DoMakeDropHiliteRegion() const { return nil; }
			// Default drop outline not wanted for eye
		
		virtual ErrorCode		ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);
			// Create the commands needed to complete a drop 
			// 	(targets will only receive kDragMove or kDrop)
			
	private:
		virtual IControlView*		GetControlView(Form::AppearanceState inState);
		
		DECLARE_HELPER_METHODS()
};

CREATE_PMINTERFACE(StateEyeDragDropTarget, kStateEyeDragDropTargetImpl)
DEFINE_HELPER_METHODS(StateEyeDragDropTarget)

StateEyeDragDropTarget::StateEyeDragDropTarget(IPMUnknown *boss)  :
	CDragDropTarget(boss),
	HELPER_METHODS_INIT(boss)
{
}


StateEyeDragDropTarget::~StateEyeDragDropTarget()
{
}

//--------------------------------------------------------------------------------------
// WillAcceptDrop
//--------------------------------------------------------------------------------------
DragDrop::TargetResponse StateEyeDragDropTarget::CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* fromSource, const IDragDropController*) const
{
	// Check the available external flavors to see if we can handle any of them
	if (dataIter)
	{
		DataExchangeResponse response = dataIter->FlavorExistsWithPriorityInAllObjects(kPMStateEyeFlavor);
		if (!response.CanDo())
			return DragDrop::kWontAcceptTargetResponse;
		else
			return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy);	// Always copy in the drag and drop sense
	}
	return DragDrop::kWontAcceptTargetResponse;
}

//--------------------------------------------------------------------------------------
// DoDragEnter
//--------------------------------------------------------------------------------------
void StateEyeDragDropTarget::DoDragEnter()
{
	// Normally for drag and drop a command would be issued in ProcessDragDropCommand.
	// For the eyeball though, we send the command as soon as the mouse enters the control.
	InterfacePtr<IDragDropController> ddController(GetExecutionContextSession(), IID_IDRAGDROPCONTROLLER);
	if (ddController)
		this->ProcessDragDropCommand(ddController, DragDrop::kDrop);
}

//--------------------------------------------------------------------------------------
// DoDragWithin
//--------------------------------------------------------------------------------------
void StateEyeDragDropTarget::DoDragWithin(const PMPoint& localPt)
{
}

//--------------------------------------------------------------------------------------
// DoDragLeave
//--------------------------------------------------------------------------------------
void StateEyeDragDropTarget::DoDragLeave()
{
}

//--------------------------------------------------------------------------------------
// ProcessDragDropCommand
//--------------------------------------------------------------------------------------
ErrorCode	StateEyeDragDropTarget::ProcessDragDropCommand(
		IDragDropController* controller,
		DragDrop::eCommandType type)
{
	ErrorCode errorCode = kFailure;

	if (controller->InternalizeDrag(kPMStateEyeFlavor, kPMStateEyeFlavor) == kSuccess)
	{
		InterfacePtr<IDataExchangeHandler> handler(controller->QueryTargetHandler());
		
		// Grab the uid of the layer where the user moused down (startingDocLayerUID),
		// Also grab the starting layer states (startingState).
		InterfacePtr<IStateData> handlerStateData(handler, IID_ISTATEDATA);
		InterfacePtr<IBoolData> handlerBoolData(handler, IID_IBOOLDATA);
		if (handlerStateData && handlerBoolData)
		{
			Form::AppearanceState startingState = handlerStateData->GetState();
			bool16 startingShown = handlerBoolData->GetBool();
			
			// Get the uid and state of the current target
			InterfacePtr<IWidgetParent>	widgetParent(this, IID_IWIDGETPARENT);
			InterfacePtr<IStateData>	listElementStateData(widgetParent->GetParent(), IID_ISTATEDATA);
			Form::AppearanceState	endingState = listElementStateData->GetState();
			
			int32 startingPos = Utils<IFormFieldUtils>()->StateToIndex(startingState);
			int32 endingPos = Utils<IFormFieldUtils>()->StateToIndex(endingState);
			int32 increment = (startingPos < endingPos) ? +1 : -1;
			int32 length = std::abs(startingPos - endingPos) + 1;
			int32 currentPos = startingPos;
			
			// If we get this far, we have succeeded as far as our caller is concerned
			errorCode = kSuccess;

			InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());

			if (iAppearanceSuite)
			{
				
				while (length)
				{
				
					Form::Appearance appearance;
					if (iAppearanceSuite->GetAppearance(  Utils<IFormFieldUtils>()->IndexToState(currentPos), &appearance )
						&& appearance.fEnabled == startingShown)
					{
					
						appearance.fEnabled = !appearance.fEnabled;
						Form::AppearanceState state = Utils<IFormFieldUtils>()->IndexToState(currentPos);
						iAppearanceSuite->SetAppearance(  state, state, appearance );
						
						// Draw the new state. Normally observer would watch for kShowLayerCmdBoss, but
						// we want it to happen immediately so user sees feedback while mouse is still down.
						IControlView* eyeControlView = this->GetControlView( Utils<IFormFieldUtils>()->IndexToState(currentPos) );
						if (eyeControlView)
						{
							eyeControlView->SetRsrcID(startingShown ? kStateDisabledIcon : kStateEnabledIcon);
							eyeControlView->ForceRedraw(nil, kTrue);
						}
						
					}
					currentPos += increment;
					length--;
				}
			}
			
		}
	}
	
	return errorCode;
}

// Find the control view for a layer with the indicated id
IControlView* StateEyeDragDropTarget::GetControlView(Form::AppearanceState inState)
{
	IControlView* view = nil;

	InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
	InterfacePtr<IViewListBoxControlData> listData((IViewListBoxControlData*) parentHolder->QueryParentFor(IID_ILISTCONTROLDATA));

	if (listData)
	{
		int32 numLayers = listData->Length();
		for (int32 i = 0; i < numLayers; i++)
		{
			InterfacePtr<IStateData> listElementStateData((*listData)[i], IID_ISTATEDATA);
			if (listElementStateData->GetState() == inState)
			{
				InterfacePtr<IControlView> listElementView((*listData)[i], IID_ICONTROLVIEW);
				InterfacePtr<IPanelControlData> listItemPanelData(listElementView, IID_IPANELCONTROLDATA);
				IControlView* theView = listItemPanelData->FindWidget(kStateListElementEyeballWidgetID);
				return theView;
			}
		}
	}

	return view;
}
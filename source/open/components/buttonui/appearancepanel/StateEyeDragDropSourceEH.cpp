//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/StateEyeDragDropSourceEH.cpp $
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
//  Based on LayerEyeDragDropSourceEH.cpp in Layer Panel Project
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "DragDropID.h"
#include "widgetid.h"

#include "DVHostedWidgetEH.h"
#include "IEvent.h"
#include "IDragDropSource.h"
#include "IDragDropController.h"
#include "ISession.h"
#include "IBoolData.h"
#include "IWidgetParent.h"
#include "IListControlDataOf.h"
#include "ITriStateControlData.h"
#include "IDocumentLayer.h"
#include "ILayerList.h"
#include "IDocument.h"

#include "EventUtilities.h"
#include "ILayoutUIUtils.h"
#include "CmdUtils.h"

#include "FormFieldUIID.h"

class StateEyeDragDropSourceEH : public DVHostedWidgetEH
{			
	public:
		typedef DVHostedWidgetEH inherited;

						StateEyeDragDropSourceEH(IPMUnknown *boss);
		virtual 		~StateEyeDragDropSourceEH();
			
		virtual bool16 	LButtonDn(IEvent* e); 
		
	private:
		DECLARE_HELPER_METHODS()
};

//========================================================================
// Class StateEyeDragDropSourceEH
//========================================================================
CREATE_PMINTERFACE(StateEyeDragDropSourceEH, kStateEyeDragDropSourceEHImpl)
DEFINE_HELPER_METHODS(StateEyeDragDropSourceEH)

StateEyeDragDropSourceEH::StateEyeDragDropSourceEH(IPMUnknown *boss) :
	inherited(boss),
	HELPER_METHODS_INIT(boss)
{
}

StateEyeDragDropSourceEH::~StateEyeDragDropSourceEH()
{
}
	

//--------------------------------------------------------------------------------------
// LButtonDn
//--------------------------------------------------------------------------------------
bool16 StateEyeDragDropSourceEH::LButtonDn(IEvent* e)
{
	bool16 optionKeyDown = e->OptionAltKeyDown();
	bool16 cmdKeyDown = e->CmdKeyDown();

	InterfacePtr<IDragDropSource> dragSource(this, IID_IDRAGDROPSOURCE);
	if (dragSource && dragSource->WillDrag(e))
	{
		// Check to see if user is trying to start a drag
		bool16 isPatientUser;
		if (::IsUserStartingDrag(e, isPatientUser))
		{
			InterfacePtr<IDragDropController> ddController(GetExecutionContextSession(), IID_IDRAGDROPCONTROLLER);
			if (ddController)
			{
				ddController->StartDrag(dragSource, e);	
				e->SetSystemHandledState(IEvent::kDontCall);
				return kTrue; // Make up for the fact that StartDrag will swallow the mouse up
			}
		}
		else if (!(optionKeyDown && cmdKeyDown))	// Allow shortcut for list focus (Option + Command + click) to pass through.
		{
			InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
			InterfacePtr< IListControlDataOf<IControlView*> > listData((IListControlDataOf<IControlView*>*) parentHolder->QueryParentFor(IID_ILISTCONTROLDATA));
			if (listData)
			{
				// Option + click is shortcut for Show All/Hide Others
				int32 numLayers = listData->Length();
				// Just Show/Hide a single layer
				InterfacePtr<ITriStateControlData> triControlData(this, IID_ITRISTATECONTROLDATA);
				if(!triControlData->IsSelected())
					triControlData->Select();
				else
					triControlData->Deselect();
				return kTrue;
			}
		}
	}

	return inherited::LButtonDn(e);
}

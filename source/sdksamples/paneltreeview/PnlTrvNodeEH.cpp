//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvNodeEH.cpp $
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

// Interfaces
#include "ITreeNodeIDData.h"
#include "ILayoutUIUtils.h"
#include "IDocument.h"

// General includes:
#include "CEventHandler.h"
#include "CAlert.h"

// Project includes:
#include "PnlTrvID.h"
#include "PnlTrvFileNodeID.h"
#include "PnlTrvUtils.h"

/** 
	Implements IEventHandler; allows this plug-in's code 
	to catch the double-click events without needing 
	access to the implementation headers.

	
	@ingroup paneltreeview
*/

class PnlTrvNodeEH : public CEventHandler
{
public:

	/** Constructor.
		@param boss interface ptr on the boss object to which the interface implemented here belongs.
	*/	
	PnlTrvNodeEH(IPMUnknown* boss);
	
	/** Destructor
	*/	
	virtual ~PnlTrvNodeEH(){}

	/**  Window has been activated. Traditional response is to
		activate the controls in the window.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 Activate(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->Activate(e);  return retval; }
		
	/** Window has been deactivated. Traditional response is to
		deactivate the controls in the window.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 Deactivate(IEvent* e) 
	{ bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->Deactivate(e);  return retval; }
	
	/** Application has been suspended. Control is passed to
		another application. 
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 Suspend(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->Suspend(e);  return retval; }
	
	/** Application has been resumed. Control is passed back to the
		application from another application.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 Resume(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->Resume(e);  return retval; }
		
	/** Mouse has moved outside the sensitive region.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 MouseMove(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->MouseMove(e);  return retval; } 
		 
	/** User is holding down the mouse button and dragging the mouse.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 MouseDrag(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->MouseDrag(e);  return retval; }
		 
	/** Left mouse button (or only mouse button) has been pressed.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/ 
	virtual bool16 LButtonDn(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->LButtonDn(e);  return retval; }
		 
	/** Right mouse button (or second button) has been pressed.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 RButtonDn(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->RButtonDn(e);  return retval; }
		 
	/** Middle mouse button of a 3 button mouse has been pressed.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 MButtonDn(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->MButtonDn(e);  return retval; }
		
	/** Left mouse button released.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 LButtonUp(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->LButtonUp(e);  return retval; } 
		 
	/** Right mouse button released.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 RButtonUp(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->RButtonUp(e);  return retval; } 
		 
	/** Middle mouse button released.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 MButtonUp(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->MButtonUp(e);  return retval; } 
		 
	/** Double click with any button; this is the only event that we're interested in here-
		on this event we load the placegun with an asset if it can be imported.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 ButtonDblClk(IEvent* e);
	/** Triple click with any button.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 ButtonTrplClk(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->ButtonTrplClk(e);  return retval; }
		 
	/** Quadruple click with any button.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 ButtonQuadClk(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->ButtonQuadClk(e);  return retval; }
		 
	/** Quintuple click with any button.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 ButtonQuintClk(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->ButtonQuintClk(e);  return retval; }

	/** mouse scroll wheel
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 MouseWheel(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->MouseWheel(e);  return retval; }
		 
	/** Event for a particular control. Used only on Windows.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 ControlCmd(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->ControlCmd(e);  return retval; } 
		
		
	// Keyboard Related Events
	
	/** Keyboard key down for every key.  Normally you want to override KeyCmd, rather than KeyDown.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 KeyDown(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->KeyDown(e);  return retval; }
		 
	/** Keyboard key down that generates a character.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 KeyCmd(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->KeyCmd(e);  return retval; }
		
	/** Keyboard key released.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual bool16 KeyUp(IEvent* e) { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->KeyUp(e);  return retval; }
		 
	
	// Keyboard Focus Related Functions
	
	/** Key focus is now passed to the window.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual void PreGetKeyFocus() { InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  delegate->PreGetKeyFocus(); }
		
	/** Window has lost key focus.
		@param e [IN] event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	*/
	virtual void PreGiveUpKeyFocus() { InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER); delegate->PreGiveUpKeyFocus(); }
		
	/** Typically called before GiveUpKeyFocus() is called. Return kFalse
		to hold onto the keyboard focus.
		@return kFalse to hold onto the keyboard focus
	*/
	virtual bool16 WillingToGiveUpKeyFocus() { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->WillingToGiveUpKeyFocus();  return retval; }
		 
	/** The keyboard is temporarily being taken away. Remember enough state
		to resume where you left off. 
		@return kTrue if you really suspended
		yourself. If you simply gave up the keyboard, return kFalse.
	*/
	virtual bool16 SuspendKeyFocus() { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->SuspendKeyFocus();  return retval; }
		 
	/** The keyboard has been handed back. 
		@return kTrue if you resumed yourself. Otherwise, return kFalse.
	*/
	virtual bool16 ResumeKeyFocus() { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->ResumeKeyFocus();  return retval; }
		 
	/** Determine if this eventhandler can be focus of keyboard event 
		@return kTrue if this eventhandler supports being the focus
		of keyboard event
	*/
	virtual bool16 CanHaveKeyFocus() const { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->CanHaveKeyFocus();  return retval; }
		 
	/** Return kTrue if this event handler wants to get keyboard focus
		while tabbing through widgets. Note: For almost all event handlers
		CanHaveKeyFocus and WantsTabKeyFocus will return the same value.
		If WantsTabKeyFocus returns kTrue then CanHaveKeyFocus should also return kTrue
		for the event handler to actually get keyboard focus. If WantsTabKeyFocus returns
		kFalse then the event handler is skipped.
		@return kTrue if event handler wants to get focus during tabbing, kFalse otherwise
	*/
	virtual bool16 WantsTabKeyFocus() const { bool16 retval; InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  retval =  delegate->WantsTabKeyFocus();  return retval; }
		 		 		
	/** Temporary.
	*/
	virtual void SetView(IControlView* view)
	{  
		InterfacePtr<IEventHandler> 
			delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER); 
		delegate->SetView(view);  
	}
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE( PnlTrvNodeEH, kPnlTrvNodeEHImpl)

	
PnlTrvNodeEH::PnlTrvNodeEH(IPMUnknown* boss) :
	CEventHandler(boss)
{

}

bool16 PnlTrvNodeEH::ButtonDblClk(IEvent* e) 
{
	do {
		InterfacePtr<ITreeNodeIDData> nodeData(this, UseDefaultIID());
		ASSERT(nodeData);
		if(!nodeData) {
			break;
		}
		TreeNodePtr<PnlTrvFileNodeID> nodeID(nodeData->Get());
		ASSERT(nodeID);
		if(!nodeID) {
			break;
		}
		PMString pstr(nodeID->GetPath());
		IDocument* doc = Utils<ILayoutUIUtils>()->GetFrontDocument();
		if(doc) {
			UIDRef docUIDRef = ::GetUIDRef(doc);
			UIDRef loadedImage = PnlTrvUtils::ImportImageAndLoadPlaceGun(docUIDRef,pstr);
		}
	} while(kFalse);
	
	bool16 retval; 
	InterfacePtr<IEventHandler> delegate(this,IID_IPNLTRVSHADOWEVENTHANDLER);  		
	retval= delegate->ButtonDblClk(e); 
	return retval;
} 

//	end, File:	PnlTrvNodeEH.cpp

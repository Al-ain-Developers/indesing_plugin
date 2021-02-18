//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/tablebasics/TblBscDialogObserver.cpp $
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
#include "IControlView.h"
#include "IPanelControlData.h"
#include "ISubject.h"

// General includes:
#include "CDialogObserver.h"
#include "CAlert.h"

// Project includes:
#include "TblBscID.h"

/**	Monitors changes in the state of the dialog controls that must be handled
	dynamically. If there is no fill specified(kTblBscPreFilledCheckboxWidgetID) 
	then this observer disables the radio buttons.

	
	@ingroup tablebasics
*/
class TblBscDialogObserver : public CDialogObserver
{
	public:
		/** Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		 */
		TblBscDialogObserver(IPMUnknown* boss) : CDialogObserver(boss) {}

		/** Destructor. 
		 */
		virtual ~TblBscDialogObserver() {}

		/** Called by the application to allow the observer to attach to the subjects 
			to be observed.
		*/
		virtual void AutoAttach();

		/** Called by the application to allow the observer to detach from 
			the subjects being observed.
		 */
		virtual void AutoDetach();

		/** Called by the host when the observed object changes.
			@param theChange specifies the class ID of the change to the subject. Frequently this is a command ID.
			@param theSubject points to the ISubject interface for the subject that has changed.
			@param protocol specifies the ID of the changed interface on the subject boss.
			@param changedBy points to additional data about the change. Often this pointer indicates the class ID of the command that has caused the change.
		*/
		virtual void Update
		(
			const ClassID& theChange, 
			ISubject* theSubject, 
			const PMIID& protocol, 
			void* changedBy
		);

	private:
		void handleCheckStateChange(const ClassID& theChange);
		void setControlEnabled(const WidgetID&  widgetID, bool16 enabled=kTrue);

};


/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(TblBscDialogObserver, kTblBscDialogObserverImpl)

/*
*/
void TblBscDialogObserver::AutoAttach()
{
	// Call the base class AutoAttach() function so that default behavior
	// will still occur (OK and Cancel buttons, etc.).
	CDialogObserver::AutoAttach();

	do
	{
		// Get the IPanelControlData interface for the dialog:
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (panelControlData == nil)
		{
			ASSERT_FAIL("TblBscDialogObserver::AutoAttach() panelControlData invalid");
			break;
		}
		
		// Now attach to TableBasics's info button widget.
		AttachToWidget(kTblBscPreFilledCheckboxWidgetID, IID_ITRISTATECONTROLDATA, panelControlData);
	} while (false);
}

/*
*/
void TblBscDialogObserver::AutoDetach()
{
	// Call base class AutoDetach() so that default behavior will occur (OK and Cancel buttons, etc.).
	CDialogObserver::AutoDetach();

	do
	{
		// Get the IPanelControlData interface for the dialog:
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (panelControlData == nil)
		{
			ASSERT_FAIL("TblBscDialogObserver::AutoDetach() panelControlData invalid");
			break;
		}
		
		// Now we detach from TableBasics's info button widget.
		DetachFromWidget(kTblBscPreFilledCheckboxWidgetID, IID_ITRISTATECONTROLDATA, panelControlData);
	} while (false);
}

/*
*/
void TblBscDialogObserver::Update(const ClassID& theChange, 
									ISubject* theSubject, 
									const PMIID &protocol, 
									void* changedBy)
{
	// Call the base class Update function so that default behavior will still occur (OK and Cancel buttons, etc.).
	CDialogObserver::Update(theChange, theSubject, protocol, changedBy);

	do
	{
		InterfacePtr<IControlView> controlView(theSubject, UseDefaultIID());
		if (controlView == nil)
		{
			ASSERT_FAIL("TblBscDialogObserver::Update() controlView invalid");
			break;
		}

		// Get the button ID from the view.
		WidgetID theSelectedWidget = controlView->GetWidgetID();

		if (theSelectedWidget == kTblBscPreFilledCheckboxWidgetID) 
		{
			handleCheckStateChange(theChange);
		}

	} while (false);
}

/*
*/
void TblBscDialogObserver::handleCheckStateChange(const ClassID& theChange)
{
	bool16 state=kFalse;
	if(theChange == kTrueStateMessage) 
	{
		state = kTrue;
	} 
	this->setControlEnabled(kTblBscAddressFillRadioWidgetID, state);
	this->setControlEnabled(kTblBscPlaceholderFillRadioWidgetID, state);

}


/*
*/
void TblBscDialogObserver::setControlEnabled(const WidgetID&  widgetID, bool16 enabled)
{
	bool16 retval = kFalse;

	do {
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if(panelControlData == nil) 
		{
			break;
		}

		IControlView* controlView = panelControlData->FindWidget(widgetID);
		ASSERT(controlView);
		if (controlView == nil)
		{
			break;
		}

		if(enabled) 
		{
			controlView->Enable(); 
		} else 
		{
			controlView->Disable();
		}


	} while(false);

}

// End, TblBscDialogObserver.cpp.




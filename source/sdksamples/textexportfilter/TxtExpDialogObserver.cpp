//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textexportfilter/TxtExpDialogObserver.cpp $
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
#include "SystemUtils.h"

// Project includes:
#include "TxtExpID.h"

/** TxtExpDialogObserver
	Allows dynamic processing of dialog widget changes, in this case
	the dialog's info button. 
  
	Implements IObserver based on the partial implementation CDialogObserver. 
	@ingroup textexportfilter
	
*/
class TxtExpDialogObserver : public CDialogObserver
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		TxtExpDialogObserver(IPMUnknown* boss) : CDialogObserver(boss) {}

		/** Destructor. */
		virtual ~TxtExpDialogObserver(void) {}

		/** 
			Called by the application to allow the observer to attach to the subjects 
			to be observed, in this case the dialog's info button widget. If you want 
			to observe other widgets on the dialog you could add them here. 
		*/
		virtual void AutoAttach(void);

		/** Called by the application to allow the observer to detach from the subjects being observed. */
		virtual void AutoDetach(void);

		/**
			Called by the host when the observed object changes, in this case when
			the dialog's info button is clicked.
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
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(TxtExpDialogObserver, kTxtExpDialogObserverImpl)

/* AutoAttach
*/
void TxtExpDialogObserver::AutoAttach()
{
	// Call the base class AutoAttach() function so that default behavior
	// will still occur (OK and Cancel buttons, etc.).
	CDialogObserver::AutoAttach();

	do
	{
		// Get the IPanelControlData interface for the dialog:
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (!panelControlData)
		{
			ASSERT_FAIL("TxtExpDialogObserver::AutoAttach() panelControlData invalid");
			break;
		}
		
		// Now attach to TextImportFilter's info button widget.
		AttachToWidget(kTxtExpIconSuiteWidgetID, IID_ITRISTATECONTROLDATA, panelControlData);

		// Attach to other widgets you want to handle dynamically here.

	} while (false);
}

/* AutoDetach
*/
void TxtExpDialogObserver::AutoDetach(void)
{
	// Call base class AutoDetach() so that default behavior will occur (OK and Cancel buttons, etc.).
	CDialogObserver::AutoDetach();

	do
	{
		// Get the IPanelControlData interface for the dialog:
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (!panelControlData)
		{
			ASSERT_FAIL("TxtExpDialogObserver::AutoDetach() panelControlData invalid");
			break;
		}
		
		// Now we detach from TextImportFilter's info button widget.
		DetachFromWidget(kTxtExpIconSuiteWidgetID, IID_ITRISTATECONTROLDATA, panelControlData);

		// Detach from other widgets you handle dynamically here.
		
	} while (false);
}

/* Update
*/
void TxtExpDialogObserver::Update
(
	const ClassID& theChange, 
	ISubject* theSubject, 
	const PMIID& protocol, 
	void* changedBy
)
{
	// Call the base class Update function so that default behavior will still occur (OK and Cancel buttons, etc.).
	CDialogObserver::Update(theChange, theSubject, protocol, changedBy);

	do
	{
		InterfacePtr<IControlView> controlView(theSubject, UseDefaultIID());
		if (!controlView)
		{
			ASSERT_FAIL("TxtExpDialogObserver::Update() controlView invalid");
			break;
		}

		// Get the button ID from the view.
		WidgetID theSelectedWidget = controlView->GetWidgetID();

		if (theSelectedWidget == kTxtExpIconSuiteWidgetID && theChange == kTrueStateMessage)
		{
			// Bring up the About box.
			CAlert::ModalAlert
			(
			   kTxtExpAboutBoxStringKey,						// Alert string
			   kOKString, 							// OK button
			   kNullString, 						// No second button
			   kNullString, 						// No third button
			   1,									// Set OK button to default
			   CAlert::eInformationIcon				// Information icon.
			);
		}

	} while (false);
}
//  Generated by Dolly build 17: template "Dialog".
// End, TxtExpDialogObserver.cpp.





//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicdialog/BscDlgDialogObserver.cpp $
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
#include "BscDlgID.h"

/**	Implements IObserver based on the partial implementation CDialogObserver; 
	allows dynamic processing of dialog widget changes, in this case
	the dialog's info button. 
  
	
	 @ingroup basicdialog
	
*/
class BscDlgDialogObserver : public CDialogObserver
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		BscDlgDialogObserver(IPMUnknown* boss) : CDialogObserver(boss) {}

		/** Destructor. */
		virtual ~BscDlgDialogObserver() {}

		/** 
			Called by the application to allow the observer to attach to the subjects 
			to be observed, in this case the dialog's info button widget. If you want 
			to observe other widgets on the dialog you could add them here. 
		*/
		virtual void AutoAttach();

		/** Called by the application to allow the observer to detach from the subjects being observed. */
		virtual void AutoDetach();

		/**
			Called by the host when the observed object changes, in this case when
			the dialog's info button is clicked.
			@param theChange specifies the class ID of the change to the subject. Frequently this is a command ID.
			@param theSubject points to the ISubject interface for the subject that has changed.
			@param protocol specifies the ID of the changed interface on the subject boss.
			@param changedBy points to additional data about the change. 
				Often this pointer indicates the class ID of the command that has caused the change.
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
CREATE_PMINTERFACE(BscDlgDialogObserver, kBscDlgDialogObserverImpl)

/* AutoAttach
*/
void BscDlgDialogObserver::AutoAttach()
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
			ASSERT_FAIL("BscDlgDialogObserver::AutoAttach() panelControlData invalid");
			break;
		}
		
		// Now attach to BasicDialog's info button widget.
		AttachToWidget(kBscDlgIconSuiteWidgetID, IID_ITRISTATECONTROLDATA, panelControlData);

		// Attach to other widgets you want to handle dynamically here.

	} while (false);
}

/* AutoDetach
*/
void BscDlgDialogObserver::AutoDetach()
{
	// Call base class AutoDetach() so that default behavior will occur (OK and Cancel buttons, etc.).
	CDialogObserver::AutoDetach();

	do
	{
		// Get the IPanelControlData interface for the dialog:
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (panelControlData == nil)
		{
			ASSERT_FAIL("BscDlgDialogObserver::AutoDetach() panelControlData invalid");
			break;
		}
		
		// Now we detach from BasicDialog's info button widget.
		DetachFromWidget(kBscDlgIconSuiteWidgetID, IID_ITRISTATECONTROLDATA, panelControlData);

		// Detach from other widgets you handle dynamically here.
		
	} while (false);
}

/* Update
*/
void BscDlgDialogObserver::Update
(
	const ClassID& theChange, 
	ISubject* theSubject, 
	const PMIID &protocol, 
	void* changedBy
)
{
	// Call the base class Update function so that default behavior will still occur (OK and Cancel buttons, etc.).
	CDialogObserver::Update(theChange, theSubject, protocol, changedBy);

	do
	{
		InterfacePtr<IControlView> controlView(theSubject, UseDefaultIID());
		if (controlView == nil)
		{
			ASSERT_FAIL("BscDlgDialogObserver::Update() controlView invalid");
			break;
		}

		// Get the button ID from the view.
		WidgetID theSelectedWidget = controlView->GetWidgetID();

		if (theSelectedWidget == kBscDlgIconSuiteWidgetID && theChange == kTrueStateMessage)
		{
			// About box
			CAlert::ModalAlert
			(
				kBscDlgAboutBoxStringKey,		// Alert string
				kOKString, 						// OK button
				kNullString, 					// No second button
				kNullString, 					// No third button
				1,								// Set OK button to default
				CAlert::eInformationIcon		// Information icon.
			);
		}

	} while (false);
}

// End, BscDlgDialogObserver.cpp.





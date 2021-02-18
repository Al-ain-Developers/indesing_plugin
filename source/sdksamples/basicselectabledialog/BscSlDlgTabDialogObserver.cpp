//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicselectabledialog/BscSlDlgTabDialogObserver.cpp $
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
#include "IListBoxController.h"
#include "IPanelControlData.h"
#include "ISelectableDialogSwitcher.h"
#include "ISubject.h"

// Implementation includes:
#include "CAlert.h"
#include "CSelectableDialogObserver.h"

// Project includes:
#include "BscSlDlgID.h"

/** This implementation subclasses CSelectableDialogObserver, not CObserver, 
	to help provide the dialog switching mechanism.  Note that 
	each of the methods in this class first call the method in the parent class, 
	CSelectableDialogObserver. (e.g. BscSlDlgTabDialogObserver::Update calls 
	CSelectableDialogObserver::Update)
	
	In addition, this implementation allows dynamic processing of the dialog's 
	info button. 
  	
	For the tabs to switch correctly, it is necessary to listen to kSelectedTabChangedMessage
	and react accordingly.  It is illustrated in the Update() method, and it is actually from
	production code of TabBasicSelectableDialogObserver class, since the header is private, we provide
	the implementation here for developer who might need it.  The previous version of this sample
	used an icon observer to dynamically process widget's state change, but it is impractical
	for plug-in that has many widgets to have one observer for each widget, thus we provide this
	dialog observer.

	@ingroup basicselectabledialog
	
*/
class BscSlDlgTabDialogObserver : public CSelectableDialogObserver
{
public: 
	/**	Constructor.
		@param boss interface ptr from boss object on which interface is aggregated.
	*/
	BscSlDlgTabDialogObserver(IPMUnknown* boss);

	/** Destructor. 
	 */
	virtual ~BscSlDlgTabDialogObserver() {}

	/**	Called by the host when the observed object changes. In this case: 
		the tab dialog's info button is clicked.  
		
		Since this class inherits CSelectableDialogObserver, it only handles the default list box widget, which
		is not used in the tab style. for tab style, we need to handle the kSelectedTabChangedMessage

		@param theChange specifies the class ID of the change to the subject. Frequently this is a command ID.
		@param theSubject points to the ISubject interface for the subject that has changed.
		@param protocol specifies the ID of the changed interface on the subject boss.
		@param changedBy points to additional data about the change. Often this pointer indicates the class ID of the command that has caused the change.
	*/
	virtual void Update(const ClassID& theChange, 
						ISubject* theSubject, 
						const PMIID& protocol, 
						void* changedBy);

	/** Called by the application to allow the observer to attach to the 
		subjects to be observed. In this case the tab dialog's info button widget.
	*/
	virtual void AutoAttach();

	/** Called by the application to allow the observer to detach from the 
		subjects being observed. 
	*/
	virtual void AutoDetach();
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(BscSlDlgTabDialogObserver, kBscSlDlgTabDialogObserverImpl)


/* Constructor
*/
BscSlDlgTabDialogObserver::BscSlDlgTabDialogObserver(IPMUnknown* boss)
	: CSelectableDialogObserver(boss)
{
}

/* Update
*/
void BscSlDlgTabDialogObserver::Update(const ClassID& theChange, 
									   ISubject* theSubject, 
									   const PMIID& protocol, 
									   void* changedBy)
{
	// Call base class Update() function so that default behavior
	// will still occur (selectable dialog listbox, OK and Cancel buttons, etc.).
	CSelectableDialogObserver::Update(theChange, theSubject, protocol, changedBy);

	InterfacePtr<IControlView> view(theSubject, UseDefaultIID());
	if (view != nil)
	{
		InterfacePtr<ISelectableDialogSwitcher> panelSwitcher(this, IID_ISELECTABLEDIALOGSWITCHER);

		if (view->GetWidgetID() == panelSwitcher->GetSelectionListWidgetID() && theChange == kSelectedTabChangedMessage)
		{
			// Handle tab switching
			InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
			InterfacePtr<IListBoxController> listCntl(iPanelControlData->FindWidget(panelSwitcher->GetSelectionListWidgetID()), IID_ILISTBOXCONTROLLER);
			panelSwitcher->SwitchDialogPanel(listCntl->GetSelected());
		}
		else if (view->GetWidgetID() == kBscSlDlgIconSuiteWidgetID && theChange == kTrueStateMessage)
		{
			// Bring up the About box
			CAlert::ModalAlert(kBscSlDlgAboutBoxStringKey,			// Alert string
							   kOKString,							// OK button
							   kNullString,							// No second button
							   kNullString,							// No third button
							   1,									// Set OK button to default
							   CAlert::eInformationIcon				// Information icon.
							   );
		}
	}
}

/* AutoAttach
*/
void BscSlDlgTabDialogObserver::AutoAttach()
{
	// Call base class AutoAttach() function so that default behavior
	// will still occur (selectable dialog listbox, OK and Cancel buttons, etc.).
	CSelectableDialogObserver::AutoAttach();

	do
	{
		// Get the IPanelControlData interface for the dialog:
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (panelControlData == nil)
		{
			ASSERT_FAIL("BscSlDlgDialogObserver::AutoAttach() panelControlData invalid");
			break;
		}

		// Now attach to BasicSelectableDialog's info button widget.
		AttachToWidget(kBscSlDlgIconSuiteWidgetID, IID_ITRISTATECONTROLDATA, panelControlData);

		// Attach to other widgets you want to handle dynamically here.

	} while (false);
}

/*	AutoDetach
*/
void BscSlDlgTabDialogObserver::AutoDetach()
{
	// Call base class AutoDetach() so that default behavior will occur 
	// (selectable dialog listbox, OK and Cancel buttons, etc.).
	CSelectableDialogObserver::AutoDetach();

	do
	{
		// Get the IPanelControlData interface for the dialog:
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (panelControlData == nil)
		{
			ASSERT_FAIL("BscSlDlgDialogObserver::AutoDetach() panelControlData invalid");
			break;
		}

		// Now detach from BasicSelectableDialog's info button widget.
		DetachFromWidget(kBscSlDlgIconSuiteWidgetID, IID_ITRISTATECONTROLDATA, panelControlData);

		// Detach from other widgets you handle dynamically here.

	} while (false);
}

// End, BscSlDlgTabDialogObserver.cpp

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicselectabledialog/BscSlDlgDialogObserver.cpp $
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
#include "IPanelControlData.h"
#include "ISubject.h"
#include "ITreeViewController.h"
#include "ITreeViewHierarchyAdapter.h"

// General includes:
#include "CAlert.h"
#include "CSelectableDialogObserver.h"
#include "K2Vector.tpp" // For NodeIDList to compile
#include "ListIndexNodeID.h"

// Project includes:
#include "BscSlDlgID.h"

/** This implementation subclasses CSelectableDialogObserver, not CObserver, 
	to help provide the dialog switching mechanism.  Note that 
	each of the methods in this class first call the method in the parent class, 
	CSelectableDialogObserver. (e.g. BscSlDlgDialogObserver::Update calls 
	CSelectableDialogObserver::Update)
	
	In addition, this implementation allows dynamic processing of the dialog's 
	info button. 
  
	@ingroup basicselectabledialog
	
*/
class BscSlDlgDialogObserver : public CSelectableDialogObserver
{
public:
	/**	Constructor.
		@param boss IN interface ptr from boss object on which interface is aggregated.
	*/
	BscSlDlgDialogObserver(IPMUnknown* boss) : CSelectableDialogObserver(boss) {}

	/** Destructor. 
	 */
	virtual ~BscSlDlgDialogObserver() {}

	/** Called by the application to allow the observer to attach to the 
		subjects to be observed. In this case: the selectable dialog listbox
		and the dialog's info button widget.
		If you want to observe other widgets on the dialog, add them here. 
	*/
	virtual void AutoAttach();

	/** Called by the application to allow the observer to detach from the 
		subjects being observed. 
	*/
	virtual void AutoDetach();

	/** Called by the host when the observed object changes. In this case: 
		when either the dialog's info button or an item on the selectable 
		dialog listbox is clicked.
		@param theChange specifies the class ID of the change to the subject. Frequently this is a command ID.
		@param theSubject points to the ISubject interface for the subject that has changed.
		@param protocol specifies the ID of the changed interface on the subject boss.
		@param changedBy points to additional data about the change. Often this pointer indicates the class ID of the command that has caused the change.
	*/
	virtual void Update(const ClassID& theChange, 
						ISubject* theSubject, 
						const PMIID& protocol, 
						void* changedBy);
protected:
	/** Override this method so that the parent CSelectableDialogObserver will be able to
	    switch dialog panel.
	*/
	virtual int32 GetSelectedPanelIndex();
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(BscSlDlgDialogObserver, kBscSlDlgDialogObserverImpl)

/* AutoAttach
*/
void BscSlDlgDialogObserver::AutoAttach()
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

		// Attach to the tree view widget
	    AttachToWidget(kSelectDialogSelectionWidgetID, IID_ITREEVIEWCONTROLLER, panelControlData);

		// Attach to other widgets you want to handle dynamically here.

	} while (false);
}

/* AutoDetach
*/
void BscSlDlgDialogObserver::AutoDetach()
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

		// Detach to the tree view widget
	    DetachFromWidget(kSelectDialogSelectionWidgetID, IID_ITREEVIEWCONTROLLER, panelControlData);

		// Detach from other widgets you handle dynamically here.

	} while (false);
}

/* Update
*/
void BscSlDlgDialogObserver::Update(const ClassID& theChange, 
									ISubject* theSubject, 
									const PMIID& protocol, 
									void* changedBy)
{
	// Call base class Update function so that default behavior will still 
	// occur (selectable dialog listbox, OK and Cancel buttons, etc.).
	CSelectableDialogObserver::Update(theChange, theSubject, protocol, changedBy);

	do
	{
		InterfacePtr<IControlView> controlView(theSubject, UseDefaultIID());
		if (controlView == nil)
		{
			ASSERT_FAIL("BscSlDlgDialogObserver::Update() controlView invalid");
			break;
		}

		// Get the button ID from the view.
		WidgetID theSelectedWidget = controlView->GetWidgetID();

		if (theSelectedWidget == kBscSlDlgIconSuiteWidgetID && theChange == kTrueStateMessage)
		{
			// Bring up the About box.
			CAlert::ModalAlert(kBscSlDlgAboutBoxStringKey,			// Alert string
							   kOKString,							// OK button
							   kNullString,							// No second button
							   kNullString,							// No third button
							   1,									// Set OK button to default
							   CAlert::eInformationIcon				// Information icon.
							   );
		}

	} while (false);
}

int32 BscSlDlgDialogObserver::GetSelectedPanelIndex()
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	IControlView* treeView = iPanelControlData->FindWidget( kSelectDialogSelectionWidgetID );
	InterfacePtr<ITreeViewController> iTreeViewController(treeView, UseDefaultIID());	

	NodeIDList selectedItems;
	iTreeViewController->GetSelectedItems(selectedItems);
	if (selectedItems.size() > 0)
	{
		InterfacePtr<ITreeViewHierarchyAdapter> iTreeViewAdapter(treeView, UseDefaultIID());	

		NodeID_rv rootNode = iTreeViewAdapter->GetRootNode();
		int32 childIndex = iTreeViewAdapter->GetChildIndex(rootNode, selectedItems[0]);
		return childIndex;
	}

	return 0;
}
// End, BscSlDlgDialogObserver.cpp.

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicselectabledialog/BscSlDlgDialogCreator.cpp $
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
#include "IApplication.h"
#include "IDialogMgr.h"
#include "ISession.h"

// Implementation includes:
#include "CDialogCreator.h"
#include "CoreResTypes.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"

// Project includes:
#include "BscSlDlgID.h"


/** Provides management and control over the dialog. 
  
	@ingroup basicselectabledialog
	
*/
class BscSlDlgDialogCreator : public CDialogCreator
{
public:
	/**	Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	BscSlDlgDialogCreator(IPMUnknown *boss) : CDialogCreator(boss) {}

	/** Destructor.
	*/
	virtual ~BscSlDlgDialogCreator() {}

	/** Creates a dialog from the resource that is cached by 
		the dialog manager until invoked.
	*/
	virtual IDialog* CreateDialog();

	/** Returns the resource ID of the resource containing an ordered list of panel IDs.
		@param classIDs specifies resource ID containing an ordered list of panel IDs.
	*/
	virtual void GetOrderedPanelIDs(K2Vector<ClassID>& classIDs);

	/** Returns an ordered list of class IDs of selectable dialogs
		that are to be installed in this dialog.
	*/
	virtual RsrcID GetOrderedPanelsRsrcID() const;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(BscSlDlgDialogCreator, kBscSlDlgDialogCreatorImpl)


/* CreateDialog
*/
IDialog* BscSlDlgDialogCreator::CreateDialog()
{
	IDialog* dialog = nil;

	// Use a do-while(false) so we can break on bad pointers:
	do
	{
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());

		InterfacePtr<IDialogMgr> dialogMgr(app, UseDefaultIID());
		if (dialogMgr == nil)
		{
			ASSERT_FAIL("BscSlDlgDialogCreator::CreateDialog: dialogMgr invalid");
			break;
		}

		// We need to load the plug-in's resource:
		PMLocaleId nLocale = LocaleSetting::GetLocale();
		RsrcSpec dialogSpec(nLocale,					// Defined in PMLocaleIDs.h. 
							kBscSlDlgPluginID,			// Defined in BscSlDlgID.h. 
							kViewRsrcType,				// This is the kViewRsrcType.
							kBscSlDlgDialogResourceID,	// Defined in BscSlDlgID.h.
							kTrue						// Initially visible.
							);

		// CreateNewDialog takes the dialogSpec created above,
		// and the type of dialog being created.	
		// The dialog manager caches the dialog for us.
		dialog = dialogMgr->CreateNewDialog(dialogSpec, IDialog::kMovableModal);

		// Make the initial focus be in the selection list.
		dialog->SetDialogFocusingAlgorithm(IDialog::kNoAutoFocus);

	} while (false); // Only do once.

	return dialog;
}

/* GetOrderedPanelIDs
*/
void BscSlDlgDialogCreator::GetOrderedPanelIDs(K2Vector<ClassID>& classIDs)
{
	CDialogCreator::GetOrderedPanelIDs(kBscSlDlgPluginID, classIDs);
}

/* GetOrderedPanelsRsrcID
*/
RsrcID BscSlDlgDialogCreator::GetOrderedPanelsRsrcID() const
{
	return kBscSlDlgPanelOrderingResourceID;
}

// End, BscSlDlgDialogCreator.cpp


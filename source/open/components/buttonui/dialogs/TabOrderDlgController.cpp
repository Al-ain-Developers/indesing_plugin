//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/dialogs/TabOrderDlgController.cpp $
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
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IActiveContext.h"
#include "ICommand.h"
#include "IDocument.h"
#include "IGeometry.h"
#include "ISetTabOrderCmdData.h"
#include "ISpreadFieldOrder.h"
#include "ISpreadList.h"
#include "IWidgetUtils.h"

// ----- Includes -----

#include "FieldOrderDlgController.h"

// ----- Utility files -----

#include "CmdUtils.h"
#include "ILayoutUIUtils.h"
#include "UserInterfaceUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"
#include "SpreadID.h"


//------------------------------------------------------------------------

class TabOrderDialogController : public FieldOrderDialogController
{
	public:
		TabOrderDialogController(IPMUnknown* boss);

	protected:
		void GetOrder( IActiveContext* dlgContext, IDocumentFieldOrder::FieldOrder* outOrder );
		void SetOrder( IDocument* inDocument, const IDocumentFieldOrder::FieldOrder& inOrder );

	private:
		UID fPageUID;
		UID fSpreadUID;
};

//------------------------------------------------------------------------

CREATE_PMINTERFACE(TabOrderDialogController, kTabOrderDialogControllerImpl)

//------------------------------------------------------------------------
//	Constructor
//------------------------------------------------------------------------
TabOrderDialogController::TabOrderDialogController(IPMUnknown* boss)
: FieldOrderDialogController(boss),
fPageUID(kInvalidUID),
fSpreadUID(kInvalidUID)
{
}

//------------------------------------------------------------------------
//	InitializeFields
//	Fills the dialog out with initial values.
//------------------------------------------------------------------------
void TabOrderDialogController::GetOrder( IActiveContext* activeContext, IDocumentFieldOrder::FieldOrder* outOrder )
{
	outOrder->clear();

	InterfacePtr<ILayoutControlData> layoutData( activeContext->GetContextView(), UseDefaultIID());
	ASSERT_MSG(layoutData, "NO Front Layout View");

	if (!layoutData)
		return;

	fSpreadUID = layoutData->GetSpreadRef().GetUID();
	fPageUID = layoutData->GetPage();

	ASSERT_MSG(fSpreadUID != kInvalidUID && fPageUID != kInvalidUID , "No Valid Page or Spread");
	
	if (fSpreadUID == kInvalidUID || fPageUID == kInvalidUID )
		return;

	InterfacePtr<ISpreadFieldOrder> iSpreadFieldOrder(layoutData->GetSpreadRef(), ::UseDefaultIID());

	ISpreadFieldOrder::TabOrder tabOrder = iSpreadFieldOrder->GetTabOrder( fPageUID );

	int32 numItems = tabOrder.size();
	
	for ( int32 ii = 0 ; ii < numItems; ii++ )
	{
		outOrder->push_back( IDocumentFieldOrder::ItemInstance(fSpreadUID, fPageUID, tabOrder[ii]) );
	}
}

//------------------------------------------------------------------------

void TabOrderDialogController::SetOrder(IDocument* inDocument, const IDocumentFieldOrder::FieldOrder& inOrder )
{
	if (!inDocument || fSpreadUID == kInvalidUID || fPageUID == kInvalidUID )
		return;

	ISpreadFieldOrder::TabOrder tabOrder;
	
	int32 numItems = inOrder.size();
	
	for ( int32 ii = 0 ; ii < numItems; ii++ )
	{
		tabOrder.push_back( inOrder[ii].fPageItem );
	}

	// Perform command to set order...

	InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSetTabOrderCmdBoss));
	InterfacePtr<ISetTabOrderCmdData> data(cmd, ::UseDefaultIID());
	data->Set( ::GetUIDRef(inDocument), fSpreadUID, fPageUID, tabOrder );

	CmdUtils::ProcessCommand(cmd);
}

// End, TabOrderDialogController.cpp.

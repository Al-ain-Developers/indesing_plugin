//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/dialogs/FieldOrderDlgController.cpp $
//  
//  Owner: Mark VerMurlen
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

// ----- Interface Includes -----

#include "IActiveContext.h"
#include "IDocument.h"
#include "IGraphicStyleDescriptor.h"
#include "IListBoxController.h"
#include "IPanelControlData.h"

// ----- Implementation Includes -----

#include "AttributesUtils.h"
#include "FieldOrderDlgController.h"
#include "OrderListControlData.h"
#include "OrderListElement.h"
#include "UserInterfaceUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"

using namespace UserInterfaceUtils;

//------------------------------------------------------------------------
//	Constructor
//------------------------------------------------------------------------
FieldOrderDialogController::FieldOrderDialogController(IPMUnknown* boss)
: CDialogController(boss)
{
}

//------------------------------------------------------------------------
//	InitializeFields
//	Fills the dialog out with initial values.
//------------------------------------------------------------------------
void FieldOrderDialogController::InitializeDialogFields( IActiveContext* dlgContext)
{
	InterfacePtr<IPanelControlData>	panelData(this, IID_IPANELCONTROLDATA);

	// Set up list...
			
	IControlView* iListBoxView = panelData->FindWidget(kListBoxListWidgetID);

	InterfacePtr<OrderListControlData> listData(iListBoxView, IID_ILISTCONTROLDATA);
	InterfacePtr<IListBoxController> listController(iListBoxView, IID_ILISTBOXCONTROLLER);

	listData->Clear();

	IDocument* document = dlgContext->GetContextDocument();

	if (document)
	{
		IDocumentFieldOrder::FieldOrder fieldOrder;
		GetOrder( dlgContext, &fieldOrder);

		int32 numItems = fieldOrder.size();
		
		IDataBase* db = ::GetDataBase( document );

		// Find the proper name of each item in the list and add the item with that name...
		
		for(int32 cc = 0; cc < numItems; ++cc)
		{
			const IDocumentFieldOrder::ItemInstance& item = fieldOrder[cc];
			
			InterfacePtr<IGraphicStyleDescriptor> styleDescriptor( UIDRef( db, item.fPageItem ), ::UseDefaultIID() );
			
			if (styleDescriptor)
			{
				PMString name = AttributesUtils::GetStringValue(styleDescriptor, kFormNameAttrBoss);
				
				if (!name.IsEmpty())
					listData->AddELement(OrderListElement(item, name));
			}
				
		}
	}

	listController->DeselectAll();			

	// Setup list buttons.

	IControlView* moveUpButton = panelData->FindWidget(kListBoxMoveUpWidgetID);
	IControlView* moveDownButton = panelData->FindWidget(kListBoxMoveDownWidgetID);
	
	moveUpButton->Enable(kFalse);
	moveDownButton->Enable(kFalse);
}

//------------------------------------------------------------------------

void FieldOrderDialogController::ApplyDialogFields( IActiveContext* myContext, const WidgetID& widgetId)
{
	//If requested, just get the attributes and return, and let the caller deal with it...

	InterfacePtr<IPanelControlData>	panelData(this, IID_IPANELCONTROLDATA);

	IControlView* iListBoxView = panelData->FindWidget(kListBoxListWidgetID);

	InterfacePtr<OrderListControlData> listData(iListBoxView, IID_ILISTCONTROLDATA);

	int32 numListItems = listData->Length();

	IDocumentFieldOrder::FieldOrder fieldOrder;
	
	for (int32 cc = 0; cc < numListItems; cc++)
	{
		IDocumentFieldOrder::ItemInstance choice = listData->GetElementAt(cc).GetItem();
		fieldOrder.push_back( choice );
	}	

	IDocument* document = myContext->GetContextDocument();

	if (document)
	{
		SetOrder( document, fieldOrder);
	}
}

// End, TabOrderDialogController.cpp.

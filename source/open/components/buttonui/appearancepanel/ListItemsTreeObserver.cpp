//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/ListItemsTreeObserver.cpp $
//  
//  Owner: Reena Agrawal
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

#include "IFormFieldSuite.h"
#include "ISelectionDataSuite.h"
#include "ISelectionMessages.h"
#include "ITreeViewController.h"
#include "ITreeViewMgr.h"

// ----- Implementation Includes -----

#include "CActiveSelectionObserver.h"
#include "IntNodeID.h"

// ----- Utility files -----

#include "FormFieldUIUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"
#include "GraphicStylesID.h"

//========================================================================================
// CLASS ListItemsTreeObserver
//========================================================================================

class ListItemsTreeObserver : public CActiveSelectionObserver
{
public:
	typedef CActiveSelectionObserver	Inherited;

	ListItemsTreeObserver(IPMUnknown *boss);
	virtual ~ListItemsTreeObserver();

	virtual void AutoAttach();
	virtual void AutoDetach();

protected:
	virtual void HandleSelectionChanged(const ISelectionMessage*);
	virtual void HandleSelectionAttributeChanged( const ISelectionMessage*	iSelectionMsg );

private:
	void	UpdateOptionsList();
	bool16	fUpdating;

};

//========================================================================================
// METHODS ListItemsTreeObserver
//========================================================================================

CREATE_PMINTERFACE(ListItemsTreeObserver, kListItemsTreeObserverImpl)

//----------------------------------------------------------------------------------------
// ListItemsTreeObserver::ListItemsTreeObserver
//----------------------------------------------------------------------------------------
ListItemsTreeObserver::ListItemsTreeObserver(IPMUnknown *boss) :
	Inherited(boss, IID_IOBSERVER),
	fUpdating(kFalse)
{
}

//----------------------------------------------------------------------------------------
// ListItemsTreeObserver::~ListItemsTreeObserver
//----------------------------------------------------------------------------------------
ListItemsTreeObserver::~ListItemsTreeObserver()
{
}

//----------------------------------------------------------------------------------------
// ListItemsTreeObserver::AutoAttach
//----------------------------------------------------------------------------------------

void ListItemsTreeObserver::AutoAttach()
{
	Inherited::AutoAttach();
	AttachToWidget(kListItemsWidgetID, IID_ITREEVIEWCONTROLLER);
}

//----------------------------------------------------------------------------------------
// ListItemsTreeObserver::AutoDetach
//----------------------------------------------------------------------------------------

void ListItemsTreeObserver::AutoDetach()
{
	Inherited::AutoDetach();
	DetachFromWidget(kListItemsWidgetID, IID_ITREEVIEWCONTROLLER);
}

//----------------------------------------------------------------------------------------
// ListItemsTreeObserver::HandleSelectionChanged
//----------------------------------------------------------------------------------------

void ListItemsTreeObserver::HandleSelectionChanged(const ISelectionMessage* selectionMessage)
{
	if ( !fUpdating )
	{
		fUpdating = kTrue;
		InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );

		Inherited::HandleSelectionChanged(selectionMessage);
		InterfacePtr<ISelectionDataSuite> iSelectionDataSuite(static_cast<ISelectionDataSuite*>(QueryAbstractSelection(IID_ISELECTIONDATASUITE)));
		bool16 isSingleSelection = iSelectionDataSuite && iSelectionDataSuite->GetSelectionCount() == 1;

		if ( isSingleSelection && iFormSuite && !iFormSuite->IsDefaultSelection() && 
			(iFormSuite->IsFieldSelectionOfType(kComboBoxItemBoss) || iFormSuite->IsFieldSelectionOfType(kListBoxFieldItemBoss)) )
		{
			UpdateOptionsList();	
		}
		else
		{
			InterfacePtr<ITreeViewMgr> viewMgr(this, UseDefaultIID());
			if (viewMgr)
				viewMgr->ChangeRoot();
		}

		fUpdating = kFalse;
	}
}

//----------------------------------------------------------------------------------------
// ListItemsTreeObserver::HandleSelectionAttributeChanged
//----------------------------------------------------------------------------------------

void ListItemsTreeObserver::HandleSelectionAttributeChanged( const ISelectionMessage*	iSelectionMsg )
{
	// Update widgets that correspond to the change.
	bool wasFormAttrChanged =	iSelectionMsg->WasSuiteAffected (IID_IAPPEARANCESUITE) ||
								iSelectionMsg->WasSuiteAffected (IID_IGRAPHICATTRIBUTESUITE) ||
								iSelectionMsg->WasSuiteAffected (IID_IFORMFIELDSUITE);
	
	InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
	InterfacePtr<ISelectionDataSuite> iSelectionDataSuite(static_cast<ISelectionDataSuite*>(QueryAbstractSelection(IID_ISELECTIONDATASUITE)));

	if (iFormSuite && wasFormAttrChanged)
	{
		bool16 selectionHasChoiceList = iFormSuite->IsFieldSelectionOfType(kComboBoxItemBoss) || iFormSuite->IsFieldSelectionOfType(kListBoxFieldItemBoss);
		bool16 isSingleSelection = iSelectionDataSuite && iSelectionDataSuite->GetSelectionCount() == 1;

		// Need to update only if its a single list box or a single combo box.
		if (isSingleSelection && selectionHasChoiceList)
			UpdateOptionsList();
	}
}

//----------------------------------------------------------------------------------------
// ListItemsTreeObserver::UpdateOptionsList
//----------------------------------------------------------------------------------------

void ListItemsTreeObserver::UpdateOptionsList()
{
	InterfacePtr<ITreeViewMgr> viewMgr(this, UseDefaultIID());
	if (viewMgr)
		viewMgr->ChangeRoot();

	InterfacePtr<ITreeViewController> viewController(viewMgr, UseDefaultIID());
	ASSERT(viewController != nil);

	PMString defaultChoice;
	int32 defaultChoiceIndex;

	InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
	iFormSuite->GetDefaultChoice(defaultChoice, defaultChoiceIndex);

	viewController->DeselectAll(kTrue, kTrue);
	if (defaultChoiceIndex >= 0)
	{
		// The list/combo box has a default choice.
		viewController->Select(IntNodeID::Create(defaultChoiceIndex), kTrue, kTrue);
	}
}

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/dialogs/OrderListObserver.cpp $
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

#include "IListControlDataOf.h"
#include "IListBoxController.h"
#include "IControlView.h"
#include "ISubject.h"
#include "IWidgetParent.h"
#include "IPanelControlData.h"

#include "CObserver.h"
#include "widgetid.h"
#include "WidgetUtils.h"

#include "K2Vector.h"
#include "OrderListControlData.h"
#include "OrderListElement.h"

#include "FormFieldUIID.h"
#include "FormFieldID.h"

//========================================================================================
// CLASS OrderListObserver
//========================================================================================

class OrderListObserver : public CObserver
{
public:
	OrderListObserver(IPMUnknown *boss);
	virtual ~OrderListObserver();
	
	virtual void AutoAttach();
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);

private:
	void AttachDetachControls(bool inAttach);
	void AttachDetachControl(WidgetID inWID, PMIID inIID, bool32 inAttach);
	bool IsSelection();

	//void		UpdateUserInterface();	
};

//========================================================================================
// METHODS OrderListObserver
//========================================================================================

CREATE_PMINTERFACE(OrderListObserver, kOrderListObserverImpl)

//----------------------------------------------------------------------------------------
// OrderListObserver constructor 
//----------------------------------------------------------------------------------------

OrderListObserver::OrderListObserver(IPMUnknown *boss) :
	CObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// OrderListObserver::~OrderListObserver: 
//----------------------------------------------------------------------------------------

OrderListObserver::~OrderListObserver()
{
}


//----------------------------------------------------------------------------------------
// OrderListObserver::AutoAttach: 
//----------------------------------------------------------------------------------------

void OrderListObserver::AutoAttach()
{
	// ----- Attach to the UI elements.
	
	AttachDetachControls(true);
}

//----------------------------------------------------------------------------------------
// OrderListObserver::AutoDetach: 
//----------------------------------------------------------------------------------------


void OrderListObserver::AutoDetach()
{
	// ----- Detach from the UI elements.
	
	AttachDetachControls(false);
}

//----------------------------------------------------------------------------------------

void OrderListObserver::AttachDetachControl(WidgetID inWID, PMIID inIID, bool32 inAttach)
{
	InterfacePtr<IControlView> iView((IControlView *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, inWID, IID_ICONTROLVIEW));
	ASSERT_MSG(iView != nil, "FormFieldUIWidgetsObserver::AttachDetachControl: Can't find widget ID!");
	if (iView == nil)
		return;
		
	InterfacePtr<ISubject> iSubject(iView, IID_ISUBJECT);
	if (inAttach)
		iSubject->AttachObserver( this, inIID);
	else
		iSubject->DetachObserver( this, inIID);
}

//----------------------------------------------------------------------------------------

void OrderListObserver::AttachDetachControls(bool inAttach)
{
	AttachDetachControl(kListBoxListWidgetID, IID_ILISTCONTROLDATA, inAttach);

	AttachDetachControl(kListBoxMoveUpWidgetID, IID_IBOOLEANCONTROLDATA, inAttach);
	AttachDetachControl(kListBoxMoveDownWidgetID, IID_IBOOLEANCONTROLDATA, inAttach);
}

//----------------------------------------------------------------------------------------

bool OrderListObserver::IsSelection()
{
	InterfacePtr<IListBoxController> listController(this, IID_ILISTBOXCONTROLLER);

	K2Vector<int32> selectedIndeces;
	listController->GetSelected(selectedIndeces);
	return selectedIndeces.size() > 0;
}

//----------------------------------------------------------------------------------------
// OrderListObserver::Update: 
//----------------------------------------------------------------------------------------

void OrderListObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	InterfacePtr<IControlView> iView(theSubject, IID_ICONTROLVIEW);
	WidgetID wid = iView->GetWidgetID();

	if (protocol == IID_ILISTCONTROLDATA && 
		(theChange == kListSelectionChangedMessage || theChange == kListSelectionChangedByUserMessage))
	{

		//Update item, export name edit fields to match list selection
		if (wid.Get() == kListBoxListWidgetID )
		{
			bool hasSelection =  IsSelection() ;

			InterfacePtr<IControlView> moveUpButton((IControlView *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kListBoxMoveUpWidgetID, IID_ICONTROLVIEW));
			InterfacePtr<IControlView> moveDownButton((IControlView *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kListBoxMoveDownWidgetID, IID_ICONTROLVIEW));

			moveUpButton->Enable( hasSelection );
			moveDownButton->Enable( hasSelection );
		}
	}
	else if (protocol == IID_IBOOLEANCONTROLDATA && theChange == kTrueStateMessage
			 && ( wid.Get()  == kListBoxMoveUpWidgetID || wid.Get()  == kListBoxMoveDownWidgetID)
			)	//sent by the command buttons
	{

		InterfacePtr<OrderListControlData> listData(this, IID_ILISTCONTROLDATA);
		
		InterfacePtr<IListBoxController> listController(this, IID_ILISTBOXCONTROLLER);
		
		K2Vector<OrderListElement> beforeSelectedElements;
		K2Vector<OrderListElement> selectedElements;
		K2Vector<OrderListElement> afterSelectedElements;
		
		int32 numElements = listData->Length();
		bool selectionFound = false;
		IListBoxController::eScrollDirection scrollDirection = IListBoxController::kNoScroll;
		if ( wid.Get() == kListBoxMoveUpWidgetID )
		{
			scrollDirection = IListBoxController::kScrollUpSlow;
			for (int32 ii = 0; ii < numElements; ii++)
			{
				if (listController->IsSelected(ii)) {
					selectedElements.push_back(listData->GetElementAt(ii));
					if ( beforeSelectedElements.size() != 0 && !selectionFound ) {
						afterSelectedElements.insert(afterSelectedElements.begin(), beforeSelectedElements.back());
						beforeSelectedElements.erase(beforeSelectedElements.begin() + beforeSelectedElements.size()-1);
					}
					selectionFound = true;
				}
				else if ( selectionFound )
					afterSelectedElements.push_back(listData->GetElementAt(ii));
				else
					beforeSelectedElements.push_back(listData->GetElementAt(ii));
			}
		}
		else {
			scrollDirection = IListBoxController::kScrollDownSlow;
			for (int32 ii = numElements-1; ii >=0; ii--)
			{
				if (listController->IsSelected(ii)) {
					selectedElements.insert(selectedElements.begin(), listData->GetElementAt(ii));
					if ( afterSelectedElements.size() != 0 && !selectionFound ) {
						beforeSelectedElements.push_back(afterSelectedElements.front());
						afterSelectedElements.erase(afterSelectedElements.begin());
					}
					selectionFound = true;
				}
				else if ( selectionFound )
					beforeSelectedElements.insert(beforeSelectedElements.begin(), listData->GetElementAt(ii));
				else
					afterSelectedElements.insert(afterSelectedElements.begin(), listData->GetElementAt(ii));
			}
		}
		
		listData->Clear();

		listData->AddELement(beforeSelectedElements);
		listData->AddELement(selectedElements);
		listData->AddELement(afterSelectedElements);
		
		int32 firstSelectedIndex = beforeSelectedElements.size();
		int32 lastSelectedIndex = firstSelectedIndex + selectedElements.size() - 1;
		
		for (int32 ee = firstSelectedIndex; ee <= lastSelectedIndex; ee++)
		{
			bool inval = ( ee == lastSelectedIndex );
			listController->Select( ee,  inval, inval );

			// Scroll the item into view.
			int32 firstVisibleItem = listController->GetFirstVisibleItem();
			int32 numVisibleItems = listController->GetMaximumVisibleItems();
			
			if(ee < firstVisibleItem || ee > firstVisibleItem + numVisibleItems)
				listController->ScrollList(scrollDirection);
		}
	}
}

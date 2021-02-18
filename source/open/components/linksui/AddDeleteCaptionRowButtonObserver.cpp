//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/AddDeleteCaptionRowButtonObserver.cpp $
//  
//  Owner: lance bushore
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
#include "IApplication.h"
#include "IEventHandler.h"
#include "IKeyBoard.h"
#include "ISubject.h"
#include "IControlView.h"
#include "IWidgetParent.h"
#include "IDialogController.h"
#include "IPanelControlData.h"
#include "ILinksUIUtils.h"
#include "IEVEUtils.h"
#include "IDropDownListController.h"

// ----- Includes -----

#include "CObserver.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"
#include "CoreResTypes.h"
#include "LinksUIResDefs.h"

// ----- Utility files -----
#include "Utils.h"

// ----- ID.h files -----

#include "LinksUIID.h"
#include "LinksID.h"

//------ Drover Utilities----
#include "DVUtilities.h"

class AddDeleteCaptionRowButtonObserver : public CObserver
{
	private:
		IControlView* RemoveFocusFromCurrentFocussedWidget(IKeyBoard* kb, IControlView*rowView, WidgetID& widgetID);
		IControlView* GetNextFocussedWidget(IControlView* rowView, IPanelControlData* rowsContainer, const WidgetID widgetID);

	public:
		AddDeleteCaptionRowButtonObserver(IPMUnknown *boss);
		virtual ~AddDeleteCaptionRowButtonObserver();
		
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
		
		virtual void AutoAttach();
		virtual void AutoDetach();
};


CREATE_PMINTERFACE(AddDeleteCaptionRowButtonObserver, kAddDeleteCaptionRowButtonObserverImpl)

AddDeleteCaptionRowButtonObserver::AddDeleteCaptionRowButtonObserver(IPMUnknown *boss) :
	CObserver(boss)
{
}

AddDeleteCaptionRowButtonObserver::~AddDeleteCaptionRowButtonObserver()
{
}

void AddDeleteCaptionRowButtonObserver::AutoAttach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject)
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);

}

void AddDeleteCaptionRowButtonObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject)
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);
	
}

void AddDeleteCaptionRowButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	#pragma unused(changedBy)
	if (protocol == IID_ITRISTATECONTROLDATA && theChange == kTrueStateMessage)
	{
		InterfacePtr<const IControlView> buttonView(theSubject,UseDefaultIID());
		ASSERT_MSG(buttonView->GetWidgetID() == kCaptionDeleteRowWidgetID || buttonView->GetWidgetID() == kCaptionAddRowWidgetID,"Unexpected widget notification");
		bool addingRow = (buttonView->GetWidgetID() == kCaptionAddRowWidgetID);

		InterfacePtr<const IWidgetParent> wp(this,UseDefaultIID());
		InterfacePtr<const IDialogController> dialogControl((IDialogController*)wp->QueryParentFor(IID_IDIALOGCONTROLLER));
		InterfacePtr<const IPanelControlData> dialogPanelData(dialogControl, UseDefaultIID());
		InterfacePtr<IControlView> dialogView(dialogControl, UseDefaultIID());

		if(addingRow)
		{
			InterfacePtr<const IControlView> rowView((IControlView*)wp->QueryParentFor(IID_ICONTROLVIEW));
			ASSERT_MSG(rowView->GetWidgetID() == kDynamicCaptionRowWidgetID,"unexpected parent ID. did someone rearrange stuff in the view file?");

			IControlView* rowContainer = dialogPanelData->FindWidget(kSelectCaptionRowsPanelWidgetID);
			InterfacePtr<IPanelControlData> rowContainerPanelData(rowContainer,UseDefaultIID());
			int32 currentRowIndex = rowContainerPanelData->GetIndex(rowView);
			
			// create new row widget, init the data
			InterfacePtr<IControlView> newRowView ((IControlView*)::CreateObject(::GetDataBase(rowContainerPanelData),RsrcSpec(LocaleSetting::GetLocale(), kLinksUIPluginID, kViewRsrcType, kDynamicCaptionRowResID),IID_ICONTROLVIEW));
			int32 newRowIndex = currentRowIndex == rowContainerPanelData->Length() ? -1 : currentRowIndex + 1;
			rowContainerPanelData->AddWidget(newRowView,newRowIndex,kFalse);
			Utils<ILinksUIUtils>()->SetupCaptionRowWidget(newRowView,"","","");
			InterfacePtr<const IPanelControlData> newRowPanelData(newRowView,UseDefaultIID());
			InterfacePtr<IDropDownListController> ddController(newRowPanelData->FindWidget(kCaptionMetadataDropDownWidgetID),UseDefaultIID());
			ddController->Select(rowContainerPanelData->Length(),kFalse);
			
		}
		else
		{
			InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
			InterfacePtr<IKeyBoard> kb(theApp, UseDefaultIID());

			InterfacePtr<IControlView> rowView((IControlView*)wp->QueryParentFor(IID_ICONTROLVIEW));
			ASSERT_MSG(rowView->GetWidgetID() == kDynamicCaptionRowWidgetID,"unexpected parent ID. did someone rearrange stuff in the view file?");
			InterfacePtr<const IWidgetParent> parentWP(rowView,UseDefaultIID());
			InterfacePtr<IPanelControlData> rowsContainer((IPanelControlData*)parentWP->QueryParentFor(IID_IPANELCONTROLDATA));
#ifdef DEBUG
			InterfacePtr<IControlView> rowsContainerView(rowsContainer,UseDefaultIID());
			ASSERT_MSG(rowsContainerView->GetWidgetID() == kSelectCaptionRowsPanelWidgetID,"unexpected grandparent ID. did someone rearrange stuff in the view file?");
#endif
			if(rowsContainer->Length() > 1)
			{
				WidgetID widgetID = NULL;
				IControlView * currFocussedView = RemoveFocusFromCurrentFocussedWidget(kb, rowView, widgetID);
				if (currFocussedView) {

					IControlView *nextFocussedRowView = GetNextFocussedWidget(rowView, rowsContainer, widgetID);
					ASSERT_MSG(nextFocussedRowView, "AddDeleteCaptionRowButtonObserver : Invalid Widget gaining focus.");
					InterfacePtr<IPanelControlData> nextFocussedRowPanelData(nextFocussedRowView, UseDefaultIID());
					rowsContainer->RemoveWidget(rowView, kTrue, kTrue);
					Utils<IEVEUtils>()->ApplyEveLayout(dialogView); // We need to force relayout here.
					nextFocussedRowPanelData->SetKeyboardFocus(widgetID);

					return;
				}
				else {
					rowsContainer->RemoveWidget(rowView, kTrue, kTrue);
				}
			}
		}
		Utils<IEVEUtils>()->ApplyEveLayout(dialogView);
	
	}
}

IControlView* AddDeleteCaptionRowButtonObserver::RemoveFocusFromCurrentFocussedWidget(IKeyBoard* kb, IControlView*rowView, WidgetID& widgetID)
{
	IEventHandler* focussedEH = kb->GetKeyFocus();
	InterfacePtr<IEventHandler> rowEventHandler(rowView, IID_IEVENTHANDLER);
	if (focussedEH) 
	{
		InterfacePtr<IControlView> currFocusView(focussedEH, UseDefaultIID());
		widgetID = currFocusView->GetWidgetID();
		if ((focussedEH == rowEventHandler) || dv_utils::IsChildOf(currFocusView, rowView)) 
			{
				kb->RelinquishKeyFocus();
				return currFocusView;
			}
	}
	return NULL;
}

IControlView* AddDeleteCaptionRowButtonObserver::GetNextFocussedWidget(IControlView* rowView, IPanelControlData* rowsContainer, const WidgetID widgetID)
{
	int32 deletedRowIndex = rowsContainer->GetIndex(rowView);
	int32 nextFocussedRowIndex = (deletedRowIndex == (rowsContainer->Length() - 1)) ? deletedRowIndex - 1 : deletedRowIndex + 1;
	
	ASSERT_MSG(((nextFocussedRowIndex >= 0) && (nextFocussedRowIndex < rowsContainer->Length())), "AddDeleteCaptionRowButtonObserver.cpp : nextFocussedRowIndex is not valid.");
	IControlView *nextFocussedRowView = rowsContainer->GetWidget(nextFocussedRowIndex);
	
	return nextFocussedRowView;
}

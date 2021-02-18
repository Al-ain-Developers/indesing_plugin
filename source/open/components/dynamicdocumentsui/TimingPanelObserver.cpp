//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/TimingPanelObserver.cpp $
//  
//  Owner: Yeming Liu
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

// ----- Interface files -----

#include "IActiveContext.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IDynamicEventTimingFacade.h"
#include "IDynamicEventTimingSuite.h"
#include "IHierarchy.h"
#include "ILayoutControlData.h"
#include "IPanelControlData.h"
#include "ISelectionManager.h"
#include "ISpreadDynamicContentMgr.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITextValue.h"
#include "ITreeViewController.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITreeViewMgr.h"
#include "ITriStateControlData.h"
#include "IApplication.h"
#include "IActionManager.h"
#include "KeyStates.h"

// ----- Include files -----

#include "SelectionObserver.h"
#include "ListLazyNotificationData.h"
#include "TimingPanelTreeNodeID.h"
#include "K2Vector.tpp"	// for NodeIDList

// ----- Utility files -----

#include "DynamicDocumentsUIUtils.h"
#include "IAnimationUtils.h"
#include "IWidgetUtils.h"

// ----- ID files -----

#include "DynamicDocumentsUIID.h"
#include "GenericID.h"
#include "FormFieldID.h"
#include "SpreadID.h"

class TimingPanelObserver : public ActiveSelectionObserver
{
	public:
		TimingPanelObserver(IPMUnknown *boss);
		
		virtual void AutoAttach(); 
		virtual void AutoDetach();

		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
		virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data);

		virtual void HandleSelectionChanged(const ISelectionMessage* iSelectionMessage);
		virtual void HandleSelectionAttributeChanged(const ISelectionMessage* iSelectionMessage);
		virtual void HandleActiveSelectionChanged ();
		
	private:
		void AttachDetachDropDownWidget(WidgetID const &widgetID, bool const &bAttach);
		void AttachDetachInlineDelayWidget(WidgetID const &widgetID, bool const &bAttach);
		void AttachDetachTreeViewWidget(WidgetID const &widgetID, bool const &bAttach);
		void AttachDetachButtonWidget(WidgetID const &widgetID, bool const &bAttach);
		void AttachDetachEditBoxWidget(WidgetID const &widgetID, bool const &bAttach);
		void AttachDetachDocument(IControlView* iLayoutView, bool const &bAttac);
		void AttachToLayoutView();
		void DetachFromLayoutView();

		void UpdateWidgets();
		void UpdateEvents();
		void UpdateTreeView();
		void UpdateDelayWidget();
		void UpdateNumPlaysLoopWidgets();
		void UpdateLabelString(PMString const &labelString, WidgetID const &widgetID);
		void UpdateGroupUngroupButtons();
		void UpdatePreviewButton();
		void UpdateChangedTimingItems(K2Vector<UID> const &changedItems);
		void GroupUngroupTargets(WidgetID const &widgetID);
		void SetTargetDelay(PMReal const &delay);
		void SetTargetNumPlays(int32 const &numPlays);
		void SetTargetLoop(bool const bOn);
		bool CanSelectedItemsBeGrouped();
		bool CanSelectedItemsBeUngrouped();

		IControlView* fCurrentLayoutView;
};

CREATE_PMINTERFACE(TimingPanelObserver, kTimingPanelObserverImpl)

//----------------------------------------------------------------------------------------
// TimingPanelObserver::TimingPanelObserver()
//----------------------------------------------------------------------------------------
TimingPanelObserver::TimingPanelObserver(IPMUnknown *boss) :
	ActiveSelectionObserver(boss),
	fCurrentLayoutView(nil)
{
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::AutoAttach()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::AutoAttach()
{
	//
	// Attach to active selection changes.
	//
 	ActiveSelectionObserver::AutoAttach();  

	//
	// Attach to current layout
	//
	this->AttachToLayoutView();

	//
	// Attach to event drop down list
	//
	this->AttachDetachDropDownWidget(kTimingPanelEventDropDownWidgetID, true/*attach*/);

	//
	// Attach to delay inline edit box
	//
	this->AttachDetachInlineDelayWidget(kTimingDelayILEWidgetID, true/*attach*/);

	//
	// Attach to loop widgets
	//
	this->AttachDetachEditBoxWidget(kTimingPanelPlayLinkedItemEditBoxWidgetID, true/*attach*/);
	this->AttachDetachButtonWidget(kTimingPanelLoopCheckBoxWidgetID, true/*attach*/);

	//
	// Attach to tree view widget
	//
	this->AttachDetachTreeViewWidget(kTimingPanelTreeWidgetID, true/*attach*/);

	//
	// Attach group/ungroup buttons
	//
	this->AttachDetachButtonWidget(kTimingPanelGroupButtonWidgetID, true/*attach*/);
	this->AttachDetachButtonWidget(kTimingPanelUngroupButtonWidgetID, true/*attach*/);
	this->AttachDetachButtonWidget(kTimingPanelPreviewButtonWidgetID, true/*attach*/);
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::AutoDetach()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::AutoDetach()
{
	//
	// Detach to event drop down list
	//
	this->AttachDetachDropDownWidget(kTimingPanelEventDropDownWidgetID, false/*attach*/);

	//
	// Detach to delay inline edit box
	//
	this->AttachDetachInlineDelayWidget(kTimingDelayILEWidgetID, false/*attach*/);

	//
	// Attach to loop widgets
	//
	this->AttachDetachEditBoxWidget(kTimingPanelPlayLinkedItemEditBoxWidgetID, false/*attach*/);
	this->AttachDetachButtonWidget(kTimingPanelLoopCheckBoxWidgetID, false/*attach*/);

	//
	// Detach to tree view widget
	//
	this->AttachDetachTreeViewWidget(kTimingPanelTreeWidgetID, false/*attach*/);

	//
	// Detach group/ungroup buttons
	//
	this->AttachDetachButtonWidget(kTimingPanelGroupButtonWidgetID, false/*attach*/);
	this->AttachDetachButtonWidget(kTimingPanelUngroupButtonWidgetID, false/*attach*/);
	this->AttachDetachButtonWidget(kTimingPanelPreviewButtonWidgetID, false/*attach*/);

	//
	// Detach from current layout
	//
	this->DetachFromLayoutView();

	//
	// Detach from active context
	//
    ActiveSelectionObserver::AutoDetach();
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::AttachDetachDropDownWidget()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::AttachDetachDropDownWidget(WidgetID const &widgetID, bool const &bAttach)
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());	
	IControlView* dropDownWidget = iPanelControlData->FindWidget(widgetID);

	InterfacePtr<ISubject> iDropDownWidgetSubject(dropDownWidget, UseDefaultIID());
	if (iDropDownWidgetSubject)
	{	
		if (bAttach && !iDropDownWidgetSubject->IsAttached( this, IID_ISTRINGLISTCONTROLDATA, IID_IOBSERVER))
			iDropDownWidgetSubject->AttachObserver(this, IID_ISTRINGLISTCONTROLDATA, IID_IOBSERVER);
		else if (!bAttach && iDropDownWidgetSubject->IsAttached( this, IID_ISTRINGLISTCONTROLDATA, IID_IOBSERVER))
			iDropDownWidgetSubject->DetachObserver(this, IID_ISTRINGLISTCONTROLDATA, IID_IOBSERVER);
	}
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::AttachDetachInlineDelayWidget()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::AttachDetachInlineDelayWidget(WidgetID const &widgetID, bool const &bAttach)
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());	
	IControlView* textWidget = iPanelControlData->FindWidget(widgetID);

	InterfacePtr<ISubject> iInlineDelayWidgetSubject(textWidget, UseDefaultIID());
	if (iInlineDelayWidgetSubject)
	{
#if 0
		//	If inline scrubby tool, uncomment this code
		if (bAttach && !iInlineDelayWidgetSubject->IsAttached( this, IID_IINLINEEDITCONTROLLER, IID_IOBSERVER))
			iInlineDelayWidgetSubject->AttachObserver(this, IID_IINLINEEDITCONTROLLER, IID_IOBSERVER);
		else if (!bAttach && iInlineDelayWidgetSubject->IsAttached( this, IID_IINLINEEDITCONTROLLER, IID_IOBSERVER))
			iInlineDelayWidgetSubject->DetachObserver(this, IID_IINLINEEDITCONTROLLER, IID_IOBSERVER);
#endif

		if (bAttach && !iInlineDelayWidgetSubject->IsAttached( this, IID_ITEXTCONTROLDATA, IID_IOBSERVER))
			iInlineDelayWidgetSubject->AttachObserver(this, IID_ITEXTCONTROLDATA, IID_IOBSERVER);
		else if (!bAttach && iInlineDelayWidgetSubject->IsAttached( this, IID_ITEXTCONTROLDATA, IID_IOBSERVER))
			iInlineDelayWidgetSubject->DetachObserver(this, IID_ITEXTCONTROLDATA, IID_IOBSERVER);
	}
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::AttachDetachTreeViewWidget()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::AttachDetachTreeViewWidget(WidgetID const &widgetID, bool const &bAttach)
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());	
	IControlView* treeViewWidget = iPanelControlData->FindWidget(widgetID);

	InterfacePtr<ISubject> iTreeViewSubject(treeViewWidget, UseDefaultIID());
	if (iTreeViewSubject)
	{
		if (bAttach && !iTreeViewSubject->IsAttached(this, IID_ITREEVIEWCONTROLLER))
			iTreeViewSubject->AttachObserver(this, IID_ITREEVIEWCONTROLLER); 
		else if (!bAttach && iTreeViewSubject->IsAttached(this, IID_ITREEVIEWCONTROLLER))
			iTreeViewSubject->DetachObserver(this, IID_ITREEVIEWCONTROLLER); 
	}
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::AttachDetachEditBoxWidget()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::AttachDetachEditBoxWidget(WidgetID const &widgetID, bool const &bAttach)
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	IControlView* editBoxWidget = iPanelControlData->FindWidget(widgetID);

	InterfacePtr<ISubject> iEditBoxSubject(editBoxWidget, UseDefaultIID());
	if (iEditBoxSubject)
	{
		if (bAttach && !iEditBoxSubject->IsAttached( this,  IID_ITEXTCONTROLDATA, IID_IOBSERVER))
			iEditBoxSubject->AttachObserver(this,  IID_ITEXTCONTROLDATA, IID_IOBSERVER);
		else if (!bAttach && iEditBoxSubject->IsAttached(this,  IID_ITEXTCONTROLDATA, IID_IOBSERVER))
			iEditBoxSubject->DetachObserver(this,  IID_ITEXTCONTROLDATA, IID_IOBSERVER);
	}
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::AttachDetachButtonWidget()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::AttachDetachButtonWidget(WidgetID const &widgetID, bool const &bAttach)
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	IControlView* buttonWidget = iPanelControlData->FindWidget(widgetID);

	InterfacePtr<ISubject> iButtonSubject(buttonWidget, UseDefaultIID());
	if (iButtonSubject)
	{
		if (bAttach && !iButtonSubject->IsAttached( this,  IID_ITRISTATECONTROLDATA, IID_IOBSERVER))
			iButtonSubject->AttachObserver(this,  IID_ITRISTATECONTROLDATA, IID_IOBSERVER);
		else if (!bAttach && iButtonSubject->IsAttached(this,  IID_ITRISTATECONTROLDATA, IID_IOBSERVER))
			iButtonSubject->DetachObserver(this,  IID_ITRISTATECONTROLDATA, IID_IOBSERVER);
	}
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::AttachToLayoutView()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::AttachToLayoutView()
{
	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	if (context)
	{
		IControlView* activeView = context->GetContextView();
		if (activeView)
		{
			this->AttachDetachDocument(activeView, true/*bAttach*/);

			fCurrentLayoutView = activeView;
		}
	}
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::DetachFromLayoutView()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::DetachFromLayoutView()
{	
	this->AttachDetachDocument(fCurrentLayoutView, false/*bAttach*/);
	
	fCurrentLayoutView = nil;
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::AttachDetachDocument()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::AttachDetachDocument(IControlView* iLayoutView, bool const &bAttach)
{ 	
	if (iLayoutView)
	{
		InterfacePtr<ILayoutControlData> iLayoutControlData(iLayoutView, UseDefaultIID());

		IDocument* iDocument = iLayoutControlData ? iLayoutControlData->GetDocument() : nil;

		InterfacePtr<ISubject> iDocumentSubject(iDocument, UseDefaultIID());
		if (iDocumentSubject)
		{
			//
			// IID_IDYNAMICEVENTTIMING_DOCUMENT --- for timing items change
			//
			if (bAttach && !iDocumentSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IDYNAMICEVENTTIMING_DOCUMENT, IID_IOBSERVER)) 
				iDocumentSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_IDYNAMICEVENTTIMING_DOCUMENT, IID_IOBSERVER); 
			else if (!bAttach && iDocumentSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IDYNAMICEVENTTIMING_DOCUMENT, IID_IOBSERVER)) 
				iDocumentSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_IDYNAMICEVENTTIMING_DOCUMENT, IID_IOBSERVER); 

			//
			// IID_ISPREADLIST --- for add/delete/modify pages/spreads
			//
			if (bAttach && !iDocumentSubject->IsAttached(ISubject::kLazyAttachment,this, IID_ISPREADLIST, IID_IOBSERVER))
				iDocumentSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_ISPREADLIST, IID_IOBSERVER);
			else if (!bAttach && iDocumentSubject->IsAttached(ISubject::kLazyAttachment,this, IID_ISPREADLIST, IID_IOBSERVER))
				iDocumentSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_ISPREADLIST, IID_IOBSERVER);

			//
			// IID_IPAGEITEMNAME --- for page item name change
			//
			if (bAttach && !iDocumentSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IPAGEITEMNAME, IID_IOBSERVER)) 
				iDocumentSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_IPAGEITEMNAME, IID_IOBSERVER); 
			else if (!bAttach && iDocumentSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IPAGEITEMNAME, IID_IOBSERVER)) 
				iDocumentSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_IPAGEITEMNAME, IID_IOBSERVER); 
		}

		//
		// IID_IACTIVESPREAD --- for active spread change
		//
		InterfacePtr<ISubject> iLayoutViewSubject(iLayoutView, UseDefaultIID());
		if (iLayoutViewSubject)
		{
			if (bAttach && !iLayoutViewSubject->IsAttached(ISubject::kLazyAttachment,this, IID_IACTIVESPREAD, IID_IOBSERVER))
				iLayoutViewSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_IACTIVESPREAD, IID_IOBSERVER);
			else if (!bAttach && iLayoutViewSubject->IsAttached(ISubject::kLazyAttachment,this, IID_IACTIVESPREAD, IID_IOBSERVER))
				iLayoutViewSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_IACTIVESPREAD, IID_IOBSERVER);
		}
	}
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::LazyUpdate()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data)
{
	switch (protocol.Get())
	{
		case IID_IDYNAMICEVENTTIMING_DOCUMENT:
		{
			this->UpdateWidgets();
			break;
		}
		case IID_IPAGEITEMNAME:
		{				
			const ListLazyNotificationData<UID>*  listData = static_cast<const ListLazyNotificationData<UID>* > (data);
			if (!listData)
				this->UpdateWidgets();
			else 
			{
				K2Vector<UID> changedItems;
				listData->BreakoutChanges(nil, nil, &changedItems);
				ASSERT(changedItems.size() > 0);
				if (changedItems.size() > 0)
					this->UpdateChangedTimingItems(changedItems);
			}
			break;
		}
		case IID_ISPREADLIST:
		case IID_IACTIVESPREAD:
		{
			this->UpdateWidgets();
			break;
		}
		default:
			break;
	}
	
}

void TimingPanelObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{	
	ActiveSelectionObserver::Update(theChange, theSubject, protocol, changedBy);

	InterfacePtr<IControlView> iWidgetView(theSubject, UseDefaultIID());
	WidgetID widgetID = iWidgetView ? iWidgetView->GetWidgetID() : kInvalidWidgetID;
	if (widgetID == kInvalidWidgetID)
		return;
	
	if (theChange == kListSelectionChangedMessage)
	{
		//
		// Selection changed in the tree 
		//
		if (widgetID == kTimingPanelTreeWidgetID)
		{	
			this->UpdateDelayWidget();
			this->UpdateNumPlaysLoopWidgets();
			this->UpdateGroupUngroupButtons();
		}
	}
	else
	{
		switch (protocol.Get())
		{
			case IID_ISTRINGLISTCONTROLDATA:  // change of event
			{
				if (widgetID == kTimingPanelEventDropDownWidgetID)
				{
					//	Need to deselect all in the timing list when switching event.
					//	Done in UpdateTreeView ().
					this->UpdateTreeView();
					this->UpdateDelayWidget();
				}
				break;
			}
			case IID_IINLINEEDITCONTROLLER:	// change of delay
			case IID_ITEXTCONTROLDATA:
			{
				if ((widgetID == kTimingDelayILEWidgetID) && 
					((theChange == kInLineEditStartEditingMessageID) || (theChange == kTextChangeStateMessage)))
				{
					InterfacePtr<ITextValue> iDelayControlData (nil);
					InterfacePtr<IPanelControlData> iInlinePanelData(iWidgetView, UseDefaultIID());
					if (iInlinePanelData)
					{
						IControlView * iStaticTextView = iInlinePanelData->FindWidget(kInLineEditStaticTextWidgetID);
						iDelayControlData = InterfacePtr<ITextValue> (iStaticTextView, UseDefaultIID()); 
					}
					else
					{
						iDelayControlData = InterfacePtr<ITextValue> (iWidgetView, UseDefaultIID()); 
					}
					
					bool16 bError = kFalse;
					PMReal delay = iDelayControlData->GetTextAsValue(&bError);
					if (!bError)
						this->SetTargetDelay(delay);
				}
				else if (widgetID == kTimingPanelPlayLinkedItemEditBoxWidgetID)
				{
					InterfacePtr<ITextControlData> iNumPlaysControlData(iWidgetView, UseDefaultIID());
					const PMString numPlaysString = iNumPlaysControlData->GetString();
					int32 numPlays = numPlaysString.GetAsNumber();

					this->SetTargetNumPlays(numPlays);

				}
				break;
			}
			case IID_ITRISTATECONTROLDATA:	// click group/ungroup button
			{
				InterfacePtr<ITriStateControlData> iTriStateControlData(theSubject, UseDefaultIID());
				bool bOn = iTriStateControlData->IsSelected();

				if (widgetID == kTimingPanelLoopCheckBoxWidgetID)
					this->SetTargetLoop(bOn);
				else if (theChange == kTrueStateMessage)
				{
					if ((widgetID == kTimingPanelGroupButtonWidgetID) || (widgetID == kTimingPanelUngroupButtonWidgetID))
						this->GroupUngroupTargets(widgetID);
					else if (widgetID == kTimingPanelPreviewButtonWidgetID)
					{											
						// HTML Preview
                        InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
                        InterfacePtr<IActionManager> actionMgr(theApp->QueryActionManager());
                        actionMgr->PerformAction(GetExecutionContextSession()->GetActiveContext(), kHTMLFXLPreviewActionID);
					}		
				}

				break;
			}
			default:
			{
				break;
			}
		}
	}
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::HandleSelectionChanged()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::HandleSelectionChanged(const ISelectionMessage* iSelectionMessage)
{        
	if (fCurrentSelection)
	{
		this->UpdateWidgets();
	}
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::HandleSelectionAttributeChanged()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::HandleSelectionAttributeChanged(const ISelectionMessage* iSelectionMessage)
{
	if (iSelectionMessage && iSelectionMessage->WasSuiteAffected (IID_IDYNAMICEVENTTIMINGSUITE)) 
	{     
		this->UpdateWidgets();
	} 
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::HandleActiveSelectionChanged()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::HandleActiveSelectionChanged()
{
	this->DetachFromLayoutView();

	this->AttachToLayoutView();
	
	ActiveSelectionObserver::HandleActiveSelectionChanged ();
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::UpdateWidgets()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::UpdateWidgets()
{	
	//
	// Update event entries
	//
	this->UpdateEvents();

	//
	// Update tree view
	//	
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	IControlView* iTreeView = iPanelControlData->FindWidget(kTimingPanelTreeWidgetID);
	InterfacePtr<ITreeViewMgr> iTreeViewMgr(iTreeView, UseDefaultIID()); 
	iTreeViewMgr->ChangeRoot();

	//
	// Enable/Disable widgets in the panel
	//
	IControlView* iEventGroupView = iPanelControlData->FindWidget(kTimingPanelEventGroupWidgetID);
	IControlView* iEventDropDown = iPanelControlData->FindWidget(kTimingPanelEventDropDownWidgetID);
	InterfacePtr<IDropDownListController> iEventDDListController(iEventDropDown, UseDefaultIID());

	if (iEventDDListController->GetSelected() == IDropDownListController::kNoSelection)
	{
		iEventGroupView->Disable();
		iTreeView->Disable();
	}
	else
	{
		iEventGroupView->Enable();
		iTreeView->Enable();
	}

	// 
	// Update delay widget
	// 
	this->UpdateDelayWidget();	

	// 
	// Update num plays and loop widget
	// 
	this->UpdateNumPlaysLoopWidgets();	

	//
	// Update group/ungroup buttons
	//
	this->UpdateGroupUngroupButtons();

	//
	// Update preview button
	//
	this->UpdatePreviewButton();
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::UpdatePreviewButton()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::UpdatePreviewButton()
{
	InterfacePtr<IPanelControlData const> iPanelControlData(this, UseDefaultIID());
	InterfacePtr<IControlView> iPreviewButtonView(iPanelControlData->FindWidget(kTimingPanelPreviewButtonWidgetID), UseDefaultIID());
	
	if (fCurrentLayoutView)
	{
		InterfacePtr<ILayoutControlData> iLayoutControlData(fCurrentLayoutView, UseDefaultIID());
		
		if (iLayoutControlData)
			iPreviewButtonView->Enable();
		else
			iPreviewButtonView->Disable();
	}
	else
	{
		iPreviewButtonView->Disable();
	}
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::UpdateEvents()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::UpdateEvents()
{	
	//
	// Cache the original event type.
	//
	EventTriggerType currentTriggerType = ddui_utils::GetCurrentEventTypeInTimingPanel();

	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	IControlView* eventDropDown = iPanelControlData->FindWidget(kTimingPanelEventDropDownWidgetID);
	InterfacePtr<IStringListControlData> iEventDropDownStringData(eventDropDown, UseDefaultIID());
	iEventDropDownStringData->Clear(kTrue, kFalse);


	InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite (static_cast<IDynamicEventTimingSuite*>(this->QueryAbstractSelection (IID_IDYNAMICEVENTTIMINGSUITE))); 
	if (iDynamicEventTimingSuite == nil) 
		return;

	int32 numEvents = 0;
	if (iDynamicEventTimingSuite->CanApply())
		numEvents = iDynamicEventTimingSuite->GetNumDynamicEvents();

	int32 selectIndex = -1;
	PMString selectEventName(kNullString);
	int32 numEventsIgnored = 0;

	if (numEvents > 0)
	{
		ISpreadDynamicContentMgr::DynamicContentType contentType = ISpreadDynamicContentMgr::kAnimationItemType;
		if (iDynamicEventTimingSuite->GetTimingParentClassID () == kMultiStateObjectItemBoss) contentType = ISpreadDynamicContentMgr::kMultiStateItemType;

		for (int32 i = 0; i < numEvents; ++i)
		{
			EventTriggerType eventType = iDynamicEventTimingSuite->GetNthDynamicEvent(i);
			ASSERT (eventType != kNoTriggerEvent);
			
			//
			// Filter out Self click/Rollover since they should not be in the timing panel.
			//
			if ((eventType == kOnSelfClick) || (eventType == kOnSelfRollover))
			{
				++numEventsIgnored;
				continue;
			}

			//
			// TODO::waiting for Susan to expose an API (e.g., GetDynamicContentType() from IDynamicEventTimingSuite.
			// We need the contentType to differentiate OnPageLoad or OnStateLoad(when contentType is kMultiStateItemType.
			//

			PMString eventName = Utils<IAnimationUtils>()->GetStringFromEventTrigger (eventType, contentType);
			iEventDropDownStringData->AddString(eventName, IStringListControlData::kEnd, kTrue, kFalse);	

			if (eventType == currentTriggerType)
			{
				selectIndex = i;
				selectEventName = eventName;
			}
		}
	}

	// We have to re-set the select index since the selectIndex and selectEventName might not be in sync due to the filter out of self click/rollover
	if (iEventDropDownStringData->Length() > 0)
		selectIndex = iEventDropDownStringData->GetIndex(selectEventName);

	std::vector<UID> unassignedTargetList;
	if (iDynamicEventTimingSuite->GetUnassignedTargets(unassignedTargetList) && !unassignedTargetList.empty ())
	{
		numEvents -= numEventsIgnored;
		if (numEvents > 0)
		{
			PMString separatorString("-");
			separatorString.SetTranslatable(kFalse);
			iEventDropDownStringData->AddString(separatorString, IStringListControlData::kEnd, kTrue, kFalse);
		}

		iEventDropDownStringData->AddString("kUnassignedEntry", IStringListControlData::kEnd, kTrue, kFalse);

		if ((selectIndex == -1) && (currentTriggerType == kNoTriggerEvent))
			selectIndex = iEventDropDownStringData->Length() - 1;
	}

	InterfacePtr<IDropDownListController> iEventDDListController(eventDropDown, UseDefaultIID());

	if (iEventDropDownStringData->Length() > 0)
	{
		if (selectIndex >= 0)
			iEventDDListController->Select(selectIndex, kTrue, kFalse);
		else
			iEventDDListController->Select(IDropDownListController::kBeginning, kTrue, kFalse);
	}
	else
	{
		iEventDDListController->Select(IDropDownListController::kNoSelection, kTrue, kFalse);
	}
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::UpdateDelayWidget()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::UpdateDelayWidget()
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());

	IControlView* iTreeView = iPanelControlData->FindWidget(kTimingPanelTreeWidgetID);
	InterfacePtr<ITreeViewController> iTreeViewController(iTreeView, UseDefaultIID());
	NodeIDList selectedNodes;
	iTreeViewController->GetSelectedItems(selectedNodes);

	InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite (static_cast<IDynamicEventTimingSuite*>(this->QueryAbstractSelection (IID_IDYNAMICEVENTTIMINGSUITE))); 
	EventTriggerType eventType = ddui_utils::GetCurrentEventTypeInTimingPanel();

	IControlView* iDelayGroupWidgetView = iPanelControlData->FindWidget(kTimingPanelDelayGroupWidgetID);

	IControlView* iDelayWidgetView = iPanelControlData->FindWidget(kTimingDelayILEWidgetID);

	if ((eventType == kNoTriggerEvent) || (selectedNodes.size() <= 0) || (fCurrentSelection == nil) || (iDynamicEventTimingSuite == nil))
	{		
		InterfacePtr<ITextControlData>	iDelayInlineControlData(iDelayWidgetView, UseDefaultIID ()); 
		iDelayInlineControlData->SetString(PMString(""), kTrue, kFalse);
		PMString labelString = PMString("kTimingPanelDelaySecondStaticText");
		this->UpdateLabelString(labelString, kTimingPanelDelaySecondStaticWidgetID);

		iDelayGroupWidgetView->Disable();
	}
	else
	{
		ASSERT(selectedNodes.size() > 0);

		iDelayGroupWidgetView->Enable();

		bool mixedValue = false;
		PMReal delay = ddui_utils::GetSelectedTimingItemsDelay (iDynamicEventTimingSuite, eventType, selectedNodes, mixedValue);

		InterfacePtr<ITextValue> iDelayData(nil); 
		InterfacePtr<IPanelControlData> iInlinePanelData(iDelayWidgetView, UseDefaultIID());
		if (iInlinePanelData)
		{
			IControlView * iInlineStaticView = iInlinePanelData->FindWidget(kInLineEditStaticTextWidgetID); 
			iDelayData = InterfacePtr<ITextValue> (iInlineStaticView, UseDefaultIID()); 
		}
		else
		{
			iDelayData = InterfacePtr<ITextValue> (iDelayWidgetView, UseDefaultIID()); 
		}

		if (!mixedValue)
		{
			iDelayData->SetTextFromValue(delay, kTrue, kFalse);
		}
		else
		{
			InterfacePtr<ITextControlData> iTextData (iDelayData, UseDefaultIID ());
			if (iTextData)
				iTextData->SetString (PMString (), kTrue, kFalse);
		}

		PMString labelString = (delay > 1) ? PMString("kTimingPanelDelaySecondsStaticText") : PMString("kTimingPanelDelaySecondStaticText");
		this->UpdateLabelString(labelString, kTimingPanelDelaySecondStaticWidgetID);
	}
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::UpdateNumPlaysLoopWidgets()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::UpdateNumPlaysLoopWidgets()
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());

	IControlView* iTreeView = iPanelControlData->FindWidget(kTimingPanelTreeWidgetID);
	InterfacePtr<ITreeViewController> iTreeViewController(iTreeView, UseDefaultIID());
	NodeIDList selectedNodes;
	iTreeViewController->GetSelectedItems(selectedNodes);

	InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite (static_cast<IDynamicEventTimingSuite*>(this->QueryAbstractSelection (IID_IDYNAMICEVENTTIMINGSUITE))); 
	EventTriggerType eventType = ddui_utils::GetCurrentEventTypeInTimingPanel();

	IControlView* iNumPlaysGroupWidgetView = iPanelControlData->FindWidget(kTimingPanelNumPlaysGroupWidgetID);

	IControlView* iLinkedItemStaticTextView = iPanelControlData->FindWidget(kTimingPanelLinkedItemStaticWidgetID);

	IControlView* iNumPlaysEditBoxView = iPanelControlData->FindWidget(kTimingPanelPlayLinkedItemEditBoxWidgetID);
	InterfacePtr<ITextControlData>	iNumPlaysControlData(iNumPlaysEditBoxView, UseDefaultIID ()); 

	IControlView* iLoopCheckBoxView = iPanelControlData->FindWidget(kTimingPanelLoopCheckBoxWidgetID);
	InterfacePtr<ITriStateControlData> iLoopControlData(iLoopCheckBoxView, UseDefaultIID());


	if ((eventType == kNoTriggerEvent) || (selectedNodes.size() <= 0) || (fCurrentSelection == nil) || (iDynamicEventTimingSuite == nil))
	{		
		iLinkedItemStaticTextView->Disable();

		iNumPlaysControlData->SetString(PMString(""), kTrue, kFalse);
		PMString labelString = PMString("kTimingPanelPlayLinkedItemTimeStaticText");
		this->UpdateLabelString(labelString, kTimingPanelPlayLinkedItemTimeStaticWidgetID);

		iLoopControlData->Deselect(kTrue, kFalse);
		iNumPlaysGroupWidgetView->Disable();
		iLoopCheckBoxView->Disable();
	}
	else 
	{		
		//
		// Update num plays edit box and label.
		//
		uint32 group = 0;
		uint32 numPlays = ddui_utils::GetSelectedTimingItemsGroupPlays (iDynamicEventTimingSuite, eventType, selectedNodes, group);
		if (group == IDynamicEventTimingMgr::kInvalidTimingPosition)
		{
			iLinkedItemStaticTextView->Disable();

			iNumPlaysControlData->SetString(PMString(""), kTrue, kFalse);
			PMString labelString = PMString("kTimingPanelPlayLinkedItemTimeStaticText");
			this->UpdateLabelString(labelString, kTimingPanelPlayLinkedItemTimeStaticWidgetID);

			iLoopControlData->Deselect(kTrue, kFalse);

			iNumPlaysGroupWidgetView->Disable();
			iLoopCheckBoxView->Disable();
			return;
		}

		iLinkedItemStaticTextView->Enable();

		PMString numPlaysString(kNullString);
		numPlaysString.AppendNumber(numPlays);
		iNumPlaysControlData->SetString(numPlaysString, kTrue, kFalse);

		PMString labelString = (numPlays > 1) ? PMString("kTimingPanelPlayLinkedItemTimesStaticText") : PMString("kTimingPanelPlayLinkedItemTimeStaticText");
		this->UpdateLabelString(labelString, kTimingPanelPlayLinkedItemTimeStaticWidgetID);

		//
		// Update loop checkbox
		//
		iLoopCheckBoxView->Enable();
		bool bLoop = iDynamicEventTimingSuite->GetNthGroupPlaysLoopInEvent(eventType, group);
		if (bLoop)
		{
			iLoopControlData->Select(kTrue, kFalse);
			iNumPlaysGroupWidgetView->Disable();
		}
		else
		{
			iLoopControlData->Deselect(kTrue, kFalse);
			iNumPlaysGroupWidgetView->Enable();
		}
	}
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::UpdateLabelString()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::UpdateLabelString(PMString const &labelString, WidgetID const &widgetID)
{
	InterfacePtr<IPanelControlData const> iPanelControlData(this, UseDefaultIID());
	IControlView* iLabelView = iPanelControlData->FindWidget(widgetID);
	InterfacePtr<ITextControlData> iLabelData(iLabelView, UseDefaultIID());
	iLabelData->SetString(labelString, kTrue, kFalse);
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::UpdateGroupUngroupButtons()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::UpdateGroupUngroupButtons()
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());

	IControlView* iGroupButtonView = iPanelControlData->FindWidget(kTimingPanelGroupButtonWidgetID);
	bool bCanGroup = CanSelectedItemsBeGrouped();
	iGroupButtonView->Enable(bCanGroup);

	IControlView* iUngroupButtonView = iPanelControlData->FindWidget(kTimingPanelUngroupButtonWidgetID);
	bool bCanUngroup = CanSelectedItemsBeUngrouped();
	iUngroupButtonView->Enable(bCanUngroup);
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::UpdateTreeView()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::UpdateTreeView()
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	IControlView* iTreeView = iPanelControlData->FindWidget(kTimingPanelTreeWidgetID);

	//	Need to deselect all before rebuilding.
	InterfacePtr<ITreeViewMgr> iTreeViewMgr(iTreeView, UseDefaultIID()); 
	InterfacePtr<ITreeViewController> iTVController (iTreeView, UseDefaultIID()); 
	iTVController->DeselectAll ();

	iTreeViewMgr->ChangeRoot();
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::GroupUngroupTargets()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::GroupUngroupTargets(WidgetID const &widgetID)
{
	IDynamicEventTimingMgr::DynamicTargetList selectedItems;
	IDataBase* db = fCurrentSelection->GetDataBase();
	ddui_utils::GetSelectedTimingItems(db, selectedItems);

	if (widgetID == kTimingPanelUngroupButtonWidgetID)
	{
		ddui_utils::UngroupTimingItems(selectedItems);
	}
	else
	{
		ddui_utils::GroupTimingItems(selectedItems);
	}

	// Deselect everything after group/ungroup. See bug #2427087.
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	IControlView* iTreeView = iPanelControlData->FindWidget(kTimingPanelTreeWidgetID);
	InterfacePtr<ITreeViewController> iTreeViewController(iTreeView, UseDefaultIID());
	iTreeViewController->DeselectAll(kFalse/*don't notify*/, kTrue/*invalidate*/);
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::SetTargetDelay()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::SetTargetDelay(PMReal const &delay)
{
	IDynamicEventTimingMgr::DynamicTargetList selectedItems;	
	IDataBase* db = fCurrentSelection->GetDataBase();
	ddui_utils::GetSelectedTimingItems(db, selectedItems);

	EventTriggerType trigger = ddui_utils::GetCurrentEventTypeInTimingPanel();

	InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite (static_cast<IDynamicEventTimingSuite*>(this->QueryAbstractSelection (IID_IDYNAMICEVENTTIMINGSUITE))); 

	CmdUtils::SequencePtr seq;
	seq->SetName("kUpdateDynamicTargetDataCmd");
	for (int32 i = 0; i < selectedItems.size(); ++i)
	{
		uint32 position = 0;
		int32 whichGroup = iDynamicEventTimingSuite->FindTargetInEvent(trigger, selectedItems[i], position);
		iDynamicEventTimingSuite->SetTargetDelayInEvent(trigger, selectedItems[i], whichGroup, delay);
	}

	PMString labelString = (delay > 1) ? PMString("kTimingPanelDelaySecondsStaticText") : PMString("kTimingPanelDelaySecondStaticText");
	this->UpdateLabelString(labelString, kTimingPanelDelaySecondStaticWidgetID);
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::SetTargetDelay()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::SetTargetNumPlays(int32 const &numPlays)
{
	IDynamicEventTimingMgr::DynamicTargetList selectedItems;	
	IDataBase* db = fCurrentSelection->GetDataBase();
	ddui_utils::GetSelectedTimingItems(db, selectedItems);
	ASSERT(selectedItems.size() > 0);

	InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite (static_cast<IDynamicEventTimingSuite*>(this->QueryAbstractSelection (IID_IDYNAMICEVENTTIMINGSUITE))); 
	
	EventTriggerType trigger = ddui_utils::GetCurrentEventTypeInTimingPanel();
	uint32 position = 0;
	int32 whichGroup = iDynamicEventTimingSuite->FindTargetInEvent(trigger, selectedItems[0], position);
	iDynamicEventTimingSuite->SetNthGroupNumPlaysInEvent(trigger, whichGroup, numPlays);

	PMString labelString = (numPlays > 1) ? PMString("kTimingPanelPlayLinkedItemTimesStaticText") : PMString("kTimingPanelPlayLinkedItemTimeStaticText");
	this->UpdateLabelString(labelString, kTimingPanelPlayLinkedItemTimeStaticWidgetID);
}

void TimingPanelObserver::SetTargetLoop(bool const bOn)
{
	IDynamicEventTimingMgr::DynamicTargetList selectedItems;	
	IDataBase* db = fCurrentSelection->GetDataBase();
	ddui_utils::GetSelectedTimingItems(db, selectedItems);
	ASSERT(selectedItems.size() > 0);

	InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite (static_cast<IDynamicEventTimingSuite*>(this->QueryAbstractSelection (IID_IDYNAMICEVENTTIMINGSUITE))); 
	
	EventTriggerType trigger = ddui_utils::GetCurrentEventTypeInTimingPanel();
	uint32 position = 0;
	int32 whichGroup = iDynamicEventTimingSuite->FindTargetInEvent(trigger, selectedItems[0], position);
	iDynamicEventTimingSuite->SetNthGroupPlaysLoopInEvent(trigger, whichGroup, bOn);

	// If loop is on, disable num play widgets; otherwise, enable it.
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	IControlView* iNumPlaysGroupWidgetView = iPanelControlData->FindWidget(kTimingPanelNumPlaysGroupWidgetID);
	if (bOn)
		iNumPlaysGroupWidgetView->Disable();
	else
		iNumPlaysGroupWidgetView->Enable();
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::CanSelectedItemsBeGrouped()
//----------------------------------------------------------------------------------------
bool TimingPanelObserver::CanSelectedItemsBeGrouped()
{		
	InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite (static_cast<IDynamicEventTimingSuite*>(this->QueryAbstractSelection (IID_IDYNAMICEVENTTIMINGSUITE))); 

	if (iDynamicEventTimingSuite)
	{
		IDataBase* db = fCurrentSelection->GetDataBase();
		IDynamicEventTimingMgr::DynamicTargetList selectedItems;
		ddui_utils::GetSelectedTimingItems(db, selectedItems);

		if (selectedItems.size() > 1)
		{
			//
			// Only when there are selected items in different group, 
			// we will allow to group; otherwise, we won't allow to group.
			//
			EventTriggerType trigger = ddui_utils::GetCurrentEventTypeInTimingPanel();

			uint32 position = 0;
			int32 firstGroup = iDynamicEventTimingSuite->FindTargetInEvent(trigger, selectedItems[0], position);

			for (IDynamicEventTimingMgr::DynamicTargetList::const_iterator iter = selectedItems.begin(); iter != selectedItems.end(); ++iter)
			{
				int32 group = iDynamicEventTimingSuite->FindTargetInEvent(trigger, *iter, position);
				if ((group >= 0) && (group != firstGroup))
					return true;
			}
		}
	}

	return false;
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::CanSelectedItemsBeUngrouped()
//----------------------------------------------------------------------------------------
bool TimingPanelObserver::CanSelectedItemsBeUngrouped()
{
	IDynamicEventTimingMgr::DynamicTargetList selectedItems;		
	IDataBase* db = fCurrentSelection->GetDataBase();
	ddui_utils::GetSelectedTimingItems(db, selectedItems);

	if (selectedItems.size() > 0)
	{
		//
		// As long as there is one item in a group, 
		// we will allow to ungroup; otherwise, we won't allow to ungroup.
		//
		EventTriggerType trigger = ddui_utils::GetCurrentEventTypeInTimingPanel();
		InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite (static_cast<IDynamicEventTimingSuite*>(this->QueryAbstractSelection (IID_IDYNAMICEVENTTIMINGSUITE))); 

		for (IDynamicEventTimingMgr::DynamicTargetList::const_iterator iter = selectedItems.begin(); iter != selectedItems.end(); ++iter)
		{
			uint32 position = 0;
			int32 group = iDynamicEventTimingSuite->FindTargetInEvent(trigger, *iter, position);

			if (group >= 0)
			{
				IDynamicEventTimingMgr::DynamicTargetList itemList;
				if (iDynamicEventTimingSuite->GetNthGroupInEvent(trigger, group, itemList) && (itemList.size() > 1))
					return true;
			}
			
		}
	}

	return false;
}

//----------------------------------------------------------------------------------------
// TimingPanelObserver::UpdateChangedTimingItems()
//----------------------------------------------------------------------------------------
void TimingPanelObserver::UpdateChangedTimingItems(K2Vector<UID> const &changedItems)
{
	InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite (static_cast<IDynamicEventTimingSuite*>(this->QueryAbstractSelection (IID_IDYNAMICEVENTTIMINGSUITE))); 

	if (iDynamicEventTimingSuite)
	{
		InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
		IControlView* iTreeView = iPanelControlData->FindWidget(kTimingPanelTreeWidgetID);
		InterfacePtr<ITreeViewMgr> iTreeViewMgr(iTreeView, UseDefaultIID());

		InterfacePtr<ITreeViewHierarchyAdapter> iTreeViewHierarchyAdapter(iTreeView, UseDefaultIID()); 
		NodeID rootNode = iTreeViewHierarchyAdapter->GetRootNode(); 

		IDataBase* db = fCurrentSelection->GetDataBase();
		EventTriggerType eventType = ddui_utils::GetCurrentEventTypeInTimingPanel();
		
		for(K2Vector<UID>::const_iterator iter = changedItems.begin(); iter != changedItems.end(); ++iter)
		{				
			if ((*iter != kInvalidUID) && db->IsValidUID(*iter))
			{
				int32 numChildren = iTreeViewHierarchyAdapter->GetNumChildren(rootNode);
				for (int32 i = 0; i < numChildren; ++i)
				{
					NodeID nthNode = iTreeViewHierarchyAdapter->GetNthChild(rootNode, i);
					TreeNodePtr<TimingPanelTreeNodeID> itemNode(nthNode); 

					IDynamicEventTimingMgr::DynamicTargetPtr dynamicTarget = Utils<Facade::IDynamicEventTimingFacade>()->CreateDynamicTarget 
														(UIDRef(db,*iter), itemNode->GetRole(), itemNode->GetAction());

					uint32 position = 0;
					int32 group = iDynamicEventTimingSuite->FindTargetInEvent(eventType, dynamicTarget, position);
					if (group >= 0)
						iTreeViewMgr->NodeChanged(nthNode);
					else if ((eventType == kNoTriggerEvent) && (*iter == itemNode->GetUID())) // update node if it's unassigned and UID matches
						iTreeViewMgr->NodeChanged(nthNode);
					else
					{
						//
						// Check the dhild of the changed item so that the content (video/audio etc.) will be changed too. 
						//
						InterfacePtr<IHierarchy> iItemHierarchy(db, *iter, UseDefaultIID());
						if (iItemHierarchy)
						{
							for (int32 j = 0; j < iItemHierarchy->GetChildCount(); ++j)
							{
								IDynamicEventTimingMgr::DynamicTargetPtr childDynamicTarget = Utils<Facade::IDynamicEventTimingFacade>()->CreateDynamicTarget 
														(UIDRef(db, iItemHierarchy->GetChildUID(j)), itemNode->GetRole(), itemNode->GetAction());
								group = iDynamicEventTimingSuite->FindTargetInEvent(eventType, childDynamicTarget, position);
								if (group >= 0)
									iTreeViewMgr->NodeChanged(nthNode);
								else if ((eventType == kNoTriggerEvent) && (itemNode->GetUID() == iItemHierarchy->GetChildUID(j)))	// update node if it's unassigned and UID matches
									iTreeViewMgr->NodeChanged(nthNode);
							}
						}
					}
				}		
			}
		}
	}
}

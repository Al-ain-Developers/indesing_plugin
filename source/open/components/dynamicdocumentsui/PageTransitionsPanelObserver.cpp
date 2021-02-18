//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/PageTransitionsPanelObserver.cpp $
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

// ----- Interfaces -----

#include "IActiveContext.h"
#include "IApplication.h"
#include "IControlView.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IHierarchy.h"
#include "ILayoutControlData.h"
#include "IMasterSpread.h"
#include "IPageTransition.h"
#include "IPanelControlData.h"
#include "IPanelMgr.h"
#include "ISelectionManager.h"
#include "ISpread.h"
#include "ISpreadList.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "ITextValue.h"
#include "IWidgetParent.h"
#include "IWindow.h"
#include "IWorkspace.h"
// ----- Includes -----

#include "CObserver.h"
#include "ListLazyNotificationData.h"
#include "UIDList.h"

// ----- Utility files -----

#include "DynamicDocumentsUIUtils.h"
#include "ILayoutUIUtils.h"
#include "IPageTransitionFacade.h"
#include "FileUtils.h"
#include "Utils.h"
#include "DVGIFPlayerView.h"

// ----- ID.h files -----

#include "DynamicDocumentsID.h"
#include "DynamicDocumentsUIID.h"
#include "PagesPanelID.h"

//========================================================================================
// class PageTransitionsPanelObserver
//========================================================================================
class PageTransitionsPanelObserver : public CObserver
{
		typedef CObserver inherited;

		IControlView* fCurrentLayoutView;
		ClassID		  fPreviousSelectedTransitionClass;
		bool		  fMixed;
		bool		  fMasterSpread;
		IDFile		  fPreviousGifFile;

		void AttachDetachPaletteMgr(bool16 const &bAttach);
		void AttachDetachDropDownWidget(WidgetID const &widgetID, bool16 const &bAttach);
		void AttachDetachButtonWidget(WidgetID const &widgetID, bool16 const &bAttach);
		void AttachToLayoutView();
		void DetachFromLayoutView();
		void AttachTo(IControlView *iLayoutView);
		void DetachFrom(IControlView *iLayoutView);
		void UpdateWidgets();
		void UpdateApplyToAllButton();
		void UpdateTransitionWidget(ClassID const &transitionClassID, bool const &bMixed, bool const &bMasterSpread);
		void UpdateDirectionWidget(ClassID const &transitionClassID, uint32 const &direction, bool const &bMixed);
		void UpdateSpeedWidget(ClassID const &transitionClassID, uint32 const &speed, bool const &bMixed);
		void UpdatePreviewProxy(ClassID const &transitionClassID, uint32 const &direction, uint32 const &speed);

		void SetPageTransitionData();
		uint32 GetDirectionFromWidget(ClassID const &transitionClassID);
		uint32 GetSpeedFromWidget();
		ClassID GetTransitionFromWidget();

	public:
		PageTransitionsPanelObserver(IPMUnknown *boss);
		virtual ~PageTransitionsPanelObserver();

	protected:
		virtual void	AutoAttach();
		virtual void	AutoDetach();

		virtual void	Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
		virtual void	LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data);	
		
};

CREATE_PMINTERFACE(PageTransitionsPanelObserver, kPageTransitionsPanelObserverImpl)

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::PageTransitionsPanelObserver
//----------------------------------------------------------------------------------------

PageTransitionsPanelObserver::PageTransitionsPanelObserver(IPMUnknown *boss) :
	CObserver(boss), 
	fCurrentLayoutView(nil),
	fPreviousSelectedTransitionClass(kInvalidClass),
	fMixed(false),
	fMasterSpread(false),
	fPreviousGifFile()
{
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::~PageTransitionsPanelObserver
//----------------------------------------------------------------------------------------

PageTransitionsPanelObserver::~PageTransitionsPanelObserver()
{
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::AutoAttach()
//----------------------------------------------------------------------------------------
void PageTransitionsPanelObserver::AutoAttach()
{
	//
	// Attach to palette manager (mainly for close pages panel message)
	//
	this->AttachDetachPaletteMgr(kTrue/*attach*/);

	//
	// Attach to all the widgets on this panel
	//
	this->AttachDetachDropDownWidget(kPageTransitionDropDownWidgetID, kTrue/*attach*/);
	this->AttachDetachDropDownWidget(kPageDirectionDropDownWidgetID, kTrue/*attach*/);
	this->AttachDetachDropDownWidget(kPageSpeedDropDownWidgetID, kTrue/*attach*/);
	this->AttachDetachButtonWidget(kApplyToAllSpreadsButtonWidgetID, kTrue/*attach*/);
	
	//
	// Attach to the active layout 
	//
	this->AttachToLayoutView();

	//
	// Initialize all the widgets on this panel
	//
	this->UpdateWidgets();
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::AutoDetach()
//----------------------------------------------------------------------------------------
void PageTransitionsPanelObserver::AutoDetach()
{
	//
	// Detach of all the widgets on this panel
	//
	this->AttachDetachDropDownWidget(kPageTransitionDropDownWidgetID, kFalse/*detach*/);
	this->AttachDetachDropDownWidget(kPageDirectionDropDownWidgetID, kFalse/*detach*/);
	this->AttachDetachDropDownWidget(kPageSpeedDropDownWidgetID, kFalse/*detach*/);
	this->AttachDetachButtonWidget(kApplyToAllSpreadsButtonWidgetID, kFalse/*detach*/);

	//
	// Detach from current layout
	//
	this->DetachFromLayoutView();

	//
	// Detach to palette manager (mainly for close pages panel message)
	//
	this->AttachDetachPaletteMgr(kFalse/*detach*/);
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::AttachDetachPaletteMgr()
//----------------------------------------------------------------------------------------
void PageTransitionsPanelObserver::AttachDetachPaletteMgr(bool16 const &bAttach)
{
	InterfacePtr<const IApplication> iApp(GetExecutionContextSession()->QueryApplication());
	if (iApp) 
	{
		InterfacePtr<const IPanelMgr> iPanelMgr( iApp->QueryPanelManager() );
		InterfacePtr<ISubject> iPanelMgrSubject(iPanelMgr, UseDefaultIID());

		if (iPanelMgrSubject) 
		{
			if (bAttach && !iPanelMgrSubject->IsAttached(this, IID_IPANELMGR, IID_IOBSERVER))
				iPanelMgrSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_IPANELMGR, IID_IOBSERVER);
			else if (!bAttach && iPanelMgrSubject->IsAttached( this, IID_IPANELMGR, IID_IOBSERVER))
				iPanelMgrSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_IPANELMGR, IID_IOBSERVER);
		}
	}
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::AttachDetachDropDownWidget()
//----------------------------------------------------------------------------------------
void PageTransitionsPanelObserver::AttachDetachDropDownWidget(WidgetID const &widgetID, bool16 const &bAttach)
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	
	IControlView* dropDownWidget = iPanelControlData->FindWidget(widgetID);
	InterfacePtr<ISubject> iDropDownWidgetSubject(dropDownWidget, IID_ISUBJECT);
	if (iDropDownWidgetSubject)
	{	
		if (bAttach && !iDropDownWidgetSubject->IsAttached( this, IID_ISTRINGLISTCONTROLDATA, IID_IOBSERVER))
			iDropDownWidgetSubject->AttachObserver( this, IID_ISTRINGLISTCONTROLDATA, IID_IOBSERVER);
		else if (!bAttach && iDropDownWidgetSubject->IsAttached( this, IID_ISTRINGLISTCONTROLDATA, IID_IOBSERVER))
			iDropDownWidgetSubject->DetachObserver( this, IID_ISTRINGLISTCONTROLDATA, IID_IOBSERVER);
	}
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::AttachDetachButtonWidget()
//----------------------------------------------------------------------------------------
void PageTransitionsPanelObserver::AttachDetachButtonWidget(WidgetID const &widgetID, bool16 const &bAttach)
{	
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());

	IControlView* buttonWidget = iPanelControlData->FindWidget(widgetID);
	InterfacePtr<ISubject> iButtonSubject(buttonWidget, IID_ISUBJECT);
	if (iButtonSubject)
	{
		if (bAttach && !iButtonSubject->IsAttached( this, IID_ITRISTATECONTROLDATA, IID_IOBSERVER))
			iButtonSubject->AttachObserver( this, IID_ITRISTATECONTROLDATA, IID_IOBSERVER);
		else if (!bAttach && iButtonSubject->IsAttached( this, IID_ITRISTATECONTROLDATA, IID_IOBSERVER))
			iButtonSubject->DetachObserver( this, IID_ITRISTATECONTROLDATA, IID_IOBSERVER);
	}
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::AttachToLayoutView()
//----------------------------------------------------------------------------------------
void PageTransitionsPanelObserver::AttachToLayoutView()
{
	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	if (context)
	{
		InterfacePtr<ISubject> iContextSubject(context, UseDefaultIID());
		if (iContextSubject && !iContextSubject->IsAttached(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT,IID_IOBSERVER))
			iContextSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT,IID_IOBSERVER);

		IControlView* activeView = context->GetContextView();
		InterfacePtr<ILayoutControlData> iLayoutView( activeView, UseDefaultIID());		
		if (iLayoutView && (fCurrentLayoutView != activeView))
		{
			if (fCurrentLayoutView)
				DetachFrom(fCurrentLayoutView);
			
			this->AttachTo(activeView);
		}
	}
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::AttachToLayoutView()
//----------------------------------------------------------------------------------------
void PageTransitionsPanelObserver::DetachFromLayoutView()
{
	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	if (context)
	{
		InterfacePtr<ISubject> iContextSubject(context, UseDefaultIID());		
		if (iContextSubject && iContextSubject->IsAttached(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT,IID_IOBSERVER))
			iContextSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT,IID_IOBSERVER);
	}
	
	if(fCurrentLayoutView)
		DetachFrom(fCurrentLayoutView);
	
	fCurrentLayoutView = nil;
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::AttachTo()
//----------------------------------------------------------------------------------------
void PageTransitionsPanelObserver::AttachTo(IControlView *iLayoutView)
{
	if (fCurrentLayoutView != iLayoutView)
	{
		//
		// Attach to the layout view for watching changes of active spread.
		//
		InterfacePtr<ISubject> iLayoutViewSubject(iLayoutView, UseDefaultIID());
		
		if (iLayoutViewSubject && !iLayoutViewSubject->IsAttached(ISubject::kLazyAttachment,this, IID_IACTIVESPREAD, IID_IOBSERVER))
			iLayoutViewSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_IACTIVESPREAD, IID_IOBSERVER);
		
		//
		// Update current layout view
		//
		fCurrentLayoutView = iLayoutView;

		//
		// Attach to current spread for watching the spread's page transition change.
		//
		InterfacePtr<ILayoutControlData> iLayoutControlData(fCurrentLayoutView, UseDefaultIID());
		if (iLayoutControlData)
		{
			IDocument* currentDoc = iLayoutControlData->GetDocument();
			InterfacePtr<ISpreadList> iSpreadList(currentDoc, IID_ISPREADLIST);

			// Attach to spread list and page transitions
			if (iSpreadList)
			{
				InterfacePtr<ISubject> iDocSubject(iSpreadList, IID_ISUBJECT);
				if (iDocSubject && !iDocSubject->IsAttached(ISubject::kLazyAttachment,this, IID_ISPREADLIST, IID_IOBSERVER))
					iDocSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_ISPREADLIST, IID_IOBSERVER);
				if (iDocSubject && !iDocSubject->IsAttached(ISubject::kLazyAttachment,this, IID_IPAGETRANSITIONINFO, IID_IOBSERVER))
					iDocSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_IPAGETRANSITIONINFO, IID_IOBSERVER);

				if (iDocSubject && !iDocSubject->IsAttached(ISubject::kRegularAttachment,this, IID_IUIDLISTCONTROLDATA , IID_IOBSERVER))
					iDocSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_IUIDLISTCONTROLDATA , IID_IOBSERVER);
			}
		}
	}
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::DetachFrom()
//----------------------------------------------------------------------------------------
void PageTransitionsPanelObserver::DetachFrom(IControlView *iLayoutView)
{ 	
	if (iLayoutView)
	{
		//
		// Detach from layout view.
		//
		InterfacePtr<ISubject> iLayoutViewSubject(iLayoutView, UseDefaultIID());
		
		if (iLayoutViewSubject && iLayoutViewSubject->IsAttached(ISubject::kLazyAttachment,this, IID_IACTIVESPREAD, IID_IOBSERVER))
			iLayoutViewSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_IACTIVESPREAD, IID_IOBSERVER);

		//
		// Detach from current spread for watching the spread's page transition change.
		//
		ASSERT(fCurrentLayoutView != nil);
		InterfacePtr<ILayoutControlData> iLayoutControlData(fCurrentLayoutView, UseDefaultIID());
		if (iLayoutControlData)
		{
			const UIDRef& currentSpread = iLayoutControlData->GetSpreadRef();

			InterfacePtr<ISubject> iCurrentSpreadSubject(currentSpread, UseDefaultIID());
			if (iCurrentSpreadSubject && iCurrentSpreadSubject->IsAttached(ISubject::kLazyAttachment,this, IID_IPAGETRANSITIONINFO,IID_IOBSERVER))
				iCurrentSpreadSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_IPAGETRANSITIONINFO,IID_IOBSERVER);

			IDocument* currentDoc = iLayoutControlData->GetDocument();
			InterfacePtr<ISpreadList> iSpreadList(currentDoc, IID_ISPREADLIST);

			// Detach from spread list and page transitions
			if (iSpreadList)
			{
				InterfacePtr<ISubject> iDocSubject(iSpreadList, IID_ISUBJECT);
				if (iDocSubject && iDocSubject->IsAttached(ISubject::kLazyAttachment,this, IID_ISPREADLIST, IID_IOBSERVER))
					iDocSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_ISPREADLIST, IID_IOBSERVER);
				if (iDocSubject && iDocSubject->IsAttached(ISubject::kLazyAttachment,this, IID_IPAGETRANSITIONINFO, IID_IOBSERVER))
					iDocSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_IPAGETRANSITIONINFO, IID_IOBSERVER);

				if (iDocSubject && iDocSubject->IsAttached(ISubject::kRegularAttachment,this, IID_IUIDLISTCONTROLDATA, IID_IOBSERVER))
					iDocSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_IUIDLISTCONTROLDATA, IID_IOBSERVER);
			}
		}
	}
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::Update
//----------------------------------------------------------------------------------------
void PageTransitionsPanelObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
//    InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
//    std::string path = "/Users/sachatur/Desktop/eglite.gif";
//    PMString gifPath(path.c_str());
//    IControlView*  gifView = iPanelControlData->FindWidget(kGIFPlayerWidgetID);
//    DVGIFPlayerView* view = dynamic_cast<DVGIFPlayerView*>(gifView);
//    view->SetGIFPath(gifPath);
	switch (protocol.Get())
	{
		case IID_IACTIVECONTEXT:  // change of layout view
		{
			const PMIID& id = *((const PMIID*)changedBy);
			if (id == IID_ICONTROLVIEW)	
			{
				InterfacePtr<IActiveContext> context(theSubject, UseDefaultIID());
				if (context)
				{
					//
					// Detach from current layout view and attach to active view.
					//
					IControlView *activeView = context->GetContextView();
					if (fCurrentLayoutView != activeView)
					{
						if (fCurrentLayoutView)
							this->DetachFrom(fCurrentLayoutView);  
						
						InterfacePtr<ILayoutControlData> iLayoutView( activeView, UseDefaultIID());
						if (iLayoutView)
							this->AttachTo(activeView);
						
						fCurrentLayoutView = iLayoutView ? activeView : nil;
					}
				}
				else if (fCurrentLayoutView)
				{
					this->DetachFrom(fCurrentLayoutView);
					fCurrentLayoutView = nil;
				}

				this->UpdateWidgets();
			}

			break;
		}
		
		case IID_IUIDLISTCONTROLDATA:
		{
			if (theChange == kPagesPanelSelectionChangedMessage)
			{
				this->UpdateWidgets();
			}

			break;
		}

		case IID_IPANELMGR: 
		{
            if (theChange == kAboutToClosePaletteMsg) 
            { 
                // If this is the pages panel, then we need to update the widgets to reflect the current active spread.
                const IControlView* panelView = (IControlView*)changedBy; 
                if (panelView && panelView->GetWidgetID() == kPagesPanelWidgetID) 
                { 
                   this->UpdateWidgets();
                } 
            } 
            break; 
		}

		case IID_ISTRINGLISTCONTROLDATA:	// change of transition or direction or speed
		{
			InterfacePtr<IControlView> iWidgetView(theSubject, UseDefaultIID());
			WidgetID widgetID = iWidgetView->GetWidgetID();
			ASSERT((widgetID == kPageTransitionDropDownWidgetID) || (widgetID == kPageDirectionDropDownWidgetID) || (widgetID == kPageSpeedDropDownWidgetID));

			ClassID transitionClassID = kInvalidClass;
			uint32 direction = 0;
			uint32 speed = IPageTransition::kDefaultDurationTime;

			InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());

			IControlView* transitionDropDown = iPanelControlData->FindWidget(kPageTransitionDropDownWidgetID);
			InterfacePtr<IDropDownListController> iTransitionDDListController(transitionDropDown, UseDefaultIID());
			int32 transitionSelected = iTransitionDDListController->GetSelected();

			if (transitionSelected >= 2)
			{
				transitionClassID = Utils<Facade::IPageTransitionFacade>()->GetNthPageTransitionClassID(transitionSelected-2);	// -2 is to count for the "No Transition" and separator
				InterfacePtr<IPageTransition> iPageTransition(Utils<Facade::IPageTransitionFacade>()->QueryNthPageTransition(transitionSelected-2));
				direction = iPageTransition->GetDefaultDirection();
				speed = iPageTransition->GetDefaultDuration();
			}

			if (widgetID == kPageTransitionDropDownWidgetID)
			{				
				// Update the direction and speed if transition is changed.
				this->UpdateDirectionWidget(transitionClassID, direction, false);	
				this->UpdateSpeedWidget(transitionClassID, speed, false);	
			}
			else if (widgetID == kPageDirectionDropDownWidgetID)
			{
				direction = this->GetDirectionFromWidget(transitionClassID);
			}
			else if (widgetID == kPageSpeedDropDownWidgetID)
			{
				speed = this->GetSpeedFromWidget();
			}

			this->UpdatePreviewProxy(transitionClassID, direction, speed);
			
			this->SetPageTransitionData();

			this->UpdateApplyToAllButton();

			break;
		}
		case IID_ITRISTATECONTROLDATA:	// click the apply to all spreads button
		{
			InterfacePtr<IControlView> iApplyToAllButtonView(theSubject, UseDefaultIID());
			WidgetID widgetID = iApplyToAllButtonView->GetWidgetID();
			if ((widgetID == kApplyToAllSpreadsButtonWidgetID) && (theChange.Get() == kTrueStateMessage))
			{
				InterfacePtr<ILayoutControlData> iLayoutControlData(fCurrentLayoutView, UseDefaultIID());
				if (iLayoutControlData)
				{	
					const UIDRef& currentSpread = iLayoutControlData->GetSpreadRef();
					UIDList spreadList(currentSpread.GetDataBase());

					// Get value from UI
					ClassID transitionClassID = this->GetTransitionFromWidget();
					uint32 direction = this->GetDirectionFromWidget(transitionClassID);
					uint32 speed = this->GetSpeedFromWidget();

					// Apply to all spreads in the document
					ErrorCode result = Utils<Facade::IPageTransitionFacade>()->ApplyPageTransitionToAllSpreads(spreadList, transitionClassID, direction, speed);
				}
			}

			break;
		}
		default:
			break;
	}
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::LazyUpdate
//----------------------------------------------------------------------------------------
void PageTransitionsPanelObserver::LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data)
{
	switch (protocol.Get())
	{
		case IID_IACTIVESPREAD:	// change of current selected spread
		{
			InterfacePtr<ILayoutControlData> iCurrentLayoutView(fCurrentLayoutView, UseDefaultIID());
			if (iCurrentLayoutView)
			{
				const ListLazyNotificationData<int32>*  listCookie = static_cast<const ListLazyNotificationData<int32>* > (data);
				if (listCookie)
				{
					K2Vector<int32> itemsChanged;
					listCookie->BreakoutChanges (nil, nil, &itemsChanged);

					//
					// As long as there are spreads changed (no matter what the change type is), we should update the widgets
					//
					if (itemsChanged.size() > 0)
					{
						this->UpdateWidgets();
					}
				}
			}

			break;
		}
		case IID_ISPREADLIST:			// add/delete page/spread
		case IID_IPAGETRANSITIONINFO:	// change of spread's page transitions, this could be optimized to look through cookies for current spread contained in changedItems
		{
			const ListLazyNotificationData<UID> *listData = static_cast<const ListLazyNotificationData<UID> *>(data);
			if (!listData)
				this->UpdateWidgets();
			else
			{
				K2Vector<UID> addedItems;
				K2Vector<UID> deletedItems;
				K2Vector<UID> changedItems;
				listData->BreakoutChanges(&addedItems, &deletedItems, &changedItems);
				
				// For deletes and changes, just mark whole panel for update.
				if (deletedItems.size() || changedItems.size() || addedItems.size())
				{
					this->UpdateWidgets();
				}
			}

			break;
		}
		default:
		{
			ASSERT("Unknown protocols!");
			break;
		}
	}
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::SetPageTransitionData
//----------------------------------------------------------------------------------------
void PageTransitionsPanelObserver::SetPageTransitionData()
{
	InterfacePtr<ILayoutControlData> iCurrentLayoutView(fCurrentLayoutView, UseDefaultIID());
	if (!iCurrentLayoutView)
		return;

	const UIDRef& currentSpread = iCurrentLayoutView->GetSpreadRef();
	IDataBase* db = currentSpread.GetDataBase();

	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());

	IControlView* transitionDropDown = iPanelControlData->FindWidget(kPageTransitionDropDownWidgetID);
	InterfacePtr<IDropDownListController> iTransitionDDListController(transitionDropDown, UseDefaultIID());
	int32 transitionSelected = iTransitionDDListController->GetSelected();
	if ((transitionSelected >= 0) && (transitionSelected != 1))	// exclude the View All and separator entries
	{
		ClassID transitionClassID = kInvalidClass;
		if (transitionSelected >= 2)
			transitionClassID = Utils<Facade::IPageTransitionFacade>()->GetNthPageTransitionClassID(transitionSelected-2);

		uint32 direction = this->GetDirectionFromWidget(transitionClassID);

		uint32 speed = this->GetSpeedFromWidget();

		UIDList selectedSpreadList(db);

		InterfacePtr<IApplication>  iApplication(GetExecutionContextSession()->QueryApplication ());
		InterfacePtr<IPanelMgr> iPanelMgr(iApplication->QueryPanelManager ());
		IControlView* pagePanelView = iPanelMgr->GetVisiblePanel(kPagesPanelWidgetID);
		if (pagePanelView != nil)
		{
			// If pages panel is visible, we get the selected spUIDList selectedSpreadList(db);
			ddui_utils::GetSelectedNonMasterSpreadsInPagesPanel(pagePanelView, selectedSpreadList);

			// If there is no selection in the pages panel, we apply to the current active spread.
			if (selectedSpreadList.size() == 0)
				selectedSpreadList = UIDList(currentSpread);
		}
		else
		{
			selectedSpreadList = UIDList(currentSpread);
		}

		// Only apply the transition when there is spread in the list.
		ASSERT(selectedSpreadList.size() > 0);
		if (selectedSpreadList.size() > 0)
		{
			Utils<Facade::IPageTransitionFacade>()->SetSpreadPageTransitionDetails(selectedSpreadList, transitionClassID, direction, speed);
		}
	}
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::UpdateWidgets
//----------------------------------------------------------------------------------------
void PageTransitionsPanelObserver::UpdateWidgets()
{	
	//
	// Update the widgets based on what spreads are selected in the pages panel if pages panel is visible or 
	// from the active spread otherwise.
	//

	ClassID transitionClassID = kInvalidClass;
	uint32 direction = IPageTransition::kNA;
	uint32 speed = IPageTransition::kPageTransitionsMediumSpeedTime; // default is to set as medium (IPageTransition::kDefaultDurationTime)

	UIDRef spread(nil, kInvalidUID);
	bool bMixed = false;
	bool bMasterSpread = false;

	InterfacePtr<ILayoutControlData> iCurrentLayoutView(fCurrentLayoutView, UseDefaultIID());
	if (iCurrentLayoutView)
	{
		IDataBase* db = iCurrentLayoutView->GetSpreadRef().GetDataBase();
		UIDList selectedSpreadList(db);

		UIDList selectedPageList(db); 
		Utils<ILayoutUIUtils>()->GetSelectedPages(selectedPageList, kFalse/*include master spread*/, kFalse/*current page only*/, kFalse/*pages only*/); 
		if (selectedPageList.size() > 0)
		{
			int32 numPages = static_cast<int32>(selectedPageList.size());
			for (int32 i = numPages-1; i >= 0; --i)
			{
				InterfacePtr<ISpread> iSpread(selectedPageList.GetRef(i), UseDefaultIID());
				if (iSpread && (selectedSpreadList.Location(selectedPageList[i]) < 0))
				{
					selectedSpreadList.push_back(selectedPageList[i]);
				}
				else if (!iSpread)
				{
					InterfacePtr<IHierarchy> iPageHierarchy(selectedPageList.GetRef(i), UseDefaultIID());
					InterfacePtr<IHierarchy> iSpreadHierarchy(iPageHierarchy->QueryRoot()); 
					InterfacePtr<ISpread> iParentSpread(iSpreadHierarchy, UseDefaultIID()); 

					if (iParentSpread && (selectedSpreadList.Location(::GetUID(iParentSpread)) < 0))
						selectedSpreadList.push_back(::GetUID(iParentSpread));
				}
			}
		}

		if (selectedSpreadList.size() > 0)
		{
			ClassID resultTransitionClass = kInvalidClass;
			if (Utils<Facade::IPageTransitionFacade>()->AllSpreadsHaveSamePageTransition(selectedSpreadList, resultTransitionClass))
				spread = selectedSpreadList.GetRef(0);
			else
				bMixed = true;
		}
		else
		{	// If nothing selected in the panel, we use current spread.
			spread = iCurrentLayoutView->GetSpreadRef();
		}
	
		if (spread != UIDRef(nil, kInvalidUID))
		{
			InterfacePtr<IMasterSpread> iMasterSpread(spread, UseDefaultIID());
			if (iMasterSpread)
			{
				bMasterSpread = true;
			}
			else
			{
				uint32 duration = IPageTransition::kDefaultDurationTime;	// duration is measured by ticks
				ErrorCode result = Utils<Facade::IPageTransitionFacade>()->GetSpreadPageTransitionDetails(spread, &transitionClassID, &direction, &duration);

				// We translate ticks into enum
				if (duration <= IPageTransition::kPageTransitionsFastSpeedTime)
					speed = IPageTransition::kPageTransitionsFastSpeedTime;
				else if (duration > IPageTransition::kPageTransitionsMediumSpeedTime)
					speed = IPageTransition::kPageTransitionsSlowSpeedTime;
				else
					speed = IPageTransition::kPageTransitionsMediumSpeedTime;
			}
		}
	}

	UpdateTransitionWidget(transitionClassID, bMixed, bMasterSpread);
	UpdateDirectionWidget(transitionClassID, direction, bMixed);
	UpdateSpeedWidget(transitionClassID, speed, bMixed);
	UpdatePreviewProxy(transitionClassID, direction, speed);

	UpdateApplyToAllButton();
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::UpdateApplyToAllButton
//----------------------------------------------------------------------------------------
void PageTransitionsPanelObserver::UpdateApplyToAllButton()
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());

	IControlView* applyToAllButton = iPanelControlData->FindWidget(kApplyToAllSpreadsButtonWidgetID);

	InterfacePtr<ILayoutControlData> iCurrentLayoutView(fCurrentLayoutView, UseDefaultIID());
	if (iCurrentLayoutView)
	{
		const UIDRef& currentSpread = iCurrentLayoutView->GetSpreadRef();
		IDataBase* db = currentSpread.GetDataBase();
		UIDList spreadList(db);

		ClassID resultTransitionClass = kInvalidClass;
		if (Utils<Facade::IPageTransitionFacade>()->AllSpreadsHaveSamePageTransition(spreadList, resultTransitionClass))
			applyToAllButton->Disable();
		else
			applyToAllButton->Enable();
	}
	else
	{
		applyToAllButton->Disable();
	}
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::UpdateTransitionWidget
//----------------------------------------------------------------------------------------
void PageTransitionsPanelObserver::UpdateTransitionWidget(ClassID const &transitionClassID, bool const &bMixed, bool const &bMasterSpread)
{	
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	IControlView* transitionDropDown = iPanelControlData->FindWidget(kPageTransitionDropDownWidgetID);
	InterfacePtr<IStringListControlData> iTransitionStringData(transitionDropDown, UseDefaultIID());
	iTransitionStringData->Clear(kTrue, kFalse);

	uint32 nTransitions = Utils<Facade::IPageTransitionFacade>()->GetPageTransitionCount();

	if (iTransitionStringData->Length() == 0)
	{
		iTransitionStringData->AddString("kPTNoTransition", IStringListControlData::kEnd, kTrue, kFalse);

		PMString separatorString("-");
        separatorString.SetTranslatable(kFalse);
		iTransitionStringData->AddString(separatorString, IStringListControlData::kEnd, kTrue, kFalse);

		for (uint32 i = 0; i < nTransitions; ++i)
		{
			PMString nTransitionName = Utils<Facade::IPageTransitionFacade>()->GetNthPageTransitionName(i);

			iTransitionStringData->AddString(nTransitionName, IStringListControlData::kEnd, kTrue, kFalse);
		}
	}

	ASSERT(iTransitionStringData->Length() == nTransitions+2);

	int32 transitionIndex = 0;
	if (transitionClassID != kInvalidClass)
	{
		transitionIndex = Utils<Facade::IPageTransitionFacade>()->FindPageTransitionIndex(transitionClassID) + 2;	// need to count for the first entry (No Transition) and separator entry
		ASSERT(transitionIndex >= 2);	
	}

	InterfacePtr<IDropDownListController> iTransitionDDListController(transitionDropDown, UseDefaultIID());

	if (bMixed)
		iTransitionDDListController->Select(IDropDownListController::kNoSelection, kTrue, kFalse);
	else
		iTransitionDDListController->Select(transitionIndex, kTrue, kFalse);

	// If there is no layout view, we disable the transition widgets
	transitionDropDown->Enable((fCurrentLayoutView != nil) && !bMasterSpread);

	// Cache the previous transition information so that when add page transition dialog is dismissed, 
	// we can revert back to previous state.
	fPreviousSelectedTransitionClass = transitionClassID;
	fMixed = bMixed;
	fMasterSpread = bMasterSpread;
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::UpdateSpeedWidget
//----------------------------------------------------------------------------------------
void PageTransitionsPanelObserver::UpdateSpeedWidget(ClassID const &transitionClassID, uint32 const &speed, bool const &bMixed)
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	IControlView* speedDropDown = iPanelControlData->FindWidget(kPageSpeedDropDownWidgetID);
	InterfacePtr<IStringListControlData> iSpeedStringData(speedDropDown, UseDefaultIID());
	iSpeedStringData->Clear(kTrue, kFalse);

	if ((transitionClassID == kInvalidClass) || (transitionClassID == kPageTurnPageTransitionBoss))
	{
		speedDropDown->Disable();
		return;
	}

	speedDropDown->Enable();

	if (iSpeedStringData->Length() == 0)
	{
		iSpeedStringData->AddString("kPTSlow", IStringListControlData::kEnd, kTrue, kFalse);
		iSpeedStringData->AddString("kPTMedium", IStringListControlData::kEnd, kTrue, kFalse);
		iSpeedStringData->AddString("kPTFast", IStringListControlData::kEnd, kTrue, kFalse);	
	}

	ASSERT(iSpeedStringData->Length() == 3);

	InterfacePtr<IDropDownListController> iDirectionDDListController(speedDropDown, UseDefaultIID());

	if (bMixed)
		iDirectionDDListController->Select(IDropDownListController::kNoSelection, kTrue, kFalse);
	else if (speed == IPageTransition::kPageTransitionsFastSpeedTime)
		iDirectionDDListController->Select(2/*fast*/, kTrue, kFalse);	
	else if (speed == IPageTransition::kPageTransitionsMediumSpeedTime)
		iDirectionDDListController->Select(1/*medium*/, kTrue, kFalse);	
	else
		iDirectionDDListController->Select(0/*slow*/, kTrue, kFalse);	
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::UpdatePreviewProxy
//----------------------------------------------------------------------------------------
void PageTransitionsPanelObserver::UpdatePreviewProxy(ClassID const &transitionClassID, uint32 const &direction, uint32 const &speed)
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
    IControlView* previewProxy = iPanelControlData->FindWidget(kGIFPlayerWidgetID);
	previewProxy->Enable(fCurrentLayoutView != nil);

	if (transitionClassID != kInvalidClass)
	{
		InterfacePtr<IPageTransition> iPageTransition(Utils<Facade::IPageTransitionFacade>()->QueryPageTransition(transitionClassID));
		IDFile GifFile;
		iPageTransition->GetSWFDynamicRepresentation(direction, speed, GifFile);
		
		if(FileUtils::DoesFileExist(GifFile))
		{
			previewProxy->ShowView();

			if (previewProxy->IsEnabled() && (GifFile != fPreviousGifFile))
			{				
				PMString localFile;
				FileUtils::IDFileToPMString(GifFile, localFile);

				DVGIFPlayerView* view = dynamic_cast<DVGIFPlayerView*>(previewProxy);
				view->SetGIFPath(localFile);
			}
		}
		else
		{
			// Temp comment out this assert since we don't have all the swfs yet. 
			ASSERT_FAIL("Unable to load GIF file");

			fPreviousGifFile = IDFile();
		}
	}
	else
	{
		previewProxy->HideView();

		fPreviousGifFile = IDFile();
	}
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::UpdateDirectionWidget
//----------------------------------------------------------------------------------------
void PageTransitionsPanelObserver::UpdateDirectionWidget(ClassID const &transitionClassID, uint32 const &direction, bool const &bMixed)
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());

	IControlView* directionDropDown = iPanelControlData->FindWidget(kPageDirectionDropDownWidgetID);
	InterfacePtr<IStringListControlData> iDirectionStringData(directionDropDown, UseDefaultIID());
	iDirectionStringData->Clear(kTrue, kFalse);

	if ((transitionClassID == kInvalidClass) || (direction == IPageTransition::kNA))
	{
		directionDropDown->Disable();
		return;
	}

	directionDropDown->Enable();

	InterfacePtr<IDropDownListController> iDirectionDDListController(directionDropDown, UseDefaultIID());

	// TODO::string of direction should get from IPageTransition instead of hard coded.

	int32 selectionIndex = -1;
	switch (transitionClassID.Get())
	{
		case kBlindsPageTransitionBoss:
		case kCombPageTransitionBoss:
			{
				iDirectionStringData->AddString("kPTHorizontal", IStringListControlData::kEnd, kTrue, kFalse);
				iDirectionStringData->AddString("kPTVertical", IStringListControlData::kEnd, kTrue, kFalse);

				ASSERT((direction == IPageTransition::kHorizontal) || (direction == IPageTransition::kVertical));
				selectionIndex = direction - IPageTransition::kHorizontal;
					
				break;
			}
		case kBoxPageTransitionBoss:
			{
				iDirectionStringData->AddString("kPTIn", IStringListControlData::kEnd, kTrue, kFalse);
				iDirectionStringData->AddString("kPTOut", IStringListControlData::kEnd, kTrue, kFalse);

				ASSERT((direction == IPageTransition::kIn) || (direction == IPageTransition::kOut));
				selectionIndex = direction - IPageTransition::kIn;

				break;
			}
		case kCoverPageTransitionBoss:
		case kPushPageTransitionBoss:
		case kUncoverPageTransitionBoss:
		case kWipePageTransitionBoss:
		case kZoomInPageTransitionBoss:
		case kZoomOutPageTransitionBoss:
			{
				iDirectionStringData->AddString("kPTDown", IStringListControlData::kEnd, kTrue, kFalse);
				iDirectionStringData->AddString("kPTLeft", IStringListControlData::kEnd, kTrue, kFalse);
				iDirectionStringData->AddString("kPTLeftDown", IStringListControlData::kEnd, kTrue, kFalse);
				iDirectionStringData->AddString("kPTLeftUp", IStringListControlData::kEnd, kTrue, kFalse);
				iDirectionStringData->AddString("kPTRight", IStringListControlData::kEnd, kTrue, kFalse);
				iDirectionStringData->AddString("kPTRightDown", IStringListControlData::kEnd, kTrue, kFalse);
				iDirectionStringData->AddString("kPTRightUp", IStringListControlData::kEnd, kTrue, kFalse);
				iDirectionStringData->AddString("kPTUp", IStringListControlData::kEnd, kTrue, kFalse);

				selectionIndex = direction - IPageTransition::kDown;
				
				break;
			}

		case kDissolvePageTransitionBoss:
		case kFadePageTransitionBoss:
		case kPageTurnPageTransitionBoss:	
			{
				selectionIndex = IDropDownListController::kNoSelection;
				break;
			}

		case kSplitPageTransitionBoss:
			{
				iDirectionStringData->AddString("kPTHorizontalIn", IStringListControlData::kEnd, kTrue, kFalse);
				iDirectionStringData->AddString("kPTHorizontalOut", IStringListControlData::kEnd, kTrue, kFalse);
				iDirectionStringData->AddString("kPTVerticalIn", IStringListControlData::kEnd, kTrue, kFalse);
				iDirectionStringData->AddString("kPTVerticalOut", IStringListControlData::kEnd, kTrue, kFalse);

				selectionIndex = direction - IPageTransition::kHorizontalIn;
					
				break;
			}
		default:
			{
				selectionIndex = IDropDownListController::kNoSelection;
				break;
			}
			
	}

	iDirectionDDListController->Select(selectionIndex, kTrue, kFalse);	
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::GetTransitionFromWidget
//----------------------------------------------------------------------------------------
ClassID PageTransitionsPanelObserver::GetTransitionFromWidget()
{
	ClassID transitionClassID = kInvalidClass;

	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());

	IControlView* transitionDropDown = iPanelControlData->FindWidget(kPageTransitionDropDownWidgetID);
	InterfacePtr<IDropDownListController> iTransitionDDListController(transitionDropDown, UseDefaultIID());
	int32 transitionSelected = iTransitionDDListController->GetSelected();

	if (transitionSelected >= 2) // 2 is to count for the "No Transition" and separator
	{
		transitionClassID = Utils<Facade::IPageTransitionFacade>()->GetNthPageTransitionClassID(transitionSelected-2);	// -2 is to count for the "No Transition" and separator
	}
	else if ((transitionSelected == 1))
	{
		ASSERT("Should not come to here!");
	}

	return transitionClassID;
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::GetDirectionFromWidget
//----------------------------------------------------------------------------------------
uint32 PageTransitionsPanelObserver::GetDirectionFromWidget(ClassID const &transitionClassID)
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());

	IControlView* directionDropDown = iPanelControlData->FindWidget(kPageDirectionDropDownWidgetID);
	InterfacePtr<IDropDownListController> iDirectionDDListController(directionDropDown, UseDefaultIID());
	int32 directionSelectedIndex = iDirectionDDListController->GetSelected();

	uint32 direction = ddui_utils::GetDirectionFromSelectionIndex(transitionClassID, directionSelectedIndex);

	return direction;
}

//----------------------------------------------------------------------------------------
// PageTransitionsPanelObserver::GetDirectionFromWidget
//----------------------------------------------------------------------------------------
uint32 PageTransitionsPanelObserver::GetSpeedFromWidget()
{
	uint32 speed = IPageTransition::kPageTransitionsMediumSpeedTime;

	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	IControlView* speedDropDown = iPanelControlData->FindWidget(kPageSpeedDropDownWidgetID);
	InterfacePtr<IDropDownListController> iSpeedDDListController(speedDropDown, UseDefaultIID());
	int32 speedSelectedIndex = iSpeedDDListController->GetSelected();

	// Translate selected index to speed enum value
	speed = ddui_utils::GetSpeedFromSelectionIndex(speedSelectedIndex);
	
	return speed;
}

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/PageTransitionsDialogController.cpp $
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
#include "IClassIDData.h"
#include "ILayoutControlData.h"
#include "DVGIFPlayerView.h"
#include "IPageTransition.h"
#include "IPanelControlData.h"
#include "IPanelMgr.h"
#include "ITextControlData.h"
#include "IWidgetIDData.h"

// ----- Includes -----

#include "CDialogController.h"
#include "UIDList.h"

// ----- Utility files -----

#include "DynamicDocumentsUIUtils.h"
#include "FileUtils.h"
#include "IPageTransitionFacade.h"
#include "IWidgetUtils.h"
#include "Utils.h"

// ----- ID.h files -----

#include "DynamicDocumentsUIID.h"

class PageTransitionsDialogController : public CDialogController
{
	public:	
							PageTransitionsDialogController(IPMUnknown *boss);
		virtual				~PageTransitionsDialogController();
		
		// ----- Dialog protocol -----

		virtual void		InitializeDialogFields( IActiveContext* dlgContext);
		virtual void		ApplyDialogFields( IActiveContext* myContext, const WidgetID& widgetId);

	private:
		void				InitializePageTransitionWidgets();
};

CREATE_PMINTERFACE(PageTransitionsDialogController, kPageTransitionsDialogControllerImpl)

//========================================================================================
// CLASS PageTransitionsDialogController
//========================================================================================

PageTransitionsDialogController::PageTransitionsDialogController(IPMUnknown *boss) :
	CDialogController(boss)
{
}

PageTransitionsDialogController::~PageTransitionsDialogController()
{

}

void PageTransitionsDialogController::InitializeDialogFields(IActiveContext* dlgContext)
{
	InitializePageTransitionWidgets();

	// Select the checkbox by default, otherwise leave in last state.
	if (!HasBeenInitialized())
		SetTriStateControlData(kPageTransitionsApplyToAllCheckBoxWidgetID, ITriStateControlData::kSelected, nil, kTrue /* invalidate */, kFalse /* notify */);
}

void PageTransitionsDialogController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& /*widgetId */) 
{
	InterfacePtr<IPanelControlData> iDialogPanelData(this,UseDefaultIID());

	ClassID transitionClassID = kInvalidClass;
	uint32 defaultDirection = IPageTransition::kNA;
	uint32 defaultSpeed = IPageTransition::kDefaultDurationTime;

	//
	// Get the transition info that is to apply
	//
	InterfacePtr<IWidgetIDData> iSelectedContainerWidgetIDData(this, IID_ISELECTEDCONTAINERWIDGETIDDATA);	
	WidgetID selectedContainerWidgetID = iSelectedContainerWidgetIDData->GetWidgetID();	// this is set in the PageTransitionsDialogObserver when radio button is clicked

	if (selectedContainerWidgetID != kInvalidWidgetID)
	{
		InterfacePtr<IControlView> iPreviewProxyGroupView(iDialogPanelData->FindWidget(kPageTransitionsDialogProxyGroup1WidgetID), UseDefaultIID());
		InterfacePtr<IClassIDData> iPageTransitionClassIDData(static_cast<IClassIDData*>(Utils<IWidgetUtils>()->QueryRelatedWidget(iPreviewProxyGroupView, selectedContainerWidgetID, IID_IASSICIATEDPAGETRANSITIONCLASSIDDATA)));		
		transitionClassID = iPageTransitionClassIDData->GetClassID();

		InterfacePtr<IPageTransition> iPageTransition(Utils<Facade::IPageTransitionFacade>()->QueryPageTransition(transitionClassID));
		defaultDirection = iPageTransition->GetDefaultDirection();
		defaultSpeed = iPageTransition->GetDefaultDuration();
	}

	ErrorCode result = kSuccess;

	//
	// Get current spread
	//
	IControlView* currentView = myContext->GetContextView();
	InterfacePtr<ILayoutControlData> iLayoutControlData(currentView, UseDefaultIID());
	if (!iLayoutControlData) return;
	const UIDRef& currentSpread = iLayoutControlData->GetSpreadRef();
	IDataBase* db = currentSpread.GetDataBase();

	InterfacePtr<ITriStateControlData> iApplyToAllCheckBox(iDialogPanelData->FindWidget(kPageTransitionsApplyToAllCheckBoxWidgetID), UseDefaultIID());
	if (iApplyToAllCheckBox->IsSelected())
	{
		//
		// If apply to all is checked, we apply the page transition to all the spreads in the document.
		//
		UIDList spreadList(db);
		result = Utils<Facade::IPageTransitionFacade>()->ApplyPageTransitionToAllSpreads(spreadList, transitionClassID, defaultDirection, defaultSpeed);
	}
	else
	{
		//
		// Otherwise, apply to the selected spreads in the pages panel.
		//
		UIDList selectedSpreadList(db);
		ddui_utils::GetSelectedNonMasterSpreadsInPagesPanel(nil, selectedSpreadList);

		// If there is no selection in the pages panel, we use the current active spread as the target spread. See bug #1842090.
		if (selectedSpreadList.size() == 0)
			selectedSpreadList = UIDList(currentSpread);

		result = Utils<Facade::IPageTransitionFacade>()->SetSpreadPageTransitionDetails(selectedSpreadList, transitionClassID, defaultDirection, defaultSpeed);
	}
	
#if 0
	// 
	// In CS4, we decided to bring up page transition panel so that user can change other parameters (speed/direction) 
	// after selecting the transition. 
	// In CS5, we decide to turn off this functionality since user does not like it. See bug #2305349.
	//

	// Bring up the page transition panel if there is transition selected.
	//
	if (transitionClassID != kInvalidClass)
	{
		InterfacePtr<IApplication>  iApplication (GetExecutionContextSession()->QueryApplication ());
		InterfacePtr<IPanelMgr> iPanelMgr (iApplication->QueryPanelManager ());
		iPanelMgr->ShowPanelByWidgetID (kPageTransitionsPanelWidgetID);
	}
#endif
}

static void FindAllPreviewProxyContainerWidgets(const IPMUnknown* widget, K2Vector<WidgetID>& containerWidgetIDList)
{
    InterfacePtr<IPanelControlData> panelData(widget, IID_IPANELCONTROLDATA);
    if (panelData)
    {
        for (int32 i = 0; i < panelData->Length(); i++)
        {
            IControlView* nthWidget = panelData->GetWidget(i);
			InterfacePtr<IClassIDData> iAssociatedPageTransitionClassID(nthWidget, IID_IASSICIATEDPAGETRANSITIONCLASSIDDATA);
			if (iAssociatedPageTransitionClassID)
			{
				WidgetID containerWidgetID = nthWidget->GetWidgetID();

				if (K2notfound(containerWidgetIDList, containerWidgetID))
					containerWidgetIDList.push_back(containerWidgetID);
			}
            
			::FindAllPreviewProxyContainerWidgets(nthWidget, containerWidgetIDList);
        }
    }
}

void PageTransitionsDialogController::InitializePageTransitionWidgets()
{
	InterfacePtr<IPanelControlData> iPanelControlData(this,UseDefaultIID());
	ASSERT(iPanelControlData);

	K2Vector<WidgetID> containerWidgetIDList;
	InterfacePtr<IControlView> iPreviewProxyGroupView(iPanelControlData->FindWidget(kPageTransitionsDialogProxyGroup1WidgetID), UseDefaultIID());
	::FindAllPreviewProxyContainerWidgets(iPreviewProxyGroupView, containerWidgetIDList);

	int32 numWidgets = containerWidgetIDList.size();

	for (int32 i = 0; i < numWidgets; ++i)
	{
		InterfacePtr<IControlView> iNthContainerView(static_cast<IControlView*>(Utils<IWidgetUtils>()->QueryRelatedWidget(iPreviewProxyGroupView, containerWidgetIDList[i], IID_ICONTROLVIEW)));

		InterfacePtr<IClassIDData> iAssociatedPageTransitionClassID(iNthContainerView, IID_IASSICIATEDPAGETRANSITIONCLASSIDDATA);
		ASSERT(iAssociatedPageTransitionClassID != nil);
		ClassID pageTransitionClassID = iAssociatedPageTransitionClassID->GetClassID();

		InterfacePtr<IPanelControlData> iNthContainerPanelData(iNthContainerView, UseDefaultIID());

        IControlView* previewProxy = iNthContainerPanelData->FindWidget(kGIFPlayerWidgetID);

		if (previewProxy)
		{
			InterfacePtr<IPageTransition> iPageTransition(Utils<Facade::IPageTransitionFacade>()->QueryPageTransition(pageTransitionClassID));
			ASSERT(iPageTransition != nil);
			if (iPageTransition)
			{
				IDFile swfFile = iPageTransition->GetSWFStaticRepresentation();
				if(FileUtils::DoesFileExist(swfFile))
				{
					PMString localFile;
					FileUtils::IDFileToPMString(swfFile, localFile);
                    
                    DVGIFPlayerView* view = dynamic_cast<DVGIFPlayerView*>(previewProxy);
                    view->SetGIFPath(localFile);
				}
			}
		}
	}
}

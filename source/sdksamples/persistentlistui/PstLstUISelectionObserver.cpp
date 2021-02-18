//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlistui/PstLstUISelectionObserver.cpp $
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

//===========================
//  Plug-in includes
//===========================

#include "VCPlugInHeaders.h"
#include "K2Vector.tpp"

// Interface includes:
#include "IDocument.h"
#include "IDropDownListController.h"
#include "ILayoutUIUtils.h"
#include "IListBoxController.h"
#include "IPanelControlData.h"
#include "ISelectionUtils.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "IWidgetParent.h"
#include "ITreeViewMgr.h"
#include "ITreeViewController.h"
#include "ITreeViewHierarchyAdapter.h"

// API includes:
#include "CAlert.h"
#include "SelectionObserver.h"
#include "K2Vector.tpp"

// Project includes:
#include "IPstLstSuite.h"
#include "PstLstUINodeID.h"
#include "PstLstUIID.h"

/** 
	Observes both the active selection and the drop-down list.

	@ingroup persistentlist
	
*/
class PstLstUISelectionObserver : public ActiveSelectionObserver
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		PstLstUISelectionObserver(IPMUnknown* boss);
		
		/**
			Destructor.
		*/
		virtual ~PstLstUISelectionObserver();


	protected:
	
		/**
			Update the panel to reflect new page items selected.  This happens when a selection changed through the
			selection tool, or page item deletion, 
		*/
		virtual void HandleSelectionChanged(const ISelectionMessage* message);

		/**
 			If the selection's data changes, we want to update the panel accordingly.  We get this notification when 
 			the user use New, Modify, Delete command to change the IPstLstData of the selection.  Because we have 
 			registered with the selection sub-system in the CreateObserverProtocolCollection() of the suite on the 
 			layout CSB that we are interested in IID_IPSTLSTDATA, the SelectionAttributeChanged() of the suite will 
 			get called when that protocol is broadcasted, and the suite will in turns relate the message to us, the 
 			client code.
			
			@param message contains the info on which suite was affected.
		*/
		virtual void HandleSelectionAttributeChanged(const ISelectionMessage* message);
				

		/**
			UpdatePanel is called when the panel's content needs to be updated.
		*/
		void UpdatePanel();
		
		/**
			Get hold of our panel data so we can access our widgets.
		*/
		IPanelControlData*	QueryPanelControlData();

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PstLstUISelectionObserver, kPstLstUISelectionObserverImpl)

/* PstLstUISelectionObserver Constructor
*/
PstLstUISelectionObserver::PstLstUISelectionObserver(IPMUnknown* boss) :
	ActiveSelectionObserver(boss)
{
}

/* PstLstUISelectionObserver Destructor
*/
PstLstUISelectionObserver::~PstLstUISelectionObserver()
{
}


/*	PstLstUISelectionObserver::UpdatePanel
*/
void PstLstUISelectionObserver::UpdatePanel()
{
	do
	{
		// Get hold of our panel data so we can access our widgets.
		InterfacePtr<IPanelControlData> iPanelControlData(QueryPanelControlData());
		if (iPanelControlData == nil)
		{
			ASSERT_FAIL("panel control data not found");
			break;
		}

		// Update tree view
		IControlView* treeWidget = iPanelControlData->FindWidget(kPstLstUITreeViewWidgetID);
		ASSERT(treeWidget);
		if(!treeWidget) {
			break;
		}

		InterfacePtr<ITreeViewMgr> iTreeViewMgr(treeWidget, UseDefaultIID());
		ASSERT(iTreeViewMgr);
		if(!iTreeViewMgr){
			break;
		}
		
		iTreeViewMgr->ChangeRoot(kFalse);

	}
	while (kFalse);
}

/*	PstLstUISelectionObserver::ChangeToMultipleSelection
*/
void PstLstUISelectionObserver::HandleSelectionChanged(const ISelectionMessage* message)
{
	UpdatePanel();
}

/*	PstLstUISelectionObserver::HandleSelectionAttributeChanged
*/
void PstLstUISelectionObserver::HandleSelectionAttributeChanged(const ISelectionMessage* iSelectionMsg)
{
	if (iSelectionMsg->WasSuiteAffected(IPstLstSuite::kDefaultIID))
	{
		UpdatePanel();
	}
}




/*	PstLstUISelectionObserver::QueryPanelControlData
*/
IPanelControlData* PstLstUISelectionObserver::QueryPanelControlData()
{
	IPanelControlData* iPanel = nil;
	do
	{
		InterfacePtr<IWidgetParent> iWidgetParent(this, UseDefaultIID());
		if (iWidgetParent == nil)
		{
			ASSERT_FAIL("iWidgetParent invalid");
			break;
		}

		InterfacePtr<IPanelControlData> iPanelControlData(iWidgetParent->GetParent(), UseDefaultIID());
		if (iPanelControlData == nil)
		{
			ASSERT_FAIL("iPanelControlData invalid");
			break;
		}

		iPanelControlData->AddRef();
		iPanel = iPanelControlData;
	}
	while (false); // only do once

	return iPanel;

}



// End, PstLstUISelectionObserver.cpp.


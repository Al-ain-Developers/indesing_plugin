//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/PageTransitionsDialogObserver.cpp $
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

#include "IClassIDData.h"
#include "IControlView.h"
#include "IPanelControlData.h"
#include "ISubject.h"
#include "ITriStateControlData.h"
#include "IWidgetIDData.h"
#include "IWidgetParent.h"

// ----- Include files -----

#include "CDialogObserver.h"

// ----- Utility files -----

#include "IWidgetUtils.h"

// ----- ID files -----

#include "DynamicDocumentsUIID.h"

//====================================================================================================================
// Class PageTransitionsDialogObserver
//====================================================================================================================
class PageTransitionsDialogObserver : public CDialogObserver
{
		K2Vector<WidgetID> fContainerWidgetIDList;

		void AttachDetachAllRadioButtons(bool16 const &bAttach);
		void UpdateOldRadioButton(WidgetID const &oldRadioButtonContainerWidgetID, ClassID const &theChange);

	public:
		PageTransitionsDialogObserver(IPMUnknown* boss);
		virtual ~PageTransitionsDialogObserver();

		virtual void AutoAttach();
		virtual void AutoDetach();
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);			
};

CREATE_PMINTERFACE(PageTransitionsDialogObserver, kPageTransitionsDialogObserverImpl)

//--------------------------------------------------------------------------------------------------------------------
// PageTransitionsDialogObserver Constructor/Destructor
//--------------------------------------------------------------------------------------------------------------------
PageTransitionsDialogObserver::PageTransitionsDialogObserver(IPMUnknown* boss)
	: CDialogObserver(boss)
{
}


PageTransitionsDialogObserver::~PageTransitionsDialogObserver()
{
}

//--------------------------------------------------------------------------------------------------------------------
// AutoAttach
//--------------------------------------------------------------------------------------------------------------------
void PageTransitionsDialogObserver::AutoAttach() 
{
	CDialogObserver::AutoAttach();
	
	AttachDetachAllRadioButtons(kTrue/*attach*/);

	//
	// Deselect the previous selected radio button before the dialog brings up 
	// since we want no radio button selected at first.
	//
	InterfacePtr<IWidgetIDData> iContainerWidgetID(this, IID_ISELECTEDCONTAINERWIDGETIDDATA);
	WidgetID oldRadioButtonContainerWidgetID = iContainerWidgetID->GetWidgetID();
	this->UpdateOldRadioButton(oldRadioButtonContainerWidgetID, kTrueStateMessage);

	// Set the first radio button as the default one.
	iContainerWidgetID->Set(kPageTransitionsDialogBlindsContainerWidgetID);
	this->UpdateOldRadioButton(kPageTransitionsDialogBlindsContainerWidgetID, kFalseStateMessage);
}


//--------------------------------------------------------------------------------------------------------------------
// AutoDetach
//--------------------------------------------------------------------------------------------------------------------
void PageTransitionsDialogObserver::AutoDetach() 
{
	AttachDetachAllRadioButtons(kFalse/*detach*/);
	
	CDialogObserver::AutoDetach();
}

//--------------------------------------------------------------------------------------------------------------------
// Update
//--------------------------------------------------------------------------------------------------------------------
void PageTransitionsDialogObserver::Update(const ClassID& theChange, ISubject* iSubject, const PMIID& protocolId, void* changedBy)
{
	InterfacePtr<IControlView> iControlView(iSubject, UseDefaultIID());
	WidgetID widgetID = iControlView->GetWidgetID();

	if (widgetID == kPageTransitionsDialogProxyRadioButtonWidgetID) 
	{
		// Here we have to figure out the container widget that holds the radio button (not the radio button itself).
		InterfacePtr<IWidgetParent> iWidgetParent(iControlView, UseDefaultIID());
		InterfacePtr<IClassIDData> iPageTransitionClassIDOnWidget(static_cast<IClassIDData*>(iWidgetParent->QueryParentFor(IID_IASSICIATEDPAGETRANSITIONCLASSIDDATA)));
		InterfacePtr<IControlView> iSelectedContainerView(iPageTransitionClassIDOnWidget, UseDefaultIID());
		WidgetID selectedContainerWidgetID = iSelectedContainerView->GetWidgetID();
		
		InterfacePtr<IWidgetIDData> iCachedContainerWidgetID(this, IID_ISELECTEDCONTAINERWIDGETIDDATA);
		WidgetID oldContainerWidgetID = iCachedContainerWidgetID->GetWidgetID();

		if(oldContainerWidgetID != selectedContainerWidgetID)
		{
			this->UpdateOldRadioButton(oldContainerWidgetID, theChange);		

			// Cache the selected container's widget id on the dialog boss.
			// If the new radio button is selected, we cache the container widgetID;
			// If the new radio button gets deselected, we reset the cached widget as kInvalidWidgetID. 
			InterfacePtr<ITriStateControlData> iNewSelectedRadioData(iControlView, UseDefaultIID());
			iCachedContainerWidgetID->Set(iNewSelectedRadioData->IsSelected() ? selectedContainerWidgetID : kInvalidWidgetID);
		}

		//
		// Enable the OK button if one of the page transition is selected
		//
		InterfacePtr<IPanelControlData> iPanelControlData(this,UseDefaultIID());
		InterfacePtr<IControlView> iOKButtonControlView(iPanelControlData->FindWidget(kOKButtonWidgetID), UseDefaultIID());
		iOKButtonControlView->Enable(selectedContainerWidgetID != kInvalidWidgetID);
	}
	else
	{
		CDialogObserver::Update(theChange, iSubject, protocolId, changedBy);
	}
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

void PageTransitionsDialogObserver::AttachDetachAllRadioButtons(bool16 const &bAttach)
{		
	InterfacePtr<IPanelControlData>	iPanelControlData(this, UseDefaultIID());
	if (iPanelControlData)
	{
		InterfacePtr<IControlView> iPreviewProxyGroupView(iPanelControlData->FindWidget(kPageTransitionsDialogProxyGroup1WidgetID), UseDefaultIID());

		if (fContainerWidgetIDList.size() <= 0)
			::FindAllPreviewProxyContainerWidgets(iPreviewProxyGroupView, fContainerWidgetIDList);

		int32 numWidgets = fContainerWidgetIDList.size();

		for (int32 i = 0; i < numWidgets; ++i)
		{
			InterfacePtr<IControlView> iNthContainerView(static_cast<IControlView*>(Utils<IWidgetUtils>()->QueryRelatedWidget(iPreviewProxyGroupView, fContainerWidgetIDList[i], IID_ICONTROLVIEW)));		

			InterfacePtr<IPanelControlData> iNthContainerPanelData(iNthContainerView, UseDefaultIID());
			InterfacePtr<IControlView> iRadioButtonView(iNthContainerPanelData->FindWidget(kPageTransitionsDialogProxyRadioButtonWidgetID), UseDefaultIID());

			InterfacePtr<ISubject> iRadioButtonSubject(iRadioButtonView, IID_ISUBJECT);
			if (iRadioButtonSubject)
			{	
				if (bAttach && !iRadioButtonSubject->IsAttached( this, IID_ITRISTATECONTROLDATA, IID_IOBSERVER))
					iRadioButtonSubject->AttachObserver( this, IID_ITRISTATECONTROLDATA, IID_IOBSERVER);
				else if (!bAttach && iRadioButtonSubject->IsAttached( this, IID_ITRISTATECONTROLDATA, IID_IOBSERVER))
					iRadioButtonSubject->DetachObserver( this, IID_ITRISTATECONTROLDATA, IID_IOBSERVER);
			}
		}
	}
}

void PageTransitionsDialogObserver::UpdateOldRadioButton(WidgetID const &oldRadioButtonContainerWidgetID, ClassID const &theChange)
{
	if (oldRadioButtonContainerWidgetID != kInvalidWidgetID)
	{
		InterfacePtr<IPanelControlData>	iDialogPanelData(this, UseDefaultIID());
		InterfacePtr<IControlView> iPreviewProxyGroupView(iDialogPanelData->FindWidget(kPageTransitionsDialogProxyGroup1WidgetID), UseDefaultIID());
		InterfacePtr<IControlView> iOldContainerWidgetView(static_cast<IControlView*>(Utils<IWidgetUtils>()->QueryRelatedWidget(iPreviewProxyGroupView, oldRadioButtonContainerWidgetID, IID_ICONTROLVIEW)));		

		InterfacePtr<IPanelControlData> iOldContainerPanelData(iOldContainerWidgetView, UseDefaultIID());
		InterfacePtr<IControlView> iOldSelectedRadioButtonView(iOldContainerPanelData->FindWidget(kPageTransitionsDialogProxyRadioButtonWidgetID), UseDefaultIID());

		//
		// Update the old radio button.
		// If we have select message, then we deselect the old one;
		// if we have deselect message, we keep the old one selected since we don't allow to deselect a radio button.
		//
		InterfacePtr<ITriStateControlData> iOldSelectedRadioButton(iOldSelectedRadioButtonView, UseDefaultIID());
		if (theChange == kTrueStateMessage)
		{
			if (iOldSelectedRadioButton->IsSelected())
				iOldSelectedRadioButton->Deselect(kTrue, kFalse);
		}
		else if (theChange == kFalseStateMessage)
		{
			iOldSelectedRadioButton->Select(kTrue, kFalse);
		}
	}
}

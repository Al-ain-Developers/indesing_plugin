//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionTagOptionsDialogObserver.cpp $
//  
//  Owner: Michele Stutzman
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

#include "IControlView.h"
#include "IConditionTag.h"
#include "IDropDownListController.h"
#include "IPanelControlData.h"
#include "IStringListControlData.h"
#include "ISubject.h"

// ----- Includes -----

#include "CDialogObserver.h"

// ----- Utility files -----


// ----- ID.h files -----

#include "ConditionalTextUIID.h"

class ConditionTagOptionsDialogObserver : public CDialogObserver
{
	public:
		ConditionTagOptionsDialogObserver(IPMUnknown* boss);
		virtual ~ConditionTagOptionsDialogObserver();
	
		virtual void AutoAttach();
		virtual void AutoDetach();
		virtual void Update(const ClassID& changeId, ISubject* iSubject, const PMIID& protocolId, void* changedBy);
	
	private:	
		void UpdateAppearanceWidget(IControlView* methodView);
};

// =============================================================================
// *** ConditionTagOptionsDialogObserver impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(ConditionTagOptionsDialogObserver, kConditionTagOptionsDialogObserverImpl)

ConditionTagOptionsDialogObserver::ConditionTagOptionsDialogObserver(IPMUnknown *boss) : 
	CDialogObserver(boss)
{
} // end constructor

ConditionTagOptionsDialogObserver::~ConditionTagOptionsDialogObserver()
{
} // end destructor

// -----------------------------------------------------------------------------

void ConditionTagOptionsDialogObserver::AutoAttach()
{
	CDialogObserver::AutoAttach();

	InterfacePtr<IPanelControlData> panelControlData(this, IID_IPANELCONTROLDATA);
	if (panelControlData != nil)
	{
		IControlView* view = panelControlData->FindWidget(kConditionTagIndicatorMethodEditWidgetID);
		if (view)
		{
			InterfacePtr<ISubject> subject(view, IID_ISUBJECT);
			if (subject && !subject->IsAttached(this, IID_ISTRINGLISTCONTROLDATA))
			{
				subject->AttachObserver(this, IID_ISTRINGLISTCONTROLDATA);
				this->UpdateAppearanceWidget(view);
			}
		}
	}
} // end AutoAttach()

// -----------------------------------------------------------------------------

void ConditionTagOptionsDialogObserver::AutoDetach()
{
	CDialogObserver::AutoDetach();

	InterfacePtr<IPanelControlData> panelControlData(this, IID_IPANELCONTROLDATA);
	if (panelControlData != nil) 
	{
		IControlView* view = panelControlData->FindWidget(kConditionTagIndicatorMethodEditWidgetID);
		if (view)
		{
			InterfacePtr<ISubject> subject(view, IID_ISUBJECT);
			if (subject && subject->IsAttached(this, IID_ISTRINGLISTCONTROLDATA))
			{
				subject->DetachObserver(this, IID_ISTRINGLISTCONTROLDATA);
			}
		}
	}
} // end AutoDetach()

// -----------------------------------------------------------------------------

void ConditionTagOptionsDialogObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	CDialogObserver::Update(theChange, theSubject, protocol, changedBy);

	InterfacePtr<IControlView> view(theSubject, IID_ICONTROLVIEW);
	if (view)
	{
		WidgetID widgetID = view->GetWidgetID();
		if (widgetID.Get() == kConditionTagIndicatorMethodEditWidgetID)
		{
			this->UpdateAppearanceWidget(view);
		}
	}
} // end Update()

// -----------------------------------------------------------------------------

void ConditionTagOptionsDialogObserver::UpdateAppearanceWidget(IControlView* methodView)
{
	IConditionTag::IndicatorMethod tagMethod;
	InterfacePtr<IStringListControlData> methodDropDownData(methodView, UseDefaultIID());
	InterfacePtr<IDropDownListController> methodDropDownList(methodDropDownData, UseDefaultIID());
	tagMethod = (IConditionTag::IndicatorMethod)methodDropDownList->GetSelected();
	if (tagMethod != IConditionTag::kUnderline)
	{
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		IControlView* appearanceView = panelControlData->FindWidget(kConditionTagIndicatorAppearanceEditWidgetID);
		if (appearanceView)
			appearanceView->Disable();
	}
	else
	{
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		IControlView* appearanceView = panelControlData->FindWidget(kConditionTagIndicatorAppearanceEditWidgetID);
		if (appearanceView)
			appearanceView->Enable();
	}
} // end UpdateAppearanceWidget()
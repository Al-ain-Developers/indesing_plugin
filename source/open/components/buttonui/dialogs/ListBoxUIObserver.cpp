//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/dialogs/ListBoxUIObserver.cpp $
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

// Interface includes:
#include "IControlView.h"
#include "IDialog.h"
#include "IDialogController.h"
#include "IPanelControlData.h"
#include "ISubject.h"
#include "IWidgetParent.h"

// Implementation includes:
#include "CObserver.h"

// FormFieldUIID
#include "FormFieldUIID.h"
#include "FormFieldUIDefs.h"


//------------------------------------------------------------

class ListBoxUIObserver : public CObserver
{
	public:
	
		ListBoxUIObserver(IPMUnknown* boss) : CObserver(boss){}

		virtual void Update
		(
			const ClassID& theChange, 
			ISubject* theSubject, 
			const PMIID &protocol, 
			void* changedBy
		);

		void AttachToWidget(const WidgetID& widgetId, const PMIID& iidOfDataToObserve, IPanelControlData* panelData);
		void DetachFromWidget(const WidgetID& widgetId, const PMIID& iidOfDataToObserve, IPanelControlData* panelData);

        virtual void AutoAttach();
        virtual void AutoDetach();
};

CREATE_PMINTERFACE(ListBoxUIObserver, kListBoxUIObserverImpl)

//------------------------------------------------------------

void ListBoxUIObserver::Update
(
	const ClassID& theChange, 
	ISubject* theSubject, 
	const PMIID &protocol, 
	void* changedBy
)
{
	InterfacePtr<IControlView> view(theSubject, IID_ICONTROLVIEW);
   
	if (view != nil)
	{
		WidgetID theSelectedWidget = view->GetWidgetID();

		InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);

		if ( theSelectedWidget == kListBoxEditableWID )
		{
			IControlView* iSpellCheckView = panelData->FindWidget(kListBoxSpellCheckWID);
			iSpellCheckView->Enable(theChange == kTrueStateMessage);
		}
    }
}

//------------------------------------------------------------

void ListBoxUIObserver::DetachFromWidget(const WidgetID& widgetId, const PMIID& iidOfDataToObserve, IPanelControlData* panelData)
{
	IControlView* view = panelData->FindWidget(widgetId);
	
	// It's possible that the widget might not exist.  For example, we always try
	// and attach to an ok and cancel button.  It's not necessary that the dialog
	// has either.
	if (view) {
		InterfacePtr<ISubject> subject(view, IID_ISUBJECT);
		if (subject)
			subject->DetachObserver(this, iidOfDataToObserve);
	}
}

//------------------------------------------------------------

void ListBoxUIObserver::AttachToWidget(const WidgetID& widgetId, const PMIID& iidOfDataToObserve, IPanelControlData* panelData)
{
	IControlView* view = panelData->FindWidget(widgetId);
	
	// It's possible that the widget might not exist.  For example, we always try
	// and attach to an ok and cancel button.  It's not necessary that the dialog
	// has either.
	if (view) {
		InterfacePtr<ISubject> subject(view, IID_ISUBJECT);
		if (subject)
			subject->AttachObserver(this, iidOfDataToObserve);
	}
}

//------------------------------------------------------------

void ListBoxUIObserver::AutoAttach()
{
	InterfacePtr<IPanelControlData> panel(this, IID_IPANELCONTROLDATA);
	if (panel != nil)
	{
		AttachToWidget(kListBoxEditableWID, IID_ITRISTATECONTROLDATA, panel);
	}

}

//------------------------------------------------------------

void ListBoxUIObserver::AutoDetach()
{
	InterfacePtr<IPanelControlData> panel(this, IID_IPANELCONTROLDATA);
	if (panel != nil)
	{
		DetachFromWidget(kListBoxEditableWID, IID_ITRISTATECONTROLDATA, panel);
	}
}

// End, ListBoxUIObserver.cpp.

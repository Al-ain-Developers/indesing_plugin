//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/dialogs/TextFieldUIObserver.cpp $
//  
//  Owner: Tim Wright
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

class TextFieldUIObserver : public CObserver
{
	public:
	
		TextFieldUIObserver(IPMUnknown* boss) : CObserver(boss){}

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

CREATE_PMINTERFACE(TextFieldUIObserver, kTextFieldUIObserverImpl)

//------------------------------------------------------------

void TextFieldUIObserver::Update
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
		
		IControlView* iPasswordView = panelData->FindWidget(kPasswordWID);
		IControlView* iFileSelView = panelData->FindWidget(kForFileSelectionWID);
		IControlView* iMultiLineView = panelData->FindWidget(kMultilineWID);
		IControlView* iScrollView = panelData->FindWidget(kScrollWID);
		IControlView* iSpellCheckView = panelData->FindWidget(kTextFieldSpellCheckWID);
		IControlView* iHasMaxLengthView = panelData->FindWidget(kCharLimitWID);
		IControlView* iCharLimitEditView = panelData->FindWidget(kCharLimitEditWID);
		IControlView* iCharLimitStaticView = panelData->FindWidget(kCharLimitStaticWID);
			
		InterfacePtr<ITriStateControlData> iScrollData(iScrollView, IID_ITRISTATECONTROLDATA);
		InterfacePtr<ITriStateControlData> iMultiLineData(iMultiLineView, IID_ITRISTATECONTROLDATA);
		InterfacePtr<ITriStateControlData> iSpellCheckData(iSpellCheckView, IID_ITRISTATECONTROLDATA);
		InterfacePtr<ITriStateControlData> iPasswordData(iPasswordView, IID_ITRISTATECONTROLDATA);
		InterfacePtr<ITriStateControlData> iFileSelData(iFileSelView, IID_ITRISTATECONTROLDATA);
		InterfacePtr<ITriStateControlData> iHasMaxLengthData(iHasMaxLengthView, IID_ITRISTATECONTROLDATA);

		if ( theSelectedWidget == kCharLimitWID )
		{
			iCharLimitEditView->Enable(theChange == kTrueStateMessage);
			iCharLimitStaticView->Enable(theChange == kTrueStateMessage);
		}
		else if ( theSelectedWidget == kForFileSelectionWID )
		{
			
			if ( theChange == kTrueStateMessage ) {
				iMultiLineData->Deselect();
				iScrollData->Select();
				iSpellCheckData->Deselect();
				iHasMaxLengthData->Deselect();
				iPasswordData->Deselect();
			}
			
			iPasswordView->Enable(theChange == kFalseStateMessage &&
							iMultiLineData->GetState() != ITriStateControlData::kSelected &&
							iSpellCheckData->GetState() != ITriStateControlData::kSelected);
			iMultiLineView->Enable(theChange == kFalseStateMessage);
			iScrollView->Enable(theChange == kFalseStateMessage);
			iSpellCheckView->Enable(theChange == kFalseStateMessage);
			iHasMaxLengthView->Enable(theChange == kFalseStateMessage);
			iCharLimitEditView->Enable(theChange == kFalseStateMessage &&
							iHasMaxLengthData->GetState() != ITriStateControlData::kUnselected);
			iCharLimitStaticView->Enable(theChange == kFalseStateMessage &&
							iHasMaxLengthData->GetState() != ITriStateControlData::kUnselected);
		}
		else if ( theSelectedWidget == kPasswordWID )
		{
			if ( theChange == kTrueStateMessage ) {
				iMultiLineData->Deselect();
				iScrollData->Deselect();
				iSpellCheckData->Deselect();
				iFileSelData->Deselect();
			}
			
			iFileSelView->Enable(theChange == kFalseStateMessage &&
							iScrollData->GetState() != ITriStateControlData::kUnselected &&
							iMultiLineData->GetState() != ITriStateControlData::kSelected &&
							iSpellCheckData->GetState() != ITriStateControlData::kSelected);
			iMultiLineView->Enable(theChange == kFalseStateMessage);
			iScrollView->Enable(theChange == kFalseStateMessage);
			iSpellCheckView->Enable(theChange == kFalseStateMessage);
		}
		else if ( theSelectedWidget == kMultilineWID )
		{
			if ( theChange == kTrueStateMessage ) {
				iPasswordData->Deselect();
				iFileSelData->Deselect();
			}
			
			iFileSelView->Enable(theChange == kFalseStateMessage &&
							iPasswordData->GetState() != ITriStateControlData::kSelected &&
							iScrollData->GetState() != ITriStateControlData::kUnselected &&
							iSpellCheckData->GetState() != ITriStateControlData::kSelected);
			iPasswordView->Enable(theChange == kFalseStateMessage &&
							iFileSelData->GetState() != ITriStateControlData::kSelected &&
							iSpellCheckData->GetState() != ITriStateControlData::kSelected);
		}
		else if ( theSelectedWidget == kScrollWID )
		{
			if ( theChange == kFalseStateMessage ) {
				iFileSelData->Deselect();
			}
			
			iFileSelView->Enable(theChange == kTrueStateMessage &&
							iPasswordData->GetState() != ITriStateControlData::kSelected &&
							iMultiLineData->GetState() != ITriStateControlData::kSelected &&
							iSpellCheckData->GetState() != ITriStateControlData::kSelected);
		}
		else if ( theSelectedWidget == kTextFieldSpellCheckWID )
		{
			if ( theChange == kTrueStateMessage ) {
				iPasswordData->Deselect();
				iFileSelData->Deselect();
			}
			
			iFileSelView->Enable(theChange == kFalseStateMessage &&
							iPasswordData->GetState() != ITriStateControlData::kSelected &&
							iScrollData->GetState() != ITriStateControlData::kUnselected &&
							iMultiLineData->GetState() != ITriStateControlData::kSelected);
			iPasswordView->Enable(theChange == kFalseStateMessage &&
							iFileSelData->GetState() != ITriStateControlData::kSelected &&
							iMultiLineData->GetState() != ITriStateControlData::kSelected);
		}
    }
}

//------------------------------------------------------------

void TextFieldUIObserver::DetachFromWidget(const WidgetID& widgetId, const PMIID& iidOfDataToObserve, IPanelControlData* panelData)
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

void TextFieldUIObserver::AttachToWidget(const WidgetID& widgetId, const PMIID& iidOfDataToObserve, IPanelControlData* panelData)
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

void TextFieldUIObserver::AutoAttach()
{
	InterfacePtr<IPanelControlData> panel(this, IID_IPANELCONTROLDATA);
	if (panel != nil)
	{
		AttachToWidget(kCharLimitWID, IID_ITRISTATECONTROLDATA, panel);
		AttachToWidget(kForFileSelectionWID, IID_ITRISTATECONTROLDATA, panel);
		AttachToWidget(kPasswordWID, IID_ITRISTATECONTROLDATA, panel);
		AttachToWidget(kMultilineWID, IID_ITRISTATECONTROLDATA, panel);
		AttachToWidget(kScrollWID, IID_ITRISTATECONTROLDATA, panel);
		AttachToWidget(kTextFieldSpellCheckWID, IID_ITRISTATECONTROLDATA, panel);
	}

}

//------------------------------------------------------------

void TextFieldUIObserver::AutoDetach()
{
	InterfacePtr<IPanelControlData> panel(this, IID_IPANELCONTROLDATA);
	if (panel != nil)
	{
		DetachFromWidget(kCharLimitWID, IID_ITRISTATECONTROLDATA, panel);
		DetachFromWidget(kForFileSelectionWID, IID_ITRISTATECONTROLDATA, panel);
		DetachFromWidget(kPasswordWID, IID_ITRISTATECONTROLDATA, panel);
		DetachFromWidget(kMultilineWID, IID_ITRISTATECONTROLDATA, panel);
		DetachFromWidget(kScrollWID, IID_ITRISTATECONTROLDATA, panel);
		DetachFromWidget(kTextFieldSpellCheckWID, IID_ITRISTATECONTROLDATA, panel);
	}
}

// End, TextFieldUIObserver.cpp.

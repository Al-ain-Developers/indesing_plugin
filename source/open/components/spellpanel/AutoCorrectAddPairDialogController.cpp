//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectAddPairDialogController.cpp $
//  
//  Owner: Heath Horton
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
//  
//  Proj:	AutoCorrectAddPairDlg
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "IBoolData.h"
#include "IPanelControlData.h"
#include "IStringData.h"
#include "ITextControlData.h"
#include "IWidgetParent.h"

#include "CDialogController.h"
#include "SpellPanelID.h"


class AutoCorrectAddPairDlgController : public CDialogController
{
public:
	AutoCorrectAddPairDlgController( IPMUnknown* boss );
	virtual				~AutoCorrectAddPairDlgController();
	
	virtual void		InitializeDialogFields(IActiveContext* dlgContext);
	virtual void		ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);
	virtual void		UserCancelled(void);

private:

};

CREATE_PMINTERFACE( AutoCorrectAddPairDlgController, kAutoCorrectAddPairDialogControllerImpl )


AutoCorrectAddPairDlgController::AutoCorrectAddPairDlgController( IPMUnknown* boss ) :
	CDialogController( boss )
{
}

AutoCorrectAddPairDlgController::~AutoCorrectAddPairDlgController()
{
}

void AutoCorrectAddPairDlgController::InitializeDialogFields( IActiveContext* dlgContext)
{
	InterfacePtr<IPanelControlData> parentPanel(this, IID_IPANELCONTROLDATA);
	if (!parentPanel)
		return;

	InterfacePtr<IBoolData> addingWordMode(this, IID_IADDINGWORDMODEBOOLDATA);
	
	PMString nilString;
	
	InterfacePtr<IControlView> misspelledEdit(parentPanel->FindWidget(kAutoCorrectMisspelledEditTextWidgetID), IID_ICONTROLVIEW);
	if (misspelledEdit)
	{
		InterfacePtr<ITextControlData> lastGoodText(misspelledEdit, IID_ILASTVALIDTEXTCONTROLDATA);
		if (lastGoodText)
		{
			PMString oldString = lastGoodText->GetString();
			lastGoodText->SetString(nilString);
		}
		InterfacePtr<ITextControlData> correctedText(misspelledEdit, UseDefaultIID());
		if (correctedText)
		{
			if (addingWordMode->Get())
			{
				correctedText->SetString(nilString);
				misspelledEdit->Enable();
			}
			else
			{
				InterfacePtr<IStringData> misspelledStringData( this, UseDefaultIID() );
				correctedText->SetString(misspelledStringData->GetString());	
				misspelledEdit->Disable();
			}
		}
	}
	
	InterfacePtr<IControlView> correctedEdit(parentPanel->FindWidget(kAutoCorrectCorrectedEditTextWidgetID), IID_ICONTROLVIEW);
	if (correctedEdit)
	{
		InterfacePtr<ITextControlData> lastGoodText(correctedEdit, IID_ILASTVALIDTEXTCONTROLDATA);
		if (lastGoodText)
		{
			PMString oldString = lastGoodText->GetString();
			lastGoodText->SetString(nilString);
		}

		InterfacePtr<ITextControlData> correctedText(correctedEdit, UseDefaultIID());
		if (correctedText)
		{
			if (addingWordMode->Get())
			{
				correctedText->SetString(nilString);
			}
			else
			{
				InterfacePtr<IStringData> correctedStringData( this, IID_ICORRECTEDSTRINGDATA );
				correctedText->SetString(correctedStringData->GetString());	
			}
		}
	}
}

void AutoCorrectAddPairDlgController::ApplyDialogFields(IActiveContext* myContext,const WidgetID& widgetId)
{
    InterfacePtr<IBoolData> dialogCancelled( this, UseDefaultIID() );
	dialogCancelled->Set(kFalse);

	InterfacePtr<IPanelControlData> parentPanel(this, IID_IPANELCONTROLDATA);
	if (!parentPanel)
		return;

	InterfacePtr<IStringData> misspelledData(this, UseDefaultIID());
	InterfacePtr<IStringData> correctedData(this, IID_ICORRECTEDSTRINGDATA);

	PMString misspelledString;
	PMString correctedString;

	InterfacePtr<IControlView> misspelledView(parentPanel->FindWidget(kAutoCorrectMisspelledEditTextWidgetID), IID_ICONTROLVIEW);
	if (misspelledView)
	{
		InterfacePtr<ITextControlData> misspelledText(misspelledView, UseDefaultIID());
		if (misspelledText)
		{
			misspelledString = misspelledText->GetString();
		}
	}

	InterfacePtr<IControlView> correctedView(parentPanel->FindWidget(kAutoCorrectCorrectedEditTextWidgetID), IID_ICONTROLVIEW);
	if (correctedView)
	{
		InterfacePtr<ITextControlData> correctedText(correctedView, UseDefaultIID());
		if (correctedText)
		{
			correctedString = correctedText->GetString();
		}
	}

	misspelledData->Set(misspelledString);
	correctedData->Set(correctedString);
}

void AutoCorrectAddPairDlgController::UserCancelled()
{
   InterfacePtr<IBoolData> dialogCancelled( this, UseDefaultIID() );
   dialogCancelled->Set(kTrue);
}



//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellPanelDialogController.cpp $
//  
//  Owner: Cindy Chen
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

#include "SpellPanelDialogController.h"

#include "IPanelControlData.h"
#include "ISession.h"
#include "IDialog.h"
#include "IWidgetParent.h"
#include "INoteFindChangeSpelling.h"
#include "Utils.h" 
#include "IEVEUtils.h" 
#include "IBoolData.h"

#ifdef OSX_HACK
static bool16 gOSXAquaInterface = kFalse;
#endif
 

CREATE_PMINTERFACE(SpellPanelDialogController, kSpellPanelDialogControllerImpl)

//========================================================================================
// SpellPanelDialogController::SpellPanelDialogController
//========================================================================================
SpellPanelDialogController::SpellPanelDialogController(IPMUnknown* boss)
: CDialogController(boss)
 {
}

//========================================================================================
// SpellPanelDialogController::~SpellPanelDialogController
//========================================================================================
SpellPanelDialogController::~SpellPanelDialogController()
{
}


// Should be overriden to initialize each widget in the dialog
// with its default value.
void  SpellPanelDialogController::InitializeDialogFields(IActiveContext* context)
{
	CDialogController::InitializeDialogFields(context);
	InterfacePtr<IControlView> dialogView(this, UseDefaultIID());
	InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
	InterfacePtr<IWidgetParent> iParent(this, UseDefaultIID());
	InterfacePtr<IDialog> iDialog((IDialog*)iParent->QueryParentFor(IID_IDIALOG));
	InterfacePtr<IBoolData> iApplyEVELayout(iDialog, IID_IAPPLYEVELAYOUTBOOLDATA);
	if (iApplyEVELayout->GetBool())
	{
		if (Utils<IEVEUtils>()->CanApplyEveLayout(dialogView))
			Utils<IEVEUtils>()->ApplyEveLayout(dialogView);
		IControlView *widgetView = panelControlData->FindWidget(kSpellLanguageBossWidgetID);
		widgetView->Resize(PMPoint(220, 21));
		IControlView *staticTextWidget = panelControlData->FindWidget(kSpellStatusTextWidgetID);
		IControlView *editBoxWidget = panelControlData->FindWidget(kSpellWordEditBoxID);
		PMRect newFrame = editBoxWidget->GetFrame();
		newFrame.Top() = staticTextWidget->GetFrame().Top();
		newFrame.Bottom() = staticTextWidget->GetFrame().Bottom();
		staticTextWidget->SetFrame(newFrame);
		iApplyEVELayout->Set(kFalse);
	}
}

//========================================================================================
// SpellPanelDialogController::ClosingDialog
//========================================================================================
void SpellPanelDialogController::ClosingDialog(IActiveContext* lastChanceToUseMyContext)
{	
	// InCopy, turn off flag
	InterfacePtr<INoteFindChangeSpelling> fcs(GetExecutionContextSession(), UseDefaultIID());
	ASSERT(fcs != nil);
	fcs->SetSpellingWarningSkipTables(false);
}

// End, SpellPanelDialogController.cpp.

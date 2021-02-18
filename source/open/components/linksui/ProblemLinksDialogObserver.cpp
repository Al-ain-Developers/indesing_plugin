//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/ProblemLinksDialogObserver.cpp $
//  
//  Owner: Steve Flenniken
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
#include "IPanelControlData.h"
#include "LinksUIID.h"
#include "CDialogObserver.h"
#include "IIntData.h"
#include "CDialogController.h"
#include "IControlView.h"
#include "ISubject.h"
#include "IBoolData.h"
#include "ILayoutUtils.h"
#include "IDocument.h"
#include "ErrorUtils.h"
#include "ILayoutUIUtils.h"
#include "StringUtils.h"
#include "IEVEUtils.h"

class ProblemLinksDialogObserver : public CDialogObserver
{
public:
	ProblemLinksDialogObserver(IPMUnknown* boss);

protected:
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);
	virtual void AutoAttach();
	virtual void AutoDetach();
};

CREATE_PMINTERFACE(ProblemLinksDialogObserver, kProblemLinksDialogObserverImpl)

ProblemLinksDialogObserver::ProblemLinksDialogObserver(IPMUnknown* boss) :
	CDialogObserver (boss)
{
}

void ProblemLinksDialogObserver::AutoAttach() 
{
	CDialogObserver::AutoAttach();

	InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);
	if (panelData)
		AttachToWidget(kFixLinksButtonWidgetID, IID_IBOOLEANCONTROLDATA, panelData);
}

void ProblemLinksDialogObserver::AutoDetach() 
{
	InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);
	if (panelData)
		DetachFromWidget(kFixLinksButtonWidgetID, IID_IBOOLEANCONTROLDATA, panelData);

	CDialogObserver::AutoDetach();
}

void ProblemLinksDialogObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
	CDialogObserver::Update(theChange, theSubject, protocol, changedBy);

	// Only respond when the button is going up.
	if (theChange == kTrueStateMessage)
	{
		InterfacePtr<IControlView> view(theSubject, IID_ICONTROLVIEW);
		ASSERT_MSG(view!=0, 0);

		if (view->GetWidgetID() == kFixLinksButtonWidgetID)
		{
			InterfacePtr<IBoolData> fixLinks(this, IID_IFIXLINKSSELECTED);
			fixLinks->Set(kTrue);
			CloseDialog();
		}
	}
}


class ProblemLinksDialogController : public CDialogController
{
public:
	ProblemLinksDialogController(IPMUnknown* boss);

protected:
	virtual void InitializeDialogFields( IActiveContext* dlgContext);
};

CREATE_PMINTERFACE(ProblemLinksDialogController, kProblemLinksDialogControllerImpl)


ProblemLinksDialogController::ProblemLinksDialogController(IPMUnknown* boss) :
	CDialogController (boss)
{
}

void ProblemLinksDialogController::InitializeDialogFields( IActiveContext* dlgContext)
{
	#pragma unused(dlgContext)

	InterfacePtr<IBoolData> fixLinks(this, IID_IFIXLINKSSELECTED);
	fixLinks->Set(kFalse);

	// Get the current missing and modified counts.
	InterfacePtr<IIntData> missing(this, IID_IMISSINGCOUNT);
	uint32 missingcount = missing->GetInt();
	InterfacePtr<IIntData> outofdate(this, IID_IOUTOFDATECOUNT);
	uint32 outofdatecount = outofdate->GetInt();
	InterfacePtr<IIntData> inaccessible(this, IID_IINACCESSIBLECOUNT);
	uint32 inaccessiblecount = inaccessible->GetInt();
	InterfacePtr<IBoolData> HTTPlinks(this, IID_IHTTPLINKS);
	bool areHTTPLinks = HTTPlinks->GetBool();

	PMString messageString(areHTTPLinks ? "#HTTPLinksModifiedWarning" : "#LinksModifiedWarning");
	messageString.Translate();
	this->SetTextControlData(kProblemLinkMultilineTextWidgetId, messageString);

	// Display the missing and modified counts.
	PMString missingString("#ProblemMissingLinksParamStr");
	missingString.Translate();
	PMString missingCountStr;
	missingCountStr.AppendNumber(missingcount);
	missingCountStr.SetTranslatable(kFalse);
	StringUtils::ReplaceStringParameters(&missingString,missingCountStr);
	this->SetTextControlData(kMissingLinksStaticWidgetID, missingString);
	
	PMString modifiedString("#ProblemModifiedLinksParamStr");
	modifiedString.Translate();
	PMString modifiedCountStr;
	modifiedCountStr.AppendNumber(outofdatecount);
	modifiedCountStr.SetTranslatable(kFalse);
	StringUtils::ReplaceStringParameters(&modifiedString,modifiedCountStr);
	this->SetTextControlData(kModifiedLinksStaticWidgetID, modifiedString);

	if (inaccessiblecount)
	{
		InterfacePtr<IPanelControlData> panelData(QueryIfNilElseAddRef(nil));
		IControlView* view = panelData->FindWidget(kInaccessibleLinksStaticWidgetID);
		if (view)
		{	
			PMString inaccessibleString("#ProblemInaccessibleLinksParamStr");
			inaccessibleString.Translate();
			PMString inaccessibleCountStr;
			inaccessibleCountStr.AppendNumber(inaccessiblecount);
			inaccessibleCountStr.SetTranslatable(kFalse);
			StringUtils::ReplaceStringParameters(&inaccessibleString,inaccessibleCountStr);
			this->SetTextControlData(kInaccessibleLinksStaticWidgetID, inaccessibleString);

			view->ShowView();
		}
	}
	
	// Because the string is parameterized, we might need more room now, so re-layout the dialog with EVE
	InterfacePtr<IControlView> dialogView(this,UseDefaultIID());
	Utils<IEVEUtils>()->ApplyEveLayout(dialogView);
}


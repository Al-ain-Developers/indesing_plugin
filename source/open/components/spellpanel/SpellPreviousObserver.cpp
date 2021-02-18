//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellPreviousObserver.cpp $
//  
//  Owner: Bernd Paradies
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

#include "ISubject.h"
#include "IControlView.h"
#include "SpellPanelObserver.h"
#include "ITriStateControlData.h"
#include "ISpellCheckWalkerData.h"
#include "ITextWalker.h"
#include "SpellPanelID.h"


//----------------------------------------------------------------------------------------
// Class SpellSkipObserver
//----------------------------------------------------------------------------------------

class SpellPreviousObserver : public SpellPanelObserver
{
public:
	SpellPreviousObserver(IPMUnknown *boss);
	virtual void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
protected:
	virtual void		AutoAttach();
	virtual void 		AutoDetach();
	virtual void		TargetToWidget();
	ISpellCheckWalkerData 		*QuerySpellCheckWalkerData();
	void   NotifyObserver(ClassID messageID);
	void   TerminateWalker();
};


#define CONTROL_PMIID		IID_IBOOLEANCONTROLDATA


//===============================================================
// CLASS SpellPreviousObserver
//===============================================================

CREATE_PMINTERFACE(SpellPreviousObserver, kSpellPreviousObserverImpl)
#define INHERITED 	SpellPanelObserver

//---------------------------------------------------------------
// SpellPreviousObserver constructor 
//---------------------------------------------------------------

SpellPreviousObserver::SpellPreviousObserver(IPMUnknown *boss) :
	INHERITED(boss)
{
	this->SetControlID(CONTROL_PMIID);
	this->SetReset(kTrue);
}

void SpellPreviousObserver::AutoAttach()
{
	// Attaching to subject of widget for protocol IID_ITRISTATECONTROLDATA. Both, this observer and the subject, are on the widget boss.
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
	{
		const PMIID nControlID = IID_ITRISTATECONTROLDATA;
		if (!subject->IsAttached(this, nControlID))
			subject->AttachObserver(this, nControlID);

	}
	TargetToWidget();

	INHERITED::AutoAttach();
}

//---------------------------------------------------------------------------
// SpellSearchBackwardsObserver::TargetToWidget()
//
// Descriptions:
//	Propagate the values from preferences into the checkbox
//---------------------------------------------------------------------------
void SpellPreviousObserver::TargetToWidget()
{
	InterfacePtr<ITriStateControlData> pCheckBoxData(this, IID_ITRISTATECONTROLDATA);
	if (!pCheckBoxData)
	{
		ASSERT_MSG(pCheckBoxData != 0, "SpellSearchBackwardsObserver - missing IID_ITRISTATECONTROLDATA at TargetToWidget");
		return;
	}

	InterfacePtr<ISpellCheckWalkerData> pWalkerData(this->QuerySpellCheckWalkerData());
	if (pWalkerData == nil) {
		ASSERT_FAIL("SpellSearchBackwardsObserver - couldn't find SpellCheckWalkerData");
		return;
	}

	bool16 isBackSearch = pWalkerData->GetDirection();

	InterfacePtr<IControlView> view(this, UseDefaultIID());
	if (view->GetWidgetID() == kSpellBackwardsRadioWidgetID)
	{
		if (isBackSearch)
			pCheckBoxData->Select(kTrue, kFalse);
		else
			pCheckBoxData->Deselect(kTrue, kFalse);
	}
	else if (view->GetWidgetID() == kSpellForwardRadioWidgetID)
	{
		if (!isBackSearch)
			pCheckBoxData->Select(kTrue, kFalse);
		else
			pCheckBoxData->Deselect(kTrue, kFalse);
	}
}

void SpellPreviousObserver::AutoDetach()
{
	INHERITED::AutoDetach();

	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
	{
		const PMIID nControlID = IID_ITRISTATECONTROLDATA;
		if (subject->IsAttached(this, nControlID))
		{
			subject->DetachObserver(this, nControlID);
		}
	}

}

//---------------------------------------------------------------
// SpellSkipObserver::Update
//---------------------------------------------------------------

void	SpellPreviousObserver::Update(const ClassID& theChange, ISubject*theSubject, const PMIID &protocol, void* changedBy)
{
	if (protocol == IID_ITRISTATECONTROLDATA && (theChange == kTrueStateMessage))
	{
		InterfacePtr<ISpellCheckWalkerData> pWalkerData(this->QuerySpellCheckWalkerData());

		if (pWalkerData != nil)
		{
			InterfacePtr<IControlView> view(theSubject, UseDefaultIID());
			bool16 direction = (view->GetWidgetID() == kSpellBackwardsRadioWidgetID);
			pWalkerData->SetDirection(direction);
			// First Halt the Walker
			this->TerminateWalker();
			// Notify that the textwalker has stopped. This will set the SpellSkipObserver mode to kFinished. This will help us set the scope correctly.
			this->NotifyObserver(kTextWalkerDoHaltMessage); 
			this->NotifyObserver(kSpellPanelMsgDirectionHasChanged);// Change To End of Story to To Beginning of Story & vice-versa.
		}
		return;
	}
}


//---------------------------------------------------------------
// SpellPreviousObserver::NotifyObserver
//---------------------------------------------------------------

// see SpellWordObserver::NotifyObserver

void	SpellPreviousObserver::NotifyObserver(ClassID nMsg)
{
	if (nMsg == kTextWalkerDoHaltMessage)
	{
		InterfacePtr<ITextWalker>pWalker(this->QueryTextWalker());
		InterfacePtr<ISubject> pWalkerSubject(pWalker, IID_ISUBJECT);
		if (pWalkerSubject)
			pWalkerSubject->Change(nMsg, IID_ITEXTWALKERMSG, this);
		return;
	}

	InterfacePtr<ISubject> pPanel(this->QueryPanelSubject());
	if (pPanel)
	{
		pPanel->Change(nMsg, IID_ISPELLPANELMSG, this);
	}
}

void SpellPreviousObserver::TerminateWalker()
{
	InterfacePtr<ITextWalker>pWalker(this->QueryTextWalker());
	if (pWalker && pWalker->IsWalking())
		pWalker->Halt();
}

//--------------------------------------------------------------- 
// SpellSearchBackwardsObserver::QuerySpellCheckWalkerData
//--------------------------------------------------------------- 

ISpellCheckWalkerData *SpellPreviousObserver::QuerySpellCheckWalkerData()
{
	InterfacePtr< ISubject>pPanel(this->QueryPanelSubject());
	return (ISpellCheckWalkerData*)pPanel->QueryInterface(IID_ISPELLCHECKWALKERDATA);
}

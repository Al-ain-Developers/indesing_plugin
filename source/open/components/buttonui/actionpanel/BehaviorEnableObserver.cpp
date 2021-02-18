//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actionpanel/BehaviorEnableObserver.cpp $
//  
//  Owner: Michael Burbidge
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

// ----- Interface Includes -----

#include "IBehaviorSuite.h"
#include "IControlView.h"
#include "IWidgetParent.h"
#include "ITreeNodeIDData.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "widgetid.h"
#include "CActiveSelectionObserver.h"
#include "SelectionUtils.h"
#include "UIDNodeID.h"
#include "Utils.h"

//========================================================================================
// CLASS BehaviorEnableObserver
//========================================================================================

class BehaviorEnableObserver : public CActiveSelectionObserver
{
public:
	BehaviorEnableObserver(IPMUnknown *boss);
	virtual ~BehaviorEnableObserver();
	
	virtual void 	AutoAttach();
	virtual void 	AutoDetach();
	virtual void 	Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
	
protected:
	virtual void HandleSelectionChanged(const ISelectionMessage*);

private:
	void 					EnableSelectedAction(const bool16& enable);
};

//========================================================================================
// METHODS BehaviorEnableObserver
//========================================================================================

CREATE_PMINTERFACE(BehaviorEnableObserver, kBehaviorEnableObserverImpl)

//----------------------------------------------------------------------------------------
// BehaviorEnableObserver constructor 
//----------------------------------------------------------------------------------------

BehaviorEnableObserver::BehaviorEnableObserver(IPMUnknown *boss) :
	CActiveSelectionObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// BehaviorEnableObserver::~BehaviorEnableObserver
//----------------------------------------------------------------------------------------

BehaviorEnableObserver::~BehaviorEnableObserver()
{
}

//----------------------------------------------------------------------------------------
// BehaviorEnableObserver::AutoAttach
//----------------------------------------------------------------------------------------

void BehaviorEnableObserver::AutoAttach()
{	
	CActiveSelectionObserver::AutoAttach();
	AttachToWidget(kBehaviorOnOffButtonWidgetID, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// BehaviorEnableObserver::AutoDetach
//----------------------------------------------------------------------------------------

void BehaviorEnableObserver::AutoDetach()
{
	CActiveSelectionObserver::AutoDetach();
	DetachFromWidget(kBehaviorOnOffButtonWidgetID, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// BehaviorEnableObserver::Update
//----------------------------------------------------------------------------------------

void BehaviorEnableObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	if (theChange == kTrueStateMessage)	
		EnableSelectedAction(kTrue);
	if (theChange == kFalseStateMessage)	
		EnableSelectedAction(kFalse);
	else
		CActiveSelectionObserver::Update(theChange, theSubject, protocol, changedBy);
}

//----------------------------------------------------------------------------------------
// BehaviorEnableObserver::HandleSelectionChanged
//----------------------------------------------------------------------------------------

void BehaviorEnableObserver::HandleSelectionChanged(const ISelectionMessage*)
{
}

//----------------------------------------------------------------------------------------
// BehaviorEnableObserver::EnableSelectedAction
//----------------------------------------------------------------------------------------

void BehaviorEnableObserver::EnableSelectedAction(const bool16& enable)
{
	InterfacePtr<IBehaviorSuite> actionSuite (SelectionUtils::QuerySuite<IBehaviorSuite>());
	if (actionSuite)
	{
		InterfacePtr<IWidgetParent> parentPtr(this, UseDefaultIID());
		InterfacePtr<ITreeNodeIDData> data((ITreeNodeIDData*) parentPtr->QueryParentFor(IID_ITREENODEIDDATA));
	
		TreeNodePtr<UIDNodeID> behaviorNode(data->Get());
		actionSuite->EnableAction(behaviorNode->GetUID(), enable);
	}
}

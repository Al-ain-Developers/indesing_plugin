//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/TimingPanelPageItemNameObserver.cpp $
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
//  ADOBE CONFIDENTIAL
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

// ----- Interface files -----

#include "IActiveContext.h"
#include "IDocument.h"
#include "IPageItemNameFacade.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITreeNodeIDData.h"
#include "IWidgetParent.h"
#include "IDynamicTargetsFacade.h"

// ----- Include files -----

#include "InLineEditObserver.h"
#include "TimingPanelTreeNodeID.h"

// ----- Utilitity files -----

#include "IPageItemNameFacade.h"
#include "Utils.h"

// ----- ID files -----

#include "DynamicDocumentsUIID.h"

class TimingPanelPageItemNameObserver : public InLineEditObserver
{
	public:
		TimingPanelPageItemNameObserver(IPMUnknown *boss);
		virtual ~TimingPanelPageItemNameObserver();
		
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
		
		virtual void AutoAttach();			
		virtual void AutoDetach();
	
};


CREATE_PMINTERFACE(TimingPanelPageItemNameObserver, kTimingPanelPageItemNameObserverImpl)

TimingPanelPageItemNameObserver::TimingPanelPageItemNameObserver(IPMUnknown *boss) :
	InLineEditObserver(boss)
{
}

TimingPanelPageItemNameObserver::~TimingPanelPageItemNameObserver()
{
}

void TimingPanelPageItemNameObserver::AutoAttach()
{
	InLineEditObserver::AutoAttach();

	InterfacePtr<ISubject> subjectList( this, UseDefaultIID() );
	if (subjectList)
		subjectList->AttachObserver(this, ITextControlData::kDefaultIID); 
}

void TimingPanelPageItemNameObserver::AutoDetach()
{
	InterfacePtr<ISubject> subjectList( this, UseDefaultIID() );
	if (subjectList)
		subjectList->DetachObserver(this, ITextControlData::kDefaultIID);

	InLineEditObserver::AutoDetach();
}

void TimingPanelPageItemNameObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	if (protocol == ITextControlData::kDefaultIID && theChange == kTextChangeStateMessage)
	{
		InterfacePtr<const IWidgetParent>	iWidgetParent(this, UseDefaultIID());
		InterfacePtr<const ITreeNodeIDData>	iTreeNodeIDData((ITreeNodeIDData*)iWidgetParent->QueryParentFor(IID_ITREENODEIDDATA));
		if (iTreeNodeIDData)
		{
			NodeID nodeData = iTreeNodeIDData->Get(); 
			TreeNodePtr<TimingPanelTreeNodeID> itemNode(nodeData); 

			InterfacePtr<const ITextControlData> iTextControlData(theSubject, UseDefaultIID());
			PMString newString(iTextControlData->GetString());
			newString.SetTranslatable(kFalse);

			IActiveContext *ac = GetExecutionContextSession()->GetActiveContext();
			IDocument* doc = ac->GetContextDocument();
			UIDRef pageItemRef = Utils<Facade::IDynamicTargetsFacade> ()->GetTargetPageItemRef (UIDRef (::GetDataBase (doc), itemNode->GetUID ()));

			Utils<Facade::IPageItemNameFacade>()->SetUserAssignedPageItemName(pageItemRef,newString);	
		}
	}

	InLineEditObserver::Update(theChange, theSubject, protocol, changedBy);
}


//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/showhide/FieldsNodeObserver.cpp $
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

#include "ISession.h"
#include "IWidgetParent.h"
#include "IWidgetUtils.h"
#include "ITriStateControlData.h"
#include "IShowHideFieldActionData.h"
#include "ISubject.h"
#include "IControlView.h"
#include "ITreeNodeIDData.h"
#include "IFieldsTreeViewAdapter.h"

// ----- Implementation Includes -----

#include "CWidgetObserver.h"
#include "BehaviorUIID.h"
#include "BehaviorID.h"
#include "widgetid.h"
#include "Utils.h"
#include "IntNodeID.h"

//========================================================================================
// CLASS FieldsNodeObserver
//========================================================================================

class FieldsNodeObserver : public CWidgetObserver
{
public:
	FieldsNodeObserver(IPMUnknown *boss);
	virtual ~FieldsNodeObserver();
	
	virtual void AutoAttach();
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);

private:
	void SetAction(const IShowHideFieldActionData::Action& action);
};

//========================================================================================
// METHODS FieldsNodeObserver
//========================================================================================

CREATE_PMINTERFACE(FieldsNodeObserver, kFieldsNodeObserverImpl)

//----------------------------------------------------------------------------------------
// FieldsNodeObserver constructor 
//----------------------------------------------------------------------------------------

FieldsNodeObserver::FieldsNodeObserver(IPMUnknown *boss) :
	CWidgetObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// FieldsNodeObserver::~FieldsNodeObserver: 
//----------------------------------------------------------------------------------------

FieldsNodeObserver::~FieldsNodeObserver()
{
}


//----------------------------------------------------------------------------------------
// FieldsNodeObserver::AutoAttach: 
//----------------------------------------------------------------------------------------

void FieldsNodeObserver::AutoAttach()
{
	AttachToWidget(kSHShowOnOffButtonWidgetID, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// FieldsNodeObserver::AutoDetach: 
//----------------------------------------------------------------------------------------

void FieldsNodeObserver::AutoDetach()
{
	DetachFromWidget(kSHShowOnOffButtonWidgetID, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// FieldsNodeObserver::Update: 
//----------------------------------------------------------------------------------------

void FieldsNodeObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	InterfacePtr<IControlView> view(theSubject, UseDefaultIID());
	if (view && view->GetWidgetID() == kSHShowOnOffButtonWidgetID && theChange == kTrueStateMessage)
	{
		SetAction(IShowHideFieldActionData::kShow);		
	}
	else if (view && view->GetWidgetID() == kSHShowOnOffButtonWidgetID && theChange == kFalseStateMessage)
	{
		SetAction(IShowHideFieldActionData::kHide);
	}
	else if (view && view->GetWidgetID() == kSHShowOnOffButtonWidgetID && theChange == kUnknownStateMessage)
	{
		SetAction(IShowHideFieldActionData::kNone);
	}
}

//----------------------------------------------------------------------------------------
// FieldsNodeObserver::SetAction: 
//----------------------------------------------------------------------------------------

void FieldsNodeObserver::SetAction(const IShowHideFieldActionData::Action& action)
{
	InterfacePtr<IFieldsTreeViewAdapter> adapter((IFieldsTreeViewAdapter *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kSHFieldsWidgetID, IID_ITREEVIEWHIERARCHYADAPTER));

	InterfacePtr<ITreeNodeIDData> treeNodeData(this, UseDefaultIID());
	adapter->SetAction(treeNodeData->Get(), action);
	
	InterfacePtr<ISubject> iSubject(adapter, UseDefaultIID());
	if ( iSubject )
		iSubject->Change(::GetClass(this), IID_ITREEVIEWCONTROLLER, this);
}



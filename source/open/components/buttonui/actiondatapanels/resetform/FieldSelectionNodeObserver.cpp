//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/resetform/FieldSelectionNodeObserver.cpp $
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
#include "IWidgetUtils.h"
#include "ISubject.h"
#include "IControlView.h"
#include "ITreeNodeIDData.h"
#include "IFieldSelectionTreeViewAdptr.h"

// ----- Implementation Includes -----

#include "CWidgetObserver.h"
#include "BehaviorUIID.h"
#include "BehaviorID.h"
#include "widgetid.h"
#include "Utils.h"
#include "IntNodeID.h"

//========================================================================================
// CLASS FieldSelectionNodeObserver
//========================================================================================

class FieldSelectionNodeObserver : public CWidgetObserver
{
public:
	FieldSelectionNodeObserver(IPMUnknown *boss);
	virtual ~FieldSelectionNodeObserver();
	
	virtual void AutoAttach();
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);

private:
	void SetSelected(const bool16& action);
};

//========================================================================================
// METHODS FieldSelectionNodeObserver
//========================================================================================

CREATE_PMINTERFACE(FieldSelectionNodeObserver, kFieldSelectionNodeObserverImpl)

//----------------------------------------------------------------------------------------
// FieldSelectionNodeObserver constructor 
//----------------------------------------------------------------------------------------

FieldSelectionNodeObserver::FieldSelectionNodeObserver(IPMUnknown *boss) :
	CWidgetObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// FieldSelectionNodeObserver::~FieldSelectionNodeObserver: 
//----------------------------------------------------------------------------------------

FieldSelectionNodeObserver::~FieldSelectionNodeObserver()
{
}


//----------------------------------------------------------------------------------------
// FieldSelectionNodeObserver::AutoAttach: 
//----------------------------------------------------------------------------------------

void FieldSelectionNodeObserver::AutoAttach()
{
	AttachToWidget(kSelectedOnOffButtonWidgetID, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// FieldSelectionNodeObserver::AutoDetach: 
//----------------------------------------------------------------------------------------

void FieldSelectionNodeObserver::AutoDetach()
{
	DetachFromWidget(kSelectedOnOffButtonWidgetID, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// FieldSelectionNodeObserver::Update: 
//----------------------------------------------------------------------------------------

void FieldSelectionNodeObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	InterfacePtr<IControlView> view(theSubject, UseDefaultIID());
	if (view && view->GetWidgetID() == kSelectedOnOffButtonWidgetID && theChange == kTrueStateMessage)
		SetSelected(kTrue);
	else if (view && view->GetWidgetID() == kSelectedOnOffButtonWidgetID && theChange == kFalseStateMessage)
		SetSelected(kFalse);
}

//----------------------------------------------------------------------------------------
// FieldSelectionNodeObserver::SetSelected: 
//----------------------------------------------------------------------------------------

void FieldSelectionNodeObserver::SetSelected(const bool16& selected)
{
	InterfacePtr<IFieldSelectionTreeViewAdapter> adapter((IFieldSelectionTreeViewAdapter *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kFieldSelectionWidgetID, IID_ITREEVIEWHIERARCHYADAPTER));

	InterfacePtr<ITreeNodeIDData> treeNodeData(this, UseDefaultIID());
	adapter->SetSelected(treeNodeData->Get(), selected);
}



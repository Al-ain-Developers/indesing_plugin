//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/resetform/FieldSltnButtonObserver.cpp $
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
// CLASS FieldSelectionButtonObserver
//========================================================================================

class FieldSelectionButtonObserver : public CWidgetObserver
{
public:
	FieldSelectionButtonObserver(IPMUnknown *boss);
	virtual ~FieldSelectionButtonObserver();
	
	virtual void AutoAttach();
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
};

//========================================================================================
// METHODS FieldSelectionButtonObserver
//========================================================================================

CREATE_PMINTERFACE(FieldSelectionButtonObserver, kFieldSelectionButtonObserverImpl)

//----------------------------------------------------------------------------------------
// FieldSelectionButtonObserver constructor 
//----------------------------------------------------------------------------------------

FieldSelectionButtonObserver::FieldSelectionButtonObserver(IPMUnknown *boss) :
	CWidgetObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// FieldSelectionButtonObserver::~FieldSelectionButtonObserver: 
//----------------------------------------------------------------------------------------

FieldSelectionButtonObserver::~FieldSelectionButtonObserver()
{
}


//----------------------------------------------------------------------------------------
// FieldSelectionButtonObserver::AutoAttach: 
//----------------------------------------------------------------------------------------

void FieldSelectionButtonObserver::AutoAttach()
{
	AttachToWidget(kSelectAllButtonWidgetID, IID_IBOOLEANCONTROLDATA);
	AttachToWidget(kDeselectAllButtonWidgetID, IID_IBOOLEANCONTROLDATA);
}

//----------------------------------------------------------------------------------------
// FieldSelectionButtonObserver::AutoDetach: 
//----------------------------------------------------------------------------------------

void FieldSelectionButtonObserver::AutoDetach()
{
	DetachFromWidget(kSelectAllButtonWidgetID, IID_IBOOLEANCONTROLDATA);
	DetachFromWidget(kDeselectAllButtonWidgetID, IID_IBOOLEANCONTROLDATA);
}

//----------------------------------------------------------------------------------------
// FieldSelectionButtonObserver::Update: 
//----------------------------------------------------------------------------------------

void FieldSelectionButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	InterfacePtr<IControlView> view(theSubject, UseDefaultIID());
	if (view
		&& (view->GetWidgetID() == kSelectAllButtonWidgetID || view && view->GetWidgetID() == kDeselectAllButtonWidgetID)
		&& theChange == kTrueStateMessage)
	{
		InterfacePtr<IFieldSelectionTreeViewAdapter> adapter((IFieldSelectionTreeViewAdapter *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kFieldSelectionWidgetID, IID_ITREEVIEWHIERARCHYADAPTER));

		K2Vector< K2Pair<UID, bool16> > fields = adapter->Get();
		for (K2Vector< K2Pair<UID, bool16> >::iterator i = fields.begin(); i != fields.end(); i++)
			(*i).second = view->GetWidgetID() == kSelectAllButtonWidgetID;
		adapter->Set(adapter->GetDataBase(), fields);
	}
}



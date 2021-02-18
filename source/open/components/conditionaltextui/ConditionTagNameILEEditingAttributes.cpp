//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionTagNameILEEditingAttributes.cpp $
//  
//  Owner: Michele Stutzman
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

// ----- Interfaces -----

#include "IActiveContext.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewController.h"
#include "IWidgetParent.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "InLineEditEditingAttributes.h"

// ----- Utility files -----

#include "IInCopySharedUtils.h"
#include "Utils.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"


class ConditionTagNameILEEditingAttributes : public InLineEditEditingAttributes
{
public:	
	ConditionTagNameILEEditingAttributes(IPMUnknown *boss);
	~ConditionTagNameILEEditingAttributes();

	virtual bool16 IsEditable() const;

	virtual bool16 IsSelected() const;
	virtual bool16 GetFitEditBoxtoText() const { return kTrue; }
};

// =============================================================================
// *** ConditionTagNameILEEditingAttributes impl ***
// -----------------------------------------------------------------------------

CREATE_PERSIST_PMINTERFACE(ConditionTagNameILEEditingAttributes, kConditionTagNameILEEditingAttributesImpl)

ConditionTagNameILEEditingAttributes::ConditionTagNameILEEditingAttributes(IPMUnknown *boss) :
	InLineEditEditingAttributes(boss)
{
} // end constructor

ConditionTagNameILEEditingAttributes::~ConditionTagNameILEEditingAttributes()
{
} // end destructor

// -----------------------------------------------------------------------------

bool16 ConditionTagNameILEEditingAttributes::IsSelected() const
{
	InterfacePtr<IWidgetParent> ileWidget(this, UseDefaultIID());
	InterfacePtr<IWidgetParent> treeNodeWidget(ileWidget->GetParent(), UseDefaultIID());

	InterfacePtr<ITreeNodeIDData> data(treeNodeWidget, UseDefaultIID());
	NodeID widgetNode = data->Get();

	InterfacePtr<ITreeViewController> treeController((ITreeViewController*)treeNodeWidget->QueryParentFor(IID_ITREEVIEWCONTROLLER));
	if (treeController->IsSelected(data->Get()))
		return kTrue;

	return kFalse;
} // end IsSelected()

// -----------------------------------------------------------------------------

bool16 ConditionTagNameILEEditingAttributes::IsEditable() const
{
	IDataBase* db = ::GetDataBase(GetExecutionContextSession()->GetActiveContext()->GetContextWorkspace());
	return Utils<IInCopySharedUtils>()->StylesEditable(db);
} // end IsEditable()

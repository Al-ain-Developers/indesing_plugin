//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelStateNameILEEditingAttributes.cpp $
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
#include "IDataBase.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewController.h"
#include "IWorkspace.h"
#include "IWidgetParent.h"

// ----- Includes -----

#include "InLineEditEditingAttributes.h"

// ----- Utility files -----

#include "IInCopySharedUtils.h"
#include "Utils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"


class MSOPanelStateNameILEEditingAttributes : public InLineEditEditingAttributes
{
public:	
	MSOPanelStateNameILEEditingAttributes(IPMUnknown *boss);
	~MSOPanelStateNameILEEditingAttributes();

	virtual bool16 IsEditable() const;

	virtual bool16 IsSelected() const;
	virtual bool16 GetFitEditBoxtoText() const { return kTrue; }
};

// =============================================================================
// *** MSOPanelStateNameILEEditingAttributes impl ***
// -----------------------------------------------------------------------------

CREATE_PERSIST_PMINTERFACE(MSOPanelStateNameILEEditingAttributes, kMSOPanelStateNameILEEditingAttributesImpl)

MSOPanelStateNameILEEditingAttributes::MSOPanelStateNameILEEditingAttributes(IPMUnknown *boss) :
	InLineEditEditingAttributes(boss)
{
} // end constructor

MSOPanelStateNameILEEditingAttributes::~MSOPanelStateNameILEEditingAttributes()
{
} // end destructor

// -----------------------------------------------------------------------------

bool16 MSOPanelStateNameILEEditingAttributes::IsSelected() const
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

bool16 MSOPanelStateNameILEEditingAttributes::IsEditable() const
{
	IDataBase* db = ::GetDataBase(GetExecutionContextSession()->GetActiveContext()->GetContextWorkspace());
	return Utils<IInCopySharedUtils>()->StylesEditable(db);
} // end IsEditable()

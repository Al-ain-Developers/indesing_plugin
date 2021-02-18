//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelStateNameILEObserver.cpp $
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

#include "IAppearanceSuite.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITreeNodeIDData.h"
#include "IWidgetParent.h"

// ----- Includes -----

#include "InLineEditObserver.h"
#include "MSOStateNodeID.h"

// ----- Utility files -----

#include "FormFieldUIUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"


class MSOPanelStateNameILEObserver : public InLineEditObserver
{
public:
	MSOPanelStateNameILEObserver(IPMUnknown *boss);
	virtual ~MSOPanelStateNameILEObserver();
		
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);		
	virtual void AutoAttach();			
	virtual void AutoDetach();
};

// =============================================================================
// *** MSOPanelStateNameILEObserver impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(MSOPanelStateNameILEObserver, kMSOPanelStateNameILEObserverImpl)

MSOPanelStateNameILEObserver::MSOPanelStateNameILEObserver(IPMUnknown *boss) :
	InLineEditObserver(boss)
{
} // end constructor

MSOPanelStateNameILEObserver::~MSOPanelStateNameILEObserver()
{
} // end destructor

// -----------------------------------------------------------------------------

void MSOPanelStateNameILEObserver::AutoAttach()
{
	InLineEditObserver::AutoAttach();

	InterfacePtr<ISubject> subjectList( this, IID_ISUBJECT );
	if (subjectList)
		subjectList->AttachObserver(this, IID_ITEXTCONTROLDATA); 
} // end AutoAttach()

// -----------------------------------------------------------------------------

void MSOPanelStateNameILEObserver::AutoDetach()
{
	InterfacePtr<ISubject> subjectList( this, IID_ISUBJECT );
	if (subjectList)
		subjectList->DetachObserver(this, IID_ITEXTCONTROLDATA);

	InLineEditObserver::AutoDetach();
} // end AutoDetach()

// -----------------------------------------------------------------------------

void MSOPanelStateNameILEObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	if (protocol == IID_ITEXTCONTROLDATA && theChange == kTextChangeStateMessage)
	{
		InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
		if (iAppearanceSuite)
		{
			InterfacePtr<IWidgetParent> inLineEditWidget(this, UseDefaultIID());
			InterfacePtr<IWidgetParent> treeNodeWidget(inLineEditWidget->GetParent(), UseDefaultIID());

			InterfacePtr<ITreeNodeIDData> data(treeNodeWidget, UseDefaultIID());
			TreeNodePtr<const MSOStateNodeID> msoStateNode(data->Get());
			if (msoStateNode->GetAppearance() != Form::kStateInvalid)
			{
				InterfacePtr<ITextControlData>	textData(theSubject, UseDefaultIID());
				if (textData && iAppearanceSuite->GetStateName(msoStateNode->GetAppearance()) != textData->GetString())
					iAppearanceSuite->SetStateName(msoStateNode->GetAppearance(), textData->GetString());
			}
		}
	}

	InLineEditObserver::Update(theChange, theSubject, protocol, changedBy);
} // end Update()

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionalTextLayoutObserver.cpp $
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

#include "ILayoutController.h"
#include "ILayoutControlData.h"
#include "ILayoutUIUtils.h"

// ----- Includes -----

#include "CObserver.h"

// ----- Utility files -----


// ----- ID.h files -----

#include "ConditionalTextID.h"
#include "ConditionalTextUIID.h"


class ConditionalTextLayoutObserver : public CObserver
{
public:
	ConditionalTextLayoutObserver(IPMUnknown *boss);
	virtual	~ConditionalTextLayoutObserver();

	// This is attached/detached in the ConditionalTextLayoutAction
	//virtual	void		AutoAttach();
	//virtual	void		AutoDetach();

	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
};

// =============================================================================
// *** ConditionalTextLayoutObserver impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(ConditionalTextLayoutObserver, kConditionalTextLayoutObserverImpl)

ConditionalTextLayoutObserver::ConditionalTextLayoutObserver(IPMUnknown *boss) :
	CObserver(boss)
{
} // end constructor

ConditionalTextLayoutObserver::~ConditionalTextLayoutObserver()
{
} // end destructor

//----------------------------------------------------------------------------------------

void ConditionalTextLayoutObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	ICommand *cmd = (ICommand *)changedBy;
	if (cmd && cmd->GetCommandState() == ICommand::kDone)
	{
		if (protocol == IID_ICONDITIONALTEXTOPTIONS && theChange == kShowConditionIndicatorsCmdBoss)
		{
			// Invalidate the screen because the conditional text indicators have changed.
			InterfacePtr<ILayoutController> iLayoutController(this, IID_ILAYOUTCONTROLLER);
			if (iLayoutController)
				iLayoutController->InvalidateContent();
			InterfacePtr<ILayoutControlData> iLayoutControlData(this,UseDefaultIID());
			Utils<ILayoutUIUtils>()->InvalidateShapeGraphixCache(iLayoutControlData->GetDocument());
		}
		else if (protocol == IID_ICONDITIONTAGLIST && 
			(theChange == kConditionTagEditColorCmdBoss || theChange == kConditionTagEditMethodCmdBoss || 
				theChange == kConditionTagEditAppearanceCmdBoss || theChange == kConditionTagEditOptionsCmdBoss))
		{
			// Invalidate the screen because the conditional text indicators have changed.
			InterfacePtr<ILayoutController> iLayoutController(this, IID_ILAYOUTCONTROLLER);
			if (iLayoutController)
				iLayoutController->InvalidateContent();
			InterfacePtr<ILayoutControlData> iLayoutControlData(this,UseDefaultIID());
			Utils<ILayoutUIUtils>()->InvalidateShapeGraphixCache(iLayoutControlData->GetDocument());
		}
	}
} // end Update()
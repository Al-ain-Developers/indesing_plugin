//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/linkwatcher/LnkWtchActionComponent.cpp $
//  
//  Owner: Adobe Developer Technologies
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


// Interface includes:
#include "IWidgetUtils.h"
#include "IPanelControlData.h"
#include "IControlView.h"
#include "IActionStateList.h"
#include "IActiveContext.h"
#include "IDocument.h"

// General includes:
#include "Utils.h"
#include "CActionComponent.h"
#include "CAlert.h"

// Project includes:
#include "LnkWtchID.h"
#include "ILnkWtchCache.h"


/**  Implements an action component, IActionComponent, defining the actions 
	that are executed when this plug-in's menu items are chosen.

	@ingroup linkwatcher
*/
class LnkWtchActionComponent : public CActionComponent
{
public:
	/** Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	LnkWtchActionComponent(IPMUnknown* boss);

	/**	 Called by the framework when the action is to be performed.
			@param myContext context in which the action is to be performed.
			@param actionID identifies the action to be performed.
			@param mousePoint ontains the global mouse location at time of event causing action (e.g. context menus), kInvalidMousePoint otherwise.
			@param widget the widget that invoked the action or nil otherwise
	*/
	virtual void DoAction(IActiveContext *myContext, ActionID actionID, GSysPoint mousePoint, IPMUnknown *widget);

private:
	/** Encapsulates functionality for the about menu item. */
	void DoAbout();
};

/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its
ImplementationID making the C++ code callable by the
application.
*/
CREATE_PMINTERFACE(LnkWtchActionComponent, kLnkWtchActionComponentImpl)

/* LnkWtchActionComponent Constructor
*/
LnkWtchActionComponent::LnkWtchActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/*
*/
void LnkWtchActionComponent::DoAction(IActiveContext *myContext, ActionID actionID, GSysPoint mousePoint, IPMUnknown *widget)
{
	switch (actionID.Get())
	{
	case kLnkWtchPopupAboutThisActionID:
		{
			this->DoAbout();
			break;
		}

	default:
		{
			break;
		}
	}
}



/*
*/
void LnkWtchActionComponent::DoAbout()
{
	CAlert::ModalAlert
		(
		kLnkWtchAboutBoxStringKey,			// Alert string
		kOKString, 							// OK button
		kNullString, 						// No second button
		kNullString, 						// No third button
		1,									// Set OK button to default
		CAlert::eInformationIcon				// Information icon.
		);
}


// End, LnkWtchActionComponent.cpp.



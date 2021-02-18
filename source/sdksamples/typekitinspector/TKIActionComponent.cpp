//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/typekitinspector/TKIActionComponent.cpp $
//  
//  Owner: Timothy Brand-Spencer
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"
#include "CActionComponent.h"
#include "CAlert.h"
#include "TKIID.h"

/** Implements IActionComponent; performs the actions that are executed when the plug-in's
	menu items are selected.

	@ingroup typekitinspector
*/
class TKIActionComponent : public CActionComponent
{
public:
		TKIActionComponent(IPMUnknown* boss);
		virtual void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
private:
		void DoAbout();
};

CREATE_PMINTERFACE(TKIActionComponent, kTKIActionComponentImpl)

TKIActionComponent::TKIActionComponent(IPMUnknown* boss) : CActionComponent(boss)
{
}

void TKIActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kTKIPopupAboutThisActionID:
		case kTKIAboutActionID:
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

void TKIActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
		kTKIAboutBoxStringKey,
		kOKString,
		kNullString,
		kNullString,
		1,
		CAlert::eInformationIcon
	);
}
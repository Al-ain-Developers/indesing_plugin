//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hidpi/HiDPIActionComponent.cpp $
//  
//  Owner: Neelabh Sunny
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
#include "CActionComponent.h"
#include "CAlert.h"
#include "HiDPIID.h"

class HiDPIActionComponent : public CActionComponent
{
	public:
		HiDPIActionComponent(IPMUnknown* boss);
		void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil);

	private:
		void DoAbout();
};

CREATE_PMINTERFACE(HiDPIActionComponent, kHiDPIActionComponentImpl)

HiDPIActionComponent::HiDPIActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

void HiDPIActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kHiDPIPopupAboutThisActionID:
		case kHiDPIAboutActionID:
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

void HiDPIActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
		kHiDPIAboutBoxStringKey,		// Alert string
		kOKString, 						// OK button
		kNullString, 					// No second button
		kNullString, 					// No third button
		1,								// Set OK button to default
		CAlert::eInformationIcon		// Information icon.
	);
}
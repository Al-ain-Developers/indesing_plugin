//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/editbehaviordlg/HolderPanelControlData.cpp $
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

#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "IBehaviorDataPanel.h"
#include "IControlView.h"
#include "ISession.h"

// ----- Implementation Includes -----

#include "DVPanelControlData.h"
#include "BehaviorUIID.h"
#include "BehaviorID.h"
#include "LocaleSetting.h"

//========================================================================================
// CLASS HolderPanelControlData
//========================================================================================

class HolderPanelControlData : public DVPanelControlData
{
public:
	typedef DVPanelControlData inherited;

	HolderPanelControlData(IPMUnknown *boss);
	virtual ~HolderPanelControlData();
	
	virtual void ReadWrite(IPMStream *s, ImplementationID prop);
};

//========================================================================================
// METHODS HolderPanelControlData
//========================================================================================

CREATE_PERSIST_PMINTERFACE(HolderPanelControlData, kHolderPanelControlDataImpl)

//----------------------------------------------------------------------------------------
// HolderPanelControlData constructor 
//----------------------------------------------------------------------------------------

HolderPanelControlData::HolderPanelControlData(IPMUnknown *boss) :
	inherited(boss)
{
}

//----------------------------------------------------------------------------------------
// HolderPanelControlData::~HolderPanelControlData
//----------------------------------------------------------------------------------------

HolderPanelControlData::~HolderPanelControlData()
{
}

//----------------------------------------------------------------------------------------
// HolderPanelControlData::ReadWrite
//----------------------------------------------------------------------------------------

void HolderPanelControlData::ReadWrite(IPMStream *s, ImplementationID prop)
{
	inherited::ReadWrite(s, prop);

	// ----- The first time that we read in this panel, that is from resource, the number
	//		 of widgets should be 0. If 0 then we load the action data panels from the
	//		 factory serive. After that they are all persisted in saved data.
	
	if (Length() == 0)
	{
		InterfacePtr<IK2ServiceRegistry> servReg(GetExecutionContextSession(), UseDefaultIID());
		int32 serviceCount = servReg->GetServiceProviderCount(kBehaviorService);
		for(int32 serviceIndex = 0; serviceIndex < serviceCount; serviceIndex++)
		{
			InterfacePtr<IK2ServiceProvider> provider(servReg->QueryNthServiceProvider(kBehaviorService, serviceIndex));
			InterfacePtr<IBehaviorDataPanel> behaviorDataPanel(provider, UseDefaultIID());
			if (behaviorDataPanel)
			{
				InterfacePtr<IControlView> widget(static_cast<IControlView*>(behaviorDataPanel->CreatePanel(LocaleSetting::GetLocale(), IID_ICONTROLVIEW)));
				widget->HideView();
				AddToWidgetList(widget);
			}
		}
	}
}


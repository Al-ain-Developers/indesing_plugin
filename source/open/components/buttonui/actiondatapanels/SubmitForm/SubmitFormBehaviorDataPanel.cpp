//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/SubmitForm/SubmitFormBehaviorDataPanel.cpp $
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
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2001 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interface Includes -----

#include "IBehaviorDataPanel.h"
#include "IControlView.h"
#include "ISession.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "BehaviorUIDefs.h"
#include "CPMUnknown.h"
#include "CoreResTypes.h"
#include "CreateObject.h"
#include "RsrcSpec.h"

//========================================================================================
// CLASS SubmitFormBehaviorDataPanel
//========================================================================================

class SubmitFormBehaviorDataPanel : public CPMUnknown<IBehaviorDataPanel>
{
public:
	SubmitFormBehaviorDataPanel(IPMUnknown *boss);
	virtual ~SubmitFormBehaviorDataPanel();

	virtual IPMUnknown* CreatePanel(const PMLocaleId& localeId, const PMIID& iid) const;
};	

//========================================================================================
// METHODS SubmitFormBehaviorDataPanel
//========================================================================================

CREATE_PMINTERFACE(SubmitFormBehaviorDataPanel, kSubmitFormBehaviorDataPanelImpl)

//----------------------------------------------------------------------------------------
// SubmitFormBehaviorDataPanel::SubmitFormBehaviorDataPanel
//----------------------------------------------------------------------------------------

SubmitFormBehaviorDataPanel::SubmitFormBehaviorDataPanel(IPMUnknown *boss) :
	CPMUnknown<IBehaviorDataPanel>(boss)
{
}

//----------------------------------------------------------------------------------------
// SubmitFormBehaviorDataPanel::~SubmitFormBehaviorDataPanel
//----------------------------------------------------------------------------------------

SubmitFormBehaviorDataPanel::~SubmitFormBehaviorDataPanel()
{
}

//----------------------------------------------------------------------------------------
// SubmitFormBehaviorDataPanel::CreatePanel
//----------------------------------------------------------------------------------------

IPMUnknown* SubmitFormBehaviorDataPanel::CreatePanel(const PMLocaleId& localeId, const PMIID& iid) const
{
	return ::CreateObject(::GetDataBase(GetExecutionContextSession()),
						  RsrcSpec(localeId, kBehaviorUIPluginID, kViewRsrcType, kSubmitFormPanelRsrcID),
						  IID_ICONTROLVIEW);
}

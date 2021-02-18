//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/gotopos/GoToPreviousPageDataPanel.cpp $
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

#include "IBehaviorDataPanel.h"
#include "ISession.h"
#include "IControlView.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "FormFieldUIID.h"
#include "BehaviorUIDefs.h"
#include "CPMUnknown.h"
#include "CreateObject.h"
#include "CoreResTypes.h"
#include "DVUtilities.h"
#include "RsrcSpec.h"

//========================================================================================
// CLASS GoToPreviousPageDataPanel
//========================================================================================

class GoToPreviousPageDataPanel : public CPMUnknown<IBehaviorDataPanel>
{
public:
	GoToPreviousPageDataPanel(IPMUnknown *boss);
	virtual ~GoToPreviousPageDataPanel();

	virtual IPMUnknown* CreatePanel(const PMLocaleId& localeId, const PMIID& iid) const;
};	

//========================================================================================
// METHODS GoToPreviousPageDataPanel
//========================================================================================

CREATE_PMINTERFACE(GoToPreviousPageDataPanel, kGoToPreviousPageDataPanelImpl)

//----------------------------------------------------------------------------------------
// GoToPreviousPageDataPanel::GoToPreviousPageDataPanel
//----------------------------------------------------------------------------------------

GoToPreviousPageDataPanel::GoToPreviousPageDataPanel(IPMUnknown *boss) :
	CPMUnknown<IBehaviorDataPanel>(boss)
{
}

//----------------------------------------------------------------------------------------
// GoToPreviousPageDataPanel::~GoToPreviousPageDataPanel
//----------------------------------------------------------------------------------------

GoToPreviousPageDataPanel::~GoToPreviousPageDataPanel()
{
}

//----------------------------------------------------------------------------------------
// GoToPreviousPageDataPanel::CreatePanel
//----------------------------------------------------------------------------------------

IPMUnknown* GoToPreviousPageDataPanel::CreatePanel(const PMLocaleId& localeId, const PMIID& iid) const
{
	/* degupta - CreateObject is creating the controlview and also calling the DoPostCreate(), breaking this into 
	 * CreateObjectNoInit() and DoPostCreate() so that theme can be set on the view before DoPostCreate() is called.
	 */
	IPMUnknown *returnVal = ::CreateObjectNoInit (::GetDataBase(GetExecutionContextSession()),
		RsrcSpec(localeId, kFormFieldUIPluginID, kViewRsrcType, kGoToPreviousPagePanelRsrcID),
		IID_ICONTROLVIEW,
		GetObjectModelInstance());
	ASSERT_MSG(returnVal, "Cannot create the appropriate control view.");
	IControlView* panel = InterfacePtr<IControlView>(returnVal, UseDefaultIID());
	ASSERT_MSG(panel, "Cannot create the appropriate control view.");
	// Set the drover theme on the Panel View and call the DoPostCreate()
	if(panel)
	{
		dv_utils::SetThemeForView(panel, dv_utils::kIDPanelTheme);
		panel->DoPostCreate();
	}
	return panel;
}

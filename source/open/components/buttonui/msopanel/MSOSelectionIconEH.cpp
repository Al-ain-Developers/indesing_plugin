//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOSelectionIconEH.cpp $
//  
//  Owner: Tom Taylor
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
#include "IControlView.h"

// ----- Includes -----

#include "ActionStateList.h"
#include "DVHostedWidgetEH.h"
#include "FormFieldUIDefs.h"

// ----- Utility files -----

#include "EventUtilities.h"
#include "FormFieldUIUtils.h"
#include "MSOPanelUtils.h"
#include "IPalettePanelUtils.h"
#include "UserInterfaceUtils.h"

// ----- ID.h files -----

#include "widgetid.h"
#include "FormFieldUIID.h"

class MSOSelectionIconEH : public DVHostedWidgetEH
{
public:
	typedef DVHostedWidgetEH inherited;

	MSOSelectionIconEH(IPMUnknown *boss);
	virtual ~MSOSelectionIconEH();

	virtual bool16 LButtonDn(IEvent* e);
};

// =============================================================================
// *** MSOSelectionIconEH impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(MSOSelectionIconEH, kMSOSelectionIconEHImpl)

MSOSelectionIconEH::MSOSelectionIconEH(IPMUnknown *boss) :
	inherited(boss)
{
} // end constructor

MSOSelectionIconEH::~MSOSelectionIconEH()
{
} // end destructor

// -----------------------------------------------------------------------------

bool16 MSOSelectionIconEH::LButtonDn(IEvent* e)
{
	bool16 result = kFalse;

	// If the MSO selection icon is the "not" selected icon then perform the 
	// action to select the MSO.

	InterfacePtr<IControlView> myView(this, IID_ICONTROLVIEW);
	if (myView && myView->IsVisible() && myView->GetRsrcID() == kMSOIsNotSelectedIconRsrcID)
	{
		InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
		if (iAppearanceSuite)
		{
			MSOPanelUtils::AcceptMSONameIfNeeded(iAppearanceSuite);
			return iAppearanceSuite->SelectAssociatedAppearanceItemOfType(kMultiStateObjectItemBoss) == kSuccess;
		}
	}

	return result;
} // end LButtonDn()

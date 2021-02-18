//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelPointyHandCursorProvider.cpp $
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

#include "IControlView.h"
#include "IPanelControlData.h"

// ----- Includes -----

#include "CCursorProvider.h"
#include "FormFieldUIDefs.h"

// ----- Utility files -----


// ----- ID.h files -----

#include "AppUIID.h"
#include "CursorID.h"
#include "FormFieldUIID.h"


class MSOPanelPointyHandCursorProvider : public CCursorProvider
{
	public:
		MSOPanelPointyHandCursorProvider(IPMUnknown* boss);
		~MSOPanelPointyHandCursorProvider();
		
		virtual CursorSpec GetCursor(IControlView* viewUnderMouse, const SysPoint globalLocation, ICursorMgr::eCursorModifierState modifiers) const;
		virtual bool16 LocationAffectsCursor(SysRgn cursorRgn) const;
		virtual bool16 HasLockedState() const;
};

// =============================================================================
// *** MSOPanelPointyHandCursorProvider impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(MSOPanelPointyHandCursorProvider, kMSOPanelPointyHandCursorProviderImpl)

MSOPanelPointyHandCursorProvider::MSOPanelPointyHandCursorProvider(IPMUnknown *boss) :
	CCursorProvider(boss)
{
} // end constructor

MSOPanelPointyHandCursorProvider::~MSOPanelPointyHandCursorProvider()
{
} // end destructor

// -----------------------------------------------------------------------------

CursorSpec	MSOPanelPointyHandCursorProvider::GetCursor(IControlView* viewUnderMouse, const SysPoint globalLocation, ICursorMgr::eCursorModifierState ) const
{
	if (viewUnderMouse)
	{
		switch (viewUnderMouse->GetWidgetID().Get())
		{
		case kMSOSelectionIconWidgetID:
			{
				if (viewUnderMouse->IsVisible() && viewUnderMouse->GetRsrcID() == kMSOIsNotSelectedIconRsrcID)
					return CursorSpec(kAppUIPluginID, kCrsrPointyHand);
			}
		}
	}

	return CursorSpec(kCrsrPointer);
}

// -----------------------------------------------------------------------------

bool16 MSOPanelPointyHandCursorProvider::LocationAffectsCursor(SysRgn cursorRgn) const
{
	return kTrue;
}

// -----------------------------------------------------------------------------

bool16	MSOPanelPointyHandCursorProvider::HasLockedState() const
{
	return kFalse;
}


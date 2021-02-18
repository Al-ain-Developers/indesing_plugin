//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/PointyHandCursorProvider.cpp $
//  
//  Owner: ???
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
//  
//  Provides cursors for the layer panel. Proxy widget, eye, pencil.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interfaces:
#include "IBoolData.h"
#include "IControlView.h"
#include "IPanelControlData.h"

// Includes:
#include "CCursorProvider.h"
#include "HelperInterface.h"
#include "LayerPanelDefs.h"

// Utility files:
//#include "LayerPanelUtils.h"
//#include "IPalettePanelUtils.h"

// ID.h files:
#include "AppUIID.h"
#include "CursorID.h"
#include "LayerPanelID.h"

class PointyHandCursorProvider : public CCursorProvider
{
	public:
		PointyHandCursorProvider(IPMUnknown* boss);
		~PointyHandCursorProvider();
		
		virtual CursorSpec	GetCursor(IControlView* viewUnderMouse, const SysPoint globalLocation, ICursorMgr::eCursorModifierState modifiers) const;
		virtual bool16	LocationAffectsCursor(SysRgn cursorRgn) const;
		virtual bool16	HasLockedState() const;
	private:
		
		DECLARE_HELPER_METHODS()
};

//========================================================================
// Class PointyHandCursorProvider
//========================================================================
CREATE_PMINTERFACE(PointyHandCursorProvider, kPointyHandCursorProviderImpl)
DEFINE_HELPER_METHODS(PointyHandCursorProvider)

PointyHandCursorProvider::PointyHandCursorProvider(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss),
	CCursorProvider(boss)
{
}

PointyHandCursorProvider::~PointyHandCursorProvider()
{
}

//--------------------------------------------------------------------------------------
// GetCursor
//--------------------------------------------------------------------------------------
CursorSpec	PointyHandCursorProvider::GetCursor(IControlView* viewUnderMouse, const SysPoint globalLocation, ICursorMgr::eCursorModifierState ) const
{
	if(viewUnderMouse)
	{
		switch(viewUnderMouse->GetWidgetID().Get())
		{
			case kPageItemSelectionProxyWidgetID:
			case kLayerListElementProxyWidgetID:
			case kLayerListElementEyeballWidgetID:
			case kLayerListElementPencilWidgetID:
			case kLayerPageItemElementPencilWidgetID:
			{
				return CursorSpec(kAppUIPluginID, kCrsrPointyHand);
			}
		}
	}

	return CursorSpec(kCrsrPointer);
}

//--------------------------------------------------------------------------------------
// LocationAffectsCursor - Cursor changes within the layer panel depending on whether
//						   cursor is over eyeball, panel, or a proxy widget.
//--------------------------------------------------------------------------------------
bool16 PointyHandCursorProvider::LocationAffectsCursor(SysRgn ) const
{
	return kTrue;
}

//--------------------------------------------------------------------------------------
// HasLockedState
//--------------------------------------------------------------------------------------
bool16	PointyHandCursorProvider::HasLockedState() const
{
	return kFalse;	// No locked state for the layer panel
}


//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/TimingPanelCursorProvider.cpp $
//  
//  Owner: Yeming Liu
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

// ----- Interface files -----

#include "IControlView.h"
#include "IPanelControlData.h"
#include "ITreeNodeIDData.h"
#include "IWidgetParent.h"

// ----- Include files -----

#include "CCursorProvider.h"
#include "TimingPanelTreeNodeID.h"

// ----- ID files -----

#include "AppUIID.h"
#include "CursorID.h"
#include "DynamicDocumentsUIID.h"

class TimingPanelCursorProvider : public CCursorProvider
{
	public:
		TimingPanelCursorProvider(IPMUnknown* boss) : CCursorProvider(boss) { }
		~TimingPanelCursorProvider() { }
		
		virtual CursorSpec	GetCursor(IControlView* viewUnderMouse, const SysPoint globalLocation, ICursorMgr::eCursorModifierState modifiers) const;

		virtual bool16	LocationAffectsCursor(SysRgn cursorRgn) const { return kTrue; }

		virtual bool16	HasLockedState() const { return kFalse; } // No locked state for the timing panel
};

CREATE_PMINTERFACE(TimingPanelCursorProvider, kTimingPanelCursorProviderImpl)

CursorSpec TimingPanelCursorProvider::GetCursor(IControlView* viewUnderMouse, const SysPoint globalLocation, ICursorMgr::eCursorModifierState ) const
{
	if (viewUnderMouse)
	{
		switch(viewUnderMouse->GetWidgetID().Get())
		{
			case kTimingPanelTreeNodeGroupWidgetID:
			{
				InterfacePtr<IWidgetParent>	iWidgetParent(viewUnderMouse, UseDefaultIID());
				InterfacePtr<ITreeNodeIDData> iHolderData(iWidgetParent->GetParent(), UseDefaultIID());
				if (iHolderData)
				{
					NodeID nodeIDHolder = iHolderData->Get();	
					TreeNodePtr<TimingPanelTreeNodeID> itemNode(nodeIDHolder);
					if (itemNode && itemNode->IsGroupItem())
						return CursorSpec(kAppUIPluginID, kCrsrPointyHand);
				}
			}
		}
	}

	return CursorSpec(kCrsrPointer);
}

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUITreePanelControlData.cpp $
//  
//  Owner: lance bushore
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
#include "DVPanelControlData.h"

// ----- Interface Includes -----

#include "IControlView.h"
#include "IWidgetUtils.h"
#include "IWidgetParent.h"
#include "IWindow.h"

// ----- Implementation Includes -----

#include "LinksUIID.h"

//========================================================================================
// CLASS LinksUITreePanelControlData
//========================================================================================

class LinksUITreePanelControlData : public DVPanelControlData
{
	typedef DVPanelControlData inherited;
public:
	// ----- Initialization -----
	
	LinksUITreePanelControlData(IPMUnknown *boss);
	virtual ~LinksUITreePanelControlData();

	// ----- Maintenance -----
	
	virtual void			WidgetAttributeChanged(IControlView* view, const WidgetAttributeID& id);
};

//========================================================================================
// METHODS LinksUITreePanelControlData
//========================================================================================

CREATE_PERSIST_PMINTERFACE(LinksUITreePanelControlData, kLinksUITreePanelControlDataImpl)

LinksUITreePanelControlData::LinksUITreePanelControlData(IPMUnknown *boss)  :
	inherited(boss)
{
}

LinksUITreePanelControlData::~LinksUITreePanelControlData()
{
}

void LinksUITreePanelControlData::WidgetAttributeChanged(IControlView* view, const WidgetAttributeID& id)
{
	inherited::WidgetAttributeChanged(view,id);
	if(id == kWidgetPosition && view->GetWidgetID() == kTreeScrollerWidgetID)
	{
		PMRect newTreeFrame = view->GetFrame();
		InterfacePtr<IControlView> headerWidget((IControlView*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinksUIColumnHeaderRowWidgetID,IID_ICONTROLVIEW));
				
		PMRect olderHeaderFrame = headerWidget->GetFrame();
		if(olderHeaderFrame.Left() != newTreeFrame.Left())
		{
			headerWidget->MoveTo(PMPoint(newTreeFrame.Left(),olderHeaderFrame.Top()));
					
			// now we want to force this area of the window to redraw.		
			headerWidget->ForceRedraw();

		}
	}
}

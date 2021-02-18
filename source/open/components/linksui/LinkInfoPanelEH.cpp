//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinkInfoPanelEH.cpp $
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

//interface includes
#include "IActionManager.h"
#include "IApplication.h"
#include "IEvent.h"
#include "IMenuManager.h"
#include "IPanorama.h"
#include "IWidgetUtils.h"
#include "IControlView.h"

//includes
#include "DVHostedWidgetEH.h"
#include "LinksUIID.h"

class  LinkInfoPanelEH : public DVHostedWidgetEH
{
public:
	typedef DVHostedWidgetEH inherited;

	LinkInfoPanelEH(IPMUnknown* boss) : inherited(boss)
		{}
	virtual ~LinkInfoPanelEH()
		{}
	
	virtual bool16 RButtonDn(IEvent* e);
	virtual bool16 MouseWheel(IEvent *e);
};


CREATE_PMINTERFACE(LinkInfoPanelEH, kLinkInfoPanelEHImpl)


bool16 LinkInfoPanelEH::RButtonDn(IEvent* e)
{
	InterfacePtr<const IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<const IActionManager> actionMgr(theApp->QueryActionManager());
	InterfacePtr<IMenuManager> menuMgr(actionMgr, UseDefaultIID());
	
	menuMgr->HandlePopupMenu("RtMenuLinksUILinkInfo", e->GlobalWhere(), e->GlobalWhere(), kTrue, this);
	return kTrue;
}

bool16 LinkInfoPanelEH::MouseWheel(IEvent *e)
{
	InterfacePtr<const IControlView> scrollbarView((IControlView*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinkInfoSectionScrollBarWidgetID,IID_ICONTROLVIEW));
	if(scrollbarView && scrollbarView->IsEnabled())
	{
		PMPoint delta = e->GetMouseScrollDelta();
		InterfacePtr<IPanorama> panelPanorama(this,UseDefaultIID());
		PMPoint scrollbyPoint(0,0);
		int32 multiplier = e->ShiftKeyDown() ? -20 * 5 : -20;
		scrollbyPoint.X() = 0; 
		scrollbyPoint.Y() = delta.Y() * multiplier; 

		TRACEFLOW("Links:LinksUI","LinkInfoPanelEH::MouseWheel. scrollbyPoint.Y is %d, deltaY is %d. \n", ::ToInt32(scrollbyPoint.Y()),::ToInt32(delta.Y()));
		panelPanorama->ScrollBy(scrollbyPoint);
	}
	return kTrue;
}


//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUITreeRowPanelEH.cpp $
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

//includes
#include "TreeNodeEventHandler.h"
#include "LinksUIID.h"

class  LinksUITreeRowPanelEH : public TreeNodeEventHandler
{
public:
	typedef TreeNodeEventHandler Inherited;

	LinksUITreeRowPanelEH(IPMUnknown* boss) : Inherited(boss)
		{}
	virtual ~LinksUITreeRowPanelEH()
		{}
	
	virtual bool16 RButtonDn(IEvent* e);
};


CREATE_PMINTERFACE(LinksUITreeRowPanelEH, kLinksUITreeRowPanelEHImpl)


bool16 LinksUITreeRowPanelEH::RButtonDn(IEvent* e)
{
	InterfacePtr<const IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<const IActionManager> actionMgr(theApp->QueryActionManager());
	InterfacePtr<IMenuManager> menuMgr(actionMgr, UseDefaultIID());
	
	menuMgr->HandlePopupMenu("RtMenuLinksUILinkItem", e->GlobalWhere(), e->GlobalWhere(), kTrue, this);
	return kTrue;
}



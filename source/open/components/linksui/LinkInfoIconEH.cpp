//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinkInfoIconEH.cpp $
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

#include "IActionManager.h"
#include "IApplication.h"
#include "IMenuManager.h"
#include "ILinkInfoProvider.h"
#include "IEvent.h"
#include "ILink.h"
#include "ILinkResource.h"

//includes
#include "DVHostedWidgetEH.h"
#include "LinksUIID.h"
#include "ILinksUIUtils.h"
#include "Utils.h"

class  LinkInfoIconEH : public DVHostedWidgetEH 
{
public:
	typedef DVHostedWidgetEH Inherited;

	LinkInfoIconEH(IPMUnknown* boss) : Inherited(boss)
		{}
	virtual ~LinkInfoIconEH()
		{}
	
	virtual bool16 MouseDrag(IEvent* e);
	virtual bool16 LButtonDn(IEvent* e);
	virtual bool16 LButtonUp(IEvent* e);
	virtual bool16 RButtonDn(IEvent* e);
	virtual bool16 ButtonDblClk( IEvent* e );
};


CREATE_PMINTERFACE(LinkInfoIconEH, kLinkInfoIconEHImpl)

bool16 LinkInfoIconEH::RButtonDn(IEvent* e)
{
	InterfacePtr<const ILinkInfoProvider> headerProvider(Utils<ILinksUIUtils>()->QueryLinkInfoProviderFromHeaderWidget(this));
	if(headerProvider)
	{
		InterfacePtr<const IApplication> theApp(GetExecutionContextSession()->QueryApplication());
		InterfacePtr<const IActionManager> actionMgr(theApp->QueryActionManager());
		InterfacePtr<IMenuManager> menuMgr(actionMgr, UseDefaultIID());

		menuMgr->HandlePopupMenu("RtMenuLinksUILinksHeader", e->GlobalWhere(), e->GlobalWhere(), kTrue, this);
		return kTrue;
	}
	return kFalse;
}

bool16 LinkInfoIconEH::LButtonDn( IEvent* e )
{
#pragma unused(e)

	InterfacePtr<const ILink> theLink(Utils<ILinksUIUtils>()->QueryLinkFromLinksUIWidget(this));
	InterfacePtr<const ILinkResource> theLinkResource(Utils<ILinksUIUtils>()->QueryLinkResourceFromLinksUIWidget(this));
	InterfacePtr<ILinkInfoProvider> infoProvider(Utils<ILinksUIUtils>()-> QueryInfoProviderFromLinksUIWidget(this));

	if(infoProvider && (theLink || theLinkResource))
	{
		if(infoProvider->CanDoSingleClickAction(theLink,theLinkResource))
		{
			infoProvider->DoSingleClickAction(theLink,theLinkResource);
			return true;
		}
	}

	e->SetUI_DoEventHandledState(IEvent::kDontCall);
	return false;
}

bool16 LinkInfoIconEH::ButtonDblClk( IEvent* e )
{
#pragma unused(e)

	InterfacePtr<const ILink> theLink(Utils<ILinksUIUtils>()->QueryLinkFromLinksUIWidget(this));
	InterfacePtr<const ILinkResource> theLinkResource(Utils<ILinksUIUtils>()->QueryLinkResourceFromLinksUIWidget(this));
	InterfacePtr<ILinkInfoProvider> infoProvider(Utils<ILinksUIUtils>()-> QueryInfoProviderFromLinksUIWidget(this));

	if(infoProvider && (theLink || theLinkResource))
	{
		if(infoProvider->CanDoDoubleClickAction(theLink,theLinkResource))
			infoProvider->DoDoubleClickAction(theLink,theLinkResource);
	}
	return true;
}

bool16 LinkInfoIconEH::LButtonUp(IEvent* e)
{
	bool16 bRetVal = kFalse;

	e->SetUI_DoEventHandledState(IEvent::kDontCall);
	return bRetVal;
}

bool16 LinkInfoIconEH::MouseDrag(IEvent* e)
{
	bool16 bRetVal = kFalse;

	e->SetUI_DoEventHandledState(IEvent::kDontCall);
	return bRetVal;
}

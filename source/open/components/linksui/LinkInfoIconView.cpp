//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinkInfoIconView.cpp $
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

#include "ILink.h"
#include "ILinkInfoProvider.h"
#include "ILinkResource.h"
#include "IApplication.h"
#include "ICursorProvider.h"
#include "ICursorRegion.h"

#include "CIDIconSuiteButtonView.h"
#include "ILinksUIUtils.h"
#include "IWidgetUtils.h"

class LinkInfoIconView : public CIDIconSuiteButtonView
{
	typedef CIDIconSuiteButtonView inherited;
public:
	LinkInfoIconView(IPMUnknown* boss);
	virtual ~LinkInfoIconView();
	
	virtual void PreDrawDoIconChange();
};

CREATE_PERSIST_PMINTERFACE(LinkInfoIconView, kLinkInfoIconViewImpl)


LinkInfoIconView::LinkInfoIconView(IPMUnknown *boss) :
	inherited(boss)
{
	InterfacePtr<const IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<ICursorProvider> globalCursorProvider(theApp, IID_ILINKSROWELEMENTCURSORPROVIDER);
	InterfacePtr<ICursorRegion> myCursorRegion(this, UseDefaultIID());
	if(myCursorRegion && globalCursorProvider)
		myCursorRegion->SetCursorProvider(globalCursorProvider);

}

LinkInfoIconView::~LinkInfoIconView() 
{ 
}


void LinkInfoIconView::PreDrawDoIconChange()
{
	InterfacePtr<const ILinkInfoProvider> infoProvider(Utils<ILinksUIUtils>()->QueryInfoProviderFromLinksUIWidget(this));
	if(infoProvider && infoProvider->IsLinkInfoDynamic())
	{
		InterfacePtr<const ILink> link(Utils<ILinksUIUtils>()->QueryLinkFromLinksUIWidget(this));
		InterfacePtr<const ILinkResource> linkResource(Utils<ILinksUIUtils>()->QueryLinkResourceFromLinksUIWidget(this));
		if(link || linkResource)
		{
			PMRsrcID updatedIconRsrc = infoProvider->GetUpdatedIconForLink(link,linkResource);

			if(updatedIconRsrc.fId != GetRsrcID() || updatedIconRsrc.fPluginId != GetRsrcPluginID() )
			{
				// DV_Note: the old version of this widget filled the background, if it still needs to it could override DV_Draw, fill and call inherited::DV_Draw
				
				this->SetRsrcPluginID(updatedIconRsrc.fPluginId);
				this->SetRsrcID(updatedIconRsrc.fId);
			}
		}
	}
}



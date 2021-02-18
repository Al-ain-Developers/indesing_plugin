//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUIRowElementCursorProvider.cpp $
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

#include "CCursorProvider.h"
#include "IControlView.h"
#include "ILinkInfoProvider.h"
#include "ILink.h"
#include "ILinkResource.h"

#include "HelperInterface.h"
#include "Utils.h"
#include "ILinksUIUtils.h"
#include "LinksUIID.h"

class LinksUIRowElementCursorProvider : public CCursorProvider
{
	public:
		LinksUIRowElementCursorProvider(IPMUnknown* boss);
		~LinksUIRowElementCursorProvider();
		
		virtual CursorSpec	GetCursor(IControlView* viewUnderMouse, const SysPoint globalLocation, ICursorMgr::eCursorModifierState modifiers) const;
		virtual bool16	LocationAffectsCursor(SysRgn) const { return kFalse; }

	private:
		bool16 MouseIsOverSomethingClickable(const IControlView* viewUnderMouse) const;
		DECLARE_HELPER_METHODS()
};

//========================================================================
// Class LinksUIRowElementCursorProvider
//========================================================================
CREATE_PMINTERFACE(LinksUIRowElementCursorProvider, kLinksUIRowElementCursorProviderImpl)
DEFINE_HELPER_METHODS(LinksUIRowElementCursorProvider)

LinksUIRowElementCursorProvider::LinksUIRowElementCursorProvider(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss),
	CCursorProvider(boss)
{
}

LinksUIRowElementCursorProvider::~LinksUIRowElementCursorProvider()
{
}

bool16 LinksUIRowElementCursorProvider::MouseIsOverSomethingClickable(const IControlView* viewUnderMouse) const
{
	InterfacePtr<const ILinkInfoProvider> infoProvider(Utils<ILinksUIUtils>()->QueryInfoProviderFromLinksUIWidget(viewUnderMouse));
	if(infoProvider )
	{
		InterfacePtr<const ILink> link(Utils<ILinksUIUtils>()->QueryLinkFromLinksUIWidget(viewUnderMouse));
		InterfacePtr<const ILinkResource> linkResource(Utils<ILinksUIUtils>()->QueryLinkResourceFromLinksUIWidget(viewUnderMouse));
		if(link || linkResource)
			return (infoProvider->CanDoSingleClickAction(link,linkResource) || infoProvider->CanDoDoubleClickAction(link,linkResource));
	}

	return kFalse;
}

CursorSpec	LinksUIRowElementCursorProvider::GetCursor(IControlView* viewUnderMouse, const SysPoint globalLocation, ICursorMgr::eCursorModifierState state) const
{
	//TRACE("LinksUIRowElementCursorProvider::GetCursor called\n");
	if(MouseIsOverSomethingClickable(viewUnderMouse))
		return CursorSpec(kCrsrPointyHand);
	else
		return CCursorProvider::GetCursor(viewUnderMouse,  globalLocation, state);
}


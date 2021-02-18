//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUILinkNamePanelView.cpp $
//  
//  Owner: Deepak Gupta
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

#include "DVPanelView.h"
#include "LinksUIID.h"

class LinksUILinkNamePanelView : public DVPanelView
{
	typedef DVPanelView inherited;
public:
	LinksUILinkNamePanelView(IPMUnknown* boss);
	virtual ~LinksUILinkNamePanelView();
};

CREATE_PERSIST_PMINTERFACE(LinksUILinkNamePanelView, kLinksUILinkNamePanelViewImpl)


LinksUILinkNamePanelView::LinksUILinkNamePanelView(IPMUnknown *boss) :
	inherited(boss)
{
	SetClipToSelfEnabled(kTrue);
}

LinksUILinkNamePanelView::~LinksUILinkNamePanelView() 
{ 
}

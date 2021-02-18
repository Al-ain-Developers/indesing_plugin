//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinkInfoPanelView.cpp $
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

#include "ISubject.h"
#include "DVPanelView.h"
#include "LinksUIID.h"
#include "IPanorama.h"

class LinkInfoPanelView : public DVPanelView
{
	typedef DVPanelView inherited;
public:
	LinkInfoPanelView(IPMUnknown* boss);
	virtual ~LinkInfoPanelView();
	
	virtual void Resize(const PMPoint& dimensions, bool16 invalidate);
	virtual void DoPostCreate();
};

CREATE_PERSIST_PMINTERFACE(LinkInfoPanelView, kLinkInfoPanelViewImpl)


LinkInfoPanelView::LinkInfoPanelView(IPMUnknown *boss) :
	inherited(boss)
{
}

LinkInfoPanelView::~LinkInfoPanelView() 
{ 
}

void LinkInfoPanelView::Resize(const PMPoint& dimensions, bool16 invalidate)
{
	TRACEFLOW("Links:LinksUI:Resize","LinkInfoPanelView::Resize to height %d\n",::ToInt32(dimensions.Y()));
	inherited::Resize(dimensions,invalidate);
	
	InterfacePtr<IPanorama> panorama(this,UseDefaultIID());
	InterfacePtr<ISubject> panoramaSubj(panorama, UseDefaultIID());
	if (panoramaSubj)
		panoramaSubj->Change(kScaleToMessage, IID_IPANORAMA, this);
	panorama->ScrollTo_neg(PMPoint(0,0));

}

void LinkInfoPanelView::DoPostCreate()
{
	inherited::DoPostCreate();
	
	SetClipToSelfEnabled(true);
}

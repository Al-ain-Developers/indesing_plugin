//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinkUILinkNameTip.cpp $
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
#include "ILinkResource.h"
#include "AbstractTip.h"
#include "PMString.h"

#include "CPMUnknown.h"
#include "LinksUIID.h"
#include "ILinksUIUtils.h"
#include "Utils.h"


class LinkUILinkNameTip : public AbstractTip
{			
public:
	LinkUILinkNameTip( IPMUnknown *boss );
	virtual ~LinkUILinkNameTip();

	virtual PMString  GetTipText(const PMPoint& mouseLocation);
};

CREATE_PMINTERFACE( LinkUILinkNameTip, kLinkUILinkNameTipImpl )


LinkUILinkNameTip::LinkUILinkNameTip(IPMUnknown *boss) :
	AbstractTip( boss )
{
} 



LinkUILinkNameTip::~LinkUILinkNameTip()
{
} 


PMString LinkUILinkNameTip::GetTipText(const PMPoint& mouseLocation)
{
#pragma unused(mouseLocation)

	PMString tipString;

	InterfacePtr<const ILinkResource> linkResource(Utils<ILinksUIUtils>()->QueryLinkResourceFromLinksUIWidget(this));
	if(linkResource)
	{
		tipString.Append(linkResource->GetLongName(true));
		tipString.SetTranslatable(kFalse);
	}
		
	return tipString;
} 

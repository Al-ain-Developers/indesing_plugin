//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinkInfoDebugUIDsProvider.cpp $
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

#ifdef DEBUG

// ----- Interface files
#include "CLinkInfoProvider.h"
#include "ILink.h"
#include "ILinkResource.h"

// ----- ID files
#include "LinksUIID.h"

class LinkInfoDebugUIDsProvider : public CLinkInfoProvider
{
	public:

	LinkInfoDebugUIDsProvider(IPMUnknown * boss);
	virtual ~LinkInfoDebugUIDsProvider();
			
	virtual PMString GetInfoDescriptionString() const { return "#LinkInfoDebugUIDsStr"; }
	virtual PMString GetUpdatedInfoForLink(const ILink* link, const ILinkResource* linkResource, bool /*shortForm*/) const;

};

CREATE_PMINTERFACE(LinkInfoDebugUIDsProvider, kLinkInfoDebugUIDsProviderImpl)

LinkInfoDebugUIDsProvider::LinkInfoDebugUIDsProvider(IPMUnknown * boss)
	: CLinkInfoProvider(boss)
{
}

LinkInfoDebugUIDsProvider::~LinkInfoDebugUIDsProvider()
{
}

PMString LinkInfoDebugUIDsProvider::GetUpdatedInfoForLink(const ILink* link, const ILinkResource* linkResource, bool /*shortForm*/) const
{
	PMString uidsStr;
	uidsStr.Append("LinkUID: ");
	uidsStr.AppendNumber(::GetUID(link).Get());
	uidsStr.Append(" ObjectUID: ");
	uidsStr.AppendNumber(link ? link->GetObject().Get() : 0);
	uidsStr.Append(" ResourceUID: ");
	uidsStr.AppendNumber(::GetUID(linkResource).Get());
	uidsStr.SetTranslatable(kFalse);

	return uidsStr;
}
#endif

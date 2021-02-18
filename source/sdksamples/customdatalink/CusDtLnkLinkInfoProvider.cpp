//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkLinkInfoProvider.cpp $
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

// ----- Interface files
#include "ILinkResource.h"
#include "ILink.h"
#include "ILinkObject.h"
#include "CLinkInfoProvider.h"
#include "ILinksUIUtils.h"
#include "Utils.h"
#include "ICusDtLnkFacade.h"
#include "WidgetDefs.h"
// ----- ID files
#include "CusDtLnkID.h"

/** Implementation of CLinkInfoProviderso we can add a column in the Links UI that displays a special icon.  This is just a simple
	demonstration on how you can hook into the Links UI panel.  You can display a more complex information by attaching an observer
	to a document for more dynamic info display.

	@ingroup customdatalink
*/
class CusDtLnkLinkInfoProvider : public CLinkInfoProvider
{
	public:

	CusDtLnkLinkInfoProvider(IPMUnknown * boss);
	virtual ~CusDtLnkLinkInfoProvider();

	/** 
		@see ILinkInfoProvider::GetInfoDescriptionString
	*/
	virtual PMString GetInfoDescriptionString() const { return kCusDtLnkAssetDataBaseLinkInfoNameKey; }
	/** 
		Just returned a simple static icon if the link is our link for demo purpose, you can display different icons based on the ILink and ILinkResource passed into the methods.
		@see ILinkInfoProvider::GetInfoDescriptionString
	*/
	virtual PMRsrcID GetUpdatedIconForLink(const ILink* link, const ILinkResource* linkResource) const;
	/** 
		@see ILinkInfoProvider::IsLinkInfoDynamic
	*/
	virtual bool16 IsLinkInfoDynamic() const {  return kFalse; }
	/** 
		If the link is ours, then grab some info from the link resource and return it as a PMString.
		@see ILinkInfoProvider::GetUpdatedInfoForLink
	*/
	virtual PMString GetUpdatedInfoForLink(const ILink* link, const ILinkResource* linkResource, bool /*shortForm*/) const;
};

CREATE_PMINTERFACE(CusDtLnkLinkInfoProvider, kCusDtLnkLinkInfoProviderImpl)

CusDtLnkLinkInfoProvider::CusDtLnkLinkInfoProvider(IPMUnknown * boss)
	: CLinkInfoProvider(boss)
{
}

CusDtLnkLinkInfoProvider::~CusDtLnkLinkInfoProvider()
{
}

PMString CusDtLnkLinkInfoProvider::GetUpdatedInfoForLink(const ILink* link, const ILinkResource* linkResource, bool /*shortForm*/) const
{
	PMString nameStr("");
	
	if(linkResource)
	{
		UIDRef linkRef = ::GetUIDRef(link); 
		bool16 isOurLInk = Utils<ICusDtLnkFacade>()->IsOurCustomDataLink(linkRef);
		if (isOurLInk)
		{
			URI uri = linkResource->GetURI();
			nameStr = Utils<ICusDtLnkFacade>()->GetAssetDescriptionFromURI(uri);
			nameStr.SetTranslatable(kFalse);
	//			TRACEFLOW("Links:LinksUI","CusDtLnkLinkInfoProvider::GetUpdatedInfoForLink returning link name '%s' for link resource UID %d\n",nameStr.GrabCString(),::GetUID(linkResource));
		}
	}

	return nameStr;
}

PMRsrcID CusDtLnkLinkInfoProvider::GetUpdatedIconForLink(const ILink* link, const ILinkResource* linkResource) const
{
	PMRsrcID iconRsrc;
	if (linkResource)
	{
		UIDRef linkRef = ::GetUIDRef(link); 
		bool16 isOurLInk = Utils<ICusDtLnkFacade>()->IsOurCustomDataLink(linkRef);
		if (isOurLInk)
		{
			iconRsrc.fId = kSDKDefIconInfoResourceID;
			iconRsrc.fPluginId = kCusDtLnkPluginID;
		}
	}
	return iconRsrc;
}
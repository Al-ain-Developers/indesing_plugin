//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkLinkResourceHelperHandler.cpp $
//
//  Owner: Sachin Singhal
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#include "VCPlugInHeaders.h"
#include "CusDtLnkLinkResourceHelperHandler.h"
#include "IFileEditorAppsUtils.h"
#include "IDFile.h"
#include "CusDtLnkID.h"
#include "ICusDtLnkFacade.h"

// =============================================================================
// *** CusDtLnkLinkResourceHelperHandler implementation ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(CusDtLnkLinkResourceHelperHandler, kCusDtLnkLinkResourceHelperHandlerImpl)

//========================================================================================
// Constructor
//========================================================================================
CusDtLnkLinkResourceHelperHandler::CusDtLnkLinkResourceHelperHandler(IPMUnknown* boss)
	: CPMUnknown<ILinkResourceHelperHandler>(boss)
{
}

//========================================================================================
// Destructor
//========================================================================================
CusDtLnkLinkResourceHelperHandler::~CusDtLnkLinkResourceHelperHandler()
{
}

bool CusDtLnkLinkResourceHelperHandler::CanProvideSupportedApplicationList(const UIDRef& ref, const URI& uri) const
{
	return true;
	// return true means GetSupportedApplicationList() will be used to create the list of supported applications by this resource.
	// Should return false here to use default implementation of GetSupportedApplicationList.
}

void CusDtLnkLinkResourceHelperHandler::GetSupportedApplicationList(const UIDRef& ref, const URI& uri, AppInfoList& appList, bool16 bDefaultEditorOnly) const
{

	IDFile file;
	if (!Utils<ICusDtLnkFacade>()->URIToIDFile(uri, file))
		return;

	// GetSupportedApplicationList implementation needs the actual file. Hence file.Exists() check is used. This check can be avoided if user writes its own implementation to 
	// get the supported applications list (which does not need file) instead of Utils<IFileEditorAppsUtils>()->GetSupportedApplicationList.
	if (!file.Exists())
		return;

	Utils<IFileEditorAppsUtils>()->GetSupportedApplicationList(file, appList, bDefaultEditorOnly);
}

ILinkResourceHelper::IconStatus CusDtLnkLinkResourceHelperHandler::GetIcon(const UIDRef& ref, const URI& uri, const ILink* link) const
{
	PMRsrcID iconRsrc(kInvalidRsrcID, kLinksPluginID);
	ILinkResourceHelper::IconStatus iconStatus(iconRsrc, ILinkResourceHelper::kIconOk, kFileLinkIconPriority);

	InterfacePtr<ILinkResource> linkResource(ref, UseDefaultIID());
	if (linkResource)
	{
		if (linkResource->GetState() == ILinkResource::kUnknown)
		{
			iconRsrc.fId = kLinksUnknownStatusIconResID;
			iconStatus.fState = ILinkResourceHelper::kIconUnknown;
		}
		else if (linkResource->GetState() == ILinkResource::kMissing)
		{
			iconRsrc.fId = kLinksMissingStatusIconResID;
			iconStatus.fState = ILinkResourceHelper::kIconMissing;
		}
		else if (linkResource->GetState() == ILinkResource::kInaccessible)
		{
			iconRsrc.fId = kLinksInaccessibleStatusIconResID;
			iconStatus.fState = ILinkResourceHelper::kIconInaccessible;
		}
		else if (linkResource->GetState() == ILinkResource::kPending)
			iconRsrc.fId = kLinksPendingStatusIconResID;
		else if (link && link->GetResourceModificationState() == ILink::kResourceModified)
		{
			iconRsrc.fId = kLinksOutOfDateStatusIconResID;
			iconStatus.fState = ILinkResourceHelper::kIconModified;
		}
		else if (linkResource->GetStoreState() == ILinkResource::kCached)
			iconRsrc.fId = kLinksCachedStatusIconResID;
		else if (linkResource->GetStoreState() == ILinkResource::kEmbedded)
			iconRsrc.fId = kLinksEmbeddedStatusIconResID;
		else
			iconRsrc.fId = kLinksStatusOKResID;
	}
	iconStatus.fIcon = iconRsrc;
	return iconStatus;
}

ILinkResourceHelper::IconStatus CusDtLnkLinkResourceHelperHandler::GetPageItemAdornmentIcon(const UIDRef& ref, const URI& uri, const ILink* link) const
{
	PMRsrcID iconRsrc(kInvalidRsrcID, kLinksPluginID);
	ILinkResourceHelper::IconStatus iconStatus(iconRsrc, ILinkResourceHelper::kIconOk, kFileLinkIconPriority);

	InterfacePtr<ILinkResource> linkResource(ref, UseDefaultIID());
	if (linkResource)
	{
		if (linkResource->GetState() == ILinkResource::kMissing)
		{
			iconRsrc.fId = kPageItemAdornmentLinkObjectMissingStatusIconRsrcID;
			iconStatus.fState = ILinkResourceHelper::kIconMissing;
		}
		else if (link && link->GetResourceModificationState() == ILink::kResourceModified)
		{
			iconRsrc.fId = kPageItemAdornmentLinkObjectOutOfDateIconRsrcID;
			iconStatus.fState = ILinkResourceHelper::kIconModified;
		}
		else
			iconRsrc.fId = kPageItemAdornmentLinkObjectIconRsrcID;
	}
	iconStatus.fIcon = iconRsrc;
	return iconStatus;
}
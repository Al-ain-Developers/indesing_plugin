//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILinkResourceHelperHandler.h $
//  
//  Owner: Manohar Gour
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
//  Copyright 2016 Adobe 
//  All Rights Reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in 
//  accordance with the terms of the Adobe license agreement accompanying 
//  it. If you have received this file from a source other than Adobe, 
//  then your use, modification, or distribution of it requires the prior 
//  written permission of Adobe.
//  
//  Description:
//  This class defines an interface that implements behavior for an ILinkResource that
//  is specific to the type of the resource as identified by the scheme of the link
//  resource's URI.
//  
//========================================================================================

#pragma once
#ifndef __ILinkResourceHelperHandler__
#define __ILinkResourceHelperHandler__

// ----- Includes -----
#include "IPMUnknown.h"
#include "LinksUIID.h"

#include "ILinkResourceHelper.h"


/**
Experimental interface - will be modified/documented in future.
*/
class ILinkResourceHelperHandler : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKRESOURCEHELPERHANDLER };

	virtual	ILinkResourceHelper::IconStatus GetIcon(const UIDRef& ref, const URI& uri, const ILink* link) const = 0;
	virtual	ILinkResourceHelper::IconStatus GetPageItemAdornmentIcon(const UIDRef& ref, const URI& uri, const ILink* link) const = 0;
	virtual bool CanDoDoubleClickInaccessibleAction() const = 0;
	virtual void DoubleClickInaccessibleAction() const = 0;
	virtual void ReplaceWithOriginalAsset() const = 0;
	virtual bool IsInaccessibleActionSupportedURIScheme() const = 0;
	virtual void InaccessibleActionOnOpenDoc() const = 0;
	virtual PMString InaccessibleLinksWarningMessage(int32 count) const = 0;

	/**
	Determines if a resource can provide the list of supported applications which can be used to open resource. This list is shown in the context menu of this resource.
	Remeber to override function GetSupportedApplicationList too if returning true here.
	@param ref [IN] UID reference of the link resource.
	@param uri [IN] URI of the link resource.
	@return true if the resource can provide the list. List will be extracted using function GetSupportedApplicationList() in case this function returns true.
	*/
	virtual bool CanProvideSupportedApplicationList(const UIDRef& ref, const URI& uri) const = 0;

	/**
	Get the list of applications supported by resource. This list is shown in the context menu of this link.
	This function is called only if CanProvideSupportedApplicationList return true. This function will genreally be used when user want to customize/add/delete to the list of softwares which
	can be used to edit this resource.
	@param ref [IN] UID reference of the link resource.
	@param uri [IN] URI of the link resource.
	@param bDefaultEditorOnly [IN] if to fill the list with only default editor
	@param appList [OUT] list which will be filled with supported applications
	*/
	virtual void GetSupportedApplicationList(const UIDRef& ref, const URI& uri, AppInfoList& appList, bool16 bDefaultEditorOnly = false) const = 0;
};

#endif // __ILinkResourceHandler__

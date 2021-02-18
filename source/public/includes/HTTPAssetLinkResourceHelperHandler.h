//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/HTTPAssetLinkResourceHelperHandler.h $
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
//  Copyright 2017 Adobe 
//  All Rights Reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in 
//  accordance with the terms of the Adobe license agreement accompanying 
//  it. If you have received this file from a source other than Adobe, 
//  then your use, modification, or distribution of it requires the prior 
//  written permission of Adobe.
//  
//========================================================================================

#ifndef __HTTPAssetLinkResourceHelperHandler__ 
#define __HTTPAssetLinkResourceHelperHandler__ 

#include "CPMUnknown.h"

#include "ILink.h"
#include "ILinkResource.h"
#include "ILinkResourceHelperHandler.h"

#include "LinksID.h"


// =============================================================================
//		* HTTPAssetLinkResourceHelperHandler											
// =============================================================================

/**
Experimental header - will be modified/documented in future.
*/
class PUBLIC_DECL HTTPAssetLinkResourceHelperHandler : public CPMUnknown<ILinkResourceHelperHandler>
{
public:
	typedef CPMUnknown<ILinkResourceHelperHandler> inherited;

	HTTPAssetLinkResourceHelperHandler(IPMUnknown* boss);
	virtual ~HTTPAssetLinkResourceHelperHandler();

	/*
	@param ref [IN] UIDRef of the Link Resource.
	@param uri [IN] uri of the Link Resource.
	@param link [IN] link corresponding to the link resource.
	@return Icon for the link in link panel.
	*/
	virtual	ILinkResourceHelper::IconStatus GetIcon(const UIDRef& ref, const URI& uri, const ILink* link) const;

	/*
	@param ref [IN] UIDRef of the Link Resource.
	@param uri [IN] uri of the Link Resource.
	@param link [IN] link corresponding to the link resource.
	@return Icon for the pageitem corresponding to the link.
	*/
	virtual ILinkResourceHelper::IconStatus GetPageItemAdornmentIcon(const UIDRef& ref, const URI& uri, const ILink* link) const;

	/*
	 @return true if double click is allowed for inaccessible link else false.
	*/
	virtual bool CanDoDoubleClickInaccessibleAction() const; 

	// performs double click on inaccessible link.
	virtual void DoubleClickInaccessibleAction() const; 
	/*

	@replace FPO with original asset.
	*/
	virtual void ReplaceWithOriginalAsset() const;
	/*

	@return true if URI specific inaccessible links action have to be taken.
	*/
	virtual bool IsInaccessibleActionSupportedURIScheme() const;
	/*

	@take URI specific inaccessible links.
	*/
	virtual void InaccessibleActionOnOpenDoc() const;
	/*
	@param count [IN] no of links for which warning message have to be shown.
	@return warning message for all same http  type URI inaccessible links.
	*/
	virtual PMString  InaccessibleLinksWarningMessage(int32 count) const;

	/**
	Determines if a resource can provide the list of supported applications which can be used to open resource. This list is shown in the context menu of this resource.
	Remeber to override function GetSupportedApplicationList too if returning true here.
	@param ref [IN] UID reference of the link resource.
	@param uri [IN] URI of the link resource.
	@return true if the resource can provide the list. List will be extracted using function GetSupportedApplicationList() in case this function returns true.
	*/
	virtual bool CanProvideSupportedApplicationList(const UIDRef& ref, const URI& uri) const;

	/**
	Get the list of applications supported by resource. This list is shown in the context menu of this link.
	This function is called only if CanProvideSupportedApplicationList return true. This function will genreally be used when user want to customize/add/delete to the list of softwares which
	can be used to edit this resource.
	@param ref [IN] UID reference of the link resource.
	@param uri [IN] URI of the link resource.
	@param bDefaultEditorOnly [IN] if to fill the list with only default editor
	@param appList [OUT] list which will be filled with supported applications
	*/
	virtual void GetSupportedApplicationList(const UIDRef& ref, const URI& uri, AppInfoList& appList, bool16 bDefaultEditorOnly = false) const;
};

#endif
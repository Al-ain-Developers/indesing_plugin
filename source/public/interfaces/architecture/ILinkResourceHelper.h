//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILinkResourceHelper.h $
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
//  This class defines an interface used to maintain and access UI properties of a linked resource.
//  
//========================================================================================

#pragma once
#ifndef __ILinkResourceHelper__
#define __ILinkResourceHelper__

// ----- Includes -----
#include "IPMUnknown.h"
#include "LinksID.h"
#include "LinksUIID.h"
#include "AppInfo.h"


class FileTypeInfo;
class IDTime;
class PMString;
class UIDList;
class URI;
class WideString;
class ILink;

/**
Experimental interface - will be modified/documented in future.
*/
class ILinkResourceHelper : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKRESOURCEHELPER };
	/*caution: Please don't change values of this enum as it is use to sort icons in shared content ui.
	this value will be decisive in case of multiple page items in a group */
	enum IconState {
		kIconUnknown = 0,
		kIconEmbedded = 5,
		kIconOk = 10,
		kIconMissing = 15,
		kIconInaccessible = 20,
		kIconModified = 25
	};

	struct IconStatus {

		IconStatus(PMRsrcID icon, IconState state, int32 priority,PMString msg=PMString("")) :
			fIcon(icon), fState(state), fPriority(priority),fmsg(msg) {}

		PMRsrcID	fIcon;
		IconState	fState;
		int32		fPriority;
		PMString    fmsg;
	};

	/**
	Returns the icon, it's state & it's priority withing the state.
	@param link [IN] The link corresponding to the resource
	@return icon and it's status.
	*/
	virtual	IconStatus GetIcon(const ILink* link) const = 0;
	virtual IconStatus GetPageItemAdornmentIcon(const ILink* link) const = 0;

	virtual bool CanDoDoubleClickInaccessibleAction() const = 0;
	virtual void DoubleClickInaccessibleAction() const = 0;
	virtual void ReplaceWithOriginalAsset() const = 0;
	virtual bool IsInaccessibleActionSupportedURIScheme() const = 0;
	virtual void InaccessibleActionOnOpenDoc() const = 0;
	virtual PMString  InaccessibleLinksWarningMessage(int32 count) const = 0;


	/**
	Determines if a resource can provide the list of supported applications which can be used to open resource. This list is shown in the context menu of this resource.
	@return true if the resource can provide the list. List will be extracted using function GetSupportedApplicationList() in case this function returns true.
	*/
	virtual bool CanProvideSupportedApplicationList() const = 0;

	/**
	Get the list of applications supported by resource. This list is shown in the context menu of this link.
	This function is called only if CanProvideSupportedApplicationList return true. This function will genreally be used when user want to customize/add/delete to the list of softwares which
	can be used to edit this resource.
	@param bDefaultEditorOnly [IN] if to fill the list with only default editor
	@param appList [OUT] list which will be filled with supported applications
	*/
	virtual void GetSupportedApplicationList(AppInfoList& appList, bool16 bDefaultEditorOnly = false) const = 0;
};


//Some well known Adobe icon priorities 
const int32 kDefaultLinkIconPriority  = 10;
const int32 kFileLinkIconPriority     = kDefaultLinkIconPriority + 10;
const int32 kCCLibLinkIconPriority    = kFileLinkIconPriority + 10;
const int32 kHTTPLinkIconPriority     = kCCLibLinkIconPriority + 10;
const int32 kHTTPFPOLinkIconPriority  = kHTTPLinkIconPriority + 10;
const int32 kAALLinkIconPriority      = kHTTPFPOLinkIconPriority + 10;
const int32 kAALFPOLinkIconPriority   = kAALLinkIconPriority + 10;



#endif // __ILinkResource__

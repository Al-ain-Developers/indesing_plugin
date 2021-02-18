//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IUpdateLink.h $
//  
//  Owner: Steve Flenniken
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

#pragma once
#ifndef __IUpdateLink__
#define __IUpdateLink__

#include "IPMUnknown.h"
#include "LinksID.h"

class IDataLink;
class ILink;


/**
 You use this interface to update a page item to the lastest linked information.
 @see ILink
*/
class IUpdateLink : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IUPDATELINK };

	/** DoUpdateLink return values */
	enum {
		/** No error */
		kSuccess = 0,
		/** Out of memory */
		kOutOfMemory = kOutOfMemoryError,
		/** Invalid parameter */
		kInvalidParameter = kInvalidParameterErr,
		/** The data link does not have an associated page item */
		kNoAssociatedPageItem = kNoAssociatedPageItemError
	};

	/** 
	 Update the link by reimporting the data. \\
	 The update uses the setting last used to import the data.
	 If this fails because the data is no longer appropriate for
	 this import filter, the import uses the standard import code
	 which picks a new filter. \\
	 A new page item wil be created to replace the original item.
	 @param providerId [IN[ Id of the update link service provider to use to update.
	 @param iLink	   [IN[ Link to be updated.
	 @param objectUID  [OUT] UID of the new link object and page item.
	 @param uiFlags	   [IN] Denotes whether to allow UI during the update operation.
	 @return kSuccess if the update succeeds, else an error code.
	*/
	virtual ErrorCode DoUpdateLink(const ClassID& providerId, ILink* iLink, UID& objectUID, UIFlags uiFlags = kSuppressUI) = 0;

	/** 
	 Determines if the link is an OPI or DCS link.
	 @param iLink [IN] Link to be checked.
	 @return True if the link is an OPI or DCS link, else false.
	*/
	virtual bool IsOPIorDCS(ILink* iLink) = 0;

	/** 
	 Updates an OPI or DCS link.
	 @param iLink [IN] Link to be updated.
	 @precondition The link must be an OPI or DCS link.
	 @return kSuccess if the update succeeds, else an error code.
	*/
	virtual ErrorCode UpdateOPIandDCS(ILink* iLink) =0;
};

#endif // __IUpdateLink__

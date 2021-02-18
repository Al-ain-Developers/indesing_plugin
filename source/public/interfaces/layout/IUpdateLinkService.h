//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IUpdateLinkService.h $
//  
//  Owner: Lin Xia
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
#ifndef __IUpdateLinkService__
#define __IUpdateLinkService__

#include "IPMUnknown.h"
#include "LinksID.h"

class ILink;

/**
	An interface used by ILink::Update() to update a link.
	Must be used in conjunction with kUpdateLinkService.
	Clients who implement custom datalink should implement this interface.
	@see ILink
*/
class IUpdateLinkService : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IUPDATELINKSERVICE };
	
	/** 
	 Returns whether the provider can update the link object.
	 @param iLink	  [IN] Link to update.
	 @return kTrue if the service provider can update the link, else kFalse.
	 */
	virtual bool16 CanUpdateLink(const ILink* iLink) = 0;
	
	/** 
	 Updates the link. \\
	 This method may delete the original link object and associated objects
	 and creates new ones to replace them. 
	 @param iLink	  [IN] Link to update.
	 @param objectUID [OUT] UID of the new link object. \\
							The UID may be the same as the original one.
	 @param uiFlags	  [IN] Denotes whether to use UI during the update operation.
	 @return kSuccess if the update succeeds, else an error code.
	 */
	virtual ErrorCode DoUpdateLink(ILink* iLink, UID& objectUID, UIFlags uiFlags) = 0;

	/** 
	 Called before the link is updated. \\
	 Ususally used to perform pre-notification of the update.
	 @param iLink [IN] Link to update.
	 @return kSuccess if the update should proceed, else an error code. \\
			 The update is aborted if the return value is not kSuccess.
	*/
	virtual ErrorCode PreUpdateLink(ILink* iLink) = 0;

	/** 
	 Called after the link is updated. \\
	 Ususally used to perform post-notification of the update.
	 @param iLink [IN] Link that has been update.
	 @return kSuccess if the update should proceed, else an error code. \\
			 The update is aborted if the return value is not kSuccess.
	*/
	virtual ErrorCode PostUpdateLink(ILink* iLink) = 0;
};

#endif

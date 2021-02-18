//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILinkResourceStateUpdater.h $
//  
//  Owner: Michael Easter
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
//  
//  Description:
//  This class defines an interface that implements state update and location resolution
//  for an ILinkResource that is specific to the type of the resource as identified by
//  the scheme of the link resource's URI.
//  
//========================================================================================

#pragma once
#ifndef __ILinkResourceStateUpdater__
#define __ILinkResourceStateUpdater__

// ----- Includes -----
#include "IPMUnknown.h"
#include "LinksID.h"

class URI;


/**
 ILinkResourceStateUpdater is used to update the state of an ILinkResource and is specific
 to the type of a resource as identified by the scheme of the link resource's URI.  The
 state updater is also responsible for resolving the location of a resource that cannot
 be located utilizing the information in the resource's URI (a missing resource).  How both
 of the above tasks are performed is left completely up to the provider.

 To associate a state updater for a specific type of resource, a factory for the type of
 resource is registered via a link resource provider for the kLinkResourceService.  For
 example, a file based link resource will require a different provider and state updater
 than a database link resource. 
 
 When ILinkManager is called to update the state of an ILinkResource or to resolve the
 location of a missing resource, the state updater is obtained using the scheme of the
 resource's URI as a key to find the appropriate provider. If no state updater is found,
 due to a missing plug-in for instance, the link resource is set to a state of unknown by
 the manager.  Therefore, all resources that have a custom URI must provide a state updater.

 @see ILinkManager
 @see ILinkResource
 */
class ILinkResourceStateUpdater : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKRESOURCESTATEUPDATER };

	/**
	 Called to update the state of a link resource synchronously.
	 @param resourceRef	 [IN] UIDRef of the link resource to update.
	 @param bNotify		 [IN] Denotes whether to notify when the resource's state is updated.
	 @return kSuccess if the link resource's state is successfully updated, else an error code.
	 */
	virtual ErrorCode UpdateResourceStateSync(const UIDRef& resourceRef, bool bNotify) = 0;

	/**
	 Called to update the state of a link resource synchronously.
	 @param resourceRef	 [IN] UIDRef of the link resource to update.
	 @return kSuccess if the state update request was successfully queued, else an error code.
	 */
	virtual ErrorCode UpdateResourceStateAsync(const UIDRef& resourceRef) = 0;

	/**
	 Cancels an asynchronous link resource state update.
	 @param resourceRef [IN] UIDRef of the link resource to cancel the asynchronous state update for.
	 */
	virtual void CancelUpdateResourceState(const UIDRef& resourceRef) = 0;

	/**
	 Wait for the asynchronous link resource state update request to get completed.
	 @param resourceRef [IN] UIDRef of the link resource whose asynchronous request needs to be completed.
	 */
	virtual void WaitForUpdateResourceStateCompletion(const UIDRef& resourceRef) = 0;

	/**
	 Called to attempt to automatically (find without user interaction) the new location
	 of the link resource if it is missing.
	 @param resourceRef	 [IN] UIDRef of the link resource to resolve.
	 @param relativeURI	 [IN] Relative location of where to start the search. \\
							  For example, this is often the location of the document,
							  and depending upon the protocal of the link may not be utilized.
	 @param bIgnoreStamp [IN] Denotes whether to ignore the resource's stamp when looking
							  for potential matches.
	 @return kSuccess if the link resource is successfully resolved, else an error code.
	 */
	virtual ErrorCode ResolveResource(const UIDRef& resourceRef, const URI& relativeURI, bool bIgnoreStamp) = 0;
};

#endif // __ILinkResourceStateUpdater__

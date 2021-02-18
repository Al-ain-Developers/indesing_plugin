//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILinkResourceFactory.h $
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
//  Factory class interface used to provide a list of schemes supported by a link
//  resource handler, and to create instances of a link resource handler.
//  
//========================================================================================

#pragma once
#ifndef __ILinkResourceFactory__
#define __ILinkResourceFactory__

// ----- Includes -----
#include "IPMUnknown.h"
#include "LinksID.h"
#include "K2Vector.h"

class IDataBase;
class ILinkResourceHandler;
class ILinkResourceStateUpdater;
class URI;


/**
 This factory class is used to provide a list of schemes supported
 by a link resource handler, and to create instances of a link resource
 handler. \\
 Include this interface on the link resource provider boss that is
 registered with the service registry as a kLinkResourceService.
 @see ILinkResourceHandler
 @see IK2ServiceProvider
 */
class ILinkResourceFactory : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKRESOURCEFACTORY };

	/**
	 Gets the list of URI schemes supported by the handler.
	 @param schemes [OUT] List of supported schemes.
	 */ 
	virtual void GetSchemes(K2Vector<WideString>& schemes) const = 0;

	/**
	 Returns the link resource handler that will be used by a link resource
	 object to act on an resource whose URI scheme matches one of the
	 supported schemes.
	 @param uri	[IN] URI of the link resource the handler will be used for.
	 @param db	[IN] Database that contains the link resource.
	 @return Link resource handler. \\
			 Caller assumes responsibility for releasing the returned object.
	 */
	virtual ILinkResourceHandler* QueryHandler(const URI& uri, IDataBase* db) const = 0;

	/**
	 Returns the link resource state updater that will be used to obtain and
	 update the state of a link resource whose URI scheme matches one of the
	 supported schemes.
	 @param uri	[IN] URI of the link resource whose state will be updated.
	 @param db	[IN] Database that contains the link resource.
	 @return Link resource state updater. \\
			 Caller assumes responsibility for releasing the returned object.
	 */
	virtual ILinkResourceStateUpdater* QueryStateUpdater(const URI& uri, IDataBase* db) const = 0;
};

#endif // __ILinkResourceFactory__

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IHTTPLinkSubsystemObjectFactory.h $
//  
//  Owner: Sanyam Jain
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
//  Factory class interface used to provide a list of schemes supported by a http link
//  resource connection, and to create instances of resource connection.
//  
//========================================================================================

#pragma once
#ifndef __IHTTPLinkSubsystemObjectFactory__
#define __IHTTPLinkSubsystemObjectFactory__

// ----- Includes -----
#include "IPMUnknown.h"
#include "LinksID.h"

class IHTTPLinkResourceConnection;
class URI;
class IHTTPLinkResourceServerAPIWrapper;
class IDataBase;
class ILinkResourceHandler;
class ILinkResourceStateUpdater;

/*
 AdobePatentID="P7137-US"
 AdobePatentID="P7225-US"
 AdobePatentID="P7609-US"
 */

/**
 IHTTPLinkSubsystemObjectFactory is used to implement custom handling of http links through scheme
 system. For creating a plugin for handling of http links, first define a scheme. Then do following
 steps:
 1.  Include this interface on the http link resource connection provider boss that is
     registered with the service registry as a kHTTPLinkResourceConnectionProvider. Its GetSchemes
     should return list of schemes supported by plugin. It will be called when HTTPLinkManager is
     initialized and schemes will be registered. IHTTPLinkManager will be using query functions defined
     here for the uri which matches with the schemes provided in GetSchemes.
 2.  Implement IHTTPLinkResourceServerAPIWrapper(for details see IHTTPLinkResourceServerAPIWrapper.h).
     It is mandatory to implement this interface. It deals with high level API interaction with server.
 3.  Implement IHTTPLinkResourceConnection(for details see IHTTPLinkResourceConnection.h). It is mandatory
     to implement this interface. It deals with creating connection with server. It handles responsibilities
     like login credentials and passing session tokens.
 
 Above mentioned interfaces are mandatory, but there are other interfaces also that can be overriden to extend
 the functionalities:
 1. IHTTPLinkResourceStateBatchUpdater - If web-api supports batch state updates, this interface can be
    implemented to alter default implementation
 2. IHTTPLinkResourceServerCache - This should be implemented if want to handle cache by yourself.
 3. IHTTPAssetDownloadManager - Should be implemented if different handling http asset downloads.
 
 @see IHTTPLinkResourceServerAPIWrapper
 @see IHTTPLinkResourceConnection
 @see IK2ServiceProvider
 @see IHTTPLinkResourceServerCache
 @see IHTTPLinkResourceStateBatchUpdater
 @see
 */
class IHTTPLinkSubsystemObjectFactory : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHTTPLINKSUBSYSTEMOBJECTFACTORY };

	/**
	 Gets the URI scheme supported by the resource connection.
	 @param schemes [OUT] all the registered schemes
	 */ 
	virtual void GetSchemes(K2Vector<WideString>& schemes) const = 0;

	/**
	Returns the link resource handler that will be used by a link resource
	object to act on an resource whose URI scheme matches one of the
	supported schemes. Caller assumes responsibility for releasing the returned object.
	@param uri    [IN] URI of the link resource the handler will be used for.
	@param db     [IN] Database that contains the link resource.
	@return HTTP Link resource handler. \\
	*/
	virtual ILinkResourceHandler* QueryHandler(const URI& uri, IDataBase* db) const = 0;

	/**
	Returns the link resource state updater that will be used to obtain and
	update the state of a link resource whose URI scheme matches one of the
	supported schemes. Caller assumes responsibility for releasing the returned object.
	@param uri    [IN] URI of the link resource whose state will be updated.
	@param db     [IN] Database that contains the link resource.
	@return HTTP Link resource state updater. \\
	*/
	virtual ILinkResourceStateUpdater* QueryStateUpdater(const URI& uri, IDataBase* db) const = 0;

	/**
	 Returns the http link resource connection that will be used by a http links subsystem to 
	 interact with the http resource connection whose URI scheme matches one of the
	 supported scheme. Caller assumes responsibility for releasing the returned object.
	 @param uri	[IN] URI of the link resource the handler will be used for.
	 @param db     [IN] Database that contains the link resource.
	 @return Http Link resource connection. \\
	 */
	virtual IHTTPLinkResourceConnection* QueryHTTPLinkResourceConnection(const URI& uri, IDataBase* db) const = 0;

	/**
	Returns the http link resource server API wrapper that will be used by a http links subsystem to
	interact with the http resource server whose URI scheme matches one of the
	supported scheme. Caller assumes responsibility for releasing the returned object.
	@param uri	[IN] URI of the link resource the handler will be used for.
	@param db     [IN] Database that contains the link resource.
	@return Http Link resource server API Wrapper. \\
	*/
	virtual IHTTPLinkResourceServerAPIWrapper* QueryHTTPLinkResourceServerAPIWrapper(const URI& uriScheme, IDataBase* db) const = 0;
};

#endif // __IHTTPLinkSubsystemObjectFactory__

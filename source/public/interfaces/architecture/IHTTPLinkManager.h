//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IHTTPLinkManager.h $
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
//========================================================================================
#pragma once
#ifndef __IHTTPLinkManager__
#define __IHTTPLinkManager__

#include "IPMUnknown.h"
#include "LinksID.h"
#include "URI.h"

#include "IHTTPLinkResourceServerAPIWrapper.h"
#include "ILinkResourceHandler.h"
#include "ILinkResourceStateUpdater.h"
#include "IHTTPLinkResourceServerCache.h"
#include "IHTTPLinkAssetURIPreprocessor.h"

/*
 AdobePatentID="P7137-US"
 AdobePatentID="P7225-US"
 AdobePatentID="P7609-US"
*/

/**
IHTTPLinkManager is reponsible for routing calls to plugins on the basis of registered scheme.
 During initialization process IHTTPLinkManager iterate through all kHTTPLinkSubsystemObjectProvider
 and calls GetSchemes of all IHTTPLinkSubsystemObjectFactory. It registers factory with list of schemes
 provided by it. It provides appropriate set of wrapper, connection, handler, stateupdater and uri pre-
 processor on the basis of passed URI's scheme.
 
 NOTE - If two plugin registers with same scheme during initialization. Plugin which
 registers scheme first will be given priority and assert will be raised on all the plugins
 after that.
*/
class IHTTPLinkManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHTTPLINKMANGER };

	/**
	Initializes the HTTP Link Manager
	@return kTrue if the Http Link Manager is initialized else kFalse
	*/
	virtual bool16 Initialize() = 0;

	/**
	Shuts down the HTTP Link Manager
	@return kTrue if the Http Link Manager is shutdown else kFalse
	*/
	virtual bool16 Shutdown() = 0;

	/*
	Gets the registered HTTP schemes.
	@param schemes [OUT] returns the registered HTTP schemes .
	*/
	virtual void GetSchemes(K2Vector<WideString>& schemes) const = 0;

	/*
	Gets the resource handler for the specified uri.
	@param inAssetURI [IN] uri of the Link Resource.
	@param db [IN] database corresponding to the link resource.
	@return resource handler for the specified Link Resource.
	*/
	virtual ILinkResourceHandler* QueryHandler(const URI& inAssetURI, IDataBase* db) = 0;

	/*
	Gets the resource state updater for the specified uri.
	@param inAssetURI [IN] uri of the Link Resource.
	@param db [IN] database corresponding to the link resource.
	@return resource state updater for the specified Link Resource.
	*/
	virtual ILinkResourceStateUpdater* QueryStateUpdater(const URI& inAssetURI, IDataBase* db) = 0;

	/*
	Gets the resource server api wrapper for the specified uri.
	@param inAssetURI [IN] uri scheme e.g aem/file/cclibrary schemes of the Link Resource.
	@param db [IN] database corresponding to the link resource.
	@return resource server api wrapper for the specified Link Resource.
	*/
	virtual IHTTPLinkResourceServerAPIWrapper* GetHTTPLinkResourceServerAPIWrapper(const URI& inAssetURI) = 0;

	/*
	Gets the resource server cache the specified uri.
	@param inAssetURI [IN] uri scheme e.g aem/file/cclibrary schemes of the Link Resource.
	@return resource server cache the specified Link Resource.
	*/
	virtual IHTTPLinkResourceServerCache* QueryHTTPLinkResourceServerCache(const URI& inAssetURI) = 0;

	/*
	Gets the resource connection for the specified uri.
	@param inAssetURI [IN] uri scheme e.g aem/file/cclibrary schemes of the Link Resource.
	@return resource connection for the specified Link Resource.
	*/
	virtual IHTTPLinkResourceConnection* QueryHTTPLinkResourceConnection(const URI& inAssetURI) = 0;

	/*
	Gets the URI Preprocessor for the specified uri.
	@param inAssetURI [IN] uri scheme e.g aem/file/cclibrary schemes of the Link Resource.
	@return URI Preprocessor for the specified Link Resource.
	*/
	virtual IHTTPLinkAssetURIPreprocessor* GetHTTPLinkAssetURIPreprocessor(const URI& inAssetURI) = 0;

	/**
	** For internal purpose only
	*/
	virtual void ReadWriteSnapshotForBackgroundThread(IPMStream* s) = 0;
};

#endif	// __IHTTPLinkManager__

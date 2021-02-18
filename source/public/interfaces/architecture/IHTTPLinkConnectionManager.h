//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IHTTPLinkConnectionManager.h $
//  
//  Owner: Arvinder Singh
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
#ifndef __IHTTPLinkConnectionManager__
#define __IHTTPLinkConnectionManager__

#include "IPMUnknown.h"
#include "LinksID.h"
#include "URI.h"

#include "IHTTPLinkResourceConnection.h"
#include "IHTTPLinkResourceStateBatchUpdater.h"

/*
 AdobePatentID="P7137-US"
 AdobePatentID="P7225-US"
 AdobePatentID="P7609-US"
*/

/**
This is manager class for handling http connections. It is responsible for
 maintaining cache for connections. In case connections is not already present,
 it asks IHTTPLinkResourceConnection object for specified URI from
 IHTTPLinkManager.h.
*/
class IHTTPLinkConnectionManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHTTPLINKCONNECTIONMANGER };

	/*
	HTTP Connection Result Enum
	*/
	enum HTTPConnectionResult
	{
		kHTTPConnectionResult_Success,
		kHTTPConnectionResult_Error,
		kHTTPConnectionResult_Unknown
	};

	/**
	Initializes the HTTP Link Connection Manager
	@return kTrue if the Http Link Connection Manager is initialized else kFalse
	*/
	virtual bool16 Initialize() = 0;

	/**
	Shuts down the HTTP Link Connection Manager
	@return kTrue if the Http Link Connecton Manager is shutdown else kFalse
	*/
	virtual bool16 Shutdown() = 0;

	/*
	Gets the HTTP Link Resource Connection for the input URI
	@param inAssetURI [IN] uri of the HTTP Asset.
	@return HTTP Link Resource Connection for the given URI.
	*/
	virtual IHTTPLinkResourceConnection* GetHTTPConnection(const URI& inAssetURI) = 0;

	/*
	Releases the input HTTP Link Resource Connection
	@param inConnection [IN] HTTP Link Resource Connection.
	@return kHTTPConnectionResult_Success on succesful release of the connection given by inConnection.
	*/
	virtual HTTPConnectionResult ReleaseHTTPConnection(IHTTPLinkResourceConnection* inConnection) = 0;

	/*
	Gets the HTTP Batch updater for the HTTP Link Resource Connection.
	@param inConnection [IN] HTTP Link Resource Connection.
	@return HTTPLinkResourceStateBatchUpdater for the given HTTP Link Resource Connection.
	*/
	virtual IHTTPLinkResourceStateBatchUpdater* GetHTTPResourceStateBatchUpdater(IHTTPLinkResourceConnection* inConnection) = 0;

	/**
	** For internal purpose only
	*/
	virtual void ReadWriteSnapshotForBackgroundThread(IPMStream* s) = 0;
};

#endif	// __IHTTPLinkConnectionManager__

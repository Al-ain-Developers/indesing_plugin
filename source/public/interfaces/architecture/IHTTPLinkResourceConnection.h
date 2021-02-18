//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IHTTPLinkResourceConnection.h $
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
#ifndef __IHTTPLinkResourceConnection__
#define __IHTTPLinkResourceConnection__

#include "IPMUnknown.h"
#include "IPMStream.h"

#include "LinksID.h"
#include "PMString.h"

/*
 AdobePatentID="P7137-US"
 AdobePatentID="P7225-US"
 AdobePatentID="P7609-US"
*/

/**
IHTTPLinkResourceConnection deals with connection details of the server.
It contains function related to connection with server. Use this interface to implement logic
related to login details, passing session token etc. This interface is largely for client plugin usage
to handle connection related operations.
 
To subclass create a boss based on kHTTPAssetLinkResourceHelperBoss with the implementation of this
interface. And return this connection instance from the IHTTPLinkSubsystemObjectFactory. It is
mandatory to implement this interface for creating new plugin to handle particular scheme.
*/
class IHTTPLinkResourceConnection : public IPMUnknown
{
public:

	//[TODO] decide on type
	typedef PMString ConnectionId;

	enum { kDefaultIID = IID_IHTTPLINKRESOURCECONNECTION };

	/**
	Shuts down the current connection
	@return kTrue if the Http Connection is shutdown else kFalse
	*/
	virtual bool16 Shutdown() = 0;

	/**
	Checks if the current connection is connected
	@return kTrue if the Http Connection is connected else kFalse
	*/
	virtual bool16 IsConnected() const = 0;

	/**
	Checks if the current connection is authorized
	@return kTrue if the Http Connection is authorized else kFalse. 
	*/
	virtual bool16 IsAuthorized() const = 0;

	/**
	Creates/Logs-in the current connection
	@return kTrue if connection is created/logged-in successfully else kFalse.
	*/
	virtual bool16 Connect() = 0;

	/**
	Reconnects the current connection
	@return kTrue if re-connection is successful else kFalse
	*/
	virtual bool16 Reconnect() = 0;

	/**
	Disconnects the current connection
	@return kTrue if the connection is disconnected else kFalse
	*/
	virtual bool16 Disconnect() = 0;

	/**
	Fetches the connection ID for the current connection
	@return ConnectionId for the current connection
	*/
	virtual ConnectionId GetConnectionId() = 0;

	/**
	Gets the login credentials for the given connection. Its intepretation depends on client.
    For example, they can combine their login data into stream, which can be interpreted in their API wrapper.
    Note - Type of parameter as stringstream still not final. Other options like IPMStream are still under evaluation.
	@param loginInformation		[OUT]  The login information that requires to be set for the given connection
	@return kFalse if credentials could not be encoded, else kTrue
	*/
    virtual bool16 GetLoginCredentials(std::stringstream& loginInformation) const = 0;

    /**
	Sets the login credentials for the given connection. Client plugins before connecting can set their information
    using this stream. And within the implementation they can parse and store as per their needs.
    Note - Type of parameter as stringstream still not final. Other options like IPMStream are still under evaluation.
	@param loginInformation		[IN]  The login information that requires to be set for the given connection
	@return kTrue if credentials are set
	*/
    virtual bool16 SetLoginCredentials(const std::stringstream& loginInformation) = 0;

    /**
     Used when snapshot is created for the object for running in background thread. Snapshots are used in
     some of the InDesign workflows like PDF export, to pass objects for processing in background thread.
     In this function, object should write relevant data into stream or read from it to create necessary data
     depending on type of stream.
     @param s stream for reading/writing object's data
     */
	virtual void ReadWriteSnapshotForBackgroundThread(IPMStream* s) = 0;
};

#endif  // __IHTTPLinkResourceConnection__

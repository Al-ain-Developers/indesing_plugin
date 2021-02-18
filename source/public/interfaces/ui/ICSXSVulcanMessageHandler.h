//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ICSXSVulcanMessageHandler.h $
//  
//  Owner: Reena Agrawal
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
//  Copyright 1997-2014 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __ICSXSVulcanMessageWrapper__
#define __ICSXSVulcanMessageWrapper__

#include "IPMUnknown.h"
#include "CSXSID.h"

class ICSXSVulcanMessageHandler : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICSXSVULCANMESSAGEHANDLER } ;

	typedef void (*MessageListenerFn) (const std::string& message);

	/**
	 * Send a message to an application.
	 *
	 * @param messageType Message type, this is used by the listener to process the messages.
	 * @param appId Application ID of the application to which this message will be sent to.
	 * @param appVersion Application Version of the application to which this message will be sent to. This can be empty as well.
	 * @param message Message payload.
	 *
	 * For example, this can be called as:
		vulcanMessage->SendMessage("com.adobe.indesign", "IDSN", "10.0", kSnipRunHelloCSXSMessage); 
	 */
	virtual void SendMessage(const std::string &messageType, const std::string& appId, const std::string& appVersion, const std::string& message) = 0;

	/**
	 * Adds a listener for vulcan messages
	 *
	 * @param messageListener Listener to add.
	 * @param messageType The message type the listener listens to.
	 */
	virtual void AddMessageListener(MessageListenerFn messageListener, const std::string &messageType) = 0;

	/**
	 * Removes a listener already added.
	 *
	 * @param messageListener Listener to remove.
	 * @param messageType The message type the listener listens to.
	 */
	virtual void RemoveMessageListener(MessageListenerFn messageListener, const std::string &messageType) = 0;

} ;

#endif

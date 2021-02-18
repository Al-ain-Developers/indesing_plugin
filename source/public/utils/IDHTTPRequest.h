//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/utils/IDHTTPRequest.h $
//  
//  Owner: Mainak Biswas
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
//  Copyright 2015 Adobe Systems Incorporated. All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by all applicable intellectual property
//  laws, including trade secret and copyright laws.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//  
//  Description:
//  This class provides a wrapper over traditional uxtech::network:HTTPRequest implementation. The benefit of using this class is that any additional setup, like setting up 
//  request to communicate over authenticated proxy is automatically taken care of.

//  Currently This class only takes care of proxy related setup. Internally proxy credentials are shared between Adobe applications and this class uses the same internal 
//  mechanism to setup proxy credentials without exposing the credentials to users of this implementation.
//  
//  Currently this class provides very limited functionality. All network related API (like setting headers, reading response received etc) will be incrementally exposed via this 
//  implementation. 
//
//  TODO: Expose more networking API from this class to make it more usable.
//  
//========================================================================================

#pragma once
#ifndef __IDHTTPREQUEST_H__
#define __IDHTTPREQUEST_H__

#include <uxtech/common/functional.hpp>
#include <uxtech/network/async_http.hpp>
#include <uxtech/thread/queue.hpp>

class PUBLIC_DECL IDHTTPRequest
{
public:
	typedef UXTECH_FUNCTION<void(IDHTTPRequest& request, uxtech::network::HttpResult result)>	AsyncIDHttpRequestNotifier;

	IDHTTPRequest();
	virtual ~IDHTTPRequest();

	/**
	Sets the Url for HTTP call
	@param url   [IN] url for HTTP call
	*/
	virtual void SetUrl(const std::string url) { mUrl = url; }

	/**
	Sets the Method(GET,POST,etc) for HTTP call
	@param method   [IN] method for HTTP call
	*/
	virtual void SetMethod(const std::string method) { mMethod = method; }

	/**
	Gets the url for HTTP call
	@return url for HTTP call
	*/
	virtual std::string GetUrl() { return mUrl; };

	/**
	Gets the Method(GET,POST,etc) for HTTP calls
	@return method for HTTP call
	*/
	virtual std::string GetMethod() { return mMethod; };

	/**
	Execute the HTTP request in an asynchronous manner once it has been set up. This function returns immediately. Care must be taken so that
	IDHTTPREquest is not destroyed by the time the http request actually completes.
	@param notifier     [IN] A reference to the callback function that will be called on request completion.
	@param threadqueue  [IN] A reference to the queue object in which this asynchronous task will be scheduled.
	*/
	virtual void ExecuteAsync(const AsyncIDHttpRequestNotifier& notifier, const uxtech::thread::QueuePtr& threadqueue);

	/**
	Execute the HTTP request in an asynchronous manner once it has been set up. Returns the corresponding response code, i.e. 200 OK or 404 NOT FOUND etc.
	For asynchronous implementation use ExecuteAsync.
	*/
	virtual uxtech::network::HttpResult ExecuteSync();

	// Private use - called during application shutdown explicitly to clean up any statically allocated IMSConnectionManager object references.
	static void CleanupOnShutdown();

private:
	std::string mUrl;
	std::string mMethod;
	uxtech::network::HttpRequestPtr mRequest;
	AsyncIDHttpRequestNotifier mNotifier;

	void AsyncUxtechHTTPResponseHandler(const uxtech::network::AsyncHttpRequestPtr& task, uxtech::network::HttpResult httpResult, const uxtech::network::HttpRequestPtr& request);
};

#endif
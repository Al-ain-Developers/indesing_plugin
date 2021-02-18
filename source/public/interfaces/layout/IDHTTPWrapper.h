//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDHTTPWrapper.h $
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
//  Copyright 2015 Adobe Systems Incorporated. All rights reserved.
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
#ifndef __IDHTTPWrapper__
#define __IDHTTPWrapper__

#include "HTTPLinkSubsystemTypes.h"

#include "LinksID.h"

#include "boost/config.hpp" 
#include "boost/shared_ptr.hpp" 
#include "boost/function.hpp" 

/*
*/

namespace IDHTTPWrapper
{
//public:
	//enum { kDefaultIID = IID_IDHTTPWRAPPER };
	
	class PUBLIC_DECL  RequestID;
	class PUBLIC_DECL  Response;

	typedef WideString URL;
	typedef std::string Payload;

	class PUBLIC_DECL  RequestIDImpl;
	class PUBLIC_DECL  RequestID
	{
	public:
		RequestID(RequestIDImpl *impl);
		
		void DeleteRequest();

	private:
		boost::shared_ptr<RequestIDImpl> fImpl;
	};

	class PUBLIC_DECL ResponseImpl;
	class PUBLIC_DECL Response
	{
	public:
		Response(ResponseImpl *impl);
		/*
		Checks from response if there is network connectivity error
		*/
		bool16 IsNetworkConnectivityError() const;
		/*
		Checks from response if there is client error
		*/
		bool16 IsClientError() const;
		/*
		Checks from response about request authorization
		*/
		bool16 IsNotAuthorized() const;
		/*
		Checks from response if request is forbidden
		*/
		bool16 IsForbidden() const;

		/*
		Fetches response status code
		*/
		int32  GetStatus() const;

		/*
		Fetches payload from response.
		*/
		Payload GetPayload() const;

		/*
		Fetches HTTP headers.
		*/
		HTTPLinkSubsystemTypes::Headers GetHeaders() const;

	private:
		boost::shared_ptr<ResponseImpl> fImpl;
	};

	typedef boost::function<void(RequestID, Response)> CompletionFunction;


	class PUBLIC_DECL HTTP {
	public:
		/*
		API for GET method invocation
		@param inCompletionFunction [IN] completionFunction to be invoked at the GET request completion
		@param inURL				[IN] inURL of the request
		@param inTimeoutInMS		[IN] time out for the request with default time out set as 2 seconds
		@return kTrue on success else kFalse
		*/
		 bool16 GET(
			const CompletionFunction& inCompletionFunction,
			const URL& inURL,
			const int inTimeoutInMS = 2000, // 0 means non-blocking
			const HTTPLinkSubsystemTypes::Headers& inHeaders = HTTPLinkSubsystemTypes::Headers());

		 /*
		 API for POST method invocation
		 @param inCompletionFunction	[IN] completionFunction to be invoked at the POST request completion
		 @param inURL					[IN] inURL of the request
		 @param payload					[IN] payload for the POST request
		 @param inTimeoutInMS			[IN] time out for the request with default time out set as 2 seconds
		 @param inHeaders				[IN] Headers for the POST request
		 @return kTrue on success else kFalse
		 */
		 bool16 POST(
			const CompletionFunction& inCompletionFunction,
			const URL& inURL,
			const Payload &payload,
			const int inTimeoutInMS = 2000, // 0 means non-blocking
			const HTTPLinkSubsystemTypes::Headers& inHeaders = HTTPLinkSubsystemTypes::Headers());
	
		 /*
		 Helper to execute a function in the main thread
		 @param inFn					[IN] Function to be called Asynchronously
		 @param inDelayInMilliseconds	[IN] delay after which the function is to be invoked (deafult is immediate invocation)
		 */
		bool AsyncCallFromMainThread(const boost::function<void()>& inFn, unsigned int inDelayInMilliseconds = 0);
	};
};

#endif
//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IFlashPlayerController.h $
//  
//  Owner: Sanjay Kumar
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
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

#ifndef __IFlashPlayerController__
#define __IFlashPlayerController__

#include "IPMUnknown.h"
#include "AppUIID.h"

/**
	This interface is on kOWLFlashPlayerWidgetBoss and it is used to control 
	the flash movie hosted in the widget. 
*/
class IFlashPlayerController : public IPMUnknown
{
	public :			
		enum { kDefaultIID = IID_IFLASHPLAYERCONTROLLER };

		/**
		 * IFlashPlayerController calls this function to report the results of LoadContent. If the Flash Player is deleted before
		 * the load completes, the callback will not be called.
		 * -----
		 * @param inRefPtr [IN]: the client reference pointer passed in the LoadContentParams struct when callback was registered.
		 * @param inErrorCode [IN]: kSuccess if the content was loaded successfully, otherwise kFailure.
		 */
		typedef void (*LoadContentCallback)( void* inRefPtr, ErrorCode inErrorCode);

		enum ContentType {
			kFirstContentType = 0,
			kSWFContentType = 0,
			kComponentContentType,
			kLastContentType,
		};

		struct LoadContentParams{

			/**
			 *	If kFalse, content is A Component, otherwise content is a naked SWF.
			 */
			ContentType fContentType;

			/**
			 *	If kFalse, content is loaded asynchronously, otherwise content is loaded synchronously.
			*/
			bool16 fLoadSynchronously;

			/**
			 *	The path to the component or SWF to be loaded. This argument must either
			 *  be a URL (preferred) or a full filesystem path.
			 */
			PMString fUrl;

			/**
			 *	Optional callback function to be invoked after the content is loaded(for asynchronous requests only).
			 */
			LoadContentCallback	fCallback;
	
			/**
			 *	Optional client reference pointer to pass to callback on invocation.
			 */
			void*	fRefPtr;

			LoadContentParams():fContentType(kComponentContentType),fLoadSynchronously(kTrue),fUrl(),fCallback(nil),fRefPtr(0){}

		} ; 

		/**
			Load initial content into the player.
		  
			a.	A naked SWF is normally loaded into a non-application sandbox and treated like in the 
				Flash Player browser plugin. AIR-related APIs are not available.(kSWFContent)

			b.	A Component is similar to an AIR application in that it includes an XML descriptor 
				and undergoes an installation process to validate its signatures. (kComponentContent)
				A Component runs in the application sandbox and has full access to all
				ActionScript APIs, including EncryptedLocalStore. 

				Supporting the Development Process

				To support component development, a Component also supports a debugging mode
				similar to what ADL supports for AIR applications. If the path supplied  with 
				a Component refers to a directory that is not an installed Component,
				but contains an Component descriptor file, LoadContent will load the content referenced
				by the descriptor and enable debugging for the session.

				Until the Component development tools are fully operational, IFlashPlayerController will temporarily allow
				use of AIR application structures in the place of Components. If the path supplied with
				LoadContent for a Component is to the resources of an installed AIR application (the application
				directory on Windows and the Resources directory on Mac), LoadContent will load
				the content specified by META-INF/AIR/application.xml. If the path supplied to
				LoadContent for a Component contains a single XML file that is a valid AIR application descriptor,
				LoadContent will load the content referenced by the descriptor and enable debugging
				for the session.

				The order of priority for these different options are:
					1. A Component directory
					2. AIR resources directory
					3. A Component descriptor
					4. AIR application descriptor

			Note that at most one thing can be loaded into a player instance(LoadContent can be called only once)

		   @param inLoadContentParams [IN]: pointer to a LoadContentParams structure.
		   @return ErrorCode: kSuccess if successful, kFailure if the fPath field is NULL or if
							  LoadContent more than once on a given instance.
		**/
		virtual ErrorCode LoadContent(const LoadContentParams& inLoadContentParams) = 0;

		/** DEPRECATED
			Use LoadContent Instead.

			Load a naked SWF into the player.

			@param url [IN]: the location. 
			@return ErrorCode: return kSuccess if load movie successfully; otherwise return kFailure.
		**/
		virtual ErrorCode LoadSWF(const PMString& url) = 0;

		/** DEPRECATED
			Use LoadContent Instead.

			Load an A Component into the player.

			@param url [IN]: the location. 
			@return ErrorCode: return kSuccess if load movie successfully; otherwise return kFailure.
		**/
		virtual ErrorCode LoadComponent(const PMString& url) = 0;

		/**
			Call a movie function of the player.
			@param inRequest [IN]: the input parameter.
			@param outRequest [OUT]: the output parameter.
			@return ErrorCode: return kSuccess if action is successful; otherwise return kFailure.
		*/
		virtual ErrorCode CallMovieFunction(const PMString& inRequest, PMString& outRequest) const = 0;

		/**
			The signature for a callback handler for when the control's movie invokes an application function.
			@param inRequest [IN]: the input parameter.
			@param inRefPtr [IN]: the client reference pointer passed when callback was registered.
			@return the result to return to the movie.
		*/
		typedef PMString (*AppFunctionCallback)( const PMString& inRequest, void* inRefPtr ) ;
		/**
			Set the callback handler for when the control's movie invokes an application function.
			@param inCallback [IN]: the function to be called when the control's movie invokes an application function.
			@param inRefPtr [IN]: a client reference pointer to pass to callback on invocation.
			@return ErrorCode: return kSuccess if successful; otherwise return kFailure.
		*/
		virtual ErrorCode SetAppFunctionCallback( AppFunctionCallback inCallback, void* inRefPtr ) = 0;


		enum URLRequestResult
		{
			kDenied,	// URL is denied 
			kPassed,	// URL is passed to the player
			kServed		// URL is served	
		};

		/**
			The signature for a callback handler for when the SWF requests data from a URL.
			This can be used by clients to deny access to certain URLs or to provide the data themself.
			@param inUrl [IN]: the URL that the SWF requests.
			@param inRefPtr [IN]: the client reference pointer passed when callback was registered.
			@param outResult [OUT]: whether the URL is denied, passed, or served.
			@return the AddRef-ed stream that contains the data if outResultis kServed. nil otherwise.
		*/
		typedef IPMStream* (*RequestUrlCallback) (const PMString& inUrl, void* inRefPtr, URLRequestResult& outResult);
		/**
			Set the callback handler for when the control's SWF requests data from a URL.
			@param inCallback [IN]: the function to be called when the control's SWF requests data from a URL.
			@param inRefPtr [IN]: a client reference pointer to pass to callback on invocation.
			@return ErrorCode: return kSuccess if successful; otherwise return kFailure.
		*/
		virtual ErrorCode SetRequestUrlCallback(RequestUrlCallback inCallback, void* inRefPtr ) = 0;

		/**
			Load a naked SWF from a resource
		    @param pid [IN]: plugin id where the swf file is from
			@param rid [IN]: resource id where the swf file is from
			@return ErrorCode: return kSuccess if load is successful; otherwise return kFailure.
		*/
		virtual ErrorCode LoadMovieFromResource(const PluginID & pid, const RsrcID & rid)= 0;

		/**
			Internal use only.
			Handles the asynchronous content loaded event from the player.
			Calls LoadContentCallback if it's been set.
			@param inLoadStatus [IN]: the status of content load
		*/
		virtual void HandleContentLoadedEvent(bool16 inLoadStatus) = 0;

		/**
			Internal use only.
			Handles the app-function event from the player.
			Calls AppFunctionCallback if it's been set.
			@param inRequest [IN]: the ActionScript XML doclet from the player.
			@param outResponse [OUT]: the response from AppFunctionCallback.
			@return kTrue if event has been handled, kFalse otherwise.
		*/
		virtual bool16 HandleAppFunctionEvent(const PMString& inRequest, PMString& outResponse) const = 0;

		/**
			Internal use only.
			Handles the url request event from the player.
			Calls RequestUrlCallback if it's been set.
			@param inUrl [IN]: the URL that the SWF requests.
			@param outResult [OUT]: whether the URL is denied, passed, or served.
			@return the AddRef-ed stream that contains the data if outResultis kServed. nill otherwise.
		*/
		virtual IPMStream* HandleRequestUrlEvent(const PMString& inUrl, URLRequestResult& outResult) const = 0;

		/**
			Returns whether to enable debugging on the Flash player.
		*/
		virtual bool16 GetEnableDebugging() const = 0;

		/**
			Set whether to enable debugging on the Flash player.
			Use this before loading content in the SWF.
		*/
		virtual void SetEnableDebugging(bool16 enable) = 0;

		/**
			Initialize the High-Bandwidth API to enable communication between the SWF's ActionScript
			DOM and the host application's ExtendScript DOM. This method should be called before the 
			SWF is loaded in the flash player, since the SWF's initialization code may wish to use 
			the HB API to talk to the host. This overload will use the default host object package name
			(e.g., "com.adobe.indesign").
			@param engineName [IN] - the name of the ExtendScript engine to connect. The engine must already exist.
		*/
		virtual void InitializeHBAPI( const PMString& engineName ) = 0 ;
		/**
			Initialize the High-Bandwidth API using a custom package name.
			@param engineName [IN] - the name of the ExtendScript engine to connect. The engine must already exist.
			@param packageName [IN] - the HBAPI host object package name
			@param isAdditional [IN] - pass false for the main extension, true for additional extensions
		*/
		virtual void InitializeHBAPI( const PMString& engineName, const PMString& packageName, bool16 isAdditional = kFalse ) = 0 ;
		/**
			Disable the High-Bandwidth API link that was established via a prior call to InitializeHBAPI.
			If InitializeHBAPI has been called, this method should be called before unloading the Flash 
			Player movie to break internal connections and to invalidate pointers.
			@param engineName - the name of the ExtendScript engine to disconnect
		*/
		virtual void UninitializeHBAPI( const PMString& engineName ) = 0 ;
};

#endif

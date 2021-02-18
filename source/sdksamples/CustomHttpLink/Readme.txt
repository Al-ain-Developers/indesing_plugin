//========================================================================================
//  
//  $File: //depot/shuksan/source/sdksamples/CustomHttpLink/Readme.txt $
//  
//  Owner: swagarg
//  
//  $Author: swagarg $
//  
//  $DateTime: 2019/05/31 08:29:54 $
//  
//  $Revision: #1 $
//  
//  $Change: 1049065 $
//  
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

### To set up local nodejs server:

- Navigate to localserver directory
- Install nodejs from their website (https://nodejs.org/en/)
- To install the required packages, run following command:
	$ npm install
- Run following command to start the server
	$ node index.js
- If everything is working, console should display "server is listening on 3000"
- Add assets named "asset1.jpg", "asset2.jpg", "asset3.jpg", ..., "asset10.jpg" to the "/image/" directory. Add their corresponding low resolution versions with same name to the "/image/fpo/" directory.


To create custom plugins to handle http calls, first a scheme needs to be implemented. Since http scheme can be used by many plugins, so it is advised to use custom scheme. Benefit of using scheme based system is that it is not dependent on server URI/address. So its easy to distribute plugin. Scheme name should be used wisely so that it doesn't end up clashing with another plugin. In such cases plugin which registers scheme first, will be given priority, also assert will be shown in those case.
1. 	Implement IHTTPLinkSubsystemObjectFactory interface on the http link resource connection provider boss that is registered with the service registry as a 
	kHTTPLinkResourceConnectionProvider. This is mandatory step. Look into CustomHttpLink.fr for reference:
	Class
    {
        kCusHttpLnkLinkResourceProviderBoss,
        kInvalidClass,
        {
            IID_IK2SERVICEPROVIDER,                kHTTPLinkSubsystemObjectProviderImpl,
            IID_IHTTPLINKSUBSYSTEMOBJECTFACTORY,   kCusHttpLnkLinkResourceFactoryImpl,
        }
    },
    Implementation should return list of schemes plugin supports. For this example we registering "myhost" scheme. It creates objects when query functions are used. It return four objects : handler, stateupdater, connection and wrapper object. Custom impplementations can be return from these functions.
    MANDATORY INTERFACES that needs to implemented are : IID_IHTTPLINKRESOURCESERVERAPIWRAPPER, IID_IHTTPLINKRESOURCECONNECTION. For others default implementation can be used. They are discussed in details below.
2.	Thes are useful boss objects and interfaces which are related to http links implementation:
	i. kHTTPAssetLinkResourceServerHelperBoss: This include following interfaces:
		a. IID_IHTTPLINKRESOURCESERVERAPIWRAPPER - Mandatory to implement. IHTTPLinkResourceServerAPIWrapper deals with high level server API/functionalities. 
			Some of its reposibilities include fetching metadata, checking server connection , generation of session token etc. This is mandatory implementation. To subclass create a boss based on kHTTPAssetLinkResourceServerHelperBoss with the implementation of this interface. And return this connection instance from above implementation of IHTTPLinkSubsystemObjectFactory. Refer CusHttpLnkResourceServerAPIWrapper.cpp and CusHttpLnkLinkResourceFactory.cpp.
		b. IID_IHTTPLINKRESOURCESERVERCACHE - This interface provides deals with caching mechanism for files and metadata for HTTP links. This interface is 			responsible for storing asset metadata. Ideally it should persist across the session. Also it should clear cache and metadata also, so that it doesn't 
			bloat. To subclass create a boss based on kHTTPAssetLinkResourceServerHelperBoss with the implementation of this interface. And return this connection instance from the IHTTPLinkSubsystemObjectFactory.
		c. IID_IHTTPASSETDOWNLOADMANAGER - IHTTPAssetDownloadManager manages downloads for http link assets(see IHTTPLinkSubsystemObjectFactory.h for more details). 
			It is called when specific asset is not found in cache from IHTTPLinkResourceServerCache. Include this interface on http asset link resource server helper boss which is registered as kHTTPAssetLinkResourceServerHelperBoss. For custom implementation aggregrate this interface with  IID_IHTTPLINKRESOURCESERVERAPIWRAPPER on kHTTPAssetLinkResourceServerHelperBoss.
		d. IID_IHTTPLINKASSETURIPREPROCESSOR - This interface is experimental and for internal use only.
	ii. kHTTPAssetLinkResourceHelperBoss - 
		a. IID_IHTTPLINKRESOURCECONNECTION - Mandatory to implement. IHTTPLinkResourceConnection deals with connection details of the server. It contains function
			related to connection with server. Use this interface to implement logic related to login details, passing session token etc.
		b. IID_IHTTPLINKRESOURCESTATEBATCHUPDATER -  IHTTPLinkResourceStateBatchUpdater contains functions for updating states in batch mode. This will only be used 	 when web-api supports batch mode. For custom imlementation return true from SupportsHTTPResourceStateBatchUpdater function of 
			IHTTPLinkResourceServerAPIWrapper.Then subclass this interface by creating a boss based on kHTTPAssetLinkResourceHelperBoss with the implementation of this interface.
	iii. IID_ILINKRESOURCESTATEUPDATER - If plugin needs to change how metadata is handled or state updation logic. This interface can be implemented to alter it. 
			Look into kCusHttpLnkLinkResourceStateUpdaterBoss in CustomHttpLink.fr. Currently it is stub implementation, functions can be overriden to alter implementations. Derive from HTTPAssetLinkResourceStateUpdater to alter its functionalities.
	iv. kHTTPAssetLinkResourceHandlerBoss: 
		a. IID_ILINKRESOURCEHANDLER : To change behaviour of HTTPAssetLinkResourceHandler. Implement this interface and derive from HTTPAssetLinkResourceHandler. 
			one such interface is showcased in CusHttpLnkLinkResourceHandler.cpp. If you want different resource to be displyed in UI and different name for 
			internal use, GetLongResourceName can be overriden. Refer to publiclib/links/HTTPAssetLinkResourceHandler.cpp
		b. IID_ILINKRESOURCEHELPERHANDLER : In CusHttpLnkLinkResourceHelperHandler, ReplaceWithOriginalAsset is used to perform action(
			kReplaceFPOWithOriginalLinkActionID).

     


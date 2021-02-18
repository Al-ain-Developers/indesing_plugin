//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/CustomHttpLink/CusHttpLnkLinkResourceHandler.cpp $
//
//  Owner: Adobe Developer Technologies
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
//  Copyright 2019 Adobe
//  All Rights Reserved.
//
//  NOTICE: Adobe permits you to use, modify, and distribute this file in
//  accordance with the terms of the Adobe license agreement accompanying
//  it. If you have received this file from a source other than Adobe,
//  then your use, modification, or distribution of it requires the prior
//  written permission of Adobe. 
//
//========================================================================================

#include "VCPlugInHeaders.h"

#include "CustomHttpLinkID.h"
#include "HTTPAssetLinkResourceHandler.h"

/**
 Provide methods to manipulate the resource
 
 @ingroup customhttplink.sdk
 */

class CusHttpLnkLinkResourceHandler : HTTPAssetLinkResourceHandler
{
public:
	typedef HTTPAssetLinkResourceHandler inherited;
	typedef object_type data_type;

	CusHttpLnkLinkResourceHandler(IPMUnknown* boss);
	virtual ~CusHttpLnkLinkResourceHandler();

	virtual WideString GetLongResourceName(const UIDRef& ref, const URI& uri, bool bUIName) const;

	virtual bool IsHTTPSSupportedURI(const URI& uri) const;

    virtual bool canGetInstanceName() const ;
    
    virtual ErrorCode GetInstanceName(PMString &uri) const ;
    
private:
	// Prevent copy construction and assignment.
	CusHttpLnkLinkResourceHandler(const CusHttpLnkLinkResourceHandler&);
	CusHttpLnkLinkResourceHandler& operator=(const CusHttpLnkLinkResourceHandler&);
};

CREATE_PMINTERFACE(CusHttpLnkLinkResourceHandler, kCusHttpLnkLinkResourceHandlerImpl)

/* Constructor
*/
CusHttpLnkLinkResourceHandler::CusHttpLnkLinkResourceHandler(IPMUnknown* boss)
: inherited(boss)
{
}

/* Destructor
*/
CusHttpLnkLinkResourceHandler::~CusHttpLnkLinkResourceHandler()
{
}

/* IsHTTPSSupportedURI
*/
bool CusHttpLnkLinkResourceHandler::IsHTTPSSupportedURI(const URI& uri) const
{
	return false;
    // return true if https is also supported
}

/* GetLongResourceName
*/
WideString CusHttpLnkLinkResourceHandler::GetLongResourceName(const UIDRef& ref, const URI& uri, bool bUIName) const
{
    // Return resource name from cache, if already present
    if (bUIName && !fLongUINameCache.empty())
    {
        return fLongUINameCache;
    }
    if (!fLongNameCache.empty())
        return fLongNameCache;

    // else, Generate resource name using uri
    URI assetURI(uri);
    assetURI.SetComponent(URI::kScheme, kHTTPAssetURIScheme);
    WideString wUri;
    URICommonUtils::URIEncodingToWideString(assetURI.GetURI(), wUri);
    fLongNameCache = wUri;
    
    // Currently, fLongUINameCache and fLongNameCache are same
    // These can be made different if we wish to show different path
    // in UI and different for internal use
    fLongUINameCache = fLongNameCache;

	return bUIName ? fLongUINameCache : fLongNameCache;
}

/*
 canGetInstanceName
 */
bool CusHttpLnkLinkResourceHandler::canGetInstanceName() const
{
    return kTrue;
}

/*
 GetInstanceName
 */
ErrorCode CusHttpLnkLinkResourceHandler::GetInstanceName(PMString &uri) const
{
    uri.SetString(kCusHttpLnkServerURL);
    uri.SetTranslatable(kFalse);
    return kSuccess;
}

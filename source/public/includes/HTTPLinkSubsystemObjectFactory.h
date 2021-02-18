//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/HTTPLinkSubsystemObjectFactory.h $
//  
//  Owner: Sanyam Jain
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
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

#ifndef __HTTPLinkSubsystemObjectFactory__
#define __HTTPLinkSubsystemObjectFactory__

#include "CPMUnknown.h"

#include "IHTTPLinkSubsystemObjectFactory.h"
#include "IHTTPLinkResourceConnection.h"
#include "IHTTPLinkResourceServerAPIWrapper.h"
#include "ILinkResourceHandler.h"
#include "ILinkResourceStateUpdater.h"

#include "URI.h"

//========================================================================================
// Class HTTPLinkSubsystemObjectFactory
//========================================================================================
class PUBLIC_DECL HTTPLinkSubsystemObjectFactory : public CPMUnknown<IHTTPLinkSubsystemObjectFactory>
{
public:
	typedef CPMUnknown<IHTTPLinkSubsystemObjectFactory> inherited;

	HTTPLinkSubsystemObjectFactory(IPMUnknown* boss);
	virtual ~HTTPLinkSubsystemObjectFactory();

	virtual void GetSchemes(K2Vector<WideString>& schemes) const;

	/*
	@param uri [IN] uri of the Link Resource.
	@param db [IN] database corresponding to the link resource.
	@return resource handler for the specified Link Resource.
	*/
	virtual ILinkResourceHandler* QueryHandler(const URI& uri, IDataBase* db) const;

	/*
	@param uri [IN] uri of the Link Resource.
	@param db [IN] database corresponding to the link resource.
	@return resource state updater for the specified Link Resource.
	*/
	virtual ILinkResourceStateUpdater* QueryStateUpdater(const URI& uri, IDataBase* db) const;

	/*
	@param uri [IN] uri of the Link Resource.
	@param db [IN] database corresponding to the link resource.
	@return resource connection for the specified Link Resource.
	*/
	virtual IHTTPLinkResourceConnection* QueryHTTPLinkResourceConnection(const URI& uri, IDataBase* db) const;

	/*
	@param uriScheme [IN] uri scheme e.g aem/file/cclibrary schemes of the Link Resource.
	@param db [IN] database corresponding to the link resource.
	@return resource server api wrapper for the specified Link Resource.
	*/
	virtual IHTTPLinkResourceServerAPIWrapper* QueryHTTPLinkResourceServerAPIWrapper(const URI& uriScheme, IDataBase* db) const;

protected:

	/*
	@param uri [IN] uri of the Link Resource.
	@return true if the scheme of the uri is supported by the underlying system else false.
	*/
	bool16 IsURISchemeSupported(const URI& uri) const;

private:
	// Prevent copy construction and assignment.
	HTTPLinkSubsystemObjectFactory(const HTTPLinkSubsystemObjectFactory&);
	HTTPLinkSubsystemObjectFactory& operator=(const HTTPLinkSubsystemObjectFactory&);
};

#endif // __HTTPLinkSubsystemObjectFactory__
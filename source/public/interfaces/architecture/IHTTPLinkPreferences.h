//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IHTTPLinkPreferences.h $
//  
//  Owner: Arvinder Singh
//  
//  $Author $
//  
//  $DateTime $
//  
//  $Revision $
//  
//  $Change $
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
#ifndef __IHTTPLinkPreferences__
#define __IHTTPLinkPreferences__

#include "IPMUnknown.h"
#include "LinksID.h"

#include "ILinkResourceRenditionData.h"

/*
 AdobePatentID="P7137-US"
 AdobePatentID="P7225-US"
 AdobePatentID="P7609-US"
*/

class IHTTPLinkPreferences : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHTTPLINKPREFERENCES };

	/*
	Gets the default rendition type
	@return the default rendition type set to HTTP Link preference(Original/FPO)
	*/
	virtual ILinkResourceRenditionData::ResourceRenditionType GetDefaultRenditionType() const = 0;

	/*
	Set the rendition type specified by inAssetType to Http Link Preferences
	@param inAssetType [IN] Link Resource rendition type (Original/FPO)
	*/
	virtual void SetDefaultRenditionType(ILinkResourceRenditionData::ResourceRenditionType inAssetType) = 0;
};

#endif // __IHTTPLinkPreferences__

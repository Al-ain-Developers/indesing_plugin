//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IFileEditorAppsUtils.h $
//  
//  Owner: Adrian O'Lenskie
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
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
#ifndef __IFileEditorAppsUtils__
#define __IFileEditorAppsUtils__

#include "Utils.h"
#include "LinksID.h"
#include "AppInfo.h"

//This utility is written as wrapper on files M/WLinkUtilsHelper. These files contain the functions implementations to get the list of applications supported by any IDFile.

class IFileEditorAppsUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFILEEDITORAPPSUTILS };

	/**
	Get the list of applications supported by given IDFile.
	@param linkFile [IN] input file.
	@param bDefaultEditorOnly [IN] if to fill the list with only default editor
	@param appList [OUT] list which will be filled with all the applications supported by given IDFile.
	*/
	virtual void GetSupportedApplicationList(const IDFile& linkFile, AppInfoList& appList, const bool16 bDefaultEditorOnly = false) const = 0;
};

#endif	// __IFileEditorAppsUtils__

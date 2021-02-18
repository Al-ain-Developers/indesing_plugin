//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/components/links/FileEditorAppsUtils.cpp $
//  
//  Owner: Dave Stephens
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

#include "VCPlugInHeaders.h"
#include "IFileEditorAppsUtils.h"

//This file and both M/WLinkUtilsHelper.cpp are being moved to public folder so that its code can be used as reference when providing own implementations of GetSupportedApplicationList in sdk projects.
// Refer to ILinkResourceHandler.h for more details.

void _PlatformGetEditorList(const IDFile& linkFile, AppInfoList& appList, bool16 bDefaultEditorOnly); // implemented in M/WLinkUtilsHelper

class FileEditorAppsUtils : public CPMUnknown<IFileEditorAppsUtils>
{
public:

	FileEditorAppsUtils( IPMUnknown *boss );
	
	virtual void GetSupportedApplicationList(const IDFile& linkFile, AppInfoList& appList, const bool16 bDefaultEditorOnly = false) const;
};


CREATE_PMINTERFACE(FileEditorAppsUtils, kFileEditorAppsUtilsImpl)

//========================================================================================
// Constructor
//========================================================================================
FileEditorAppsUtils::FileEditorAppsUtils(IPMUnknown* boss) : CPMUnknown<IFileEditorAppsUtils>(boss)
{
}

void FileEditorAppsUtils::GetSupportedApplicationList(const IDFile& linkFile, AppInfoList& appList, const bool16 bDefaultEditorOnly) const
{
	_PlatformGetEditorList(linkFile, appList, bDefaultEditorOnly);
}

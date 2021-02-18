//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/components/links/MLinkUtilsHelper.cpp $
//  
//  Owner: lance bushore
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
#include "AppInfo.h"
#include "IDFile.h"
#include "MacFileUtils.h"
#include "FileUtils.h"
#include "FileUtility.h"

#include <boost/tokenizer.hpp>
typedef boost::char_separator<UniCodePoint> UTF32TextCharSeparator;
typedef boost::tokenizer<UTF32TextCharSeparator, WideString::const_iterator, WideString > WideTokenizer;

AppInfo _LookupDefaultAppForFile(const IDFile& theFile);
PMString _GetAppDisplayName (const PMString& path);
PMString _GetVersionInfoFromPath(const PMString& inPath);
OSType _GetCreatorFromPath(const PMString& inPath);
bool16 _FilterApp(const PMString& inPath);
bool16 _IsAdobeApp(const PMString& inPath);
CFBundleRef _GetBundleFromPath(const PMString& inPath);

//----------------------------------------------------------
// _PlatformGetEditorList
//
// NOTE:
// This code was based on AddSystemOpenWithApps taken from the Bridge team:
//		bridge/main/core/source/openappsupport/OpenWithApps.cpp#99
//
// See also:
// http://developer.apple.com/documentation/Carbon/Conceptual/LaunchServicesConcepts/LaunchServicesConcepts.pdf
//----------------------------------------------------------
void	_PlatformGetEditorList(const IDFile& linkFile, AppInfoList& appList, bool16 bDefaultEditorOnly)
{
	PMString extension;
	FileUtils::GetExtension(linkFile,extension);
	extension.ToLower();

	// 1. Add the default application to the app list
	AppInfo defaultApp = _LookupDefaultAppForFile(linkFile);
	if (!(defaultApp == kNullAppInfo))
		appList.push_back(defaultApp);	// Add default app

	// We might be done if requested to just get the default editor
	if (bDefaultEditorOnly)
		return;

	// 2. Gather all of the applications that will work with the file using LSCopyApplicationURLsForURL
	CFURLRef url = MacFileUtils::AFileToCFURLRef(linkFile);
	
	if (url != NULL)
	{
		CFArrayRef appArray = ::LSCopyApplicationURLsForURL (url, kLSRolesViewer | kLSRolesEditor);
		::CFRelease(url);
		
		if (appArray != NULL)
		{
			CFIndex numApps = ::CFArrayGetCount(appArray);  
			if (numApps > 0)
			{
				for (CFIndex i = 0; i < numApps; i++)
				{
					CFURLRef appURL = (CFURLRef)::CFArrayGetValueAtIndex(appArray, i);
					CFStringRef app_str = ::CFURLCopyFileSystemPath(appURL, kCFURLPOSIXPathStyle);
					PMString appPath;
					if (app_str)
					{
						appPath.SetCFString(app_str);
						::CFRelease(app_str);
					}
					
					bool16 bIsAdobeApp = _IsAdobeApp(appPath);
					PMString displayName = _GetAppDisplayName(appPath);
					PMString version = _GetVersionInfoFromPath(appPath);
					AppInfo appInfo(appPath, displayName, version, kFalse /* defaultApp */, bIsAdobeApp);
					
					if (K2find(appList, appInfo) == appList.end() && !_FilterApp(appPath))
						appList.push_back(appInfo);
				}
			}
			
			::CFRelease(appArray);
		}
	}
	
}


//----------------------------------------------------------
// GetAppDisplayName
//----------------------------------------------------------
PMString _GetAppDisplayName (const PMString& path)
{
	if (path.IsEmpty())
		return kNullString;

	PMString result;
	PMString displayName;

	// 1. Attempt to get a display name from the OS for the bundle in question
	CFStringRef pathRef = path.CreateCFString();
	if (pathRef != NULL)
	{
		CFURLRef bundleURL = ::CFURLCreateWithFileSystemPath(NULL, pathRef, kCFURLPOSIXPathStyle, true);
		if (bundleURL != NULL)
		{
			CFStringRef displayNameRef;
			OSStatus err = ::LSCopyDisplayNameForURL(bundleURL, &displayNameRef);
			if (err == noErr && displayNameRef)
			{
				displayName.SetCFString(displayNameRef);
				::CFRelease(displayNameRef);
			}
			::CFRelease(bundleURL);
		}
		::CFRelease(pathRef);
	}


	// 2. If a display name was not available from the OS, make one from the bundle name
	if (displayName.IsEmpty())
	{
		PMString bundleName(path);
		FileUtils::GetBaseFileName(bundleName, displayName);
	}

	return displayName;
}


//----------------------------------------------------------
// GetVersionInfoFromPath
//----------------------------------------------------------
PMString _GetVersionInfoFromPath(const PMString& inPath)
{
	PMString result;

	CFBundleRef bundle = _GetBundleFromPath(inPath);

	if (bundle != NULL)
	{
		UInt32 version = ::CFBundleGetVersionNumber(bundle);
		if (version != 0)
		{
			result.AppendNumber(int32(10 * ((version & 0xF0000000) >> 28) + ((version & 0x0F000000) >> 24)));
			result += ".";
			result.AppendNumber(int32((version & 0x00F00000) >> 20));
			int32 minorVersion = (int32)((version & 0x000F0000) >> 16);
			if (minorVersion != 0)
			{
				result += ".";
				result.AppendNumber(minorVersion);
			}
		}
		else
		{
			// This app didn't have a standard version number. Get a string.
			CFTypeRef longVersionString = ::CFBundleGetValueForInfoDictionaryKey(bundle, CFSTR("CFBundleShortVersionString"));
			if (longVersionString != NULL && ::CFGetTypeID(longVersionString) == ::CFStringGetTypeID())
			{
				result.SetCFString((CFStringRef)longVersionString);
			}
			if (result.IsEmpty())
			{
				CFTypeRef versionString = ::CFBundleGetValueForInfoDictionaryKey(bundle, kCFBundleVersionKey);
				if (versionString != NULL && ::CFGetTypeID(versionString) == ::CFStringGetTypeID())
				{
					result.SetCFString((CFStringRef)versionString);
				}
			}
		}
		::CFRelease(bundle);
	}

	// We no longer check the resource fork for the version resource. We just append a space to the result and return.
	if (result.IsEmpty())
		result = " ";

	return result;
}

//----------------------------------------------------------
// GetCreatorFromPath
//----------------------------------------------------------
OSType _GetCreatorFromPath(const PMString& inPath)
{
	OSType creator(0);

	CFBundleRef bundle = _GetBundleFromPath(inPath);
	if (bundle != NULL)
	{
		::CFBundleGetPackageInfo(bundle, NULL /* fileType */, &creator);
		::CFRelease(bundle);
	}

	// Try the good old HFS type/creator. This is necessary for droplets, which don't have bundle info.
	if (creator == 0)
	{
		IDFile file = FileUtils::PosixPathToSysFile(inPath.GetPlatformString());
		file.GetAttribute(AFile::kCreator, creator);
	}

	return creator;
}

//----------------------------------------------------------
// _LookupDefaultAppForFile
//
// Return the default application for this file
//----------------------------------------------------------
AppInfo _LookupDefaultAppForFile(const IDFile& theFile)
{
	PMString extension;
	FileUtils::GetExtension(theFile,extension);
	extension.ToLower();

	AppInfo result(kNullAppInfo);
	
	CFURLRef url = MacFileUtils::AFileToCFURLRef(theFile);
	
	if (url != NULL)
	{
		CFURLRef appURL = NULL;
		OSErr err = ::LSGetApplicationForURL (url, kLSRolesViewer | kLSRolesEditor, NULL, &appURL);
		::CFRelease(url);
		
		if (err == noErr)
		{
			CFStringRef app_str = ::CFURLCopyFileSystemPath(appURL, kCFURLPOSIXPathStyle);
			PMString appPath;
			if (app_str)
			{
				appPath.SetCFString(app_str);
				::CFRelease(app_str);
			}
			
			bool16 bIsAdobeApp = _IsAdobeApp(appPath);
			PMString displayName = _GetAppDisplayName(appPath);
			PMString version = _GetVersionInfoFromPath(appPath);
			result = AppInfo(appPath, displayName, version, kTrue /* defaultApp */, bIsAdobeApp);
		}
		
		if (appURL)
			::CFRelease(appURL);
	}
	

	return result;
}



//----------------------------------------------------------
// _FilterApp
// Filter out undesirable apps
//----------------------------------------------------------
bool16 _FilterApp(const PMString& inPath)
{
	OSType creator = _GetCreatorFromPath(inPath);

	// Exclude ImageReady and Photoshop droplets
	if (creator == '8BDR' || creator == 'MxSA')
	{
		return kTrue;
	}
	else
	{
		// Exclude applications that are inside other apps (like Opera)
		// e.g. /Applications/Adobe Bridge CS3/Bridge CS3.app/Contents/MacOS/Opera.app
		int32 appCount = 0;
		PMString exeExtension("app");

		UniCodePoint solidusSeparator[2] = { kTextChar_Solidus, kTextChar_Null };
		UTF32TextCharSeparator  separator(solidusSeparator);
		WideString inPathAsWS(inPath);
		WideTokenizer tokens( inPathAsWS, separator);

		// Count number of apps in this path. If greater than 1, it's a nested app.
		for (WideTokenizer::iterator i = tokens.begin(); i != tokens.end(); ++i)
		{
			PMString item = *i;
			if (!item.IsEmpty())
			{
				FileUtility f(item);
				PMString extension = f.GetExtension();
				if (extension.IsEqual(exeExtension, kFalse))
					appCount++;
			}
		}

		if (appCount > 1)
			return kTrue;
	}

	return kFalse;
}


//----------------------------------------------------------
// IsAdobeApp
//----------------------------------------------------------
bool16 _IsAdobeApp(const PMString& inPath)
{
	bool16 result = kFalse;

	OSType creator = _GetCreatorFromPath(inPath);

	// List of well-known Adobe apps.
	if (creator == 'Brdg' || 	// Bridge
		creator == 'GoMk' || 	// GoLive
		creator == 'ART5' || 	// Illustrator
		creator == 'ID30' ||	// InDesign ?
		creator == 'InDn' ||	// InDesign 4
		creator == '8BIM' || 	// Photoshop
		creator == 'CARO' ||	// Acrobat
		creator == 'InCp' ||	// InCopy
		creator == 'MeSa' ||	// ImageReady
		creator == '8ELE' ||	// Photoshop Elements
		creator == 'NCOR' ||	// Encore
		creator == 'DmWr' ||	// Dreamweaver
		creator == 'MFL2' ||	// Flash
		creator == 'MmXm' ||	// Extension Manager
		creator == 'FXTC' ||	// After Effects
		creator == 'PrMr' ||	// Premiere - deprecated
		creator == 'PPro' ||	// Premiere - new
		creator == 'AdMC' ||	// Device Central
		creator == 'SnTh' ||	// Soundbooth
		creator == 'SWF2' ||	// Flash Player
		creator == 'MKBY'		// Fireworks
		)
		result = kTrue;

	return result;
}

CFBundleRef _GetBundleFromPath(const PMString& inPath)
{
	CFBundleRef result = NULL;
	CFStringRef pathRef = inPath.CreateCFString();
	if (pathRef != NULL)
	{
		CFURLRef bundleURL = ::CFURLCreateWithFileSystemPath(NULL, pathRef, kCFURLPOSIXPathStyle, true);
		if (bundleURL != NULL)
		{
			result = ::CFBundleCreate(NULL, bundleURL);
			::CFRelease(bundleURL);
		}
		::CFRelease(pathRef);
	}
	return result;
}

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/components/links/WLinkUtilsHelper.cpp $
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
#include "FileUtils.h"
#include "PMString.h"
#include <vector>
#include "FileUtility.h"

#include <shlobj.h>
#include <shlwapi.h>

//#include "TextChar.h"
//#include "WideString.h"
#include <boost/tokenizer.hpp>
typedef boost::char_separator<UniCodePoint> UTF32TextCharSeparator;
typedef boost::tokenizer<UTF32TextCharSeparator, WideString::const_iterator, WideString > WideTokenizer;


AppInfo _LookupDefaultAppForFile(const IDFile& idFile);
void _GetAppPathsByExeName(const PMString& exeName, std::vector<PMString>& outPaths);
bool16 _IsAdobeApp(const PMString& inPath);
PMString _GetAppDisplayName (const PMString& path, bool16 useProductName);
PMString _GetVersionInfoFromPath(const PMString& inPath);
bool16 _FilterApp(const PMString& inPath);
PMString _GetOSFileInfo(const PMString& inPath, WCHAR* inInfo);
PMString _GetRegistryKeyValue( HKEY hKey, const PMString& name );
bool16 _ReplaceSystemVariableWithString(PMString& result, int nFolder);
PMString _GetExeNameFromPath(const PMString& appPath);

//----------------------------------------------------------
// _PlatformGetEditorList
//
// NOTE:
// This code was based on AddSystemOpenWithApps taken from the Bridge team:
//		bridge/main/core/source/openappsupport/OpenWithApps.cpp#99
//----------------------------------------------------------
void _PlatformGetEditorList(const IDFile& linkFile, AppInfoList& appList, const bool16 bDefaultEditorOnly)
{
	PMString extension;
	FileUtils::GetExtension(linkFile,extension);
	extension.ToLower();

	// 0. Add the default application to the app list
	AppInfo defaultApp = _LookupDefaultAppForFile(linkFile);
	if (!(defaultApp == kNullAppInfo))
		appList.push_back(defaultApp);	// Add default app

	// We might be done if requested to just get the default editor
	if (bDefaultEditorOnly)
		return;

	// 1. Go through the OpenWithList key for this app in the registry
	PMString openWithKey(L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.");
	openWithKey.Append(extension);
	openWithKey.append(L"\\OpenWithList");
	HKEY keyOpenWith;
	LONG lRet = ::RegOpenKeyEx(HKEY_CURRENT_USER, openWithKey.GrabTString(), 0, KEY_QUERY_VALUE, &keyOpenWith );
	if( lRet == ERROR_SUCCESS )
	{
		DWORD   cValues;              // number of values for key
		DWORD   cbMaxValueData;       // longest value data
		DWORD 	i = 0;
		DWORD	retCode;
		DWORD	valueType;
		DWORD	cchValue;
		DWORD	bufferLen;

		// Get the class name and the value count.
		retCode = ::RegQueryInfoKey(
			keyOpenWith,                   // key handle
			NULL,					// buffer for class name
			NULL,					// size of class string
			NULL,                   // reserved
			NULL,					// number of subkeys
			NULL,					// longest subkey size
			NULL,					// longest class string
			&cValues,				// number of values for this key
			NULL,					// longest value name
			&cbMaxValueData,		// longest value data
			NULL,					// security descriptor
			NULL);					// last write time

		char  achValue[255];	// value names are 'a', 'b', ..., 'MRUList',...

		// Allocate buffer to receive string value
		unsigned char* buffer = new unsigned char[cbMaxValueData];

		for (i = 0, retCode=ERROR_SUCCESS; i<cValues; i++)
		{
			cchValue = 255;
			bufferLen = cbMaxValueData;
			::memset(achValue, 0, 255);
			::memset(buffer, 0, cbMaxValueData);
			retCode = ::RegEnumValueA(keyOpenWith, i,
				achValue,
				&cchValue,
				NULL,
				&valueType,
				buffer,
				&bufferLen);

			// Do not include the "MRUList" value
			if ((retCode == ERROR_SUCCESS) && (cchValue < 3))
			{
				PMString exeName(CString((char*)buffer));

				// Get all the apps matching this executable
				std::vector<PMString> paths;
				_GetAppPathsByExeName(exeName, paths);

				// Now add them all to the cache and our resulting applist
				std::vector<PMString>::const_iterator iter(paths.begin());
				std::vector<PMString>::const_iterator end(paths.end());
				while (iter != end)
				{
					bool16 bIsAdobeApp = _IsAdobeApp(*iter);
					PMString displayName = _GetAppDisplayName(*iter, bIsAdobeApp);
					PMString version = _GetVersionInfoFromPath(*iter);
					AppInfo appInfo(*iter, displayName, version, kFalse, bIsAdobeApp);

					if (K2find(appList, appInfo) == appList.end() && !_FilterApp(*iter))
						appList.push_back(appInfo);
					++iter;
				}
			}
		}

		delete [] buffer;
		::RegCloseKey(keyOpenWith);
	}
}

//----------------------------------------------------------
// _LookupDefaultAppForFile
//
// Return the default application for this file
//----------------------------------------------------------
AppInfo _LookupDefaultAppForFile(const IDFile& idFile)
{
	PMString extension;
	FileUtils::GetExtension(idFile,extension);
	extension.ToLower();

	AppInfo result(kNullAppInfo);

	if (extension.IsEmpty())
		return result;

	// Let's ask the OS based on the type
	TCHAR appBuff[MAX_PATH];

	// FindExecutable retrieves the name of the executable associated with the specified file name
	// Returns a value greater than 32 if successful
	PMString filepath;
	FileUtils::IDFileToPMString(idFile,filepath);
	if (HINSTANCE(32) < ::FindExecutableW( filepath.GrabTString(), NULL, appBuff ))
	{
		PMString	appPath;
		appPath.SetTString(appBuff);

		PMString exeName = _GetExeNameFromPath(appPath);
		if (exeName.CharCount())
		{
			PMString displayName = _GetAppDisplayName(appPath,kFalse);
			PMString version = _GetVersionInfoFromPath(appPath);
			bool16 bIsAdobeApp = _IsAdobeApp(appPath);
			result = AppInfo(appPath, displayName, version, kTrue, bIsAdobeApp);
		}
	}
#if 0
	else
	{
		CString tempExtension(extension);
		tempExtension.Prepend(".");
		std::string stdExt;
		// do it the hard way, see if there's an Open shell command with an application
		// and hope for the best
		// Try looking for the file extension under HKEY_CLASSES_ROOT
		tempExtension.GetCString(stdExt, CP_ACP);

		HKEY keyExt;
		long lExtRet = RegOpenKeyExA( HKEY_CLASSES_ROOT,
			stdExt.c_str(), 0, KEY_QUERY_VALUE, &keyExt );
		if (lExtRet == ERROR_SUCCESS)
		{
			// Default value for this key is the name of the file type, like 'jpegfile'
			CString name = GetRegistryKeyValue(keyExt);
			if (name.NotEmpty())
			{
				// Check for an 'open' verb under this file type
				std::string name_cstr;
				name.Append("\\shell\\open\\command");
				HKEY keyOpen;
				name.GetCString(name_cstr, CP_ACP);

				long lOpenRet = ::RegOpenKeyExA( HKEY_CLASSES_ROOT,
					name_cstr.c_str(), 0, KEY_QUERY_VALUE, &keyOpen );
				if (lOpenRet == ERROR_SUCCESS)
				{
					CString appPath;
					CString exeName;
					CString openCommand = GetRegistryKeyValue(keyOpen);  // command line to invoke editor
					std::vector<CString> segments;
					std::vector<CString>::const_iterator iter;
					openCommand.GetSegments(segments,'\"');
					for (iter = segments.begin(); iter != segments.end(); iter++)
					{
						if (!(*iter).IsEmpty() && (*iter).EndsWithASCII(".exe", false))
						{
							// See if it's one of apps in our cache, if not it'll create a new entry
							appPath = *iter;
							appPath.PathGetLastSegment(exeName);
							std::string stdExeName;
							exeName.GetCString(stdExeName, CP_ACP);


							appInfo = AddToGeneralAppCache(stdExeName.c_str(), appPath);
							break;
						}
					}
				}
			}
			::RegCloseKey(keyExt);
		}
	}
#endif

	return result;
}

//----------------------------------------------------------
// _GetAppDisplayName
//
// Return a nice user name for an application
//----------------------------------------------------------
PMString _GetAppDisplayName (const PMString& path, bool16 useProductName)
{
	if (path.IsEmpty())
		return kNullString;

	PMString result;

	// Adobe's Apps give better display name for their product name than File Description,
	// so we want to use that instead. ProductName for windows apps such as Notepad and
	// IE are "Windows Operating System", so use FileDescription.
	if (useProductName)
		result = _GetOSFileInfo(path, L"ProductName");
	else
		result = _GetOSFileInfo(path, L"FileDescription");

	// As a backup, if failed to get ProductName or FileDescription from resource, trim off .exe name from path
	if (result.IsEmpty())
	{
	    PMString fileName(path);
		if (fileName.GetChar(fileName.CharCount() - 1) == ';')
			fileName.Truncate();
		FileUtils::GetBaseFileName(fileName, result);
	}

	return result;
}

//----------------------------------------------------------
// _GetVersionInfoFromPath
//
// Return a string representing the version of an application
//----------------------------------------------------------
PMString _GetVersionInfoFromPath(const PMString& inPath)
{
	PMString result = _GetOSFileInfo(inPath, L"ProductVersion");
	if (result.IsEmpty())
		result = _GetOSFileInfo(inPath, L"FileVersion");
	if (!result.IsEmpty())
	{
		// Take everything before a ':'
		// (used as a date separator with Mozilla products, i.e.:
		// 7.0: 20040809
		PMString* item = result.GetItem(":", 1);
		if (item)
		{
			result = *item;
			delete item;
		}

		// Now with remaining string take "major.minor" part of it (could be comma separated). So if string is "6.0.2", take 6.0.
		UniCodePoint versionSeparators[3] = { kTextChar_Period, kTextChar_Comma, kTextChar_Null };
		UTF32TextCharSeparator  separator(versionSeparators);
		WideString resultAsWS(result);
		WideTokenizer tokens( resultAsWS, separator);

		// Break into major and minor parts
		PMString major, minor;
		for (WideTokenizer::iterator i = tokens.begin(); i != tokens.end(); ++i)
		{
			if (major.IsEmpty())
			{
				major = *i;
			}
			else if (minor.IsEmpty())
			{
				minor = *i;
				break;
			}
		}

		// Build up return string from major and minor parts.
		if (!major.IsEmpty())
		{
			result = major;
			if (!minor.IsEmpty())
			{
				result += ".";
				result += minor;
			}
		}

		result.StripWhiteSpace();
	}

	if (result.IsEmpty())
		result = " ";

	return result;
}

//----------------------------------------------------------
// _FilterApp
// Filter out undesirable apps
//----------------------------------------------------------
bool16 _FilterApp(const PMString& inPath)
{
	PMString exeName = _GetExeNameFromPath(inPath);

	// Make sure this is an exe (the Windows Picture and Fax Viewer is a DLL that claims some file types)
	if (!exeName.IsEmpty())
	{
		PMString exeExtension("exe");
		FileUtility f(exeName);
		PMString extension = f.GetExtension();

		if (extension.IsEqual(exeExtension, kFalse))
			return kFalse;
	}

	return kTrue;
}

//----------------------------------------------------------
// _IsAdobeApp
//----------------------------------------------------------
bool16 _IsAdobeApp(const PMString& inPath)
{
	bool16 result = kFalse;

	PMString exeName = _GetExeNameFromPath(inPath);

	if (exeName.IsEqual("photoshop.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("photoshp.exe", kFalse /* casesensitive */))			// Version 6 and before
		result = kTrue;
	else if (exeName.IsEqual("imageready.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("acrobat.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("acroread.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("golive.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("illustrator.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("indesign.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("incopy.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("dreamweaver.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("fireworks.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("flash.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("AfterFX.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("Extension Manager.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("soundbooth.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("adobe premiere.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("adobe encore.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("adobe encore dvd.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("soundbooth.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("devicecentral.exe", kFalse /* casesensitive */))
		result = kTrue;
	else if (exeName.IsEqual("flashplayer.exe", kFalse /* casesensitive */))
		result = kTrue;

	return result;
}

//----------------------------------------------------------
// GetOSFileInfo
//----------------------------------------------------------
PMString _GetOSFileInfo(const PMString& inPath, WCHAR* inInfo)
{
	PMString result;
	if (!inPath.IsEmpty())
	{
		DWORD handle;
		DWORD infoSize = ::GetFileVersionInfoSizeW(inPath.GrabTString(), &handle);
		if (infoSize > 0)
		{
			WCHAR* fileInfo = new WCHAR [infoSize];
			::memset( fileInfo, 0, infoSize * sizeof(WCHAR) );

			const int codeSize = 32;
			WCHAR codePage[codeSize];
			::memset( &codePage, 0, codeSize * sizeof(WCHAR) );

			WCHAR* queryItem;
			UINT dwBytes;
			void *lpFixedPointer = NULL;

			BOOL ret = ::GetFileVersionInfoW(inPath.GrabTString(), 0/*ignored*/, infoSize, fileInfo);

			// Structure used to store enumerated languages and code pages.

			struct LANGANDCODEPAGE {
				WORD wLanguage;
				WORD wCodePage;
			} *lpTranslate;

			// Read the list of languages and code pages.

			// this needs to succeed otherwise just stop
			if ( VerQueryValueW(fileInfo,
				L"\\VarFileInfo\\Translation",
				(LPVOID*)&lpTranslate,
				&dwBytes))
			{
				LANGID lang = GetUserDefaultLangID();
				// Read the file description for each language and code page.
				// Do we have executables that span multiple languages? if yes,
				// pick one that match our locale and if none matching
				UINT i=0;
				UINT numLangs = dwBytes/sizeof(struct LANGANDCODEPAGE);
				for( i=0; i < numLangs; i++ )
				{
					if (lang == lpTranslate[i].wLanguage)
					{
						break;
					}
				}
				if (i == numLangs)
					i = 0;	// not found? just take arbitrarily the first one
#if _MSC_VER >= 1400
				std::swprintf(codePage, 32, L"%04x%04x", lpTranslate[i].wLanguage, lpTranslate[i].wCodePage);
#else
				std::swprintf(codePage, L"%04x%04x", lpTranslate[i].wLanguage, lpTranslate[i].wCodePage);
#endif
				std::wstring queryString(L"\\StringFileInfo\\");
				queryString += codePage;
				queryString += L"\\";
				queryString += inInfo;

				queryItem = const_cast<WCHAR*>(queryString.c_str());

				// Retrieve file description for language and code page "i".
				::VerQueryValueW(fileInfo,
					queryItem,
					&lpFixedPointer,
					&dwBytes);
				if (dwBytes > 0 && lpFixedPointer != 0)
					result.SetTString(reinterpret_cast<TCHAR *>(lpFixedPointer));
			}

			// make sure to clean this up
			delete [] fileInfo;
		}
	}
	return result;
}

//----------------------------------------------------------
// GetRegistryKeyValue
//----------------------------------------------------------
PMString _GetRegistryKeyValue( HKEY hKey, const PMString& name )
{
	if( hKey == NULL )
		return kNullString;

	// Determine buffer size required for string value
	DWORD	type		= REG_SZ;
	DWORD	numBytes	= 0;

	long err = ::RegQueryValueExW( hKey, (LPCWSTR)name.GrabUTF16Buffer(nil), 0, &type, NULL, &numBytes );

	if( err != ERROR_SUCCESS || numBytes == 0 )
		return kNullString;

	// RegQueryValueExW documentation is unclear on null termination, allow two extra bytes for a UTF16 terminator
	numBytes += 2;
	
	DWORD utf16TextCharSize = numBytes/sizeof(UTF16TextChar);
	UTF16TextChar* buffer = new UTF16TextChar[utf16TextCharSize];	// Same as an array of numBytes size
	::memset( buffer, 0, numBytes );	// This guarantees null termination

	// Get the string value
	err = ::RegQueryValueExW( hKey, (LPCWSTR)name.GrabUTF16Buffer(nil), 0, &type, (BYTE*)buffer, &numBytes );

	PMString result;
	if( err == ERROR_SUCCESS )
	{
		result.SetTString(reinterpret_cast<TCHAR*>(buffer));
	}

	delete [] buffer;

	return result;
}

//----------------------------------------------------------
// GetAppPathsByExeName
//----------------------------------------------------------
void _GetAppPathsByExeName(const PMString& exeName, std::vector<PMString>& outPaths)
{
	// Look up the registry for App Path key
	// http://msdn.microsoft.com/library/en-us/shellcc/platform/shell/
	// programmersguide/shell_basics/shell_basics_extending/fileassociations/fa_perceived_types.asp?frame=true

	PMString result;
	PMString registryPath = ("Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\");
	registryPath.Append(exeName);

	HKEY keyAppPath;
	LONG lRet = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE,	registryPath.GrabTString(), 0, KEY_QUERY_VALUE, &keyAppPath );
	if( lRet == ERROR_SUCCESS )
	{
		// Use the default value (it's the 8.3 compatibility path)
		result = _GetRegistryKeyValue(keyAppPath,kNullString);
		if (result.IsEmpty())
		{
			// fall back on Path attribute (it's the full path), and add exeName
			result = _GetRegistryKeyValue(keyAppPath, "Path");
			if (!result.IsEmpty())
			{
				UniCodePoint semiSeparator[2] = { kTextChar_Semicolon, kTextChar_Null };
				UTF32TextCharSeparator  separator(semiSeparator);
				WideString resultAsWS(result);
				WideTokenizer tokens( resultAsWS, separator);

				// The paths can be a ; delimited list. Use the first non-empty one
				for (WideTokenizer::iterator i = tokens.begin(); i != tokens.end(); ++i)
				{
					PMString item = *i;
					if (!item.IsEmpty())
					{
						result = item;
						break;
					}
				}

				if (!result.IsEmpty())
				{
					// Ensure we have a folder separator character at the end.
					if (result.LastIndexOfWChar(kTextChar_ReverseSolidus) != result.CharCount() - 1)
						result.AppendW(kTextChar_ReverseSolidus);
					result.Append(exeName);
				}
			}
		}

		::RegCloseKey(keyAppPath);
	}

	if (result.IndexOfCharacter(kTextChar_ReverseSolidus) == 0 && result.LastIndexOfWChar(kTextChar_ReverseSolidus) == result.CharCount() - 1)
	{
		result.Remove(0);
		result.Truncate();
	}

	// Look for and replace %systemroot% variable if present
	bool16 bReplacedVariable = _ReplaceSystemVariableWithString(result, CSIDL_SYSTEM);
	if (!bReplacedVariable)
		bReplacedVariable = _ReplaceSystemVariableWithString(result, CSIDL_PROGRAM_FILES);

	// Use AssocQueryString to find the executable
	if (result.IsEmpty())
	{
		TCHAR szDefault[MAX_PATH];
		DWORD ccDefault = MAX_PATH;
		HRESULT rc = ::AssocQueryStringW (ASSOCF_OPEN_BYEXENAME, ASSOCSTR_EXECUTABLE,(LPCWSTR)exeName.GrabUTF16Buffer(nil), L"open", szDefault, &ccDefault);
		if (ccDefault && rc == S_OK)
			result.SetTString(szDefault);
	}

	// Not in registry, look into Windows/System32 and Windows directories for executable, as documented in above URL.
	if (result.IsEmpty())
	{
		IDFile path;
		if (FileUtils::CoverSHGetFolderPath(CSIDL_SYSTEM, &path) == kSuccess ||
			FileUtils::CoverSHGetFolderPath(CSIDL_WINDOWS, &path) == kSuccess)	// Does not exist in Windows/System32 dir, try the windows directory
		{
			result.SetTString(path.GrabTString());

			// Ensure we have a folder separator character at the end.
			if (result.LastIndexOfWChar(kTextChar_ReverseSolidus) != result.CharCount() - 1)
				result.AppendW(kTextChar_ReverseSolidus);

			result.Append(exeName);
		}

		if (::GetFileAttributes(result.GrabTString()) == INVALID_FILE_ATTRIBUTES)
			result.clear();
	}

	if (!result.IsEmpty())
		outPaths.push_back(result);
}

//----------------------------------------------------------
// ReplaceSystemVariableWithString
//----------------------------------------------------------
bool16 _ReplaceSystemVariableWithString(PMString& result, int nFolder)
{
	PMString variable;
	if (nFolder == CSIDL_SYSTEM)
		variable = "%systemroot%";
	else if (nFolder == CSIDL_PROGRAM_FILES)
		variable = "%programfiles%";
	variable.SetTranslatable(kFalse);

	PMString tempResult(result);
	tempResult.ToLower();

	CharCounter pos;
	if ((pos = tempResult.IndexOfString(variable)) >= 0)
	{
		IDFile path;
		if (FileUtils::CoverSHGetFolderPath(nFolder, &path) == kSuccess)
		{
			result.Remove(pos, variable.CharCount());
			PMString substitutePath;
			substitutePath.SetTString(path.GrabTString());
			result.Insert(substitutePath, pos);
			return kTrue;
		}
	}

	return kFalse;
}

//----------------------------------------------------------
// GetExeNameFromPath
//----------------------------------------------------------
PMString _GetExeNameFromPath(const PMString& appPath)
{
	// Extract just the "app.exe" part of app path
	PMString exeName(appPath);
	CharCounter pos = exeName.LastIndexOfWChar(kTextChar_ReverseSolidus);
	if (pos != -1)
	{
		exeName.Remove(0, pos + 1);
	}
	else
	{
		exeName.clear();
	}

	return exeName;
}


//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/external/afl/includes/CorePathUtils.h $
//  
//  Owner: Michael Easter
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
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
#ifndef __CorePathUtils__
#define __CorePathUtils__

// ----- Includes -----
#include "AFLDecl.h"
#include "APath.h"
#include "APathComponent.h"
#include "ATypes.h"

namespace adobe {
namespace afl {

/**
 Utility class used to manipulate and obtain information for paths
 and path components.
 @see APath
 @see APathComponent
 */
class AFL_DECL CorePathUtils
{
public:
	/**
	 Gets the application's current working directory.
	 @return The application's current working directory as an APath object.
	 */
	static APath GetCurrentDir();

	/**
	 Sets the application's current working directory.
	 @param path	IN Path to set the current working directory to.
					   The path must be valid and absolute.
	 @return True if the current working directory was set, else false.
	 */
	static bool SetCurrentDir(const APath& path);

	/**
	 Gets the system's temporary directory.
	 @return The system's temporary directory as an APath object.
	 */
	static APath GetTempDir();

	/**
	 Test whether the path is a POSIX path.
	 @param path	IN Path to get test.
					   The path must be valid and absolute.
	 @return True if the path is a POSIX path, else false.
	 */
	static bool IsPosixPath(const APath& path);

	/**
	 Test whether the path is a Windows UNC path.
	 @param path	IN Path to get test.
					   The path must be valid and absolute.
	 @return True if the path is a Windows UNC path, else false.
	 */
	static bool IsUNCPath(const APath& path);

	/**
	 Test whether the path is a Windows local drive path.
	 @param path	IN Path to get test.
					   The path must be valid and absolute.
	 @return True if the path is a Windows local drive path, else false.
	 */
	static bool IsWinLocalPath(const APath& path);

	/**
	 Returns the available file system space for the given path.
	 @param path	IN Path to get the available space for.
					   The path must be valid and absolute.
	 @return The available file system space for the given path.
	 */
	static uint64 GetPathFreeSpace(const APath& path);

	/**
	 Converts an APath object to a UTF8 string.
	 @param path	IN APath object to convert.
	 @param str		OUT Resulting UTF8 string.
	 */
	static void APathToUTF8(const APath& path, AString8& str);

	/**
	 Converts a UTF8 string to an APath object.
	 @param str		IN UTF8 string to convert.
	 @param path	OUT Resulting APath object.
	 */
	static void UTF8ToAPath(const AString8& str, APath& path);

	/**
	 Converts an APath object to a file URL.
	 @param path	IN APath object to convert.
	 @param url		OUT Resulting file URL.
	 */
	static void APathToFileURL(const APath& path, AString8& url);

	/**
	 Converts a file URL to an APath object.
	 @param url		IN File URL to convert.
	 @param path	OUT Resulting APath object.
	 */
	static void FileURLToAPath(const AString8& url, APath& path);

	/**
	 Converts an APathComponent object to a UTF8 string.
	 @param component	IN APathComponent object to convert.
	 @param str			OUT Resulting UTF8 string.
	 */
	static void APathComponentToUTF8(const APathComponent& component, AString8& str);

	/**
	 Converts a UTF8 string to an APathComponent object.
	 @param str			IN UTF8 string to convert.
	 @param component	OUT Resulting APathComponent object.
	 */
	static void UTF8ToAPathComponent(const AString8& str, APathComponent& component);
};

}	// namespace afl
}	// namespace adobe

#endif	// __CorePathUtils__

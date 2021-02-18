//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/external/afl/includes/CoreFileUtils.h $
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
#ifndef __CoreFileUtils__
#define __CoreFileUtils__

// ----- Includes -----
#include "AFLDecl.h"
#include "AErrors.h"
#include "AFile.h"
#include "APath.h"
#include "APathComponent.h"
#include "AString.h"
#include "ATypes.h"

namespace adobe {
namespace afl {

/**
 Utility class used to manipulate and obtain information for files and directories.
 @see AFile
 @see APath
 @see APathComponent
 @see AString
 */
class AFL_DECL CoreFileUtils
{
public:
	/**
	 Gets the application's current working directory.
	 @return The application's current working directory as an AFile object.
	 */
	static AFile GetCurrentDir();

	/**
	 Sets the application's current working directory.
	 @param file	IN Path to set the current working directory to.
					   The path must be valid and absolute.
	 @return True if the current working directory was set, else false.
	 */
	static bool SetCurrentDir(const AFile& file);

	/**
	 Gets the system's temporary directory.
	 @return The system's temporary directory as an AFile object.
	 */
	static AFile GetTempDir();

	/**
	 Creates a unique file in the directory specified by the given path.
	 @param path		IN Path to the directory where to create the file.
	 @param namePrefix	IN Unique file name's prefix.
	 @param nameSuffix	IN Unique file name's suffix.
	 @param file		OUT AFile object pointing to the created file.
	 @return True if the file was successfully created, else false.\\
	 */
	static bool CreateUniqueFile(const APath& path, const AString& namePrefix, const AString& nameSuffix, AFile& file);

	/**
	 Creates a unique directory in the directory specified by the given path.
	 @param path		IN Path to the directory where to create the directory.
	 @param namePrefix	IN Unique directory name's prefix.
	 @param nameSuffix	IN Unique directory name's suffix.
	 @param dir			OUT AFile object pointing to the created directory.
	 @return True if the directory was successfully created, else false.\\
	 */
	static bool CreateUniqueDir(const APath& path, const AString& namePrefix, const AString& nameSuffix, AFile& dir);

	/**
	 Creates a temporary file in the system’s temp directory using the given name.
	 @param name	IN Temporary file name.
	 @param file	OUT AFile object pointing to the created temporary file.
	 @return True if the temporary file was successfully created, else false. 
	 */
	static bool CreateTempFile(const APathComponent& name, AFile& file);

	/**
	 Creates a temporary directory in the system’s temp directory using the given name.
	 @param name	IN Temporary directory name.
	 @param dir		OUT AFile object pointing to the created temporary directory.
	 @return True if the temporary directory was successfully created, else false. 
	 */
	static bool CreateTempDir(const APathComponent& name, AFile& dir);

	/**
	 Creates a unique temporary file in the system’s temp directory.
	 @param namePrefix	IN Unique temporary file name's prefix.
	 @param nameSuffix	IN Unique temporary file name's suffix.
	 @param file		OUT AFile object pointing to the created temporary file.
	 @return True if the temporary file was successfully created, else false. 
	 */
	static bool CreateUniqueTempFile(const AString& namePrefix, const AString& nameSuffix, AFile& file);

	/**
	 Creates a unique temporary directory in the system’s temp directory.
	 @param namePrefix	IN Unique temporary directory name's prefix.
	 @param nameSuffix	IN Unique temporary directory name's suffix.
	 @param dir			OUT AFile object pointing to the created temporary directory.
	 @return True if the temporary directory was successfully created, else false. 
	 */
	static bool CreateUniqueTempDir(const AString& namePrefix, const AString& nameSuffix, AFile& dir);

	/**
	 Resolves an alias file by setting an AFile object to the file the alias references.
	 @param aliasFile	IN File that is an alias file.
	 @param file		OUT File that the alias file references.
							May be the same object as the aliasFile argument.
	 @param bIsDir		OUT Denotes whether the alias pointed to a directory.
	 						nullptr if not interested. 
	 @param bWasAlias	OUT Denotes whether the given aliasFile was actually an alias.
	 						nullptr if not interested. 
	 @param bSuppressUI	IN Denotes whether to prevent the OS from displaying a dialog when
						   the alias cannot be automatically resolved.
	 @return kAFLSuccess if the alias file was successfully resolved,\\
			 kAFLResolveAliasError if the alias could not be resolved, or\\
			 kAFLFailure if an unexpected error is encountered. 
	 */
	static AError ResolveAlias(const AFile& aliasFile, AFile& file, bool* bIsDir = nullptr, bool* bWasAlias = nullptr, bool bSuppressUI = true);

	/**
	 Copies the contents of the given source file to the given destination file.
	 @param sourceFile		IN Source file to copy.
	 @param destFile		IN Destination file of the copy operation.
	 @param bFailIfExists	IN Denotes whether to fail if the destination file already exists.
	 @return True if the file was successfully copied, else false. 
	 */
	static bool CopyFile(const AFile& sourceFile, const AFile& destFile, bool bFailIfExists = false);
	static bool FileCopy(const AFile& sourceFile, const AFile& destFile, bool bFailIfExists = false);

	/**
	 Moves the given source file to the given destination file.
	 @param sourceFile		IN Source file to move.
	 @param destFile		IN Destination file of the move operation.
	 @param bFailIfExists	IN Denotes whether to fail if the destination file already exists.
	 @return True if the file was successfully moved, else false. 
	 */
	static bool MoveFile(const AFile& sourceFile, const AFile& destFile, bool bFailIfExists = false);
	static bool FileMove(const AFile& sourceFile, const AFile& destFile, bool bFailIfExists = false);

	/**
	 Renames the given file to the given name.
	 @param sourceFile	IN File to rename.
	 @param newFileName	IN New name of the file.
	 @return True if the file was successfully renamed, else false. 
	 */
	static bool RenameFile(AFile& file, const AString& newFileName);

	/**
	 Deletes the given directory and all the files and folders it contains
	 from the file system.  The call will recursively iterate over the contents
	 of the directory and delete all the contents possible.
	 @param dir		IN Directory to delete.
	 @param bForce	IN Denotes whether to attempt to forcibly delete files and folders
					   that are locked or read-only.
	 @return True if the directory and all the files and folders it contained were
			 successfully deleted. \\
			 False if the directory or one or more files or folders it contained
			 could not be deleted.
	 */
	static bool DeleteDirectory(const AFile& dir, bool bForce = false);

	/**
	 Returns the name of the volume the file is located on.
	 @param file	IN File to get the volume name for.
	 @return The name of the volume the file is located on. \\
			 An empty string if the input parameters are invalid.
	 */
	static AString GetVolumeName(const AFile& file);

	/**
	 Tests whether the given file is located on a network server volume.
	 @param file	IN File to check.
	 @return True if the file is located on a network server volume, else false. 
	 */
	static bool OnServerVolume(const AFile& file);

	/**
	 Tests whether the given files are located on the same volume.
	 @param file1	IN File to check.
	 @param file2	IN File to check.
	 @return True if the files are located on the same volume, else false. 
	 */
	static bool OnSameVolume(const AFile& file1, const AFile& file2);

	/**
	 Tests whether the given files' paths refer to the same file location.
	 @param file1		IN File to check.
	 @param file2		IN File to check.
	 @param bResolve	IN Denotes whether to resolve aliases when comparing the files.
	 @return True if the files' paths refer to the same file location, else false. 
	 */
	static bool PathsEquivalent(const AFile& file1, const AFile& file2, bool bResolve = true);

	/**
	 Returns the amount of free space available to the user associated with the
	 calling thread on the disk volume containing the the given file
	 @param file	IN File to get the available space for.
					   The file or the parent folder must be exist.
					   If file is an alias, the returned available file
					   system space is for the file the alias references.
	 @return The available file system space for the given file.
	 */
	static uint64 GetFileFreeSpace(const AFile& file);

	/**
	 Displays the location of the file in the finder or file explorer.
	 @param file	IN File whose location to display.
	 @return True if the file location was successfully displayed, else false. 
	 */
	static bool ShowFileLocation(const AFile& file);

	/**
	 Converts an AFile object to a UTF8 string.
	 @param file	IN AFile object to convert.
	 @param str		OUT Resulting UTF8 string.
	 */
	static void AFileToUTF8(const AFile& file, AString8& str);

	/**
	 Converts a UTF8 string to an AFile object.
	 @param str		IN UTF8 string to convert.
	 @param file	OUT Resulting AFile object.
	 */
	static void UTF8ToAFile(const AString8& str, AFile& file);
};

}	// namespace afl
}	// namespace adobe

#endif	// __CoreFileUtils__

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IFileUtility.h $
//  
//  Owner: Robin_Briggs
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
#ifndef __IFILEUTILITY__
#define __IFILEUTILITY__

#include "IDFile.h"

class PMString;

/**
 Utility interface that provides methods used to manipulate IDFiles and paths.

 When possible, it is preferred to manipulate IDFile objects directly rather
 than using the IFileUtility methods.
 @see IDFile
 */
class IFileUtility		
{
public:
	/**
	 Destructor.
	 Destroys the IFileUtility object.
	 */
	virtual ~IFileUtility()	{}

	/**
	 Deletes the file from the file system. \\
	 On the Mac, this call can also be used to delete an empty directory.
	 */
	virtual void DeleteFile() = 0;
		
	/**
	 Makes a path to a temporary file in the system's temporary file directory
	 using the current file name. \\
	 This call does not create the temporary file.
	 @return kTrue if success, else kFalse.
	 */

	enum SetTemporaryFileFlags {
	   kNone = 0x0,

   	   // -- Mac Flags -- //
	   kUserDomainMac	= 0x1,				/* Finds a folder in the user domain. 
											   See kUserDomain in Folders.h on Mac. */
	   kPreferencesFolderTypeMac = 0x2,		/* Sets the temporary file to a file in the 
											   Preferences folder, instead of a folder
											   that is deleted on startup. */

	   // -- Windows Flags -- //
	   
	};
	virtual bool16 SetTemporaryFile(int32 flags = kNone) = 0;
	
	/**
	 Ensures that the file name is unique within the directory by appending a
	 unique numerical suffix.
	 */
	virtual void SetUniqueName() = 0;
	
	/**
	 Gets the full path of the file as a string.
	 @param pathName	OUT Pointer to the string to be set to the file's full path.
	 */
	virtual void GetPathName(PMString *pathName) = 0;
	
	/**
	 Gets the file name of the file as a string.
	 @param fileName	OUT Pointer to the string to be set to the file's name.
	 */
	virtual void GetFileName(PMString* fileName) = 0;
		
	/**
	 Returns the file as an IDFile object.
	 @return Reference to file's IDFile object.
	 */
	virtual const IDFile& GetSysFile() = 0;
	
	/**
	 Gets the parent path of the file as an IDFile object.
	 @param fileSpec	OUT Parent path of the file as an IDFile object.
	 */
	virtual void GetDirectory(IDFile& fileSpec) = 0;
	
	/**
	 Copies the contents of the file to the given destination file.
	 @param destFile	IN Destination file of the copy operation.
	 @return kTrue if the file was successfully copied, else kFalse. 
	 */
	virtual bool16 CopyFile(const IDFile& destSpec) = 0;

	/**
	 Tests whether the file or directory exists on the file system.
	 @return kTrue if exists, else kFalse.
	 */
	virtual bool16 FileExists() = 0;

	/**
	 Tests whether this object refers to a existing directory or an alias to a directory.
	 @return kTrue if a directory or an alias to a directory, else kFalse.
	 */
	virtual bool16 IsFolder() = 0;

	/**
	 Identifiers that denote the type of file access desired. \\
	 You cannot obtain access to a file with an access mode that conflicts with
	 a sharing mode specified in a previous open request (from any process) whose
	 handle is still open.
	 */
	typedef enum {
		/** Read access; open the file for reading only. */
		kRead,
		/** Write access; open the file for writing only. */
		kWrite,
		/** Read and write access; open the file for reading and writing. */
		kReadWrite
	} Access;

	/**
	 Tests whether the file or directory can be opened with the specified access. \\
	 The state of whether a file can be opened may change at any time, so it is best to attempt to
	 open the file immediately following the call to CanOpen(). 
	 @param access	IN Type of file access desired.
	 @return kTrue if the file or directory can be opened with the given access, else kFalse.
	 */
	virtual bool8 CanOpen(Access access = kReadWrite) = 0;
		
	/**
	 Gets the type and creator of the file. \\
	 Does nothing on Windows.
	 @param fileType	OUT Type of the file.
	 @param creator		OUT Creator of the file.
	 */
	virtual void GetFileCreatorType(SysOSType* fileType, SysOSType* creator) = 0;

	/**
	 Sets the creator and type of the file. \\
	 Does nothing on Windows.
	 @param fileType	IN Type of the file.
	 @param creator		IN Creator of the file.
	 */
	virtual void SetFileCreatorType(SysOSType fileType, SysOSType creator) = 0;
		
	/**
	 Tests whether file is marked as stationery.
	 @return kTrue if the file is marked as stationery, else kFalse.
	 */
	virtual bool16 IsStationery() = 0;
		
	/**
	 Sets the stationery bit of the file. \\
	 Does nothing on Windows.
	 @param asStationery	IN Denotes whether the stationery bit should be set.
	 */
	virtual void SetFileAsStationery(bool16 asStationery) = 0;
		
	/**
	 Returns the date and time the file or directory was last modified.
	 @return Date and time the file or directory was last modified.
	 */
	virtual uint32 GetModificationDate() = 0;
	
	/**
	 Returns the date and time the file or directory was created.
	 @return Date and time the file or directory was created.
	 */
	virtual uint32 GetCreationDate() = 0;

	/**
	 Returns the file's extension.
	 @return File's extension as a string.
	 */
	virtual PMString GetExtension() = 0;
	
	/**
	 Returns the size of a file.
	 @return The size of the file.
			 0 if the file is empty or does not exist.
	 */
	virtual uint32 GetFileSize() = 0;
	
	/**
	 Creates the directory if it does not already exists.
	 */
	virtual void CreateDirectory() = 0;
		
	/**
	 Tests whether the directory is read-only.
	 @return kTrue if the directory is read-only, else kFalse.
	 */
	virtual bool16 DirIsReadOnly() = 0;
		
	/**
	 Tests whether the file is an alias or shortcut.
	 @return kTrue if the file is an alias or shortcut, else kFalse.
	 */
	virtual bool16 IsAliasFile() = 0;
		
	/**
	 Resolves an alias file by setting the IDFile to the file the alias references.
	 @param suppressUI	IN Denotes whether to prevent the OS from displaying a dialog when
						   the alias cannot be automatically resolved.
	 @return kSuccess if the alias file was successfully resolved,\\
			 kCouldntResolveAliasError if the alias could not be resolved, or\\
			 kFailure if an unexpected error was encountered. 
	 */
	virtual ErrorCode ResolveAliasFile(bool16 suppressUI = kTrue) = 0;
		
	/**
	 Sets the system's read-only attribute for the file.
	 @param readOnly	IN If kTrue, the file's read-only attribute is set.
	 */
	virtual bool16 SetFileReadOnly(bool16 readOnly = kTrue) = 0;

	/**
	 Returns the visibility state of the file.
	 @return kTrue if the file is visible, kFalse if it is hidden.
	 */
	virtual bool16 GetFileVisibility() = 0;

	/**
	 Sets the visibility state of the file.
	 @param show	IN Denotes whether the file should be visible or hidden.
					   kTrue to set the file to be visible.
	 @return kTrue if the visibility state of the file was set, else kFalse.
	 */
	virtual bool16 SetFileVisibility(bool16 show) = 0;	
};



#endif // __IFILEUTILITY__


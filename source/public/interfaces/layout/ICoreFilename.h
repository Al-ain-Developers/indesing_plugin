//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ICoreFilename.h $
//  
//  Owner: Steve Flenniken
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
#ifndef __ICOREFILENAME__
#define __ICOREFILENAME__

#include "IDatalink.h"  // for ProgressParam
#include "CmdUtils.h"	// for CreateObject

class IDFile;
class NameInfo;
class PMString;

/** ICoreFilename provides file I/0 and filename features in a core way.

See also newer IDFile and associated classes.

There are currently two styles of names, PC and Macintosh.
Either style can exist on either platform.  
 
A pc name has a filename, no volname (0) and no dirid (0).
The filename is a fully qualified pathname, up to 259 characters.

A Mac name has all three parameters.  The filename and volname have
a maximum length of 31 characters.  The dirid must not be 0.

You can create a ICoreFilename object as follows:
InterfacePtr<ICoreFilename> cfn((ICoreFilename *)::CreateObject(kCoreFilenameBoss, IID_ICOREFILENAME));
*/
class ICoreFilename : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOREFILENAME };

	/** Method to stream out the CoreFilename data.
        @param s is the stream to write to.
	*/ 
	virtual void ReadWrite(IPMStream *s) = 0;

	/** Method to initialize.
        @param name is an IDFile to initialize from.
		@return 0 when the method succeeds and non-zero otherwise.
	*/ 
	virtual int32 Initialize(const IDFile *name) = 0;

	/** Method to initialize.  
        @param filename is the filename to initialize from. For Macintosh style names, 
		filename is the name without path or extension.  For Windows style names, filename
		is a fully qualitfied path name.
		@param volname is the volume name on the Macintosh or nil for Windows.
		@param dirid is the directory ID on the Macintosh or 0 for Windows.
		@param fullPath is an optional full path name.
		@return 0 when the method succeeds and non-zero otherwise.
	*/ 
	virtual int32 Initialize(PMString *filename, PMString *volname, int32 dirid, const PMString *fullPath = nil) = 0;

	/** Method to initialize.
        @param cfn is an ICoreFilename to initialize from.
		@return 0 when the method succeeds and non-zero otherwise.
	*/ 
	virtual int32 Initialize(ICoreFilename *cfn) = 0;

	/** Method to initialize.
        @param ni is an NameInfo to initialize from.
		@param fullPath is an optional full path name.
		@return 0 when the method succeeds and non-zero otherwise.
	*/ 
	virtual int32 Initialize(NameInfo *ni, const PMString *fullPath = nil) = 0;

	/** Method to initialize.
		@param fullPath is a full path name.
		@return 0 when the method succeeds and non-zero otherwise.
	*/ 
	virtual int32 Initialize(PMString *fullpath) = 0;

	/** Method to change the base name.  The base name is the filename without path information.
		@param name to become the base name.
		@return 0 when the method succeeds and non-zero otherwise.
	*/ 
	virtual int32 SetBaseName(PMString *name) = 0;

	/** Method to get the IDFile that represents this ICoreFilename.
		@param name to get.
		@return 0 when the method succeeds and non-zero otherwise.
	*/ 
	virtual int32 GetSysFile(IDFile *name) = 0;
	
	/** Method to get the system file information that represents this ICoreFilename.
		GetSysFile which can be used without calling Initialize.
		@param ni NameInfo to get.
		@param name to get.
		@return 0 when the method succeeds and non-zero otherwise.
	*/ 
	virtual int32 GetSysFile(NameInfo& ni, IDFile *name) const = 0;
	
	/** Method to get the NameInfo that represents this ICoreFilename.
		@param ni to get.
		@return 0 when the method succeeds and non-zero otherwise.
	*/ 
	virtual int32 GetNameInfo(NameInfo *ni) = 0;

	/** Method to get the associated filename.
		@return the filename.
	*/ 
	virtual PMString *GetFilename() = 0;

	/** Method to get the associated volume name.
		@return the volume name.
	*/ 
	virtual PMString *GetVolume() = 0;

	/** Method to get the associated Dir ID.
		@return the Dir ID.
	*/ 
	virtual int32 GetDirID() = 0;

	/** Method to get the associated Class ID (part of NameInfo).
		@return the Class ID.
	*/ 
	virtual ClassID GetClassID() = 0;

	/** Method to get the associated IDFile.
		@return the IDFile.
	*/ 
	virtual IDFile* GetFile() = 0;

	/** Method to get the associated file extension.
		@return the file extension.
	*/ 
	virtual void GetExtension(PMString *extension) = 0;

	/** Method to get the associated base name, the filename without path information.
		@return the base name.
	*/ 
	virtual PMString *GetBaseName() = 0;

	/** Method to get the associated full path name.
		@param bChangedName optional parameter to return whether the name was changed (initialized).
		@return the full path name.
	*/ 
	virtual PMString *GetFullName(bool16* bChangedName = nil) = 0;

	/**	Get the file size and file modified time stamp information. 
		@param size optional parameter to get the size of the file in bytes. 
		Pass nil if you don't want the size.
		@param time optional parameter to get the file's modified time stamp. See GlobalTime.h.
		Pass nil if you don't want the time stamp.
		@param The link parameter is a hack to fix dirID problem on MAC
		when file is located on network file system such as NFS or SMB. When link is not 
		nil, IDataLink object could be updated to reflect correct dirID for current 
		session. This operation will not dirty document. Generally, you should use default 
		value. It is not used on windows. 
		@return 0 when the method succeeds and non-zero otherwise.
	*/
	virtual int32 GetFileInfo(uint64 *size, uint64 *time, IDataLink * link = nil) = 0;

	/** Method to determine whether the file exists.
		@return true when the file exists.
	*/ 
	virtual bool16 FileExists() = 0;

	/** Method to determine whether the directory the file is in exists.
		@return true when the directory exists.
	*/ 
	virtual bool16 DirectoryExists() = 0;

	/** Method to copy a file.
		@param dirname is the destination directory.
		@param pp is an optional progress callback, pass nil for no callback.
		@return 0 when the method succeeds and non-zero otherwise.
	*/ 
	virtual int32 Copy(ICoreFilename *dirname, ProgressParam *pp) = 0;

	/** Method to delete the file.
		@return 0 when the method succeeds and non-zero otherwise.
	*/ 
	virtual int32 Delete() = 0;

	/** Method to update the file's modified time stamp to the current time.
		@return 0 when the method succeeds and non-zero otherwise.
	*/ 
	virtual int32 Touch() = 0;

	/** Method to open the file using the standard C file I/O method.
		@param mode to open the file.  Writable = "w", Readonly = "r", Writeable binary = "wb". See fopen.
		@return a FILE pointer or nil when the file cannot be opened.
	*/ 
	virtual FILE *fileopen(PMString *mode) = 0;

	/** Method to determine the file's Macintosh type and creator.
		@param type optional parameter to get the Macintosh type, 0 is returned on Windows. 
		Pass nil if you don't want this information.
		@param creator optional parameter to get the Macintosh creator, 0 is returned on Windows.
		Pass nil if you don't want this information.
		@return 0 when the method succeeds and non-zero otherwise.
	*/ 
	virtual int32 GetTypeAndCreator(uint32 *type, uint32 *creator) = 0;

	/** Method to determine the amount of free bytes on the file's disk.
		@param free parameter to get the free disk space in bytes. 
		@return 0 when the method succeeds and non-zero otherwise.
	*/ 
	virtual int32 GetDiskFreeSpace(uint64 *free) = 0;

	/** Method to quickly find the file relative to the given directory.
		@param dirname is the directory where relative search is based on.
		@param newname returns the name when found.
		@return 0 when the file is found and non-zero otherwise.
	*/ 
	virtual int32 FindRelative(ICoreFilename *dirname, ICoreFilename *newname) = 0;

	/** Method to create a new ICoreFilename from a directory and the file's base name.
		@param dirname is the directory for the new name.
		@param pcombined returns the new name, directory plus the file's base name.
		@return 0 when the method succeeds and non-zero otherwise.
	*/ 
	virtual int32 Combine(ICoreFilename *dirname, ICoreFilename *pcombined) = 0;

	/** Method to compare the base name of two ICoreFilenames.
		@param cfn contains the name to compare.
		@return true when the base names are the same.
	*/ 
	virtual bool16 CompareBaseName(ICoreFilename *cfn) = 0;

	/** Method to compare the directory name of two ICoreFilenames.
		@param cfn contains the name to compare.
		@return true when the directory names are the same.
	*/ 
	virtual bool16 CompareDirectory(ICoreFilename *cfn) = 0;

	/** Method to determine whether the file is open. See IDFile::IsOpen.
		@return true when the file is open.
	*/ 
	virtual bool16 IsFileOpen() = 0;

	/** Method to determine whether the file is locked, IDFile::kLocked bit. See IDFile::GetAttribute.
		@return true when the file is locked.
	*/ 
	virtual bool16 IsFileLocked() = 0;

	/** Method to set the Macintosh type and creator.
		@param fileType is the Macintosh file type.
		@param creator is the Macintosh creator.
	*/ 
	virtual void SetTypeAndCreator(uint32 fileType, uint32 creator) = 0;
	
	/** Method to create a directory.
		@param name is the directory name to create in the current directory. The current directory is
		the directory of the associated file. If name is nil, create the current directory.
		@return 0 when the method succeeds and non-zero otherwise.
	*/ 
	virtual int32 CreateFolder(PMString *name) = 0;

	/** Method to create a new ICoreFilename. The directory comes from the child directory within current directory.
		@param childFolder is a directory within the current directory. The current directory is
		the directory of the associated file. 
		@param filePart is the base name for the new ICoreFilename.
		@return ICoreFilename when the method succeeds and nil otherwise.
	*/ 
	virtual ICoreFilename *CreateChildFolderFilename(const PMString &childFolder, PMString &filePart) = 0;

	/** If the file is on a network drive, convert the path name to UNC from the drive letter one.
		@return true when the name is converted (it is on a network drive).  Always returns false on Macintosh.
	*/ 
	virtual bool32 ConvertToUNC() = 0;

	/** Method to determine whether the file is currently open for exclusive read access.
		@return true when the file is open exclusive.
	*/ 
	virtual bool16 IsFileOpenExclusive() = 0;

	/** Method to moves up one level in the file system hierarchy.
		@return true when the method succeeds.
	*/ 
	virtual bool32 SwitchToParentDir() = 0;
};

#endif // __ICOREFILENAME__

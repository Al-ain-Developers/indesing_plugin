//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/WFileUtility.h $
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
#ifndef __WFILEUTILITY__
#define __WFILEUTILITY__

#include "IFileUtility.h"

#pragma export on

class PUBLIC_DECL WFileUtility : public IFileUtility
{
public:
	WFileUtility();
	WFileUtility(const PMString& fileName); // Converts mac path to win and vice versa if needed
	WFileUtility(const IDFile& fileSpec);
	virtual ~WFileUtility();

	virtual void DeleteFile();
		// Delete the file

	virtual void RenameFile(const PMString& newName);
	
	virtual void SetUniqueName();
	
	virtual bool16 SetTemporaryFile(int32 flags = kNone);
		// Take the file name and make it a name in the temporary directory
	
	virtual void GetPathName(PMString *pathName);
		// Return the complete pathname
	
	virtual void GetFileName(PMString* fileName);
		// Returns just the pathname
		
	virtual const IDFile& GetSysFile();
		// Return the file spec.
	
	virtual void GetDirectory(IDFile& fileSpec);
		// Return a file spec of the file's parent directory.
	
	virtual bool16 CopyFile(const IDFile& destSpec);
		// Copy the file into the destination file

	virtual bool16 FileExists();
		// Return true if there really is a corresponding file or folder on disk.
		
	virtual bool16 IsFolder();

	virtual bool8 CanOpen(Access access);
		
	virtual void GetFileCreatorType(SysOSType* fileType, SysOSType* creator);
	virtual void SetFileCreatorType(SysOSType fileType, SysOSType creator);
		// Set/Get the file creator and type. Does nothing on Windows.
		
	virtual bool16 IsStationery();
	virtual void SetFileAsStationery(bool16 asStationery);
		// Check for and set the file as stationery.  Does nothing on Windows
		
	virtual uint32 GetModificationDate();
	
	virtual uint32 GetCreationDate();

	// returns the extension associated with the file
	virtual PMString GetExtension();
	
	virtual uint32 GetFileSize();
	
	virtual void CreateDirectory();
		
	virtual bool16 DirIsReadOnly();
		// returns kTrue if the directory is readonly
	
	virtual bool16 IsAliasFile();
		
	virtual ErrorCode ResolveAliasFile(bool16 suppressUI = kTrue);

	// lock or unlock a file
	// return value indicates success
	virtual bool16 SetFileReadOnly(bool16 readOnly = kTrue);

	// returns kTrue if the file is visible in the OS, false if it is hidden or invisible
	virtual bool16 GetFileVisibility();

	// if show is kTrue, we remove the invisible bit on the file, otherwise we mark it as invisible/hidden
	// return value indicates success
	virtual bool16 SetFileVisibility(bool16 show);

private:
	void ResolveName();
		// Create a path name from a file spec
	void ResolveSpec();
		// Create a file spec from a path name
	void GetPathOnly(PMString *pathName);
		// Strips the files name from the path
	CharCounter GetNamePos();
		// Finds the Position of the file name
	
	IDFile 		fSpec;
	bool16 			fSpecIsValid;
	PMString 	fPathName;
	bool16 			fNameIsValid;
};

#pragma export off


#endif // __WFILEUTILITY__


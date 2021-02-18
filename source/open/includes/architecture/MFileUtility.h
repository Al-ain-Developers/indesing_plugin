//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/MFileUtility.h $
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
#ifndef __MFILEUTILITY__
#define __MFILEUTILITY__

#include "IFileUtility.h"
#include "PMString.h"

#pragma export on

class PUBLIC_DECL MFileUtility	: public IFileUtility	
{
public:
	MFileUtility();
	MFileUtility(const PMString& fileName); // Converts mac path to win and vice versa if needed
	MFileUtility(const IDFile& fileSpec);
	virtual ~MFileUtility();
	
	virtual void DeleteFile();

	virtual void RenameFile(const PMString& newName);

	virtual bool16 SetTemporaryFile(int32 flags = kNone);
	
	virtual void SetUniqueName();
	
	virtual void GetPathName(PMString *pathName);
	
	virtual void GetFileName(PMString* fileName);
		
	virtual const IDFile& GetSysFile();

	virtual void GetDirectory(IDFile& fileSpec);
	
	virtual bool16 CopyFile(const IDFile& destSpec);

	virtual bool16 FileExists();
	
	virtual bool16 IsFolder();

	virtual bool8 CanOpen(Access access);
		
	virtual void GetFileCreatorType(SysOSType* fileType, SysOSType* creator);
	virtual void SetFileCreatorType(SysOSType fileType, SysOSType creator);
		
	virtual bool16 IsStationery();
	virtual void SetFileAsStationery(bool16 asStationery);
		
	virtual uint32 GetModificationDate();

	virtual uint32 GetCreationDate();
	
	virtual PMString GetExtension();
	
	virtual uint32 GetFileSize();
	
	virtual void CreateDirectory();
	
	virtual bool16 DirIsReadOnly();
	
	virtual bool16 IsAliasFile();
		
	virtual ErrorCode ResolveAliasFile(bool16 suppressUI = kTrue);

	// lock/unlock the disk file - can be unlocked/locked from Finder Get Info window
	virtual bool16 SetFileReadOnly(bool16 readOnly = kTrue);

	// returns kTrue if the file is visible in the OS, false if it is hidden or invisible
	virtual bool16 GetFileVisibility();

	// if show is kTrue, we remove the invisible bit on the file, returns kTrue if successful
	virtual bool16 SetFileVisibility(bool16 show);
	
private:
	void ResolveName();
		// Create a path name from a file spec

	void ResolveSpec();
		// Create a file spec from a path name
	
	IDFile 		fSpec;
	bool16 			fSpecIsValid;
	PMString 		fPathName;
	bool16 			fNameIsValid;
};

#pragma export off


#endif // __MFILEUTILITY__


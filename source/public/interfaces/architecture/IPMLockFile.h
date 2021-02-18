//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPMLockFile.h $
//  
//  Owner: Gang Xiao
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
#ifndef __IPMLockFile_h__
#define __IPMLockFile_h__

#include "IPMUnknown.h"
#include "DocFrameworkID.h"

//========================================================================================
// INTERFACE ILockFile
//========================================================================================

/**
 Interface used to create and manage a document's lock file.
 */
class IPMLockFile : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IPMLOCKFILE };

	/**
	 Sets the document file that the lock file will be created for.
	 @param docFile	IN Document file the lock file will be created for.
	 */
	virtual void SetDocumentName(const IDFile &docFile) = 0;

	/**
	 Returns the document file that the lock file is created for.
	 @return Pointer to the document file the lock file is created for.
	 */
	virtual const IDFile * GetDocumentName() const = 0;

	/**
	 Returns the lock file.
	 @return Pointer to the lock file.
	 */
	virtual const IDFile * GetPMLockFileName() const = 0;

	/**
	 Creates and opens the lock file.
	 @return kTrue if the lock file is created and opened, else kFalse.
	 */
	virtual bool16 CreatePMLockFile() = 0;

	/**
	 Determines if the lock file exists.
	 @return kTrue if the lock file exists, else kFalse.
	 */
	virtual bool16 PMLockFileExist() = 0;

	/**
	 Opens the lock file.
	 @return kTrue if the lock file is opened, else kFalse.
	 */
	virtual bool16 OpenPMLockFile() = 0;

	/**
	 Closes the lock file.
	 */
	virtual void ClosePMLockFile() = 0;

	/**
	 Deletes the lock file.
	 */
	virtual void DeletePMLockFile() = 0;

	/**
	 Acquires the lock file. \\
	 If the lock file exists, opens the lock file. \\
	 Otherwise, creates and opens the lock file.
	 @return kTrue if successful, else kFalse.
	 */
	virtual bool16 AcquirePMLockFile() = 0;
	
	/**
	 Closes and conditionally deletes the lock file.
	 @param deleteFile	IN Denotes whether to delete the lock file.
	 */
	virtual void RelinquishPMLockFile(const bool16& deleteFile = kTrue) = 0;
};

#endif // __ILockFile_h__

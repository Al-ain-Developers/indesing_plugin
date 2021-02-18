//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IFileList.h $
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
#ifndef __IRecentDocsList__
#define __IRecentDocsList__

#include "IPMUnknown.h"
#include "DocumentID.h"

/**
 @deprecated This Interface is deprecated. Please use IRecentFileListFacade instead.
 @see IRecentFileListFacade 
 Interface used to maintain a list of the most recently used document files. 
 @see IDFile
 */
class IFileList : public IPMUnknown
{
public:
	/**
	 Returns the maximum number of document files the list can hold.
	 @return Maximum number of document files the list can hold.
	 */
	virtual int32 GetFileMax() const = 0;

	/**
	 Sets the number of document files to keep track of.
	 @param newDocCount	IN Number of document files to keep track of.
	 */
	virtual void SetFileMax(int32 newDocCount) = 0;

	/**
	 Returns the number of document files in the list.
	 @return Number of document files in the list.
	 */
	virtual int32 GetFileCount() const = 0;

	/**
	 Returns the n'th document file in the list.
	 @param n	IN Index of the document file to return from the list.
	 @return Pointer to the n'th document file in the list.
	 */
	virtual const IDFile* GetNthFile(int32 n) = 0;

	/**
	 Returns the n'th document file in the list as a path string.
	 @param n	IN Index of the document file whose path to return from the list.
	 @return Pointer to the n'th document file's path string.\\
			 On the Mac, the returned path is an HFS path.
	 */
	virtual const PMString* GetNthPathName(int32 n) = 0;

	/**
	 Adds a document file to the list.
	 @param addThis	IN Document file to add to the list.
	 */
	virtual void AddFile(const IDFile *addThis) = 0;

	/**
	 Removes the document file matching the given file from the list.
	 @param removeThis	IN Matching document file to remove from the list.
	 */
	virtual void RemoveFile(const IDFile *removeThis) = 0;

	/**
	 Does the system policy prohibit a MRU list.
	 @return true or false
	 */
	virtual bool16 SystemPolicyProhibitsList (void) = 0;

	// ===============================================================
	// For internal use only
	// ===============================================================	

	virtual void CleanList() = 0;

	// Internal really constant functions:
	
	virtual const IDFile* GetNthFileIntConst(int32 n) const = 0;		
};

#endif	// __IRecentDocsList__

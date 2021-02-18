//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SysFileList.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __SysFileList__
#define __SysFileList__

#include "K2Vector.h"

class IDFile;

#pragma export on

/**
 Class used to hold a list of file objects.
 @see IDFile
 */
class PUBLIC_DECL SysFileList
{
public:
	/**
	 Default constructor.
	 Constructs a SysFileList object.
	 */
	SysFileList();

	/**
	 Destructor.
	 Destroys the SysFileList object.
	 */
	~SysFileList();

	/**
	 Returns the number of files in the list.
	 @return Number of files in the list.
	 */
	virtual int32 GetFileCount() const;

	/**
	 Returns the n'th file in the list.
	 @param n	IN Index of the file to return from the list.
	 @return Pointer to the n'th file in the list.
	 */
	virtual IDFile* GetNthFile(int32 n) const;

	/**
	 Adds a file to the list.
	 @param newFile	IN File to add to the list.
	 */
	virtual void AddFile(const IDFile *newFile);

	/**
	 Sorts the list alphabetically by filename(case insensitive)
	 */
	virtual void SortListByFilename();
	
private:
	SysFileList(const SysFileList& rhs);				// disable copying
	SysFileList& operator=(const SysFileList& rhs);
	
private:
	K2Vector<IDFile*> fFileList;
};
#pragma export off
#endif

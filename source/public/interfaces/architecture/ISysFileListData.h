//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISysFileListData.h $
//  
//  Owner: Paul Sorrick
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
//  
//  Interface for storing lists of SysFiles.
//  
//========================================================================================

#pragma once
#ifndef __ISysFileListData__
#define __ISysFileListData__

#include "IPMUnknown.h"

#include "DocumentID.h"

/**
 Container interface used to hold a list of file objects.
 @see IDFile
 */
class ISysFileListData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISYSFILELISTDATA };

	/**
	Appends a file to the list.
	@param theFile	IN File to append to the list.
	*/
	virtual void Append(const IDFile& theFile) = 0;

	/**
	 Returns the n'th file in the list.
	 @param i	IN Index of the file to return from the list.
	 @return The n'th file in the list.
	 */
	virtual IDFile GetSysFileItem(int32 i) const = 0;

	/**
	Returns the number of files in the list.
	@return Number of files in the list.
	*/
	virtual int32 Length() = 0;

	/**
	Removes all the files from the list.
	*/
	virtual void Clear() = 0;

	/**
	 Sorts the list alphabetically by filename(case insensitive)
	 */
	virtual void SortListByFilename() = 0;
};

#endif // __ISysFileListData__

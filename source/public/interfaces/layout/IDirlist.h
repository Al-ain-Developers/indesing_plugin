//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDirlist.h $
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
//  
//  IDirList.h
//  
//  This file defines an interface for maintaining a list of links.
//  Whenever a user manually finds a missing link, that link is added
//  to this list.  All the directories of these links are looked in
//  to finding missing links.  This list is maintained for the duration
//  of the session.  A pointer to IDirList can be obtained by querying
//  the session object.
//  
//========================================================================================

#pragma once
#ifndef __DIRLIST__
#define __DIRLIST__

class NameInfo;

#include "LinksID.h"

/**
 Interface for maintaining a list of links. 
 Whenever a user manually finds a missing link, that link is added
 to this list.  All the directories of these links are looked in
 to finding missing links.  This list is maintained for the duration
 of the session.  A pointer to IDirList can be obtained by querying
 the session object.
 @see NameInfo
 */
class IDirList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDIRLIST };

	/**
	 Returns the number of directories in the list.
	 @return Number of directories in the list.
	 */
	virtual uint32 GetCount() = 0;

	/**
	 Adds the directory referenced by the given data link to the list.
	 This call does not create the temporary file.
	 @param dir	IN IDFile that references the directory to add.
	 @return 0 if the directory was successfully added,\\
			 1 if invalid parameter, or\\
			 2 if out of memory.
	 */
	virtual int32 AddDir(const IDFile &dir) = 0;

	/**
	 Gets the directory at the given index from the list.
	 @param index	IN Index of the directory to get.
	 @param dir		OUT Pointer to a existing NameInfo object that
						is set with the directory information.
	 @return True if the directory was successfully obtained,
			 else false if an invalid index.
	 */
	virtual bool GetDir(uint32 index, IDFile& dir) = 0;

	/**
	 Gets the directory at the given index from the list.
	 @param index	IN Index of the directory to get.
	 @param ni		OUT Pointer to a existing NameInfo object that
						is set with the directory information.
	 @return 0 if the directory was successfully obtained,\\
			 2 if invalid parameter.
	 */
	virtual int32 GetDir(uint32 index, NameInfo *ni) = 0;

	/**
	 Removes all the directories from the list.
	 */
	virtual void Empty() = 0;
};

#endif // __DIRLIST__

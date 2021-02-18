//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyStoryList.h $
//  
//  Owner: cparrish
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
#ifndef __IInCopyStoryList__
#define __IInCopyStoryList__

#include "InCopyCoreID.h"

/** This interface is added to each document (kDocBoss) to indicate the stories in the current
		pub that are InCopy stories. Code that imports InCopy stories should add
		the imported stories to this list.

	In general, you should use the Process calls to Add/remove from the list.  The commands
		that are processed will call AddStory/RemoveStory to do the direct modifications

	ADDITIONAL NOTE (6/23/2004):
	This interface now holds incopy *text* and *graphic* stories, callers should check
	for appropriate interfaces.
*/
class IInCopyStoryList : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINCOPYSTORYLIST };
		

/**	Uses a command to add a story to the list
	@param story The story being added in the list
 */
		virtual void	ProcessAddStory(UID story) = 0;
		
/**	 Uses a command to remove a story from the list
	@param story The story being removed from the list
 */
		virtual void	ProcessRemoveStory(UID story) = 0;
		
/**	Get the number of stories in the list
	@param none
	@return int32 
 */
		virtual int32	GetStoryCount() const= 0;
		

/**	Get the nth story UIDRef
	@param nth 
	@return UIDRef 
 */
		virtual UIDRef	GetNthStoryRef(int32 nth) const = 0;

/**	Get the nth story UID
	@param nth 
	@return UID 
 */
		virtual UID		GetNthStoryUID(int32 nth) const = 0;

/**	Get the index of giving story in the list
	@param story 
	@return int32 -1 means the story is not in the list
 */
		virtual int32	Location(UID story) const = 0;
		

/**	Adds the story if not already in the list
	@param story 
 */
		virtual void	AddStory(UID story) = 0;

/**	Removes a story from the list
	@param story 
 */
		virtual void	RemoveStory(UID story) = 0;

/**	Is there a text story in the list?
	@param none
	@return bool16 
 */
		virtual bool16	HasTextStory() const = 0;
			

/**	Is there a graphic story in the list?
	@param none
	@return bool16 
 */
		virtual bool16	HasGraphicStory() const = 0;
};

#endif //__InCopyStoryList__
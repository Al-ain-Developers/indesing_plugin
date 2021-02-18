//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IAssignedStory.h $
//  
//  Owner: Jon Pugh
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
#ifndef _IASSIGNEDSTORY_
#define _IASSIGNEDSTORY_

#include "AssignmentID.h"
#include "PMString.h"


class IAssignment;


/** This class is used to model the assignment of one or more stories to a user.
	@see IAssignment
	@see IAssignmentMgr
*/
class IAssignedStory : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IASSIGNEDSTORY };

	/**
		Return a reference to the story's page item.
		@return The story's page item.  May be a text model or graphic frame.
	*/
	virtual UIDRef						GetUIDRef() = 0;

	/**
		Change the story's page item.  Must be called from a command.
		@param uidref The new page item for this story.
	*/
	virtual void						SetUIDRef(const UIDRef& uidref) = 0;

	/**
		The file path of the story's linked InCopy file.
		@return A reference to the story's linked InCopy file path.
	*/
	virtual const PMString&				GetFile() = 0;

	/**
		Set the story's linked InCopy file path. Does not change the IDataLink.  Must be called from a command.
		@param file A file path in the current platform's encoding.
	*/
	virtual void						SetFile(const PMString& file) = 0;

	/**
		The assigned story's name which is displayed in the assignment palette.
		@return The display name.
	*/
	virtual const PMString&				GetName() = 0;

	/**
		Change the name displayed for this story in the assignment palette.  Must be called from a command.
		@param name The new name.
	*/
	virtual void						SetName(const PMString& name) = 0;

	/**
		The assignment this story is in.
		@return A pointer to the assignment, without the refcount incremented.
	*/
	virtual IAssignment*				GetAssignment() = 0;

	/**
		Set the assignment.  This does not move the assignment and must be called from a command.
		This is called the IAssignment::MoveStoryCmd.
		@param assignment The new assignment to remember.
	*/
	virtual void						SetAssignment(IAssignment* assignment) = 0;

	/**
		Return whether a story has been recomposed or not.
	*/
	virtual bool16						IsDirty() = 0;
	
	/**
		Update the assigned story and frames, making sure they have the proper adornment color and the like.
		Must be called from a command.
	*/
	virtual void						Update() = 0;
	
	/**
		Register this story with the assigned frame's IScrapItem interface.
	*/
	virtual void						Register() = 0;

	/**
		Unregister this story from the assigned frame's IScrapItem interface.
	*/
	virtual void						Unregister() = 0;

	/**
		Process a command to set the properties of this assignment.
		@param uidref The new page item reference
		@param file The new file path
		@param name The new assigned story name
		@return ErrorCode Any error that may have occurred
	*/
	virtual ErrorCode					SetProps(const UIDRef& uidref, const PMString& file, const PMString& name) = 0;
};

typedef InterfacePtr<IAssignedStory> IAssignedStoryPtr;
typedef K2Vector<IAssignedStory*> IAssignedStoryList;

#endif //_IASSIGNEDSTORY_

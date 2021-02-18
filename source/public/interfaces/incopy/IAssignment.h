//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IAssignment.h $
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
#ifndef _IASSIGNMENT_
#define _IASSIGNMENT_

#include "AssignmentID.h"
#include "PMString.h"

#include "IAssignedStory.h"
#include "URI.h"

/** This class is used to model the assignment of stories and images.
	@see IAssignedDocument
	@see IAssignmentMgr
*/
class IAssignment : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IASSIGNMENT };

	/** The assignment preview export options. */
	enum AssignmentExportOptions
	{
		/** Export only wireframes for unassigned stories, no content or images */
		kAssignmentExportFrames = 0,

		/** Export only the spreads which have assigned stories on them */
		kAssignmentExportSpreads,

		/** Export the entire publication */
		kAssignmentExportAll
	};

	/** The assignment compatibility. */
	enum AssignmentCompatibility
	{
		/** Compatible with CS3: Assignment file is INCA format and can only contain INCX and INCD stories. */
		kAssignmentCS3Compatibility = 0,

		/** Optimized for CS4: Assignment file is ICMA format and can only have ICML stories. */
		kAssignmentCS4Compatibility,

		/** Unassigned: Assignment does not export and can contain all assigned story formats. */
		kUnassignedCompatibility
	};

	/**
		Returns the name of the assignment.
		@return A reference to the assignment's PMString name
	*/
	virtual const PMString&				GetName() const = 0;

	/**
		Sets the name of the assignment.
		@param name - A PMString containing the new name.
	*/
	virtual void						SetName(const PMString& name) = 0;
	
	/**
		Returns the path of the assignment file itself.
		@return - A reference to the assignment's PMString file path.
	*/
	virtual const PMString&				GetFile() = 0;

	/**
		Changes the file the assignment writes to.
		@param file - A new file path in the current platform encoding.
	*/
	virtual void						SetFile(const PMString& file) = 0;

	
	/**
		Returns the URI of the assignment itself.
		@return - A reference to the assignment's URI.
	*/
	virtual const URI&					GetURI() = 0;

	/**
		Changes the URI the assignment writes to.
		@param uri - A new URI.
	*/
	virtual void						SetURI(const URI& uri) = 0;

	/**
		The name that this assignment is assigned to.  Currently only displayed in the panel, not used.
		@return - A reference to the assigned name.
	*/
	virtual const PMString&				GetUser() const = 0;

	/**
		Set the name of the assigned user for this assignment.  Currently only displayed in the panel, not used.
		@param user - A PMString containing the new user name.
	*/
	virtual void						SetUser(const PMString& user) = 0;
	
	/**
		The color to use when showing assigned frame edges.
		@return - The UID of the color object, which should be an IInCopyUIColor object.
	*/
	virtual UID							GetColor() const = 0;

	/**
		Set the color for an assignment to use when showing assigned frame edges.
		@param color - The UID of the IInCopyUIColor object.
	*/
	virtual void						SetColor(UID color) = 0;

	/**
		The assignment preview export level for this assignment.
		@return - The export level enumeration.
	*/
	virtual AssignmentExportOptions		GetExportOption() const = 0;

	/**
		Set the assignment preview export level.
		@param options - The enumeration desired.
	*/
	virtual void						SetExportOption(AssignmentExportOptions options) = 0;
	
	/**
		Determines and returns the compatibility for this assignment. This is read-only and, except for Unassigned, is computed based on the 
		assignment file type info ID where kAssignmentFileTypeInfoID is kAssignmentCS3Compatibility and 
		kAssignmentMarkupFileTypeInfoID is kAssignmentCS4Compatibility.
		@return - The compatibility enumeration.
	*/
	virtual AssignmentCompatibility		GetCompatibility() const = 0;
	
	/**
		Whether the assignment needs to be written or not.  Dirty assignments have changed since last updated.
		@return - True if not saved.
	*/
	virtual bool16						GetDirty() = 0;

	/**
		Set whether or not this assignment should be saved.
		@param dirty - Pass true in to make sure this assignment requests to be saved, or 
		false if you want to mark this assignment as up to date.
	*/
	virtual void						SetDirty(bool16 dirty) = 0;
	
	/**
		The list of stories in this assignment. You can ask this list for a const iterator.
		@return - A const reference to the list, which can supply a const_iterator.
	*/
	virtual UIDList		GetStories() const = 0;

	/**
		Adds a story to the assignment.  This must be called from a command.
		@param story - The IAssignedStory to add.
	*/
	virtual void						AddStory(IAssignedStory* story) = 0;

	/**
		Removes a story from the assignment and unregisters it from its page items.  
		This will unreference the story, so keep a reference if you want to use it.
		This must be called from a command.
		@param story - The story to remove.
	*/
	virtual void						RemoveStory(IAssignedStory* story) = 0;

	/**
		Deletes an assigned story from the database.  This must be called from a command.
		@param story - The assigned story to delete.  Do not hold onto this story, 
		as it will be deleted and uncallable after this completes.
	*/
	virtual void						DeleteStory(IAssignedStory* story) = 0;

	/**
		Reorders the story list.  This must be called from a command.
		@param story - The assigned story to move.
		@param beforeStory - The assigned story to place this before.  Pass nil for the end of the list.
	*/
	virtual void						MoveStory(IAssignedStory* story, IAssignedStory* beforeStory) = 0;

	/**
		Process a command to set the various properties of an assignment.
		@param name - A pointer to a new name, or nil to not change the name.
		@param file - A pointer to a new file path, or nil to not change the file path.
		@param user - A pointer to a new user name, or nil to not change the user name.
		@param color - A pointer to the new color, or nil to not change the color.
		@param options - A pointer to the new export options, or nil to not change the export options.
		@param dirty - A pointer to the new dirty flag, or nil to not change the dirty state 
		@param includeLinkFilesPackaging - A pointer to the new option for including linked files when packaging.
		@param uri - A pointer to the new uri, or nil to base the uri on the file if provided or to not change the uri.
		(typically allowing the other changes to dirty the assignment). 
		@return - Any errors that may have occured.
	*/
	virtual ErrorCode					SetPropsCmd(const PMString* name, 
													 const PMString* file, 
													 const PMString* user, 
													 const UID* color,
													 const AssignmentExportOptions* options, 
													 const bool16* dirty,
													 const bool16* includeLinkFilesPackaging,
													 const URI* uri = nil) = 0;

	/**
		Processes a command which removes an assigned story from the assignment.
		@param story - The assigned story to remove.
		@return - Any errors that may have occurred.
	*/
	virtual ErrorCode					RemoveStoryCmd(IAssignedStory* story) = 0;

	/**
		Process a command to move a story within the assigned story list.
		@param story - The story to move.
		@param beforeStory - The story to move before, or nil for the end.
		@return - Any errors that may have occurred.
	*/
	virtual ErrorCode					MoveStoryCmd(IAssignedStory* story, IAssignedStory* beforeStory) = 0;

	/**
		The assignment option for including linked files or not when packaging.
		@return bool16 kTrue if should include, otherwise kFalse.
	*/
	virtual bool16						GetIncludeLinkedFilesWhenPackage() const = 0;

	/**
		Set the assignment option for including linked files or not when packaging.
		@param includeFlag pass kTrue to include linked files, otherwise kFalse.
	*/
	virtual void						SetIncludeLinkedFilesWhenPackage(bool16 includeFlag) = 0;
};

typedef InterfacePtr<IAssignment> IAssignmentPtr;
typedef K2Vector<IAssignment*> IAssignmentList;

#endif //_IASSIGNMENT_

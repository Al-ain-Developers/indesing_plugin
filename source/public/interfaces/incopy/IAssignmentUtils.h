//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IAssignmentUtils.h $
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
//  
//  Functions to aid in InCopy Document file actions
//  
//========================================================================================

#pragma once
#ifndef __IAssignmentUtils__
#define __IAssignmentUtils__

#include "AssignmentID.h"
#include "Utils.h"

#include "KeyValuePair.h"

class IAssignment;
class IAssignedStory;
class IAssignedDocument;
class IHierarchy;
class IScript;
class ITextFrameColumn;


/** Utilities relating to assignments.
	@see IAssignmentMgr
*/
class IAssignmentUtils : public IPMUnknown
{
public:
	enum	{kDefaultIID = IID_IASSIGNMENTUTILS};

	/**
		Get the assignment for a particular IScript object.
		@param script - The IScript object provided by the scripting subsystem.
		@return - The assignment, or nil if things are not going according to plan
	*/
	virtual IAssignment* GetAssignment(const IScript* script) = 0;

	/**
		Get the assigned story for a particular IScript object.
		@param script - The IScript object provided by the scripting subsystem.
		@return - The assigned story, or nil if things are not going according to plan
	*/
	virtual IAssignedStory* GetStory(const IScript* script) = 0;

	/**
		Given a frame, this will figure out if it contains a text model and 
		change the reference to point at that instead.
		@param ref - IN/OUT the spline which may become a text model
	*/
	virtual void NormalizeTextModelRef(UIDRef& ref) = 0;

	/**
		Walks the open document list to see if the given database is still open.
		@param db - A database pointer which may or may not still be open
		@return - whether or not this database is still open
	*/
	virtual	bool16 IsDataBaseOpen(IDataBase* db) = 0;

	/**
		Given a UIDRef, find out its parent on Assignment Manager structure.
		If object is a kAssignedStoryBoss, return its parent kAssignmentBoss UIDRef.
		If object is a kAssignmentBoss, return its parent kDocBoss UIDRef.
		If object is none of above, return UIDRef::gNull.
		@param object
		@return - the parent UIDRef of the object
	*/
	virtual UIDRef GetParent(UIDRef object) = 0;

	/**
		Returns the UID of the graphic frame of the text frame.
		@param frame - The ITextFrameColumn to find the graphic frame from.
		@return - The UID of the IGraphicFrameData
	*/
	virtual UID TextFrameToGraphicFrame(ITextFrameColumn *frame) = 0;

	/**
		Returns the UID of the graphic frame of the IHierarchy frame.
		@param frame - The IHierarchy to find the graphic frame from.
		@return - The UID of the IGraphicFrameData
	*/
	virtual UID TextFrameToGraphicFrame(IHierarchy *frame) = 0;

	/**
		Returns the UID of the graphic frame of the frame.
		@param frame - The frame UIDRef to find the graphic frame from.
		@return - The UID of the IGraphicFrameData
	*/
	virtual UID TextFrameToGraphicFrame(const UIDRef& frame) = 0;

	/**
		Finds the UID of the text frame contained by a graphic frame, optionally finding the
		first frame of the text thread instead of the supplied frame.
		@param frame - The graphic frame's IHierarchy interface.
		@param bFirstFrame - A boolean indicating whether the first text frame is desired.
		@return - The UID of the text frame.
	*/
	virtual UID GraphicFrameToTextFrame(IHierarchy *frame, bool16 bFirstFrame) = 0;

	/**
		Finds the UID of the text frame contained by a graphic frame, optionally finding the
		first frame of the text thread instead of the supplied frame.
		@param frame - The graphic frame's UIDRef.
		@param bFirstFrame - A boolean indicating whether the first text frame is desired.
		@return - The UID of the text frame.
	*/
	virtual UID GraphicFrameToTextFrame(const UIDRef& frame, bool16 bFirstFrame) = 0;

	/**
		Given a database, determines the default assignment folder.  This is a folder in the same 
		location as the InDesign document name after the InDesign document with " Assignments" appended.
		Example: c:\foo.indd, default assignement folder would be c:\foo Assignments\.
		@param db - Database of the InDesign document.
		@return - The default folder name.
	*/
	virtual PMString GetDefaultAssignmentFolder(IDataBase *db) = 0;
	
	/**
		Tests if a specified FileTypeInfoID is for an Assignment document filetype (*.inca *.icma).
		@param fileTypeID is a FileTypeInfoID.
		@return kTrue if the fileTypeID is for an Assignment document file; kFalse otherwise.	 
	*/		 
	virtual bool16 IsAssignmentFileTypeID(const FileTypeInfoID& fileTypeID) const = 0;
	
	/**
		Tests if a specified file extension is for an Assignment document filetype (*.inca *.icma).
		@param fileExt is a file extension.
		@return kTrue if the file extension is for an Assignment document file; kFalse otherwise.	 
	*/		 
	virtual bool16 IsAssignmentFileExtension(const PMString& fileExt) const = 0;
	
	/**
		Tests if a specified FileTypeInfoID is for an InCopy Assignment package filetype (*.incp *.icap).
		@param fileTypeID is a FileTypeInfoID.
		@return kTrue if the fileTypeID is for an InCopy Assignment package file; kFalse otherwise.	 
	*/		 
	virtual bool16 IsInCopyAssignmentPackageFileTypeID(const FileTypeInfoID& fileTypeID) const = 0;
	
	/**
		Tests if a specified FileTypeInfoID is for an InDesign Assignment package filetype (*.indp *.idap).
		@param fileTypeID is a FileTypeInfoID.
		@return kTrue if the fileTypeID is for an InDesign Assignment package file; kFalse otherwise.	 
	*/		 
	virtual bool16 IsInDesignAssignmentPackageFileTypeID(const FileTypeInfoID& fileTypeID) const = 0;

	/**
		Tests if a the format type of the specified story is compatible with the specified assignment.
		That is, INCX and INCD are compatible with IAssignment::kAssignmentCS3Compatibility and ICML
		are compatibile with IAssignment::kAssignmentCS4Compatibility. All story formats are compatible
		with Unassigned Stories assignment.
		@param toAssignment Assignment whose compatibility so compared
		@param storyRef UIDRef of the story whose format type is compared.
		@return bool16 Return kTrue if the format type is compatibile with the assignment compatibility; kFalse otherwise.
		@see IAssignment::AssignmentCompatibility
	*/		 
	virtual bool16 StoryFormatCompatible(IAssignment* toAssignment, UIDRef storyRef) const = 0;
};

#endif //__IAssignmentUtils__

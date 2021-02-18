//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IAssignmentMgr.h $
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
#ifndef _IAssignmentMgr_
#define _IAssignmentMgr_

#include "AssignmentID.h"

#include "IAssignment.h"
#include "IAssignedDocument.h"

class IDocument;
class PMString;
class IINXImportPolicy;


/** This class is used to manage the modeling of assignments, containing one or more stories per document. 

	@see IAssignedDocument
	@see IAssignment
	@see IAssignedStory
*/
class IAssignmentMgr : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IASSIGNMENTMGR };

	/** The status of a frame, according to the Assignment Manager. */
	typedef enum { 
		/** The frame is not an InCopy story. */
		kNotExported, 
		/** The frame is an assigned InCopy story. */
		kAssigned, 
		/** The frame is an unassigned InCopy story (in its unassignment). */
		kUnassigned, 
		/** The frame is an InCopy story that is not contained in its assigned document. */
		kUnknown
	} FrameStatus;

	
	/** Get the assignment status of a UID.
		@param object - The UIDRef of the document, layer, story or article to assign. 
		@return - An boolean indicating whether the specified UID is assigned
	*/
	virtual bool16 IsAssigned(const UIDRef& object) const = 0;

	// assignment data access
	
	/** Save all assignments associated with a specific document
		@param document - The document containing the assignments to be saved
		@param uiFlags - A flag indicating whether or not ui is permitted
		@param forceSave - A flag indicating whether or not up to date assignments should be saved.  If false, only out of date assignments are saved.
		@return - An error code signifying success or failure
	*/
	virtual ErrorCode SaveAssignments(IDocument* document, UIFlags uiFlags = kFullUI, bool16 forceSave = kFalse) = 0;
	
	/** Save an assignment to its file.
		@param assignment - The assignment to export
		@param uiFlags - A flag indicating whether or not ui is permitted
		@return - An error code signifying success or failure
	*/
	virtual ErrorCode SaveAssignment(IAssignment* assignment, UIFlags uiFlags = kFullUI) = 0;
	
	/** Open an assignment from its file and create the document proxy.  This should only be called
		from InCopy when opening an assignment file.
		@parma document - The empty document which will become the proxy.
		@param assignFile - The assignment file path
		@param assignment - An out parameter returning a pointer to the IAssignment (can be nil)
		@param uiFlags - A flag indicating whether or not ui is permitted
		@return - An error code signifying success or failure
	*/
	virtual ErrorCode OpenAssignmentWithProxy(const PMString& assignFile, InterfacePtr<IAssignment>& assignment, UIFlags uiFlags = kFullUI) = 0;
	
	/** Import an assignment.
		@param stream - The stream to import from
		@param policy - The policy to use to import, if nil then will use kICAssignmentImportPolicyBoss
		@param uiFlags - A flag indicating whether or not ui is permitted
		@return - An error code signifying success or failure
	*/
	virtual ErrorCode ImportAssignment(IPMStream* stream, IINXImportPolicy* policy = nil, UIFlags uiFlags = kFullUI) = 0;
	
	/** Export an assignment.
		@param assignment - The assignment to export
		@param stream - The stream to export into
		@param uiFlags - A flag indicating whether or not ui is permitted
		@return - An error code signifying success or failure
	*/
	virtual ErrorCode ExportAssignment(const IAssignment* assignment, IPMStream* stream, UIFlags uiFlags = kFullUI) = 0;
	
	/** Create an assignment (by processing a command)
		@param doc - The assigned document to add this assignment to
		@param assignFile - The file for the assignment, which is empty for the unassignment
		@param saveAssignment - kTrue means to save the assignment, this value is ignored when creating unassigned assignment(not saved)
		@param objects - A UIDList of page items to add to the created assignment, if nil then all unassigned InCopy stories are added
		@return - A refcounted IAssignment pointer
	*/
	virtual IAssignment* CreateAssignmentCmd(IAssignedDocument* doc, const PMString& assignFile, bool16 saveAssignment=kFalse, UIDList* objects = nil) = 0;

	/** Create an assigned story (must be called from a command)
		@param story - The uid of the story to assign
		@return - A refcounted IAssignedStory pointer
	*/
	virtual IAssignedStory* CreateAssignedStory(const UIDRef& story) = 0;

	/** Get an existing assignment
		@param doc - The assigned document which contains the assignment
		@param assignFile - The file for the assignment, which is empty for the unassignment
		@return - A pointer to the resulting IAssignment record
	*/
	virtual IAssignment* QueryAssignment(IAssignedDocument* doc, const PMString& assignFile) const = 0;

	/** Whether a linked file is a text story (as opposed to an image)
		@param docInfo - The IAssignedDocument reference
		@param assignPath - The assignment's file
		@param storyPath - The linked story's path
		@return - Whether or not the storyPath file is a linked story
	*/
	virtual bool16 IsTextStory(IAssignedDocument* docInfo, const PMString& assignPath, const PMString& storyPath) const = 0;

	/** Whether a page item is a text story (as opposed to an image)
		@param itemRef - The page item's UIDRef
		@return - Whether or not the itemRef is a linked story
	*/
	virtual bool16 IsTextStory(const UIDRef& itemRef) const = 0;

	/** Find the IAssignedDocument record based on a document's file path
		@param db - The document's database
		@return - A pointer to the IAssignedDocument record, or nil if there is no info for that document.
	*/
	virtual IAssignedDocument* GetAssignedDocument(IDataBase* db) const = 0;

	/** Find the IAssignedDocument record based on a document's file path
		@param docPath - The document's file
		@return - A pointer to the IAssignedDocument record, or nil if there is no info for that document.
	*/
	virtual IAssignedDocument* GetAssignedDocument(const PMString& docPath) const = 0;

	/** This is used by the panel to get labels for display
		@param storyref - a UIDRef to the story
		@param IAssignment - an out parameter that returns a pointer to the story's IAssignment
		@param IAssignedStory - an out parameter that returns a pointer to the story's IAssignedStory
	*/
	virtual void QueryAssignmentAndAssignedStory(const UIDRef& storyref, InterfacePtr<IAssignment>& iAssignmentRef, InterfacePtr<IAssignedStory>& iAssignedStoryRef) const = 0;
	
	/** Return a list of assigned stories in the document
		@param docInfo - The IAssignedDocument reference
		@param storyList - The returned list of stories
	*/
	virtual void GetStoryListOnDoc(IAssignedDocument* docInfo, UIDList& storyList) const = 0;
	
	/** Return a list of assigned stories in an assignment
		@param docInfo - The IAssignedDocument reference
		@param storyPath - The path of the assignment's file
		@param storyList - The returned list of stories
	*/
	virtual void GetStoryListOnAssignment(IAssignment* assignment, UIDList& storyList) const = 0;

	/** Add some page items to an assignment, removing them from their current assignment if necessary.
		This calls ProcessCommand to perform the operation.
		@param assignment - The assignment to add to.  Use nil for the unassignment.
		@param objects - A UIDList of page items
		@param beforeStory - An assigned story to place this story in front of, defaults to nil, the end of the list
		@param notifyPanel - kTrue to notify the assignment panel to update the assignment node
	*/
	virtual ErrorCode AddToAssignmentCmd(IAssignment* assignment, UIDList& objects, IAssignedStory* beforeStory = nil, bool16 notifyPanel = kTrue) = 0;

	/** This marks all assignments which display this spread as dirty (i.e. need update/export).  This can call ProcessCommand.
		@param spreadRef - A UIDRef to the spread which has changed.
	*/
	virtual ErrorCode DirtySpreadCmd(UIDRef spreadRef) = 0;

	/** Add some page items to an assignment, removing them from their current assignment if necessary.
		This calls ProcessCommand to perform the operation.
		@param docInfo - The IAssignedDocument reference
		@param assignPath - The file path of assignment to add to (empty for unassignments)
		@param objects - A UIDList of page items
		@param notifyPanel - kTrue to notify the assignment panel to update the assignment node
	*/
	virtual ErrorCode AddToAssignmentCmd(IAssignedDocument* docInfo, const PMString& assignPath, UIDList& objects, bool16 notifyPanel = kTrue) = 0;

	/** Return the current state of a particular page item
		@param object - A page item's UIDRef
		@return - An enum describing the status of the page item
	*/
	virtual IAssignmentMgr::FrameStatus GetFrameStatus(const UIDRef& object) const = 0;

	/** Update the Assignment options.  Calls ProcessCommand.
		@param uiFlags - A flag indicating whether or not ui is permitted
		@return - kTrue if this assignment is dirty
	*/
	virtual	bool16 UpdateAssignmentOptions(IAssignment *assignment, const PMString& assignName, const PMString &file, const PMString& assignWriter, const IAssignment::AssignmentExportOptions exportOption, 
		const UID uiColor, const bool16 includeLinkFilesPackaging, UIFlags uiFlags = kFullUI) = 0;
	
	/** Notify the StoryListPanel that it needs to update.
		@param theChange = kAssignmentMgrChangedNotifyMsg will ask the assignment panel to rebuild, this was used when you change the structure of assignment nodes
			   theChange = kAssignmentPanelInvalidateNotifyMsg will cause the assignment panel redraw, this was used when you only want to redraw the panel
	*/
	virtual void NotifyPanel(ClassID theChange  = kAssignmentMgrChangedNotifyMsg) = 0;

	/** Package an assignment into a job bag zip file.
		@param assignment - The assignment to package
		@param packageFile - The file to hold the package, an InCopy assignment package
		@param uiFlags - a flag indicating whether or not ui is permitted
		@return - An error code signifying success or failure
	*/
	virtual ErrorCode PackageAssignment(IAssignment* assignment, const IDFile& packageFile, UIFlags uiFlags = kFullUI) = 0;

	/** Tests whether the specified assignment is packaged or not.
	    @param assignment IN the assignment to test
	    @return bool16 kTrue if assignment is packaged, kFalse otherwise
   */
	virtual bool16 IsAssignmentPackaged(IAssignment* assignment) = 0;

	/** Tests whether the specified assignment's package is up to date or not; that is, did it contain the current assignment file.
	    @param assignment IN the assignment to test
	    @return bool16 kTrue if assignment package is up to date, kFalse otherwise
   */
	virtual bool16 IsAssignmentPackageUpToDate(IAssignment* assignment) = 0;

	/** Return an assignment package to InDesign user.  Creates a package for the assignment at the specified file location
		which includes the assigned stories and the original manifest file and package info file.  Optionally, forwards linked files
		added by InCopy user.
		@param assignment - The assignment to return
		@param packageFile - The file to hold the return package, an InDesign assignment package
		@param uiFlags - a flag indicating whether or not ui is permitted
		@param includeAdded - a flag indicating whether or not added links should be forwarded
		@return - An error code signifying success or failure
	*/
	virtual ErrorCode ReturnPackageAssignment(IAssignment* assignment, const IDFile& packageFile, UIFlags uiFlags = kFullUI, bool16 includeAdded = kTrue) = 0;

	/** Extracts the contents of the package file.  The assignment file to open are returned.
		@param packageFile IN the assignment package file to open
		@param uiFlags - a flag indicating whether or not ui is permitted
	    @param assignmentFileToOpen OUT the assignment file to be opened
	    @return ErrorCode kSuccess if open succeeded, kFailure otherwse.
   */
	virtual ErrorCode ExplodeInCopyPackageForOpen(const IDFile& packageFile, UIFlags uiFlags, IDFile& assignmentFileToOpen) = 0;

	/**	Returns the assignment file to be opened from the specified package file.
		@param packageFile the package file to examine
		@return IDFile the file to be opened
	*/
	virtual IDFile GetAssignmentFileToOpenFromPackage(const IDFile& packageFile) = 0;

	/** Forward an assignment package to another InCopy user.  Creates a package for the assignment at the specified file location
		which includes the assigned stories and the original manifest file and package info file.  Optionally, forwards linked files
		added by InCopy user.
		@param assignment - The assignment to forward
		@param packageFile - The file to hold the forward package, an InCopy assignment package
		@param uiFlags - a flag indicating whether or not ui is permitted
		@param includeAdded - a flag indicating whether or not added links should be forwarded
		@return - An error code signifying success or failure
	*/
	virtual ErrorCode ForwardPackageAssignment(IAssignment* assignment, const IDFile& packageFile, UIFlags uiFlags = kFullUI, bool16 includeAdded = kTrue) = 0;

	/** Extracts the contents of the package file.
		@param packageFile IN the assignment package file to open
		@param assignmentRef IN the current assignment in the original indesign pub
		@param uiFlags - a flag indicating whether or not ui is permitted
	    @return ErrorCode kSuccess if open succeeded, kFailure otherwse.
   */
	virtual ErrorCode ExplodeInDesignPackageForOpen(const IDFile& packageFile, const UIDRef& assignmentRef, UIFlags uiFlags) = 0;

	/** Extracts the contents of the package file to the specified folder.
		@param packageFile IN the assignment package file to open
		@param targetFolder IN the folder to extract the package to
		@param uiFlags - a flag indicating whether or not ui is permitted
   */
	virtual ErrorCode ExplodeInDesignPackageToFolder(const IDFile& packageFile, const IDFile& targetFolder, UIFlags uiFlags) = 0;
};

typedef InterfacePtr<IAssignmentMgr> IAssignmentMgrPtr;

#endif //_IAssignmentMgr_

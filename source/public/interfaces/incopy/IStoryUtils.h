//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IStoryUtils.h $
//  
//  Owner: 
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
#ifndef __IStoryUtils__
#define __IStoryUtils__

#include "InCopySharedID.h"
#include "Utils.h"

class IDocument;
class ILink;

/**
	IStoryUtils is a utility class on the Utils boss which provides common services for InCopy stories.
	This interface should be accessed like so: 
		<pre> Utils<IStoryUtils>()->HasStories( ... ); </pre>
	@see kUtilsBoss
	@see Utils.h
*/
class IStoryUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTORYUTILS };

	/**
		Checks if there are any InCopy stories in a document. Faster than calling GetStories()
		if you just want to know if this document has at least one incopy story.
		@param fromDoc IN document with or without InCopy stories.
		@return bool16 whether or not this document contains incopy stories.
	*/
	virtual bool16 HasStories(const IDocument *fromDoc) const = 0;

	/**
		Collects InCopy stories from a document.
		@param fromDoc IN document with or without InCopy stories.
		@return UIDList with InCopy stories.
	*/
	virtual UIDList GetStories(const IDocument *fromDoc) const = 0;

	/**
		Collects InCopy story links from a document.
		@param fromDoc IN document with or without InCopy stories.
		@return UIDList with InCopy story link UIDs.
	*/
	virtual UIDList GetStoryLinks(const IDocument *fromDoc) const = 0;

	/**
		Check to see if the text model or page item is an InCopy story (text or graphic) - that is,
		it has an InCopy format data link.
		@param itemRef IN text model or page item to examine
		@return bool16 kTrue if the item is an InCopy story (text or graphic).
	*/
	virtual bool16 IsAStory(const UIDRef& itemRef) const = 0;

	/**
		Tests if a specified file format name is for an InCopy story.
		@param formatName is a PMString containing the format name; typically, this PMString can be
			 obtained from the ILinkResource::GetFormatType method.
		@return kTrue if the formatName is for an InCopy story; kFalse otherwise.	 
	*/		 
	virtual bool16 IsAStoryFormatName(const PMString & formatName) const = 0;
	
	/**
		Tests if a specified FileTypeInfoID is for an InCopy interchange filetype.
		@param fileTypeID is a FileTypeInfoID.
		@return kTrue if the fileTypeID is for an InCopy interchange file; kFalse otherwise.	 
	*/		 
	virtual bool16	IsAStoryInterchangeFileTypeID(const FileTypeInfoID& fileTypeID) const = 0;
	
	/**
		Tests if a specified FileTypeInfoID is for an InCopy document filetype (*.incx, *.icml).
		@param fileTypeID is a FileTypeInfoID.
		@return kTrue if the fileTypeID is for an InCopy document file; kFalse otherwise.	 
	*/		 
	virtual bool16	IsAStoryDocumentFileTypeID(const FileTypeInfoID& fileTypeID) const = 0;

	/**
		Tests if a specified FileTypeInfoID is for the current InCopy document filetype (*.incx, *.icml).
		@param fileTypeID is a FileTypeInfoID.
		@return kTrue if the fileTypeID is for the current InCopy document file; kFalse otherwise.	 
	*/		 
	virtual bool16	IsCurrentStoryDocumentFileType(const FileTypeInfoID& fileTypeID) const = 0;

	/**
		Tests if a specified FileTypeInfoID is for the current InCopy filetype.
		@param fileTypeID is a FileTypeInfoID.
		@return kTrue if the fileTypeID is for the current InCopy file; kFalse otherwise.	 
	*/		 
	virtual bool16	IsAnyCurrentStoryFileType(const FileTypeInfoID& fileTypeID) const = 0;

	/**
		Tests if a specified FileTypeInfoID is for an InCopy filetype.
		@param fileTypeID is a FileTypeInfoID.
		@return kTrue if the fileTypeID is for an InCopy file; kFalse otherwise.	 
	*/		 
	virtual bool16	IsAnyStoryFileTypeID(const FileTypeInfoID& fileTypeID) const = 0;

	/** 
		Check if the given InCopy story's link resource is modified or not.
		@param itemRef IN text model or page item to examine.
		@return bool16 kTrue if the text model or page item is an InCopy story and the link resource is modified.
	*/
	virtual bool16 IsLinkResourceOutOfDate(const UIDRef& itemRef) const = 0;

	/**
		CreateLink, unsurprisingly, creates a link for an InCopy story. This will remove and replace any existing link on the story.
		@param story IN The InCopy story UIDRef.
		@param file IN The InCopy story file.
		@param provider IN The ClassID of the provider; for example kInCopyImportProviderBoss.
		@param fileTypeID IN The file type info ID for the InCopy file.
		@param linkUID OUT UID of the created link.
		@return kSuccess if the link was created successfully.
	*/
	virtual ErrorCode CreateLink(const UIDRef& story, const IDFile& file, ClassID provider, FileTypeInfoID fileTypeInfo, UID& linkUID) = 0;

	/** 
		Check if the given InCopy story's link resource is accessible or not.  Note: missing is considered 
		accessible as long as it's parent directory exists.
		@param itemRef IN text model or page item to examine.
		@return bool16 kTrue if the text model or page item is an InCopy story and the link resource is accessible.
	*/
	virtual bool16 IsLinkResourceAccessible(const UIDRef& storyRef) const = 0;
	
	/**
		Test if an ILink instance if for an InCopy story.
		@param iLink valid pointer to  an ILink instance to test.
		@return kTrue if the ILink is for a story; kFalse otherwise.
	*/
	virtual bool16 IsAStoryLink( const ILink * iLink ) const = 0;

	/**
		Get the format type for the InCopy story.  This is the format type of the story's link resource.  See ILinkResource.
		@param itemRef The UIDRef of the InCopy story to get the format type.
		@return PMString The format type if succeeded or an empty string (i.e. item is not an InCopy story).
	*/
	virtual PMString GetStoryFormatType(const UIDRef& itemRef) const = 0;
};

#endif	// __IStoryUtils__

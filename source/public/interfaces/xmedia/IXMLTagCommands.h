//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLTagCommands.h $
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
//  
//  Adobe Patent or Adobe Patent Pending Invention Included Within this File
//  Adobe patent application tracking # P515, entitled 'Representing Structured Data', inventors: Joss
//  
//  Purpose:
//  Processes commands for creating, deleting, and manipulating XML tags.
//  
//========================================================================================

#pragma once
#ifndef __IXMLTagCommands__
#define __IXMLTagCommands__

#include "IPMUnknown.h"
#include "XMLID.h"

class ICommand;
class UIDList;
	
/** Encapsulates commands to change the properties of tags (IXMLTag) and the tag collection (IXMLTagList).
*/
class IXMLTagCommands : public IPMUnknown 
{
	public:
		enum	{kDefaultIID = IID_IXMLTAGCOMMANDS};

		/** Method for creating an XML tag.  Returns the UID of the newly created tag or the UID 
			of an existing tag if a tag by that name already exists.  Will return an error if the 
			tag name specified is not valid. This and related methods may process a command of 
			type kXMLCreateTagCmdBoss behind the facade
			@param tagList the tag list (IXMLTagList) to which the tag is to be added
			@param tagName specifes the name for the tag (without begin/end markers), see IXMLTag
			@param createdTag [OUT] ptr to UID for created tag
			@return kSuccess if the operation succeeded, kFailure otherwise
		*/
		virtual ErrorCode CreateTag(const UIDRef& tagList, const WideString& tagName, UID tagColor = kInvalidUID, UID* createdTag = nil) = 0;

		/** Delete a tag. Requires a tag that can be used to replace the deleted tag with. This 
			and related methods may process a command of type kXMLDeleteTagCmdBoss behind the 
			facade
			@param tagList tag list  (IXMLTagList) from which tag should be deleted
			@param tag specifies to the tag to be deleted
			@param tagReplaceWith specifies the tag to replace the one being deleted with
			@return kSuccess if the operation succeeded, kFailure otherwise	
		*/ 
		virtual ErrorCode DeleteTag(const UIDRef& tagList, UID tag, UID tagReplaceWith) = 0;

		/** Delete a set of tags. Requires a tag that can be used to replace the deleted tag 
			with. This and related methods may process a command of type kXMLDeleteTagCmdBoss 
			behind the facade
			@param tagList (IXMLTagList) from which tags should be deleted
			@param tagsToDelete UIDList of tags to remove
			@param tagReplaceWith specifies one tag to replace all those in deleted list by
			@return kSuccess if the operation succeeded, kFailure otherwise
		*/
		virtual ErrorCode DeleteTags(const UIDRef& tagList, const UIDList& tagsToDelete, UID tagReplaceWith) = 0;
		
		/** Find the set of tags that are not referenced by any element and delete them. This and 
			related methods may process a command of type kXMLDeleteUnusedTagsCmdBoss behind the 
			facade
			@param tagList specifies tag-list (IXMLTagList) from which tags should be deleted
			@return kSuccess if the operation succeeded, kFailure otherwise
		*/
		virtual ErrorCode DeleteUnusedTags(const UIDRef& tagList) = 0;

		/** Method to change the name of a tag. This and related methods may process a command of 
			type kXMLSetTagNameCmdBoss behind the facade
			@param db database containing the tag-list (IXMLTagList)
			@param tag specifies the tag to be renamed
			@param tagName specifies the new name for the tag (see IXMLTag)
			@return kSuccess if the operation succeeded, kFailure otherwise
		*/
		virtual ErrorCode SetTagName(IDataBase* db, UID tag, const WideString& tagName) = 0;
		
		/** Method to change the color of a tag. This and related methods may process a command 
			of type kXMLSetTagColorCmdBoss behind the facade
			@param db database containing the tag-list (IXMLTagList)
			@param tag specifies the tag whose color is to be changed
			@param color specifies the new color for the tag
			@return kSuccess if the operation succeeded, kFailure otherwise
		*/
		virtual ErrorCode SetTagColor(IDataBase* db, UID tag, UID color) = 0;
		
		/** Save the list of tags to the specified file. This and related methods may process a 
			command of type kSaveTagListCmdBoss behind the facade
			@param tagList (IXMLTagList) specifies tag-list to be saved out
			@param theFile specifies destination file
			@return kSuccess if the operation succeeded, kFailure otherwise
		*/
		virtual ErrorCode SaveTagList(const UIDRef& tagList, const IDFile& theFile) = 0;

		/**  Load the tag list from another InDesign document or an xml file. This and related 
			methods may process a command of type kLoadTagListCmdBoss behind the facade
			@param tagList tag-list (IXMLTagList) into which the tags are to be loaded
			@param theFile target file from which tag-list is to be loaded
			@return kSuccess if the operation succeeded, kFailure otherwise
		*/
		virtual ErrorCode LoadTagList(const UIDRef& tagList, const IDFile& theFile) = 0;
};
	
#endif // __IXMLElementCommands__

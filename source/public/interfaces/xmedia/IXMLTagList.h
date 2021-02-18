//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLTagList.h $
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
#ifndef __IXMLTagList__
#define __IXMLTagList__

#include "IPMUnknown.h"
#include "XMLID.h"
#include "UIDList.h"

/** This is interface is designed to hold a list of XML tag names
	stored in the workspaces (documents or session); use IXMLTagCommands rather
	than calling mutators on this interface from client code.
*/
class IXMLTagList : public IPMUnknown
{
	public:
		enum	{kDefaultIID = IID_IXMLTAGLIST};

		/** Get the tag object specified by the tag name.  
			@param tagName name of the tag of interest (see IXMLTag)
			@return UID of named tag, or kInvalidUID if the tag is not in the list
		*/
		virtual UID GetTag(const WideString& tagName) const = 0;

		/** Does the tag list already contain this tag?
			@param tag specifies tag of interest
			@return if the tag-list contains specified tag, kFalse otherwise
		*/
		virtual bool16 HasTag(UID tag) const = 0;

		/** Accessor for count of tags stored on this
			@return count of tags in list
		*/
		virtual int32	GetNumberOfTags() const = 0;
		/** Accessor for tag stored on this interface by index
			@return UID of tag at specified index in zero-based collection
		*/
		virtual UID GetNthTag(int32 index) const = 0;

		/**  Accessor for name of tag stored on this interface by index.
			@return name of tag at specified index in zero-based collection.
		*/
		virtual WideString GetNthTagString(int32 index) const = 0;
		
		/** Mutator; use IXMLTagCommands from client code.
			@param tag specifies tag to be added.
		*/
		virtual void		AddTag(UID tag) = 0;

		/** Mutator; use IXMLTagCommands from client code 
			@param tag specifies UID of tag to be removed
		*/
		virtual void 	RemoveTag(UID tag) = 0;

		/** Mutator, which sorts tag names alphabetically. This should be called after a tag has	
			changed its name. It should not be called after Add and Remove tags;
			this is handled automatically by the list. 
		*/
		virtual void Sort() = 0;
		
		/** [INTERNAL USE ONLY]
			Add a tag with the given name if one doesn't already exist
			@param tagName name of the tag to search for and add
			@param tagColorUID if need to create new tag, use this as tag color
			@param [OUT] optionally receives whether a new tag was made
			@return UID of named tag
		*/
		virtual UID AddTag(const WideString& tagName, UID tagColorUID, bool16 *newTag = nil) = 0;
};

#endif


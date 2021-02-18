//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLStyleToTagMap.h $
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
#ifndef __IXMLStyleToTagMap__
#define __IXMLStyleToTagMap__

#include "IPMUnknown.h"
#include "XMLID.h"

/**  This interface describes a style to tag mapping used for defining structure inside
	of text frames; rather than calling mutators on
	this from client code, use IXMLMappingCommands methods in preference.  
	
	This interface belongs to the document workspace and is used
	to store a set of associations between
	a Style UID (in the paragraph or character style name table) and an IXMLTag.
	Low-level commands such kXMLMapParaStyleToTagCmdBoss use this interface, but this and related commands
	are  processed by IXMLMappingCommands.
*/
class IXMLStyleToTagMap : public IPMUnknown
{
	public:
		enum	{kDefaultIID = IID_IXMLSTYLETOTAGMAP};


		/**	Copy contents of an existing IXMLStyleToTagMap into this interface
			@param dataToCopy [IN] parameter
		 */
		virtual void CopyData(IXMLStyleToTagMap* dataToCopy) = 0;


		/**	Add an associative map between a style specified by UID and a tag specified by UID
			@param style UID of style (paragraph or character) in style name table
			@param tag UID of tag (IXMLTag) in tag list, IXMLTagList
		 */
		virtual void AddMapping(UID style, UID tag) = 0;

		/**	Remove style-tag mapping for given style UID
			@param style UID of style (paragraph or character) in style name table
		 */
		virtual void RemoveMapping(UID style) = 0;

		/**	Empty the contents of this mapping.		
		 */
		virtual void ClearMap() = 0;
	

		/**	Determine if given style has mapping to an element tagname
			@param style UID in the style name table (paragraphs or characters)
			@return kTrue if style is mapped to a tag, kFalse otherwise
		 */
		virtual bool16 IsStyleMapped(UID style) const = 0;

		/**	Determine number of entries in the map
			
			@return size of map
		 */
		virtual int32 GetMappingCount() const = 0;

		/**	Accessor for style UID of mapping by index
			@param pos specifies index of interest, should be 0 < pos < GetMappingCount()
			@return UID of entry in the map, which 
		 */
		virtual UID GetStyleAt(int32 pos) const = 0;

		/**	Accessor for tag UID that you can use to get IXMLTag interface, given a style UID
			@param style UID of style (paragraph or character) in style name table
			@return UID of IXMLTag corresponding to given style UID
		 */
		virtual UID GetTagMappedToStyle(UID style) const = 0;

		/**	Accessor for whether or not to include master page stories when mapping.
			@return bool16 to include (kTrue) or exclude (kFalse) master page stories
		 */
		virtual bool16 GetIncludeMasterPageStories() const = 0;

		/**	Set whether or not to include master page stories when mapping.
			@param include bool flag to include (kTrue) or exclude (kFalse) master page stories
		 */
		virtual void SetIncludeMasterPageStories(bool16 include) = 0;

		/**	Accessor for whether or not to include pasteboard stories when mapping.
			@return bool16 to include (kTrue) or exclude (kFalse) pasteboard stories
		 */
		virtual bool16 GetIncludePasteboardStories() const = 0;

		/**	Set whether or not to include pasteboard stories when mapping.
			@param include bool flag to include (kTrue) or exclude (kFalse) pasteboard stories
		 */
		virtual void SetIncludePasteboardStories(bool16 include) = 0;

		/**	Accessor for whether or not to include empty stories when mapping.
			@return bool16 to include (kTrue) or exclude (kFalse) empty stories
		 */
		virtual bool16 GetIncludeEmptyStories() const = 0;

		/**	Set whether or not to include empty stories when mapping.
			@param include bool flag to include (kTrue) or exclude (kFalse) empty stories
		 */
		virtual void SetIncludeEmptyStories(bool16 include) = 0;
};

#endif
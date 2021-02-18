//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLMappingCommands.h $
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
#ifndef __IXMLMappingCommands__
#define __IXMLMappingCommands__

#include "IPMUnknown.h"
#include "XMLID.h"

class ICommand;
	
/** Processes commands for creating, deleting, and manipulating mappings from tags to styles
	and styles to tags. Tag to style mappings are referenced during the XML import process to apply the approriate text styles
	to the incoming XML content.
	Style to tag mappings are used to automatically tag a document based on the ranges of text specified
	by style ranges.
*/
class IXMLMappingCommands : public IPMUnknown 
{
	public:
		enum	{kDefaultIID = IID_IXMLMAPPINGCOMMANDS};
		

		/**	Map the specified tag to the specified style.  If the tag has already been
			been associated with a style then this will map the tag to the new style.
			Processes kXMLMapTagToStyleCmdBoss behind the facade
			@param tagToStyleMap specifies tag-to-style map (IXMLTagToStyleMap)
			@param tag specifies tag to associate (IXMLTag)
			@param style specifies style (from style name table, e.g. IStyleInfo)
			@return ErrorCode kSuccess if operation could be completed, kFailure otherwise.
		 */
		virtual ErrorCode MapTagToStyle(const UIDRef& tagToStyleMap, UID tag, UID style) = 0;

		/**	Delete the mapping between a tag and a style. Processes kXMLUnMapTagToStyleCmdBoss
			behind the facade.

			@param tagToStyleMap specifies tag-to-style map (IXMLTagToStyleMap)
			@param tag specifies the tag (IXMLTag)to remove from the mapping
			@return ErrorCode kSuccess if operation could be completed, kFailure otherwise. 
		 */
		virtual ErrorCode UnMapTagToStyle(const UIDRef& tagToStyleMap, UID tag) = 0;
		
		/**	Copy the set of associations from one map to another.
			@param sourceMap specifies source map (IXMLTagToStyleMap)
			@param targetMap specifies destination map (IXMLTagToStyleMap)
			@return ErrorCode kSuccess if operation could be completed, kFailure otherwise. 
		 */
		virtual ErrorCode CopyTagToStyleMap(const UIDRef& sourceMap, const UIDRef& targetMap) = 0;
		
		/**	Map the specified style to the specified tag.  If the style has already been
			been associated with a tag then this will map the style to the new tag.

			@param styleToTagMap styleToTagMap specifies IXMLStyleToTagMap
			@param style specifies style (from style name table, e.g. IStyleInfo)
			@param tag specifies the tag (IXMLTag) to associate with given style
			@return ErrorCode kSuccess if operation could be completed, kFailure otherwise. 
		 */
		virtual ErrorCode MapStyleToTag(const UIDRef& styleToTagMap, UID style, UID tag) = 0;


		/**	Delete the mapping between a style and a tag.
			@param styleToTagMap  styleToTagMap specifies IXMLStyleToTagMap
			@param style  from style name table (IStyleInfo) to remove from mapping
			@return ErrorCode kSuccess if operation could be completed, kFailure otherwise. 
		 */
		virtual ErrorCode UnMapStyleToTag(const UIDRef& styleToTagMap, UID style) = 0;

		/**	Copy the set of associations from one map to another.
			@param sourceMap specifies source map (IXMLStyleToTagMap)
			@param targetMap specifies destination map (IXMLStyleToTagMap)
			@return ErrorCode kSuccess if operation could be completed, kFailure otherwise. 
		 */
		virtual ErrorCode CopyStyleToTagMap(const UIDRef& sourceMap, const UIDRef& targetMap) = 0;
};
	
#endif

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLTagToStyleMap.h $
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
#ifndef __IXMLTagToStyleMap__
#define __IXMLTagToStyleMap__

#include "IPMUnknown.h"
#include "XMLID.h"

/** This interface describes a tag to style mapping used when importing an XML document
	and applying predefined paragraph styles to the text.  It belongs to the document workspace.
	From client code, you should use IXMLMappingCommands if you want to vary the contents of this map
	rather than calling mutators on this interface.

*/
class IXMLTagToStyleMap : public IPMUnknown
{
	public:
		enum	{kDefaultIID = IID_IXMLTAGTOSTYLEMAP};


		/**	Mutator to copy information out of another tag-style mapping into this one; use IXMLMappingCommands::CopyTagToParaStyleMap
			instead from client code.
			@param dataToCopy specifies the mapping to copy data from
		 */
		virtual void CopyData(IXMLTagToStyleMap* dataToCopy) = 0;


		/**	Mutator to add a given mapping; use IXMLMappingCommands::MapTagToParaStyle instead from client code.
			@param tag specifies the tag (IXMLTag) of interest
			@param style specifies the paragraph style of interest in the paragraph style name-table (IStyleNameTable, IID_IPARASTYLEGROUPMANAGER)
		 */
		virtual void AddMapping(UID tag, UID style) = 0;

		/**	Mutator to remove a given mapping; use IXMLMappingCommands::UnMapTagToParaStyle instead from client code.
			@param tag specifies the tag (IXMLTag) of interest
		 */
		virtual void RemoveMapping(UID tag) = 0;

		/**	Mutator to empty the map
			
		 */
		virtual void ClearMap() = 0;
	

		/**	Accessor to determine whether a given tag (IXMLTag) has an associated mapping in this
			@param tag specifies the tag (IXMLTag) of interest
			@return kTrue if given tag exists in map stored on this interface, kFalse otherwise
		 */
		virtual bool16 IsTagMapped(UID tag) const = 0;

		/**	Accessor for the map size
			
			@return  size of the associative mapping held in this
		 */
		virtual int32 GetMappingCount() const = 0;

		/**	Accessor for the tag at the given index position
			@param pos zero-based index, 0 <= pos < GetMappingCount()
			@return UID of the requested tag, kInvalidUID if out of range
		 */
		virtual UID GetTagAt(int32 pos) const = 0;

		/**	Accessor for the style UID in paragraph name table (IStyleNameTable, IID_IPARASTYLEGROUPMANAGER) associated with given tag (IXMLTag)
			@param tag specifies the tag (IXMLTag) of interest
			@return UID paragraph style requested if one exists associated with the given tag, kInvalidUID otherwise
		 */
		virtual UID GetStyleMappedToTag(UID tag) const = 0;
};

#endif
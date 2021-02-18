//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IIndexEntryData.h $
//  
//  Owner: Michel Hutinel
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
//  Comments: This interface saves the information about a Index Entry.
//  
//========================================================================================

#pragma once
#ifndef __IINDEXENTRYDATA__
#define __IINDEXENTRYDATA__

#include "IPMUnknown.h"
#include "IndexingID.h"

class IndexTopicEntry;
class UIDRef;

/** Data interface that aggregates information about an index entry.
	@ingroup layout_index
*/
class IIndexEntryData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINDEXENTRYDATA };
		
		/** Specifies the type of the index entry */
		enum IndexEntryType { kNoEntryType, kPageRefType, kXRefType };

		/**	Retrieves the type of the index entry.
			@see IndexEntryType.
			@return the entry type. 
		 */
		virtual const IndexEntryType	GetEntryType() const = 0;		

		/**	Sets the type of an index entry.
			@param entryType [IN] - the type of the entry.
		 */
		virtual void					SetEntryType(const IndexEntryType entryType) = 0;

		/**	Retrieves the section UID of the topic entry referenced by this index entry.
			@return UID of the topic section.
		 */
		virtual const UID				GetTopicSectionUID() const = 0;		

		/**	Sets the topic section UID for this index entry.
			@param topicSectionUID [IN] - the section UID for this index entry.
		 */
		virtual void					SetTopicSectionUID(const UID topicSectionUID) = 0;

		/**	Retrieves the topic entry referenced by this index entry. 
			@param topicEntry [OUT] - the topic entry associated with this index entry.
			@param sectionUID [OUT] - optional, UID of the topic section.
			@param nodeId [OUT] - optional, the topic node id.
		 */
		virtual void					GetTopicEntry(IndexTopicEntry& topicEntry, UID *sectionUID = nil, int32 *nodeId = nil) const = 0;

		/**	Retrieves the UIDRef of the topic list that contains the topic referenced by this index entry.
			@param topicListUIDRef [OUT] - UIDRef of the topic list.
		 */
		virtual void					GetTopicListUIDRef(UIDRef& topicListUIDRef) const = 0;

		/**	Retrieves the book content UID referenced by this index entry.
			@return UID of the book content.
		 */
		virtual const UID				GetBookContentUID() const = 0;		

		/**	Sets the book content UID referenced by this index entry.
			@param bookContentUID [IN] - the book content UID associated with this index entry.
		 */
		virtual void					SetBookContentUID(const UID& bookContentUID) = 0;
};

#endif // __IINDEXENTRYDATA__
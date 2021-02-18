//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IIndexTopicList.h $
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
//  Comments: This class keeps track of an Index Topic list on Session/Doc workspace.
//  
//========================================================================================

#pragma once
#ifndef __IINDEXTOPICLIST__
#define __IINDEXTOPICLIST__

#include "IndexingID.h"
#include "IIndexPageEntryData.h"
#include "KeyValuePair.h"

class PMString;
class WideString;
class IndexSectionHeader;
class IIndexHeaderSetOptions;
class IndexTopicEntry;
class UIDRef;

//----------------------------------------------------------------
// IDXPageRangeData Class declaration
//----------------------------------------------------------------
class IDXPageRangeData
{
	public:
		typedef object_type data_type;
		IDXPageRangeData():
			fStartPageIndex(-1),
			fEndPageIndex(-1),
			fStartPageString(kNullString),
			fEndPageString(kNullString),
			fStartPageUseTCY(kTrue),
			fEndPageUseTCY(kTrue),
			fMarkerPlace(IIndexPageEntryData::kDummyValue),
			fPageRangeType(IIndexPageEntryData::kNoPageRange),
			fStyleUID(kInvalidUID),
			fBookContentUID(kInvalidUID),
			fPageEntryUIDRef(kInvalidUIDRef)
			{}

		bool16 operator==(const IDXPageRangeData& other) const
		{ 
			return ( (fStartPageIndex == other.fStartPageIndex) && 
					 (fEndPageIndex == other.fEndPageIndex) && 
					 (fStartPageString == other.fStartPageString) && 
					 (fEndPageString == other.fEndPageString) && 
					 (fStartPageUseTCY == other.fStartPageUseTCY) && 
					 (fEndPageUseTCY == other.fEndPageUseTCY) && 
					 (fMarkerPlace == other.fMarkerPlace) && 
					 (fPageRangeType == other.fPageRangeType) &&
					 (fStyleUID == other.fStyleUID) && 
					 (fBookContentUID == other.fBookContentUID) );
		}

		int32	fStartPageIndex;
		int32	fEndPageIndex;
		PMString fStartPageString;
		PMString fEndPageString;
		bool16  fStartPageUseTCY;
		bool16  fEndPageUseTCY;
		IIndexPageEntryData::MarkerPlace fMarkerPlace;
		IIndexPageEntryData::PageRangeType fPageRangeType;
		UID     fStyleUID;
		UID     fBookContentUID;
		UIDRef	fPageEntryUIDRef;
};

class IDXPageRangeKey
{
	public:
		typedef object_type data_type;
		IDXPageRangeKey():
			fSectionUID(kInvalidUID),
			fNthNode(-1),
			fNthEntry(-1)
			{}
		IDXPageRangeKey(const UID& sectionUID, const int32& nthNode, const int32& nthEntry):
			fSectionUID(sectionUID),
			fNthNode(nthNode),
			fNthEntry(nthEntry)
			{}
		bool16 operator==(const IDXPageRangeKey& other) const
		{ 
			return ( (fSectionUID == other.fSectionUID) && 
					 (fNthNode == other.fNthNode) && 
					 (fNthEntry == other.fNthEntry) ); 
		}

		UID     fSectionUID;
		int32	fNthNode;
		int32	fNthEntry;
};

typedef K2Vector<KeyValuePair<IDXPageRangeKey, IDXPageRangeData> > IDXPageRangeDataMap;

/** Data interface that models a list of index topics.
	This list is aggregated by the session/document workspace
	and contains the topic section UIDs.
	Each section contains a list of topics.
	@ingroup layout_index
*/
class IIndexTopicList : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINDEXTOPICLIST };

		/** This method is not used and it will be deprecated 
		*/
		virtual bool16			IsModifiedWithoutAvailableHSHandler() const = 0;

		/** This method is not used and it will be deprecated 
		*/
		virtual void			SetModifiedWithoutAvailableHSHandler(bool16 modified) = 0;

		/**	Retrieves the total number of topic sections within this list.
			@return number of topic sections. 
		*/
		virtual const int32		GetNumTopicSections() const = 0;

		/**	Retrieves the total number of topics contained in this list.
			@return number of topics. 
		*/
		virtual const int32		GetNumTopics() const = 0;

		/**	Adds a topic section to the list.
			@param indexUID [IN] - the UID of the topic section to be added to the list.
		 */
		virtual void			AddTopicSection(UID indexUID) = 0;

		/**	Removes a topic section from the list.
			@param indexUID [IN] - the UID of the topic section to be removed. 
		 */
		virtual void			RemoveTopicSection(UID indexUID) = 0;

		/**	Removes all topic sections from the list.
		 */
		virtual void			ClearTopicSectionList() = 0;

		/**	Retrieves the UID of the topic section at the specified index.
			@param id [IN] - index of the desired topic section.
			@return the UID of the specified topic section.
		 */
		virtual const UID		GetNthTopicSectionUID(int32 id) const = 0;

		/**	Retrieves the index of the specified topic section UID.
			@param sectionUID [IN] - the UID of the topic section.
			@return the index within the list of the specified topic section.
		 */
		virtual const int32		GetTopicSectionId(UID sectionUID) const = 0;

		/**	Retrieves the topic section header at the specified index.
			@param id [IN] - index of the section header in the list.
			@return the desired section header.
			@see IndexSectionHeader
		 */
		virtual const IndexSectionHeader&	GetNthTopicSectionHeader(int32 id) const = 0;

		/** Adds an index instance.
			This method was initially intended to be used for the case when we have
			multiple instances of an index of the same topic list.
			This method is not currently used.
			@see IIndexInstanceList
		*/
		virtual void			AddIndexInstance(const UID indexUID) = 0;

		/** Removes an index instance.
			This method was initially intended to be used for the case when we have
			multiple instances of an index of the same topic list.
			This method is not currently used.
			@see IIndexInstanceList
		*/
		virtual void			RemoveIndexInstance(const UID indexUID) = 0;

		/** Retrieves the number of index instances.
			This method was initially intended to be used for the case when we have
			multiple instances of an index of the same topic list.
			This method is not currently used.
			@see IIndexInstanceList
		*/
		virtual	const int32		GetNumOfIndexInstances() const = 0;

		/** Retrieves the index instance at the specified index.
			This method was initially intended to be used for the case when we have
			multiple instances of an index of the same topic list.
			This method is not currently used.
			@see IIndexInstanceList
		*/
		virtual const UID		GetNthIndexInstance(int32 id) const = 0;

		/** Finds an index instance by name.
			This method was initially intended to be used for the case when we have
			multiple instances of an index of the same topic list.
			This method is not currently used.
			@see IIndexInstanceList
		*/
		virtual const UID		FindIndexInstanceByName(const PMString& name) const = 0;

		/**	Gets the parent node id of the specified topic node.
			This method is mostly used by the UI.
			@see IndexTopicEntryNode
			@param sectionId [IN] - section id where the topic resides.
			@param childNodeId [IN] - id of the topic node within the section.
			@return the id of the parent topic node.
			If no parent is found or if the child is the top most node the function returns -1.
		 */
		virtual const int32		GetParentNodeId(int32 sectionId, int32 childNodeId) const = 0;

		/**	Retrieves the number of children nodes of the specified topic node.
			This method is mostly used by the UI.
			@param sectionId [IN] - the section id where the specified topic resides.
			@param parentNodeId [IN] - id of the topic within the section.
			@param excludeUnused [IN] - flag that specifies is the unused topics should be excluded.
			@return the number of children topic nodes that the specidfied topic has.
		 */
		virtual const int32		GetNumChildrenOfNode(int32 sectionId, int32 parentNodeId, bool16 excludeUnused = kFalse) const = 0;

		/**	Retrieves the specified child node id.
			This method is mostly used by the UI.
			@param sectionId [IN] - the section id where the specified topic resides.
			@param parentNodeId [IN] - id of the topic whithin the section.
			@param nth [IN] - index of the child node within it's parent node.
			@param excludeUnused [IN] - flag that specifies is the unused topics should be excluded.
			@return the node id of the specified child.
		 */
		virtual const int32		GetNthChildNodeId(int32 sectionId, int32 parentNodeId, int32 nth, bool16 excludeUnused = kFalse) const = 0;

		/**	Retrieves the index of the specified child node within it's parent node.
			This method is mostly used by the UI.
			@param sectionId [IN] - the section id where the specified topic resides.
			@param parentNodeId [IN] - id of the topic whithin the section.
			@param childNodeId [IN] - the node id of the specified child
			@param excludeUnused [IN] - flag that specifies is the unused topics should be excluded.
			@return the index of the child within it's parent node.
		 */
		virtual const int32		GetChildRank(int32 sectionId, int32 parentNodeId, int32 childNodeId, bool16 excludeUnused = kFalse) const = 0;

		/**	Retrieves the display string for the specified topic.
			This method is mostly used by the UI.
			The display string can be different from the sort string.
			@param sectionId [IN] - the section id where the specified topic resides.
			@param nodeId [IN] - id of the topic whithin the section.
			@param string [OUT] - on return will contain the display string of the specified topic.
		 */
		virtual void			GetDisplayString(int32 sectionId, int32 nodeId, WideString& string) const = 0;

		/**	Retrieves the number of page entries associated with the specified topic.
			This method is mostly used by the UI.
			@param sectionId [IN] - the section id where the specified topic resides.
			@param nodeId [IN] - id of the topic whithin the section.
			@return the number of associated page entries.
		 */
		virtual const int32		GetNumPageEntriesOfNode(int32 sectionId, int32 nodeId) const = 0;

		/**	Retrieves the index of the specified page entry within that topic.
			This method is mostly used by the UI.
			@param sectionId [IN] - the section id where the specified topic resides.
			@param nodeId [IN] - id of the topic whithin the section.
			@param entryUIDRef [IN] - UID of the page entry we are looking for.
			@return the index of the specified page entry.
		 */
		virtual const int32		GetPageEntryRankInNode(int32 sectionId, int32 nodeId, UIDRef entryUIDRef) const = 0;

		/**	Retrieves the UIDRef of the specified page entry.
			This method is mostly used by the UI.
			@param sectionId [IN] - the section id where the specified topic resides.
			@param nodeId [IN] - id of the topic whithin the section.
			@param nth [IN] - index of the page entry within the topic (see GetPageEntryRankInNode)
			@param entryUIDRef [OUT] - the UIDRef of the specified page entry.
		 */
		virtual void			GetNthPageEntryUIDRef(int32 sectionId, int32 nodeId, int32 nth, UIDRef& entryUIDRef) const = 0;

		/**	Retrieves the number of cross-references that refer to the specified node.
			This method is mostly used by the UI.
			@param sectionId [IN] - the section id where the specified topic resides.
			@param nodeId [IN] - id of the topic whithin the section.
			@return number of cross-references to the specified topic.
		 */
		virtual const int32		GetNumXRefEntriesOfNode(int32 sectionId, int32 nodeId) const = 0;

		/**	Retrieves the specified cross-reference.
			This method is mostly used by the UI.
			@param sectionId [IN] - the section id where the specified topic resides.
			@param nodeId [IN] - id of the topic whithin the section.
			@param nth [IN] - index (0-based) of the cross-reference. 
			@return UID of the cross-reference.
		 */
		virtual const UID		GetNthXRefEntryUID(int32 sectionId, int32 nodeId, int32 nth) const = 0;

		/**	Retrieves the UID of the kIndexXRefLinksBoss that manages the cross-references
			for the specified topic.
			This method is mostly used by the UI.
			@param sectionId [IN] - the section id where the specified topic resides.
			@param nodeId [IN] - id of the topic whithin the section.
			@return UID  of the kIndexXRefLinksBoss.
		 */
		virtual const UID		GetXRefLinksUID(int32 sectionId, int32 nodeId) const = 0;

		/**	Retrieves the section and node id of the topic referenced by the specified cross-reference.
			This method is mostly used by the UI.
			@param xRefLinksUID [IN] - the UID of the cross-reference.
			@param sectionUID [OUT] - on return will contain the section UID of the referenced topic
			or kInvalidUID if the function fails.
			@param nodeId [OUT] - on return will contain the node id of the referenced topic or -1 
			if the function fails.
		 */
		virtual	void			GetRefedTopicNodeId(const UID xRefLinksUID, UID& sectionUID, int32& nodeId) const = 0;

		/**	Retrieves the complete topic entry that contains the topic
			specified by the section and node id. If there are any parent topic nodes,
			they will be filled in the result topic entry.
			@doc Example: if we have a topic hierarchy like [Fruit | Apple | Jonathan],
			and we call this method passing the section and node id of topic "Jonathan",
			we will get back a topic entry that contains [Fruit | Apple | Jonathan] -
			all three topics. If we call it with the section and node id of the topic "Apple"
			we will get back [Fruit | Apple].
			@see IndexTopicEntry.
			@param sectionId [IN] - the section id where the specified topic resides.
			@param nodeId [IN] - id of the topic whithin the section.
			@param topicEntry [OUT] - complete topic entry that will contain the specified topic node
			and it's parents.
		 */
		virtual void			GetTopicEntry(int32 sectionId, int32 nodeId, IndexTopicEntry& topicEntry) const = 0;

		/**	Checks if the specified topic has at least one index reference
			(page reference, cross-reference or pointed by a cross-reference).
			@param sectionId [IN] - the section id where the specified topic resides.
			@param nodeId [IN] - id of the topic whithin the section.
			@param includeChildren [IN] - flag that specifies if the children of the specified
			topic should be included in the search.
			@return kTrue if the specified topic is used in at least one index reference.
		 */
		virtual bool16			TopicEntryIsUsed(int32 sectionId, int32 nodeId, bool16 includeChildren = kTrue) const = 0;

		/**	Finds a topic entry by matching the display name.
			@param topicEntry [IN/OUT] - topic entry used as a reference entry to find out the
			entry above or below topicEntry.
			@param startSectionId [IN] - section where the search should start.
			@param startNodeId [IN]- the topic node id with which the search should start.
			@param foundSectionId [OUT] - on return will contain the section id where the topic is located. 
			@param foundNodeId [OUT] - on return will contain the node id of the located topic.
			@param caseSensitive [IN] - flag that specifies if the match is case sensitive
			@param wholeWord [IN] - flag that specifies if the match is partial or whole word.
			@param searchDir [IN] - flag that specifies the search direction. kTrue means forward/down.
			@return kTrue if the entry was found.
		 */
		virtual bool16			FindTopicEntryByDisplay(IndexTopicEntry& topicEntry,
												int32 startSectionId = 0,
												int32 startNodeId = 0,
												int32* foundSectionId = NULL,
												int32* foundNodeId = NULL,
												bool16 caseSensitive = kTrue,
												bool16 wholeWord = kTrue,
												bool16 searchDir = kTrue) const = 0;

		/**	Finds a topic that matches the specified string.
			@param startSectionId [IN] - section where the search should start.
			@param startNodeId [IN]- the topic node id with which the search should start.
			@param startXRefId [IN] - the start index for the search.
			@param foundSectionId [OUT] - on return will contain the section id where the topic is located. 
			@param foundNodeId [OUT] - on return will contain the node id of the located topic.
			@param foundXRefId [OUT] - the result index of the found entry.
			@param caseSensitive [IN] - flag that specifies if the match is case sensitive
			@param wholeWord [IN] - flag that specifies if the match is partial or whole word.
			@param searchDir [IN] - flag that specifies the search direction. kTrue means forward/down.
			@return kTrue if the string was found.
		 */
		virtual bool16			FindStringByDisplay(const WideString& str,
													int32 startSectionId = 0,
													int32 startNodeId = 0,
													int32 startXRefId = 0,
													int32* foundSectionId = NULL,
													int32* foundNodeId = NULL,
													int32* foundXRefId = NULL,
													bool16 caseSensitive = kTrue,
													bool16 wholeWord = kTrue,
													bool16 searchDir = kTrue,
													int32* currentSearchNum = NULL) const = 0;

		/**	Finds the section UID and node id of the topic referenced by the specified page entry. 
			@param pageEntryUIDRef [IN] - UIDRef of the page entry.
			@param sectionUID [OUT] - the section UID of the topic
			@param nodeId [OUT] - the node id of the topic.
			@return kTrue if the topic referenced by the specified page entry was found.
		 */
		virtual bool16			FindPageEntrySectionUIDandNodeId(const UIDRef& pageEntryUIDRef, UID& sectionUID, int32& nodeId) const = 0;

		/**	Finds the topic referenced by the last node in the topic entry.
			This function is the reverse of GetTopicEntry.
			@param topicEntry [IN] - topic entry that contains the topic node we are looking for. 
			@param sectionUID [OUT] - on return will contain the section UID of the topic.
			@param nodeId [OUT] - on return will contain the node id of the topic.
			@return kTrue if the topic was found.
		 */
		virtual	bool16			FindTopicEntry(const IndexTopicEntry& topicEntry, UID* sectionUID, int32* nodeId) const = 0;


		//-------------- For Internal Use Only -------------------------

		/** Get the cached map related to page range entries data.
			@param dataMap [OUT] --- on return will contain the cached map.
		*/
		virtual void			GetIndexPageRangeDataMap(IDXPageRangeDataMap& dataMap) const = 0;

		/** Update the single entry in the cached map with the given key and value.
			@param pageRangeKey [IN] - the key of the single entry to look for in the map.
			@param pageRangeData [IN] - the value of the single entry to update.
		*/
		virtual void			UpdateIndexPageRangeDataMap(const IDXPageRangeKey& pageRangeKey, const IDXPageRangeData& pageRangeData) = 0;

		/** Set the entry in the cached map with the given key and value. The key might be changed when the entry is added into the map.
			@param pageRangeKey [IN] - the key of the single entry to be inserted in the map.
			@param pageRangeData [IN] - the value of the single entry to be inserted in the map.
		*/
		virtual void			SetIndexPageRangeData(const IDXPageRangeKey& pageRangeKey, const IDXPageRangeData& pageRangeData) = 0;

		/** Clear the cached map. 
		*/
		virtual void            ClearIndexPageRangeData() = 0;

		/**	Finds total number of topics that matches the specified string.
		@param startSectionId [IN] - section where the search should start.
		@param startNodeId [IN]- the topic node id with which the search should start.
		@param startXRefId [IN] - the start index for the search.
		@param foundSectionId [OUT] - on return will contain the section id where the topic is located.
		@param foundNodeId [OUT] - on return will contain the node id of the located topic.
		@param foundXRefId [OUT] - the result index of the found entry.
		@param caseSensitive [IN] - flag that specifies if the match is case sensitive
		@param wholeWord [IN] - flag that specifies if the match is partial or whole word.
		@param searchDir [IN] - flag that specifies the search direction. kTrue means forward/down.
		@return kTrue if the string was found.
		*/
		virtual int32			FindNumberOfStringMatchesByDisplay(const WideString& str,
			int32 startSectionId = 0,
			int32 startNodeId = 0,
			int32 startXRefId = 0,
			int32* foundSectionId = NULL,
			int32* foundNodeId = NULL,
			int32* foundXRefId = NULL,
			bool16 caseSensitive = kTrue,
			bool16 wholeWord = kTrue,
			bool16 searchDir = kTrue) const = 0;
};

#endif	// __IINDEXTOPICLIST__

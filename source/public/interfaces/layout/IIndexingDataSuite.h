//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IIndexingDataSuite.h $
//  
//  Owner: Yeming Liu
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
#ifndef __IINDEXINGDATASUITE__
#define __IINDEXINGDATASUITE__

// ----- Interface files
#include "IPMUnknown.h"
#include "IIndexPageEntryData.h"
#include "IIndexXRefEntryData.h"

// ----- Include files
#include "IndexTopicEntry.h"
#include "K2Vector.h"
#include "K2Pair.h"

// ----- ID files
#include "TextID.h"	

class WideString;
class RangeData;


// Associates a IndexTopicEntry with the position in the text
typedef K2Pair<IndexTopicEntry, TextIndex> TopicEntryInfoPair;
typedef K2Vector<TopicEntryInfoPair> TopicEntryInfoArray;

/** Defines the interface for a index data suite to be used in the new selection architecture.
	@ingroup layout_suite
	@ingroup layout_index
*/
class IIndexingDataSuite : public IPMUnknown
{
	public:
		/** kDefaultIID */
		enum { kDefaultIID = IID_IINDEXINGDATASUITE };

		// ----- Abilities

		/** Check if we can create a index based on the current selection.

			@return bool16 
			kTrue if we can, kFalse otherwise.
		*/
		virtual bool16  CanCreateIndex() = 0;

		/** Check if we can generate index story.

			@return bool16 
			kTrue if we can, kFalse otherwise.
		*/
		virtual bool16  CanGenerateIndex() = 0;

		/** Check if we can update index story. 
		    We can only update index in the following cases:
			1) In layout mode, text focus/text selection is within an index story;
			2) In layout mode, only one text frame is selected and it is an index story;
			3) In story editor mode, story is an index story.

			@return bool16 
			kTrue if we can, kFalse otherwise.
		*/
		virtual bool16  CanUpdateIndex() = 0;

		/** Get the UIDRef of the selected index story.

			@param UIDRef --- if no story is selected or selected story is not an index story, 
			                  set selectedIndexStory as UIDRef(nil, kInvalidUID); otherwise, 
							  return the selectedIndexStory
			@return void
		*/
		virtual void    GetSelectedIndexStory(UIDRef& selectedIndexStory) = 0;

		/** Get the current selection.

			@param selectedText with the selected content.
			@return void 
		*/
		virtual void	GetSelectedText(WideString& selectedText) = 0;

		/** Get index mark from the current selection.

			@param indexMarkUID with UID of index mark.
			@return void 
		*/
		virtual void    GetIndexMarkOfSelection(UID& indexMarkUID) = 0;

		// ----- Action

		/** Create a page reference index.

			@param entry describe the index entry itself.
			@param pageRangeType describes the option to create a page range in index.
			@param nextStyleUID describes the paragraph style that the page range extends from the index marker to the next change of the paragraph style.
			@param numOfParOrPage describe the number of paragraphs/pages to which the page range extends from index marker.
			@param styleUID describe the paragraph style that the page range extends from the index marker 
			 to the page where the next occurrence of the paragraph style.
			@param updateSelection is a flag determining if we need to update the selection after creating page reference.
			@param sortPRefs is a flag determining if we need to sort the page references.

			@return ErrorCode as the execution result.
		*/
		virtual ErrorCode CreatePageReference
							(
								const IndexTopicEntry &entry,
								IIndexPageEntryData::PageRangeType pageRangeType,
								UID nextStyleUID,
								int32 numOfParOrPage,
								UID styleUID,
								bool16 updateSelection = kTrue,
								bool16 sortPRefs = kTrue
							) = 0;

		/** This is another version for CreatePageReference. See CreatePageReference for the explanation 
		    of this function. Due to a bug in make_functor which fail to recognize 
			same function name with different signature, I rename the function to avoid 
			the limitation. Talked to Mat Marcus and he will fix it soon.

			@param entry describe the index entry itself.
			@param pageRangeType describes the option to create a page range in index.
			@param nextStyleUID describes the paragraph style that the page range extends from the index marker to the next change of the paragraph style.
			@param numOfParOrPage describe the number of paragraphs/pages to which the page range extends from index marker.
			@param styleUID describe the paragraph style that the page range extends from the index marker 
			 to the page where the next occurrence of the paragraph style.
			@param updateSelection is a flag determining if we need to update the selection after creating page reference.
			@param sortPRefs is a flag determining if we need to sort the page references.
		*/ 
		virtual ErrorCode CreatePageReference1	
							(
								const IndexTopicEntry &entry,
								IIndexPageEntryData::PageRangeType pageRangeType,
								UID nextStyleUID,
								int32 numOfParOrPage,
								UID styleUID,
								UIDRef textModelUIDRef,
								int32 start,
								int32 end,
								bool16 updateSelection = kTrue,
								bool16 sortPRefs = kTrue
							) = 0;


		/** Creates page references with the word(s) selected in the text.

			@param pageRangeType describes the option to create a page range in index.
			@param nextStyleUID describes the paragraph style that the page range extends from the index marker to the next change of the paragraph style.
			@param numOfParOrPage describe the number of paragraphs/pages to which the page range extends from index marker.
			@param styleUID describe the paragraph style that the page range extends from the index marker 
			 to the page where the next occurrence of the paragraph style.
			@param updateSelection is a flag determining if we need to update the selection after creating page reference.
			@param sortPRefs is a flag determining if we need to sort the page references.
			@param bReversedNames [in] - if the entries should have a <LastName, FirstName> form.

			@return ErrorCode as the execution result.
		*/
		virtual ErrorCode CreatePageReferences
							(
								IIndexPageEntryData::PageRangeType pageRangeType,
								UID nextStyleUID,
								int32 numOfParOrPage,
								UID styleUID,
								bool16 updateSelection = kTrue,
								bool16 sortPRefs = kTrue,
								bool16 reversedNames = kFalse
							) = 0;

		/** This is another version for CreatePageReference. See CreatePageReference for the explanation 
		    of this function. Due to a bug in make_functor which fail to recognize 
			same function name with different signature, I rename the function to avoid 
			the limitation. Talked to Mat Marcus and he will fix it soon.

			@param entries[in] - array of pairs IndexTopicEntry and text indexes that will be used to create the page references.
			@param pageRangeType describes the option to create a page range in index.
			@param nextStyleUID describes the paragraph style that the page range extends from the index marker to the next change of the paragraph style.
			@param numOfParOrPage describe the number of paragraphs/pages to which the page range extends from index marker.
			@param styleUID describe the paragraph style that the page range extends from the index marker 
			 to the page where the next occurrence of the paragraph style.
			@param updateSelection is a flag determining if we need to update the selection after creating page reference.
			@param sortPRefs is a flag determining if we need to sort the page references.
		*/ 
		virtual ErrorCode CreatePageReferences1	
							(
								TopicEntryInfoArray const& entries,
								IIndexPageEntryData::PageRangeType pageRangeType,
								UID nextStyleUID,
								int32 numOfParOrPage,
								UID styleUID,
								UIDRef textModelUIDRef,
								bool16 updateSelection = kTrue,
								bool16 sortPRefs = kTrue
							) = 0;


		/** Creates one or more topic entries into a topic list.

			@param topicList [in] - the topic list where the entries will be added.
			@param bReversedNames [in] - if the entries should have a <LastName, FirstName> form.

			@return ErrorCode as the execution result.
		*/
		virtual ErrorCode CreateTopicEntriesForTopicList
							(
								UIDRef topicList,
								bool16 bReversedNames
							) = 0;
};

#endif		// __IINDEXINGDATASUITE__
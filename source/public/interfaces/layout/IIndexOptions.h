//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IIndexOptions.h $
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
//  Comments: This interface saves the information about an Index instance (generated index).
//  
//========================================================================================

#pragma once
#ifndef __IINDEXOPTIONS__
#define __IINDEXOPTIONS__

#include "IPMUnknown.h"
#include "IndexingID.h"

class PMString;
class WideString;

/** Data interfaces that aggregates information regarding a generated index (an index instance).
	@ingroup layout_index
*/
class IIndexOptions : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINDEXOPTIONS };
		
		/**	Retrieves the title for the index.
			@return the title string.
		 */
		virtual const WideString&	GetTitle() const = 0;

		/**	Sets the index title.
			@param indexTitle [IN] - the index title.
		 */
		virtual void				SetTitle(const WideString& indexTitle) = 0;

		/**	Retrieves the paragraph style used for formatting the title of indexing story.
			@return the style name of the title.
		 */
		virtual const PMString&		GetTitleParagraphStyle() const = 0;

		/**	Sets the paragraph style for formatting the title of indexing story.
			@param style [IN] - the name of the paragraph style.
		 */
		virtual void				SetTitleParagraphStyle(const PMString& style) = 0;

		/**	Retrieves the "replace existing" flag option.
			@return kTrue if the flag is true (index will be replaced).
		 */
		virtual const bool16		GetReplaceExistingIndexFlag() const = 0;

		/**	Sets the "replace existing" flag option.
			@param replaceExistingIndex [IN] - the flag for replacing an existing index.
		 */
		virtual void				SetReplaceExistingIndexFlag(bool16 replaceExistingIndex = kFalse) = 0; 

		/**	Retrieves the book name to which the index belongs (if the scope is book).
			@see SetScope().
			@return the name of the book. 
		 */
		virtual const PMString&		GetBookName() const = 0;

		/**	Sets the name of the book to which the index belongs.
			@param bookName [IN] - the book name.
		 */
		virtual void				SetBookName(const PMString& bookName) = 0;

		/** Specifies if the index refers to a single document or a book. */
		typedef enum {
			kDocumentScope = 0,
			kBookScope = 1
		} Scope;

		/**	Retrieves the scope of the index.
			@return the scope of the index. 
		 */
		virtual const IIndexOptions::Scope	GetScope() const = 0;

		/**	Sets the scope of the index.
			@param scope [IN] - the scope of the index.
		 */
		virtual void				SetScope(const IIndexOptions::Scope scope = kDocumentScope) = 0;

		/**	Retrieves the flag that specifies if the topics included on hidden layers should
			be included in the index.
			@return kTrue if the entries on hidden layers are visible in the index.
		 */
		virtual const bool16		GetShowEntriesOnHiddenLayerFlag() const = 0;

		/**	Sets the flag that specifies if the topics included on hidden layers should
			be included in the index.
			@param showEntriesOnHiddenLayer [IN] - flag for the option.
		 */
		virtual void				SetShowEntriesOnHiddenLayerFlag(bool16 showEntriesOnHiddenLayer = kFalse) = 0;

		/** Specifies if the last level entries of the index are run-in or nested format */
		typedef enum {
			kNested,
			kRunIn
		} IndexFormat;

		/**	Retrieves the format for the index.
			@see IndexFormat enumeration.
			@return the format of the index. 
		 */
		virtual const IIndexOptions::IndexFormat	GetIndexFormat() const = 0;

		/**	Sets the format for the index.
			@see IndexFormat enumeration.
			@param format [IN] - the format of the index. 
		 */
		virtual void				SetIndexFormat(const IIndexOptions::IndexFormat format = kNested) = 0;

		/**	Retrieves the flag that specifies whether the section headers are included in the index.
			@return kTrue if the section headers are included in the index.
		 */
		virtual const bool16		GetShowSectionHeadersFlag() const = 0;

		/**	Sets the flag that specifies whether the section headers are included in the index.
			@param showSectionHeaders [IN] - flag value.
		 */
		virtual void				SetShowSectionHeadersFlag(bool16 showSectionHeaders = kTrue) = 0;

		/**	Retrieves the flag that specifies whether the empty section headers are included in the index.
			@return kTrue if the empty section headers are included in the index. 
		 */
		virtual const bool16		GetShowEmptySectionsFlag() const = 0;

		/**	Sets the flag that specifies whether the empty section headers are included in the index.
			@param showEmptySections [IN] - the flag value.
		 */
		virtual void				SetShowEmptySectionsFlag(bool16 showEmptySections = kFalse) = 0;

		/**	Gets the separator string that follows after each index topic.
			@return the separator. 
		 */
		virtual const WideString&	GetFollowingTopicSeparator() const = 0;

		/**	Sets the separator string that follows after each index topic.
			@param separator [IN] - the separator. 
		 */
		virtual void				SetFollowingTopicSeparator(const WideString& separator) = 0;

		/**	Gets the separator between the page numbers or page ranges.
			@return the separator. 
		 */
		virtual const WideString&	GetBetweenPageNumberSeparator() const = 0;

		/**	Sets the separator between the page numbers or page ranges.
			@param separator [IN] - the separator.
		 */
		virtual void				SetBetweenPageNumberSeparator(const WideString& separator) = 0;

		/**	Retrieves the string used between each index entry.
			@return the separator.
		 */
		virtual const WideString&	GetBetweenEntriesSeparator() const = 0;

		/**	Sets the separator used between each index entry.
			@param separator [IN] -  the separator string.
		 */
		virtual void				SetBetweenEntriesSeparator(const WideString& separator) = 0;

		/**	Retrieves the separator used before each cross-reference.
			@return the separator.
		 */
		virtual const WideString&	GetBeforeXRefSeparator() const = 0;

		/**	Sets the separator used before each cross-reference.
			@param separator [IN] -  the separator string.
		 */
		virtual void				SetBeforeXRefSeparator(const WideString& separator) = 0;

		/**	Retrieves the separator between the page ranges.
			@return the separator.
		 */
		virtual const WideString&	GetPageRangeSeparator() const = 0;

		/**	Sets the separator between the page ranges.
			@param separator [IN] - the separator string.
		 */
		virtual void				SetPageRangeSeparator(const WideString& separator) = 0;

		/**	Retrieves the separator at the end of each index entry.
			@return the separator.
		 */
		virtual const WideString&	GetEntryEndSeparator() const = 0;

		/**	Sets the separator used at the end of each index entry.
			@param separator [IN] -  the separator string.
		 */
		virtual void				SetEntryEndSeparator(const WideString& separator) = 0;

		/**	Retrieves the paragraph style used for formatting the topics in the index story.
			@param level [IN] - level of the topic.
			@param style [OUT] - style name for the specified level.
		 */
		virtual void				GetTopicLevelParagraphStyle(const int32 level, PMString& style) const = 0;

		/**	Sets the paragraph style used for formatting the topics in the index story.
			@param level [IN] - level of the topic.
			@param style [IN] - style name for the specified level.
		 */
		virtual void				SetTopicLevelParagraphStyle(const int32 level, const PMString& style) = 0;

		/**	Retrieves the paragraph style used for formatting the section headers in the index story.
			@return the style name for the section headers.
		 */
		virtual const PMString&		GetSectionHeaderParagraphStyle() const = 0;

		/**	Sets the paragraph style used for formatting the section headers in the index story.
			@param style [IN] - the style name for the section headers.
		 */
		virtual void				SetSectionHeaderParagraphStyle(const PMString& style) = 0;

		/**	Retrieves the paragraph style used for formatting the page numbers in the index story.
			@return the style name for the page numbers.
		 */
		virtual const PMString&		GetPageNumberCharacterStyle() const = 0;

		/**	Sets the paragraph style used for formatting the page numbers in the index story.
			@param style [IN] - the style name for the page numbers.
		 */
		virtual void				SetPageNumberCharacterStyle(const PMString& style) = 0;

		/**	Retrieves the paragraph style used for formatting the
			cross-reference specifiers ("see, see also", etc) in the index story.
			@return the style name for the cross-reference specifiers.
		 */
		virtual const PMString&		GetCrossRefCharacterStyle() const = 0;

		/**	Sets the paragraph style used for formatting the
			cross-reference specifiers ("see, see also", etc) in the index story.
			@param style [IN] - the style name for the cross-reference specifiers.
		 */
		virtual void				SetCrossRefCharacterStyle(const PMString& style) = 0;

		/**	Retrieves the paragraph style used for formatting the
			cross-reference index entries in the index story.
			@return the style name for the cross-references.
		 */
		virtual const PMString&		GetReferencedCharacterStyle() const = 0;

		/**	Sets the paragraph style used for formatting the
			cross-reference index entries in the index story.
			@param style [IN] - the style name for the cross-references.
		 */
		virtual void				SetReferencedCharacterStyle(const PMString& style) = 0;

		/** Specifies the direction of frame for the index story. */
		typedef enum {
			kHorizontal,
			kVertical
		} FrameType;

		/**	Retrieves the direction of the frame for the index story.
			Used for the J version.
			@return the direction of the frame.
		 */
		virtual const IIndexOptions::FrameType GetFrameType() const = 0;

		/**	Sets the direction of the frame for the index story.
			Used for the J version. The Roman version used the default value (kHorizontal).
			@param frameType [IN] - the direction of the frame.
		 */
		virtual void				SetFrameType(const IIndexOptions::FrameType frameType = kHorizontal) = 0;

		/**	Utility function that copied the index options from another interface.
			@param source [IN] - source index options that will be copied in this instance.
			@param bDirty [IN] - flag that specifies if the data will be marked as "dirty",
			causing the observers to be notified.
		 */
		virtual void				CopyDataFrom(const IIndexOptions* source, bool16 bDirty = kTrue) = 0;
};

#endif // __IINDEXOPTIONS__
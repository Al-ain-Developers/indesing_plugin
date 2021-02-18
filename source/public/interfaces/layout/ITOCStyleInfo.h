//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ITOCStyleInfo.h $
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
//  
//  Comments: This interface saves the information about TOC style.
//  
//========================================================================================

#pragma once
#ifndef __ITOCSTYLEINFO__
#define __ITOCSTYLEINFO__

#include "IPMUnknown.h"
#include "K2Vector.h"
#include "KeyValuePair.h"
#include "TOCID.h"

class TOCFormatEntryInfo;
class PMString;

typedef K2Vector<KeyValuePair<PMString, TOCFormatEntryInfo> >  FormatEntriesInfo;

/** Data interface for the non-attribute parts of a table of content style. 
    It is necessary for anything listed by an ITOCStyleNameTable.
	This interface may be part of the style itself, or part of a command that operates on styles.
	@see ITOCStyleNameTable
*/
class ITOCStyleInfo : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITOCSTYLEINFO };
		
		/** Enum value about story direction for generated table of content story.
		*/
		typedef enum {
			kHorizontal,	// horizontal
			kVertical		// vertical
		} TOCStoryDirection;

		/** Enum value about the type of entries to be generated for numbered paragraphs.
		*/
		typedef enum {
			/**	kIncludeFullParagraph : Include the numbering and the paragraph text.
			*/
			kIncludeFullParagraph,
			/** kIncludeNumbersOnly : Include the numbers only.
			*/
			kIncludeNumbersOnly,
			/** kExcludeNumbers : Include the paragraph text only and exclude the numbers.
			*/
			kExcludeNumbers
		} TOCNumberedParagraphsEntriesType;

		/**	Get the name of this style.
			@param none
			@return const PMString& the name of the style.
		*/
		virtual const PMString& GetName() const = 0;		

		/**	Set the name of this style.
			@param s IN the style name to be set.
			@param translatable IN flag indicates if style name should be translated or not. 
			       It would always be kFalse for user-specified names and kTrue for predefined style.
		*/
		virtual void SetName(const PMString& s, bool16 translatable = kFalse) = 0;

		/**	Get the map of included paragraph style and its format information of this style. 
		    The key is original paragraph style name and the value is the corresponding format 
			information. 
			@see TOCFormatEntryInfo.
			@param none
			@return const FormatEntriesInfo& a list of included style and its format information.
		*/
		virtual const FormatEntriesInfo& GetTOCEntryMap() const = 0;	

		/**	Set the included style and its corresponding format information into the style.
			@param tocEntryMap IN the new map.
		*/
		virtual void SetTOCEntryMap(const FormatEntriesInfo& tocEntryMap) = 0;

		/**	Get the flag about include hidder layer or not when generate table of content(TOC).
			@param none
			@return bool16 kTrue means include hidder layer, otherwise kFalse.
		*/
		virtual const bool16 GetIncludeHidderLayerFlag() const = 0;

		/**	Set the flag about include hidder layer.
			@param includeHidderLayer IN the boolean flag to be set.
		*/
		virtual void SetIncludeHidderLayerFlag(bool16 includeHidderLayer = kFalse) = 0;

		/**	Get the flag about include all the documents in the book or not when generate table of content(TOC).
			@param none
			@return bool16 kTrue menas include all the documents in the book, otherwise kFalse.
		*/
		virtual const bool16 GetIncludeBookPubs() const = 0;

		/**	Set the flag about include all the documents in the book or not.
			@param includeBookPubs IN the boolean flag to be set.
		*/
		virtual void SetIncludeBookPubs(const bool16 includeBookPubs = kFalse) = 0;

		/**	Get the flag about if we should honor run-in. 
			@param none
			@return bool16 kTrue means do honor run-in, otherwise kFalse.
		*/
		virtual const bool16 GetRunInFlag() const = 0;

		/**	Get the flag about run-in. 
			@param runIn IN the boolean flag to be set.
		*/
		virtual void SetRunInFlag(bool16 runIn = kFalse) = 0;

		/**	Get the format style for table of content's title.
			@param none
			@return const UID IN the format style.
		*/
		virtual const UID GetTOCTitleFormatStyle() const = 0;

		/**	Set the format style for table of content's title.
			@param formatStyle IN the style used to format the table of content's title.
		*/
		virtual void SetTOCTitleFormatStyle(const UID formatStyle) = 0;

		/**	Get the title for table of content story.
			@param none
			@return const PMString& IN the title for table of content story.
		*/
		virtual const PMString& GetTOCTitle() const = 0;

		/**	Set the title for table of content story.
			@param tocTitle IN the title to be set as table of content story.
		*/
		virtual void SetTOCTitle(const PMString& tocTitle) = 0;

		/**	Get the book name if we want to include all the documents in book when generate table of content.
			@param none
			@return const PMString& the name of the book.
		*/
		virtual const PMString& GetBookName() const = 0;

		/**	Set the book name.
			@param bookName IN the name to be set for book. 
		*/
		virtual void SetBookName(const PMString& bookName) = 0;

		/**	Get the flag about whether to include bookmarks or not when generate table of content.
			@param none
			@return bool16 kTrue means we do include bookmarks, otherwise kFalse.
		*/
		virtual const bool16 GetIncludeBookmarks() const = 0;

		/**	Set the flag about whether to include bookmarks or not.
			@param bIncludeBookmarks IN the boolean flag to be set.
		*/
		virtual void SetIncludeBookmarks(const bool16 bIncludeBookmarks = kFalse) = 0;

		/** Get the story direction for the generated table of content story.
			@param none
			@return ITOCStyleInfo::TOCStoryDirection the story direction. 
		*/
        virtual const ITOCStyleInfo::TOCStoryDirection GetStoryDirection() const = 0;

		/**	Set the story direction for the generated table of content story.
			@param storyDirection IN the story direction to be set. 
		*/
        virtual void  SetStoryDirection(const ITOCStyleInfo::TOCStoryDirection storyDirection = ITOCStyleInfo::kHorizontal) = 0;

		/**	Get the type of entries for Numbered Paragraphs to be generated.
			@param none
			@return ITOCStyleInfo::TOCNumberedParagraphsEntriesType the type of entry to be generated for numbered paragraphs.
		*/
		virtual const ITOCStyleInfo::TOCNumberedParagraphsEntriesType GetNumberedParagraphsEntriesType() const = 0;

		/**	Set the type of entries for Numbered Paragraphs to be generated.
			@param numberedParagraphsEntriesType IN the type of entries to be generated for numbered paragraphs. 
		*/
		virtual void  SetNumberedParagraphsEntriesType(const ITOCStyleInfo::TOCNumberedParagraphsEntriesType numberedParagraphsEntriesType = ITOCStyleInfo::kIncludeFullParagraph) = 0;

		/**	Get the create text anchor flag.
			@return bool16 kTrue create text anchor at source paragraph, otherwise kFalse.
		*/
		virtual const bool16 GetCreateTextAnchor() const = 0;

		/**	Set the flag which inserts text anchor at source paragraph location. This is for html/epub export.
			@param insertTextAnchor IN the boolean flag to be set.
		*/
		virtual void SetCreateTextAnchor(bool16 insertTextAnchor) = 0;

		/**	Get the remove line feed flag.
		@return bool16 kTrue remove line feed at source paragraph, otherwise kFalse.
		*/
		virtual const bool16 GetRemoveForcedLineBreak() const = 0;

		/**	Set the flag which removes line feed at source paragraph location.
		@param removeForcedLineBreak IN the boolean flag to be set.
		*/
		virtual void SetRemoveForcedLineBreak(bool16 removeForcedLineBreak) = 0;
};

#endif // __ITOCSTYLEINFO__

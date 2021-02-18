//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ITOCCmdData.h $
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
//  Purpose: This is generic interface for creating and generating TOC.
//  
//========================================================================================

#pragma once
#ifndef __ITOCCMDDATA__
#define __ITOCCMDDATA__

#include "IPMUnknown.h"

#include "ITOCStyleInfo.h"

#include "TOCID.h"

class TOCEntryInfo;

/** This interface is used for accessing command data for creating/editing 
    table of content(TOC) style or table of content story. Some functions 
	are only used for CreateTOCCmd, some functions are only used for FormatTOCCmd, 
	some functions are used as a bridge for CreateTOCCmd and FormatTOCCmd and some 
	functions are used for commands related to table of content styles.
	@see kCreateTOCCmdBoss, kFormatTOCCmdBoss, kCreateTOCStyleCmdBoss and kEditTOCStyleCmdBoss.
*/
class ITOCCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITOCCMDDATA };

		/** Enum values for page number position.
			kAfterEntry means displaying page number after page entry.
			kBeforeEntry means displaying page number before page entry.
			kNotIncluded means don't displaying page number.
		*/
		typedef enum {kAfterEntry, kBeforeEntry, kNotIncluded} PageNumPosition;

		/**	Get the boolean data for hidder layer to determine if we should include 
		    hidder layer when collecting table of content entries. 
			This is used for CreateTOCCmd.
			@param none
			@return const bool16 the boolean flag.
		*/
		virtual const bool16 GetIncludeHidderLayerFlag() const = 0;

		/**	Get the boolean data about replacing existing table of content story.
		    This is used for CreateTOCCmd.
			@param none
			@return const bool16 the boolean flag.
		*/
		virtual const bool16 GetReplaceExistingTOCFlag() const = 0;

		/**	Get the boolean data determiningif we should include all the documents in book 
		    when collecting table of content entries.
			This is used for CreateTOCCmd.
			@param none
			@return const bool16 the boolean flag.
		*/
		virtual const bool16 GetIncludeBookPubs() const = 0;

		/**	Get the boolean data of runin to determine if we should display the table of content 
		    entries as runin. 
			This is used for CreateTOCCmd.
			@param none
			@return const bool16 the boolean flag.
		*/
		virtual const bool16 GetRunInFlag() const = 0;		

		/**	Set the include hidden layer flag.
		    This is used for CreateTOCCmd.
			@param includeHidderLayer IN the boolean data to be set. By default, it sets as kFalse.
		*/
		virtual void SetIncludeHidderLayerFlag(const bool16 includeHidderLayer = kFalse) = 0;

		/**	Set the replace existing table of content story flag.
			This is used for CreateTOCCmd.
			@param replaceExistingTOC IN the boolean data to be set. By default, it sets as kFalse.
		*/
		virtual void SetReplaceExistingTOCFlag(const bool16 replaceExistingTOC = kFalse) = 0;

		/**	Set the include documents in book flag.
			This is used for CreateTOCCmd.
			@param includeBookPubs IN the boolean data to be set. By default, it sets as kFalse.
		*/
		virtual void SetIncludeBookPubs(const bool16 includeBookPubs = kFalse) = 0;

		/**	Set the runin flag.
			This is used for CreateTOCCmd.
			@param runIn IN the boolean data to be set. By default, it sets as kFalse.
		*/
		virtual void SetRunInFlag(const bool16 runIn = kFalse) = 0;

		/**	Get the book name which is valid when includeBookPubs flag is set as kTrue.
			This is used for CreateTOCCmd.
			@param none
			@return const PMString& the book name.
		*/
		virtual const PMString& GetBookName() const = 0;

		/**	Set the book name which needs to be set only when includeBookPubs flag is set as kTrue. 
			This is used for CreateTOCCmd.
			@param bookName IN the name to be set for book.
		*/
		virtual void SetBookName(const PMString& bookName) = 0;

		/**	Get the include overset flag to determine if we should include table of content 
		    entries in overset. In fact, the include overset flag is set in runtime through 
			user's input(a warning dialog). Currently, the function is only used for scripting 
			to control the default behavior if we should include overset or not. 
			This is used for CreateTOCCmd.
			@param none
			@return const bool16& the boolean flag.
		*/
		virtual const bool16 GetIncludeOversetFlag() const = 0;

		/**	Set the include overset flag.
			This is used for CreateTOCCmd.
			@param includeOverset IN the boolean flag to be set.
		*/
		virtual void SetIncludeOversetFlag(bool16 includeOverset) = 0;

		/**	Set the format map for original style name and its corresponding format information. 
		    The style map is set before processing CreateTOCCmd and get before processing FormatTOCCmd.
		    The format information includes(format style for included paragraph style, 
			indent level, page number position, page number format style, separator for 
			entry and page number, separator's format style.
		    @see TOCFormatEntryInfo.
			This is used for FormatTOCCmd.
			@param formatStyleMap IN the format information map.
		*/
		virtual void SetFormatEntryMap(const FormatEntriesInfo& formatStyleMap) = 0;

		/**	Get the format map.
			This is used for FormatTOCCmd.
			@param none
			@return const FormatEntriesInfo& the format information map.
		*/
		virtual const FormatEntriesInfo& GetFormatEntryMap() const = 0;	

		/**	Get the include bookmark flag to determine if we should include bookmark information 
		    when generating table of content. Those bookmarks can be seen through bookmark panel.
			This is used for FormatTOCCmd.
			@param none
			@return const bool16 the boolean flag.
		*/
		virtual const bool16 GetIncludeBookmarks() const = 0;

		/**	Set the include bookmark flag.
			This is used for FormatTOCCmd.
			@param bIncludeBookmarks IN the boolean flag to be set.
		*/
		virtual void SetIncludeBookmarks(const bool16 bIncludeBookmarks = kFalse) = 0;

		/**	Get the UIDRef of a target(document or document/session workspace) 
		    where the table of content story will be placed on.
			@param none
			@return const UIDRef& UIDRef of target.
		*/
		virtual const UIDRef& GetTargetItem() const = 0;

		/**	Set the UIDRef of a target(document or document/session workspace).
			@param sourceItem the target to be set.
		*/
		virtual void SetTargetItem(const UIDRef& sourceItem) = 0;

		/**	Get the string for table of content story's title.
			@param none
			@return const PMString the title string.
		*/
		virtual const PMString GetTOCTitle() const = 0;

		/**	Set the string for table of content story's title.
			@param tocTitle IN the title string to be set.
		*/
		virtual void SetTOCTitle(const PMString& tocTitle) = 0;

		/**	Get the format style(paragraph style) for table of content story's title.
			@param none
			@return const UID the UID of a paragraph style.
		*/
		virtual const UID GetTOCTitleFormatStyle() const = 0;

		/**	Set the format style for table of content story's title.
			@param formatStyle IN the UID of a paragraph style to be set as title's format style.
		*/
		virtual void SetTOCTitleFormatStyle(const UID formatStyle) = 0;

		/**	Get the UIDRef of a story in which the table of content will be stored in.
			@param none
			@return const UIDRef& the UIDRef of a story.
		*/
		virtual const UIDRef& GetTextModelUIDRef() const = 0;

		/**	Set the UIDRef of a story to be the table of content story. By default, 
		    it is UIDRef(nil, kInvalidUID) which means that we need to create a new story 
			to hold the table of content. If we pass in a valid UIDRef, it means  
			the passed in story will be the table of content story.
			@param textModelUIDRef IN the story to be set.
		*/
		virtual void SetTextModelUIDRef(const UIDRef& textModelUIDRef = UIDRef(nil, kInvalidUID)) = 0;

		/**	Set the list of table of content entries and each entry contains information about 
		    original included paragraph style name, page number and format style. 
			We set this information in CreateTOCCmd.
		    @see TOCEntryInfo
			@param tocEntryInfoList IN the list to be set.
		*/
		virtual void SetTOCEntryInfoList(const K2Vector<TOCEntryInfo>& tocEntryInfoList) = 0;

		/**	Get the list of table of content entries which includes information about original 
		    included paragraph style name, page number and format style. We then use the original 
			style name to find all the format information through format entry map. 
			This is used in FormatTOCCmd. 
			@param none
			@return const K2Vector<TOCEntryInfo>& the table of content entry information list.
		*/
		virtual const K2Vector<TOCEntryInfo>& GetTOCEntryInfoList() const = 0;

		/**	Get the direction for the table of content(TOC) story to be generated.
			@param none
			@return ITOCStyleInfo::TOCStoryDirection the story direction.
		*/
		virtual const ITOCStyleInfo::TOCStoryDirection GetStoryDirection() const = 0;

		/**	Set the direction for the table of content(TOC) story to be generated.
			@param storyDirection IN the direction to be set. 
		*/
		virtual void  SetStoryDirection(const ITOCStyleInfo::TOCStoryDirection storyDirection = ITOCStyleInfo::kHorizontal) = 0;

		/**	Get the type of entries to be generated for numbered paragraphs.
			@param none
			@return ITOCStyleInfo::TOCNumberedParagraphsEntriesType the type of entry tobe generated for Numbered Paragraphs.
		*/
		virtual const ITOCStyleInfo::TOCNumberedParagraphsEntriesType GetNumberedParagraphsEntriesType() const = 0;

		/**	Set the type of entries to be generated for numbered paragraphs.
			@param numberedParagraphsEntriesType IN the type of entries to be generated for numbered paragraphs. 
		*/
		virtual void  SetNumberedParagraphsEntriesType(const ITOCStyleInfo::TOCNumberedParagraphsEntriesType numberedParagraphsEntriesType = ITOCStyleInfo::kIncludeFullParagraph) = 0;

		/**	Get the name of table of content(TOC) style. 
		    This is used for creating/editing table of content(TOC) style command.
			@param none
			@return const PMString& the name of the style.
		*/
		virtual const PMString& GetTOCStyleName() const = 0;

		/**	Set the name of table of content(TOC) style.
		    This is used for creating/editing table of content(TOC) style command.
			@param styleName IN the style name to be set.
		*/
		virtual void SetTOCStyleName(const PMString& styleName) = 0;

		/**	Get the create text anchor flag.
		@return bool16 kTrue create text anchor at source paragraph, otherwise kFalse.
		*/
		virtual const bool16 GetCreateTextAnchor() const = 0;

		/**	Set the flag which inserts text anchor at source paragraph location. This is for html/epub export.
		@param createAnchor IN the boolean flag to be set.
		*/
		virtual void SetCreateTextAnchor(bool16 createAnchor) = 0;

		/**	Get the remove line feed flag.
		@return bool16 kTrue remove line feed at source paragraph, otherwise kFalse.
		*/
		virtual const bool16 GetRemoveForcedLineBreak() const = 0;

		/**	Set the flag which removes line feed at source paragraph location.
		@param removeForcedLineBreak IN the boolean flag to be set.
		*/
		virtual void SetRemoveForcedLineBreak(bool16 removeForcedLineBreak) = 0;
};

#endif	// __ITOCCMDDATA__

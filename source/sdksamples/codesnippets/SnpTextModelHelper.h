//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpTextModelHelper.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __SnpTextModelHelper_H_DEFINED__
#define __SnpTextModelHelper_H_DEFINED__

#include "TextRange.h"

/** 
	\li Provide helper method to insert, replace, delete text in a story using ITextModelCmds.
	\li Provide helper method to apply/clear text attributes overrides using ITextModelCmds.
	\li Provide helper method to copy text from one story to another using kCopyStoryRangeCmdBoss.
	\li Provide helper method to detect if a story or parcel is overset.
	\li Provide helper method to determine that parcel that displays a given TextIndex.
	\li Provide helper method to determine the range of characters
		displayed by a parcel.

  	@ingroup sdk_snippet
	@ingroup sdk_text

	@see ITextModel
	@see ITextModelCmds
	@see IParcel
	@see IParcelList
	@see ITextParcelList
	@see ITextParcelListComposer
*/
class SnpTextModelHelper
{
	public:
		/** Constructor.
		*/
		SnpTextModelHelper();

		/** Destructor
		*/
		virtual ~SnpTextModelHelper();

		/**	Insert text into a story using ITextModelCmds::InsertCmd.
			@param textModel of story to be changed.
			@param position index at which insertion to be made.
			@param text to be inserted.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode	InsertText(ITextModel* textModel, const TextIndex position, const boost::shared_ptr<WideString>& text);

		/**	Delete text from a story using ITextModelCmds::DeleteCmd.
			@param textModel of story to be changed.
			@param position index first character to be deleted.
			@param length number of characters to be deleted.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode	DeleteText(ITextModel* textModel, const TextIndex position, const int32 length);

		/**	Replace text in a story using ITextModelCmds::ReplaceCmd.
			@param textModel of story to be changed.
			@param position index first character to be replaced.
			@param length number of characters to be replaced.
			@param text text to replace.
			@return kSuccess on success, other ErrorCode otherwise. 
		 */
		ErrorCode	ReplaceText(ITextModel* textModel, const TextIndex position, const int32 length, const boost::shared_ptr<WideString>& text);

		/**	Apply paragraph alignment, the point size,
			leading and underline overrides using ITextModelCmds::ApplyCmd.
			@param textModel of story to be changed.
			@param position index of first character to be formatted.
			@param length number of characters to be formatted.
			@param attr attribute boss lists that contains the point size, leading and underline overrides we want to apply here.
			@param whichStrand which strand this attribute overrides are to apply, it has to be either kParaAttrStrandBoss or kCharAttrStrandBoss.
			@return kSuccess on success, other ErrorCode otherwise. 
		 */
		ErrorCode	ApplyOverrides(ITextModel* textModel, const TextIndex position, const int32 length, const boost::shared_ptr<AttributeBossList>& attr, ClassID whichStrand);

		/**	Clear paragraph alignment, character point size,
			leading and underline overrides using ITextModelCmds::ApplyCmd.
			@param textModel of story to be changed.
			@param position index of first character to be formatted.
			@param length number of characters to be formatted.
			@param attr attribute boss lists that contains the point size, leading and underline overrides we want to clear here.
			@param whichStrand which strand this attribute overrides are to apply, it has to be either kParaAttrStrandBoss or kCharAttrStrandBoss.
			@return kSuccess on success, other ErrorCode otherwise. 
		 */
		ErrorCode	ClearOverrides(ITextModel* textModel, const TextIndex position, const int32 length, const boost::shared_ptr<AttributeBossList>& attr, ClassID whichStrand);

		/** Process kCopyStoryRangeCmdBoss to copy a given range of text from the
			source story to the destination story. By specifying a destLength
			> 0 the text copied from the source story can replace text in the
			destination story. The sourceStory and destStory UIDRefs can refer
			to the same story if text is to be copied around inside a story
			or they can refer to different stories in the same document or
			to stories in different documents.
			@param sourceStory UIDRef of story from which to copy content
			@param sourceStart index of text to be copied
			@param sourceLength amount of text to be copied
			@param destStory UIDRef of story to which content is to be copied
			@param destStart index where text to be copied
			@param destLength 0 to insert text in destination story, >0 to replace
			@precondition 0 <= sourceStart < ITextModel::GetPrimaryStoryThreadSpan() for sourceStory
			@precondition 1 <= sourceLength <= ITextModel::GetPrimaryStoryThreadSpan() for sourceStory
			@precondition 0 <= destStart < ITextModel::GetPrimaryStoryThreadSpan() for destStory
			@precondition 0 <= destLength <= ITextModel::GetPrimaryStoryThreadSpan() for destStory
			@return kSuccess on success, some other ErrorCode otherwise.
			@see kCopyStoryRangeCmdBoss
			@see ITextUtils for wrapper methods.
		*/
		ErrorCode ProcessCopyStoryRangeCmd
		(
			const UIDRef& sourceStory, 
			TextIndex sourceStart, 
			int32 sourceLength, 
			const UIDRef& destStory,
			TextIndex destStart, 
			int32 destLength
		);
		/** Detect if the text in a story is overset via ITextUtils::IsOverset.

			@param textModel for story to be tested.
			@return kTrue if overset, kFalse otherwise.
			@see ITextUtils::IsOverset
		*/
		bool16		IsStoryOverset(InterfacePtr<ITextModel> textModel);

		/** Detect if a text frame is overset.
			When a frame is not large enough to show all of the remaining characters 
			of the the story it displays it is considered by this method as overset.
		*/
		bool16		IsTextFrameOverset(const InterfacePtr<ITextFrameColumn> textFrameColumn);

		/** Detect if a parcel is overset.
		*/
		bool16		IsParcelOverset(const InterfacePtr<IParcel> parcel);

		/** Return interface pointer to parcel that displays the given
				TextIndex or nil if the TextIndex is not displayed.
			@param textModel
			@param at
			@return interface pointer to parcel that displays the given
				TextIndex or nil if the TextIndex is not displayed. 
		*/
		IParcel*	QueryParcelContaining(ITextModel* textModel, const TextIndex at);

		/** Return the range of text displayed by the given parcel.
			@param parcel
			@return the range of text displayed by the given parcel.
		*/
		InDesign::TextRange	GetParcelTextRange(IParcel* parcel);

		/** Return string containing the given range of text from the text model. 
			@param range specifies the text model and range of characters wanted.
			@return string containing the given range of text from the text model. 
		*/
		WideString	GetWideStringFromTextRange(const InDesign::TextRange& range);

		/** Return string containing the text displayed in the given parcel. 
			@param parcel specifies the object whose text is wanted.
			@return string containing the text displayed in the given parcel. 
		*/
		WideString	GetWideStringFromParcel(IParcel* parcel);
};

#endif //  __SnpTextModelHelper_H_DEFINED__

//End, SnpTextModelHelper.h

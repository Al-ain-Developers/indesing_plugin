//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateTextModel.cpp $
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "ITextModel.h"
#include "ITextFocus.h"
#include "ITextModelCmds.h"
#include "ITextAttrAlign.h"
#include "ITextAttrRealNumber.h"
#include "ITextAttrUnderlineMode.h"
#include "IAttrReport.h"
#include "IComposeScanner.h"
#include "ITextFrameColumn.h"
#include "IFrameList.h"
#include "ISelectionManager.h"
#include "ITextTarget.h"
#include "ITextSelectionSuite.h"
#include "ITool.h"
#include "IToolBoxUtils.h"
#include "ICommand.h"
#include "ITextStoryThreadDictHier.h"
#include "ITextStoryThreadDict.h"
#include "ITableModel.h"
#include "ITextUtils.h"
#include "IHierarchy.h"
#include "IGeometry.h"
#include "IParcelList.h"
#include "IParcel.h"
#include "ITextParcelList.h"
#include "ITextParcelListComposer.h"

// General includes:
#include "Utils.h"
#include "CreateObject.h"
#include "TextEditorID.h"
#include "CmdUtils.h"
#include "UIDList.h"
#include "RangeData.h"
#include "Utils.h"
#include "TransformUtils.h"

// SDK includes:
#include "SDKLayoutHelper.h"
#include "SnpTextModelHelper.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"
#include "SnpTextAttrHelper.h"

/** 
	\li How to insert, replace, delete and style text in a story using ITextModelCmds.
	\li how to copy text, tables and inline graphics from one story to another using kCopyStoryRangeCmdBoss.
	
	The following 2.x code snippets have been consolidated into this snippet:
	\li SnipCopyStory.cpp
	\li SnipTextModel.cpp

  	@ingroup sdk_snippet
  	@ingroup sdk_text

	@see ITextModel
	@see ITextModelCmds
	@see kCopyStoryRangeCmdBoss
	@see ITextUtils
 */
class SnpManipulateTextModel 
{
public:
	/** Constructor.
		*/
	SnpManipulateTextModel() {}

	/** Destructor.
		*/
	virtual			~SnpManipulateTextModel() {}

	/**	Insert text into a story using SnpTextModelHelper::InsertCmd.
		@param textModel of story to be changed.
		@param position index at which insertion to be made.
		@param text to be inserted.
		@return kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode	InsertText(ITextModel* textModel, const TextIndex position, const WideString& text);

	/**	Delete text from a story using SnpTextModelHelper::DeleteCmd.
		@param textModel of story to be changed.
		@param position index first character to be deleted.
		@param length number of characters to be deleted.
		@return kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode	DeleteText(ITextModel* textModel, const TextIndex position, const int32 length);

	/**	Replace text in a story using SnpTextModelHelper::ReplaceCmd.
		@param textModel of story to be changed.
		@param position index first character to be replaced.
		@param length number of characters to be replaced.
		@param data text to be inserted.
		@return kSuccess on success, other ErrorCode otherwise. 
		*/
	ErrorCode	ReplaceText(ITextModel* textModel, const TextIndex position, const int32 length, const WideString& data);

	/**	Apply paragraph alignment, the point size,
		leading and underline overrides using ITextModelCmds::ApplyCmd.
		@param textModel of story to be changed.
		@param position index of first character to be formatted.
		@param length number of characters to be formatted.
		@return kSuccess on success, other ErrorCode otherwise. 
		*/
	ErrorCode	ApplyOverrides(ITextModel* textModel, const TextIndex position, const int32 length);

	/**	Clear paragraph alignment, character point size,
		leading and underline overrides using ITextModelCmds::ApplyCmd.
		@param textModel of story to be changed.
		@param position index of first character to be formatted.
		@param length number of characters to be formatted.
		@return kSuccess on success, other ErrorCode otherwise. 
		*/
	ErrorCode	ClearOverrides(ITextModel* textModel, const TextIndex position, const int32 length);

	/**	Return text focus describing the range of characters
		displayed in the given frame.
		@param textFrameColumn 
		@return text focus describing the range of characters displayed in the frame.
		*/
	ITextFocus*	QueryTextFocus(ITextFrameColumn* textFrameColumn);

	/**	Return text focus describing the whole range of characters in a parcel which contains the start of a text range
		@param textModel that contains the text focus
		@param range is the selected text range, the start of the range will be used to determined which parcel will be the focus frame/parcel
		@return text focus describing the range of characters displayed in the parcel.
		*/
	ITextFocus* QueryParcelTextFocus(ITextModel* textModel, const RangeData range);
	
	/** Set a text selection.
		@param selectionManager in which items are to be selected.
		@param textFocus describing the text to be selected.
		@return kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode	SelectText(ISelectionManager* selectionManager, ITextFocus* textFocus);
	

	/** Call SnpTextModelHelper::ProcessCopyStoryRangeCmd to copy a given range of text from the
		source story to the destination story. 
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
	
	/** Copy all of the source story content to the destination story.
		@param sourceStory UIDRef of story from which to copy content.
		@param destStory UIDRef of story to which content is to be copied.
		@return kSuccess on success, some other ErrorCode otherwise.
	*/
	ErrorCode CopyAll(const UIDRef& sourceStory, const UIDRef& destStory);
	
	/** Copy each inline graphic in the source story to the destination story.
		@param sourceStory UIDRef of story from which to copy content.
		@param destStory UIDRef of story to which content is to be copied.
		@return kSuccess on success, some other ErrorCode otherwise.
	*/
	ErrorCode CopyInlines(const UIDRef& sourceStory, const UIDRef& destStory);

	/** Copy each table in the source story to the destination story.
		@param sourceStory UIDRef of story from which to copy content.
		@param destStory UIDRef of story to which content is to be copied.
		@return kSuccess on success, some other ErrorCode otherwise.
	*/
	ErrorCode CopyTables(const UIDRef& sourceStory, const UIDRef& destStory);


	
	/** Create a text frame alongside the given frame.
		@param fromGraphicFrameUIDRef IN references the spline the frame is to be created alongside.
		@param storyUIDRef OUT the story associated with the newly created text frame.
		@return reference to the new text frame's kSplineItemBoss object on success, UIDRef::gNull otherwise.
	*/
	UIDRef		CreateTextFrame(const UIDRef& fromGraphicFrameUIDRef, UIDRef& storyUIDRef);
	
	/**
		Collects and copies owned items.
		@param sourceStory UIDRef of story from which to copy content.
		@param destStory UIDRef of story to which content is to be copied.
		@param ownedItemType kInlineBoss for inlines
		@return kSuccess on success, some other ErrorCode otherwise.
	*/
	ErrorCode CopyOwnedItem(const UIDRef& sourceStory, const UIDRef& destStory, const ClassID& ownedItemType);	


};


/*
*/
ErrorCode SnpManipulateTextModel::InsertText(ITextModel* textModel, const TextIndex position, const WideString& data)
{
	boost::shared_ptr<WideString>	wide(new WideString(data));
	SnpTextModelHelper	textCmdHelper;
	return textCmdHelper.InsertText(textModel, position, wide);
}

/*
*/
ErrorCode SnpManipulateTextModel::DeleteText(ITextModel* textModel, const TextIndex position, const int32 length)
{
	SnpTextModelHelper	textCmdHelper;
	return textCmdHelper.DeleteText(textModel, position, length);
}

/*
*/
ErrorCode SnpManipulateTextModel::ReplaceText(ITextModel* textModel, const TextIndex position, const int32 length, const WideString& data)
{
	boost::shared_ptr<WideString>	wide(new WideString(data));
	SnpTextModelHelper	textCmdHelper;
	return textCmdHelper.ReplaceText(textModel, position, length, wide);
}

/*
*/
ErrorCode SnpManipulateTextModel::ApplyOverrides(ITextModel* textModel, const TextIndex position, const int32 length)
{
	ErrorCode status = kFailure;

	do {
		// Wrap the changes to be made in a command sequence.
		CmdUtils::SequenceContext seq;

		// First set the paragraph alignment.

		// Create a container for the paragraph attribute to be applied.
		boost::shared_ptr<AttributeBossList> paraAttributeBossList (new AttributeBossList());
		ASSERT(paraAttributeBossList);
		if (!paraAttributeBossList) {
			break;
		}

		// Create an alignment attribute.
		InterfacePtr<IAttrReport> textAttrAlign(SnpTextAttrHelper::CreateTextAttribute<ITextAttrAlign, ITextAttrAlign::ValueType>(kTextAttrAlignmentBoss, ICompositionStyle::kTextAlignCenter));
		ASSERT(textAttrAlign != nil);
		if(textAttrAlign==nil) {
			break;
		}
		paraAttributeBossList->ApplyAttribute(textAttrAlign);

		// Use SnpTextModelHelper::ApplyOverrides to apply the attribute. We are applying a paragraph 
		// attribute, so we indicate kParaAttributeStrand.
		SnpTextModelHelper	textCmdHelper;
		status = textCmdHelper.ApplyOverrides(textModel, position, length, paraAttributeBossList, kParaAttrStrandBoss);
		if (status != kSuccess) {
			ASSERT_FAIL("SnpTextModelHelper::ApplyOverrides failed to apply paragraph attributes");
			break;
		}

		// Now set the point size, leading and underline for the characters.
		status = kFailure;

		// Create a container for the character attributes to be applied.
		boost::shared_ptr<AttributeBossList> charAttributeBossList (new AttributeBossList());
		ASSERT(charAttributeBossList);
		if (!charAttributeBossList) {
			break;
		}

		// Create a point size, leading and underline attributes.
		InterfacePtr<IAttrReport> textAttrPointSize(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, ITextAttrRealNumber::ValueType>(kTextAttrPointSizeBoss, PMReal(18.0)));
		ASSERT(textAttrPointSize != nil);
		if(textAttrPointSize==nil) {
			break;
		}
		charAttributeBossList->ApplyAttribute(textAttrPointSize);
		
		InterfacePtr<IAttrReport> textAttrLeading(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, ITextAttrRealNumber::ValueType>(kTextAttrLeadBoss, PMReal(24.0)));
		ASSERT(textAttrLeading != nil);
		if(textAttrLeading==nil) {
			break;
		}
		charAttributeBossList->ApplyAttribute(textAttrLeading);
		
		InterfacePtr<IAttrReport> textAttrUnderlineMode(SnpTextAttrHelper::CreateTextAttribute<ITextAttrUnderlineMode, ITextAttrUnderlineMode::ValueType>(kTextAttrUnderlineBoss, IDrawingStyle::kUnderlineSingle));
		ASSERT(textAttrUnderlineMode);
		if (!textAttrUnderlineMode) {
			break;
		}
		charAttributeBossList->ApplyAttribute(textAttrUnderlineMode);

		// Use SnpTextModelHelper::ApplyOverrides to apply the attribute. We are applying a character 
		// attribute, so we indicate kCharAttrStrandBoss.
		status = textCmdHelper.ApplyOverrides(textModel, position, length, charAttributeBossList, kCharAttrStrandBoss);
		if (status != kSuccess) {
			ASSERT_FAIL("SnpTextModelHelper::ApplyOverrides failed to apply character attributes");
			break;
		}
	} while(false);
	return status;
}

/*
*/
ErrorCode SnpManipulateTextModel::ClearOverrides(ITextModel* textModel, const TextIndex position, const int32 length)
{
	ErrorCode status = kFailure;
	do {
		// Wrap the changes to be made in a command sequence.
		CmdUtils::SequenceContext seq;

		// First clear any paragraph alignment override.

		// Create a container for the paragraph attribute to be applied.
		boost::shared_ptr<AttributeBossList> paraAttributeBossList (new AttributeBossList());
		ASSERT(paraAttributeBossList);
		if (!paraAttributeBossList) {
			break;
		}

		// Create an alignment attribute.
		InterfacePtr<ITextAttrAlign> textAttrAlign(::CreateObject2<ITextAttrAlign>(kTextAttrAlignmentBoss));
		ASSERT(textAttrAlign != nil);
		if(textAttrAlign==nil) {
			break;
		}
		paraAttributeBossList->ApplyAttribute(textAttrAlign);
		// Use SnpTextModelHelper::ApplyOverrides to apply the attribute. We are applying a paragraph 
		// attribute, so we indicate kParaAttributeStrand.
		SnpTextModelHelper	textCmdHelper;
		status = textCmdHelper.ClearOverrides(textModel, position, length, paraAttributeBossList, kParaAttrStrandBoss);
		if (status != kSuccess) {
			ASSERT_FAIL("SnpTextModelHelper::ClearOverrides failed to clear paragraph attributes");
			break;
		}
		
		// Now clear any point size, leading or underline override.
		status = kFailure;

		// Create a container for the character attributes to be cleared.
		boost::shared_ptr<AttributeBossList> charAttributeBossList (new AttributeBossList());
		ASSERT(charAttributeBossList);
		if (!charAttributeBossList) {
			break;
		}

		// Create a point size, leading and underline attributes.
		InterfacePtr<ITextAttrRealNumber> textAttrPointSize(::CreateObject2<ITextAttrRealNumber>(kTextAttrPointSizeBoss));
		ASSERT(textAttrPointSize != nil);
		if(textAttrPointSize==nil) {
			break;
		}
		charAttributeBossList->ApplyAttribute(textAttrPointSize);
		InterfacePtr<ITextAttrRealNumber> textAttrLeading(::CreateObject2<ITextAttrRealNumber>(kTextAttrLeadBoss));
		ASSERT(textAttrLeading != nil);
		if(textAttrLeading==nil) {
			break;
		}
		charAttributeBossList->ApplyAttribute(textAttrLeading);
		InterfacePtr<ITextAttrUnderlineMode> textAttrUnderlineMode(::CreateObject2<ITextAttrUnderlineMode>(kTextAttrUnderlineBoss));
		ASSERT(textAttrUnderlineMode);
		if (!textAttrUnderlineMode) {
			break;
		}
		charAttributeBossList->ApplyAttribute(textAttrUnderlineMode);
		// Use SnpTextModelHelper::ApplyOverrides to apply the attribute. We are applying a character 
		// attribute, so we indicate kCharAttrStrandBoss.
		status = textCmdHelper.ClearOverrides(textModel, position, length, charAttributeBossList, kCharAttrStrandBoss);
		if (status != kSuccess) {
			ASSERT_FAIL("SnpTextModelHelper::ClearOverrides failed to clear character attributes");
			break;
		}
	} while(false);
	return status;
}

/*
*/
ITextFocus* SnpManipulateTextModel::QueryTextFocus(ITextFrameColumn* textFrameColumn)
{
	ITextFocus* result = nil;
	do {
		ASSERT(textFrameColumn);
		if (!textFrameColumn) {
			break;
		}
		InterfacePtr<ITextModel> textModel(textFrameColumn->QueryTextModel());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		
		// Check if the story contains any characters.
		// Note that when a story is created it has a terminating
		// character and length of 1 characters. We never
		// want to include the terminating character in our focus.
		int32 charactersInPrimaryStoryThread = textModel->GetPrimaryStoryThreadSpan();
		// Number of characters in the story including the terminating character
		if (charactersInPrimaryStoryThread <= 1) {
			break; // the story has no significant characters
		}

		// Check if this text frame displays any characters.
		int32 span = textFrameColumn->TextSpan();
		if (span <= 0) {
			break; // the text frame is empty
		}
			
		// Get the range of characters displayed in the frame.	
		TextIndex startIndex = textFrameColumn->TextStart();
		// Index into the text model of the first character in the frame.
		TextIndex finishIndex = startIndex + span;
		// Index into the text model of the last character in the frame.

		// Check if this frame displays the story's terminating character.
		if (finishIndex >= charactersInPrimaryStoryThread)
		{
			// This frame contains the story's terminating character.
			// Exclude the terminating character from the range of
			// characters described by the text focus being created.
			span--;
			finishIndex--; 	
		}
		
		// Don't make a text focus if the frame only displays
		// the story's terminating character.	
		if (span <= 0) {
			break;	
		}

		// Create a new text focus to describe the range 
		// of characters displayed in the text frame...												
		InterfacePtr<ITextFocusManager> textFocusManager(textModel, UseDefaultIID());
		ASSERT(textFocusManager);
		if (!textFocusManager) {
			break;
		}
		result = textFocusManager->NewFocus(RangeData(startIndex, finishIndex, RangeData::kLeanForward), kInvalidClass);
		ASSERT(result != nil);	
	} while(false);
	return result;
}

/*
*/
ITextFocus* SnpManipulateTextModel::QueryParcelTextFocus(ITextModel* textModel, const RangeData range)
{
	ITextFocus* result = nil;
	do {
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		
		SnpTextModelHelper	textModelHelper;
		InterfacePtr<IParcel>	parcel(textModelHelper.QueryParcelContaining(textModel, range.Start(nil)));
		ASSERT(parcel);
		if (!parcel) {
			break;
		}
		
		InDesign::TextRange	parcelRange = textModelHelper.GetParcelTextRange(parcel);
		// Don't make a text focus if the parcel only displays
		// the story's terminating character.	
		if (parcelRange.Length() <= 1)
		{
			SNIPLOG("There is no text in the text frame/parcel to select from");
			break;
		}
		// Create a new text focus to describe the range 
		// of characters displayed in the text frame...												
		InterfacePtr<ITextFocusManager> textFocusManager(textModel, UseDefaultIID());
		ASSERT(textFocusManager);
		if (!textFocusManager) {
			break;
		}
		result = textFocusManager->NewFocus(parcelRange.GetRange(), kInvalidClass);
		ASSERT(result != nil);	
		
	} while(false);
	return result;
}

/*
*/
ErrorCode SnpManipulateTextModel::SelectText(ISelectionManager* selectionManager, ITextFocus* textFocus)
{
	ErrorCode status = kFailure;
	do {
		InterfacePtr<ITextModel> textModel(textFocus->QueryModel());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}

		selectionManager->DeselectAll(nil); // deselect every active CSB

		// To display a text selection the text tool must be active.
		// Change to the text tool if necessary.
		InterfacePtr<ITool> activeTool(Utils<IToolBoxUtils>()->QueryActiveTool());
		if (activeTool == nil || activeTool->IsTextTool() == kFalse) {
			InterfacePtr<ITool> textTool(Utils<IToolBoxUtils>()->QueryTool(kIBeamToolBoss));
			ASSERT(textTool);
			if (!textTool) {
				break;
			}
			if (Utils<IToolBoxUtils>()->SetActiveTool(textTool) == kFalse) {
				ASSERT_FAIL("IToolBoxUtils::SetActiveTool failed to change to kIBeamToolBoss");
				break;
			}
		}

		// Select text from the given text focus.
		InterfacePtr<ITextSelectionSuite> textSelectionSuite(selectionManager, UseDefaultIID());
		if (!textSelectionSuite) {
			break;
		}
		if (textSelectionSuite->SetTextSelection(::GetUIDRef(textModel), 
			RangeData(textFocus->GetStart(nil), textFocus->GetEnd()),
			Selection::kScrollIntoView, 
			nil))
			status = kSuccess;			
	} while(false);
	return status;
}


/*
*/
ErrorCode SnpManipulateTextModel::ProcessCopyStoryRangeCmd
(
	const UIDRef& sourceStory, 
	TextIndex sourceStart, 
	int32 sourceLength, 
	const UIDRef& destStory,
	TextIndex destStart, 
	int32 destLength
)
{
	SnpTextModelHelper	textCmdHelper;
	return textCmdHelper.ProcessCopyStoryRangeCmd(sourceStory, sourceStart, sourceLength, destStory, destStart, destLength);
}

/*
*/
ErrorCode SnpManipulateTextModel::CopyAll(const UIDRef& sourceStory, const UIDRef& destStory)	
{
	ErrorCode status = kFailure;
	do {
		InterfacePtr<ITextModel> sourceTextModel(sourceStory, UseDefaultIID());
		if (sourceTextModel == nil) {
			ASSERT_FAIL("sourceTextModel invalid");
			break;
		}
		InterfacePtr<ITextModel> destTextModel(destStory, UseDefaultIID());
		if (destTextModel == nil) {
			ASSERT_FAIL("destTextModel invalid");
			break;
		}
		status = this->ProcessCopyStoryRangeCmd
			(
				sourceStory,
				0,
				sourceTextModel->GetPrimaryStoryThreadSpan()-1,
				destStory,
				0, // Insert the copied text at the start of the destination story.
				0
			);
	} while (false);
	return status;
}

/*
*/
ErrorCode SnpManipulateTextModel::CopyInlines(const UIDRef& sourceStory, const UIDRef& destStory)	
{
	return this->CopyOwnedItem(sourceStory, destStory, kInlineBoss);
}

/*
*/
ErrorCode SnpManipulateTextModel::CopyTables(const UIDRef& sourceStory, const UIDRef& destStory)	
{
	ErrorCode status = kFailure;
	do {
		// Collect the ranges of text in the source story 
		// on which each embedded table is anchored.
		Text::StoryRangeList tableAnchorRanges;
		InterfacePtr<ITextModel> textModel(sourceStory, UseDefaultIID());
		ASSERT(textModel);
		if (textModel == nil) {
			ASSERT_FAIL("invalid textModel");
			break;
		}
		InterfacePtr<ITextStoryThreadDictHier> textStoryDictHier(textModel, UseDefaultIID());
		ASSERT(textStoryDictHier);
		if(textStoryDictHier == nil) {
			break;
		}
		UID nextUID = sourceStory.GetUID();
		while(nextUID != kInvalidUID) {
			InterfacePtr<ITextStoryThreadDict> textStoryThreadDict(sourceStory.GetDataBase(), nextUID, UseDefaultIID());
			ASSERT(textStoryThreadDict);
			if(textStoryThreadDict == nil) {
				break;
			}
			InterfacePtr<ITableModel> tableModel(textStoryThreadDict, UseDefaultIID());
			if (tableModel) {
				// This is a table.
				bool16 wasAnchored;
				Text::StoryRange anchorRange = textStoryThreadDict->GetAnchorTextRange(&wasAnchored);
				if (wasAnchored && anchorRange.End() < textModel->GetPrimaryStoryThreadSpan()) {
					// This table is anchored in the story so store
					// the range of text on which it is anchored for
					// the subsequent copy operation.
					tableAnchorRanges.push_back(anchorRange);
				}
			}
			// Get the next text story thread dictionary in the collection.
			nextUID = textStoryDictHier->NextUID(nextUID);	
		} // end while(nextUID != kInvalidUID)

		if (tableAnchorRanges.size() == 0) {
			// Nothing to copy.
			status = kSuccess;
			break;
		}

		// Copy tables embedded in the soure story by copying the range
		// of text on which each table is anchored.
		CmdUtils::SequencePtr sequence;
		Text::StoryRangeList::iterator iter = tableAnchorRanges.end();
		while (--iter >= tableAnchorRanges.begin()) {
				status = this->ProcessCopyStoryRangeCmd
				(
				sourceStory,
				iter->GetStart(nil),
				iter->GetEnd() - iter->GetStart(nil),
				destStory,
				0, // Insert the copied stuff at the start of the destination story.
				0 // insert rather than replace
				);
			if (status != kSuccess) {
				ASSERT_FAIL("CopyStoryRangeCmd failed");
				break;
			}
		}
		if (status != kSuccess)
			ErrorUtils::PMSetGlobalErrorCode(status);
	} while (false);
	return status;
}

/*
*/
ErrorCode SnpManipulateTextModel::CopyOwnedItem(const UIDRef& sourceStory, const UIDRef& destStory, const ClassID& ownedItemType)	
{
	ErrorCode status = kFailure;
	do {
		// Collect the TextIndex of each owned item in the source story of the desired type.
		OwnedItemDataList ownedItems;
		InterfacePtr<ITextModel> textModel(sourceStory, UseDefaultIID());
		if (textModel == nil) {
			ASSERT_FAIL("invalid textModel");
			break;
		}
		Utils<ITextUtils> textUtils;
		ASSERT(textUtils);
		if (!textUtils) {
			break;
		}
		textUtils->CollectOwnedItems(textModel, 0, textModel->TotalLength(), &ownedItems);
		OwnedItemDataList::iterator iter = ownedItems.begin();
		K2Vector<TextIndex> anchors;
		while (iter != ownedItems.end()) {
			if (iter->fClassID == ownedItemType) {
				// Copy those owned items that are of the desired type.
				anchors.push_back(iter->fAt);
			}
			iter++;
		}
		if (anchors.size() == 0) {
			// Nothing to copy.
			status = kSuccess;
			break;
		}

		// Copy owned items by copying the TextIndex on which the owned item is anchored.
		CmdUtils::SequencePtr sequence;
		K2Vector<TextIndex>::iterator anchorIter = anchors.end();
		while (--anchorIter >= anchors.begin()) {
			TextIndex runPosition = *anchorIter;
			status = this->ProcessCopyStoryRangeCmd
				(
				sourceStory,
				runPosition,
				1,
				destStory,
				0, // Insert the copied stuff at the start of the destination story.
				0 // insert rather than replace
				);
			if (status != kSuccess) {
				ASSERT_FAIL("CopyStoryRangeCmd failed");
				break;
			}
		}
		if (status != kSuccess)
			ErrorUtils::PMSetGlobalErrorCode(status);
	} while (false);
	return status;
}

/*
*/
UIDRef SnpManipulateTextModel::CreateTextFrame(const UIDRef& fromGraphicFrameUIDRef, UIDRef& storyUIDRef)
{
	UIDRef result = UIDRef::gNull;

	do {
		// Create a new text frame.

		// Determine the bounds of the new text frame.
		// Make it the same size as the given frame, positioned alongside at a 10 point offset.
		InterfacePtr<IGeometry> geometry(fromGraphicFrameUIDRef, UseDefaultIID());
		ASSERT(geometry);
		if (!geometry) {
			break;
		}
		PMMatrix inner2parent = ::InnerToParentMatrix(geometry);
		PMRect boundsInParentCoords = geometry->GetStrokeBoundingBox(inner2parent);
		boundsInParentCoords.MoveRel(boundsInParentCoords.Width()+ 10.0, 0.0);

		// Parent the new text frame on the same spread layer as the given text frame.
		InterfacePtr<IHierarchy> hierarchy(fromGraphicFrameUIDRef, UseDefaultIID());
		ASSERT(hierarchy);
		if (!hierarchy) {
			break;
		}
		UIDRef parentUIDRef = UIDRef(fromGraphicFrameUIDRef.GetDataBase(), hierarchy->GetLayerUID());


		// Create the new frame based on the properties of the given text frame determined above.
		SDKLayoutHelper layoutHelper;
		UIDRef toGraphicFrameUIDRef = layoutHelper.CreateTextFrame(parentUIDRef, boundsInParentCoords, 1, kFalse, &storyUIDRef);
		if (toGraphicFrameUIDRef == UIDRef::gNull) {
			ASSERT("SDKLayoutHelper::CreateTextFrame failed");
			break;
		}

		result = toGraphicFrameUIDRef;

	} while(false);
	return result;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
class _SnpRunnerManipulateTextModel : public SnpRunnable
{
	
	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerManipulateTextModel();

		/** Destructor.
		 */
		virtual			~_SnpRunnerManipulateTextModel();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTextTargetContext;}
};
/* Constructor.
*/
_SnpRunnerManipulateTextModel::_SnpRunnerManipulateTextModel() : SnpRunnable("ManipulateTextModel")
{
	this->SetDescription("Inserts, deletes, replaces and styles text using text model commands");
	this->SetPreconditions("text selection");
	this->SetCategories("sdk_snippet, sdk_text");
}

/* Destructor.
*/
_SnpRunnerManipulateTextModel::~_SnpRunnerManipulateTextModel()
{
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerManipulateTextModel::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil) {
			break;
		}
		result = kTrue;
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerManipulateTextModel::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do {
		SnpManipulateTextModel instance;
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil) {
			SNIPLOG("Please select a text frame and try again");
			break;
		}
		InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel());
		ASSERT(textModel);
		if (textModel == nil) {
			break;
		}		
		RangeData range = textTarget->GetRange();
		
		// Prompt for parameter values.
		K2Vector<PMString> choices;
		choices.push_back(PMString("Insert Text")); //0
		if (textModel->TotalLength() > 1) {
			choices.push_back(PMString("Delete Text")); //1
			choices.push_back(PMString("Replace Text")); //2
			choices.push_back(PMString("Apply Overrides")); //3
			choices.push_back(PMString("Clear Overrides")); //4
			choices.push_back(PMString("Select Text")); //5
			choices.push_back(PMString("Copy Story")); //6
			choices.push_back(PMString("Copy Inlines")); //7
			choices.push_back(PMString("Copy Tables")); //8
		}
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 choice = parameterUtils->GetChoice(PMString("What story data do you want to manipulate?"), choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		if (choice == 0) {
			// Ask for the position to insert.
			int32 position = 
				parameterUtils->GetInt32(PMString("Please specify position(TextIndex) for insertion"), range.Start(nil), 0, textModel->TotalLength()-1);
			if (parameterUtils->WasDialogCancelled())
				break;
			// Ask for the text string to insert.
			PMString insertString = parameterUtils->GetPMString("Please specify string to insert", "");
			if (parameterUtils->WasDialogCancelled())
				break;
			WideString text(insertString);
			status =  instance.InsertText(textModel, position, text);
		}
		else if (choice == 1) {
			// Determine the range of text to be deleted.
			int32 position = range.Start(nil);
			int32 length = 1;
			if (range.Length() > 0) {
				length = range.Length();
			}
			else if (position > 0) {
				position = position - 1;
			}
			if (textModel->TotalLength() > 2) {
				// Give the user a change to adjust the range.
				position = parameterUtils->GetInt32(PMString("Please specify start position(TextIndex) for deletion"), position, 0, textModel->TotalLength()-2);
				if (parameterUtils->WasDialogCancelled())
					break;
				length = parameterUtils->GetInt32(PMString("Please specify number of characters to delete"), length, 1, textModel->TotalLength()-position-1);
				if (parameterUtils->WasDialogCancelled())
					break;
			}
			status = instance.DeleteText(textModel, position, length);
		}
		else if (choice == 2) {
			// Determine the range of text to be replaced.
			int32 position = range.Start(nil);
			int32 length = 1;
			if (range.Length() > 0) {
				length = range.Length();
			}
			else if (position > 0) {
				position = position - 1;
			}
			if (textModel->TotalLength() > 2) {
				// Give the user a change to adjust the range.
				position = 
					parameterUtils->GetInt32(PMString("Please specify start position(TextIndex) for replacement"), position, 0, textModel->TotalLength()-2);
				if (parameterUtils->WasDialogCancelled())
					break;
				length = 
					parameterUtils->GetInt32(PMString("Please specify number of characters to replace"), length, 1, textModel->TotalLength()-position-1);
				if (parameterUtils->WasDialogCancelled())
					break;
			}
			// ask for the text to replace
			PMString replaceString = parameterUtils->GetPMString("Please specify string to replace the given range with", "");
			if (parameterUtils->WasDialogCancelled())
				break;
			WideString text(replaceString);
			status = instance.ReplaceText(textModel, position, length, text);
		}
		else if (choice == 3) {
			// Determine the range of text to be formatted.
			int32 position = range.Start(nil);
			int32 length = 1;
			if (range.Length() > 0) {
				length = range.Length();
			}
			else if (position > 0) {
				position = position - 1;
			}
			if (textModel->TotalLength() > 2) {
				// Give the user a change to adjust the range.
				position = 
					parameterUtils->GetInt32(PMString("Please specify start position(TextIndex) for formatting"), position, 0, textModel->TotalLength()-2);
				if (parameterUtils->WasDialogCancelled())
					break;
				length = 
					parameterUtils->GetInt32(PMString("Please specify number of characters to format"), length, 1, textModel->TotalLength()-position-1);
				if (parameterUtils->WasDialogCancelled())
					break;
			}
			status = instance.ApplyOverrides(textModel, position, length);
		}
		else if (choice == 4) {
			// Determine the range of text to be formatted.
			int32 position = range.Start(nil);
			int32 length = 1;
			if (range.Length() > 0) {
				length = range.Length();
			}
			else if (position > 0) {
				position = position - 1;
			}
			if (textModel->TotalLength() > 2) {
				// Give the user a change to adjust the range.
				position = 
					parameterUtils->GetInt32(PMString("Please specify start position(TextIndex) for formatting"), position, 0, textModel->TotalLength()-2);
				if (parameterUtils->WasDialogCancelled())
					break;
				length = 
					parameterUtils->GetInt32(PMString("Please specify number of characters to format"), length, 1, textModel->TotalLength()-position-1);
				if (parameterUtils->WasDialogCancelled())
					break;
			}
			status = instance.ClearOverrides(textModel, position, length);
		}
		else if (choice == 5) {
			InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel());
			if (textModel == nil) {
				break;
			}
			RangeData	range = textTarget->GetRange();
			InterfacePtr<ITextFocus> textParcelTextFocus(instance.QueryParcelTextFocus(textModel, range));
			if (!textParcelTextFocus) {
				break;
			}
			status = instance.SelectText(runnableContext->GetActiveContext()->GetContextSelection(), textParcelTextFocus);
			
		}
		else if (choice == 6) {
			// Create a new text frame of alongside the frame in which the range of text that
			// is currently selected starts.
			SnpTextModelHelper	textHelper;
			InterfacePtr<IParcel> parcel(textHelper.QueryParcelContaining(textModel, range.Start(nil)));
			if (parcel == nil) {
				SNIPLOG("Please click text caret in a text frame");
				break;
			}
			InterfacePtr<ITextFrameColumn> textFrameColumn(parcel->QueryFrame());
			if (textFrameColumn == nil) {
				break;
			}
			SDKLayoutHelper layoutHelper;
			UIDRef sourceStory = ::GetUIDRef(textModel);
			UIDRef sourceFrameRef = layoutHelper.GetGraphicFrameRef(textFrameColumn);	
			UIDRef destStory;
			instance.CreateTextFrame(sourceFrameRef, destStory);
			// Copy all of the text into the story associated with the new text frame.	
			status = instance.CopyAll(sourceStory, destStory);
		}
		else if (choice == 7) {
			// Create a new text frame of alongside the frame in which the range of text that
			// is currently selected starts.
			SnpTextModelHelper	textHelper;
			InterfacePtr<IParcel> parcel(textHelper.QueryParcelContaining(textModel, range.Start(nil)));
			if (parcel == nil) {
				SNIPLOG("Please click text caret in a text frame");
				break;
			}
			InterfacePtr<ITextFrameColumn> textFrameColumn(parcel->QueryFrame());
			if (textFrameColumn == nil) {
				break;
			}
			SDKLayoutHelper layoutHelper;
			UIDRef sourceStory = ::GetUIDRef(textModel);
			UIDRef sourceFrameRef = layoutHelper.GetGraphicFrameRef(textFrameColumn);	
			UIDRef destStory;
			instance.CreateTextFrame(sourceFrameRef, destStory);
			// Copy all of the inlines in the selected story into the story associated with the new text frame.
			status = instance.CopyInlines(sourceStory, destStory);
		}
		else if (choice == 8) {
			// Create a new text frame of alongside the frame in which the range of text that
			// is currently selected starts.
			SnpTextModelHelper	textHelper;
			InterfacePtr<IParcel> parcel(textHelper.QueryParcelContaining(textModel, range.Start(nil)));
			if (parcel == nil) {
				SNIPLOG("Please click text caret in a text frame");
				break;
			}
			InterfacePtr<ITextFrameColumn> textFrameColumn(parcel->QueryFrame());
			if (textFrameColumn == nil) {
				break;
			}
			SDKLayoutHelper layoutHelper;
			UIDRef sourceStory = ::GetUIDRef(textModel);
			UIDRef sourceFrameRef = layoutHelper.GetGraphicFrameRef(textFrameColumn);	
			UIDRef destStory;
			instance.CreateTextFrame(sourceFrameRef, destStory);
			// Copy all of the tables in the selected story into the story associated with the new text frame.	
			status = instance.CopyTables(sourceStory, destStory);
		}		
	} while(false);
	return status;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerManipulateTextModel instance_SnpRunnerManipulateTextModel;
DEFINE_SNIPPET(_SnpRunnerManipulateTextModel) 	

// End, SnpManipulateTextModel.cpp


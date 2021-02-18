//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpTextModelHelper.cpp $
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
#include "ITextModelCmds.h"
#include "IUIDData.h"
#include "IRangeData.h"
#include "ITextParcelList.h"
#include "IFrameList.h"
#include "ITextFrameColumn.h"
#include "IFrameListComposer.h"
#include "ITextParcelListComposer.h"
#include "textiterator.h"
// General includes:
#include "Utils.h"
#include "UIDList.h"
#include "CmdUtils.h"

//Project includes:
#include "SnpTextModelHelper.h"

/*
*/
SnpTextModelHelper::SnpTextModelHelper()
{
}

/*
*/
SnpTextModelHelper::~SnpTextModelHelper()
{
}

/*
*/
ErrorCode SnpTextModelHelper::InsertText(ITextModel* textModel, const TextIndex position, const boost::shared_ptr<WideString>& text)
{
	ErrorCode status = kFailure;
	do {
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		if (position < 0 || position >= textModel->TotalLength()) {
			ASSERT_FAIL("position invalid");
			break;
		}
    	InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
    	ASSERT(textModelCmds);
    	if (!textModelCmds) {
			break;
		}
		InterfacePtr<ICommand> insertCmd(textModelCmds->InsertCmd(position, text));
		ASSERT(insertCmd);
		if (!insertCmd) {
			break;
		}
		status = CmdUtils::ProcessCommand(insertCmd);
	} while(false);
	return status;
}

/*
*/
ErrorCode SnpTextModelHelper::DeleteText(ITextModel* textModel, const TextIndex position, const int32 length)
{
 	ErrorCode status = kFailure;
	do {
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		if (position < 0 || position >= textModel->TotalLength()) {
			ASSERT_FAIL("position invalid");
			break;
		}
		if (length < 1 || length >= textModel->TotalLength()) {
			ASSERT_FAIL("length invalid");
			break;
		}
   		InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
    	ASSERT(textModelCmds);
    	if (!textModelCmds) {
			break;
		}
		InterfacePtr<ICommand> deleteCmd(textModelCmds->DeleteCmd(position, length));
		ASSERT(deleteCmd);
		if (!deleteCmd) {
			break;
		}
		status = CmdUtils::ProcessCommand(deleteCmd);
	} while(false);
	return status;
}

/*
*/
ErrorCode SnpTextModelHelper::ReplaceText(ITextModel* textModel, const TextIndex position, const int32 length, const boost::shared_ptr<WideString>& text)
{
	ErrorCode status = kFailure;
	do {
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		if (position < 0 || position >= textModel->TotalLength()) {
			ASSERT_FAIL("position invalid");
			break;
		}
		if (length < 1 || length >= textModel->TotalLength()) {
			ASSERT_FAIL("length invalid");
			break;
		}
    	InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
    	ASSERT(textModelCmds);
    	if (!textModelCmds) {
			break;
		}
		InterfacePtr<ICommand> replaceCmd(textModelCmds->ReplaceCmd(position, length, text));
		ASSERT(replaceCmd);
		if (!replaceCmd) {
			break;
		}
		status = CmdUtils::ProcessCommand(replaceCmd);
	} while(false);
	return status;
}

/*
*/
ErrorCode SnpTextModelHelper::ApplyOverrides(ITextModel* textModel, const TextIndex position, const int32 length, const boost::shared_ptr<AttributeBossList>& attr, ClassID whichStrand)
{
	ErrorCode status = kFailure;

	do {
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		if (whichStrand != kParaAttrStrandBoss && whichStrand != kCharAttrStrandBoss) {
			ASSERT_FAIL("overrides only apply to either kParaAttrStrandBoss or kCharAttrStrandBoss");
			break;
		}
		if (position < 0 || position >= textModel->TotalLength()) {
			ASSERT_FAIL("position invalid");
			break;
		}
		if (length < 1 || length >= textModel->TotalLength()) {
			ASSERT_FAIL("length invalid");
			break;
		}

		// Create a command to apply the attribute.
     	InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
    	ASSERT(textModelCmds);
    	if (!textModelCmds) {
			break;
		}
		InterfacePtr<ICommand> applyAttrCmd(textModelCmds->ApplyCmd(position,
			length,
			attr, 
			whichStrand));
		ASSERT(applyAttrCmd);
		if(applyAttrCmd == nil) {
			break;
		}

		// Apply the attribute.
		status = CmdUtils::ProcessCommand(applyAttrCmd);
		if (status != kSuccess) {
			ASSERT_FAIL("ITextModelCmds::ApplyCmd failed to apply attributes");
			break;
		}
	} while(false);
	return status;
}

/*
*/
ErrorCode SnpTextModelHelper::ClearOverrides(ITextModel* textModel, const TextIndex position, const int32 length, const boost::shared_ptr<AttributeBossList>& attr, ClassID whichStrand)
{
	ErrorCode status = kFailure;

	do {
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		if (whichStrand != kParaAttrStrandBoss && whichStrand != kCharAttrStrandBoss) {
			ASSERT_FAIL("overrides only apply to either kParaAttrStrandBoss or kCharAttrStrandBoss");
			break;
		}
		if (position < 0 || position >= textModel->TotalLength()) {
			ASSERT_FAIL("position invalid");
			break;
		}
		if (length < 1 || length >= textModel->TotalLength()) {
			ASSERT_FAIL("length invalid");
			break;
		}

		// Create a command to apply the attribute.
     	InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
    	ASSERT(textModelCmds);
    	if (!textModelCmds) {
			break;
		}
		InterfacePtr<ICommand> clearAttrCmd(textModelCmds->ClearOverridesCmd(position,
			length,
			attr, 
			whichStrand));
		ASSERT(clearAttrCmd);
		if(clearAttrCmd == nil) {
			break;
		}

		// Apply the attribute.
		status = CmdUtils::ProcessCommand(clearAttrCmd);
		if (status != kSuccess) {
			ASSERT_FAIL("ITextModelCmds::ClearOverridesCmd failed to clear attributes");
			break;
		}
	} while(false);
	return status;
}

/*
*/
ErrorCode SnpTextModelHelper::ProcessCopyStoryRangeCmd(
			const UIDRef& sourceStory, 
			TextIndex sourceStart, 
			int32 sourceLength, 
			const UIDRef& destStory,
			TextIndex destStart, 
			int32 destLength
		)
{
	ErrorCode status = kFailure;
	do {
		// Validate the range of text to be copied from the source story.
		InterfacePtr<ITextModel> sourceTextModel(sourceStory, UseDefaultIID());
		if (sourceTextModel == nil) {
			break;
		}
		int32 sourceStoryLength = sourceTextModel->TotalLength();
		if (sourceStart > sourceStoryLength - 1) {
			break;
		}
		if (sourceLength < 1) {
			break;
		}
		TextIndex sourceEnd = sourceStart + sourceLength;
		if (sourceEnd > sourceStoryLength - 1) {
			break;
		}

		// Validate the range of text to be replaced in the destination story.
		InterfacePtr<ITextModel> destTextModel(destStory, UseDefaultIID());
		if (destTextModel == nil) {
			break;
		}
		int32 destStoryLength = destTextModel->TotalLength();
		if (destStart> destStoryLength - 1) {
			break;
		}
		if (destLength < 0) {
			break;
		}
		TextIndex destEnd = destStart + destLength;
		if (destEnd > destStoryLength - 1) {
			break;
		}

		// Create kCopyStoryRangeCmdBoss.
		InterfacePtr<ICommand> copyStoryRangeCmd(CmdUtils::CreateCommand(kCopyStoryRangeCmdBoss));
		if (copyStoryRangeCmd == nil) {
			break;
		}

		// Refer the command to the source story and range to be copied.
		InterfacePtr<IUIDData> sourceUIDData(copyStoryRangeCmd, UseDefaultIID());
		if (sourceUIDData == nil) {
			break;
		}
		sourceUIDData->Set(sourceStory);
		InterfacePtr<IRangeData> sourceRangeData(copyStoryRangeCmd, UseDefaultIID());
		if (sourceRangeData == nil) {
			break;
		}
		sourceRangeData->Set(sourceStart, sourceEnd);

		// Refer the command to the destination story and the range to be replaced.
		UIDList itemList(destStory);
		copyStoryRangeCmd->SetItemList(itemList);
		InterfacePtr<IRangeData> destRangeData(copyStoryRangeCmd, IID_IRANGEDATA2);
		destRangeData->Set(destStart, destEnd);

		// Process CopyStoryRangeCmd
		status = CmdUtils::ProcessCommand(copyStoryRangeCmd);
	} while(false);
	return status;
}

/*
 */
bool16 SnpTextModelHelper::IsStoryOverset(InterfacePtr<ITextModel> textModel)
{
	bool16 overset = kFalse;
	do {
		// Find the parcel list associated with the primary story thread.
        InterfacePtr<IFrameList> frameList(textModel->QueryFrameList());
		ASSERT(frameList);
		if (!frameList) {
			break;
		}
		// Use ITextUtils to determine if it is overset.
		overset = Utils<ITextUtils>()->IsOverset(frameList);
	} while (false); 
	return overset;
}

/*
 */
bool16 SnpTextModelHelper::IsTextFrameOverset(const InterfacePtr<ITextFrameColumn> textFrameColumn)
{
	bool16 overset = kFalse;
	do {
		// Check for damage & recompose if necessary
		InterfacePtr<IFrameList> frameList(textFrameColumn->QueryFrameList());
		if (frameList == nil) {
			ASSERT_FAIL("invalid frameList");
			break;
		}
		int32 firstDamagedFrameIndex = frameList->GetFirstDamagedFrameIndex();
		UID frameUID = ::GetUID(textFrameColumn);
		int32 frameIndex = frameList->GetFrameIndex(frameUID);
		if (frameIndex < 0) {
			ASSERT_FAIL("invalid frameIndex");
			break;
		}
		if (firstDamagedFrameIndex <= frameIndex) {
			// Frame not fully composed, force recomposition.
			InterfacePtr<IFrameListComposer> frameListComposer(frameList, UseDefaultIID());
			if (frameListComposer == nil) {
				ASSERT_FAIL("frameListComposer invalid");
				break;
			}

			//
			// It is not very reasonable to ask if a particular TextFrameColumn
			// is overset unless it is the last one in the framelist and even
			// then this check does not deal with split footnotes.
			//
			// The approved way of detecting overset is asking the MCF.
			//
			frameListComposer->RecomposeThruLastFrame();
		}

		// Find the TextIndex of the final character in the story.
		InterfacePtr<ITextModel> textModel(textFrameColumn->QueryTextModel());
		if (textModel == nil) {
			ASSERT_FAIL("invalid textModel");
			break;
		}
		TextIndex storyFinalTextIndex = textModel->GetPrimaryStoryThreadSpan() - 1;
		
		// Find the TextIndex of the final character in the frame.
		TextIndex frameFinalTextIndex = 
			textFrameColumn->TextStart() + textFrameColumn->TextSpan() - 1;

		if (frameFinalTextIndex == storyFinalTextIndex) {
			// Frame displays the final character in the story.
			break;
		}

		if (frameFinalTextIndex == storyFinalTextIndex - 1) {
			// Frame does not display the terminating kTextChar_CR.
			// But don't consider this condition as overset.
			break;
		}

		// If we drop through to this point in the code
		// the frame is overset.
		overset = kTrue;

	} while (false); // only do once
	return overset;
}

/*
*/
bool16 SnpTextModelHelper::IsParcelOverset(const InterfacePtr<IParcel> parcel)
{
	bool16 overset = kFalse;
	do {
		ParcelKey parcelKey = parcel->GetParcelKey();
		if (parcelKey.IsValid() == kFalse) {
			overset = kTrue;
			break;
		}

		// Check for damage & recompose if necessary
		InterfacePtr<IParcelList> parcelList(parcel->QueryParcelList());
		ASSERT(parcelList);
		if (parcelList == nil) {
			break;
		}
		InterfacePtr<ITextParcelList> textParcelList(parcelList, UseDefaultIID());
		ASSERT(textParcelList);
		if (textParcelList == nil) {
			break;
		}
		if (textParcelList->GetIsDamaged(parcelKey)) {
			// Parcel is damaged, recompose.
			InterfacePtr<ITextParcelListComposer> textParcelListComposer(textParcelList, UseDefaultIID());
			ASSERT(textParcelListComposer);
			if (textParcelListComposer == nil) {
				break;
			}
			textParcelListComposer->RecomposeThru(parcelKey);
			ASSERT_MSG(textParcelList->GetIsDamaged(parcelKey) == kFalse, "parcel should have been recomposed, why is it still damaged?");
		}

		// Check if the story thread is completely displayed in the parcel list.
		if (textParcelList->GetIsOverset()) {
			// The story thread is not completely displayed in the parcel list.
			// Therefore all parcels in the parcel list are overset, so
			// this particular parcel must be too.
			overset = kTrue;
			break;
		}

	} while (false); // only do once
	return overset;
}

/*
*/
IParcel* SnpTextModelHelper::QueryParcelContaining(ITextModel* textModel, const TextIndex at)
{
	InterfacePtr<IParcel> result;
	do {
		// Find the parcel list that displays the TextIndex.
		InterfacePtr<ITextParcelList> textParcelList(textModel->QueryTextParcelList(at));
		if (!textParcelList) {
			// Likely it belongs to a note or deleted text or 
			// another story thread that does not use parcels.
			// Or perhaps we are not in the layout view (i.e.
			// we are in a story or galley view).
			break;
		}
		ParcelKey firstDamagedParcelKey = textParcelList->GetFirstDamagedParcel();
		if (firstDamagedParcelKey.IsValid() == kTrue){
			// Recompose the text in this parcel list.
			InterfacePtr<ITextParcelListComposer> textParcelListComposer(textParcelList, UseDefaultIID());
			ASSERT(textParcelListComposer);
			if (!textParcelListComposer) {
				break;
			}
			textParcelListComposer->RecomposeThruLastParcel();
		}

		// Find the parcel that displays the TextIndex.
		ParcelKey parcelKey = textParcelList->GetParcelContaining(at);
		if (parcelKey.IsValid() == kFalse) {
			// Parcel is not displayed. Could be that the parcel
			// that displays this TextIndex is an overset text
			// cell in a table for example.
			break;
		}
		InterfacePtr<IParcelList> parcelList(textParcelList, UseDefaultIID());
		ASSERT(parcelList);
		if (!parcelList) {
			break;
		}
		InterfacePtr<IParcel> parcel(parcelList->QueryParcel(parcelKey));
		ASSERT(parcel);
		if (!parcel) {
			break;
		}
		result = parcel;
	} while(false);
	return result.forget();
}

/*
*/
InDesign::TextRange SnpTextModelHelper::GetParcelTextRange(IParcel* parcel)
{
	InDesign::TextRange result;
	do {
		ASSERT(parcel);
		if (!parcel) {
			break;
		}
		InterfacePtr<IParcelList> parcelList(parcel->QueryParcelList());
		ASSERT(parcelList);
		if (!parcelList) {
			break;
		}
		InterfacePtr<ITextParcelList> textParcelList(parcelList, UseDefaultIID());
		ASSERT(textParcelList);
		if (!textParcelList) {
			break;
		}

		ParcelKey parcelKey = parcel->GetParcelKey();
		if (textParcelList->GetIsDamaged(parcelKey)) {
			// Compose the text so the range is accurate.
			InterfacePtr<ITextParcelListComposer> textParcelListComposer(textParcelList, UseDefaultIID());
			ASSERT(textParcelListComposer);
			if (!textParcelListComposer) {
				break;
			}
			textParcelListComposer->RecomposeThru(parcelKey);
		}
		
		// Determine the range of text displayed in the parcel.		
		RangeData range = textParcelList->GetTextRange(parcelKey);

		InterfacePtr<ITextModel> textModel(textParcelList->GetTextModelRef(), UseDefaultIID());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}

		result = InDesign::TextRange(textModel, range);

	} while(false);
	return result;	
}
/*
*/
WideString SnpTextModelHelper::GetWideStringFromTextRange(const InDesign::TextRange& range)
{
	WideString result;
	do {
		ASSERT(range.IsValid());
		if (!range.IsValid()) {
			break;
		}
		InterfacePtr<ITextModel> textModel(range.QueryModel());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		TextIterator begin(textModel, range.Start());
		TextIterator end(textModel, range.End());
		for (TextIterator iter = begin; iter != end; iter++) {
			const UTF32TextChar characterCode = *iter;
			result.Append(characterCode);
		}		
	} while(false);
	return result;
}

/*
*/
WideString SnpTextModelHelper::GetWideStringFromParcel(IParcel* parcel)
{
	WideString result;
	do {
		InDesign::TextRange range = this->GetParcelTextRange(parcel);
		if (!range.IsValid()) {
			break;
		}
		result = this->GetWideStringFromTextRange(range);
	} while(false);
	return(result);
}
//End, SnpTextModelHelper.cpp

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateTextEndnotes.cpp $
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
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2017 Adobe 
//  All Rights Reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in 
//  accordance with the terms of the Adobe license agreement accompanying 
//  it. If you have received this file from a source other than Adobe, 
//  then your use, modification, or distribution of it requires the prior 
//  written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IComposeScanner.h"
#include "IDocument.h"
#include "IEndnoteFacade.h"
#include "IEndnoteReferenceData.h"
#include "IEndnoteSettings.h"
#include "IEndnoteTextRangeData.h"
#include "IItemStrand.h"
#include "INoteDataUtils.h"
#include "IOwnedItem.h"
#include "ISelectionUtils.h"
#include "ITextEditSuite.h"
#include "ITextFocus.h"
#include "ITextMiscellanySuite.h"
#include "ITextModel.h"
#include "ITextModelCmds.h"
#include "itextRangeNode.h"
#include "ITextSelectionSuite.h"
#include "ITextStoryThread.h"
#include "ITextTarget.h"

// General includes:
#include "WideString.h"
#include "Utils.h"
#include "CmdUtils.h"

// Framework includes:
#include "SnipRunLog.h"
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnpTextModelHelper.h"

/**
*	\li How to access endnotes in a story.
* 	\li	How to inspect the content of endnotes within a story.
*	\li How to create a endnote within a story.
*	\li How to delete all endnotes in a story.
*	\li How to flatten endnotes into a story.
*	\li How to convert a selection into a endnote.
* Endnotes are text ranges in a separate endnotes story.
*
* Select the story of interest (i.e. have a valid text selection or focus).
*
* 	@ingroup sdk_snippet
* 	@ingroup sdk_text
*/
class SnpManipulateTextEndnotes
{
public:
	/** Constructor.
	*/
	SnpManipulateTextEndnotes() {}

	/** Destructor.
	*/
	virtual	~SnpManipulateTextEndnotes() {}

	/**
	Driver for dumping information about endnotes in the currently selected story.
	\li In the story, where is the endnote anchor point?
	\li What is the endnote content?
	@param iTextTarget IN identifies the story we are interested in.
	@return kFailure if problems are encountered.
	*/
	ErrorCode ExploreEndnotes(ITextTarget * iTextTarget);

	/**
	Driver for inserting endnotes. Determines which story we are interested in.
	@param iTextTarget IN identifies the story we are interested in.
	@param endnoteString IN the string we wish to insert into the endnote
	@return kFailure on cancel of error.
	*/
	ErrorCode InsertEndnote(ITextTarget * iTextTarget, const boost::shared_ptr<WideString>& endnoteString);

	/**
	Driver for deleting endnotes in a story. Determines which story we are interested in.
	@param iTextTarget IN identifies the story we are interested in.
	@return kFailure on error.
	*/
	ErrorCode DeleteStoryEndnotes(ITextTarget * iTextTarget);

	/**
	Driver for flattening story endnotes. Determines which story we are interested in.
	@param iTextTarget IN identifies the story we are interested in.
	@return kFailure on error.
	*/
	ErrorCode FlattenStoryEndnotes(ITextTarget * iTextTarget);

	/**
	Driver for converting the current selection to a endnote. iTextTarget identifies the insert position for the endnote reference
	character, and, potentially, the intial text of the endnote, if the selection has a length > 0.
	@param iTextTarget IN identifies the story/initial text we are interested in.
	@return kFailure on error.
	*/
	ErrorCode ConvertSelectionToEndnote(ITextTarget * iTextTarget);

private:
	/**
	Implementation for getting information about endnotes in the currently selected story.
	\li In the story, where is the endnote anchor point?
	\li What is the endnote content?
	@param iTextTarget IN identifies the story we are interested in.
	@return kFailure if problems are encountered.
	*/
	ErrorCode ExploreEndnotes(ITextModel * iTextModel);

	/**
	Takes all endnotes associated with a story and places them inline. i.e. the original endnote anchor
	character is replaced with the text from the endnote. Three operations are required to achieve this:
	\li we add parenthesis round the endnote contents
	\li move the endnote contents into the primary story thread.
	\li delete the reference character, this action also deletes the endnote.

	@param iTextModel IN the story with the endnotes to be inlined
	@return kFailure on error.
	@see IEndnoteSettings
	@see IEndnoteFacade
	*/
	ErrorCode FlattenStoryEndnotes(ITextModel * iTextModel);

	/**
	Delete all the endnotes found in the text model. Endnote deletion occurs as
	a side effect of deleting the endnote reference character in the text nodel.
	@param iTextModel IN the endnote we wish to delete.
	@return kFailure on error.
	*/
	ErrorCode DeleteAllStoryEndnotes(ITextModel * iTextModel);

	/**
	Delete the charatcer from the text model at the specified position.
	@param iTextModel IN the model to delete from.
	@param position IN the position to delete from.
	@return kFailure on error.
	*/
	ErrorCode DeleteStoryChar(ITextModel *iTextModel, const TextIndex position);

	/**
	Inserts a endnote into the text model, populates the endnote with text.
	There are two parts to adding a endnote;
	\li adding the anchor/reference character to the primary story thread,
	\li populating the endnote with text.

	@param endnoteText IN the text for the endnote.
	@param position IN the position the endnote is associated with.
	@param iTextModel IN the text model into which the endnote is to be inserted.
	@return kFailure on error, or if it is illegal to insert a endnote at the indicated position.
	*/
	ErrorCode InsertEndnote(ITextEditSuite *textEditSuite, const boost::shared_ptr<WideString>& endnoteText, TextIndex position, ITextModel *iTextModel);

	/**
	Converts the text in iTextModel identified with rangeData into a endnote for the same story.
	In order to achieve this, the method;
	\li inserts a endnote character into the primary story thread,
	\li creates a endnote associated with this reference character,
	\li copies the text from the primary story thread to the endnote using ITextUtils::QueryMoveStoryCommand
	@param iTextModel IN the model we want to manipulate.
	@param rangeData IN the range of text we wish to convert to a endnote
	@return kFailure on error, or if it is illegal to insert a endnote at the position indicated by the range.
	*/
	ErrorCode ConvertSelectionToEndnote(ITextTarget *iTextTarget, ITextModel * iTextModel, RangeData rangeData);

	/**
	Can we insert a endnote into the text model at the specified position?
	@param iTextModel IN the text model we wish to test
	@param position IN the position within the text model we wish to test
	@return kTrue if it is possible to insert a endnote into this text story thread, kFalse otherwise
	*/
	bool16 CanInsertEndnote(ITextModel *iTextModel, TextIndex position);

	/**
	Is there any endnote already present in the given range?
	@param iTextModel IN the text model we wish to test
	@param range IN the range within the text model we wish to test
	@return kTrue if there is an endnote in this range, kFalse otherwise
	*/
	bool16 AnyEndnotes(const ITextModel* model, const RangeData& range);

	/**
	For the story range, return the associated text.
	@param iTextModel IN the story of interest.
	@param position IN the starting text index.
	@param length IN the number of characters.
	@return the text associated with the story range, or an empty string on error.
	*/
	WideString GetTextFromStoryRange(ITextModel * iTextModel, TextIndex position, int32 length);

	/**
	Get the endnote separator as specified in the endnote settings.
	*/
	WideString GetEndnoteSeparator(IDataBase *iDataBase);

	/**
	Reduce the endnote range specified by start and span to remove the XML markers, endnote marker and endnote separator
	from the range.
	*/
	void GetRawEndnoteTextRange(int32 separatorLen, TextIndex &start, int32 &span);

	/**
	Is the given story an endnote story.
	@param iTextModel IN the story of interest.
	@return kTrue if this is an endnote story, kFalse otherwise.
	*/
	bool16 IsEndnoteStory(ITextModel *iTextModel);
};

/*

*/
bool16
SnpManipulateTextEndnotes::CanInsertEndnote(ITextModel *iTextModel, TextIndex position)
{
	bool16 canInsert = kFalse;
	do
	{
		// we cannot insert endnotes into an endnote story
		if (this->IsEndnoteStory(iTextModel))
		{
			break;
		}
		// is this operation possible?
		InterfacePtr<ITextStoryThread>	iTextStoryThread(iTextModel->QueryStoryThread(position));
		if (iTextStoryThread == nil)
		{
			ASSERT(iTextStoryThread);
			break;
		}

		InterfacePtr<IOwnedItem> ownedItem(::GetDataBase(iTextModel), iTextStoryThread->GetDictUID(), UseDefaultIID());
		if (ownedItem)
		{
			//Cannot insert in Footnote text or note text 
			if (::GetClass(ownedItem) == kFootnoteReferenceBoss || Utils<INoteDataUtils>()->IsNoteOwnedItem(::GetClass(ownedItem)))
				break;
		} 
		canInsert = kTrue;
	} while (kFalse);
	return canInsert;
}

/*
driver for converting a selection to a endnote.
*/
ErrorCode
SnpManipulateTextEndnotes::ConvertSelectionToEndnote(ITextTarget * iTextTarget) {
	ErrorCode result = kFailure;
	do {
		InterfacePtr<ITextFocus> iTextFocus(iTextTarget->QueryTextFocus());
		if (iTextFocus == nil) {
			ASSERT(iTextFocus);
			break;
		}

		InterfacePtr<ITextModel> iTextModel(iTextFocus->QueryModel());
		if (iTextModel == nil) {
			ASSERT(iTextModel);
			break;
		}

		RangeData rangeData = iTextFocus->GetCurrentRange();
		result = this->ConvertSelectionToEndnote(iTextTarget, iTextModel, rangeData);
	} while (kFalse);
	return result;
}


/*
In order to convert the selection, we need to;
\li insert the endnote character
\li insert the endnote
\li move the text from the primary thread to the newly created endnote
*/
ErrorCode
SnpManipulateTextEndnotes::ConvertSelectionToEndnote(ITextTarget *iTextTarget, ITextModel * iTextModel, RangeData rangeData) {
	ErrorCode result = kFailure;
	do {
		Utils<ITextUtils> iTextUtils;
		if (iTextUtils == nil) {
			ASSERT(iTextUtils);
			break;
		}
		// the operation can only proceed if no endnotes exist in the selection, and 
		// the rangedata represents a text type that can accept a endnote reference	
		if (AnyEndnotes(iTextModel, rangeData) || !this->CanInsertEndnote(iTextModel, rangeData.Start(nil)))
		{
			SNIPLOG("Focus either cannot include endnote reference, or has existing endnote reference");
			break;
		}

		// Step 1: Get hold of the selected text
		InterfacePtr<ISelectionManager> iSelectionManager(Utils<ISelectionUtils>()->QueryActiveSelection());
		if (iSelectionManager == nil) {
			ASSERT(iSelectionManager);
			break;
		}
		InterfacePtr<ITextMiscellanySuite> iTextMiscSuite(iSelectionManager, UseDefaultIID());
		if (iTextMiscSuite == nil) {
			ASSERT(iTextMiscSuite);
			break;
		}
		WideString selectedText;
		result = iTextMiscSuite->GetSelectedText(selectedText);
		if (result != kSuccess || selectedText.empty())
		{
			break;
		}

		// Step 2: Delete the selected text
		InterfacePtr<ITextEditSuite> iTextEditSuite(iSelectionManager, UseDefaultIID());
		if (iTextEditSuite == nil) {
			ASSERT(iTextEditSuite);
			break;
		}

		InterfacePtr<ITextFocus> iTextFocus(iTextTarget->QueryTextFocus());
		if (iTextFocus == nil) {
			ASSERT(iTextFocus);
			break;
		}

		InterfacePtr<ITextModelCmds> iTextModelCmds(iTextModel, UseDefaultIID());
		if (iTextModelCmds == nil) {
			ASSERT(iTextModelCmds);
			break;
		}

		// note: this behaviour is purposely distinct from that given in the UI, which inserts the endnote reference at the end of the selection
		TextIndex insertPoint = iTextFocus->GetStart(nil);

		InterfacePtr<ITextModel> iTextModel(iTextFocus->QueryModel());
		if (iTextModel == nil) {
			ASSERT(iTextModel);
			break;
		}
		SnpTextModelHelper    textCmdHelper;
		result = textCmdHelper.DeleteText(iTextModel, insertPoint, iTextFocus->Length());
		if (result != kSuccess)
			break;

		// Step 3: Now simply insert an endnote with this text
		boost::shared_ptr<WideString> theNewEndnote(new WideString(selectedText));
		result = this->InsertEndnote(iTextEditSuite, theNewEndnote, insertPoint, iTextModel);

	} while (kFalse);
	return result;
}

/*
delete a single character
*/
ErrorCode
SnpManipulateTextEndnotes::DeleteStoryChar(ITextModel *iTextModel, const TextIndex position) {
	ErrorCode result = kFailure;
	do {
		InterfacePtr<ITextModelCmds> iTextModelCmds(iTextModel, UseDefaultIID());
		if (iTextModelCmds == nil) {
			ASSERT(iTextModelCmds);
			break;
		}
		InterfacePtr<ICommand> iDeleteCmd(iTextModelCmds->DeleteCmd(position, 1));
		if (iDeleteCmd == nil) {
			ASSERT(iDeleteCmd);
			break;
		}
		result = CmdUtils::ProcessCommand(iDeleteCmd);
	} while (kFalse);
	return result;
}

/*
There are 3 things we need to do to flatten each endnote;
1. add parenthesis around the raw content of the endnote
2. move the raw content to the primary story thread
3. delete the endnote reference character in the primary story thread
*/
ErrorCode
SnpManipulateTextEndnotes::FlattenStoryEndnotes(ITextModel * iTextModel) {
	ErrorCode result = kFailure;
	do {
		Utils<ITextUtils> iTextUtils;
		if (iTextUtils == nil) {
			ASSERT(iTextUtils);
			break;
		}
		InterfacePtr<ITextModelCmds> iTextModelCmds(iTextModel, UseDefaultIID());
		if (iTextModelCmds == nil) {
			ASSERT(iTextModelCmds);
			break;
		}

		InterfacePtr<ISelectionManager> iSelectionManager(Utils<ISelectionUtils>()->QueryActiveSelection());
		if (iSelectionManager == nil) {
			ASSERT(iSelectionManager);
			break;
		}
		InterfacePtr<ITextSelectionSuite> selectionSuite(iSelectionManager, UseDefaultIID());
		InterfacePtr<ITextEditSuite> iTextEditSuite(iSelectionManager, UseDefaultIID());
		UIDRef sourceStoryRef(::GetDataBase(iTextModel), ::GetUID(iTextModel));

		// get the separator text from the document workspace
		WideString separatorString = this->GetEndnoteSeparator(::GetDataBase(iTextModel));
		int32 separatorStrWCharLen = separatorString.CharCount();

		OwnedItemDataList ownedItemList;

		iTextUtils->CollectOwnedItems(iTextModel, 0, iTextModel->GetPrimaryStoryThreadSpan() - 1, &ownedItemList);
		for (int32 i = ownedItemList.size() - 1; i >= 0; --i) {
			ErrorCode innerResult = kFailure;
			do
			{
				// filter for only references to endnotes
				if (ownedItemList[i].fClassID == kEndnoteAnchorBoss) {
					SNIPLOG("*** Inlining endnote at char position %d. ***", ownedItemList[i].fAt);
					InterfacePtr<IEndnoteReferenceData> iEndnoteReferenceData(::GetDataBase(iTextModel), ownedItemList[i].fUID, UseDefaultIID());
					if (!iEndnoteReferenceData)
						continue;
					InterfacePtr<IEndnoteTextRangeData>  iEndnoteTextRangeData(iEndnoteReferenceData->QueryEndnoteReference());
					if (!iEndnoteTextRangeData)
						continue;
					TextIndex    rangeStart = iEndnoteTextRangeData->GetStartTextIndex();
					int32 span = iEndnoteTextRangeData->GetEndTextIndex() - rangeStart;

					// Endnote text range contains XML markers at start and end - exclude them now. Also exclude endnote marker and separator
					this->GetRawEndnoteTextRange(separatorStrWCharLen, rangeStart, span);
					if (span < 0)
						break;

					InterfacePtr<ITextModel> iEndnoteTextModel(iEndnoteTextRangeData->QueryOwningStory());
					InterfacePtr<ITextModelCmds> iEndnoteTextModelCmds(iEndnoteTextModel, UseDefaultIID());
					if (iEndnoteTextModelCmds == nil) {
						ASSERT(iEndnoteTextModelCmds);
						break;
					}
					// left paren
					boost::shared_ptr<WideString>	leftParen(new WideString);
					leftParen->Append('(');
					InterfacePtr<ICommand> iInsertLCmd(iEndnoteTextModelCmds->InsertCmd(rangeStart, leftParen));
					if (iInsertLCmd == nil) {
						ASSERT(iInsertLCmd);
						break;
					}
					if (CmdUtils::ProcessCommand(iInsertLCmd) != kSuccess) {
						SNIPLOG("Could not insert left paren into endnote");
						break;
					}

					++span; //We added a left parenthesis, so overall span increases

					// right paren
					boost::shared_ptr<WideString>	rightParen(new WideString);
					rightParen->Append(')');
					InterfacePtr<ICommand> iInsertRCmd(iEndnoteTextModelCmds->InsertCmd(rangeStart + span, rightParen));
					if (iInsertRCmd == nil) {
						ASSERT(iInsertRCmd);
						break;
					}
					if (CmdUtils::ProcessCommand(iInsertRCmd) != kSuccess) {
						SNIPLOG("Could not insert right paren into endnote");
						break;
					}

					++span; //We added a right parenthesis, so overall span increases

					UIDRef storyUIDRef = ::GetUIDRef(iTextModel);
					UIDRef endnoteStoryUIDRef = ::GetUIDRef(iEndnoteTextModel);
					// work out the updated start and end positions
					TextIndex ownedlistAt = ownedItemList[i].fAt;

					// create a move command that will copy the text from the endnote to the position of the reference
					InterfacePtr<ICommand> iMoveStoryCmd(iTextUtils->QueryMoveStoryCommand(endnoteStoryUIDRef, storyUIDRef, Text::StoryRange(rangeStart, rangeStart + span), Text::StoryRange(ownedItemList[i].fAt + 1, ownedItemList[i].fAt + 1)));
					iMoveStoryCmd->SetItemList(UIDList(storyUIDRef));


					if (iMoveStoryCmd == nil) {
						ASSERT(iMoveStoryCmd);
						break;
					}
					if (CmdUtils::ProcessCommand(iMoveStoryCmd) != kSuccess)
					{
						SNIPLOG("Failed to move endnote text");
						break;
					}


					TextIndex ownedItemIndex = ownedItemList[i].fAt;
					InterfacePtr<ICommand> iDeleteCmd(iTextModelCmds->DeleteCmd(ownedItemIndex, 1));
					if (iDeleteCmd == nil) {
						ASSERT(iDeleteCmd);
						break;
					}

					if (CmdUtils::ProcessCommand(iDeleteCmd) == kFailure)
					{
						SNIPLOG("Failed to delete endnote reference character");
						break;
					}

					innerResult = kSuccess;

				} // if kEndnoteReferenceBoss
			} while (kFalse);
			if (innerResult == kFailure) {
				break;
			}
			else {
				result = kSuccess;
			}
		} // for each inline
	} while (kFalse);
	return result;
}

/*
flatten the endnotes associated with the text target
*/
ErrorCode
SnpManipulateTextEndnotes::FlattenStoryEndnotes(ITextTarget * iTextTarget) {
	ErrorCode result = kFailure;
	do {
		InterfacePtr<ITextFocus> iTextFocus(iTextTarget->QueryTextFocus());
		if (iTextFocus == nil) {
			ASSERT(iTextFocus);
			break;
		}

		InterfacePtr<ITextModel> iTextModel(iTextFocus->QueryModel());
		if (iTextModel == nil) {
			ASSERT(iTextModel);
			break;
		}

		int32 numOfCharsInPrimaryThread = iTextModel->GetPrimaryStoryThreadSpan() - 1;
		if (numOfCharsInPrimaryThread <= 0) {
			SNIPLOG("No endnotes found");
			result = kSuccess;
			break;
		}

		Utils<ITextUtils> iTextUtils;
		if (iTextUtils == nil) {
			ASSERT(iTextUtils);
			break;
		}

		if (AnyEndnotes(iTextModel, RangeData(0, iTextModel->GetPrimaryStoryThreadSpan() - 1))) {
			result = this->FlattenStoryEndnotes(iTextModel);
		}

	} while (false);
	return result;
}

/*
driver to delete all endnotes associated with the text target.
*/
ErrorCode
SnpManipulateTextEndnotes::DeleteStoryEndnotes(ITextTarget * iTextTarget) {
	ErrorCode result = kFailure;
	do {
		InterfacePtr<ITextFocus> iTextFocus(iTextTarget->QueryTextFocus());
		if (iTextFocus == nil) {
			ASSERT(iTextFocus);
			break;
		}

		InterfacePtr<ITextModel> iTextModel(iTextFocus->QueryModel());
		if (iTextModel == nil) {
			ASSERT(iTextModel);
			break;
		}

		Utils<ITextUtils> iTextUtils;
		if (iTextUtils == nil) {
			ASSERT(iTextUtils);
			break;
		}
		int32 numOfCharsInPrimaryThread = iTextModel->GetPrimaryStoryThreadSpan() - 1;
		if (numOfCharsInPrimaryThread <= 0) {
			SNIPLOG("No characters in primary thread");
			break;
		}
		if (AnyEndnotes(iTextModel, RangeData(0, iTextModel->GetPrimaryStoryThreadSpan() - 1))) {
			result = this->DeleteAllStoryEndnotes(iTextModel);
		}
		else
		{
			result = kSuccess;
		}
	} while (false);
	return result;
}

/*
deletes all endnotes in the story
*/
ErrorCode SnpManipulateTextEndnotes::DeleteAllStoryEndnotes(ITextModel * iTextModel)
{
	ErrorCode result = kFailure;
	do
	{
		Utils<ITextUtils> iTextUtils;
		if (iTextUtils == nil)
		{
			ASSERT(iTextUtils);
			break;
		}

		OwnedItemDataList ownedItemList;
		iTextUtils->CollectOwnedItems(iTextModel, 0, iTextModel->GetPrimaryStoryThreadSpan() - 1, &ownedItemList);
		bool16 abortLoop = kFalse;
		for (int32 i = ownedItemList.size() - 1; i >= 0; --i)
		{
			// filter for only references to endnotes
			if (ownedItemList[i].fClassID == kEndnoteAnchorBoss)
			{
				SNIPLOG("*** Deleting endnote at char position %d. ***", ownedItemList[i].fAt);
				if (this->DeleteStoryChar(iTextModel, ownedItemList[i].fAt) == kFailure)
				{
					abortLoop = kTrue;
					break;
				}
			}
		}
		result = abortLoop ? kFailure : kSuccess;
	} while (false);

	return result;
}

/*
insert a endnote with the reference position being identified by the text target
*/
ErrorCode
SnpManipulateTextEndnotes::InsertEndnote(ITextTarget * iTextTarget, const boost::shared_ptr<WideString>& endnoteString) {
	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISelectionManager> iSelectionManager(Utils<ISelectionUtils>()->QueryActiveSelection());
		if (iSelectionManager == nil) {
			ASSERT(iSelectionManager);
			break;
		}
		InterfacePtr<ITextEditSuite> iTextEditSuite(iSelectionManager, UseDefaultIID());
		if (iTextEditSuite == nil) {
			ASSERT(iTextEditSuite);
			break;
		}
		// make sure the operation is valid
		// the suite supports this test, however there is not existing test for the model, 
		// see SnpManipulateTextEndnotes::CanInsertEndnote for an example of how to achieve this
		if ((iTextEditSuite == nil) || !iTextEditSuite->CanInsertEndnote()) {
			SNIPLOG("Can't insert endnote here");
			break;
		}


		InterfacePtr<ITextFocus> iTextFocus(iTextTarget->QueryTextFocus());
		if (iTextFocus == nil) {
			ASSERT(iTextFocus);
			break;
		}

		// note: this behaviour is purposely distinct from that given in the UI, which inserts the endnote reference at the end of the selection
		TextIndex insertPoint = iTextFocus->GetStart(nil);

		InterfacePtr<ITextModel> iTextModel(iTextFocus->QueryModel());
		if (iTextModel == nil) {
			ASSERT(iTextModel);
			break;
		}
		result = this->InsertEndnote(iTextEditSuite, endnoteString, insertPoint, iTextModel);
	} while (false);
	return result;
}

/*
Assuming adding a endnote is a valid operation, there are three parts to adding a endnote
* adding the anchor/reference character to the primary story thread,
* creating the endnote itself and
* populating the endnote with text.
*/
ErrorCode
SnpManipulateTextEndnotes::InsertEndnote(ITextEditSuite *iTextEditSuite, const boost::shared_ptr<WideString>& endnoteText, TextIndex position, ITextModel *iTextModel) {
	ErrorCode result = kFailure;
	do {

		if (this->CanInsertEndnote(iTextModel, position) == kFalse)
		{
			SNIPLOG("Cannot insert endnote at this focus");
			break;
		}

		// Step 1: Insert the endnote marker and create a blank endnote range. Focus will be at the endnote range at this point.
		result = iTextEditSuite->InsertEndnote();
		if (result != kSuccess)
			return result;

		// Step 2: Insert the actual endnote text
		SNIPLOG("Adding %s", PMString(*endnoteText.get()).GetPlatformString().c_str());
		result = iTextEditSuite->InsertText(*endnoteText.get());
		if (result != kSuccess)
			return result;

		// Step 3: Return to original selection
		InterfacePtr<ITextSelectionSuite> selectionSuite(iTextEditSuite, UseDefaultIID());

		UIDRef sourceStoryRef(::GetDataBase(iTextModel), ::GetUID(iTextModel));
		RangeData range(position, RangeData::kLeanBack);

		selectionSuite->SetTextSelection(sourceStoryRef, range, Selection::kScrollIntoView, nil);
		result = kSuccess;
	} while (false);

	return result;
}

/* Called with a text target, pulls out the text model from the target
*/
ErrorCode
SnpManipulateTextEndnotes::ExploreEndnotes(ITextTarget * iTextTarget) {
	ErrorCode result = kFailure;
	do {
		Utils<ITextUtils> iTextUtils;
		if (iTextUtils == nil) {
			ASSERT(iTextUtils);
			break;
		}

		InterfacePtr<ITextModel> iTextModel(iTextTarget->QueryTextModel());
		if (iTextModel == nil) {
			ASSERT(iTextModel);
			break;
		}
		int32 primarySpan = iTextModel->GetPrimaryStoryThreadSpan() - 1;
		if (primarySpan == 0) {
			result = kSuccess;
			break;
		}
		if (!this->IsEndnoteStory(iTextModel))
		{
			if (AnyEndnotes(iTextModel, RangeData(0, primarySpan))) {
				result = this->ExploreEndnotes(iTextModel);
			}
		}
	} while (kFalse);
	return result;
}


/* Called with a text target, pulls out the text model from the target
*/
ErrorCode
SnpManipulateTextEndnotes::ExploreEndnotes(ITextModel * iTextModel) {
	ErrorCode result = kFailure;
	do {
		Utils<ITextUtils> iTextUtils;
		if (iTextUtils == nil) {
			ASSERT(iTextUtils);
			break;
		}

		// Get the endnote separator string length - needed later to adjust endnote text
		WideString separatorString = this->GetEndnoteSeparator(::GetDataBase(iTextModel));
		int32 separatorStrWCharLen = separatorString.CharCount();

		OwnedItemDataList ownedItemList;
		int32 primarySpan = iTextModel->GetPrimaryStoryThreadSpan() - 1;
		if (primarySpan == 0) {
			result = kSuccess;
			break;
		}
		iTextUtils->CollectOwnedItems(iTextModel, 0, primarySpan, &ownedItemList);
		bool16 abortLoop = kFalse;
		for (int32 i = 0; i<ownedItemList.size(); i++) {
			// filter for only references to endnotes
			if (ownedItemList[i].fClassID == kEndnoteAnchorBoss) {
				SNIPLOG("*** Endnote found at char position %d. ***", ownedItemList[i].fAt);

				InterfacePtr<IEndnoteReferenceData> iEndnoteReferenceData(::GetDataBase(iTextModel), ownedItemList[i].fUID, UseDefaultIID());
				if (!iEndnoteReferenceData)
					continue;
				InterfacePtr<IEndnoteTextRangeData>  iEndnoteTextRangeData(iEndnoteReferenceData->QueryEndnoteReference());
				if (!iEndnoteTextRangeData)
					continue;
				TextIndex    rangeStart = iEndnoteTextRangeData->GetStartTextIndex();
				int32 span = iEndnoteTextRangeData->GetEndTextIndex() - rangeStart;

				// Endnote text range contains XML markers at start and end - exclude them now. Also exclude endnote marker and separator
				this->GetRawEndnoteTextRange(separatorStrWCharLen, rangeStart, span);
				if (span < 0)
				{
					abortLoop = kTrue;
					break;
				}
				SNIPLOG("Contents:");
				InterfacePtr<ITextModel> iEndnoteTextModel(iEndnoteTextRangeData->QueryOwningStory());
				SNIPLOG(PMString(this->GetTextFromStoryRange(iEndnoteTextModel, rangeStart, span)).GetPlatformString().c_str());
			}
		}
		SNIPLOG("*************************");
		result = abortLoop ? kFailure : kSuccess;
	} while (kFalse);
	return result;
}


WideString SnpManipulateTextEndnotes::GetTextFromStoryRange(ITextModel * iTextModel, TextIndex position, int32 length) {
	WideString retval("");
	do {
		InterfacePtr<IComposeScanner> iComposeScanner(iTextModel, UseDefaultIID());
		if (iComposeScanner == nil)
		{
			ASSERT(iComposeScanner);
			break;
		}

		iComposeScanner->CopyText(position, length, &retval);
	} while (false);
	return retval;
}

void SnpManipulateTextEndnotes::GetRawEndnoteTextRange(int32 separatorLen, TextIndex &start, int32 &span)
{
	// Blindly adjusts the input values to remove markers. Does not validate input
	// Endnote text range contains XML markers at start and end - exclude them now. Also exclude endnote marker and separator
	++start; // excluding start XML marker
	++start; // excluding the endnote marker character as well
	start += separatorLen; //excluding the separator as well

	span -= 3; //excluding both start and end XML markers and the endnote marker as well
	span -= separatorLen; //excluding the separartor as well
}

bool16 SnpManipulateTextEndnotes::IsEndnoteStory(ITextModel * iTextModel)
{
	if (::GetClass(iTextModel) == kEndnoteStoryBoss)
		return kTrue;
	else
		return kFalse;
}

WideString SnpManipulateTextEndnotes::GetEndnoteSeparator(IDataBase *iDataBase)
{
	WideString separatorString;
	do
	{
		if (iDataBase == nil) {
			ASSERT(iDataBase);
			break;
		}
		InterfacePtr<IDocument> iDocument(iDataBase, iDataBase->GetRootUID(), IID_IDOCUMENT);
		if (iDocument == nil) {
			ASSERT(iDocument);
			break;
		}
		InterfacePtr<IEndnoteSettings> iEndnoteSettings(iDocument->GetDocWorkSpace(), UseDefaultIID());
		if (iEndnoteSettings == nil) {
			ASSERT(iEndnoteSettings);
			break;
		}

		Utils<Facade::IEndnoteFacade> iEndnoteFacade;
		if (iEndnoteFacade == nil) {
			ASSERT(iEndnoteFacade);
			break;
		}

		separatorString = iEndnoteFacade->GetEndnoteSeparator(iEndnoteSettings);
	} while (false);

	return separatorString;
}

bool16 SnpManipulateTextEndnotes::AnyEndnotes(const ITextModel* model, const RangeData& range)
{
	int32 start = range.Start(nil);
	int32 length = range.Length();

	ASSERT(start >= 0 && length >= 0);
	if (start < 0 || length <= 0)                        // Disallow insertion points also (they can't, by definition, contain footnotes) 
		return kFalse;

	// Collect all the owned items for this story. 
	int32 storyLen = model->GetPrimaryStoryThreadSpan();

	if (start + length > storyLen)                    // Footnotes only in primary story. 
		return kFalse;

	OwnedItemDataList oiList;
	InterfacePtr<IItemStrand> itemStrand(static_cast<IItemStrand*>(model->QueryStrand(kOwnedItemStrandBoss, IItemStrand::kDefaultIID)));
	itemStrand->CollectOwnedItems(start, length, &oiList);

	for (int32 i = 0; i < oiList.size(); i++)
	{
		if (oiList[i].fClassID == kEndnoteAnchorBoss)
			return kTrue;
	}

	return kFalse;
} 

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
// includes for framework hooks
#include "IStoryList.h"
#include "IDocument.h"
#include "Utils.h"

/** Makes the snippet SnpManipulateTextEndnotes available to the SnippetRunner framework.

@ingroup sdk_snippet_run

*/
class _SnpRunnerManipulateTextEndnotes : public SnpRunnable
{
public:
	// SnippetRunner framework hooks.

	/** Constructor.
	*/
	_SnpRunnerManipulateTextEndnotes();

	/** Destructor.
	*/
	virtual				~_SnpRunnerManipulateTextEndnotes();

	/** Return kTrue if the snippet can run.
	@param iSnpRunnableContext see ISnpRunnableContext for documentation.
	@return kTrue if snippet can run, kFalse otherwise
	*/
	bool16				CanRun(ISnpRunnableContext* iSnpRunnableContext);

	/** Run the snippet.
	@param iSnpRunnableContext see ISnpRunnableContext for documentation.
	@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode			Run(ISnpRunnableContext* iSnpRunnableContext);

	/**
	get the snippet context
	@return eSnpRunContextType for this snippet
	*/
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void) { return ISnipRunSuite::kSnpRunTextTargetContext; }
};
/* Constructor
*/
_SnpRunnerManipulateTextEndnotes::_SnpRunnerManipulateTextEndnotes() : SnpRunnable("ManipulateTextEndnotes")
{
	this->SetDescription("Explore, modify, create or delete endnotes.");
	this->SetPreconditions("Valid text story");
	this->SetCategories("sdk_snippet, sdk_text");
}

/* Destructor
*/
_SnpRunnerManipulateTextEndnotes::~_SnpRunnerManipulateTextEndnotes()
{
}

/*
*/
bool16 _SnpRunnerManipulateTextEndnotes::CanRun(ISnpRunnableContext* iSnpRunnableContext)
{
	bool16 result = kTrue;
	InterfacePtr<ITextTarget> iTextTarget(iSnpRunnableContext, UseDefaultIID());
	if (iTextTarget == nil) {
		result = kFalse;
	}
	return result;
}


/*
*/
ErrorCode _SnpRunnerManipulateTextEndnotes::Run(ISnpRunnableContext* iSnpRunnableContext)
{
	ErrorCode status = kFailure;
	do {
		SnpManipulateTextEndnotes instance;

		K2Vector<PMString> choices;
		choices.push_back(PMString("Explore endnotes"));
		choices.push_back(PMString("Insert endnote"));
		choices.push_back(PMString("Delete endnotes"));
		choices.push_back(PMString("Flatten endnotes"));
		choices.push_back(PMString("Convert selection to endnote"));

		enum
		{
			kExploreEndnotes, kInsertEndnote, kDeleteEndnotes, kFlattenEndnotes, kSelectionToEndnote
		};

		Utils<ISnipRunParameterUtils> iParameterUtils;
		int32 choiceScope = iParameterUtils->GetChoice("Endnote operation?", choices);
		if (iParameterUtils->WasDialogCancelled())
		{
			break;
		}

		InterfacePtr<ITextTarget> iTextTarget(iSnpRunnableContext, UseDefaultIID());
		if (iTextTarget == nil) {
			break;
		}

		switch (choiceScope)
		{
		case kExploreEndnotes:
		{
			status = instance.ExploreEndnotes(iTextTarget);
			break;
		}
		case kInsertEndnote:
		{
			PMString endnoteString = iParameterUtils->GetPMString("Text for endnote", "");
			if (iParameterUtils->WasDialogCancelled()) {
				break;
			}
			const boost::shared_ptr<WideString> endnoteStringWS(new WideString(endnoteString));
			status = instance.InsertEndnote(iTextTarget, endnoteStringWS);
			break;
		}
		case kDeleteEndnotes:
		{
			status = instance.DeleteStoryEndnotes(iTextTarget);
			break;
		}
		case kFlattenEndnotes:
		{
			status = instance.FlattenStoryEndnotes(iTextTarget);
			break;
		}
		case kSelectionToEndnote:
		{
			status = instance.ConvertSelectionToEndnote(iTextTarget);
			break;
		}
		default:
			ASSERT("Choice not covered");
			break;
		}
	} while (false);
	return status;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerManipulateTextEndnotes instance_SnpRunnerManipulateTextEndnotes;
DEFINE_SNIPPET(_SnpRunnerManipulateTextEndnotes)

//End, SnpManipulateTextEndnotes.cpp

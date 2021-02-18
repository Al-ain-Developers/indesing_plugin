//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateTextFootnotes.cpp $
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
#include "IStoryList.h"
#include "ITextModel.h"
#include "IFootnoteFacade.h"
#include "IFootnoteSettings.h"
#include "IDocument.h"
#include "IOwnedItem.h"
#include "ITextStoryThreadDict.h"
#include "ITextAttrPositionMode.h"
#include "ITextFrameColumn.h"
#include "ITextParcelList.h"
#include "ITextUtils.h"
#include "IStoryList.h"
#include "IStoryService.h"
#include "ITextStoryThread.h"
#include "IComposeScanner.h"
#include "ITextFocus.h"
#include "ISelectionUtils.h"
#include "ITextEditSuite.h"
#include "ITextTarget.h"
#include "ITextModelCmds.h"
#include "IRangeData.h"
#include "IUIDData.h"
#include "IFootnoteNumber.h"

// General includes:
#include "WideString.h"
#include "Utils.h"
#include "CmdUtils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"


/** 
 *	\li How to access footnotes in a story.
 * 	\li	How to detect overset footnotes within a story.
 * 	\li	How to detect non-visible footnotes within a story (anchor character overset).
 * 	\li	How to inspect the content of footnotes within a story.
 *	\li How to create a footnote within a story.
 *	\li How to delete all footnotes in a story.
 *	\li How to flatten footnotes into a story.
 *	\li How to convert a selection into a footnote.
 * Footnotes are owned items, with distinct story threads. 
 *  
 * Select the story of interest (i.e. have a valid text selection or focus).
 * 
 * 	@ingroup sdk_snippet
 * 	@ingroup sdk_text
 */
class SnpManipulateTextFootnotes 
{
public:
	/** Constructor.
	 */
	SnpManipulateTextFootnotes() {}

	/** Destructor.
	 */
	virtual	~SnpManipulateTextFootnotes() {}

	/**
		Driver for dumping information about footnotes in the currently selected story.
		\li In the story, where is the footnote anchor point?
		\li Is the footnote visible (anchor point not overset)?
		\li What is the footnote content?
		@param iTextTarget IN identifies the story we are interested in.
		@return kFailure if problems are encountered.
	*/
	ErrorCode ExploreFootnotes(ITextTarget * iTextTarget);

	/** 
		Driver for inserting footnotes. Determines which story we are interested in.
		@param iTextTarget IN identifies the story we are interested in.
		@param footnoteString IN the string we wish to insert into the footnote
		@return kFailure on cancel of error.
	*/
	ErrorCode InsertFootnote(ITextTarget * iTextTarget, const boost::shared_ptr<WideString>& footnoteString);

	/**
		Driver for deleting footnotes in a story. Determines which story we are interested in.
		@param iTextTarget IN identifies the story we are interested in.
		@return kFailure on error.
	*/
	ErrorCode DeleteStoryFootnotes(ITextTarget * iTextTarget);

	/** 
		Driver for flattening story footnotes. Determines which story we are interested in.
		@param iTextTarget IN identifies the story we are interested in.
		@return kFailure on error.
	*/
	ErrorCode FlattenStoryFootnotes(ITextTarget * iTextTarget);

	/** 
		Driver for converting the current selection to a footnote. iTextTarget identifies the insert position for the footnote reference
		character, and, potentially, the intial text of the footnote, if the selection has a length > 0.
		@param iTextTarget IN identifies the story/initial text we are interested in.
		@return kFailure on error.
	*/
	ErrorCode ConvertSelectionToFootnote(ITextTarget * iTextTarget);

private:
	/**
		Implementation for getting information about footnotes in the currently selected story.
		\li In the story, where is the footnote anchor point?
		\li Is the footnote visible (anchor point not overset)?
		\li What is the footnote content?
		@param iTextTarget IN identifies the story we are interested in.
		@return kFailure if problems are encountered.
	*/
	ErrorCode ExploreFootnotes(ITextModel * iTextModel);

	/**
		Takes all footnotes associated with a story and places them inline. i.e. the original footnote anchor 
		charatcer is replaced with the text from the footnote. Three operations are required to achieve this:
		\li we add parenthesis round the footnote contents
		\li move the footnote contents into the primary story thread.
		\li delete the reference character, this action also deletes the footnote.
		
		@param iTextModel IN the story with the footnotes to be inlined
		@return kFailure on error.
		@see IFootnoteNumber
		@see IFootnoteSettings
		@see IFootnoteFacade
	*/
	ErrorCode FlattenStoryFootnotes(ITextModel * iTextModel);

	/** 
		For the story thread, return the associated text.
		@param iTextStoryThread IN the story thread of interest.
		@return the text associated with the story thread, or an empty string on error.
	*/
	WideString GetStoryThreadContents(ITextStoryThread * iTextStoryThread);

	/**
		Delete all the footnotes found in the text model. Footnote deletion occurs as
		a side effect of deleting the footnote reference character in the text nodel. 
		@param iTextModel IN the footnote we wish to delete.
		@return kFailure on error.
	*/
	ErrorCode DeleteAllStoryFootnotes(ITextModel * iTextModel);

	/** 
		Delete the charatcer from the text model at the specified position.
		@param iTextModel IN the model to delete from.
		@param position IN the position to delete from.
		@return kFailure on error.
	*/
	ErrorCode DeleteStoryChar(ITextModel *iTextModel, const TextIndex position);

	/**
		Inserts a footnote into the text model, populates the footnote with text.
		There are three parts to adding a footnote;
		\li adding the anchor/reference character to the primary story thread, 
		\li creating the footnote itself,
		\li populating the footnote with text.

		@param footnoteText IN the text for the footnote.
		@param position IN the position the footnote is associated with.
		@param iTextModel IN the text model into which the footnote is to be inserted.
		@return kFailure on error, or if it is illegal to insert a footnote at the indicated position.
		@see kCreateFootnoteCmdBoss
	*/
	ErrorCode InsertFootnote(const boost::shared_ptr<WideString>& footnoteText, TextIndex position, ITextModel *iTextModel);

	/** 
		Converts the text in iTextModel identified with rangeData into a footnote for the same story.
		In order to achieve this, the method;
		\li inserts a footnote character into the primary story thread,
		\li creates a footnote associated with this reference character,
		\li copies the text from the primary story thread to the footnote using ITextUtils::QueryMoveStoryCommand 
		@param iTextModel IN the model we want to manipulate.
		@param rangeData IN the range of text we wish to convert to a footnote
		@return kFailure on error, or if it is illegal to insert a footnote at the position indicated by the range.
	*/
	ErrorCode ConvertSelectionToFootnote(ITextModel * iTextModel, RangeData rangeData);
	
	/** 
		At the model level, you can insert a footnote into a story thread if it has a dictionary that
		supports the IFootnoteNumbering capability. While the interface is private, the interface ID 
		is not, allowing us to test the model for the capability.
		@param iTextStoryThreadDict IN the text story thread dictionary we wish to test
		@return kTrue if it is possible to insert a footnote into this text story thread, kFalse otherwise
	*/
	bool16 CanInsertFootnote(ITextStoryThreadDict * iTextStoryThreadDict);
	

	/** 
		Can we insert a footnote into the text model at the specified position?
		@param iTextModel IN the text model we wish to test
		@param position IN the position within the text model we wish to test
		@return kTrue if it is possible to insert a footnote into this text story thread, kFalse otherwise
	*/
	bool16 CanInsertFootnote(ITextModel *iTextModel, TextIndex position);
};

/*
 
*/
bool16 
SnpManipulateTextFootnotes::CanInsertFootnote(ITextModel *iTextModel, TextIndex position)
{
	bool16 canInsert = kFalse;
	do 
	{
		// is this operation possible?
		InterfacePtr<ITextStoryThread>	iTextStoryThread(iTextModel->QueryStoryThread(position));
		if (iTextStoryThread==nil)
		{
			ASSERT(iTextStoryThread);
			break;			
		}
		// get the thread dictionary
		InterfacePtr<ITextStoryThreadDict> iTextStoryThreadDict(UIDRef(::GetDataBase(iTextModel),iTextStoryThread->GetDictUID()),UseDefaultIID());

		if (iTextStoryThreadDict==nil)
		{
			ASSERT(iTextStoryThreadDict);
			break;			
		}
		
		canInsert = this->CanInsertFootnote(iTextStoryThreadDict); 
	} while(kFalse);
	return canInsert;
}

/*
	driver for converting a selection to a footnote. 
*/
ErrorCode 
SnpManipulateTextFootnotes::ConvertSelectionToFootnote(ITextTarget * iTextTarget){
	ErrorCode result = kFailure;
	do{
		InterfacePtr<ITextFocus> iTextFocus(iTextTarget->QueryTextFocus());
		if (iTextFocus == nil) {
			ASSERT(iTextFocus);
			break;
		}

		InterfacePtr<ITextModel> iTextModel(iTextFocus->QueryModel());
		if (iTextModel == nil){
			ASSERT(iTextModel);
			break;
		}

		RangeData rangeData = iTextFocus->GetCurrentRange();
		result = this->ConvertSelectionToFootnote(iTextModel,rangeData);		
	} while (kFalse);
	return result;
}


/* 
	In order to convert the selection, we need to;
	\li insert the footnote character
	\li insert the footnote
	\li move the text from the primary thread to the newly created footnote
*/
ErrorCode 
SnpManipulateTextFootnotes::ConvertSelectionToFootnote(ITextModel * iTextModel, RangeData rangeData){
	ErrorCode result = kFailure;
	do {
		Utils<ITextUtils> iTextUtils;
		if (iTextUtils == nil){
			ASSERT(iTextUtils);
			break;
		}
		// the operation can only proceed if no footnotes exist in the selection, and 
		// the rangedata represents a text type that can accept a footnote reference	
		if (iTextUtils->AnyFootnotes(iTextModel, rangeData) || !this->CanInsertFootnote(iTextModel,rangeData.Start(nil)))
		{
			SNIPLOG("Focus either cannot include footnote reference, or has existing footnote reference");
			break;
		}
		
		InterfacePtr<ITextModelCmds> iTextModelCmds(iTextModel, UseDefaultIID());
		if (iTextModelCmds == nil){
			ASSERT(iTextModelCmds);
			break;
		}

		// Step 1: Insert the footnote marker into the story.
		boost::shared_ptr<WideString>	markerText(new WideString);
		markerText->Append(kTextChar_FootnoteMarker);
		InterfacePtr<ICommand> iInsertCmd(iTextModelCmds->InsertCmd(rangeData.Start(nil), markerText));
		if (iInsertCmd == nil){
			ASSERT(iInsertCmd);
			break;
		}

		if (CmdUtils::ProcessCommand(iInsertCmd)!= kSuccess){
			break;
		}

		// Step 2: Create the footnote itself
		InterfacePtr<ICommand> iCreateFootnoteCmd(CmdUtils::CreateCommand(kCreateFootnoteCmdBoss));
		if (iCreateFootnoteCmd == nil){
			ASSERT(iCreateFootnoteCmd);
			break;
		}

		iCreateFootnoteCmd->SetItemList(UIDList(iTextModel));
	 	InterfacePtr<IRangeData> iRangeData(iCreateFootnoteCmd, UseDefaultIID());
		if (iRangeData == nil) {
			ASSERT(iRangeData);
			break;
		}

		// uses the position to insert
		iRangeData->Set(rangeData.Start(nil), rangeData.Start(nil));
		if (CmdUtils::ProcessCommand(iCreateFootnoteCmd)==kFailure){
			break;
		}

		// Step 3: Add the text to the footnote, first obtain the footnote reference
		// if we are here, we have inserted the footnote reference character, we now 
		// need to create a new range that reflects the character added.
		RangeData newRange(rangeData.Start(nil)+1,rangeData.End()+1,RangeData::kLeanForward);
		InterfacePtr<IUIDData> iUIDData(iCreateFootnoteCmd,UseDefaultIID());
		if (iUIDData == nil){
			ASSERT(iUIDData);
			break;
		}
	
		// grab the text story thread from the footnote
		InterfacePtr<ITextStoryThread> iFNTextStoryThread(iUIDData->GetRef(),UseDefaultIID());
		
		// the footnote comes prepacked with numbering, just add our text.
		TextIndex fStoryThreadEnd = iFNTextStoryThread->GetTextEnd();

		UIDRef storyUIDRef = ::GetUIDRef(iTextModel);

		// create a move command that will copy the text to a different point in the same story
		InterfacePtr<ICommand> iMoveStoryCmd(iTextUtils->QueryMoveStoryCommand(storyUIDRef,storyUIDRef,newRange,Text::StoryRange(fStoryThreadEnd-1, fStoryThreadEnd-1)));
		iMoveStoryCmd->SetItemList(UIDList(storyUIDRef));

			
		if (iMoveStoryCmd == nil){
			ASSERT(iMoveStoryCmd);
			break;
		}
		result = CmdUtils::ProcessCommand(iMoveStoryCmd);		
	} while (kFalse);
	return result;
}

/*
	delete a single character
*/
ErrorCode 
SnpManipulateTextFootnotes::DeleteStoryChar(ITextModel *iTextModel, const TextIndex position){
	ErrorCode result = kFailure;
	do {
		InterfacePtr<ITextModelCmds> iTextModelCmds(iTextModel, UseDefaultIID());
		if (iTextModelCmds == nil){
			ASSERT(iTextModelCmds);
			break;
		}
		InterfacePtr<ICommand> iDeleteCmd(iTextModelCmds->DeleteCmd(position, 1));
		if (iDeleteCmd == nil){
			ASSERT(iDeleteCmd);
			break;
		}
		result = CmdUtils::ProcessCommand(iDeleteCmd);
	} while(kFalse);
	return result;
}

/*
	There are 3 things we need to do to flatten each footnote;
	1. add parenthesis around the raw content of the footnote
	2. move the raw content to the primary story thread
	3. delete the footnote reference character in the primary story thread
*/
ErrorCode 
SnpManipulateTextFootnotes::FlattenStoryFootnotes(ITextModel * iTextModel){
	ErrorCode result = kFailure;
	do {
		Utils<ITextUtils> iTextUtils;
		if (iTextUtils == nil){
			ASSERT(iTextUtils);
			break;
		}
		InterfacePtr<ITextModelCmds> iTextModelCmds(iTextModel, UseDefaultIID());
		if (iTextModelCmds == nil){
			ASSERT(iTextModelCmds);
			break;
		}
		OwnedItemDataList ownedItemList;
		
		iTextUtils->CollectOwnedItems(iTextModel, 0, iTextModel->GetPrimaryStoryThreadSpan()-1, &ownedItemList);
		for (int32 i = ownedItemList.size()-1; i>=0;--i) { 
			ErrorCode innerResult = kFailure;
			do 
			{
				// filter for only references to footnotes
				if (ownedItemList[i].fClassID == kFootnoteReferenceBoss) {
					SNIPLOG("*** Inlining footnote at char position %d. ***",ownedItemList[i].fAt);

					InterfacePtr<ITextStoryThread> iTextStoryThread(UIDRef(::GetUIDRef(iTextModel).GetDataBase(),ownedItemList[i].fUID),UseDefaultIID());
					if (iTextStoryThread == nil){
						ASSERT(iTextStoryThread);
						break;
					}

					InterfacePtr<IOwnedItem> iOwnedItem(iTextStoryThread,UseDefaultIID());
					if (iOwnedItem == nil){
						ASSERT(iOwnedItem);
						break;
					}
					
					int32 numOfCharsInFootnote = iTextStoryThread->GetTextSpan()-1;
					
					// what we would like to do is ignore the numbering information in the contents of the footnote
					// when doing the move. Our naive implementation assumes if there is enough characters in the thread
					// the numbering hasn't been modified.
					
					
					// get the numbering settings from the preferences, i.e. what should the numbering be?
					InterfacePtr<IFootnoteNumber> iFootnoteNumber(iTextStoryThread,UseDefaultIID());
					if (iFootnoteNumber == nil){
						ASSERT(iFootnoteNumber);
						break;
					}

					// get the separator text from the document workspace
					IDataBase* iDataBase = ::GetDataBase(iTextModel);
					if (iDataBase == nil){
						ASSERT(iDataBase);
						break;
					}
					InterfacePtr<IDocument> iDocument(iDataBase, iDataBase->GetRootUID(), IID_IDOCUMENT);
					if (iDocument == nil){
						ASSERT(iDocument);
						break;
					}
					InterfacePtr<IFootnoteSettings> iFootnoteSettings(iDocument->GetDocWorkSpace(),UseDefaultIID());
					if (iFootnoteSettings == nil){
						ASSERT(iFootnoteSettings);
						break;
					}

					PMString numberString;
					iFootnoteNumber->GetNumberString(IFootnoteNumber::kFootnoteReferenceInText,numberString);
					Utils<IFootnoteFacade> iFootnoteFacade;
					if (iFootnoteFacade == nil){
						ASSERT(iFootnoteFacade);
						break;
					}

					numberString.Append(iFootnoteFacade->GetFootnoteSeparator(iFootnoteSettings));
					
					int32 numberStrWCharLen = numberString.WCharLength();
					SNIPLOG("Footnote number is %s and its length is %d",numberString.GetPlatformString().c_str(),numberStrWCharLen);

					// if the footnote is large enough, assume the numbering hasn't been munged and strip it off.
					if (numOfCharsInFootnote<numberStrWCharLen){
						SNIPLOG("Malformed footer, has it been edited?");
						break;
					
					}

					// left paren
					boost::shared_ptr<WideString>	leftParen(new WideString);
					leftParen->Append('(');
					InterfacePtr<ICommand> iInsertLCmd(iTextModelCmds->InsertCmd(iTextStoryThread->GetTextStart()+numberStrWCharLen, leftParen));
					if (iInsertLCmd == nil){
						ASSERT(iInsertLCmd);
						break;
					}
					if (CmdUtils::ProcessCommand(iInsertLCmd)!= kSuccess){
						SNIPLOG("Could not insert left paren into footnote");
						break;
					}
					
					// right paren
					boost::shared_ptr<WideString>	rightParen(new WideString);
					rightParen->Append(')');
					InterfacePtr<ICommand> iInsertRCmd(iTextModelCmds->InsertCmd(iTextStoryThread->GetTextEnd()-1, rightParen));
					if (iInsertRCmd == nil){
						ASSERT(iInsertRCmd);
						break;
					}
					if (CmdUtils::ProcessCommand(iInsertRCmd)!= kSuccess){
						SNIPLOG("Could not insert right paren into footnote");
						break;
					}

					UIDRef storyUIDRef = ::GetUIDRef(iTextModel);

					// work out the updated start and end positions
					TextIndex footnoteStart = iTextStoryThread->GetTextStart();
					TextIndex footnoteEnd = iTextStoryThread->GetTextEnd()-1; // not interested int he EOS marker character
					TextIndex ownedlistAt = ownedItemList[i].fAt;
					
					// create a move command that will copy the text from the footnote to the position of the reference
					InterfacePtr<ICommand> iMoveStoryCmd(iTextUtils->QueryMoveStoryCommand(storyUIDRef,storyUIDRef,Text::StoryRange(footnoteStart+numberStrWCharLen,footnoteEnd),Text::StoryRange(ownedItemList[i].fAt, ownedItemList[i].fAt)));
					iMoveStoryCmd->SetItemList(UIDList(storyUIDRef));

						
					if (iMoveStoryCmd == nil){
						ASSERT(iMoveStoryCmd);
						break;
					}
					if (CmdUtils::ProcessCommand(iMoveStoryCmd)!=kSuccess)
					{
						SNIPLOG("Failed to move footnote text");
						break;
					}


					TextIndex ownedItemIndex = iOwnedItem->GetTextIndex();
					InterfacePtr<ICommand> iDeleteCmd(iTextModelCmds->DeleteCmd(ownedItemIndex,1));
					if (iDeleteCmd == nil){
						ASSERT(iDeleteCmd);
						break;
					}

					if(CmdUtils::ProcessCommand(iDeleteCmd) == kFailure)
					{
						SNIPLOG("Failed to delete footnote reference character");
						break;
					}

					innerResult = kSuccess;

				} // if kFootnoteReferenceBoss
			} while (kFalse);
			if (innerResult == kFailure){
				break;
			}
			else {
				result = kSuccess;
			}
		} // for each inline
	} while(kFalse);
	return result;
}

/*
	flatten the footnotes associated with the text target
*/
ErrorCode 
SnpManipulateTextFootnotes::FlattenStoryFootnotes(ITextTarget * iTextTarget){
	ErrorCode result = kFailure;
	do{
		InterfacePtr<ITextFocus> iTextFocus(iTextTarget->QueryTextFocus());
		if (iTextFocus == nil) {
			ASSERT(iTextFocus);
			break;
		}

		InterfacePtr<ITextModel> iTextModel(iTextFocus->QueryModel());
		if (iTextModel == nil){
			ASSERT(iTextModel);
			break;
		}

		int32 numOfCharsInPrimaryThread = iTextModel->GetPrimaryStoryThreadSpan()-1;
		if (numOfCharsInPrimaryThread <=0){
			SNIPLOG("No footnotes found");
			result = kSuccess;
			break;
		}

		Utils<ITextUtils> iTextUtils;
		if (iTextUtils == nil){
			ASSERT(iTextUtils);
			break;
		}

		if (iTextUtils->AnyFootnotes(iTextModel, RangeData(0,iTextModel->GetPrimaryStoryThreadSpan()-1))){
			result = this->FlattenStoryFootnotes(iTextModel);
		}

	} while(false);
	return result;
}

/*
	driver to delete all footnotes associated with the text target. 
*/
ErrorCode 
SnpManipulateTextFootnotes::DeleteStoryFootnotes(ITextTarget * iTextTarget){
	ErrorCode result = kFailure;
	do {
		InterfacePtr<ITextFocus> iTextFocus(iTextTarget->QueryTextFocus());
		if (iTextFocus == nil) {
			ASSERT(iTextFocus);
			break;
		}

		InterfacePtr<ITextModel> iTextModel(iTextFocus->QueryModel());
		if (iTextModel == nil){
			ASSERT(iTextModel);
			break;
		}

		Utils<ITextUtils> iTextUtils;
		if (iTextUtils == nil){
			ASSERT(iTextUtils);
			break;
		}
		int32 numOfCharsInPrimaryThread = iTextModel->GetPrimaryStoryThreadSpan()-1;
		if (numOfCharsInPrimaryThread <=0){
			SNIPLOG("No characters in primary thread");
			break;
		}
		if (iTextUtils->AnyFootnotes(iTextModel, RangeData(0,iTextModel->GetPrimaryStoryThreadSpan()-1))){
			result = this->DeleteAllStoryFootnotes(iTextModel);
		}
		else 
		{
		result = kSuccess;
		}
	}while (false);
	return result;
}

/*
	deletes all footnotes in the story
*/
ErrorCode SnpManipulateTextFootnotes::DeleteAllStoryFootnotes(ITextModel * iTextModel)
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
		iTextUtils->CollectOwnedItems(iTextModel, 0, iTextModel->GetPrimaryStoryThreadSpan()-1, &ownedItemList);
		bool16 abortLoop = kFalse;
		for (int32 i = ownedItemList.size()-1; i>=0;--i)
		{ 
			// filter for only references to footnotes
			if (ownedItemList[i].fClassID == kFootnoteReferenceBoss)
			{
				SNIPLOG("*** Deleting footnote at char position %d. ***",ownedItemList[i].fAt);
				if (this->DeleteStoryChar(iTextModel,ownedItemList[i].fAt)==kFailure)
				{
					abortLoop = kTrue;
					break;
				}
			}
		}
		result = abortLoop ? kFailure : kSuccess;
	}
	while(false);
	
	return result;
}

/*
	insert a footnote with the reference position being identified by the text target
*/
ErrorCode 
SnpManipulateTextFootnotes::InsertFootnote(ITextTarget * iTextTarget, const boost::shared_ptr<WideString>& footnoteString){
	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISelectionManager> iSelectionManager(Utils<ISelectionUtils>()->QueryActiveSelection());
		if (iSelectionManager==nil){
			ASSERT(iSelectionManager);
			break;
		}
		InterfacePtr<ITextEditSuite> iTextEditSuite(iSelectionManager, UseDefaultIID());
		if (iTextEditSuite==nil){
			ASSERT(iTextEditSuite);
			break;
		}
		// make sure the operation is valid
		// the suite supports this test, however there is not existing test for the model, 
		// see SnpManipulateTextFootnotes::CanInsertFootnote for an example of how to achieve this
		if ((iTextEditSuite == nil) || !iTextEditSuite->CanInsertFootnote()){
			SNIPLOG("Can't insert footnote here");
			break;
		}


		InterfacePtr<ITextFocus> iTextFocus(iTextTarget->QueryTextFocus());
		if (iTextFocus == nil) {
			ASSERT(iTextFocus);
			break;
		}
		
		// note: this behaviour is purposely distinct from that given in the UI, which inserts the footnote reference at the end of the selection
		TextIndex insertPoint = iTextFocus->GetStart(nil);
		
		InterfacePtr<ITextModel> iTextModel(iTextFocus->QueryModel());
		if (iTextModel == nil){
			ASSERT(iTextModel);
			break;
		}
		result = this->InsertFootnote(footnoteString,insertPoint,iTextModel);
	} while(false);
	return result;
}

/*
	Assuming adding a footnote is a valid operation, there are three parts to adding a footnote
	* adding the anchor/reference character to the primary story thread, 
	* creating the footnote itself and 
	* populating the footnote with text.
*/
ErrorCode 
SnpManipulateTextFootnotes::InsertFootnote(const boost::shared_ptr<WideString>& footnoteText, TextIndex position, ITextModel *iTextModel){
	ErrorCode result = kFailure;
	do {
		
		if (this->CanInsertFootnote(iTextModel,position) == kFalse)
		{
			SNIPLOG("Cannot insert footnote at this focus");
			break;
		}

		// Step 1: Insert the footnote marker into the story.
		boost::shared_ptr<WideString>	markerText(new WideString);
		markerText->Append(kTextChar_FootnoteMarker);

		InterfacePtr<ITextModelCmds> iTextModelCmds(iTextModel, UseDefaultIID());
		if (iTextModelCmds == nil){
			ASSERT(iTextModelCmds);
			break;
		}
		InterfacePtr<ICommand> iInsertCmd(iTextModelCmds->InsertCmd(position, markerText));
		if (iInsertCmd == nil){
			ASSERT(iInsertCmd);
			break;
		}
		if (CmdUtils::ProcessCommand(iInsertCmd)!= kSuccess){
			break;
		}

		// Step 2: Create the footnote itself
		InterfacePtr<ICommand> iCreateFootnoteCmd(CmdUtils::CreateCommand(kCreateFootnoteCmdBoss));
		if (iCreateFootnoteCmd == nil){
			ASSERT(iCreateFootnoteCmd);
			break;
		}

		iCreateFootnoteCmd->SetItemList(UIDList(iTextModel));
	 	InterfacePtr<IRangeData> iRangeData(iCreateFootnoteCmd, UseDefaultIID());
		if (iRangeData == nil) {
			ASSERT(iRangeData);
			break;
		}

		// uses the position to insert
		iRangeData->Set(position, position);

		if (CmdUtils::ProcessCommand(iCreateFootnoteCmd)==kFailure){
			break;
		}

		// Step 3: Add the text to the footnote, first obtain the footnote reference
		InterfacePtr<IUIDData> iUIDData(iCreateFootnoteCmd,UseDefaultIID());
		if (iUIDData == nil){
			ASSERT(iUIDData);
			break;
		}
		
		// grab the text story thread from the footnote
		InterfacePtr<ITextStoryThread> iFNTextStoryThread(iUIDData->GetRef(),UseDefaultIID());
		
		// the footnote comes prepacked with numbering, just add our text.
		TextIndex fStoryThreadEnd = iFNTextStoryThread->GetTextEnd();

		SNIPLOG("Adding %s",PMString(*footnoteText.get()).GetPlatformString().c_str());
		InterfacePtr<ICommand> iInsert2Cmd(iTextModelCmds->InsertCmd(fStoryThreadEnd-1, footnoteText));
		if (iInsert2Cmd == nil){
			ASSERT(iInsert2Cmd);
			break;
		}
		if (CmdUtils::ProcessCommand(iInsert2Cmd)!= kSuccess){
			break;
		}

		result = kSuccess;
	}while(false);
	return result;
}

/*
	Can we insert a footnote into this text story thread?
*/
bool16 
SnpManipulateTextFootnotes::CanInsertFootnote(ITextStoryThreadDict * iTextStoryThreadDict){
	bool16 retval = kTrue;
	InterfacePtr<IPMUnknown> iFootnoteNumbering(iTextStoryThreadDict, IID_IFOOTNOTENUMBERING);
	if (iFootnoteNumbering == nil)
	{
		retval = kFalse;
	}
	return retval;
}


/* Called with a text target, pulls out the text model from the target
*/
ErrorCode 
SnpManipulateTextFootnotes::ExploreFootnotes(ITextTarget * iTextTarget){
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
		int32 primarySpan = iTextModel->GetPrimaryStoryThreadSpan()-1;
		if (primarySpan == 0) {
			result = kSuccess;
			break;
		}
		if (iTextUtils->AnyFootnotes(iTextModel, RangeData(0,primarySpan))){
			result = this->ExploreFootnotes(iTextModel);
		}
	} while (kFalse);
	return result;
}

		
/* Called with a text target, pulls out the text model from the target
*/
ErrorCode 
SnpManipulateTextFootnotes::ExploreFootnotes(ITextModel * iTextModel){
	ErrorCode result = kFailure;
	do {
		Utils<ITextUtils> iTextUtils;
		if (iTextUtils == nil) {
			ASSERT(iTextUtils);
			break;
		}
		OwnedItemDataList ownedItemList;
		int32 primarySpan = iTextModel->GetPrimaryStoryThreadSpan()-1;
		if (primarySpan == 0) {
			result = kSuccess;
			break;
		}
		iTextUtils->CollectOwnedItems(iTextModel, 0, primarySpan, &ownedItemList);
		bool16 abortLoop = kFalse;
		for (int32 i = 0; i<ownedItemList.size(); i++) {
			// filter for only references to footnotes
			if (ownedItemList[i].fClassID == kFootnoteReferenceBoss) {
				SNIPLOG("*** Footnote found at char position %d. ***",ownedItemList[i].fAt);

				InterfacePtr<ITextStoryThread> iTextStoryThread(UIDRef(::GetUIDRef(iTextModel).GetDataBase(),ownedItemList[i].fUID),UseDefaultIID());
				if (iTextStoryThread == nil)
				{
					abortLoop = kTrue;
					ASSERT(iTextStoryThread);
					break;
				}
				// determine visibility of footnote, it can either be fully visible, overset or
				// invisible (if the anchor character is overset 
				// if the owned item has no associated text frame, the footnote is not visible)
				InterfacePtr<IOwnedItem> iOwnedItem(iTextStoryThread,UseDefaultIID());
				if (iOwnedItem == nil)
				{
					abortLoop = kTrue;
					ASSERT(iOwnedItem);
					break;
				}
				
				InterfacePtr<ITextFrameColumn> iTextFrameColumn(iOwnedItem->QueryFrame());
				if (iTextFrameColumn == nil){
					SNIPLOG("Footnote not visible");
				}
				else {
					// to determine whether the footnote is overset, take a peek at the last character
					TextIndex fStoryThreadStart = iTextStoryThread->GetTextStart();
					InterfacePtr<ITextParcelList> iTextParcelList(iTextModel->QueryTextParcelList(fStoryThreadStart)); 
					if (iTextParcelList == nil)
					{
						abortLoop = kTrue;
						ASSERT(iTextParcelList);
						break;
					}
					if (iTextParcelList->GetIsOverset())  {
						SNIPLOG("Footnote overset");
					}
				}

				SNIPLOG("Contents:");
				SNIPLOG(PMString(this->GetStoryThreadContents(iTextStoryThread)).GetPlatformString().c_str());
			}
		}
		SNIPLOG("*************************");
		result = abortLoop ? kFailure:kSuccess;
	} while (kFalse);
	return result;
}

		
WideString SnpManipulateTextFootnotes::GetStoryThreadContents(ITextStoryThread * iTextStoryThread){
	WideString retval("");
	do {
		InterfacePtr<ITextModel> iTextModel(iTextStoryThread->QueryTextModel());
		if (iTextModel == nil)
		{
			ASSERT(iTextModel);
			break;
		}
		
		InterfacePtr<IComposeScanner> iComposeScanner(iTextModel,UseDefaultIID());
		if (iComposeScanner == nil)
		{
			ASSERT(iComposeScanner);
			break;
		}
		// to get the contents of the story thread, we use IStoryService
		TextIndex fStoryThreadStart = iTextStoryThread->GetTextStart();
		int32 fStoryThreadSpan = iTextStoryThread->GetTextSpan();

		iComposeScanner->CopyText(fStoryThreadStart,fStoryThreadSpan,&retval);
	} while (false);
	return retval;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
// includes for framework hooks
#include "IStoryList.h"
#include "IDocument.h"
#include "Utils.h"

/** Makes the snippet SnpManipulateTextFootnotes available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerManipulateTextFootnotes : public SnpRunnable
{
	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerManipulateTextFootnotes();

		/** Destructor.
		 */
		virtual				~_SnpRunnerManipulateTextFootnotes();

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
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTextTargetContext;}
};
/* Constructor
*/
_SnpRunnerManipulateTextFootnotes::_SnpRunnerManipulateTextFootnotes() : SnpRunnable("ManipulateTextFootnotes")
{
	this->SetDescription("Explore, modify, create or delete footnotes.");
	this->SetPreconditions("Valid text story");
	this->SetCategories("sdk_snippet, sdk_text");
}

/* Destructor
*/
_SnpRunnerManipulateTextFootnotes::~_SnpRunnerManipulateTextFootnotes()
{
}

/*
*/
bool16 _SnpRunnerManipulateTextFootnotes::CanRun(ISnpRunnableContext* iSnpRunnableContext)
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
ErrorCode _SnpRunnerManipulateTextFootnotes::Run(ISnpRunnableContext* iSnpRunnableContext)
{
	ErrorCode status = kFailure;
	do {
		SnpManipulateTextFootnotes instance;

		K2Vector<PMString> choices;
		choices.push_back(PMString("Explore footnotes"));
		choices.push_back(PMString("Insert footnote"));
		choices.push_back(PMString("Delete footnotes"));
		choices.push_back(PMString("Flatten footnotes"));
		choices.push_back(PMString("Convert selection to footnote"));

		enum
		{
			kExploreFootnotes, kInsertFootnote, kDeleteFootnotes, kFlattenFootnotes, kSelectionToFootnote
		};

		Utils<ISnipRunParameterUtils> iParameterUtils;
		int32 choiceScope  = iParameterUtils->GetChoice("Footnote operation?", choices);
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
		case kExploreFootnotes:
		{
			status = instance.ExploreFootnotes(iTextTarget);
			break;
		}
		case kInsertFootnote:
		{
			PMString footnoteString = iParameterUtils->GetPMString("Text for footnote", "");
			if (iParameterUtils->WasDialogCancelled()){
				break;
			}
			const boost::shared_ptr<WideString> footnoteStringWS(new WideString(footnoteString));
			status = instance.InsertFootnote(iTextTarget,footnoteStringWS);
			break;
		}
		case kDeleteFootnotes:
		{
			status = instance.DeleteStoryFootnotes(iTextTarget);
			break;
		}
		case kFlattenFootnotes:
		{
			status = instance.FlattenStoryFootnotes(iTextTarget);
			break;
		}
		case kSelectionToFootnote:
		{
			status = instance.ConvertSelectionToFootnote(iTextTarget);
			break;
		}
		default:
			ASSERT("Choice not covered");			
			break;
		}
	} while(false);
	return status;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerManipulateTextFootnotes instance_SnpRunnerManipulateTextFootnotes;
DEFINE_SNIPPET(_SnpRunnerManipulateTextFootnotes) 	

//End, SnpManipulateTextFootnotes.cpp

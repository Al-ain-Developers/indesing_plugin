//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtCommands.cpp $
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
#include "ICommand.h"
#include "IRangeData.h"
#include "ITextModel.h"
#include "ITextModelCmds.h"
#include "IItemStrand.h"
#include "ITextStoryThread.h"
#include "IDocument.h"
#include "IStyleNameTable.h"
#include "IStyleGroupManager.h"
#include "IStyleGroupHierarchy.h"
#include "ICommand.h"
#include "IOwnedItem.h"
#include "IInsertTextData.h"

// General includes:
#include "UIDList.h"
#include "WideString.h"
#include "CmdUtils.h"

// Project includes:
#include "HidTxtCommands.h"
#include "HidTxtID.h"
#include "IHidTxtModel.h"

/*
*/
HidTxtCommands::HidTxtCommands()
{
}

/*
*/
HidTxtCommands::~HidTxtCommands()
{
}

/*
*/
IHidTxtModel* HidTxtCommands::Create(ITextModel* textModel, const TextIndex& anchorTextIndex) const
{
	TRACEFLOW("HiddenText", "HidTxtCommands::Create()-->In anchorTextIndex=%d\n", anchorTextIndex);
	IHidTxtModel* result = nil;
	ErrorCode status = kFailure;
	do {
		InterfacePtr<ICommand> hidTxtModelCreateCmd(CmdUtils::CreateCommand(kHidTxtModelCreateCmdBoss));
		ASSERT(hidTxtModelCreateCmd != nil);
		if (hidTxtModelCreateCmd == nil) {
			break;
		}
		InterfacePtr<IRangeData> rangeData(hidTxtModelCreateCmd, UseDefaultIID());
		ASSERT(rangeData != nil);
		if (rangeData == nil) {
			break;
		}
		const RangeData anchor(anchorTextIndex, anchorTextIndex+1);
		rangeData->SetRange(anchor);
		hidTxtModelCreateCmd->SetItemList(UIDList(::GetUIDRef(textModel)));
		status = CmdUtils::ProcessCommand(hidTxtModelCreateCmd);
		if (status != kSuccess) {
			break;
		}

		UIDRef hidTxtModelUIDRef = hidTxtModelCreateCmd->GetItemListReference().GetRef(0);
		InterfacePtr<IHidTxtModel> hidTxtModel(hidTxtModelUIDRef, UseDefaultIID());
		ASSERT(hidTxtModel != nil);
		result = hidTxtModel.forget();

	} while(false);

	TRACEFLOW("HiddenText", "HidTxtCommands::Create()-->Out result=0x%x\n",
		result);
	return result;
}

/*
*/
IHidTxtModel* HidTxtCommands::Query(ITextModel* textModel, const TextIndex& anchorTextIndex) const
{
	TRACEFLOW("HiddenText", "HidTxtCommands::Query()-->In anchorTextIndex=%d\n", anchorTextIndex);
	IHidTxtModel* result = nil;
	do {
		ASSERT(textModel != nil);
		if (textModel == nil) {
			break;
		}
		InterfacePtr<IItemStrand> itemStrand((IItemStrand*)textModel->QueryStrand(kOwnedItemStrandBoss, IItemStrand::kDefaultIID));		
		ASSERT(itemStrand != nil);
		if (itemStrand == nil) {
			break;
		}
		UID hidTxtModelUID = itemStrand->GetOwnedUID(anchorTextIndex, kHidTxtModelBoss);
		if (hidTxtModelUID.IsValid() == kFalse) {
			break;
		}
		InterfacePtr<IHidTxtModel> hidTxtModel(::GetDataBase(textModel), hidTxtModelUID, UseDefaultIID());
		ASSERT(hidTxtModel != nil);
		if (hidTxtModel == nil) {
			break;
		}
		result = hidTxtModel.forget();
	} while(false);
	TRACEFLOW("HiddenText", "HidTxtCommands::Query()-->Out result=0x%x\n", result);
	return result;
}

/*
*/
ErrorCode HidTxtCommands::ClearHiddenTextStyle(IHidTxtModel* hidTxtModel) const
{
	TRACEFLOW("HiddenText", "HidTxtCommands::ClearHiddenTextStyle()-->In\n");
	ErrorCode status = kFailure;
	do {
		ASSERT(hidTxtModel != nil);
		if (hidTxtModel == nil) {
			break;
		}
		TextIndex hiddenTextStart = kInvalidTextIndex;
		int32 hiddenTextSpan = 0;
		bool16 found = hidTxtModel->GetHiddenTextRange(hiddenTextStart, hiddenTextSpan);
		ASSERT(found == kTrue && hiddenTextStart != kInvalidTextIndex && hiddenTextSpan > 0);
		if (!(found == kTrue && hiddenTextStart != kInvalidTextIndex && hiddenTextSpan > 0)) {
			break;
		}

		InterfacePtr<ITextModel> textModel(hidTxtModel->QueryTextModel());
		ASSERT(textModel != nil);
		if (textModel == nil) {
			break;
		}
		InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
		ASSERT(textModelCmds != nil);
		if (textModelCmds == nil) {
			break;
		}

		// Apply [No character style]
		IDataBase* db = ::GetDataBase(hidTxtModel);
		InterfacePtr<IDocument> doc(db, db->GetRootUID(), UseDefaultIID());
		InterfacePtr<IStyleGroupManager> charStyleNameTable(doc->GetDocWorkSpace(), IID_ICHARSTYLEGROUPMANAGER);
		UID noCharStyle = charStyleNameTable->GetRootStyleUID();

		InterfacePtr<ICommand> applyNoCharStyleCmd(textModelCmds->ApplyStyleCmd(hiddenTextStart, 0, noCharStyle, kCharAttrStrandBoss, kFalse));
		CmdUtils::ProcessCommand(applyNoCharStyleCmd);

		// Apply [No paragraph style]
		InterfacePtr<IStyleGroupManager> paraStyleNameTable(doc->GetDocWorkSpace(), IID_IPARASTYLEGROUPMANAGER);
		UID noParaStyle = paraStyleNameTable->GetRootStyleUID();
		InterfacePtr<ICommand> applyNoParaStyleCmd(textModelCmds->ApplyStyleCmd(hiddenTextStart, 0, noParaStyle, kParaAttrStrandBoss, kFalse));
		CmdUtils::ProcessCommand(applyNoParaStyleCmd);

		status = kSuccess;
	} while(false);
	TRACEFLOW("HiddenText", "HidTxtCommands::ClearHiddenTextStyle()-->Out, status=%d\n", status);
	return status;
}

/*
*/
ErrorCode HidTxtCommands::ModifyHiddenText(IHidTxtModel* hidTxtModel, const WideString& text) const
{
	TRACEFLOW("HiddenText", "HidTxtCommands::ModifyHiddenText()-->In\n");
	ErrorCode status = kFailure;

	do {
		ASSERT(hidTxtModel != nil);
		if (hidTxtModel == nil) {
			break;
		}
		InterfacePtr<ICommand> hidTxtModelModifyTextCmd(CmdUtils::CreateCommand(kHidTxtModelModifyTextCmdBoss));
		ASSERT(hidTxtModelModifyTextCmd != nil);
		if (hidTxtModelModifyTextCmd == nil) {
			break;
		}
		InterfacePtr<IInsertTextData> insertTextData(hidTxtModelModifyTextCmd, UseDefaultIID());
		ASSERT(insertTextData != nil);
		if (insertTextData == nil) {
			break;
		}

		// TODO: push use of K2:;shared_ptr<WideString> up into client code
		// so that we minimise copying of string data
		boost::shared_ptr<WideString> theString(new WideString(text));
		insertTextData->Set(theString);

		hidTxtModelModifyTextCmd->SetItemList(UIDList(::GetUIDRef(hidTxtModel)));
		status = CmdUtils::ProcessCommand(hidTxtModelModifyTextCmd);
		if (status != kSuccess) {
			break;
		}

	} while(false);

	TRACEFLOW("HiddenText", "HidTxtCommands::ModifyHiddenText()-->Out status=%d\n", status);
	return status;
}

/*
*/
ErrorCode HidTxtCommands::Delete(IHidTxtModel* hidTxtModel) const
{
	TRACEFLOW("HiddenText", "HidTxtCommands::Delete()-->In\n");
	ErrorCode status = kFailure;

	do {
		ASSERT(hidTxtModel != nil);
		if (hidTxtModel == nil) {
			break;
		}

		// Get the range of text anchoring the hidden text.
		TextIndex anchorTextIndex;
		int32 anchorSpan;
		bool16 found = hidTxtModel->GetAnchorTextRange(anchorTextIndex, anchorSpan);
		ASSERT(found == kTrue);
		if (found == kFalse) {
			break;
		}
		ASSERT(anchorTextIndex != kInvalidTextIndex);
		if (anchorTextIndex == kInvalidTextIndex) {
			break;
		}
		ASSERT(anchorSpan > 0);
		if (anchorSpan <= 0) {
			break;
		}

		// Delete the anchor text and the associated hidden text gets deleted too.
		InterfacePtr<ITextModel> textModel(hidTxtModel->QueryTextModel());
		ASSERT(textModel != nil);
		if (textModel == nil) {
			break;
		}
		InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
		ASSERT(textModelCmds != nil);
		if (textModelCmds == nil) {
			break;
		}
		InterfacePtr<ICommand> deleteCmd(textModelCmds->DeleteCmd(anchorTextIndex, anchorSpan));
		ASSERT(deleteCmd != nil);
		if (deleteCmd == nil) {
			break;
		}
		status = CmdUtils::ProcessCommand(deleteCmd);
	} while(false);

	TRACEFLOW("HiddenText", "HidTxtCommands::Delete()-->Out status=%d\n", status);
	return status;
}

// End, HidTxtCommands.cpp
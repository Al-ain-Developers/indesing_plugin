//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtFacade.cpp $
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
#include "IItemLockData.h"

// General includes:
#include "WideString.h"
#include "CmdUtils.h"
#include "PersistUtils.h"
#include "textiterator.h"

// Project includes:
#include "IHidTxtModel.h"
#include "HidTxtFacade.h"
#include "HidTxtCommands.h"
#include "HidTxtID.h"

/*
*/
HidTxtFacade::HidTxtFacade(const UIDRef& textModelUIDRef, const TextIndex& anchorTextIndex)
:
fTextModelUIDRef(textModelUIDRef),
fAnchorTextIndex(anchorTextIndex),
fHidTxtModelUIDRef(nil, kInvalidUID)
{
	InterfacePtr<ITextModel> textModel(textModelUIDRef, UseDefaultIID());
	ASSERT(textModel != nil);
	if (textModel != nil) {
		HidTxtCommands hidTxtCommands;
		InterfacePtr<IHidTxtModel> hidTxtModel(hidTxtCommands.Query(textModel, anchorTextIndex));
		if (hidTxtModel != nil) {
			fHidTxtModelUIDRef = ::GetUIDRef(hidTxtModel);
		}
	}
}

/*
*/
HidTxtFacade::~HidTxtFacade()
{
}

/*
*/
bool16 HidTxtFacade::CanCreateHiddenText()
{
	bool16 result = kFalse;
	if (this->IsTextLocked() == kFalse) {
		result = kTrue;
	}
	return result;
}
		
/*
*/
ErrorCode HidTxtFacade::CreateHiddenText(const WideString& text)
{
	TRACEFLOW("HiddenText", "HidTxtFacade::CreateHiddenText()-->In fAnchorTextIndex=%d\n", fAnchorTextIndex);
	ErrorCode status = kFailure;

	CmdUtils::SequencePtr sequence;
    sequence->SetName(kHidTxtCreateHiddenTextStringKey);

	do {
		InterfacePtr<ITextModel> textModel(fTextModelUIDRef, UseDefaultIID());
		HidTxtCommands hidTxtCommands;
		InterfacePtr<IHidTxtModel> hidTxtModel(hidTxtCommands.Create(textModel, fAnchorTextIndex));
		ASSERT(hidTxtModel != nil);
		if (hidTxtModel == nil) {
			break;
		}
		status = hidTxtCommands.ClearHiddenTextStyle(hidTxtModel);
		ASSERT(status == kSuccess);
		if (status != kSuccess) {
			break;
		}
		status = hidTxtCommands.ModifyHiddenText(hidTxtModel, text);
		ASSERT(status == kSuccess);
		if (status != kSuccess) {
			break;
		}
	} while(false);

	if (status != kSuccess)
		ErrorUtils::PMSetGlobalErrorCode(status);

	TRACEFLOW("HiddenText", "HidTxtFacade::CreateHiddenText()-->In status=%d\n",
		status);
	return status;
}

/*
*/
bool16 HidTxtFacade::CanGetHiddenText() 
{
	if (fHidTxtModelUIDRef == UIDRef(nil, kInvalidUID)) {
		return kFalse; 
	}
	else {
		return kTrue;
	}
}

/*
*/
ErrorCode HidTxtFacade::GetHiddenText(WideString& text)
{
	ErrorCode status = kFailure;
	text.Clear();
	do {
		InterfacePtr<IHidTxtModel> hidTxtModel(fHidTxtModelUIDRef, UseDefaultIID());
		if (hidTxtModel == nil) {
			break;
		}
		TextIndex start = kInvalidTextIndex;
		int32 span = 0;
		bool16 found = hidTxtModel->GetHiddenTextRange(start, span);
		if (found == kFalse) {
			break;
		}
		InterfacePtr<ITextModel> textModel(fTextModelUIDRef, UseDefaultIID());
		TextIterator begin(textModel, start);
		TextIterator end(textModel, start + span);
		for (TextIterator iter = begin; iter != end; iter++) {
			text.Append(*iter);
		}
		status = kSuccess;
	} while(false);
	return status;
}

/*
*/
bool16 HidTxtFacade::CanModifyHiddenText() 
{ 
	return this->CanChangeHiddenText(); 
}
		
/*
*/
ErrorCode HidTxtFacade::ModifyHiddenText(const WideString& text)
{
	TRACEFLOW("HiddenText", "HidTxtFacade::ModifyHiddenText()-->In fAnchorTextIndex=%d\n", fAnchorTextIndex);
	ErrorCode status = kFailure;

	CmdUtils::SequencePtr sequence;
    sequence->SetName(kHidTxtModifyHiddenTextStringKey);

	do {
		InterfacePtr<IHidTxtModel> hidTxtModel(fHidTxtModelUIDRef, UseDefaultIID());
		if (hidTxtModel == nil) {
			break;
		}
		HidTxtCommands hidTxtCommands;
		status = hidTxtCommands.ModifyHiddenText(hidTxtModel, text);
	} while(false);

	if (status != kSuccess)
		ErrorUtils::PMSetGlobalErrorCode(status);

	TRACEFLOW("HiddenText", "HidTxtFacade::ModifyHiddenText()-->In status=%d\n",
		status);
	return status;

}

/*
*/
bool16 HidTxtFacade::CanDeleteHiddenText() 
{ 
	return this->CanChangeHiddenText(); 
}

/*
*/
ErrorCode HidTxtFacade::DeleteHiddenText()
{
	TRACEFLOW("HiddenText", "HidTxtFacade::DeleteHiddenText()-->In fAnchorTextIndex=%d\n", fAnchorTextIndex);
	ErrorCode status = kFailure;

	CmdUtils::SequencePtr sequence;
    sequence->SetName(kHidTxtDeleteHiddenTextStringKey);

	do {
		InterfacePtr<IHidTxtModel> hidTxtModel(fHidTxtModelUIDRef, UseDefaultIID());
		if (hidTxtModel == nil) {
			break;
		}
		HidTxtCommands hidTxtCommands;
		status = hidTxtCommands.Delete(hidTxtModel);
	} while(false);

	if (status != kSuccess)
		ErrorUtils::PMSetGlobalErrorCode(status);

	TRACEFLOW("HiddenText", "HidTxtFacade::DeleteHiddenText()-->In status=%d\n",
		status);
	return status;
}

/*
*/
bool16 HidTxtFacade::CanChangeHiddenText()
{
	bool16 result = kFalse;
	if (this->CanGetHiddenText() == kTrue) {
		if (this->IsTextLocked() == kFalse) {
			result = kTrue;
		}
	}
	return result;
}

/*
*/
bool16 HidTxtFacade::IsTextLocked()
{
	bool16 result = kFalse;
	InterfacePtr<IItemLockData> itemLockData(fTextModelUIDRef, UseDefaultIID());
	if (itemLockData) {
		// Text model locking is installed.
		if (itemLockData->GetInsertLock() == kTrue) {
			// The text model is insert locked.
			result = kTrue;
		}
	}
	return result;
}

// End, HidTxtFacade.cpp

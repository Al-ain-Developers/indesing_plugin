//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/csxsdemo/VDSuiteCSB.cpp $
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
//  Copyright 1997-2013 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "ISession.h"

// General includes:
#include "CPMUnknown.h"

// Project includes:
#include "VDID.h"
#include "IVDSuite.h"

#include "ITextModel.h"
#include "ITextTarget.h"
#include "TextRange.h"
#include "TextIterator.h"
#include "IActiveContext.h"
#include "ISelectionUtils.h"

#include "IGraphicFrameData.h"
#include "IMultiColumnTextFrame.h"

class VDSuiteCSB : public CPMUnknown<IVDSuite>
{
	public:
		VDSuiteCSB(IPMUnknown* boss);
		virtual ~VDSuiteCSB();	
		virtual ErrorCode GetTextFromSelectedFrame(const UIDRef &frameUIDRef, PMString &result);
	private:
		InDesign::TextRange	GetTextFrameTextRange(IMultiColumnTextFrame* mcf);
		WideString GetWideStringFromTextRange(const InDesign::TextRange& range);
};

CREATE_PMINTERFACE(VDSuiteCSB, kVDSuiteCSBImpl)

VDSuiteCSB::VDSuiteCSB(IPMUnknown* boss) : 
	CPMUnknown<IVDSuite>(boss)
{
}

VDSuiteCSB::~VDSuiteCSB()
{
}

ErrorCode VDSuiteCSB::GetTextFromSelectedFrame(const UIDRef &frameUIDRef, PMString &result)
{
	ErrorCode resultCode = kFailure;
	
	do {
		InterfacePtr<IGraphicFrameData> frameData(frameUIDRef, UseDefaultIID());
		if (!frameData)
		{
			break;
		}

		InterfacePtr<IMultiColumnTextFrame> mcf(frameUIDRef.GetDataBase(), frameData->GetTextContentUID(), UseDefaultIID());
		if (!mcf)
		{
			break;
		}

		InDesign::TextRange range = this->GetTextFrameTextRange(mcf);
		if (!range.IsValid())
		{
			break;
		}

		WideString wstr = this->GetWideStringFromTextRange(range);
		result = PMString(wstr);
	} while (false);

	return resultCode;
}

/////// private util methods //////

InDesign::TextRange VDSuiteCSB::GetTextFrameTextRange(IMultiColumnTextFrame* mcf)
{
	InDesign::TextRange result;
	do {
		ASSERT(mcf);
		if (!mcf) {
			break;
		}

		// Make sure the text is composed.
		InterfacePtr<IFrameList> frameList(mcf->QueryFrameList());
		ASSERT(frameList);
		if (frameList == nil) {
			break;
		}
		const int32 kNoDamage = -1;
		if (frameList->GetFirstDamagedFrameIndex() != kNoDamage) {
			// Re-compose.
			mcf->RecomposeThru();
		}

		InterfacePtr<ITextModel> textModel(mcf->QueryTextModel());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}

		// Check if the story contains any characters.
		// Note that when a story is created it has a terminating
		// character and length of 1 characters. We never
		// want to include the terminating character in our range.
		int32 charactersInPrimaryStoryThread = textModel->GetPrimaryStoryThreadSpan();
		// Number of characters in the story including the terminating character
		if (charactersInPrimaryStoryThread <= 1) {
			break; // the story has no significant characters
		}

		// Check if this text frame displays any characters.
		int32 span = mcf->TextSpan();
		if (span <= 0) {
			break; // the text frame is empty
		}

		// Get the range of characters displayed in the frame.
		TextIndex startIndex = mcf->TextStart();
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

		result = InDesign::TextRange(textModel, startIndex, span, RangeData::kLeanForward);
	} while(false);
	return result;
}

WideString VDSuiteCSB::GetWideStringFromTextRange(const InDesign::TextRange& range)
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
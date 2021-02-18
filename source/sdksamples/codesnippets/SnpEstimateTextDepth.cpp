//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpEstimateTextDepth.cpp $
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
#include "ITextFrameColumn.h"
#include "IParcelList.h"
#include "IParcel.h"
#include "IFrameList.h"
#include "ITextParcelList.h"
#include "ITextParcelListComposer.h"
#include "IWaxStrand.h"
#include "IWaxIterator.h"
#include "IWaxLine.h"
#include "IHierarchy.h"
#include "ITextTarget.h"
// General includes:
#include "Utils.h"
#include "UIDList.h"
#include "TextRange.h"
//#include "TextIterator.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"
#include "SnpTextModelHelper.h"

/** \li	How to estimate the composed depth of text using 
		the parcel architecture,
	\li how to make sure text is fully composed,
	\li how to detect if a story or parcel is overset,
	\li how to determine that parcel that displays a given TextIndex,
	\li how to determine the range of characters
		displayed by a parcel,
	\li composed text is displayed in parcels (IParcel), this allows text 
		to be displayed in both text frames, table text cells and in the 
		future other objects that support the parcel architecture.

	Consolidated  the following 2.x snippets in here so far:
	\li SnipIsStoryOverset
	\li SnipIsTextFrameOverset

  	@ingroup sdk_snippet
	@ingroup sdk_text
	
	@see IParcel
	@see IParcelList
	@see ITextParcelList
	@see ITextParcelListComposer
	@see IWaxIterator
 */
class SnpEstimateTextDepth
{
public:
	/** Constructor.
		*/
	SnpEstimateTextDepth() {}

	/** Destructor.
		*/
	virtual			~SnpEstimateTextDepth() {}

	/**	Estimates the depth of the text in a parcel as the y position of
		the last line of wax (IWaxLine) in the parcel minus the y position of 
		the first line plus the height of the first line.
		@param textParcelList gives range of text in each parcel.
		@param fromParcelKey IParcelList index of first parcel to be considered
		@param numberOfParcels must be >=1
		@param estimatedDepth the composed depth of the text in the parcels.
		@return kSuccess on success, kFailure otherwise. 
	*/
	ErrorCode EstimateTextDepth(const InterfacePtr<ITextParcelList>& textParcelList, ParcelKey fromParcelKey, int32 numberOfParcels, PMReal& estimatedDepth);

	/**	Estimates the composed depth of a story.
		@param textModel of story to be measured.
		@param estimatedDepth the composed depth of the text in the story.
		@return kSuccess on success, kFailure otherwise. 
	*/
	ErrorCode EstimateStoryDepth(const InterfacePtr<ITextModel>& textModel, PMReal& estimatedDepth);

	/**	Estimates the composed depth of a text frame.
		@param textFrameColumn to be measured.
		@param estimatedDepth the composed depth of the text in the frame.
		@return kSuccess on success, kFailure otherwise. 
	*/
	ErrorCode EstimateFrameDepth(const InterfacePtr<ITextFrameColumn>& textFrameColumn, PMReal& estimatedDepth);

	/**	Estimates the composed depth of a parcel.
		@param parcel to be measured.
		@param estimatedDepth the composed depth of the text in the parcel.
		@return kSuccess on success, kFailure otherwise. 
	*/
	ErrorCode EstimateParcelDepth(const InterfacePtr<IParcel>& parcel, PMReal& estimatedDepth);


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

/*
*/
ErrorCode SnpEstimateTextDepth::EstimateTextDepth(const InterfacePtr<ITextParcelList>& textParcelList, ParcelKey fromParcelKey, int32 numberOfParcels, PMReal& estimatedDepth)
{
	ErrorCode status = kFailure;
	do {
		// Validate parameters.
		ASSERT(textParcelList != nil);
		if (textParcelList == nil) {
			break;
		}
		InterfacePtr<IParcelList> parcelList(textParcelList, UseDefaultIID());
		ASSERT(parcelList != nil);
		if (parcelList == nil) {
			break;
		}
		int32 fromParcelIndex = parcelList->GetParcelIndex(fromParcelKey);
		ASSERT(fromParcelIndex >= 0);
		if (fromParcelIndex < 0) {
			break;
		}
		ASSERT(numberOfParcels > 0 && numberOfParcels <= parcelList->GetParcelCount());
		if(numberOfParcels <= 0 || numberOfParcels > parcelList->GetParcelCount()) {
			break;
		}

		// Make sure the text is composed.
		ParcelKey firstDamagedParcelKey = textParcelList->GetFirstDamagedParcel();
		if (firstDamagedParcelKey.IsValid() == kTrue){
			InterfacePtr<ITextParcelListComposer> textParcelListComposer(textParcelList, UseDefaultIID());
			ASSERT(textParcelListComposer);
			if (!textParcelListComposer) {
				break;
			}
			ParcelKey thruKey = parcelList->GetNthParcelKey(fromParcelIndex + numberOfParcels - 1);
			textParcelListComposer->RecomposeThru(thruKey);
		}
		
		// Scan the wax and use the position of the first and last line
		// in each parcel that displays text to estimate the overall depth.
		InterfacePtr<IWaxStrand> waxStrand(textParcelList->GetWaxStrandRef(), UseDefaultIID());
		if (waxStrand == nil) {
			break;
		}
		K2::scoped_ptr<IWaxIterator> firstIterator(waxStrand->NewWaxIterator());
		K2::scoped_ptr<IWaxIterator> lastIterator(waxStrand->NewWaxIterator());
		ASSERT(firstIterator != nil && lastIterator != nil);
		if (firstIterator == nil || lastIterator == nil) {
			break;
		}
		for (int32 i = fromParcelIndex; i < fromParcelIndex + numberOfParcels; i++) {
			// Get the range of text in this parcel.
			ParcelKey key = parcelList->GetNthParcelKey(i);
			TextIndex start = textParcelList->GetTextStart(key);
			int32 span = textParcelList->GetTextSpan(key);
			if (span <= 0) {
				// Some parcels may not be able to display any text.
				// But we can't assume that the story is displayed
				// in its entirety by preceeding parcels. It is possible
				// that a parcel was not big enough to accept text and
				// so text flowed into a subsequent and larger parcel.
				// To handle this continue and consider the depth
				// of other parcels in the list.
				continue;
			}
			TextIndex end = start + span - 1;

			// Get the wax lines that display the first and last characters in the parcel.
			IWaxLine* firstLine = firstIterator->GetFirstWaxLine(start);
			IWaxLine* lastLine = lastIterator->GetFirstWaxLine(end);	
			ASSERT(firstLine != nil && lastLine != nil);
			if (firstLine == nil || lastLine == nil) {
				continue;
			}
	
			// Estimate the depth of the text.	
			estimatedDepth += lastLine->GetYPosition() - (firstLine->GetYPosition() - firstLine->GetTOFLineHeight());
		}

		status = kSuccess;

	} while (false);
	return status;
}

/*
*/
ErrorCode SnpEstimateTextDepth::EstimateStoryDepth(const InterfacePtr<ITextModel>& textModel, PMReal& estimatedDepth)
{
	ErrorCode status = kFailure;
	estimatedDepth = 0.0;
	do {
		InterfacePtr<IFrameList> frameList(textModel->QueryFrameList());
		ASSERT(frameList != nil);
		if (frameList == nil) {
			break;
		}
		InterfacePtr<IParcelList> parcelList(frameList, UseDefaultIID());
		ASSERT(parcelList != nil);
		if (parcelList == nil) {
			break;
		}
		InterfacePtr<ITextParcelList> textParcelList(frameList, UseDefaultIID());
		ASSERT(textParcelList != nil);
		if (textParcelList == nil) {
			break;
		}
		status = this->EstimateTextDepth(textParcelList, parcelList->GetNthParcelKey(0), parcelList->GetParcelCount(), estimatedDepth);
	} while (false);
	return status;
}

/*
*/
ErrorCode SnpEstimateTextDepth::EstimateFrameDepth(const InterfacePtr<ITextFrameColumn>& textFrameColumn, PMReal& estimatedDepth)
{
	ErrorCode status = kFailure;
	estimatedDepth = 0.0;
	do {
		InterfacePtr<IParcel> parcel(textFrameColumn, UseDefaultIID());
		if (parcel != nil) {
			status = this->EstimateParcelDepth(parcel, estimatedDepth);
			break;
		}

		// No parcel on this ITextFrameColumn so assume its a kMultiColumnItemBoss or similar
		// and check out its children for parcels.
		InterfacePtr<IHierarchy> hierarchy(textFrameColumn, UseDefaultIID());
		ASSERT(hierarchy != nil);
		if (hierarchy == nil) {
			break;
		}
		UIDList parcelUIDList(::GetDataBase(textFrameColumn));
		hierarchy->GetDescendents(&parcelUIDList, IParcel::kDefaultIID);
		for (int32 i = 0; i < parcelUIDList.Length(); i++) {
			InterfacePtr<IParcel> parcel(parcelUIDList.GetRef(i), UseDefaultIID());
			ASSERT(parcel != nil);
			if (parcel == nil) {
				continue;
			}
			status = this->EstimateParcelDepth(parcel, estimatedDepth);
			ASSERT(status == kSuccess);
			if (status != kSuccess) {
				break;
			}
		}
	} while(false);
	return status;
}

/*
*/
ErrorCode SnpEstimateTextDepth::EstimateParcelDepth(const InterfacePtr<IParcel>& parcel, PMReal& estimatedDepth)
{
	ErrorCode status = kFailure;
	do {
		InterfacePtr<IParcelList> parcelList(parcel->QueryParcelList());
		ASSERT(parcelList != nil);
		if (parcelList == nil) {
			break;
		}
		InterfacePtr<ITextParcelList> textParcelList(parcelList, UseDefaultIID());
		ASSERT(textParcelList != nil);
		if (textParcelList == nil) {
			break;
		}
		status = this->EstimateTextDepth(textParcelList, parcel->GetParcelKey(), 1, estimatedDepth);
	} while(false);
	return status;
}

/*
 */
bool16 SnpEstimateTextDepth::IsStoryOverset(InterfacePtr<ITextModel> textModel)
{
	SnpTextModelHelper	textModelHelper;
	return textModelHelper.IsStoryOverset(textModel);
}

/*
 */
bool16 SnpEstimateTextDepth::IsTextFrameOverset(const InterfacePtr<ITextFrameColumn> textFrameColumn)
{
	SnpTextModelHelper	textModelHelper;
	return textModelHelper.IsTextFrameOverset(textFrameColumn);
}

/*
*/
bool16 SnpEstimateTextDepth::IsParcelOverset(const InterfacePtr<IParcel> parcel)
{
	SnpTextModelHelper	textModelHelper;
	return textModelHelper.IsParcelOverset(parcel);
}

/*
*/
IParcel* SnpEstimateTextDepth::QueryParcelContaining(ITextModel* textModel, const TextIndex at)
{
	SnpTextModelHelper	textModelHelper;
	return textModelHelper.QueryParcelContaining(textModel, at);
}

/*
*/
InDesign::TextRange SnpEstimateTextDepth::GetParcelTextRange(IParcel* parcel)
{
	SnpTextModelHelper	textModelHelper;
	InDesign::TextRange	range = textModelHelper.GetParcelTextRange(parcel);
	SNIPLOG("start=%d, end=%d",
		range.Start(),
		range.End());

	return range;
}
/*
*/
WideString SnpEstimateTextDepth::GetWideStringFromTextRange(const InDesign::TextRange& range)
{
	SnpTextModelHelper	textModelHelper;
	return textModelHelper.GetWideStringFromTextRange(range);
}

/*
*/
WideString SnpEstimateTextDepth::GetWideStringFromParcel(IParcel* parcel)
{
	SnpTextModelHelper	textModelHelper;
	return textModelHelper.GetWideStringFromParcel(parcel);
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/** Makes the snippet SnpEstimateTextDepth available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerEstimateTextDepth : public SnpRunnable
{
	
		
	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerEstimateTextDepth();

		/** Destructor.
		 */
		virtual			~_SnpRunnerEstimateTextDepth();

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
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTextSelectionTargetContext;}
};
/* Constructor.
*/
_SnpRunnerEstimateTextDepth::_SnpRunnerEstimateTextDepth() : SnpRunnable("EstimateTextDepth")
{
	this->SetDescription("Estimates the composed depth of text");
	this->SetPreconditions("text selection set");
	this->SetCategories("sdk_snippet, sdk_text");
}

/* Destructor.
*/
_SnpRunnerEstimateTextDepth::~_SnpRunnerEstimateTextDepth()
{
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerEstimateTextDepth::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
	if (textTarget) {
		result = kTrue;
	}
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerEstimateTextDepth::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpEstimateTextDepth instance;
		// Find the parcel and text frame displaying the selected TextIndex
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (!textTarget) {
			break;
		}
		InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel());
		if (textModel == nil) {
			break;
		}
		RangeData range = textTarget->GetRange();
		TextIndex at = range.Start(nil/*lean*/);
		if (range.Length() == 0 && at > 0) {
			at = at - 1;
		}
		InterfacePtr<IParcel> parcel(instance.QueryParcelContaining(textModel, at));
		InterfacePtr<ITextFrameColumn> textFrameColumn(nil);
		if (parcel) {
			textFrameColumn.reset(parcel->QueryFrame());
		}

		SNIPLOG("TextIndex at=%d", at);
		if (!parcel) {
			SNIPLOG("parcel unknown");
		}
		if (!textFrameColumn) {
			SNIPLOG("text frame unknown");
		}

		// Estimate the overall depth of the story.
		PMReal estimatedStoryDepth(0.0);
		status = instance.EstimateStoryDepth(textModel, estimatedStoryDepth);
		if (status == kSuccess) {
			SNIPLOG("estimatedStoryDepth=%f", ::ToDouble(estimatedStoryDepth));
		}

		// Estimate the depth of the text in the column that displays TextIndex at.
		if (textFrameColumn) {
			PMReal estimatedColumnDepth(0.0);
			status = instance.EstimateFrameDepth(textFrameColumn, estimatedColumnDepth);
			if (status == kSuccess) {
				SNIPLOG("estimatedColumnDepth=%f", ::ToDouble(estimatedColumnDepth));
			}
		}

		// Estimate the depth of the text in the parcel that displays TextIndex at.
		// If the TextIndex lies in table cell text this will be different than
		// the depth of a column.
		if (parcel) {
			PMReal estimatedParcelDepth(0.0);
			status = instance.EstimateParcelDepth(parcel, estimatedParcelDepth);
			if (status == kSuccess) {
				SNIPLOG("estimatedParcelDepth=%f", ::ToDouble(estimatedParcelDepth));
			}
		}

		// Check if the text frame or parcel are overset.
		SNIPLOG("IsStoryOverset=%d", instance.IsStoryOverset(textModel));
		if (textFrameColumn) {
			SNIPLOG("IsTextFrameOverset=%d", instance.IsTextFrameOverset(textFrameColumn));
		}
		if (parcel) {
			SNIPLOG("IsParcelOverset=%d", instance.IsParcelOverset(parcel));
		}

		// Dump the characters displayed by the parcel.
		if (parcel) {
			WideString wstr = instance.GetWideStringFromParcel(parcel);
			PMString str(wstr);
			SNIPLOG("characters in parcel=%s", str.GetPlatformString().c_str());
		}

	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerEstimateTextDepth instance_SnpRunnerEstimateTextDepth;
DEFINE_SNIPPET(_SnpRunnerEstimateTextDepth) 	

// End, SnpEstimateTextDepth.cpp


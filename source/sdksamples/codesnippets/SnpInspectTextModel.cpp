//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpInspectTextModel.cpp $
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
#include "IDataBase.h"
#include "ITextFocus.h"
#include "ITextModel.h"
#include "textiterator.h"
#include "IStrand.h"
#include "ITextTarget.h"
#include "TextAttributeRunIterator.h"
#include "ITextAttrRealNumber.h"
#include "IItemStrand.h"
#include "TablesID.h"
#include "IndexingID.h"
#include "HyperlinkID.h"
#include "IAttributeStrand.h"
#include "IStyleInfo.h"
#include "IDocument.h"
#include "IStyleNameTable.h"
#include "IStyleGroupManager.h"
#include "IStyleGroupHierarchy.h"
#include "IStoryList.h"
#include "ITextFocusManager.h"
#include "IWaxStrand.h"
#include "IFrameList.h"
#include "IWaxIterator.h"
#include "IWaxLine.h"
#include "IFrameListComposer.h"
#include "IObjectModel.h"
#include "IOwnedItem.h"
#include "ISession.h"
#include "ITextStoryThread.h"
#include "IParcelList.h"
#include "IParcel.h"
#include "IGeometry.h"
#include "ITextFrameColumn.h"
#include "ITextStoryThreadDictHier.h"
#include "ITextStoryThreadDict.h"
#include "ITableModel.h"
#include "IRedlineDataStrand.h"
#include "ITrackChangeUtils.h"
#include "redlineiterator.h"
#include "VOSRedline.h"
#include "IDeletedTextData.h"
#include "ITrackChangesSettings.h"
#include "ITrackChangeUtils.h"

// General includes:
#include "TextRange.h"
#include "Utils.h"
#include "PersistUtils.h"
#include "CTUnicodeTranslator.h"
#include "TextChar.h"
#include "textiterator.h"
#include "TextID.h"
#include "TablesID.h"
#include "TextOnPathID.h"
#include "K2Vector.h"

// Framework includes:
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"

/** \li How to inspect various properties of a story's text model (ITextModel),
	\li how to inspect the character data,
	\li how to inspect the characters in each paragraph and line,
	\li how to use TextRange and TextAttributeRunIterator to discover the point sizes present in a range of text,
	\li how to use IItemStrand to count the number of different types of owned items in the selected story,
	\li how to inspect the style runs on the paragraph attribute strand's IAttributeStrand interface,
	\li	how to inspect story threads, story thread dictionary and parcel information
		for a story.

	Integrated the following 2.x code snippets in here:
	\li InspectTextModelCharacters
	\li SnipCountStoryParagraphs
	\li SnipInspectStoryPointSizes
	\li SnipCountStoryOwnedItems
	\li SnipCountStoryParaAttrRuns
	\li SnipInspectStoryThreads

	@ingroup sdk_snippet
	@ingroup sdk_text

	@see kTextStoryBoss
	@see ITextModel
	@see IStrand
	@see IItemStrand
	@see kCharAttrStrandBoss
	@see kParaAttrStrandBoss
	@see kTextAttrPointSizeBoss
	@see kOwnedItemStrandBoss
	@see TextIterator
*/
class SnpInspectTextModel
{
public:
	/** Constructor.
		@param range the range of text data to be reported on.
		*/
	SnpInspectTextModel(const InDesign::TextRange& range);

	/** Destructor.
		*/
	virtual		~SnpInspectTextModel();

	/**	Report the range this class is reporting on.
		*/
	void	ReportTextRange();

	/**	Report the stories in the document.
		@return kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode	ReportStories();

	/**	Report characters using TextIterator.
		@return kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode	ReportCharacters();

	/** Reports the number of paragraphs by using the paragraph strand's 
		IStrand interface are used to discover paragraph boundaries.
		
		There are many different ways to count the number of
		paragraphs e.g use IComposeScanner::FindSurroundingParagraph or scan the text and
		count the number of  kTextChar_CR characters. The IStrand approach is probably the
		fastest.

		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode	ReportParagraphs();

	/** Report the point sizes present using TextAttributeRunIterator.

		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode	InspectStoryPointSizes();
	
	/** Report the number of different types of owned items.

		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode	CountStoryOwnedItems();
	
	/** Reports the style runs on the paragraph attribute strand (IAttributeStrand).
		Paragraphs with the same attributes are grouped into runs on
		IAttributeStrand.

		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode	CountStoryParaAttrRuns();

	/**	Report the text foci(ITextFocus) associated with the story.
		@return kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode	ReportTextFoci();

	/**	Report the content of a text focus.
		@param textFocus 
		@return kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode	ReportTextFocus(ITextFocus* textFocus);

	/**	Report the wax lines using a wax iterator (IWaxIterator).
		@return kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode ReportLines();

	/**	Report the leading for each wax line in a story using a 
		wax iterator (IWaxIterator).
		@return kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode ReportWaxLineLeading();

	/**	Report the runs on all strands.
		@return kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode	ReportStrands();

	/**	Iterate through all the text index in a story and report the track changes type using RedlineIterator.
		This method is different from InspectTrackChange in that it will iterates through all text index, create/delete 
		a RedlineIterator based on each text index, use it to examin the current change record, if there are more than
		one change records under one index, it will report the insert record only.
		@return kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode	ReportChangeInfo();

	/**	Report all the track changes records type on the story using one RedlineIterator initialized from the primary thread start.
		This method is different from ReportChangeInfo() in that this only uses one RedlineIterator constructed from the text index 0
		and use this RedlineIterator to return all the change records in the story.
		@return kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode	InspectTrackChange();

	/** Reports the story threads. 
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode InspectStoryThreads();

	/** Reports the story thread dictionaries. 
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode InspectStoryThreadDicts();

	/** Reports the parcels associated with each story thread.
		@return kSuccess on success, other ErrorCode otherwise.		
	*/
	ErrorCode InspectParcels();

private:
	ErrorCode InspectChars(TextIndex startIndex, TextIndex endIndex);
	ErrorCode InspectStoryThreadDict(const InterfacePtr<ITextStoryThreadDict> textStoryThreadDict);
	PMString GetClassIDName(const ClassID& classID);
	PMString GetCharacter(UTF32TextChar character);

private:
	InDesign::TextRange fTextRange;
};

/*
*/
SnpInspectTextModel::SnpInspectTextModel(const InDesign::TextRange& range)
{
	fTextRange = range;
}

/*
*/
SnpInspectTextModel::~SnpInspectTextModel()
{
}
/*
*/
ErrorCode SnpInspectTextModel::ReportStories()
{
	ErrorCode status = kFailure;
	do {
		InterfacePtr<ITextModel> textModel(fTextRange.QueryModel());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		UIDRef	storyRef = ::GetUIDRef(textModel);
		InterfacePtr<IDocument> document(storyRef.GetDataBase(), storyRef.GetDataBase()->GetRootUID(), UseDefaultIID());
		if (!document) {
			break;
		}
		PMString documentName;
		document->GetName(documentName);
	
		// Get the list of stories in this document
		InterfacePtr<IStoryList> storyList(document, UseDefaultIID());
		ASSERT(storyList);
		if (!storyList) {
			break;
		}

		// Iterate over all the stories.
		SNIPLOG("Stories in document %s", documentName.GetPlatformString().c_str());
		SNIPLOG("i, uid, TextStory_StoryAccess, TotalLength, GetPrimaryStoryThreadSpan");
		const char* storyAccessName[] = { "invalid", "userAccessible", "notUserAccessible"};
		for (int32 i = 0; i < storyList->GetAllTextModelCount(); i++ )
		{
			TextStory_StoryAccess storyAccess = storyList->GetNthTextModelAccess(i);
	
			// Get the text model of the story.
			UIDRef storyUIDRef = storyList->GetNthTextModelUID(i);
			InterfacePtr<ITextModel> textModel(storyUIDRef, UseDefaultIID());
			ASSERT(textModel);
			if (!textModel) {
				break;
			}
			int32 totalLength = textModel->TotalLength();
			int32 primaryStoryThreadSpan = textModel->GetPrimaryStoryThreadSpan();

			SNIPLOG("%d, 0x%x, %s, %d, %d", 
				i, 
				storyUIDRef.GetUID().Get(),
				storyAccessName[storyAccess],
				totalLength,
				primaryStoryThreadSpan);

			if (storyAccess == kUserAccessible) {
				// Note that not all stories in a document are for 
				// display in text frames. Some have other uses. If
				// you are only interested in displayed stories you
				// need to check what type of TextStory_StoryAccess
				// the story has.
			}

		} // iterate stories
		status = kSuccess;
	} while(false);
	return status;
}

/*
*/
ErrorCode SnpInspectTextModel::ReportCharacters()
{
	do {
		InterfacePtr<ITextModel> textModel(fTextRange.QueryModel());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		this->InspectChars(fTextRange.Start(), fTextRange.End());
	} while(false);
	return kSuccess;
}

/*
*/
ErrorCode SnpInspectTextModel::ReportParagraphs()
{
	ErrorCode status = kFailure;
	do {
		// Acquire the text model for the story from the text focus:
		InterfacePtr<ITextModel> textModel(fTextRange.QueryModel());
		if (textModel == nil) {
			break;
		}

		// Navigate to the paragraph strand for this story:
		InterfacePtr<IStrand> strand
		(
			(IStrand*)textModel->QueryStrand
			(
				kParaAttrStrandBoss, 
				IStrand::kDefaultIID
			)
		);		
		if (strand == nil) {
			break;
		}

		// Initialise loop control variables
		TextIndex position = fTextRange.Start();
		int32 length = fTextRange.Length();
		int32 numberOfParagraphs = 0;
		
		// Loop round reporting runs on the strand & totting up the number of paragraphs
		SNIPLOG(" position, length, characters");
		while (position < fTextRange.End())
		{
			// The length returned by GetRunLength indicates the boundary
			// of the paragraph.
			length = strand->GetRunLength(position);

			// Build a string displaying the first and last
			// characters in the paragraph. Show kTextChar_CR 
			// as "<CR>".
			TextIterator firstChar(textModel, position);
			TextIterator lastChar(textModel, position + length - 1);
			ASSERT(*lastChar==kTextChar_CR);
			PMString paraText;
			paraText.AppendW(*firstChar);
			if (length > 2)
			{
				lastChar--;
				paraText += "...";
				paraText.AppendW(*lastChar);
			}
			paraText += "<CR>";

			// Report the details of this run.
			SNIPLOG(" %d, %d, %s", position, length, paraText.GetPlatformString().c_str());
			position += length;
			numberOfParagraphs++;
		}
		SNIPLOG("number of paragraphs=%d", numberOfParagraphs);

		status = kSuccess;
	} while (false);
	return status;
}

/*
*/
ErrorCode SnpInspectTextModel::InspectStoryPointSizes()
{
	ErrorCode status = kFailure;
	do {
		if (fTextRange.IsValid() == kFalse) {
			break;
		}

		// Create a K2Vector containing this TextRange.
		// Note: TextAttributeRunIterator can iterate over
		// multiple ranges of text. We only have one range
		// of text so our vector only has one member.
		K2Vector<InDesign::TextRange> textRanges;
		textRanges.push_back(fTextRange);

		// Create a K2Vector containing the ClassIDs of the
		// text attributes we want the iterator to find.
		// TextAttributeRunIterator can find multiple 
		// attributes passed. We looking for
		// one attribute, point size.
		K2Vector<ClassID> attributeClasses;
		attributeClasses.push_back(kTextAttrPointSizeBoss);

		// Construct the iterator.
		TextAttributeRunIterator runIter
			(
			textRanges.begin(), 
			textRanges.end(), 
			attributeClasses.begin(), 
			attributeClasses.end()
			);

		// Iterate of the range of text and report the point sizes present.
		while (runIter)
		{
			// Here we could also use: runIter->QueryByClassID(kTextAttrPointSizeBoss, ITextAttrRealNumber::kDefaultIID)));
			InterfacePtr<const ITextAttrRealNumber> textAttr
			(	
				static_cast<const ITextAttrRealNumber *>
				(
					// TextAttributeRunIterator's -> operator returns a 
					// pointer to an AttributeBossList. Dig the attributes
					// out of there.
					runIter->QueryBossN
					(
						0, // kTextAttrPointSizeBoss should be at index 0, it's the only one we are looking for
						ITextAttrRealNumber::kDefaultIID
					)
				)
			);

			if (textAttr == nil)
				break;

			PMReal pointSize = textAttr->Get();
			SNIPLOG("Point size is %2.1f pts.", ::ToDouble(pointSize));

			++runIter;
		}

		status = kSuccess;
	} while (false);
	return status;
} 

/*
*/
ErrorCode SnpInspectTextModel::CountStoryOwnedItems()
{
	ErrorCode status = kFailure;
	do {

		// Acquire the text model for the story from the text focus:
		InterfacePtr<ITextModel> textModel(fTextRange.QueryModel());
		if (textModel == nil) {
			ASSERT_FAIL("Invalid text model");
			break;
		}

		// IItemStrand maintains the owned items in a story, if any.
		InterfacePtr<IItemStrand> itemStrand (((IItemStrand*) 
			textModel->QueryStrand(kOwnedItemStrandBoss, 
			IItemStrand::kDefaultIID)));
		if (itemStrand == nil) {
			ASSERT_FAIL("invalid itemStrand");
			break;
		}

		OwnedItemDataList ownedList;
		itemStrand->CollectOwnedItems(fTextRange.Start(), fTextRange.Length(), &ownedList);
		int32 count = ownedList.size();

		int32 numberOfTables = 0;
		int32 numberOfInlines = 0;
		int32 numberOfHyperlinksDestination = 0;
		int32 numberOfIndexs = 0;
		int32 numberOfUnknowns = 0;

        // Search through the list to look for possible owned items in this story.
		SNIPLOG("position, UID, ClassID, ClassName");
		for (int32 i = 0; i < count; i++)
        {
			PMString className;
			ClassID ithOwnedItemClass = ownedList[i].fClassID;
			if (ithOwnedItemClass == kTableFrameBoss)
			{
				className = "kTableFrameBoss";
				numberOfTables++;
			}
			else if (ithOwnedItemClass == kInlineBoss)
			{
				className = "kInlineBoss";
				numberOfInlines++;
			}
			else if (ithOwnedItemClass == kIndexPageEntryBoss)
			{
				className = "kIndexPageEntryBoss";
				numberOfIndexs++;
			}
			else if (ithOwnedItemClass == kHyperlinkTextDestinationMarkerBoss)
			{
				// Page destinations & URL destinations don't need this marker
				className = "kHyperlinkTextDestinationMarkerBoss";
				numberOfHyperlinksDestination++;
			}
			else
			{
				className = "unknown";
				numberOfUnknowns++;
			}
			SNIPLOG("%d, 0x%x, 0x%x, %s", 
				ownedList[i].fAt,
				ownedList[i].fUID.Get(),
				ownedList[i].fClassID.Get(),
				className.GetPlatformString().c_str());
		}

		SNIPLOG("Totals");
		SNIPLOG("Table frames, %d", numberOfTables);
		SNIPLOG("Inline graphics, %d", numberOfInlines);
		SNIPLOG("Hyperlink destinations, %d", numberOfHyperlinksDestination);
		SNIPLOG("Index markers, %d", numberOfIndexs);
		SNIPLOG("Unknown owned items, %d", numberOfUnknowns);
		SNIPLOG("The total number of owned items is %d", count);

		status = kSuccess;
		
	} while(false);

	return status;
}

/*
*/
ErrorCode SnpInspectTextModel::CountStoryParaAttrRuns()
{
	ErrorCode status = kFailure;
	do
	{
		// Acquire the text model
		InterfacePtr<ITextModel> textModel(fTextRange.QueryModel());
		if (textModel == nil) {
			break;
		}

		// Navigate to the paragraph attribute strand for this story.
		InterfacePtr<IAttributeStrand> attributeStrand
		(
			(IAttributeStrand*)textModel->QueryStrand
			(
				kParaAttrStrandBoss, 
				IAttributeStrand::kDefaultIID
			)
		);		
		if (attributeStrand == nil)
		{
			break;
		}

		// Get the UID of the root paragraph style from the document's 
		// paragraph style table. This let's us report if the root style
		// or some other style applies.
		IDataBase* db = ::GetDataBase(textModel);
		InterfacePtr<IDocument> document(db, db->GetRootUID(), UseDefaultIID());
		if (document == nil) 
		{
			break;
		}
		InterfacePtr<IStyleGroupManager> paraStyleNameTable(document->GetDocWorkSpace(), IID_IPARASTYLEGROUPMANAGER);
		if (paraStyleNameTable == nil)
		{
			break;
		}
		UID rootParaStyleUID = paraStyleNameTable->GetRootStyleUID();

		// Initialise loop control variables.
		TextIndex position = fTextRange.Start();
		int32 length = 0;
		int32 numberOfRuns = 0;
		IDataBase* database = ::GetDataBase(textModel);
		
		// Loop round reporting runs on the paragraph attribute strand
		// and count up the total number of runs.
		SNIPLOG(" position, length, styleName, rootStyle");
		while (position < fTextRange.End())
		{
			// The length returned by GetStyleUID indicates the boundary
			// of the run to which the style applies.
			UID styleUID = attributeStrand->GetStyleUID(position,&length);

			// Get the name of the style.
			InterfacePtr<IStyleInfo> styleInfo(database, styleUID, UseDefaultIID());
			if (styleInfo == nil)
			{
				break;
			}
			const PMString& styleName = styleInfo->GetName();

			// Check for root style.
			PMString rootStyle("No");
			if (styleUID == rootParaStyleUID) {
				rootStyle = "Yes";
			}

			SNIPLOG(" %d, %d, %s, %s", 
				position, 
				length,
				styleName.GetPlatformString().c_str(),
				rootStyle.GetPlatformString().c_str()
			);

			position += length;
			numberOfRuns++;
		}
		SNIPLOG("number of runs=%d", numberOfRuns);

		status = kSuccess;
	} while (false);
	return status;
} 

/*
*/
ErrorCode SnpInspectTextModel::ReportTextFoci()
{
	ErrorCode status = kFailure;
	do {
		// Acquire the text model
		InterfacePtr<ITextModel> textModel(fTextRange.QueryModel());
		if (textModel == nil) {
			break;
		}
		InterfacePtr<ITextFocusManager> textFocusManager(textModel, UseDefaultIID());
		ASSERT(textFocusManager);
		if (!textFocusManager) {
			break;
		}
		int32 focusCount = textFocusManager->GetFocusCount();
		for (int32 i=0; i < focusCount; i++) {
			InterfacePtr<ITextFocus> textFocus(textFocusManager->QueryNthFocus(i));
			this->ReportTextFocus(textFocus);
		}
		status = kSuccess;
	} while(false);
	return status;
}

/*
*/
ErrorCode SnpInspectTextModel::ReportTextFocus(ITextFocus* textFocus)
{
	ErrorCode status = kFailure;
	do {
		InterfacePtr<ITextModel> textModel(textFocus->QueryModel());
		SNIPLOG("textModel UID=0x%x, start=%d, length=%d, end=%d, isRange=%d",
			(::GetUID(textModel)).Get(),
			textFocus->GetStart(nil),
			textFocus->Length(),
			textFocus->GetEnd(),
			textFocus->IsRange());
		status = kSuccess;
	} while(false);
	return status;
}

/*
*/
void SnpInspectTextModel::ReportTextRange()
{
	InterfacePtr<ITextModel> textModel(fTextRange.QueryModel());
	if (textModel) {
		SNIPLOG("textModel UID=0x%x, TotalLength=%d, PrimaryStoryThreadSpan=%d\nrange.start=%d, range.length=%d, range.end=%d",
				(::GetUID(textModel)).Get(),
				textModel->TotalLength(),
				textModel->GetPrimaryStoryThreadSpan(),
				fTextRange.Start(),
				fTextRange.Length(),
				fTextRange.End());
	}
}

/*
*/
ErrorCode SnpInspectTextModel::ReportLines()
{
	ErrorCode status = kFailure;

	do {
		// Acquire the text model
		InterfacePtr<ITextModel> textModel(fTextRange.QueryModel());
		if (textModel == nil) {
			break;
		}
		InterfacePtr<IWaxStrand> waxStrand (((IWaxStrand*)textModel->QueryStrand(kFrameListBoss, IID_IWAXSTRAND)));
		if (waxStrand == nil) {
			break;
		}
		InterfacePtr<IFrameList> frameList(waxStrand, UseDefaultIID());
		if (frameList == nil) {
			break;
		}
		const int32 kNoDamage = -1;
		if (frameList->GetFirstDamagedFrameIndex() != kNoDamage) {
			// Recompose.
			InterfacePtr<IFrameListComposer> frameListComposer(frameList, UseDefaultIID());
			ASSERT(frameListComposer);
			if (!frameListComposer) {
				break;
			}
			frameListComposer->RecomposeThruLastFrame();
		}
		K2::scoped_ptr<IWaxIterator> waxIterator(waxStrand->NewWaxIterator());
		if (waxIterator == nil) {
			break;
		}
		TextIndex start = fTextRange.Start();
		IWaxLine* waxLine = waxIterator->GetFirstWaxLine(start);
		int32	i = 0;
		SNIPLOG("#, TextOrigin, GetTextSpan, Leading(pts)");
		while (waxLine != nil && waxLine->TextOrigin() < fTextRange.End()) {
			SNIPLOG("%d, %d, %d, %2.1f pts.", 
				i, 
				waxLine->TextOrigin(),
				waxLine->GetTextSpan(),
				::ToDouble(waxLine->GetYAdvance()));
			waxLine = waxIterator->GetNextWaxLine();
			i++;
		}
		status = kSuccess;
	} while (false);
	return status;
}

/*
*/
ErrorCode SnpInspectTextModel::ReportWaxLineLeading()
{
	ErrorCode status = kFailure;

	do
	{
		// Acquire the text model
		InterfacePtr<ITextModel> textModel(fTextRange.QueryModel());
		if (textModel == nil) {
			break;
		}
		InterfacePtr<IWaxStrand> waxStrand (((IWaxStrand*)textModel->QueryStrand(kFrameListBoss, IID_IWAXSTRAND)));
		if (waxStrand == nil) {
			break;
		}
		InterfacePtr<IFrameList> frameList(waxStrand, UseDefaultIID());
		if (frameList == nil) {
			break;
		}
		const int32 kNoDamage = -1;
		if (frameList->GetFirstDamagedFrameIndex() != kNoDamage) {
			// Recompose.
			InterfacePtr<IFrameListComposer> frameListComposer(frameList, UseDefaultIID());
			ASSERT(frameListComposer);
			if (!frameListComposer) {
				break;
			}
			frameListComposer->RecomposeThruLastFrame();
		}
		K2::scoped_ptr<IWaxIterator> waxIterator(waxStrand->NewWaxIterator());
		if (waxIterator == nil) {
			break;
		}
		TextIndex start = 0;
		IWaxLine* waxLine = waxIterator->GetFirstWaxLine(start);
		int32	i = 0;
		while (waxLine != nil) {
			SNIPLOG("Wax Line %d leading is %2.1f pts.", i, ::ToDouble(waxLine->GetYAdvance()));
			waxLine = waxIterator->GetNextWaxLine();
			i++;
		}
		status = kSuccess;
	} while (false);
	return status;
}

/*
*/
ErrorCode SnpInspectTextModel::ReportStrands()
{

	ErrorCode status = kFailure;
	do {
		// Acquire the text model
		InterfacePtr<ITextModel> textModel(fTextRange.QueryModel());
		if (textModel == nil) {
			break;
		}
		// Iterate over all the strands.
		int32 strandNumber = 0;
		const int32 totalLength = textModel->TotalLength();
		SNIPLOG("IStrand runs on ITextModel of TotalLength=%d", totalLength);
		SNIPLOG(" strandBossClassID, run, textIndex, runLength");
		InterfacePtr<IStrand> strand(static_cast<IStrand*>(textModel->QueryNthStrand(strandNumber,	IStrand::kDefaultIID)));
		while (strand != nil) {

			// Dump the name of the strand boss class.
			ClassID id = ::GetClass(strand);
			InterfacePtr<IObjectModel> objectModel(GetExecutionContextSession(),IObjectModel::kDefaultIID);
			PMString strandBossClassID;
			const char* classIDName = objectModel->GetIDName(id);
			if (classIDName != nil) {
				strandBossClassID = classIDName;
			}
			else {
				// No name, use the hex ID instead.
				char buf[32];
				sprintf(buf, "0x%x", id.Get());
				strandBossClassID = buf;
			}

			// Report the IStrand runs on the strand boss class.
			int32 run = 0;
			TextIndex textIndex = fTextRange.Start();
			int32 runLength = strand->GetRunLength(textIndex);

			if (runLength == 0) {
				SNIPLOG(" %s (no runs on IStrand)", 
					strandBossClassID.GetPlatformString().c_str());
			}
			else {
				while (runLength > 0 && textIndex < fTextRange.End()) {
					SNIPLOG(" %s, %d, %d, %d", 
						strandBossClassID.GetPlatformString().c_str(), 
						run, 
						textIndex, 
						runLength);
					textIndex += runLength;
					run++;
					runLength = strand->GetRunLength(textIndex);
				}
			}

			// Next strand. We break out of the loop when we are done.
            strand.reset(static_cast<IStrand*>(textModel->QueryNthStrand(++strandNumber, IStrand::kDefaultIID)));
		}
		status = kSuccess;
	} while(false);
	return status;
}

/*
*/
ErrorCode SnpInspectTextModel::InspectChars(TextIndex startIndex, TextIndex endIndex)
{
	do {
		InterfacePtr<ITextModel> textModel(fTextRange.QueryModel());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		TextIterator begin(textModel, startIndex);
		TextIterator end(textModel, endIndex);
		SNIPLOG(" TextIndex, textchar(hex), character");
		for (TextIterator iter = begin; iter != end; iter++) {
			const UTF32TextChar characterCode = *iter;
			PMString character = this->GetCharacter(characterCode);
			TextIndex position = iter.Position();
			SNIPLOG(" %d, 0x%x, %s", position, characterCode.GetValue(), character.GetPlatformString().c_str());
		}	
	} while(false);

	return kSuccess;

}
/*
*/
ErrorCode SnpInspectTextModel::ReportChangeInfo()
{
	do {
		InterfacePtr<ITextModel> textModel(fTextRange.QueryModel());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		UIDRef storyUIDRef(::GetUIDRef(textModel));
		int32 storyThreadCount = 0;
		TextIndex position = fTextRange.Start();
		InterfacePtr<IRedlineDataStrand> redline((IRedlineDataStrand*)textModel->QueryStrand(
				kRedlineStrandBoss, IRedlineDataStrand::kDefaultIID));
		bool16	markDeleted = Utils<ITrackChangeUtils>() && Utils<ITrackChangeUtils>()->MarkDeleteChanges();
		TextIterator iter(textModel, position);
		PMString typeString;
							
		while (position < fTextRange.End())
		{
			typeString = "has no track change info";
			if (redline)
			{
				bool16	inDeletion = kFalse;
				TextIndex	redlineIndex = position;
				if (position >= textModel->GetPrimaryStoryThreadSpan())
				{
					// current position is in a story thread other than primary find it and convert to anchor position in 
					// the primary text model
					TextIndex threadStart;
					int32 threadSpan;
					// use the position to reach the ITextStoryThread it is in
					InterfacePtr<ITextStoryThread> storyThread(textModel->QueryStoryThread(position, &threadStart, &threadSpan));
				
					if (storyThread != nil)
					{	
						// We need to find out if the story thread belonged to the kDeletedTextBoss owned item
						InterfacePtr<IItemStrand> itemStrand((IItemStrand*)textModel->QueryStrand(kOwnedItemStrandBoss, IID_IITEMSTRAND));
						InterfacePtr<IOwnedItem> ownedItem(storyUIDRef.GetDataBase(), storyThread->GetDictUID(), UseDefaultIID());
						if (ownedItem && ::GetClass(ownedItem) == kDeletedTextBoss)
						{
							// if we are in deleted text, then find its anchor in the primary thread, we will use it to 
							// give us the change record, the track changes does not maintain change record in the story thread
							// other than primary story.  So in this case, we will just report we are in the deleted text.
							redlineIndex = itemStrand->GetOwnedItemIndex(ownedItem);
							if (position <= threadStart+threadSpan-1)
							{
								// current position is within deletion's thread range
								inDeletion = kTrue;
							}
						}
					}
				}
				
				// create a new RedlineIterator based on the current text index
				RedlineIterator *redIterator = redline->NewRedlineIterator(redlineIndex);

				if (redIterator)
				{
					const VOSRedlineChange* currRecord = redIterator->GetCurrentChangeRecord();	
					
					if (!inDeletion)
					{							
						int32	changePosition, numChanges;
						redIterator->GetCurrentPosition(&changePosition, &numChanges);
						if (numChanges > 1)	// if multiple change records, get the insert record at position 1 at the same text index
						{
							redIterator->MoveToPosition(redlineIndex, 1);
							if (currRecord)
								delete currRecord;
							currRecord = redIterator->GetCurrentChangeRecord();
						}
					}
					if (currRecord)
					{	
						bool16 isAdded = kFalse, isMoved = kFalse, isDeleted = kFalse;
						if (((isAdded = currRecord->GetIsAddedText()) && Utils<ITrackChangeUtils>()->MarkInsertChanges()) ||
							((isMoved = currRecord->GetIsMovedText()) && Utils<ITrackChangeUtils>()->MarkMoveChanges()) ||
							((isDeleted = currRecord->GetIsDeletedText()) && markDeleted))
						{
							if (isAdded)
							{
								typeString = " is added text";
							}
							else if (isMoved)
							{
								typeString = "is moved text";
							}
							else if (isDeleted)
							{
								if (inDeletion)
									typeString = "is in the deleted text in deleted text thread";
								else
									typeString = "is deleted text";
									
							}
							else
							{
								typeString = "has no track change info";
							}
						}
					}
					
					if (currRecord)
						delete currRecord;
					
					delete redIterator;
				}
			}


			const UTF32TextChar characterCode = *iter;
			TextIndex index = iter.Position();
			SNIPLOG("Text Index %d %s", index, typeString.GetPlatformString().c_str());
			iter++;
			position++;
			
		}
	} while(false);

	return kSuccess;

}

/*
*/
ErrorCode SnpInspectTextModel::InspectTrackChange()
{
	do {
		InterfacePtr<ITextModel> textModel(fTextRange.QueryModel());
		if (!textModel) {
			break;
		}
		InterfacePtr<IRedlineDataStrand> redline((IRedlineDataStrand*)textModel->QueryStrand(
				kRedlineStrandBoss, IRedlineDataStrand::kDefaultIID));
		// Create a new RedlineIterator at the text index 0
		RedlineIterator *redIterator = redline->NewRedlineIterator(0);
		if (redIterator)
		{
			int32	changeCounts=0;
			bool16 done = kFalse;
			while (!done)
			{
				PMString typeString;							
				int32	index, length, changePosition, numChanges;
				// asked the iterator to tell me the where is the current change position
				TextIndex	textIndex = redIterator->GetCurrentPosition(&changePosition, &numChanges);
				// retrive the current change record
				const VOSRedlineChange* record = redIterator->GetCurrentChangeRecord(&index, &length);
				VOSRedlineChange::RedlineChangeType	changeType;
				if (record)
				{
					changeCounts++;
					changeType = record->GetChangeType();
					// need to delete the VOSRedlineChange when I am done with it.
					delete record;
				}
				else
					changeType = VOSRedlineChange::kUnknown;
				
				PMString	deletedString;						
				switch(changeType)
				{
					case VOSRedlineChange::kDelete:
					{
						UIDRef deletedTextUIDRef;
						deletedTextUIDRef = redIterator->DescribeChangeContent(deletedString);
						typeString = " has change record kDelete";
						break;
					}
					case VOSRedlineChange::kInsert:
						typeString = " has change record kInsert";
						break;
					case VOSRedlineChange::kApply:
						typeString = " has change record kApply";
						break;
					default:
						typeString = " has no change record";
						break;
				}
				
				SNIPLOG("Text Index %d %s of length %d", textIndex, typeString.GetPlatformString().c_str(), length);
				if (deletedString != "")
				{
					SNIPLOG("deleted text = %s", deletedString.GetPlatformString().c_str());
				}
				// go to the next record
				done = (redIterator->Increment(kFalse) == kFalse);
			}
			// don't forget to delete the RedlineIterator too!
			delete redIterator;
			SNIPLOG("Total %d change record(s) found in story", changeCounts);
		}
	} while(false);

	return kSuccess;

}

/*
*/
ErrorCode SnpInspectTextModel::InspectStoryThreads()
{
	// A story thread is a range of text in the text model that represents 
	// a flow of text.

	// ITextModel has a method, QueryStoryThread, that makes
	// finding the story thread associated with a TextIndex easy.
	// Underneath the hood the boundaries of the story threads are
	// maintained by a new strand in the text model, kStoryThreadStrandBoss.
	bool16 corrupt = kFalse;
	do {
		InterfacePtr<ITextModel> textModel(fTextRange.QueryModel());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		int32 storyThreadCount = 0;
		TextIndex position = fTextRange.Start();
		while (position < fTextRange.End())
		{
			int32 length;
			InterfacePtr<const ITextStoryThread> textStoryThread
			(
				textModel->QueryStoryThread
				(
					position,
					&position,
					&length
				)
			);
			if (textStoryThread == nil)
			{
				break;
			}

			// Report information about this story thread to the log.
			ClassID classID = ::GetClass(textStoryThread);
			SNIPLOG("-----ITextStoryThread[%d] UID 0x%x-----", storyThreadCount, (::GetUID(textStoryThread)).Get());
			SNIPLOG(" boss=%s",	this->GetClassIDName(classID).GetPlatformString().c_str());
			SNIPLOG(" position=%d, length=%d",
				position,
				length);
			this->InspectChars(position, position+length-1);
			if (length < 1) {
				SNIPLOG(" *** CORRUPTION story thread has length < 1 ***");
				corrupt = kTrue;
			}
			else {
				TextIterator end(textModel, position+(length-1));
				if (*end != kTextChar_CR) {
					SNIPLOG(" *** CORRUPTION story thread is missing terminating CR ***");
					corrupt = kTrue;
				}
			}

			SNIPLOG("-----ITextStoryThread[%d]-end-", storyThreadCount);
			position = position + length;
			storyThreadCount++;
		}

		SNIPLOG("%d story threads in story", storyThreadCount);

	} while(false);

	if (corrupt) {
		SNIPLOG("*** CORRUPTION in story threads detected ***");
	}

	return kSuccess;

}

/*
*/
ErrorCode SnpInspectTextModel::InspectStoryThreadDicts()
{
	do {
		InterfacePtr<ITextModel> textModel(fTextRange.QueryModel());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		// Story threads are managed by a UID based boss
		// that aggregates the ITextStoryThreadDict interface.
		// Current dictionary implementations are stories (kTextStoryBoss),
		// tables(kTableModelBoss) and notes(InCopy).

		// The interface ITextStoryThreadDictHier is aggregated on kTextStoryBoss.
		// It is a collection of all dictionaries, ITextStoryThreadDict's, embedded in the
		// story. The story has a dictionary for the primary story thread, associates a dictionary
		// per table and in the future other dictionaries for other features.
		InterfacePtr<ITextStoryThreadDictHier> textStoryDictHier(textModel, UseDefaultIID());
		ASSERT(textStoryDictHier);
		if(textStoryDictHier == nil) 
		{
			break;
		}


		// kTextStoryBoss aggregates ITextStoryThreadDictHier for all the story thread 
		// dictionaries in the story, ITextStoryThreadDict the dictionary for the 
		// primary story thread and an ITextStoryThread the primary story thread.
		// 
		// kTableModelBoss, on the other hand, has an ITextStoryThreadDict and ITextStoryThread
		// but not a ITextStoryThreadDictHier. The collection of story thread dictionaries is 
		// maintained by kTextStoryBoss.
		//
		// So we can start the iteration through the story thread dictionaries 
		// by kicking off with what is the UID of the primary story thread.
		int32 storyThreadDictCount = 0;
		UIDRef storyUIDRef(::GetUIDRef(textModel));
		UID nextUID = storyUIDRef.GetUID();
		while(nextUID != kInvalidUID)
		{
			InterfacePtr<ITextStoryThreadDict> textStoryThreadDict
					(
						storyUIDRef.GetDataBase(), 
						nextUID, 
						UseDefaultIID()
					);
			ASSERT(textStoryThreadDict);
			if(textStoryThreadDict == nil) 
			{
				break;
			}
			SNIPLOG("-----ITextStoryThreadDict[%d]-----", storyThreadDictCount);				
			ClassID textStoryThreadDictClassID = ::GetClass(textStoryThreadDict);
			SNIPLOG("boss=%s", this->GetClassIDName(textStoryThreadDictClassID).GetPlatformString().c_str());

			// Report info on this dictionary.
			this->InspectStoryThreadDict(textStoryThreadDict);

			SNIPLOG("-----ITextStoryThreadDict[%d]-end-", storyThreadDictCount);
			storyThreadDictCount++;
			nextUID = textStoryDictHier->NextUID(nextUID);	

		} // end while( nextUID != kInvalidUID);	
		
		SNIPLOG("%d dictionaries in story", storyThreadDictCount);

	} while(false);
	return kSuccess;
}

/*
*/
ErrorCode SnpInspectTextModel::InspectStoryThreadDict(const InterfacePtr<ITextStoryThreadDict> textStoryThreadDict)
{
	do {
		InterfacePtr<ITextModel> textModel(fTextRange.QueryModel());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		// A dictionary is either anchored into
		// the text model or not. Associating an owned item with a text index
		// gives an anchor. Tables for example puts the UID of the first 
		// table frame into the owned item strand at the text index at
		// which the table is being inserted. Tables also inserts special 
		// characters into the text flow, kTextChar_Table for the first
		// table row and kTextChar_TableContinued for subsequent rows.
		// Inserting characters into the text flow is not necessary
		// to create an anchor. All that is needed is an owned item at 
		// the text index where the anchor is to be located.
		//
		// All the StoryThreads managed by a dictionary must
		// be stored contiguously in the text model. This is known as the
		// dictionary's ThreadBlock. So all the story threads for one
		// table's cells will be stored in one ThreadBlock, those for
		// another table in another ThreadBlock.
		//
		// The location of this ThreadBlock must be consistent
		// with the hierarchical location of where the dictionary
		// is anchored. In other words, if you insert a Table
		// in a StoryThread then your ThreadBlock must follow
		// the ThreadBlock containing the StoryThread that you
		// have been inserted at.
		//
		// A Dictionary which is not anchored into the TextModel must return
		// StoryRange(kInvalidTextIndex, kInvalidTextIndex). The Dictionary
		// on the kStoryBoss does this.

		// Report anchor text range and the owned items in that range
		// if the dictionary is anchored.
		bool16 isAnchored;
		Text::StoryRange anchorTextRange = textStoryThreadDict->GetAnchorTextRange(&isAnchored);
		TextIndex start = isAnchored ? anchorTextRange.GetStart() : kInvalidTextIndex;
		TextIndex end = isAnchored ? anchorTextRange.GetEnd() : kInvalidTextIndex;
		SNIPLOG("anchorTextRange.fStart=%d", start);
		SNIPLOG("anchorTextRange.fEnd=%d", end);
		if (isAnchored) {
			// Dictionary is anchored.
			InterfacePtr<IItemStrand> itemStrand (((IItemStrand*) textModel->QueryStrand(kOwnedItemStrandBoss, IItemStrand::kDefaultIID)));
			if (itemStrand == nil) {
				ASSERT_FAIL("invalid itemStrand");
				break;
			}
			OwnedItemDataList ownedItems;
			int32 length = end - start;
			itemStrand->CollectOwnedItems(start, length, &ownedItems);
			SNIPLOG("owned items in anchor range %d..%d", start, end);
			SNIPLOG(" position, UID, boss");
			for (int32 i = 0; i < ownedItems.size(); i++)
			{
			SNIPLOG(" %d, 0x%x, %s", 
				ownedItems[i].fAt,
				ownedItems[i].fUID.Get(),
				this->GetClassIDName(ownedItems[i].fClassID).GetPlatformString().c_str());
			}
		}

		// Report the thread block and the text in each of the story threads in the dictionary.
		Text::StoryRange threadBlockTextRange = textStoryThreadDict->GetThreadBlockTextRange();
		TextIndex blockStart = threadBlockTextRange.GetStart();
		TextIndex blockEnd = threadBlockTextRange.GetEnd();
		SNIPLOG("threadBlockTextRange.fStart=%d)", blockStart);
		SNIPLOG("threadBlockTextRange.fEnd=%d)", blockEnd);
		int32 storyThreadCount = 0;
		TextIndex position = blockStart;
		while (position < blockEnd)
		{
			int32 length;
			InterfacePtr<const ITextStoryThread> textStoryThread
			(
				textModel->QueryStoryThread
				(
					position,
					&position,
					&length
				)
			);
			if (textStoryThread == nil)
			{
				break;
			}
			ClassID classID = ::GetClass(textStoryThread);
			SNIPLOG(" -----ITextStoryThread[%d]-----", storyThreadCount);
			SNIPLOG(" boss=%s",	this->GetClassIDName(classID).GetPlatformString().c_str());
			SNIPLOG(" position=%d, length=%d",
				position,
				length);
			this->InspectChars(position, position+length-1);

			SNIPLOG(" -----ITextStoryThread[%d]-end-", storyThreadCount);
			position = position + length;
			storyThreadCount++;
		}

		SNIPLOG(" %d story threads in dictionary", storyThreadCount);

	} while(false);
	return kSuccess;
}

/*
*/
ErrorCode SnpInspectTextModel::InspectParcels()
{
	do
	{
		InterfacePtr<ITextModel> textModel(fTextRange.QueryModel());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		// Report the story threads, the list of parcels used to lay out the text in the
		// story thread and the text frame that is associated with each parcel.
		//
		// A parcel is a container into which text can be flowed for layout.
		TextIndex position = fTextRange.Start();
		int32 storyThreadCount = 0;
		while (position < fTextRange.End())
		{
			// Report the story thread and the characters in it.
			int32 length;
			InterfacePtr<const ITextStoryThread> textStoryThread
			(
				textModel->QueryStoryThread
				(
					position,
					&position,
					&length
				)
			);
			if (textStoryThread == nil)
			{
				break;
			}
			ClassID classID = ::GetClass(textStoryThread);
			SNIPLOG("-----ITextStoryThread[%d]-----", storyThreadCount);
			SNIPLOG(" boss=%s",	this->GetClassIDName(classID).GetPlatformString().c_str());
			SNIPLOG(" position=%d, length=%d",
				position,
				length);
			this->InspectChars(position, position+length-1);

			// Report the associated parcel list.
			SNIPLOG(" -----IParcelList-----");
			InterfacePtr<const IParcelList> parcelList(textStoryThread->QueryParcelList());
			if (parcelList == nil)
				break;
			ClassID parcelListClassID = ::GetClass(parcelList);
			SNIPLOG(" boss=%s",this->GetClassIDName(parcelListClassID).GetPlatformString().c_str());

			// Report the associated parcels.
			int32 parcelCount = parcelList->GetParcelCount();
			for (int32 i = 0; i < parcelCount; i++)
			{	
				ParcelKey	key = parcelList->GetNthParcelKey(i);
				InterfacePtr<const IParcel> parcel(parcelList->QueryParcel(key));
				if (parcel == nil)
					break;
				SNIPLOG("  -----IParcel[%d]-----", i);
				ClassID parcelClassID = ::GetClass(parcel);
				PMRect parcelBounds = parcel->GetBounds();
				SNIPLOG("  boss=%s", this->GetClassIDName(parcelClassID).GetPlatformString().c_str());
				SNIPLOG("  parcelBounds[left, top, right, bottom]");
				SNIPLOG("  [%6.2f, %6.2f, %6.2f, %6.2f]",
					::ToDouble(parcelBounds.Left()), ::ToDouble(parcelBounds.Top()), ::ToDouble(parcelBounds.Right()), ::ToDouble(parcelBounds.Bottom()));


				// Report the text frame associated with the parcel.
				SNIPLOG("  -----ITextFrameColumn-----");
				UID frameUID = parcel->GetFrameUID();
				SNIPLOG("  textFrameUID=0x%x", frameUID.Get());
				PMRect textFrameBounds;
				InterfacePtr<ITextFrameColumn> textFrameColumn(parcel->QueryFrame());
				if (textFrameColumn != nil)
				{
					InterfacePtr<IGeometry> textFrameGeometry(textFrameColumn, UseDefaultIID());
					if (textFrameGeometry != nil)
						textFrameBounds = textFrameGeometry->GetStrokeBoundingBox();
				}
				SNIPLOG("  frameBounds[left,top,right,bottom]");
				SNIPLOG("  [%6.2f, %6.2f, %6.2f, %6.2f]",
					::ToDouble(textFrameBounds.Left()), ::ToDouble(textFrameBounds.Top()), ::ToDouble(textFrameBounds.Right()), ::ToDouble(textFrameBounds.Bottom()));
				SNIPLOG("  -----IParcel[%d]-end-", i);
			}

			SNIPLOG(" %d parcels displaying story thread", parcelCount);
			SNIPLOG("-----ITextStoryThread[%d]-end-\n", storyThreadCount);

			// On to the next story thread.

			position = position + length;
			storyThreadCount++;
		}
	} while(false);

	return kSuccess;

}


/*
*/
PMString SnpInspectTextModel::GetCharacter(UTF32TextChar character)
{
	PMString result;

	if (character == kTextChar_CR)
	{
		result.Append("<CR>");
	}
	else if (character == kTextChar_SoftCR)
	{
		result.Append("<SoftCR>");
	}
	else if (character == kTextChar_Table)
	{
		result.Append("<Table>");
	}
	else if (character == kTextChar_TableContinued)
	{
		result.Append("<TableContinued>");
	}
	else if (character == kTextChar_ObjectReplacementCharacter)
	{
		result.Append("<Object>");
	}
	else
	{
		result.AppendW(character);
	}
	return result;
}

/*
*/
PMString SnpInspectTextModel::GetClassIDName(const ClassID& classID)
{
	PMString result;
	do
	{
		InterfacePtr<IObjectModel> objectModel(GetExecutionContextSession(), UseDefaultIID());
		if (objectModel == nil)
			break;
		const char* classIDName = objectModel->GetIDName(kClassIDSpace, classID.Get());
		if (classIDName != nil)
			result = classIDName;
		else
		{
			if (classID == kTextCellContentBoss)
			{
				result = "kTextCellContentBoss";
				break;
			}
			else if (classID == kTextStoryBoss)
			{
				result = "kTextStoryBoss";
				break;
			}
			else if (classID == kFrameListBoss)
			{
				result = "kFrameListBoss";
				break;
			}
			else if (classID == kTextCellContentBoss)
			{
				result = "kTextCellContentBoss";
				break;
			}
			else if (classID == kTextCellParcelBoss)
			{
				result = "kTextCellParcelBoss";
				break;
			}
			else if (classID == kFrameItemBoss)
			{
				result = "kFrameItemBoss";
				break;
			}
			else if (classID == kTOPFrameItemBoss)
			{
				result = "kTOPFrameItemBoss";
				break;
			}
			else if (classID == kTableModelBoss)
			{
				result = "kTableModelBoss";
				break;
			}
			else if (classID == kTableFrameBoss)
			{
				result = "kTableFrameBoss";
				break;
			}
			else
			{
				char buf[64];
				sprintf(buf,"unknown(0x%x)",classID.Get());
				result = PMString(buf);
			}
		}
	} while (false);
	return result;
}


// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/** Makes the snippet SnpInspectTextModel available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run
*/
class _SnpRunnerInspectTextModel : public SnpRunnable
{
	public:
		// SnippetRunner framework hooks.
		_SnpRunnerInspectTextModel();
		virtual		~_SnpRunnerInspectTextModel();
		bool16			CanRun(ISnpRunnableContext* runnableContext);
		ErrorCode		Run(ISnpRunnableContext* runnableContext);		
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTextSelectionTargetContext;}
};

/*
*/
_SnpRunnerInspectTextModel::_SnpRunnerInspectTextModel() : SnpRunnable("InspectTextModel")
{
	this->SetDescription("Reports character data and other properties of story");
	this->SetPreconditions("text selection");
	this->SetCategories("sdk_snippet, sdk_text");
}

/*
*/
_SnpRunnerInspectTextModel::~_SnpRunnerInspectTextModel()
{
}

/*
*/
bool16 _SnpRunnerInspectTextModel::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {		
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil) {
			break;
		}
		InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
		ASSERT(textFocus);
		if (textFocus == nil) {
			break;
		}
		result = kTrue;
	} while(false);
	return result;
}

/*
*/
ErrorCode _SnpRunnerInspectTextModel::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do {
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil) {
			SNIPLOG("Please select a text frame and try again");
			break;
		}
		InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
		ASSERT(textFocus);
		if (textFocus == nil) {
			break;
		}

		// Prompt for parameter values.
		K2Vector<PMString> choices;
		choices.push_back(PMString("Stories")); //0
		choices.push_back(PMString("Characters")); //1
		choices.push_back(PMString("Paragraphs")); //2
		choices.push_back(PMString("Paragraph attribute runs")); //3
		choices.push_back(PMString("Point sizes")); //4
		choices.push_back(PMString("Owned items")); //5	
		choices.push_back(PMString("Lines")); //6		
		choices.push_back(PMString("Story Threads")); // 7
		choices.push_back(PMString("Dictionaries")); //8
		choices.push_back(PMString("Parcels")); //9
		choices.push_back(PMString("Strands")); //10	
		choices.push_back(PMString("Track Changes Info")); //11	
		choices.push_back(PMString("Change Records")); //12	
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 choice = parameterUtils->GetChoice(PMString("What story data do you want to inspect?"), choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Echo back to the user the choice they made and the story
		// and range of text that is to be reported on.
		SNIPLOG("%s", choices[choice].GetPlatformString().c_str());
		InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel());
		RangeData rangeData = textTarget->GetRange();
		TextIndex start = rangeData.Start(nil);
		TextIndex end = rangeData.End();
		if (rangeData.Length() == 0) {
			start = 0;
			end = textModel->TotalLength();
		}
		InDesign::TextRange range(textModel, start, end - start);


		// Run the requested report.
		SnpInspectTextModel instance(range);
		instance.ReportTextRange();
		if (choice == 0) {
			status = instance.ReportStories();
		}
		else if (choice == 1) {
			status = instance.ReportCharacters();
		}
		else if (choice == 2) {
			status = instance.ReportParagraphs();
		}
		else if (choice == 3) {
			status = instance.CountStoryParaAttrRuns();
		}
		else if (choice == 4) {
			status = instance.InspectStoryPointSizes();
		}
		else if (choice == 5) {
			status = instance.CountStoryOwnedItems();
		}	
		else if (choice == 6) {
			status = instance.ReportLines();
		}	
		else if (choice == 7) {
			status = instance.InspectStoryThreads();
		}
		else if (choice == 8) {
			status = instance.InspectStoryThreadDicts();
		}
		else if (choice == 9) {
			status = instance.InspectParcels();
		}
		else if (choice == 10) {
			status = instance.ReportStrands();
		}
		else if (choice == 11) {
			status = instance.ReportChangeInfo();
		}
		else if (choice == 12) 
		{
			status = instance.InspectTrackChange();
		}
	} while(false);

	return status;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerInspectTextModel instance_SnpRunnerInspectTextModel;
DEFINE_SNIPPET(_SnpRunnerInspectTextModel) 	

//End, SnpInspectTextModel.cpp

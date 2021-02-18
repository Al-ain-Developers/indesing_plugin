//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateTextFrame.cpp $
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
//  Copyright 2011 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IGraphicFrameData.h"
#include "ITextColumnSizer.h"
#include "ITextColumnData.h"
#include "IMultiColumnTextFrame.h"
#include "ITextFrameColumn.h"
#include "IFrameList.h"
#include "IFrameListComposer.h"
#include "ITextModel.h"
#include "IHierarchy.h"
#include "IGeometry.h"
#include "IParcel.h"
#include "IParcelList.h"
#include "ITextParcelList.h"
#include "ITextParcelListComposer.h"
#include "ITextInset.h"
#include "ITextWrapFacade.h"
#include "IItemLockData.h"
#include "IWaxStrand.h"
#include "IWaxIterator.h"
#include "IWaxLine.h"
#include "IActiveContext.h"
#include "ILayoutTarget.h"
#include "ISelectionManager.h"
#include "ILayoutSelectionSuite.h"
#include "ITextSelectionSuite.h"
#include "IPageItemTypeUtils.h"
#include "ICommand.h"
#include "ITool.h"
#include "IToolBoxUtils.h"
#include "ITOPSplineData.h"
#include "ISharedContentFacade.h"
#include "ILinkManager.h"
#include "ILayoutUtils.h"
// General includes:
#include "TextRange.h"
#include "CmdUtils.h"
#include "UIDList.h"
#include "Utils.h"
#include "UIDRef.h"
#include "UIDList.h"
#include "RangeData.h"
#include "TextID.h"
#include "TextEditorID.h"	// kIBeamToolBoss
#include "PageItemScrapID.h" // kDeleteCmdBoss
#include "GenericID.h" // kConvertItemToTextCmdBoss
#include "PersistUtils.h"
#include "TransformUtils.h"
#include "textiterator.h"
#include "SDKFileHelper.h"
#ifdef DEBUG
	#include "DebugClassUtils.h"
#endif
#include "LocaleSetting.h"

// SDK includes:
#include "SDKLayoutHelper.h"

// Framework includes:
#include "SnipRunID.h"
#include "ISnpRunnableContext.h"
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"
#include "SnpTextModelHelper.h"
#if __INTEL_COMPILER || MACINTOSH
#include "K2Vector.tpp"
#endif

/**
	\li How to inspect the structure and properties of a text frame,
	\li how to create and delete a text frame,
	\li how to link text frames together so that text flows
		between them and how to unlink them,
	\li how change the properties of a text frame such as
		number of columns, the text inset, the text wrap mode,
	\li how to make sure text is composed and discover the
		range of text displayed by a text frame,
	\li how to estimate the composed depth of text in a frame,
	\li how to select text displayed in a frame.
	\li how to create linked story.

	Integrated the following 2.x code snippets in here so far.
		SnipNudgeNumTextCols.cpp
		SnipTextLinkCmd.cpp

  	@ingroup sdk_snippet
	@ingroup sdk_text

*/
class SnpManipulateTextFrame
{
public:

	/** Constructor.
	*/
	SnpManipulateTextFrame() {}

	/** Destructor
	*/
	virtual ~SnpManipulateTextFrame() {}

	/** Inspect the structure of a text frame.
		@param graphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
		@return	kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode	InspectTextFrame(const UIDRef& graphicFrameUIDRef);

	/** Inspect the structure of the frame list and story associated with a text frame.
		@param graphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
		@return	kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode	InspectFrameList(const UIDRef& graphicFrameUIDRef);

	/** Inspect the characters displayed in a text frame.
		@param graphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
		@return	kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode	InspectTextInFrame(const UIDRef& graphicFrameUIDRef);


	/** Inspect the frames that preceed and succeed the given text frame,
		text can flow between threaded frames.
		@param graphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
		@return	kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode	InspectThreadedTextFrames(const UIDRef& graphicFrameUIDRef);

	/** Create a new text frame and thread the out-port of the given text frame
		to the in-port of the new text frame.
		@param fromGraphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
		@return	kSuccess on success, other ErrorCode otherwise.
		*/
	UIDRef		CreateAndThreadTextFrame(const UIDRef& fromGraphicFrameUIDRef);

	/** Delete the given text frame.
		@param graphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
		@return	kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode	DeleteTextFrame(const UIDRef& graphicFrameUIDRef);

	/** Return kTrue if the given text frames can be threaded so that text flows
		between them, kFalse otherwise. There are a few checks made:
		\li the stories associated with the frames must be unlocked,
		\li if the story underlying toGraphicFrameUID is empty we can link the frame
			anywhere in the frame list, otherwise we must be appending toGraphicFrameUID
			onto the end of the frame list underlying fromGraphicFrameUID.

		@param	database containing frames to be threaded.
		@param	fromGraphicFrameUID reference to source text frame
		@param	toGraphicFrameUID reference to destination text frame.
		@return kTrue if the given text frames can be threaded so that text flows
		between them, kFalse otherwise.
	*/
	bool16		CanThreadTextFrames(IDataBase* database, const UID& fromGraphicFrameUID, const UID& toGraphicFrameUID);

	/** Connects text flow between text frames using kTextLinkCmdBoss. The out-port of
		the frame given by parameter fromGraphicFrameUID is linked to the in-port
		of the frame given by parameter toGraphicFrameUID.
		@param	database containing objects to be linked.
		@param	fromGraphicFrameUID reference to source text frame.
		@param	toGraphicFrameUID reference to destination text frame.
		@return	kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode	ThreadTextFrames(IDataBase* database, const UID& fromGraphicFrameUID, const UID& toGraphicFrameUID);

	/** Return kTrue if the given text frames can be unthreaded so that text
		no longer flows between them, kFalse otherwise.
		@param graphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
		@return kTrue if the given text frames can be unthreaded so that text
			no longer flows between them, kFalse otherwise.
	*/
	bool16		CanUnthreadTextFrame(const UIDRef& graphicFrameUIDRef);

	/** Disconnect text flow between text frames using kTextUnlinkCmdBoss.
		@param graphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
		@return	kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode	UnthreadTextFrame(const UIDRef& graphicFrameUIDRef);


	/** Add a column to the given text frame using kChangeNumberOfColumnsCmdBoss.
		@param graphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
		@return	kSuccess on success, other ErrorCode otherwise.
		@see kChangeNumberOfColumnsCmdBoss
	*/
	ErrorCode	IncrementNumberOfColumns(const UIDRef& graphicFrameUIDRef);

	/** Adjust the text inset applied to the given text frame using kSetTextInsetCmdBoss.
		@param graphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
		@param increment the adjustment to be made to the inset on all sides.
		@return	kSuccess on success, other ErrorCode otherwise.
		@see kSetTextInsetCmdBoss
		@see ITextFrameOptionsSuite and ITextFrameOptionsData
		@see ITextFrameDialogUtils/ITextFrameOptionsData
	*/
	ErrorCode	IncrementTextInset(const UIDRef& graphicFrameUIDRef, const PMReal& increment);

	/** Adjust the stand off mode of the given frame using ITextWrapFacade.
		@param graphicFrameUIDRef reference to the frame object (kSplineItemBoss).
		@param mode the kind of stand off to be applied.
		@return	kSuccess on success, other ErrorCode otherwise.
		@see ITextWrapFacade
		@see ITextWrapSuite
		@see kStandOffModeCmdBoss, kStandOffFormCmdBoss, kStandOffMarginCmdBoss
	*/
	ErrorCode	ChangeTextWrapMode(const UIDRef& graphicFrameUIDRef, IStandOff::mode mode);


	/** Select all of the text displayed by the given frame.
		@param graphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
		@param selectionManager
		@return	kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode	SelectTextInFrame(const UIDRef& graphicFrameUIDRef, ISelectionManager* selectionManager);

	/** Prompt for a TextIndex then select the frame displaying the character
		at that position.
		@param graphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
		@param selectionManager
		@return	kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode	SelectFrameDisplayingTextIndex(const UIDRef& graphicFrameUIDRef, ISelectionManager* selectionManager);

	/** Create an internal or external linked story for the text diaplayed by the given frame.
		@param sourceTextFrameRef reference to the text frame's kSplineItemBoss object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode   CreateLinkedStory(const UIDRef& sourceTextFrameRef);

	/** Prompt for a TextIndex then select the character at that position.
		@param graphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
		@param selectionManager
		@return	kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode	SelectTextAtTextIndex(const UIDRef& graphicFrameUIDRef, ISelectionManager* selectionManager);

	/** Activate kIBeamToolBoss if a text tool is not already active.
		@return kTrue on success, kFalse otherwise.
		*/
	bool16		ActivateTextEditor();


	/** Return kTrue if the given frame is a text frame, kFalse otherwise.
		@param graphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
	*/
	bool16		IsTextFrame(const UIDRef& graphicFrameUIDRef);

	/** Return UID of the multi-column item (kMultiColumnItemBoss) associated with
		the given text frame, kInvalidUID if none.
		@param graphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
		@return UID of the multi-column item (kMultiColumnItemBoss) associated with
		the given text frame, kInvalidUID if none.
	*/
	UID			GetTextContentUID(const UIDRef& graphicFrameUIDRef);

	/** Return kTrue if text flows into the given frame another frame or
		if text flows out of the given frame into another frame, kFalse otherwise.
		@param graphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
	*/
	bool16		IsThreadedTextFrame(const UIDRef& graphicFrameUIDRef);

	/** Return reference to the frame(kSplineItemBoss) into which
			text from the given frame flows, UIDRef::gNull if there
			is no next frame.
		@param graphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
		@return reference to the frame(kSplineItemBoss) into which
			text from the given frame flows, UIDRef::gNull if there
			is no next frame.
	*/
	UIDRef		GetNextGraphicFrame(const UIDRef& graphicFrameUIDRef);

	/** Return reference to the frame(kSplineItemBoss) from which
			text flows into the given frame, UIDRef::gNull if there
			is no previous frame.
		@param graphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
		@return reference to the frame(kSplineItemBoss) from which
			text flows into the given frame, UIDRef::gNull if there
			is no previous frame.
	*/
	UIDRef		GetPreviousGraphicFrame(const UIDRef& graphicFrameUIDRef);

	/** Return reference to the text frame's kSplineItemBoss object.
		@param textFrameColumn
		@param isTOPFrameAllowed if kTrue and the given textFrameColumn is a text
			on a path frame then the kTOPSplineItemBoss reference will be returned,
			otherwise a kSplineItemBoss reference will be returned.
		@return reference to the text frame's kSplineItemBoss object.
	*/
	UIDRef		GetGraphicFrameRef(const InterfacePtr<ITextFrameColumn>& textFrameColumn, const bool16 isTOPFrameAllowed);


	/** Return the range of text displayed by the given text frame.
		@param mcf
		@return the range of text displayed by the given frame.
	*/
	InDesign::TextRange	GetTextFrameTextRange(IMultiColumnTextFrame* mcf);


	/** Return the range of text displayed by the given text frame.
		@param graphicFrameUIDRef reference to the text frame's kSplineItemBoss object.
		@return the range of text displayed by the given frame.
	*/
	InDesign::TextRange	GetFrameTextRange(const UIDRef& graphicFrameUIDRef);

	/** Return string containing the text displayed in the given text frame.
		@param mcf specifies the frame whose text is wanted.
		@return string containing the text displayed in the given text frame.
	*/
	WideString GetWideStringFromTextFrame(IMultiColumnTextFrame* mcf);

	/** Return interface pointer to text frame that displays the given
			TextIndex or nil if the TextIndex is not displayed.
		@param textModel
		@param at
		@return interface pointer to text frame that displays the given
			TextIndex or nil if the TextIndex is not displayed.
	*/
	ITextFrameColumn*	QueryTextFrameContaining(ITextModel* textModel, const TextIndex at);

private:
	PMString	ResolveClass(const ClassID& classID);


};

/*
*/
ErrorCode SnpManipulateTextFrame::InspectTextFrame(const UIDRef& graphicFrameUIDRef)
{
	ErrorCode status = kFailure;
	do {
		// Report information on the graphic frame.
		InterfacePtr<IGraphicFrameData> graphicFrameData(graphicFrameUIDRef, UseDefaultIID());
		SNIPLOG("graphicFrameUID=0x%x, graphicFrameClass=%s",
				graphicFrameUIDRef.GetUID().Get(),
				this->ResolveClass(::GetClass(graphicFrameData)).GetPlatformString().c_str());
		IDataBase* database = graphicFrameUIDRef.GetDataBase();

		// Report information on the multi-column item(kMultiColumnItemBoss)
		InterfacePtr<IHierarchy> graphicFrameHierarchy(graphicFrameUIDRef, UseDefaultIID());
		if (graphicFrameHierarchy == nil) {
			break;
		}
		ASSERT(graphicFrameHierarchy->GetChildCount() == 1);
		if (graphicFrameHierarchy->GetChildCount() != 1) {
			break;
		}
		InterfacePtr<IHierarchy> multiColumnItemHierarchy(graphicFrameHierarchy->QueryChild(0));
		ASSERT(multiColumnItemHierarchy);
		if (!multiColumnItemHierarchy) {
			break;
		}
		InterfacePtr<IMultiColumnTextFrame> multiColumnItemTextFrame(multiColumnItemHierarchy, UseDefaultIID());
		ASSERT(multiColumnItemTextFrame);
		if (!multiColumnItemTextFrame) {
			break;
		}
		InterfacePtr<ITextColumnSizer> textColumnSizer(multiColumnItemHierarchy, UseDefaultIID());
		ASSERT(textColumnSizer != nil);
		if (textColumnSizer == nil) {
			break;
		}
		SNIPLOG("multiColumnItemUID=0x%x, multiColumnItemClass=%s, numberOfColumns=%d, numberOfTextFrameColumns:%d",
			(::GetUID(multiColumnItemHierarchy)).Get(),
			this->ResolveClass(::GetClass(multiColumnItemHierarchy)).GetPlatformString().c_str(),
			textColumnSizer->GetNumberOfColumns(),
			multiColumnItemHierarchy->GetChildCount());

		// Report information on the story associated with the multi-column item.
		// The same story is associated with the multi-column item as is
		// associated with its children, the columns(kFrameItemBoss).
		UID storyUID = multiColumnItemTextFrame->GetTextModelUID();

		// Report information on the frame items(kFrameItemBoss) associated with the multi-column item.
		// Note that the number of TextFrameColumn children may be DIFFERENT
		// than the number of colums reported by the TextColumnSizer.
		SNIPLOG("frameItemIndex, frameItemUID, frameItemClass");
		for (int32 frameItemIndex = 0; frameItemIndex < multiColumnItemHierarchy->GetChildCount(); frameItemIndex++) {
			InterfacePtr<IHierarchy> frameItemHierarchy(multiColumnItemHierarchy->QueryChild(frameItemIndex));
			ASSERT(frameItemHierarchy);
			if (!frameItemHierarchy) {
				continue;
			}
			InterfacePtr<ITextFrameColumn> frameItemTFC(frameItemHierarchy, UseDefaultIID());
			ASSERT(frameItemTFC);
			if (!frameItemTFC) {
				continue;
			}
			ASSERT(frameItemTFC->GetTextModelUID() == storyUID);
			if (frameItemTFC->GetTextModelUID() != storyUID) {
				// The story associated with the multi-column item is different
				// from the story associated with this frame item. This should
				// not happen.
				break;
			}
			SNIPLOG("%d, 0x%x, %s",
				frameItemIndex,
				(::GetUID(frameItemTFC)).Get(),
				this->ResolveClass(::GetClass(frameItemTFC)).GetPlatformString().c_str());
		}

		// Report information on the associated story.
		InterfacePtr<ITextModel> textModel(database, storyUID, UseDefaultIID());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		SNIPLOG("storyUID=0x%x, storyClass=%s",
			storyUID.Get(),
			this->ResolveClass(::GetClass(textModel)).GetPlatformString().c_str());

		status = kSuccess;
	} while(false);
	return status;
}

/*
*/
ErrorCode SnpManipulateTextFrame::InspectFrameList(const UIDRef& graphicFrameUIDRef)
{
	ErrorCode status = kFailure;
	do {
		IDataBase* database = graphicFrameUIDRef.GetDataBase();
		InterfacePtr<IMultiColumnTextFrame> multiColumnItemTextFrame(database, this->GetTextContentUID(graphicFrameUIDRef), UseDefaultIID());
		ASSERT(multiColumnItemTextFrame != nil);
		if (multiColumnItemTextFrame == nil) {
			// The given frame is not a text frame.
			break;
		}
		InterfacePtr<IFrameList> frameList(multiColumnItemTextFrame->QueryFrameList());
		ASSERT(frameList);
		if (!frameList) {
			break;
		}

		// The information we inspect requires the text to be fully composed.
		// Check for damage and force composition if necessary.
		const int32 kNoDamage = -1;
		if (frameList->GetFirstDamagedFrameIndex() != kNoDamage) {
			InterfacePtr<IFrameListComposer> frameListComposer(frameList, UseDefaultIID());
			ASSERT(frameListComposer);
			if (!frameListComposer) {
				break;
			}
			frameListComposer->RecomposeThruLastFrame();
		}

		// Report information on each kFrameItemBoss in the frame list.
		SNIPLOG("#, frameItemUID, frameItemClass, start, span, multiColumnItemUID, multiColumnItemClass, graphicFrameUID, splineClass");
		for (int32 i = 0; i < frameList->GetFrameCount(); i++) {
			// Get information about the kFrameItemBoss.
			InterfacePtr<ITextFrameColumn> textFrameColumn(frameList->QueryNthFrame(i));
			ASSERT(textFrameColumn);
			if (!textFrameColumn) {
				break;
			}
			UID frameItemUID = ::GetUID(textFrameColumn);
			PMString frameItemClass = this->ResolveClass(::GetClass(textFrameColumn));
			// Index into the text model of the first character displayed by this kFrameItemBoss.
			TextIndex start = textFrameColumn->TextStart();
			// Number of characters displayed.
			int32 span = textFrameColumn->TextSpan();

			// Get information on the associated kMultiColumnItemBoss.
			InterfacePtr<IHierarchy> hierarchy(textFrameColumn, UseDefaultIID());
			ASSERT(hierarchy);
			if (!hierarchy) {
				break;
			}
			UID multiColumnItemUID = hierarchy->GetParentUID();
			InterfacePtr<IMultiColumnTextFrame> t_multiColumnItemTextFrame(database, multiColumnItemUID, UseDefaultIID());
			ASSERT(t_multiColumnItemTextFrame != nil);
			if (t_multiColumnItemTextFrame == nil) {
				break;
			}
			PMString multiColumnItemClass = this->ResolveClass(::GetClass(t_multiColumnItemTextFrame));

			// Get information on the associated kSplineItemBoss.
			hierarchy.reset(InterfacePtr<IHierarchy>(t_multiColumnItemTextFrame, UseDefaultIID()).forget());
			ASSERT(hierarchy);
			if (!hierarchy) {
				break;
			}
			UID graphicFrameUID = hierarchy->GetParentUID();
			InterfacePtr<IGraphicFrameData> graphicFrameData(database, graphicFrameUID, UseDefaultIID());
			ASSERT(graphicFrameData);
			if (!graphicFrameData) {
				break;
			}
			PMString splineClass = this->ResolveClass(::GetClass(graphicFrameData));

			SNIPLOG("%d, 0x%x, %s, %d, %d, 0x%x, %s, 0x%x, %s",
				i,
				frameItemUID.Get(),
				frameItemClass.GetPlatformString().c_str(),
				start,
				span,
				multiColumnItemUID.Get(),
				multiColumnItemClass.GetPlatformString().c_str(),
				graphicFrameUID.Get(),
				splineClass.GetPlatformString().c_str());
		}


		// Report information on the story associated with the frame.
		UID storyUID = multiColumnItemTextFrame->GetTextModelUID();
		InterfacePtr<ITextModel> textModel(database, storyUID, UseDefaultIID());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		PMString storyClass = this->ResolveClass(::GetClass(textModel));
		int32 primaryStoryThreadSpan = textModel->GetPrimaryStoryThreadSpan();
		int32 totalLength = textModel->TotalLength();
		SNIPLOG("storyUID=0x%x, storyClass=%s, primaryStoryThreadSpan=%d, totalLength=%d",
			storyUID.Get(),
			storyClass.GetPlatformString().c_str(),
			primaryStoryThreadSpan,
			totalLength);

		status = kSuccess;
	} while(false);
	return status;
}

/*
*/
ErrorCode SnpManipulateTextFrame::InspectTextInFrame(const UIDRef& graphicFrameUIDRef)
{
	ErrorCode status = kFailure;
	do {
		InterfacePtr<IMultiColumnTextFrame> mcf(graphicFrameUIDRef.GetDataBase(), this->GetTextContentUID(graphicFrameUIDRef), UseDefaultIID());
		ASSERT(mcf);
		if (!mcf) {
			break;
		}
		WideString wstr = this->GetWideStringFromTextFrame(mcf);
		PMString str(wstr);
		SNIPLOG("%s", str.GetPlatformString().c_str());
		status = kSuccess;
	} while(false);
	return status;
}


/*
*/
ErrorCode SnpManipulateTextFrame::InspectThreadedTextFrames(const UIDRef& graphicFrameUIDRef)
{
	ErrorCode status = kFailure;
	do {
		// Report information on the given graphic frame.
		InterfacePtr<IGraphicFrameData> graphicFrame(graphicFrameUIDRef, UseDefaultIID());
		ASSERT(graphicFrame);
		if (!graphicFrame) {
			break;
		}
		SNIPLOG("graphicFrameUID=0x%x, graphicFrameClass=%s",
				graphicFrameUIDRef.GetUID().Get(),
				this->ResolveClass(::GetClass(graphicFrame)).GetPlatformString().c_str());

		// Report information on the frames that preceed the given frame.
		UIDRef previousGraphicFrameUIDRef = this->GetPreviousGraphicFrame(graphicFrameUIDRef);
		if (previousGraphicFrameUIDRef != UIDRef::gNull) {
			do {
				InterfacePtr<IGraphicFrameData> previousGraphicFrame(previousGraphicFrameUIDRef, UseDefaultIID());
				SNIPLOG("previousGraphicFrameUID=0x%x, previousGraphicFrameClass=%s",
					previousGraphicFrameUIDRef.GetUID().Get(),
					this->ResolveClass(::GetClass(previousGraphicFrame)).GetPlatformString().c_str());
				previousGraphicFrameUIDRef = this->GetPreviousGraphicFrame(previousGraphicFrameUIDRef);
			} while(previousGraphicFrameUIDRef != UIDRef::gNull);
		}
		else {
			SNIPLOG("no preceeding frames");
		}

		// Report information on the frames that succeed the given frame.
		UIDRef nextGraphicFrameUIDRef = this->GetNextGraphicFrame(graphicFrameUIDRef);
		if (nextGraphicFrameUIDRef != UIDRef::gNull) {
			do {
				InterfacePtr<IGraphicFrameData> nextGraphicFrame(nextGraphicFrameUIDRef, UseDefaultIID());
				SNIPLOG("nextGraphicFrameUID=0x%x, nextGraphicFrameClass=%s",
					nextGraphicFrameUIDRef.GetUID().Get(),
					this->ResolveClass(::GetClass(nextGraphicFrame)).GetPlatformString().c_str());
				nextGraphicFrameUIDRef = this->GetNextGraphicFrame(nextGraphicFrameUIDRef);
			} while(nextGraphicFrameUIDRef != UIDRef::gNull);
		}
		else {
			SNIPLOG("no succeeding frames");
		}

		status = kSuccess;
	} while(false);
	return status;
}

/*
*/
UIDRef SnpManipulateTextFrame::CreateAndThreadTextFrame(const UIDRef& fromGraphicFrameUIDRef)
{
	UIDRef result = UIDRef::gNull;

	// Wrap the commands in a sequence.
	CmdUtils::SequencePtr seq;

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

		// Get the number of columns in the given text frame.
		InterfacePtr<ITextColumnSizer> frameColumnSizer(fromGraphicFrameUIDRef.GetDataBase(), this->GetTextContentUID(fromGraphicFrameUIDRef), UseDefaultIID());
		ASSERT(frameColumnSizer);
		if (!frameColumnSizer) {
			break;
		}
		int32 numberOfColumns = frameColumnSizer->GetNumberOfColumns();

		// Determine if the given text frame is vertical.
		InterfacePtr<IMultiColumnTextFrame> mcf(frameColumnSizer, UseDefaultIID());
		if (!mcf) {
			break;
		}
		InterfacePtr<IFrameList> frameList(mcf->QueryFrameList());
		if (!frameList) {
			break;
		}
		InterfacePtr<ITextParcelList> textParcelList(frameList,UseDefaultIID());
		if (!textParcelList) {
			break;
		}
		bool16 isVertical = textParcelList->GetIsVertical();
		bool16 isRightToLeft = textParcelList->GetIsRightToLeft();

		// Create the new frame based on the properties of the given text frame determined above.
		SDKLayoutHelper layoutHelper;
		UIDRef toGraphicFrameUIDRef = layoutHelper.CreateTextFrame(parentUIDRef, boundsInParentCoords, numberOfColumns, isVertical, nil, !isRightToLeft);

		if (toGraphicFrameUIDRef == UIDRef::gNull) {
			break;
		}

		// Link the out-port of the given text frame to the in-port of the new text frame.
		if (this->CanThreadTextFrames(fromGraphicFrameUIDRef.GetDataBase(), fromGraphicFrameUIDRef.GetUID(), toGraphicFrameUIDRef.GetUID()) == kFalse) {
			break;
		}
		if (this->ThreadTextFrames(fromGraphicFrameUIDRef.GetDataBase(), fromGraphicFrameUIDRef.GetUID(), toGraphicFrameUIDRef.GetUID()) != kSuccess) {
			break;
		}

		// If we get here we have successfully created a new text frame and linked it to the given text frame.
		result = toGraphicFrameUIDRef;

	} while(false);

	if (result == UIDRef::gNull)
		ErrorUtils::PMSetGlobalErrorCode(kFailure);
	return result;
}

/*
*/
ErrorCode SnpManipulateTextFrame::DeleteTextFrame(const UIDRef& graphicFrameUIDRef)
{
	ErrorCode status = kFailure;
	do {
		if (this->IsTextFrame(graphicFrameUIDRef) == kFalse) {
			break;
		}
		InterfacePtr<ICommand> deleteCmd(CmdUtils::CreateCommand(kDeleteCmdBoss));
		ASSERT(deleteCmd);
		if (!deleteCmd) {
			break;
		}
		deleteCmd->SetItemList(UIDList(graphicFrameUIDRef));
		status = CmdUtils::ProcessCommand(deleteCmd);
		ASSERT_MSG(status == kSuccess, "kDeleteCmdBoss failed");
	} while(false);
	return status;
}

/*
*/
bool16 SnpManipulateTextFrame::CanThreadTextFrames(IDataBase* database, const UID& fromGraphicFrameUID, const UID& toGraphicFrameUID)
{
	bool16 result = kFalse;
	do {
		UID fromMultiColumnItemUID = this->GetTextContentUID(UIDRef(database, fromGraphicFrameUID));
		if (fromMultiColumnItemUID == kInvalidUID) {
			break;
		}

		// Check if the story underlying fromGraphicFrameUID is locked.
		InterfacePtr<IMultiColumnTextFrame> fromMCF(database, fromMultiColumnItemUID, UseDefaultIID());
		ASSERT(fromMCF != nil);
		if (fromMCF == nil) {
			break;
		}
		InterfacePtr<ITextModel> fromTextModel(fromMCF->QueryTextModel());
		ASSERT(fromTextModel != nil);
		if (fromTextModel == nil) {
			break;
		}
		InterfacePtr<IItemLockData> fromTextLockData(fromTextModel, UseDefaultIID());
		ASSERT(fromTextLockData != nil);
		if (fromTextLockData == nil) {
			break;
		}
		if (fromTextLockData) {
			if (fromTextLockData->GetInsertLock() == kTrue || fromTextLockData->GetAttributeLock() == kTrue) {
				// A lock exists so don't link.
				break;
			}
		}

		// Check if the story underlying toGraphicFrameUID is locked.
		UID toMultiColumnItemUID = this->GetTextContentUID(UIDRef(database, toGraphicFrameUID));
		if (toMultiColumnItemUID == kInvalidUID) {
			break;
		}
		InterfacePtr<IMultiColumnTextFrame> toMCF(database, toMultiColumnItemUID, UseDefaultIID());
		ASSERT(toMCF != nil);
		if (toMCF == nil) {
			break;
		}
		InterfacePtr<ITextModel> toTextModel(toMCF->QueryTextModel());
		ASSERT(toTextModel != nil);
		if (toTextModel == nil) {
			break;
		}
		InterfacePtr<IItemLockData> toTextLockData(toTextModel, UseDefaultIID());
		ASSERT(toTextLockData != nil);
		if (toTextLockData == nil) {
			break;
		}
		if (toTextLockData) {
			if (toTextLockData->GetInsertLock() == kTrue || toTextLockData->GetAttributeLock() == kTrue) {
				// A lock exists so don't link.
				break;
			}
		}

		// If we get here there are no text locks on the stories involved in the link operation.

		// If the story underlying toGraphicFrameUID is empty we can link the frame
		// anywhere in the frame list.
		if (toTextModel->TotalLength() == 1) {
			result = kTrue;
			break;
		}

		// The story underlying toGraphicFrameUID is not empty.

		// Check we are appending toGraphicFrameUID onto the end of the frame list underlying fromGraphicFrameUID.
		InterfacePtr<IFrameList> fromFrameList(fromMCF->QueryFrameList());
		ASSERT(fromFrameList);
		if (!fromFrameList) {
			break;
		}
		InterfacePtr<IFrameList> toFrameList(toMCF->QueryFrameList());
		ASSERT(toFrameList);
		if (!toFrameList) {
			break;
		}
		if (!fromMCF->GetIsLastMCF()) {
			// Frame being linked from is not the last one in its frame list.
			break;
		}
		if (!toMCF->GetIsFirstMCF()) {
			// Frame being linked to is not the first one in its frame list.
			break;
		}

		// If we get here we are linking the last frame in the frame list underlying fromGraphicFrameUID
		// onto the first frame in the frame list underlying fromGraphicFrameUID.
		// We have an end to start link.
		result = kTrue;

	} while(false);
	return result;
}

/*
*/
ErrorCode SnpManipulateTextFrame::ThreadTextFrames(IDataBase* database, const UID& fromGraphicFrameUID, const UID& toGraphicFrameUID)
{
	ErrorCode status = kFailure;
	CmdUtils::SequencePtr seq;

	do {
		UID fromMultiColumnItemUID = this->GetTextContentUID(UIDRef(database, fromGraphicFrameUID));
		if (fromMultiColumnItemUID== kInvalidUID) {
			break;
		}
		InterfacePtr<IMultiColumnTextFrame> fromMCF(database, fromMultiColumnItemUID, UseDefaultIID());
		ASSERT(fromMCF != nil);
		if (fromMCF == nil) {
			break;
		}
		InterfacePtr<ITextModel> fromTextModel(fromMCF->QueryTextModel());
		ASSERT(fromTextModel != nil);
		if (fromTextModel == nil) {
			break;
		}

		UID toMultiColumnItemUID = this->GetTextContentUID(UIDRef(database, toGraphicFrameUID));
		if (toMultiColumnItemUID== kInvalidUID) {
			break;
		}
		InterfacePtr<IMultiColumnTextFrame> toMCF(database, toMultiColumnItemUID, UseDefaultIID());
		ASSERT(toMCF != nil);
		if (toMCF == nil) {
			break;
		}
		InterfacePtr<ITextModel> toTextModel(toMCF->QueryTextModel());
		ASSERT(toTextModel != nil);
		if (toTextModel == nil) {
			break;
		}

		// If there is text content in the story underlying the text frame
		// given by toGraphicFrameUID, append this text to the end of the story
		// underlying the text frame given by parameter fromGraphicFrameUID.
		if (toTextModel->TotalLength() > 1) {
			Utils<ITextUtils> textUtils;
			ASSERT(textUtils);
			if (!textUtils) {
				break;
			}
			InterfacePtr<ICommand> moveStoryRangeCmd(textUtils->QueryMoveStoryFromAllToEndCommand(::GetUIDRef(toTextModel), ::GetUIDRef(fromTextModel)));
			ASSERT(moveStoryRangeCmd);
			if (!moveStoryRangeCmd) {
				break;
			}
			status = CmdUtils::ProcessCommand(moveStoryRangeCmd);
			ASSERT_MSG(status == kSuccess, "ITextUtils::QueryMoveStoryFromAllToEndCommand failed");
			if (status != kSuccess) {
				break;
			}
			if (toTextModel->TotalLength() > 1) {
				ASSERT_FAIL("toTextModel->TotalLength() should be 1, the content should have been merged");
			}
		}

		// Link the text flow across kMultiColumnItemBoss objects.
		// Requires an item list containing pairs of UID that refer to the
		// objects to be linked together in from(out-port)/to(in-port) order.
	    InterfacePtr<ICommand> textLinkCmd(CmdUtils::CreateCommand(kTextLinkCmdBoss));
		ASSERT(textLinkCmd != nil);
		if (textLinkCmd == nil) {
			break;
		}
		UIDList itemList(database);
		itemList.Append(fromMultiColumnItemUID);
		itemList.Append(toMultiColumnItemUID);
		// Note that the story underlying the object referenced by toMultiColumnItemUID
		// must be empty. You need to move any text content it has before linking the
		// frames as illustrated by the code above.
		textLinkCmd->SetItemList(itemList);
		status = CmdUtils::ProcessCommand(textLinkCmd);
		ASSERT_MSG(status == kSuccess, "kTextLinkCmdBoss failed");

	} while (false);
	if (status != kSuccess)
		ErrorUtils::PMSetGlobalErrorCode(status);
	return status;
}

/*
*/
bool16 SnpManipulateTextFrame::CanUnthreadTextFrame(const UIDRef& graphicFrameUIDRef)
{
	bool16 result = kFalse;
	do {
		InterfacePtr<IMultiColumnTextFrame> mcf(graphicFrameUIDRef.GetDataBase(), this->GetTextContentUID(graphicFrameUIDRef), UseDefaultIID());
		ASSERT(mcf != nil);
		if (mcf == nil) {
			break;
		}
		InterfacePtr<IFrameList> frameList(mcf->QueryFrameList());
		ASSERT(frameList);
		if (!frameList) {
			break;
		}
		if (mcf->GetIsLastMCF()) {
			break;
		}

		// There's a frame comes after this one so this frame can be unlinked.
		result = kTrue;

		// kTextUnlinkCmdBoss breaks the frame list in two immediately
		// after the given frame. In order for it to work there
		// must be other frames after the given frame.

	} while (false);
	return result;
}

/*
*/
ErrorCode SnpManipulateTextFrame::UnthreadTextFrame(const UIDRef& graphicFrameUIDRef)
{
	ErrorCode result = kFailure;
	do {
		UIDRef multiColumnItemUIDRef = UIDRef(graphicFrameUIDRef.GetDataBase(), this->GetTextContentUID(graphicFrameUIDRef));
		InterfacePtr<ICommand> textUnlinkCmd(CmdUtils::CreateCommand(kTextUnlinkCmdBoss));
		ASSERT(textUnlinkCmd);
		if (!textUnlinkCmd) {
			break;
		}
		textUnlinkCmd->SetItemList(UIDList(multiColumnItemUIDRef));
		result = CmdUtils::ProcessCommand(textUnlinkCmd);
		ASSERT_MSG(result == kSuccess, "kTextUnlinkCmdBoss failed");
	} while (false);
	return result;
}

/*
*/
ErrorCode SnpManipulateTextFrame::IncrementNumberOfColumns(const UIDRef& graphicFrameUIDRef)
{
	ErrorCode result = kFailure;
	do {
		InterfacePtr<ITextColumnSizer> frameColumnSizer(graphicFrameUIDRef.GetDataBase(), this->GetTextContentUID(graphicFrameUIDRef), UseDefaultIID());
		ASSERT(frameColumnSizer);
		if (!frameColumnSizer) {
			break;
		}

		// Create kChangeNumberOfColumnsCmdBoss and get its data interface.
		InterfacePtr<ICommand> changeNumberOfColumnsCmd(CmdUtils::CreateCommand(kChangeNumberOfColumnsCmdBoss));
		ASSERT(changeNumberOfColumnsCmd);
		if (!changeNumberOfColumnsCmd) {
			break;
		}
		InterfacePtr<ITextColumnData> cmdColumnData(changeNumberOfColumnsCmd, UseDefaultIID());
		ASSERT(cmdColumnData);
		if (cmdColumnData == nil) {
			break;
		}

		// Increment the number of columns in the frame.
		cmdColumnData->SetNumberOfColumns(frameColumnSizer->GetNumberOfColumns() + 1);

		// Leave the other properties set by this command as is.
		cmdColumnData->SetGutterWidth(-1);
		cmdColumnData->UseFixedColumnSizing(-1);
		cmdColumnData->SetFixedWidth(-1);

		// Process the command.
		changeNumberOfColumnsCmd->SetItemList(UIDList(graphicFrameUIDRef));
		result = CmdUtils::ProcessCommand(changeNumberOfColumnsCmd);
		ASSERT_MSG(result == kSuccess, "kChangeNumberOfColumnsCmdBoss failed");
	} while(false);
	return result;
}

/*
*/
ErrorCode SnpManipulateTextFrame::IncrementTextInset(const UIDRef& graphicFrameUIDRef, const PMReal& increment)
{
	ErrorCode result = kFailure;
	do {
		// Get the current inset values and adjust them by the given increment.
		InterfacePtr<ITextInset> textInset(graphicFrameUIDRef, UseDefaultIID());
		if (!textInset) {
			break;
		}
		PMRect rectInset = textInset->GetRectInset();
		SNIPLOG("rectInset %f, %f, %f, %f",
			::ToDouble(rectInset.Left()),
			::ToDouble(rectInset.Top()),
			::ToDouble(rectInset.Right()),
			::ToDouble(rectInset.Bottom()));
		rectInset.Left() = rectInset.Left() + increment;
		rectInset.Top() = rectInset.Top() + increment;
		rectInset.Right() = rectInset.Right() + increment;
		rectInset.Bottom() = rectInset.Bottom() + increment;

		// Create kSetTextInsetCmdBoss.
		InterfacePtr<ICommand> setTextInsetCmd(CmdUtils::CreateCommand(kSetTextInsetCmdBoss));
		ASSERT(setTextInsetCmd);
		if (setTextInsetCmd == nil) {
			break;
		}
		InterfacePtr<ITextInset> textInsetCmdData(setTextInsetCmd, UseDefaultIID());
		if (!textInsetCmdData) {
			break;
		}
		textInsetCmdData->SetInset(rectInset.Top());
		textInsetCmdData->SetRectInset(rectInset);

		// Process the command.
		UIDList itemList(graphicFrameUIDRef);
		setTextInsetCmd->SetItemList(itemList);
		result = CmdUtils::ProcessCommand(setTextInsetCmd);
		if (result != kSuccess){
			ASSERT_FAIL("kSetTextInsetCmdBoss failed");
			break;
		}

		// Force recalculation of column widths based on changed text inset values
		// by processing kChangeNumberOfColumnsCmdBoss.
		InterfacePtr<ICommand> changeNumberOfColumnsCmd(CmdUtils::CreateCommand(kChangeNumberOfColumnsCmdBoss));
		ASSERT(changeNumberOfColumnsCmd);
		if (!changeNumberOfColumnsCmd) {
			break;
		}
		InterfacePtr<ITextColumnData> cmdColumnData(changeNumberOfColumnsCmd, UseDefaultIID());
		ASSERT(cmdColumnData);
		if (cmdColumnData == nil)
		{
			ASSERT_FAIL("cmdColumnData invalid");
			break;
		}
		cmdColumnData->SetNumberOfColumns(-1); // leave as is
		cmdColumnData->SetGutterWidth(-1); // leave as is
		cmdColumnData->UseFixedColumnSizing(-1); // leave as is
		cmdColumnData->SetFixedWidth(-1); // leave as is
		changeNumberOfColumnsCmd->SetItemList(itemList);
		result = CmdUtils::ProcessCommand(changeNumberOfColumnsCmd);
		if (result != kSuccess) {
			ASSERT_FAIL("kChangeNumberOfColumnsCmdBoss failed");
			break;
		}

	} while(false);
	return result;
}

/*
*/
ErrorCode SnpManipulateTextFrame::ChangeTextWrapMode(const UIDRef& graphicFrameUIDRef, IStandOff::mode mode)
{
	ErrorCode result = kFailure;
	do {
		Utils<Facade::ITextWrapFacade> textWrapFacade;
		if (!textWrapFacade) {
			break;
		}
		if (textWrapFacade->GetMode(graphicFrameUIDRef) == mode) {
			break;
		}
		bool16 setUserModified = kFalse;
		result = textWrapFacade->SetMode(UIDList(graphicFrameUIDRef), mode, setUserModified);
		ASSERT_MSG(result == kSuccess, "ITextWrapFacade::SetMode failed");
	} while(false);
	return result;
}

/*
*/
ITextFrameColumn* SnpManipulateTextFrame::QueryTextFrameContaining(ITextModel* textModel, const TextIndex at)
{
	InterfacePtr<ITextFrameColumn> resultTFC;
	do {
		SnpTextModelHelper textModelHelper;
		InterfacePtr<IParcel> parcel(textModelHelper.QueryParcelContaining(textModel, at));
		if (!parcel) {
			break;
		}
		resultTFC.reset(parcel->QueryFrame());
	// You could call IFrameList::QueryFrameContaining as below.
	///	InterfacePtr<IFrameList> frameList(textModel->QueryFrameList());
	//	ASSERT(frameList);
	//	if (frameList == nil) {
	//		break;
	//	}
	//	InterfacePtr<ITextFrameColumn> textFrameColumn(frameList->QueryFrameContaining(at, nil/*frameIndex*/, kFalse/*leanLeftSide*/));
	//	if (!textFrameColumn) {
	//		break;
	//	}
	//	result = textFrameColumn;
	} while(false);
	return resultTFC.forget();
}

/*
*/
ErrorCode SnpManipulateTextFrame::SelectTextInFrame(const UIDRef& graphicFrameUIDRef, ISelectionManager* selectionManager)
{
	ErrorCode status = kFailure;
	do {
		if (this->IsTextFrame(graphicFrameUIDRef) == kFalse) {
			break;
		}
		if (selectionManager == nil) {
			break;
		}
		InterfacePtr<ITextSelectionSuite> textSelectionSuite(selectionManager, UseDefaultIID());
		if (!textSelectionSuite) {
			// The selection manager does not support text selection. Might
			// be the selection manager for a structure view for example.
			break;
		}

		// Find the range of text displayed.
		InDesign::TextRange textRange = this->GetFrameTextRange(graphicFrameUIDRef);
		if (!textRange.IsValid()) {
			break;
		}

		// Select the text.
		InterfacePtr<ITextModel> textModel(textRange.QueryModel());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		UIDRef storyRef(::GetDataBase(textModel), ::GetUID(textModel));
		if (selectionManager->SelectionExists(kInvalidClass/*any CSB*/, ISelectionManager::kAnySelection)) {
			// Clear the selection
			selectionManager->DeselectAll(nil);
		}
		Selection::ScrollChoice doScroll = Selection::kScrollIntoView;
		const RangeData* scrollTo = nil;
		if (!textSelectionSuite->SetTextSelection(storyRef, textRange.GetRange(), doScroll, scrollTo)) {
			ASSERT_FAIL("ITxtSelectionSuite::SetTextSelection failed");
			break;
		}
		status = kSuccess;

	} while(false);
	return status;
}

/*
*/
ErrorCode SnpManipulateTextFrame::SelectTextAtTextIndex(const UIDRef& graphicFrameUIDRef, ISelectionManager* selectionManager)
{
	ErrorCode status = kFailure;
	do {
		if (this->IsTextFrame(graphicFrameUIDRef) == kFalse) {
			break;
		}
		if (selectionManager == nil) {
			break;
		}
		InterfacePtr<ITextSelectionSuite> textSelectionSuite(selectionManager, UseDefaultIID());
		if (!textSelectionSuite) {
			// The selection manager does not support text selection. Might
			// be the selection manager for a structure view for example.
			break;
		}

		// Find the text model underlying the given text frame.
		InterfacePtr<IGraphicFrameData> graphicFrameData(graphicFrameUIDRef, UseDefaultIID());
		if (graphicFrameData == nil) {
			break;
		}
		SDKLayoutHelper layoutHelper;
		InterfacePtr<ITextModel> textModel(layoutHelper.GetTextModelRef(graphicFrameData), UseDefaultIID());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}

		// Ask which TextIndex should be selected.
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 totalLength = textModel->TotalLength();
		TextIndex at = 0;
		if (totalLength > 1) {
			at = parameterUtils->GetInt32("TextIndex", 0, 0, totalLength-1);
			if (parameterUtils->WasDialogCancelled()) {
				break;
			}
		}

		// If we get here we know the parcel that displays the chosen TextIndex
		// is viewable.
		RangeData range(at, at+1);
		SNIPLOG("start=%d, end=%d",
			range.Start(nil),
			range.End());

		// Select that text.
		if (selectionManager->SelectionExists (kInvalidClass/*any CSB*/, ISelectionManager::kAnySelection)) {
			// Clear the selection
			selectionManager->DeselectAll(nil);
		}
		UIDRef storyRef = ::GetUIDRef(textModel);
		Selection::ScrollChoice doScroll = Selection::kScrollIntoView;
		const RangeData* scrollTo = nil;
		if (!textSelectionSuite->SetTextSelection(storyRef, range, doScroll, scrollTo)) {
			ASSERT_FAIL("ITxtSelectionSuite::SetTextSelection failed");
		}
		status = kSuccess;
	} while(false);
	return status;
}

/*
*/
ErrorCode SnpManipulateTextFrame::SelectFrameDisplayingTextIndex(const UIDRef& graphicFrameUIDRef, ISelectionManager* selectionManager)
{
	ErrorCode status = kFailure;
	do {
		if (this->IsTextFrame(graphicFrameUIDRef) == kFalse) {
			break;
		}
		if (selectionManager == nil) {
			break;
		}
		InterfacePtr<ILayoutSelectionSuite> layoutSelectionSuite(selectionManager, UseDefaultIID());
		if (!layoutSelectionSuite) {
			// The selection manager does not support layout selection. Might
			// be the selection manager for a galley or story view for example.
			break;
		}

		InterfacePtr<IGraphicFrameData> graphicFrameData(graphicFrameUIDRef, UseDefaultIID());
		if (graphicFrameData == nil) {
			break;
		}
		SDKLayoutHelper layoutHelper;
		InterfacePtr<ITextModel> textModel(layoutHelper.GetTextModelRef(graphicFrameData), UseDefaultIID());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}

		// Ask which TextIndex should be selected.
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 totalLength = textModel->TotalLength();
		TextIndex at = 0;
		if (totalLength > 1) {
			at = parameterUtils->GetInt32("TextIndex", 0, 0, totalLength-1);
			if (parameterUtils->WasDialogCancelled()) {
				break;
			}
		}

		InterfacePtr<ITextFrameColumn> textFrameColumn(this->QueryTextFrameContaining(textModel, at));
		if (!textFrameColumn) {
			break;
		}
		UIDRef graphicFrameRef = this->GetGraphicFrameRef(textFrameColumn, kFalse/*IsTOPFrameAllowed*/);
		if (graphicFrameRef == UIDRef::gNull) {
			break;
		}

		// Select that frame.
		if (selectionManager->SelectionExists (kInvalidClass/*any CSB*/, ISelectionManager::kAnySelection)) {
			// Clear the selection
			selectionManager->DeselectAll(nil);
		}
		layoutSelectionSuite->SelectPageItems(UIDList(graphicFrameRef), Selection::kReplace, Selection::kAlwaysCenterInView);

		status = kSuccess;
	} while(false);
	return status;
}

ErrorCode SnpManipulateTextFrame::CreateLinkedStory(const UIDRef& sourceTextFrameRef)
{
	ErrorCode result = kFailure;

	do {
		IDataBase* db = nil;
		UIDRef targetTextFrameRef;

		K2Vector<PMString> choices;
		choices.push_back(PMString("kCreateInternalLink"));
		choices.push_back(PMString("kCreateExternalLink"));
		Utils<ISnipRunParameterUtils> parameterUtils;

		int32 linkType = parameterUtils->GetChoice("Create internal or external link?", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		if(linkType == 0)
		{
			//create target text frame for internal link
			InterfacePtr<IGeometry> geometry(sourceTextFrameRef, UseDefaultIID());
			ASSERT(geometry);
			if (!geometry)
			{
				break;
			}
			PMMatrix inner2Parent = ::InnerToParentMatrix(geometry);
			PMRect boundsInParentCoords = geometry->GetStrokeBoundingBox(inner2Parent);
			boundsInParentCoords.MoveRel(boundsInParentCoords.Width() + 10.0, 0.0);

			InterfacePtr<IHierarchy> hierarchy(sourceTextFrameRef, UseDefaultIID());
			ASSERT(hierarchy);
			if (!hierarchy)
			{
				break;
			}
			//get the database of the source text frame
			db = sourceTextFrameRef.GetDataBase();
			UIDRef parentUIDRef = UIDRef(db, hierarchy->GetLayerUID());
			//create a target text frame
			SDKLayoutHelper layoutHelper;
			targetTextFrameRef = layoutHelper.CreateTextFrame(parentUIDRef, boundsInParentCoords);
		}
		else if (linkType == 1)
		{
			//create target text frame for external link
			SDKLayoutHelper layoutHelper;
			UIDRef documentUIDRef = layoutHelper.CreateDocument();
			layoutHelper.OpenLayoutWindow(documentUIDRef);

			InterfacePtr<ISpreadList> spreadList(documentUIDRef, UseDefaultIID());
			if(!spreadList) {
				break;
			}
			UIDRef spreadRef = UIDRef(documentUIDRef.GetDataBase(), spreadList->GetNthSpreadUID(0));
			UIDRef spreadLayerRef = layoutHelper.GetActiveSpreadLayerRef(spreadRef);
			//create a target text frame
			targetTextFrameRef = layoutHelper.CreateTextFrame(spreadLayerRef, PMRect(10, 10, 100, 100));
			//get the database of the target text frame
			db = targetTextFrameRef.GetDataBase();
		}
		else
		{
			//error link type
			break;
		}

		//get story of the source text frame
		InterfacePtr<IGraphicFrameData> srcGraphicFrameData(sourceTextFrameRef, UseDefaultIID());
		InterfacePtr<ITextModel> srcTextModel(Utils<ITextUtils>()->QueryTextModelFromSpline(srcGraphicFrameData) );
		UID sourceStory = GetUID(srcTextModel);
		UIDRef sourceStoryRef(sourceTextFrameRef.GetDataBase(), sourceStory);
		
		//get story of the target text frame
		InterfacePtr<IGraphicFrameData> targetGraphicFrameData(targetTextFrameRef, UseDefaultIID());
		InterfacePtr<ITextModel> targetTextModel(Utils<ITextUtils>()->QueryTextModelFromSpline(targetGraphicFrameData) );
		UID targetStory = GetUID(targetTextModel);
		UIDRef targetStoryRef(targetTextFrameRef.GetDataBase(), targetStory);

		//check if it can create share content link for source and target text frame
		if(Utils<Facade::ISharedContentFacade>()->CanCreateSharedContentLink(sourceStoryRef, targetStoryRef) )
		{
			UID linkUID;
			//create share content link for source and target text frame
			ErrorCode errCode = Utils<Facade::ISharedContentFacade>()->CreateSharedContentLink(sourceStoryRef, targetStoryRef, linkUID);
			if(errCode != kSuccess)
			{
				break;
			}
			InterfacePtr<const ILinkManager> linkManager(db, db->GetRootUID(), UseDefaultIID());
			InterfacePtr<ILink> link(linkManager->QueryLinkByUID(linkUID) );
			if (link == nil)
			{
				break;
			}
			//check the link type
			if(Utils<Facade::ISharedContentFacade>()->IsSharedContentInternalLink(link) )
			{
				SNIPLOG("An internal link is created!");
			}
			else if(Utils<Facade::ISharedContentFacade>()->IsSharedContentExternalLink(link) )
			{
				SNIPLOG("An external link is created!");
			}
			
			result = kSuccess;
		}
	} while(kFalse);
	
	return result;
}

/*
*/
bool16 SnpManipulateTextFrame::ActivateTextEditor()
{
	bool16 result = kFalse;
	do {
		InterfacePtr<ITool> activeTool(Utils<IToolBoxUtils>()->QueryActiveTool());
		if (activeTool->IsTextTool()) {
			// A text tool is already active so we've nothing to do.
			result = kTrue;
			break;
		}
		InterfacePtr<ITool> iBeamTool(Utils<IToolBoxUtils>()->QueryTool(kIBeamToolBoss));
		ASSERT(iBeamTool);
		if (!iBeamTool) {
			break;
		}
		result = Utils<IToolBoxUtils>()->SetActiveTool(iBeamTool);
	} while(false);
	return result;
}

/*
*/
bool16 SnpManipulateTextFrame::IsTextFrame(const UIDRef& graphicFrameUIDRef)
{
	bool16 result = kFalse;
	Utils<IPageItemTypeUtils> pageItemTypeUtils;
	if (pageItemTypeUtils && pageItemTypeUtils->IsTextFrame(graphicFrameUIDRef)) {
		result = kTrue;
	}
	return result;
}

/*
*/
UID SnpManipulateTextFrame::GetTextContentUID(const UIDRef& graphicFrameUIDRef)
{
	UID result = kInvalidUID;
	InterfacePtr<IGraphicFrameData> graphicFrameData(graphicFrameUIDRef, UseDefaultIID());
	if (graphicFrameData) {
		result = graphicFrameData->GetTextContentUID();
	}
	return result;
}

/*
*/
bool16 SnpManipulateTextFrame::IsThreadedTextFrame(const UIDRef& graphicFrameUIDRef)
{
	bool16 result = kFalse;
	do {
		InterfacePtr<IMultiColumnTextFrame> mcf(graphicFrameUIDRef.GetDataBase(), this->GetTextContentUID(graphicFrameUIDRef), UseDefaultIID());
		if (mcf == nil) {
			break;
		}
		InterfacePtr<IFrameList> frameList(mcf->QueryFrameList());
		ASSERT(frameList);
		if (!frameList) {
			break;
		}
		if (!mcf->GetIsFirstMCF()) {
			// There's a frame before this one so this frame is linked.
			result = kTrue;
			break;
		}
		if (!mcf->GetIsLastMCF()) {
			// There's a frame comes after this one so this frame is linked.
			result = kTrue;
			break;
		}
	} while (false);
	return result;
}

/*
*/
UIDRef SnpManipulateTextFrame::GetGraphicFrameRef(const InterfacePtr<ITextFrameColumn>& textFrameColumn, const bool16 isTOPFrameAllowed)
{
	UIDRef result = UIDRef::gNull;

	do {
		ASSERT(textFrameColumn);
		if (!textFrameColumn) {
			break;
		}

		// Check for a regular text frame by going up
		// the hierarchy till we find a parent object
		// that aggregates IGraphicFrameData. This is
		// the graphic frame that contains the text content.
		UIDRef graphicFrameDataUIDRef = UIDRef::gNull;
		InterfacePtr<IHierarchy> child(textFrameColumn, UseDefaultIID());
		if (child == nil) {
			break;
		}
		do {
			InterfacePtr<IHierarchy> parent(child->QueryParent());
			if (parent == nil) {
				break;
			}
			InterfacePtr<IGraphicFrameData> graphicFrameData(parent, UseDefaultIID());
			if (graphicFrameData != nil) {
				// We have a text frame.
				graphicFrameDataUIDRef = ::GetUIDRef(graphicFrameData);
				break;
			}
			child = parent;
		} while(child != nil);

		if (graphicFrameDataUIDRef == UIDRef::gNull) {
			break;
		}

		InterfacePtr<ITOPSplineData> topSplineData(graphicFrameDataUIDRef, UseDefaultIID());
		if (topSplineData) {
			// We have a text on a path frame.
			if (isTOPFrameAllowed == kTrue) {
				// Return the text on a path frame
				result = graphicFrameDataUIDRef;
			}
			else {
				// Return the graphic frame associated with the text on a path frame.
				UID mainSplineItemUID = topSplineData->GetMainSplineItemUID();
				ASSERT(mainSplineItemUID != kInvalidUID);
				result = UIDRef(graphicFrameDataUIDRef.GetDataBase(), mainSplineItemUID);
			}
		}
		else {
			// We have a normal graphic frame.
			result = graphicFrameDataUIDRef;
		}

	} while(false);

	return result;

}


/*
*/
UIDRef SnpManipulateTextFrame::GetNextGraphicFrame(const UIDRef& graphicFrameUIDRef)
{
	UIDRef result = UIDRef::gNull;
	do {
		InterfacePtr<IMultiColumnTextFrame> mcf(graphicFrameUIDRef.GetDataBase(), this->GetTextContentUID(graphicFrameUIDRef), UseDefaultIID());
		ASSERT(mcf != nil);
		if (mcf == nil) {
			break;
		}
		InterfacePtr<IFrameList> frameList(mcf->QueryFrameList());
		ASSERT(frameList);
		if (!frameList) {
			break;
		}
		int32 mcfLastFrameIndex = frameList->GetFrameIndex(mcf->GetUIDInFrameList(kTrue/*last*/));
		if (mcfLastFrameIndex == frameList->GetFrameCount() - 1) {
			// The given graphic frame contains the last frame in the frame list.
			// There is no next frame.
			break;
		}
		// Determine the graphic frame that contains the next kFrameItemBoss in the frame list.
		InterfacePtr<ITextFrameColumn> nextTFC(frameList->QueryNthFrame(mcfLastFrameIndex+1));
		if (!mcf) {
			break;
		}
		UIDRef nextGraphicFrameRef = this->GetGraphicFrameRef(nextTFC, kTrue/*isTOPFrameAllowed*/);
		result = nextGraphicFrameRef;
	} while (false);
	return result;
}

/*
*/
UIDRef SnpManipulateTextFrame::GetPreviousGraphicFrame(const UIDRef& graphicFrameUIDRef)
{
	UIDRef result = UIDRef::gNull;
	do {
		InterfacePtr<IMultiColumnTextFrame> mcf(graphicFrameUIDRef.GetDataBase(), this->GetTextContentUID(graphicFrameUIDRef), UseDefaultIID());
		ASSERT(mcf != nil);
		if (mcf == nil) {
			break;
		}
		InterfacePtr<IFrameList> frameList(mcf->QueryFrameList());
		ASSERT(frameList);
		if (!frameList) {
			break;
		}
		int32 mcfFirstFrameIndex = frameList->GetFrameIndex(mcf->GetUIDInFrameList(kFalse/*first*/));
		if (mcfFirstFrameIndex == 0) {
			// The given graphic frame contains the first frame in the frame list.
			// There is no previous frame.
			break;
		}
		// Determine the graphic frame that contains the previous kFrameItemBoss in the frame list.
		InterfacePtr<ITextFrameColumn> previousTFC(frameList->QueryNthFrame(mcfFirstFrameIndex-1));
		if (!previousTFC) {
			break;
		}
		UIDRef previousGraphicFrameRef = this->GetGraphicFrameRef(previousTFC, kTrue/*isTOPFrameAllowed*/);
		result = previousGraphicFrameRef;
	} while (false);
	return result;
}

/*
*/
InDesign::TextRange SnpManipulateTextFrame::GetTextFrameTextRange(IMultiColumnTextFrame* mcf)
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

/*
*/
WideString SnpManipulateTextFrame::GetWideStringFromTextFrame(IMultiColumnTextFrame* mcf)
{
	WideString result;
	do {
		InDesign::TextRange range = this->GetTextFrameTextRange(mcf);
		if (!range.IsValid()) {
			break;
		}
		SnpTextModelHelper textModelHelper;
		result = textModelHelper.GetWideStringFromTextRange(range);
	} while(false);
	return(result);
}


/*
*/
InDesign::TextRange SnpManipulateTextFrame::GetFrameTextRange(const UIDRef& graphicFrameUIDRef)
{
	InDesign::TextRange result;
	do {
		InterfacePtr<IMultiColumnTextFrame> mcf(graphicFrameUIDRef.GetDataBase(), this->GetTextContentUID(graphicFrameUIDRef), UseDefaultIID());
		ASSERT(mcf);
		if (!mcf) {
			break;
		}
		result = this->GetTextFrameTextRange(mcf);
	} while(false);
	return result;
}

/*
*/
PMString	SnpManipulateTextFrame::ResolveClass(const ClassID& classID)
{
	PMString result;

#ifdef DEBUG
	DebugClassUtilsBuffer classBuf;
	const char* className = DebugClassUtils::GetIDName(&classBuf, classID);
	if (className != nil) {
		result = className;
	}
#else
	typedef	KeyValuePair<int32, PMString> ClassName;
	typedef	K2Vector<ClassName> ClassNameDictionary;
	static	ClassNameDictionary gClassNameDict;
	if (gClassNameDict.size() == 0) {
		gClassNameDict.push_back(ClassName(0x201,	"kTextStoryBoss"));
		gClassNameDict.push_back(ClassName(0x263,	"kMultiColumnItemBoss"));
		gClassNameDict.push_back(ClassName(0x227,	"kFrameItemBoss"));
		gClassNameDict.push_back(ClassName(0x6201,	"kSplineItemBoss"));
		gClassNameDict.push_back(ClassName(0xb320,	"kTOPSplineItemBoss"));
		gClassNameDict.push_back(ClassName(0xb318,	"kTOPFrameItemBoss"));
		gClassNameDict.push_back(ClassName(0x262,	"kInlineBoss"));
	}

	int32 key = classID.Get();
	ClassNameDictionary::const_iterator iter = K2find(gClassNameDict.begin(), gClassNameDict.end(), key);
	if (iter != gClassNameDict.end()) {
		// ID's name is available.
		result = iter->Value();
	}
#endif

	if (result.empty()) {
		// ID's name is not available, represent ID as hex string.
		char buf[16];
		sprintf(buf,"0x%x", classID.Get());
		result = buf;
	}

	return result;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

class _SnpRunnerManipulateTextFrame : public SnpRunnable
{

	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		*/
		_SnpRunnerManipulateTextFrame();

		/** Destructor
		*/
		virtual ~_SnpRunnerManipulateTextFrame();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if a document is open, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);

		/**	Don't present this snippet in the framework's UI if the
			product we are running under is InCopy.
			@return kTrue if the snippet can be loaded, kFalse otherwise.
		*/
		bool16 CanLoad() const;

		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunLayoutTargetContext;}
};

/* Constructor
*/
_SnpRunnerManipulateTextFrame::_SnpRunnerManipulateTextFrame() : SnpRunnable("ManipulateTextFrame")
{
	this->SetDescription("manipulates text layout objects of various kinds");
	this->SetPreconditions("text frame selected");
	this->SetCategories("sdk_snippet, sdk_text");
}

/* Destructor
*/
_SnpRunnerManipulateTextFrame::~_SnpRunnerManipulateTextFrame()
{
}

/*
*/
bool16 _SnpRunnerManipulateTextFrame::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
		if (!layoutTarget) {
			break;
		}
		UIDList itemList = layoutTarget->GetUIDList(kStripStandoffs);
		if (itemList.Length() != 1) {
			break;
		}
		SnpManipulateTextFrame instance;
		if (instance.IsTextFrame(itemList.GetRef(0)) == kFalse) {
			break;
		}

		// If we get here a layout selection exists of a single frame
		// and that frame has text content.
		result = kTrue;
	} while(false);
	return result;
}

/*
*/
ErrorCode _SnpRunnerManipulateTextFrame::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do {
		SnpManipulateTextFrame instance;
		// Find the selected text frame.
		InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
		if (!layoutTarget) {
			break;
		}
		UIDList itemList = layoutTarget->GetUIDList(kStripStandoffs);
		if (itemList.Length() != 1) {
			SNIPLOG("Please select a text frame");
			break;
		}
		UIDRef graphicFrameUIDRef = itemList.GetRef(0);
		if (instance.IsTextFrame(graphicFrameUIDRef) == kFalse) {
			SNIPLOG("Please select a text frame");
			break;
		}

		// Find the text frame manipluation to be performed.
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("Inspect text frame"));
		choices.push_back(PMString("Inspect frame list"));
		choices.push_back(PMString("Inspect text in frame"));
		choices.push_back(PMString("Create and link text frame"));
		choices.push_back(PMString("Delete text frame"));
		choices.push_back(PMString("Unlink text frame"));
		choices.push_back(PMString("Inspect linked text frames"));
		choices.push_back(PMString("Increment number of columns"));
		choices.push_back(PMString("Increment text inset"));
		choices.push_back(PMString("Change text wrap mode"));
		choices.push_back(PMString("Select text in frame"));
		choices.push_back(PMString("Select frame displaying TextIndex"));
		choices.push_back(PMString("Create linked story"));

		enum {kInspectTextFrame,
			kInspectFrameList,
			kInspectTextInFrame,
			kCreateAndThreadTextFrame,
			kDeleteTextFrame,
			kUnLinkTextFrame,
			kInspectThreadedTextFrames,
			kIncrementNumberOfColumns,
			kIncrementTextInset,
			kChangeTextWrapMode,
			kSelectTextInFrame,
			kSelectFrameDisplayingTextIndex,
			kCreateLinkedStory};

		int32 choice  = parameterUtils->GetChoice("operation?", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		SNIPLOG("%s", choices[choice].GetPlatformString().c_str());

		// Apply the manipulation.
		switch (choice)
		{
		case kInspectTextFrame:
			{
				status = instance.InspectTextFrame(graphicFrameUIDRef);
				break;
			}

		case kInspectFrameList:
			{
				status = instance.InspectFrameList(graphicFrameUIDRef);
				break;
			}

		case kInspectTextInFrame:
			{
				status = instance.InspectTextInFrame(graphicFrameUIDRef);
				break;
			}

		case kCreateAndThreadTextFrame:
			{
				UIDRef newFrameUIDRef = instance.CreateAndThreadTextFrame(graphicFrameUIDRef);
				if (newFrameUIDRef == UIDRef::gNull) {
					break;
				}
				status = kSuccess;
				break;
			}

		case kDeleteTextFrame:
			{
				status = instance.DeleteTextFrame(graphicFrameUIDRef);
				break;
			}

		case kUnLinkTextFrame:
			{
				if (instance.CanUnthreadTextFrame(graphicFrameUIDRef) == kFalse) {
					UIDRef previousGraphicFrameUIDRef = instance.GetPreviousGraphicFrame(graphicFrameUIDRef);
					if (previousGraphicFrameUIDRef == UIDRef::gNull) {
						break;
					}
					if (instance.CanUnthreadTextFrame(previousGraphicFrameUIDRef) == kFalse) {
						break;
					}
					graphicFrameUIDRef = previousGraphicFrameUIDRef;
				}
				status = instance.UnthreadTextFrame(graphicFrameUIDRef);
				break;
			}

		case kInspectThreadedTextFrames:
			{
				status = instance.InspectThreadedTextFrames(graphicFrameUIDRef);
				break;
			}

		case kIncrementNumberOfColumns:
			{
				status = instance.IncrementNumberOfColumns(graphicFrameUIDRef);
				break;
			}

		case kIncrementTextInset:
			{
				// Suite: ITextFrameOptionsSuite/ITextFrameOptionsData
				// Facade: ITextFrameDialogUtils/ITextFrameOptionsData
				// The above API's are hard to use from snippet code because they need
				// a data interface implementation ITextFrameOptionsData.
				const PMReal kInsetIncrement = 4.0;
				status = instance.IncrementTextInset(graphicFrameUIDRef, kInsetIncrement);
				break;
			}

		case kChangeTextWrapMode:
			{
				Utils<ISnipRunParameterUtils> parameterUtils;
				K2Vector<PMString> choices; // See IStandOff::mode
				choices.push_back(PMString("kNone"));
				choices.push_back(PMString("kBand"));
				choices.push_back(PMString("kNextFrame"));
				choices.push_back(PMString("kBoundingBox"));
				choices.push_back(PMString("kManualContour"));
				int32	index = parameterUtils->GetChoice("IStandOff::mode?", choices);
				IStandOff::mode choice;
				switch (index)
				{
					case 0:
					default:
						choice = IStandOff::kNone;
						break;
					case 1:
						choice = IStandOff::kBand;
						break;
					case 2:
						choice = IStandOff::kNextFrame;
						break;
					case 3:
						choice = IStandOff::kBoundingBox;
						break;
					case 4:
						choice = IStandOff::kManualContour;
						break;
				}
			
				if (parameterUtils->WasDialogCancelled()) {
					break;
				}
				status = instance.ChangeTextWrapMode(graphicFrameUIDRef, choice);
				break;
			}

		case kSelectTextInFrame:
			{
				status = instance.SelectTextInFrame(graphicFrameUIDRef, runnableContext->GetActiveContext()->GetContextSelection());
				break;
			}

		case kSelectFrameDisplayingTextIndex:
			{
				status = instance.SelectFrameDisplayingTextIndex(graphicFrameUIDRef, runnableContext->GetActiveContext()->GetContextSelection());
				break;
			}

		case kCreateLinkedStory:
			{
				status = instance.CreateLinkedStory(graphicFrameUIDRef);
				break;
			}
		default:
			{
				SNIPLOG("unrecognised choice");
				break;
			}
		}
	} while(false);
	return status;
}

/*
*/
bool16  _SnpRunnerManipulateTextFrame::CanLoad() const
{
	bool16 result = kTrue;
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS)) {
		// Text frames can be manipulated under InCopy
		// but we don't load this snippet because there's no pointer tool
		// to select a text frame with. If we loaded the Go button for the
		// snippet would pretty much always be disabled.
		result = kFalse;
	}
	return result;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerManipulateTextFrame instance_SnpRunnerManipulateTextFrame;
DEFINE_SNIPPET(_SnpRunnerManipulateTextFrame)

//End, SnpManipulateTextFrame.cpp

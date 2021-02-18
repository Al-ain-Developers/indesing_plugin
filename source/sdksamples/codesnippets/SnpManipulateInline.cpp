//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateInline.cpp $
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
#include "INewPageItemCmdData.h"
#include "ITextModel.h"
#include "IGeometry.h"
#include "IRangeData.h"
#include "IFrameUtils.h"
#include "IUIDData.h"
#include "ITextModelCmds.h"
#include "ISelectionManager.h"
#include "ILayoutTarget.h"
#include "ITextTarget.h"
#include "ITextFocus.h"
#include "IAnchoredObjectSuite.h"
#include "SDKLayoutHelper.h"

// General includes:
#include "Utils.h"
#include "SplineID.h"
#include "TextChar.h"
#include "UIDList.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	\li	How to create an inline within a story by processing kInsertILGCmdBoss.
	\li How to manipulate the type of inline (standard, aboveline or anchored), and how to 
		set the position using IAnchoredObjectSuite
	
  	@ingroup sdk_snippet
	@ingroup sdk_text

	@see kInsertILGCmdBoss
	@see IAnchoredObjectSuite
 */
class SnpManipulateInline 
{
	public:
		/** Constructor.
		 */
		SnpManipulateInline() {}

		/** Destructor.
		 */
		virtual			~SnpManipulateInline() {}

private:
		/** Creates a new inline frame in the given story.
			@param storyUIDRef refers to the story in which the inline is to be created.
			@param whereTextIndex index where the inline should be inserted.
			@return kSuccess on success, kFailure otherwise.
		*/
		ErrorCode InsertInline(const UIDRef& storyUIDRef, const TextIndex& whereTextIndex);

protected:
		/**	Create a frame. Note you can create a frame that contains
			any type of content, or no content at all, and make it into an inline.
			This method makes a graphic frame.
			@param database the frame should be created in.
			@param newFrameUIDRef OUT frame to be made into an inline. 
			@return kSuccess on success, other status otherwise.
			@postcondition the created frame is not parented on any hierarchy.
		*/
		ErrorCode CreateFrame(IDataBase* database, UIDRef& newFrameUIDRef);

		/**	Insert kTextChar_Inline into the text flow and
			process kChangeILGCmdBoss to make the given frame into an inline on
			the owned item strand(IItemStrand) of the text model(ITextModel).
			@param storyUIDRef refers to the story in which the inline is to be created.
			@param whereTextIndex index where the inline should be inserted.
			@param frameUIDRef frame to be made into an inline. Note this frame must not
			be parented on any hierarchy(IHierarchy). If you have a frame that is process 
			kRemoveFromHierarchyCmdBoss before calling this method.
			@return kSuccess on success, other status otherwise. 
		*/
		ErrorCode ChangeToInline(const UIDRef& storyUIDRef, const TextIndex& whereTextIndex, const UIDRef& frameUIDRef);
public:

		/** Creates a new inline frame in the given story. 
			@param iSnpRunnableContext IN the current context
			@return kSuccess on success, kFailure otherwise.
		*/
		ErrorCode InsertInline(ISnpRunnableContext* iSnpRunnableContext);

		/** Allows the position of the anchored item to be modified.
			This sets the type of the anchored item (to one of inline, above line or anchored).
			The position of the inline can be specified.
			@param iSnpRunnableContext IN the current context
			@return kSuccess on success, kFailure otherwise.
		*/
		ErrorCode ModifyAnchorPosition(ISnpRunnableContext* iSnpRunnableContext);
};

/*
*/
ErrorCode
SnpManipulateInline::ModifyAnchorPosition(ISnpRunnableContext* iSnpRunnableContext)
{
	ErrorCode status = kFailure;
	do {
		// this snippet requires an inline to be selected
		InterfacePtr<ILayoutTarget> iLayoutTarget(iSnpRunnableContext, UseDefaultIID());
		if (iLayoutTarget == nil) {
			SNIPLOG("Snippet expects an inline to be selected");
			break;
		}

		UIDList itemList = iLayoutTarget->GetUIDList( kStripStandoffs, kStripIfParentLocked);
		if (itemList.Length() == 0) {
			SNIPLOG("Snippet expects an inline to be selected");
			break;
		}

		// we modify the first item
		UIDRef itemToModify = itemList.GetRef(0);
        
		if (Utils<IFrameUtils>()->IsPageItemAnchoredObject(itemToModify) == kFalse){
			SNIPLOG("Snippet expects an inline to be selected");
			break;
		}

		InterfacePtr<IAnchoredObjectSuite> iAnchoredObjectSuite(iSnpRunnableContext->GetActiveContext()->GetContextSelection(), UseDefaultIID());
		if (iAnchoredObjectSuite == nil){
			ASSERT(iAnchoredObjectSuite);
			break;
		}

		if (iAnchoredObjectSuite->CanSetAnchoredObjectParams() == kFalse){
			SNIPLOG("Cannot set anchored object data field");
			break;
		}

		// we do not care what the inline preferences are, we modify a couple here...
		Utils<ISnipRunParameterUtils> parameterUtils;

		if (parameterUtils == nil){
			ASSERT(parameterUtils);
			break;
		}
		K2Vector<PMString> choices;
		choices.push_back(PMString("Standard inline"));
		choices.push_back(PMString("Above text line"));
		choices.push_back(PMString("Anchored elsewhere"));

		enum {kStandardInline, kAboveTextLine, kAnchoredElsewhere};

		int32 choice  = parameterUtils->GetChoice("Where should the inline be placed?", choices);
 		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// for standard inline, we have the potential for a Y offset
		// for "above line" we allow space before and space after
		// for anchored elsewhere, we allow x&y offset.

		switch(choice)
		{
			case kStandardInline:
			{
				PMReal yOffset = parameterUtils->GetPMReal("Y Offset",  0, 0, 50);
				if (parameterUtils->WasDialogCancelled()) {
					break;
				}

				if (iAnchoredObjectSuite->SetPosition(IAnchoredObjectData::kStandardInline)!=kSuccess){
					SNIPLOG("Error setting position type");
					break;
				}
				if (iAnchoredObjectSuite->SetYOffset(yOffset)!=kSuccess){
					SNIPLOG("Error setting position");
					break;
				}
				status = kSuccess;
				break;
			}
			case kAboveTextLine:
			{
				PMReal yAbove = parameterUtils->GetPMReal("Y Above",  0, 0, 50);
				if (parameterUtils->WasDialogCancelled()) {
					break;
				}

				PMReal yBelow = parameterUtils->GetPMReal("Y Below",  0, 0, 50);
				if (parameterUtils->WasDialogCancelled()) {
					break;
				}

				if (iAnchoredObjectSuite->SetPosition(IAnchoredObjectData::kAboveLine)!=kSuccess){
					SNIPLOG("Error setting position type");
					break;
				}

				if (iAnchoredObjectSuite->SetYOffset(yBelow)!=kSuccess){
					SNIPLOG("Error setting position");
					break;
				}

				if (iAnchoredObjectSuite->SetYOffsetAbove(yAbove)!=kSuccess){
					SNIPLOG("Error setting position");
					break;
				}
				status = kSuccess;
				break;
			}
			case kAnchoredElsewhere:
			{
				// for some text containers, e.g. text on a path, anchored inlines
				// are not supported. Texst the capability
				if (iAnchoredObjectSuite->CanSetAnchoredPosition() == kFalse){
					SNIPLOG("Cannot set the anchored position on this object");
					break;
				}
				PMReal yOffset = parameterUtils->GetPMReal("Y Offset",  0, 0, 500);
				if (parameterUtils->WasDialogCancelled()) {
					break;
				}

				PMReal xOffset = parameterUtils->GetPMReal("X Offset",  0, 0, 500);
				if (parameterUtils->WasDialogCancelled()) {
					break;
				}

				if (iAnchoredObjectSuite->SetPosition(IAnchoredObjectData::kAnchoredObject)!=kSuccess){
					SNIPLOG("Error setting position type");
					break;
				}

				// indicate the anchored item does not need to be contained within the height of the frame
				if (iAnchoredObjectSuite->SetPinPosition(kFalse)!=kSuccess){
					SNIPLOG("Error setting position type");
					break;
				}

				if (iAnchoredObjectSuite->SetYOffset(yOffset)!=kSuccess){
					SNIPLOG("Error setting position");
					break;
				}

				if (iAnchoredObjectSuite->SetXOffset(yOffset)!=kSuccess){
					SNIPLOG("Error setting position");
					break;
				}
				status = kSuccess;
				break;
			}
			default:
			{
				SNIPLOG("Invalid operation");
				break;
			}

		}
	}while(kFalse);
	return status;
}
/*
*/
ErrorCode 
SnpManipulateInline::InsertInline(const UIDRef& storyUIDRef, const TextIndex& whereTextIndex)	
{
	ErrorCode status = kFailure;
	CmdUtils::SequencePtr cmdSeq;
	do {

		UIDRef newFrameUIDRef;
		status = this->CreateFrame(storyUIDRef.GetDataBase(), newFrameUIDRef);
		ASSERT(status == kSuccess);
		if (status != kSuccess) {
			break;
		}
		status = this->ChangeToInline(storyUIDRef, whereTextIndex, newFrameUIDRef);
		ASSERT(status == kSuccess);
	} while (false);
	if (status != kSuccess)
		ErrorUtils::PMSetGlobalErrorCode(status);
	return status;
}

/*
*/
ErrorCode 
SnpManipulateInline::InsertInline(ISnpRunnableContext* iSnpRunnableContext)
{
	ErrorCode status = kFailure;
	do {
		InterfacePtr<ITextTarget> textTarget(iSnpRunnableContext, UseDefaultIID());
		if (textTarget == nil) {
			SNIPLOG("Please select a text frame and try again");
			break;
		}
		InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel());
		ASSERT(textModel);
		if (textModel == nil) {
			break;
		}
		RangeData	range = textTarget->GetRange();
		UIDRef storyUIDRef = ::GetUIDRef(textModel);
		status = this->InsertInline(storyUIDRef, range.Start(nil));
	}while(kFalse);
	return status;
}

/* 
*/
ErrorCode SnpManipulateInline::CreateFrame(IDataBase* database, UIDRef& newFrameUIDRef)
{
	// You can make any type of frame into an inline. Here we make a new graphic frame.	
	PMRect bounds(0, 0, 100, 100);
	SDKLayoutHelper layoutHelper;
	newFrameUIDRef = layoutHelper.CreateRectangleFrame(UIDRef(database, kInvalidUID), bounds);
	if (newFrameUIDRef)
		return kSuccess;
	else
		return kFailure;
}


/*
*/
ErrorCode SnpManipulateInline::ChangeToInline(const UIDRef& storyUIDRef, const TextIndex& whereTextIndex, const UIDRef& frameUIDRef)
{
	ErrorCode status = kFailure;
	do {
		// Validate parameters.
		InterfacePtr<ITextModel> textModel(storyUIDRef, UseDefaultIID());
		ASSERT(textModel != nil);
		if(!textModel) {
			break;
		}
		InterfacePtr<IGeometry> pageItemGeometry(frameUIDRef, UseDefaultIID());
		ASSERT(pageItemGeometry != nil);
		if (pageItemGeometry == nil) {
			break;
		}

		// Insert character in text flow to anchor the inline.
		boost::shared_ptr<WideString>	insertMe(new WideString);

		insertMe->Append(kTextChar_Inline); 
    	InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
		InterfacePtr<ICommand> insertTextCmd(textModelCmds->InsertCmd(whereTextIndex, insertMe));
		ASSERT(insertTextCmd != nil);
		status = CmdUtils::ProcessCommand(insertTextCmd);
		ASSERT(status == kSuccess);
		if(status != kSuccess) {
			break;
		}

		// Change the page item into an inline.
		InterfacePtr<ICommand> changeILGCmd(CmdUtils::CreateCommand(kChangeILGCmdBoss));
		ASSERT(changeILGCmd != nil);
		if (changeILGCmd == nil) {
			break;
		}
		InterfacePtr<IRangeData> rangeData(changeILGCmd, UseDefaultIID());
		ASSERT(rangeData != nil);
		if (rangeData == nil) {
			break;
		}
		rangeData->Set(whereTextIndex, whereTextIndex);
		InterfacePtr<IUIDData> ilgUIDData(changeILGCmd, UseDefaultIID());
		ASSERT(ilgUIDData != nil);
		if (ilgUIDData == nil) {
			break;
		}
		ilgUIDData->Set(frameUIDRef);
		changeILGCmd->SetItemList(UIDList(textModel));
		status = CmdUtils::ProcessCommand(changeILGCmd);
		ASSERT(status == kSuccess);

	} while(kFalse);
	return status;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
class _SnpRunnerManipulateInline : public SnpRunnable
{
	
	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerManipulateInline();

		/** Destructor.
		 */
		virtual			~_SnpRunnerManipulateInline();

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
_SnpRunnerManipulateInline::_SnpRunnerManipulateInline() : SnpRunnable("ManipulateInline")
{
	this->SetDescription("Insert inline at the text caret or select an inline");
	this->SetPreconditions("Text caret in a text frame or inline item selected");
	this->SetCategories("sdk_snippet, sdk_text");
}

/* Destructor.
*/
_SnpRunnerManipulateInline::~_SnpRunnerManipulateInline()
{
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerManipulateInline::CanRun(ISnpRunnableContext* runnableContext)
{
	// this snippet delegates the CanRun functionality to the individual sub-snippet
	return kTrue;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerManipulateInline::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		Utils<ISnipRunParameterUtils> parameterUtils;

		if (parameterUtils == nil){
			ASSERT(parameterUtils);
			break;
		}
		K2Vector<PMString> choices;
		choices.push_back(PMString("Create new inline"));
		choices.push_back(PMString("Modify anchored object position"));

		enum {kCreateInline, kModifyAnchorObjPosition};

		int32 choice  = parameterUtils->GetChoice("Which operation?", choices);
 		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		SNIPLOG("%s", choices[choice].GetPlatformString().c_str());

		SnpManipulateInline instance;

		switch (choice) 
		{
			case kCreateInline:
			{
				status = instance.InsertInline(runnableContext);
				break;
			}

			case kModifyAnchorObjPosition:
			{
				status = instance.ModifyAnchorPosition(runnableContext);
				break;
			}
			
			default:
			{
				SNIPLOG("Invalid option. Skipping.");
				break;
			}
		}
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerManipulateInline instance_SnpRunnerManipulateInline;
DEFINE_SNIPPET(_SnpRunnerManipulateInline) 	

// End, SnpManipulateInline.cpp


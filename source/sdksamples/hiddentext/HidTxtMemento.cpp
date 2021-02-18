//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtMemento.cpp $
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
#include "ITextModelMemento.h"
#include "ITextStoryThreadDictHier.h"
#include "ITextModel.h"
#include "IHidTxtModel.h"
#include "ITextStoryThreadDict.h"
#include "ICommand.h"
#include "IUIDData.h"

// General includes:
#include "VOSSavedData.h"
#include "CPMUnknown.h"
#include "CmdUtils.h"
#include "Trace.h"

// Project includes:
#include "HidTxtID.h"

/**	Implements the memento (ITextModelMemento) that manages the hidden text
	(kHidTxtModelBoss) owned item when it is affected by text model operations. For example
	they allow the kHidTxtModelBoss object and its associated story thread to be
	deleted when the TextIndex on which the hidden text is anchored gets deleted.

	
	@ingroup hiddentext
	@see ITextModelMemento
 */
class HidTxtMemento : public CPMUnknown<ITextModelMemento>
{
	public:
		/** Constructor.
			@param boss refers to boss class on which this interface is aggregated
		 */
		HidTxtMemento(IPMUnknown* boss);
		
		/** Desructor.
		 */
		virtual ~HidTxtMemento();	

	public:
		/** @see ITextModelMemento.
		 */
		virtual UID		GetAssociatedUID() const;

		/** @see ITextModelMemento.
		 */
		virtual ErrorCode	OnDelete(const UIDRef& story, 
								 TextIndex dataStart,
								 int32		dataLen,
								 const Text::StoryRangeList& subranges, 
								 K2Vector<InterfacePtr<ICommand> >& cmdList);

		/** @see ITextModelMemento.
		 */
		virtual ErrorCode	OnCut(const UIDRef& story, 
							  TextIndex dataStart,
							  int32		dataLen,
							  const Text::StoryRangeList& subranges);

		/** @see ITextModelMemento.
		 */
		virtual ErrorCode	OnCopyRange(PasteData* context);

		/** @see ITextModelMemento.
		 */
		virtual ErrorCode	OnReplace(const UIDRef& story, 
								  TextIndex dataStart,
								  int32		dataLen,
								  int32		replaceDataLen,
								  const Text::StoryRangeList& subranges, 
								  K2Vector<InterfacePtr<ICommand> >& cmdList);

		/** @see ITextModelMemento.
		 */
		virtual ErrorCode	TransferTo(PasteDataXRefContext* xRefContext);

		/** @see ITextModelMemento.
		 */
		virtual ErrorCode	OnPaste();

		/** @see ITextModelMemento.
		 */
		virtual bool16		MustHandleReplaceIndividually();

	private:
		/** Remove hidden text.
			@param doCut kTrue if hidden text should be cut, kFalse if hidden text should be deleted.
		 */
		virtual ErrorCode		RemoveContentFromStory(bool16 doCut);
		
		/** @return interface pointer to kHidTxtModelDeleteCmdBoss.
		 */
		virtual ICommand*		QueryHidTxtModelDeleteCmd() const;
		
		/** Process kHidTxtModelCopyCmdBoss.
			@param ownedItemUIDRef
			@param toStory
		 */
		virtual UID				ProcessHidTxtModelCopyCmd(const UIDRef& ownedItemUIDRef, const UIDRef& toStory) const;
		
		/** Set reference to owned item being managed by this memento.
			@param ownedItemUIDRef
		 */
		virtual void			SetOwnedItemUIDRef(const UIDRef& ownedItemUIDRef);
		
		/** Return reference to owned item being managed by this memento.
			@return reference to owned item being managed by this memento.
		 */
		virtual const UIDRef&	GetOwnedItemUIDRef() const;

	private:
		/** kTrue if memento came from a HidTxtMemento::CopyRange call, kFalse otherwise.
		 */
		bool16						fIsCopyRange;	
		boost::shared_ptr<PasteData>	fCopyRangeVOSAllSavedData;
};

/*
*/
CREATE_PMINTERFACE(HidTxtMemento, kHidTxtMementoImpl)

/*
*/
HidTxtMemento::HidTxtMemento(IPMUnknown* boss) : CPMUnknown<ITextModelMemento>(boss),
	fIsCopyRange(kFalse),
	fCopyRangeVOSAllSavedData()
{
	TRACEFLOW("HiddenText", "HidTxtMemento::Constructor()-->In/Out\n");
}

/*
*/
HidTxtMemento::~HidTxtMemento()
{
	TRACEFLOW("HiddenText", "HidTxtMemento::Destructor()-->In\n");

	TRACEFLOW("HiddenText", "HidTxtMemento::Destructor()-->Out\n");
}

/*
*/
UID HidTxtMemento::GetAssociatedUID() const
{
	UID result = this->GetOwnedItemUIDRef().GetUID();
	TRACEFLOW("HiddenText", "HidTxtMemento::GetAssociatedUID-->In/Out() uid=0x%x\n", result.Get());
	return result;
}

/*
//
*/
ErrorCode HidTxtMemento::OnDelete(const UIDRef& story, 
								 TextIndex dataStart,
								 int32		dataLen,
								 const Text::StoryRangeList& subranges, 
								 K2Vector<InterfacePtr<ICommand> >& cmdList)
{
	ErrorCode status = kFailure;
	TRACEFLOW("HiddenText", "HidTxtMemento::OnDelete-->In\n");

	// Remove the content the associated hidden text model has embedded in the story.
	status = this->RemoveContentFromStory(kFalse);

	// Add a command to delete the associated hidden text model.
	InterfacePtr<ICommand> cmd(this->QueryHidTxtModelDeleteCmd());
	if (cmd != nil) {
		cmdList.push_back(cmd);
	}

	TRACEFLOW("HiddenText", "HidTxtMemento::OnDelete-->Out\n");
	return status;
}

/*
*/
ErrorCode HidTxtMemento::OnCut(const UIDRef& story, 
							  TextIndex dataStart,
							  int32		dataLen,
							  const Text::StoryRangeList& subranges)
{
	ErrorCode status = kFailure;
	TRACEFLOW("HiddenText", "HidTxtMemento::OnCut-->In\n");

	status = this->RemoveContentFromStory(kTrue);

	TRACEFLOW("HiddenText", "HidTxtMemento::OnCut-->Out\n");
	return status;
}

/*
*/
ErrorCode HidTxtMemento::OnCopyRange(PasteData* context)
{
	ErrorCode status = kFailure;
	TRACEFLOW("HiddenText", "HidTxtMemento::OnCopyRange-->In\n");
	do {
		InterfacePtr<IHidTxtModel> hidTxtModel(this->GetOwnedItemUIDRef(), UseDefaultIID());
		ASSERT(hidTxtModel != nil);
		if (hidTxtModel == nil) {
			break;
		}
		ASSERT(hidTxtModel->GetConnectedToTextContent());

		// Copy the hidden text.
		TextIndex threadStart = kInvalidTextIndex;
		int32 threadSpan = 0;
		bool16 found = hidTxtModel->GetHiddenTextRange(threadStart, threadSpan);
		ASSERT(found == kTrue);
		if (!found) {
			break;
		}
		InterfacePtr<ITextModel> textModel(hidTxtModel->QueryTextModel());
		ASSERT(textModel != nil);
		if (!textModel) {
			break;
		}
		status = textModel->CopyRange(threadStart, threadSpan, fCopyRangeVOSAllSavedData);
		fIsCopyRange = kTrue;
	} while(false);

	TRACEFLOW("HiddenText", "HidTxtMemento::OnCopyRange-->Out\n");
	return status;
}

/*
*/
ErrorCode HidTxtMemento::OnReplace(const UIDRef& story, 
								  TextIndex dataStart,
								  int32		dataLen,
								  int32		replaceDataLen,
								  const Text::StoryRangeList& subranges, 
								  K2Vector<InterfacePtr<ICommand> >& cmdList)
{
	ErrorCode status = kFailure;
	TRACEFLOW("HiddenText", "HidTxtMemento::OnReplace-->In\n");

	status = this->OnDelete(story, dataStart, dataLen, subranges, cmdList); 

	TRACEFLOW("HiddenText", "HidTxtMemento::OnReplace-->Out\n");
	return status;
}

/*
*/
ErrorCode HidTxtMemento::TransferTo(PasteDataXRefContext* xRefContext)
{
	ErrorCode status = kFailure;
	TRACEFLOW("HiddenText", "HidTxtMemento::TransferTo-->In\n");
	ASSERT(xRefContext != nil);
	const UIDRef toStory(xRefContext->GetDestStoryRef());
	if (fIsCopyRange == kTrue) {
		// This memento came from a CopyRange operation. We start by creating
		// a copy in the target database of the the kHidTxtModelBoss object 
		// associated with the memento. Next the context needs to be updated 
		// to understand that the original UID has been replace with a new UID. Finally we
		// update the memento to reflect our new status...
		UID	newUID = this->ProcessHidTxtModelCopyCmd(this->GetOwnedItemUIDRef(), toStory);
		xRefContext->XRefBind(this->GetAssociatedUID(), newUID);
		this->SetOwnedItemUIDRef(UIDRef(toStory.GetDataBase(), newUID));
		// ...the memento now refers to the newly created copy.
		fIsCopyRange = kFalse;
	}
	else {
		//
		// We are moving an existing object to a new story.
		//
		if (xRefContext->GetSrcStoryRef() == toStory) {
			//
			// Same story
			//
			// We have nothing to do here since we are already part of the
			// Story we are being moved to.
			//
		}
		else if (xRefContext->GetSrcStoryRef().GetDataBase() == toStory.GetDataBase()) {
			//
			// Same database
			//
			// We have nothing to do here but we require fixup on paste to
			// connect us to the new story.
			//
		}
		else {
			//
			// Different database.
			//
			// This is very, very bad and indicates a logic error high up
			// outside the call to the TextModel. The problem is that we
			// cannot move the object so we are instead forced to duplicate
			// the existing object (remember, it is not an alias) and then
			// delete the original. Since there is no Undo of the Paste
			// operation a delete of the target and move to the source will
			// NOT result in the orinal object being restored - it will now
			// hava new UID.
			//
			ASSERT_FAIL("Error: Cannot move to different database!");
		}
	}

	// Transfer it to the new Story. 
	if (fCopyRangeVOSAllSavedData.get() != nil)
		status = fCopyRangeVOSAllSavedData->TransferTo(xRefContext); 

	TRACEFLOW("HiddenText", "HidTxtMemento::TransferTo-->Out\n");
	return status;
}

/*
*/
ErrorCode HidTxtMemento::OnPaste()
{ 
	ErrorCode status = kFailure;
	TRACEFLOW("HiddenText", "HidTxtMemento::OnPasteDone-->In\n");
	do {
		// At this stage the hidden text model should 
		// not be connected to its text content.
		InterfacePtr<IHidTxtModel> hidTxtModel(this->GetOwnedItemUIDRef(), UseDefaultIID());
		ASSERT(hidTxtModel != nil);
		if (hidTxtModel == nil) {
			break;
		}
		ASSERT(hidTxtModel->GetConnectedToTextContent() == kFalse);

		// Start connecting...

		InterfacePtr<ITextModel> textModel(hidTxtModel->QueryTextModel());
		ASSERT(textModel != nil);
		if (textModel == nil) {
			break;
		}
		InterfacePtr<ITextStoryThreadDictHier> storyThreadDictHier(textModel, UseDefaultIID());
		ASSERT(storyThreadDictHier != nil);
		if (storyThreadDictHier == nil) {
			break;
		}
		storyThreadDictHier->Insert(this->GetAssociatedUID());

		ASSERT(fCopyRangeVOSAllSavedData.get() != nil);
		if (fCopyRangeVOSAllSavedData.get() == nil) {
			break;
		}
		InterfacePtr<ITextStoryThreadDict> storyThreadDict(hidTxtModel, UseDefaultIID());
		TextIndex at = storyThreadDict->GetThreadBlockTextRange().GetStart();
		status = textModel->Paste(at, fCopyRangeVOSAllSavedData);
		if (status != kSuccess) {
			break;
		}
		// Done with the PasteData. The Undo of the Paste is a Delete.
		fCopyRangeVOSAllSavedData.reset();

		// ...connected.
		hidTxtModel->SetConnectedToTextContent(kTrue);

	} while(false);

	TRACEFLOW("HiddenText", "HidTxtMemento::OnPasteDone-->Out\n");
	return status;
}

/*
*/
bool16 HidTxtMemento::MustHandleReplaceIndividually()
{
	return kTrue;
}

/*
*/
ErrorCode HidTxtMemento::RemoveContentFromStory(bool16 doCut)
{
	ErrorCode status = kFailure;
	TRACEFLOW("HiddenText", "HidTxtMemento::RemoveContentFromStory-->In\n");
	do {
		// At this stage the hidden text model should be connected to its text content.
		InterfacePtr<IHidTxtModel> hidTxtModel(this->GetOwnedItemUIDRef(), UseDefaultIID());
		ASSERT(hidTxtModel != nil);
		if (hidTxtModel == nil) {
			break;
		}
		InterfacePtr<ITextModel> textModel(hidTxtModel->QueryTextModel());
		ASSERT(textModel != nil);
		if (textModel == nil) {
			break;
		}
		ASSERT(hidTxtModel->GetConnectedToTextContent() == kTrue);

		// Start disconnecting...
		hidTxtModel->SetConnectedToTextContent(kFalse);

		// Cut or delete the text range from the text model that stores the hidden text.
		TextIndex threadStart = kInvalidTextIndex;
		int32 threadSpan = 0;
		bool16 found = hidTxtModel->GetHiddenTextRange(threadStart, threadSpan);
		ASSERT(found == kTrue);
		if (found == kTrue) {
			if (doCut)
				status = textModel->Cut(threadStart, threadSpan, fCopyRangeVOSAllSavedData);
			else
				status = textModel->Delete(threadStart, threadSpan);

			if (status != kSuccess) {
				break;
			}
		}

		// Remove the hidden text model (kHidTxtModelBoss) from the story's dictionary hierarchy.
		InterfacePtr<ITextStoryThreadDictHier> storyThreadDictHier(textModel, UseDefaultIID());
		ASSERT(storyThreadDictHier != nil);
		if (storyThreadDictHier != nil) {
			storyThreadDictHier->Remove(this->GetAssociatedUID());
		}

		// ...disconnected.
		status = kSuccess;

	} while(false);
	TRACEFLOW("HiddenText", "HidTxtMemento::RemoveContentFromStory-->Out\n");
	return status;
}

/*
*/
ICommand* HidTxtMemento::QueryHidTxtModelDeleteCmd() const
{
	TRACEFLOW("HiddenText", "HidTxtMemento::QueryHidTxtModelDeleteCmd-->In()\n");
	InterfacePtr<ICommand> result;
	do {
		InterfacePtr<ICommand> deleteHidTxtModelCmd(CmdUtils::CreateCommand(kHidTxtModelDeleteCmdBoss));
		ASSERT(deleteHidTxtModelCmd != nil);
		if (deleteHidTxtModelCmd == nil) {
			break;
		}
		deleteHidTxtModelCmd->SetItemList(this->GetOwnedItemUIDRef());
		result = deleteHidTxtModelCmd;
	} while(false);
	TRACEFLOW("HiddenText", "HidTxtMemento::QueryHidTxtModelDeleteCmd-->Out() result=0x%x\n", result.get());
    return result.forget();
}

/*
*/
UID HidTxtMemento::ProcessHidTxtModelCopyCmd(const UIDRef& ownedItemUIDRef, const UIDRef& toStory) const
{
	TRACEFLOW("HiddenText", "HidTxtMemento::ProcessHidTxtModelCopyCmd-->In\n");
	UID	newItemUID = kInvalidUID;

	InterfacePtr<ICommand> hidTxtModelCopyCmd(CmdUtils::CreateCommand(kHidTxtModelCopyCmdBoss));
	if (hidTxtModelCopyCmd != nil) {
		hidTxtModelCopyCmd->SetItemList(UIDList(ownedItemUIDRef));
		InterfacePtr<IUIDData> cmdData(hidTxtModelCopyCmd, IID_IHIDTXTTOSTORYUIDDATA);
		cmdData->Set(toStory);
		if (CmdUtils::ProcessCommand(hidTxtModelCopyCmd) == kSuccess) {
			newItemUID = hidTxtModelCopyCmd->GetItemList()->First();
		}
	}

	TRACEFLOW("HiddenText", "HidTxtMemento::ProcessHidTxtModelCopyCmd-->Out\n");
	return newItemUID;
}

/*
*/
void HidTxtMemento::SetOwnedItemUIDRef(const UIDRef& ownedItemUIDRef)
{
	TRACEFLOW("HiddenText", "HidTxtMemento::SetOwnedItemUIDRef-->In\n");
	InterfacePtr<IUIDData> ownedItemUIDData(this, IID_IHIDTXTOWNEDITEMUIDDATA);
	ASSERT(ownedItemUIDData != nil);
	if (ownedItemUIDData != nil) {
		ownedItemUIDData->Set(ownedItemUIDRef);
	}
	TRACEFLOW("HiddenText", "HidTxtMemento::SetOwnedItemUIDRef-->Out\n");
}

/*
*/
const UIDRef& HidTxtMemento::GetOwnedItemUIDRef() const
{
	TRACEFLOW("HiddenText", "HidTxtMemento::GetOwnedItemUIDRef-->In\n");
	InterfacePtr<IUIDData> ownedItemUIDData(this, IID_IHIDTXTOWNEDITEMUIDDATA);
	ASSERT(ownedItemUIDData != nil);
	TRACEFLOW("HiddenText", "HidTxtMemento::SetOwnedItemUIDRef-->Out\n");
	return ownedItemUIDData->GetRef();
}

// End, HidTxtMemento.cpp
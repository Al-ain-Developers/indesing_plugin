//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtModel.cpp $
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
#include "IDataBase.h"
#include "IPMStream.h"
#include "ITextStoryThreadDictHier.h"
#include "ITextStoryThreadDict.h"
#include "IItemStrand.h"
#include "IOwnedItem.h"

// General includes:
#include "CmdUtils.h"
#include "TextChar.h"
#include "WideString.h"
// Removed from API at InDesign CS #include "UndoInfo.h" 
#include "VOSSavedData.h"
#include "PersistUtils.h"
#include "Trace.h"

// Project includes:
#include "HidTxtID.h"
#include "IHidTxtModel.h"

/**	Implements the hidden text model (IHidTxtModel).
	
	
	@ingroup hiddentext
	@see IHidTxtModel
 */
class HidTxtModel : public CPMUnknown<IHidTxtModel>
{
	public:
		/** Constructor.
			@param boss refers to boss class on which this interface is aggregated

		 */
							HidTxtModel(IPMUnknown* boss);
							
		/** Destructor.
		 */
		virtual				~HidTxtModel();	

	public:
		/** @see IHidTxtModel::QueryTextModel.
		 */
		virtual ITextModel*	QueryTextModel() const;
		
		/** @see IHidTxtModel::GetAnchorTextRange.
		 */		
		virtual bool16		GetAnchorTextRange(TextIndex& start, int32& span) const;
		
		/** @see IHidTxtModel::GetHiddenTextRange.
		 */
		virtual bool16		GetHiddenTextRange(TextIndex& start, int32& span) const;

		/** @see IHidTxtModel::AttachToTextModel.
		 */
		virtual ErrorCode	AttachToTextModel(UID textModelUID, const TextIndex& anchorTextIndex);
		
		/** @see IHidTxtModel::DetachFromTextModel.
		 */
		virtual ErrorCode	DetachFromTextModel();
		
		/** @see IHidTxtModel::GetConnectedToTextContent.
		 */
		virtual bool16		GetConnectedToTextContent() const;

		/** @see IHidTxtModel::SetConnectedToTextContent.
		 */
		virtual void		SetConnectedToTextContent(bool16 connected);

	private:
		bool16				fConnectedToTextContent;
		IDataBase*			fDB;

	public:
		/** Restores and saves this implementations persistent data.
		 */
		void				ReadWrite(IPMStream *s, ImplementationID id);

	private:
		/** Calls Dirty to indicate this implementations data has changed.
		 */
		void				DoDirty();
};

/* Make this persistent implementation available to the application.
*/
CREATE_PERSIST_PMINTERFACE(HidTxtModel, kHidTxtModelImpl)

/*
*/
HidTxtModel::HidTxtModel(IPMUnknown* boss) : CPMUnknown<IHidTxtModel>(boss),
	fDB(::GetDataBase(boss)),
	fConnectedToTextContent(kFalse)
{
	TRACEFLOW("HiddenText", "HidTxtUtils::Constructor()-->In/Out\n");
}

/*
*/
HidTxtModel::~HidTxtModel()
{
	TRACEFLOW("HiddenText", "HidTxtUtils::Destructor()-->In/Out\n");
}

/*
*/
ITextModel* HidTxtModel::QueryTextModel() const
{
	TRACEFLOW("HiddenText", "HidTxtModel::QueryTextModel()-->In\n");
	ITextModel* result = nil;
	// Ask boss object's owned item for the text model it is
	// associated with if any.
	InterfacePtr<IOwnedItem> ownedItem(this, UseDefaultIID());
	ASSERT(ownedItem != nil);
	if (ownedItem != nil) {
		result = ownedItem->QueryTextModel();
	}
	TRACEFLOW("HiddenText", "HidTxtModel::QueryTextModel()-->Out result=0x%x\n", result);
    return result;
}

/*
*/
bool16 HidTxtModel::GetAnchorTextRange(TextIndex& start, int32& span) const
{
	TRACEFLOW("HiddenText", "HidTxtModel::GetAnchorTextRange()-->In\n");
	bool16 isAnchored = kFalse;
	// Ask this boss object's story thread dictionary for the range
	// of text it is anchored on. Hidden text in this implementation
	// is always anchored on a single character so the span of this
	// range will always be 1.
	InterfacePtr<ITextStoryThreadDict> storyThreadDict(this, UseDefaultIID());
	if (storyThreadDict != nil) {
		Text::StoryRange anchorRange = storyThreadDict->GetAnchorTextRange(&isAnchored);
		if (isAnchored == kTrue) {
			start = anchorRange.GetStart();
			span = anchorRange.GetEnd() - start;
		}
	}
	TRACEFLOW("HiddenText", "HidTxtModel::GetAnchorTextRange()-->Out isAnchored=%d, start=%d, span=%d\n", 
		isAnchored,
		start,
		span);
	return isAnchored;
}

/*
*/
bool16 HidTxtModel::GetHiddenTextRange(TextIndex& start, int32& span) const
{
	TRACEFLOW("HiddenText", "HidTxtModel::GetHiddenTextRange()-->In\n");
	bool16 result = kFalse;
	do {
		// Use ITextModel::FindStoryThread to find the range of text in the
		// story where this boss object's hidden text is stored.
		InterfacePtr<ITextModel> textModel(this->QueryTextModel());
		ASSERT(textModel != nil);
		if (textModel == nil) {
			break;
		}
		const UID hidTxtModelUID = ::GetUID(this);
		result = textModel->FindStoryThread(hidTxtModelUID, 
			kHidTxtStoryThreadDictKey, 
			&start, 
			&span);
		ASSERT_MSG(result == kTrue, "Hidden text story thread not found");
	} while(false);
	TRACEFLOW("HiddenText", "HidTxtModel::GetHiddenTextRange()-->Out result=%d, start=%d, span=%d\n",
		result,
		start,
		span);
	return result;
}

/*
*/
ErrorCode HidTxtModel::AttachToTextModel(UID textModelUID, const TextIndex& anchorTextIndex)
{
	TRACEFLOW("HiddenText", "HidTxtModel::AttachToTextModel()-->In textModelUID=0x%x, anchorTextIndex=%d\n", 
		textModelUID.Get(),
		anchorTextIndex);
	ErrorCode status = kFailure;
	do {
		// Associate this boss object's owned item at the TextIndex at which this object is anchored.
		InterfacePtr<ITextModel> textModel(fDB, textModelUID, UseDefaultIID());
		ASSERT(textModel != nil);
		if (textModel == nil) {
			break;
		}
		InterfacePtr<IItemStrand> itemStrand((IItemStrand*)textModel->QueryStrand(kOwnedItemStrandBoss, IItemStrand::kDefaultIID));		
		ASSERT(itemStrand != nil);
		if (itemStrand == nil) {
			break;
		}
		itemStrand->SetOwnedUID(anchorTextIndex, kHidTxtModelBoss, ::GetUID(this));

		// Add this boss object to the story's dictionary hierarchy so that it is
		// aware of its story thread dictionary.
		InterfacePtr<ITextStoryThreadDictHier> storyThreadDictHier(textModel, UseDefaultIID());
		ASSERT(storyThreadDictHier != nil);
		if (storyThreadDictHier == nil) {
			break;
		}
		storyThreadDictHier->Insert(::GetUID(this));

		// Figure out where this boss object's thread block is. This tells
		// us the TextIndex where we should insert the story thread.
		InterfacePtr<ITextStoryThreadDict> storyThreadDict(this, UseDefaultIID());
		ASSERT(storyThreadDict != nil);
		if (storyThreadDict == nil) {
			break;
		}
		TextIndex threadBlockStart = storyThreadDict->GetThreadBlockTextRange().GetStart();

		// Create a story thread to store this boss object's
		// hidden text and insert a kTextChar_CR as we do so.
		// Important Note: All story threads must be terminated
		// by a kTextChar_CR character.
		WideString initialContent;
		initialContent.Append(kTextChar_CR);
		// Undo is provided by HidTxtModelCreateCmd.
		status = textModel->InsertStoryThread
			(threadBlockStart, 
			::GetUID(this), 
			kHidTxtStoryThreadDictKey, 
			&initialContent);
		ASSERT(status == kSuccess);
		if (status != kSuccess) {
			break;
		}

		// Indicate this boss object is connected to its text.
		this->SetConnectedToTextContent(kTrue);

		status = kSuccess;

	} while(false);
	TRACEFLOW("HiddenText", "HidTxtModel::AttachToTextModel()-->Out status=%d\n", status);
	return status;
}

/*
*/
ErrorCode HidTxtModel::DetachFromTextModel()
{
	TRACEFLOW("HiddenText", "HidTxtModel::DetachFromTextModel()-->In\n");
	ErrorCode status = kFailure;
	do {
		// Delete the story thread.
		InterfacePtr<ITextModel> textModel(this->QueryTextModel());
		ASSERT(textModel != nil);
		if (textModel == nil) {
			break;
		}
		TextIndex storyThreadStart;
		int32 storyThreadSpan;
		bool16 storyThreadFound = textModel->FindStoryThread(::GetUID(this), 
			kHidTxtStoryThreadDictKey, 
			&storyThreadStart, 
			&storyThreadSpan);
		ASSERT(storyThreadFound == kTrue);
		if (storyThreadFound == kFalse) {
			break;
		}
		// Undo is provided by HidTxtModelCreateCmd.
		status = textModel->Delete(storyThreadStart, storyThreadSpan);
		ASSERT(status == kSuccess);

		// Remove this boss object from the story's story thread dictionary hierachy.
		InterfacePtr<ITextStoryThreadDictHier> storyThreadDictHier(textModel, UseDefaultIID());
		ASSERT(storyThreadDictHier != nil);
		if (storyThreadDictHier == nil) {
			break;
		}
		storyThreadDictHier->Remove(::GetUID(this));

		// Indicate this boss object is disconnected from its text.
		this->SetConnectedToTextContent(kFalse);

		// Remove this boss object's owned item from the text model.
		InterfacePtr<IItemStrand> itemStrand((IItemStrand*)textModel->QueryStrand(kOwnedItemStrandBoss, IID_IITEMSTRAND));
		ASSERT(itemStrand !=nil);
		if(itemStrand == nil) {
			break;
		}
		InterfacePtr<IOwnedItem> ownedItem(this, UseDefaultIID());
		ASSERT(ownedItem !=nil);
		if(ownedItem == nil) {
			break;
		}
		itemStrand->SetOwnedUID(ownedItem->GetTextIndex(), kHidTxtModelBoss, kInvalidUID);

		status = kSuccess;

	} while(false);
	TRACEFLOW("HiddenText", "HidTxtModel::DetachFromTextModel()-->Out status=%d\n", status);
	return status;
}

/*
*/
bool16 HidTxtModel::GetConnectedToTextContent() const
{
	TRACEFLOW("HiddenText", "HidTxtModel::GetConnectedToTextContent()-->In/Out fConnectedToTextContent=%d\n", fConnectedToTextContent);
    return fConnectedToTextContent;
}

/*
*/
void HidTxtModel::SetConnectedToTextContent(bool16 connected)
{
	TRACEFLOW("HiddenText", "HidTxtModel::SetConnectedToTextContent()-->In connected=%d\n", connected);
    if (fConnectedToTextContent != connected)
    {
		// Dirty must be called before changing the data.
		// Otherwise you get the assert below from AutoCmdUIDTrackingInfo.cpp (140)
		// "Interface data changed before calling Dirty(): must pre-dirty in order for auto undo to work."
		this->DoDirty(); 
        fConnectedToTextContent = connected;
    }
	TRACEFLOW("HiddenText", "HidTxtModel::SetConnectedToTextContent()-->Out\n");
}

/*
*/
void HidTxtModel::ReadWrite(IPMStream *s, ImplementationID id)
{
	TRACEFLOW("HiddenText", "HidTxtModel::ReadWrite()-->In\n");
	s->XferBool(fConnectedToTextContent);
	TRACEFLOW("HiddenText", "HidTxtModel::ReadWrite()-->Out\n");
}

/*
*/
void HidTxtModel::DoDirty(void)
{
	PreDirty(kHidTxtModelImpl);
}

// End, HidTxtModel

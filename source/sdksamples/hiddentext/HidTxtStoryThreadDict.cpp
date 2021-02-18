//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtStoryThreadDict.cpp $
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
#include "ITextStoryThreadDict.h"
#include "ITextStoryThread.h"
#include "ITextModel.h"
#include "ITextStoryThreadDictHier.h"
#include "IOwnedItem.h"

// Project includes:
#include "HidTxtID.h"
#include "IHidTxtModel.h"

/**	Implements ITextStoryThreadDict to manage a collection of associated
	story threads, in this implementation there is only one story thread
	in the dictionary, it has a fixed key given by kHidTxtStoryThreadDictKey.

	Many instances of hidden text can be embedded in a story but each has its
	own hidden text model (kHidTxtModelBoss) with its own dictionary
	(ITextStoryThreadDict) and story thread(ITextStoryThread).
	
	
	@ingroup hiddentext
	@see ITextStoryThreadDict
 */
class HidTxtStoryThreadDict : public CPMUnknown<ITextStoryThreadDict>
{
	public:
		/** Constructor.
			@param boss
		 */
		HidTxtStoryThreadDict(IPMUnknown* boss);
		
		/** Destructor.
		 */
		virtual ~HidTxtStoryThreadDict();	
	
	public:
		/** @see ITextStoryThreadDict.
		 */
		virtual ITextStoryThread*	QueryThread(uint32 key) const;
		
		/** @see ITextStoryThreadDict.
		 */
		virtual Text::StoryRange	GetAnchorTextRange(bool16* isAnchored) const;
		
		/** @see ITextStoryThreadDict.
		 */
		virtual Text::StoryRange	GetThreadBlockTextRange() const;
		
		/** @see ITextStoryThreadDict.
		 */
		virtual uint32				GetFirstKey();
		
		/** @see ITextStoryThreadDict.
		 */
		virtual uint32				GetNextKey();
};

/*
*/
CREATE_PMINTERFACE(HidTxtStoryThreadDict, kHidTxtStoryThreadDictImpl)

/*
*/
HidTxtStoryThreadDict::HidTxtStoryThreadDict(IPMUnknown* boss) : CPMUnknown<ITextStoryThreadDict>(boss)
{
	TRACEFLOW("HiddenText", "HidTxtStoryThreadDict::Constructor()-->In/Out\n");
}

/*
*/
HidTxtStoryThreadDict::~HidTxtStoryThreadDict()
{
	TRACEFLOW("HiddenText", "HidTxtStoryThreadDict::Destructor()-->In/Out\n");
}

/*
*/
ITextStoryThread* HidTxtStoryThreadDict::QueryThread(uint32 key) const
{
	TRACEFLOW("HiddenText", "HidTxtStoryThreadDict::QueryThread()-->In\n");
	ASSERT_MSG(key == kHidTxtStoryThreadDictKey, "Invalid key, hidden text only has one story thread with key = 0");
    InterfacePtr<ITextStoryThread> storyThread(this, UseDefaultIID());
	TRACEFLOW("HiddenText", "HidTxtStoryThreadDict::QueryThread()-->Out, storyThread=0x%x\n", storyThread.get());
    return storyThread.forget();
}

/*
*/
Text::StoryRange HidTxtStoryThreadDict::GetAnchorTextRange(bool16* isAnchored) const
{
	TRACEFLOW("HiddenText", "HidTxtStoryThreadDict::GetAnchorTextRange()-->In\n");
	Text::StoryRange result(0, 0);
	do {
		// Initialise isAnchored flag to false and update it later.
		ASSERT(isAnchored != nil);
		if (isAnchored != nil) {
			*isAnchored = kFalse;
		}

		// Use this boss object's owned item to find the anchor.
		InterfacePtr<IOwnedItem> ownedItem(this, UseDefaultIID());
		ASSERT(ownedItem != nil);
		if (ownedItem == nil) {
			break;
		}
		TextIndex anchorIndex = ownedItem->GetTextIndex();
		ASSERT(anchorIndex != kInvalidTextIndex);
		if (anchorIndex == kInvalidTextIndex) {
			// An invalid TextIndex for the anchor means we are not anchored.
			// We should be!
			break;
		}
		int32 anchorSpan = ownedItem->GetNumSpecialAnchorChars();
		result = Text::StoryRange(anchorIndex, anchorIndex + anchorSpan);
		
		// Set the isAnchoredFlag to indicate we are anchored.
		if (isAnchored != nil) {
			*isAnchored = kTrue;
		}

	} while(false);

	TRACEFLOW("HiddenText", "HidTxtStoryThreadDict::GetAnchorTextRange()-->Out start=%d, end=%d\n",
		result.GetStart(),
		result.GetEnd());
	return result;
}

/*
*/
Text::StoryRange HidTxtStoryThreadDict::GetThreadBlockTextRange() const
{
	TRACEFLOW("HiddenText", "HidTxtStoryThreadDict::GetThreadBlockTextRange()-->In\n");
	// All the story threads managed by a dictionary must be stored in a contiguous
	// range in the text model. This is known as the dictionary's thread block.
	Text::StoryRange result(0, 0);
	do {
		InterfacePtr<IHidTxtModel> hidTxtModel(this, UseDefaultIID());
		ASSERT(hidTxtModel != nil);
		if (hidTxtModel == nil) {
			break;
		}
		if (hidTxtModel->GetConnectedToTextContent() == kTrue) {
			// We are connected.
			// Ask this boss object where our thread block is.
			TRACEFLOW("HiddenText", " Connected - asking ourself where our thread block is\n");
			InterfacePtr<ITextStoryThread> storyThread(this, UseDefaultIID());
			ASSERT(storyThread != nil);
			if (storyThread == nil) {
				break;
			}

			result = Text::StoryRange(storyThread->GetTextStart(), storyThread->GetTextEnd());
			break; // done!
		}
		else {
			// We are not connected and need to figure out where our thread block should be. 
			// ITextStoryThreadDictHier on the story boss helps determine
			// what the next dictionary to the one being inserted is. You determine where your thread
			// block should go by inserting it at the beginning of the next dictionary's thread block or at
			// the end of the story, ITextModel::TotalLength, if there is no next dictionary.
			InterfacePtr<ITextModel> textModel(hidTxtModel->QueryTextModel());
			ASSERT(textModel != nil);
			if (textModel == nil) {
				break;
			}

			// If there is a next dictionary use it to figure out the TextIndex at
			// which its thread block starts.
			InterfacePtr<ITextStoryThreadDictHier> storyThreadDictHier(textModel, UseDefaultIID());
			if (storyThreadDictHier != nil) {
				UID	nextDictUID = storyThreadDictHier->NextUID(::GetUID(this));
				if (nextDictUID.IsValid()) {
					InterfacePtr<ITextStoryThreadDict> nextStoryThreadDict(::GetDataBase(this), nextDictUID, UseDefaultIID());
					if (nextStoryThreadDict != nil) {
						TextIndex nextThreadBlockStart = nextStoryThreadDict->GetThreadBlockTextRange().GetStart();
						if (nextThreadBlockStart != kInvalidTextIndex) {
							TRACEFLOW("HiddenText", " Not connected - asked next dictionary where it starts.\n");
							result = Text::StoryRange(nextThreadBlockStart, nextThreadBlockStart);
							break; // done!
						}
					}
				}
			}

			// Put our dictionary's thread block at the end of the story.
			TRACEFLOW("HiddenText", " Not connected - adding this dictionary's thread block to end of story.\n");
			TextIndex threadBlockStart = textModel->TotalLength();
			result = Text::StoryRange(threadBlockStart, threadBlockStart);
		}
	} while(false);
	TRACEFLOW("HiddenText", "HidTxtStoryThreadDict::GetThreadBlockTextRange()-->Out start=%d, end=%d\n",
		result.GetStart(),
		result.GetEnd());
	return result;
}

/*
*/
uint32 HidTxtStoryThreadDict::GetFirstKey()
{
	TRACEFLOW("HiddenText", "HidTxtStoryThreadDict::GetFirstKey()-->In/Out\n");
	return kHidTxtStoryThreadDictKey;
}

/*
*/
uint32 HidTxtStoryThreadDict::GetNextKey()
{
	TRACEFLOW("HiddenText", "HidTxtStoryThreadDict::GetNextKey()-->In/Out\n");
   return kHidTxtStoryThreadDictKey;
}

// End, HidTxtStoryThreadDict.cpp

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                


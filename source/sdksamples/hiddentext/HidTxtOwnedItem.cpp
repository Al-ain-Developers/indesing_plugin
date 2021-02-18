//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtOwnedItem.cpp $
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
#include "ICommand.h"
#include "IUIDData.h"
#include "IWaxRun.h"
#include "IGlobalTextAdornment.h"

// General includes:
#include "COwnedItem.h"
#include "CmdUtils.h"
#include "Trace.h"

// Project includes:
#include "HidTxtID.h"

/** Implements the owned item (IOwnedItem) that anchors hidden text 
	(kHidTxtModelBoss) on a TextIndex in a story. Owned items
	are stored by the owned item strand (kOwnedItemStrandBoss) in the
	story's text model (ITextModel).

	The IOwnedItem and ITextModelMemento implementations are the hooks that allow the
	hidden text to be managed when it is affected by text model operations. For example
	they allow the kHidTxtModelBoss object and its associated story thread to be
	deleted when the TextIndex on which the hidden text is anchored gets deleted.

	This implementation also attaches this plug-ins text adornment 
	(kHidTxtAnchorTextAdornmentBoss) to the wax when IOwnedItem::Moved is called.
	
	
	@ingroup hiddentext
 */
class HidTxtOwnedItem : public COwnedItem
{
	public:
		/** Constructor.
			@param boss
		 */
		HidTxtOwnedItem(IPMUnknown* boss);
		
		/** Destructor.
		 */
		virtual ~HidTxtOwnedItem();

	public:
		/** @return interface pointer to a kHidTxtModelDeleteCmdBoss command.
			@see IOwnedItem and COwnedItem
		 */
		virtual ICommand*			QueryRemoveFromDocumentCmd() const;

		/** @return interface pointer to a kHidTxtTextModelMementoBoss object.
			@see IOwnedItem and COwnedItem
		 */
		virtual ITextModelMemento*	QueryMemento() const;

		/** @return 1, this owned item is anchored on a single character.
			@see IOwnedItem and COwnedItem
		 */
		virtual int32				GetNumSpecialAnchorChars() const;

		/** @see IOwnedItem and COwnedItem
		Implementations which don't have any position specific issues should
		override and stub out these methods to improve performance.
		*/
		virtual bool16				Moved(ITextModel* textModel,
												IParcelList* pl,
												const IWaxLine* waxLine,
												TextIndex ownedItemTextIndex,
												TextIndex waxLineTextIndex); // Changed at InDesign CS3

		/** @see IOwnedItem and COwnedItem
		Implementations which don't have any position specific issues should
		override and stub out these methods to improve performance.
		*/
		virtual void				MovedIntoOverset(IParcelList* pl); // Changed at InDesign CS3

		/** @see IOwnedItem and COwnedItem
		Implementations which don't have any position specific issues should
		override and stub out these methods to improve performance.
		*/
		virtual void				Applied(ITextModel* textModel,
												IParcelList* pl,
												const IWaxLine* waxLine,
												TextIndex ownedItemTextIndex,
												TextIndex waxLineTextIndex);

		/** @see IOwnedItem and COwnedItem
		Implementations which don't have any position specific issues should
		override and stub out these methods to improve performance.
		 */
		virtual void				Rebuilt(ITextModel* textModel,
												IParcelList* pl,
												const IWaxLine* waxLine,
												IWaxRun* waxRun,
												TextIndex ownedItemTextIndex,
												TextIndex waxLineTextIndex); // Added at InDesign CS2

		
		/** @see IOwnedItem and COwnedItem
		Implementations which don't have any position specific issues should
		override and stub out these methods to improve performance.
		*/
		virtual void				ParcelMoved();	// Added at InDesign CS3

};

/* Make the implementation avaiable to the application.
*/
CREATE_PERSIST_PMINTERFACE(HidTxtOwnedItem, kHidTxtOwnedItemImpl)

/*
*/
HidTxtOwnedItem::HidTxtOwnedItem(IPMUnknown* boss) : COwnedItem(boss)
{
	TRACEFLOW("HiddenText", "HidTxtOwnedItem::Constructor()-->In/Out\n");
}

/*
*/
HidTxtOwnedItem::~HidTxtOwnedItem()
{
	TRACEFLOW("HiddenText", "HidTxtOwnedItem::Destructor()-->In/Out\n");
}

/*
*/
ICommand* HidTxtOwnedItem::QueryRemoveFromDocumentCmd() const
{
	TRACEFLOW("HiddenText", "HidTxtOwnedItem::QueryRemoveFromDocumentCmd-->In()\n");
	InterfacePtr<ICommand> result;
	do {
		InterfacePtr<ICommand> deleteHidTxtModelCmd(CmdUtils::CreateCommand(kHidTxtModelDeleteCmdBoss));
		ASSERT(deleteHidTxtModelCmd != nil);
		if (deleteHidTxtModelCmd == nil) {
			break;
		}
		deleteHidTxtModelCmd->SetItemList(UIDList(::GetUIDRef(this)));
		result = deleteHidTxtModelCmd;
	} while(false);
	TRACEFLOW("HiddenText", "HidTxtOwnedItem::QueryRemoveFromDocumentCmd-->Out() result=0x%x\n", result.get());
    return result.forget();
}

/*
*/
ITextModelMemento*	HidTxtOwnedItem::QueryMemento() const
{
	TRACEFLOW("HiddenText", "HidTxtOwnedItem::QueryMemento-->In()\n");
	InterfacePtr<ITextModelMemento> memento(::CreateObject2<ITextModelMemento>(kHidTxtTextModelMementoBoss));
	ASSERT(memento != nil);
	if (memento != nil) {
		InterfacePtr<IUIDData> ownedItemUIDData(memento, IID_IHIDTXTOWNEDITEMUIDDATA);
		ASSERT(ownedItemUIDData != nil);
		if (ownedItemUIDData != nil) {
			ownedItemUIDData->Set(::GetUIDRef(this));
		}
	}
	TRACEFLOW("HiddenText", "HidTxtOwnedItem::QueryMemento-->Out() memento=0x%x\n", memento.get());
	return memento.forget();
}

/*
*/
int32 HidTxtOwnedItem::GetNumSpecialAnchorChars() const
{
	// Hidden text is anchored on one character.
	int32 result = 1;
	TRACEFLOW("HiddenText", "HidTxtOwnedItem::GetNumSpecialAnchorChars-->In/Out() result=%d\n", result);
	return result;	
}

/*
*/
bool16 HidTxtOwnedItem::Moved(ITextModel* textModel,
	IParcelList* pl,
	const IWaxLine* waxLine,
	TextIndex ownedItemTextIndex,
	TextIndex waxLineTextIndex)
{
	TRACEFLOW("HiddenText", "HidTxtOwnedItem::Moved-->In/Out()\n");

	return kFalse;
}

/*
*/
void HidTxtOwnedItem::MovedIntoOverset(IParcelList* pl)
{
	TRACEFLOW("HiddenText", "HidTxtOwnedItem::MovedInto-->In/Out()\n");
}

/*
*/
void HidTxtOwnedItem::Applied(ITextModel* textModel,
	IParcelList* pl,
	const IWaxLine* waxLine,
	TextIndex ownedItemTextIndex,
	TextIndex waxLineTextIndex)
{
	TRACEFLOW("HiddenText", "HidTxtOwnedItem::Applied-->In/Out()\n");
}

/*
*/
void HidTxtOwnedItem::Rebuilt(ITextModel* textModel,
	IParcelList* pl,
	const IWaxLine* waxLine,
	IWaxRun* waxRun,
	TextIndex ownedItemTextIndex,
	TextIndex waxLineTextIndex)
{
	TRACEFLOW("HiddenText", "HidTxtOwnedItem::Rebuilt-->In()\n");

	// The adornment decorates all the hidden text anchor characters it finds
	// in the run. So we only need to add it to a wax run if the run does not
	// already have it.
	if (!waxRun->FindAdornment(kHidTxtAnchorTextAdornmentBoss, nil, nil)) {
		waxRun->AddAdornment(kHidTxtAnchorTextAdornmentBoss, kTAPriMissingGlyphs, nil);
	}

	TRACEFLOW("HiddenText", "HidTxtOwnedItem::Rebuilt-->Out()\n");
}

/*
*/
void HidTxtOwnedItem::ParcelMoved()
{
	TRACEFLOW("HiddenText", "HidTxtOwnedItem::ParcelMoved-->In/Out()\n");
}

// End, HidTxtOwnedItem.cpp

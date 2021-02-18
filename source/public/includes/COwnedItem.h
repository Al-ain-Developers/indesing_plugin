//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/COwnedItem.h $
//  
//  Owner: dwaterfa
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

#pragma once
#ifndef __COwnedItem__
#define __COwnedItem__

#include "IOwnedItem.h"
#include "IParcelList.h"
#include "IWaxLine.h"
#include "IWaxRun.h"

#include "HelperInterface.h"

#pragma export on

class PUBLIC_DECL COwnedItem : public IOwnedItem
{
public:
	COwnedItem(IPMUnknown *boss);

	virtual void				SetDiskPage(UID diskPage);

	virtual UID					GetDiskPage() const;

	virtual TextIndex			GetTextIndex() const;

	virtual UID					GetTextModelUID() const;

	virtual ITextModel*			QueryTextModel() const;

	virtual UIDRef				GetFrameRef() const;

	virtual ITextFrameColumn*	QueryFrame() const;

	virtual PMRect 				GetInkBounds(void) const;

	// Must implement QueryRemoveFromDocumentCmd()

	// Must implement QueryMemento()

	// Must implement GetNumSpecialAnchorChars()

	virtual bool16				GetIsParcelPositionDependent() const;

	virtual void				CollectStoryRanges(Text::StoryRangeList* rList,
											TextIndex hIndex,
											Text::HIndexList* hIndexList) const;

	virtual	void				CollectChildren(VisitorHelperList* rList,
												const PMRect* pHitRect,
												const bool16 useParcelInkBounds) const;

	virtual	void				CollectChildren(VisitorHelperList* rList) const;

	virtual bool16				Moved(ITextModel* textModel,
										IParcelList* pl,
										const IWaxLine* waxLine,
										TextIndex ownedItemTextIndex,
										TextIndex waxLineTextIndex);

	virtual void				MovedIntoOverset(IParcelList* pl);

	virtual void				Applied(ITextModel* textModel,
										IParcelList* pl,
										const IWaxLine* waxLine,
										TextIndex ownedItemTextIndex,
										TextIndex waxLineTextIndex);

	virtual void				StoryThreadChanged(UID newDictUID, uint32 newDictKey);
	
	virtual void				StoryDirectionChanged();

	virtual IParagraphComposer*	QueryComposer() const;

	virtual void				StoryAccessChanged(TextStory_StoryAccess);

	virtual bool16				GetAreAnchorCharsFindable() const;

	virtual bool16				GetHasStandOff() const;

	virtual void				Rebuilt(ITextModel* textModel,
										IParcelList* pl,
										const IWaxLine* waxLine,
										IWaxRun* waxRun,
										TextIndex ownedItemTextIndex,
										TextIndex waxLineTextIndex);

	virtual void				Rebuilt(ITextModel* textModel,
										IParcelList* pl,
										const IWaxLine* waxLine,
										IWaxRun* waxRun,
										TextIndex ownedItemTextIndex,
										TextIndex waxLineTextIndex,
										bool16* damagedBack);

	virtual void				LayerChanged(const IDocumentLayer* newDocLayer);

	virtual void				VisibilityChanged();

	virtual void				ZOrderChanged();

	virtual bool16				GetContainsOversetContent() const;

	virtual void				ParcelMoved();

	virtual void				ParcelResized();

	virtual ITextStoryThread*	QueryStoryThread() const;

	virtual IParcelList*		QueryParcelList() const;

	virtual ITextParcelList*	QueryTextParcelList() const;

	/**
	In general, no, the exception being if the OwnedItem boss has an IScript.
	*/
	bool16						GetCanReturnIScript() const;

	IScript*					QueryIScript(const ScriptInfo::RequestContext& context) const;

	void						ReadWrite(IPMStream *s, ImplementationID i);

protected:
	UID		fDiskPage;

	DECLARE_HELPER_METHODS()
};

#pragma export off

#endif

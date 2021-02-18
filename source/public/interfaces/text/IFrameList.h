//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFrameList.h $
//  
//  Owner: Zak_Williamson
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
#ifndef __IFrameList__
#define __IFrameList__

#include "IPMUnknown.h"
#include "TextID.h"
#include "K2Vector.h"

class ITextFrameColumn;
class ITextModel;
class RangeData;

/**
	The IFrameList contains a list of the frames of a ITextModel, it maintains information about 
	what text index ranges are contained in what frames, and it maintains information about which 
	frames are, and are not, fully composed. The order of the frames in the IFrameList is the 
	order in which text flows through the frames. IFrameList interface is aggregated on the Frame List boss.

	@ingroup text_layout
*/
class IFrameList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFRAMELIST };

	enum { kAtTheEnd = -1 };

	/**
	This method is used to associate a IFrameList with a specific ITextModel. Generally, this is only 
	called when creating a new ITextModel and IFrameList. The CreateMultiColumnItemCmd handles all 
	the nuiances of creating a new frame (and optionally a new IFrameList and/or new ITextModel).
	@param modelUID UID of ITextModel.
	*/
	virtual void SetTextModelUID(UID modelUID) = 0;

	/**
	Gets the UID of the ITextModel that we are associated with.
	@return UID of ITextModel.
	*/
	virtual UID GetTextModelUID() const = 0;

	/**
	Get the ITextModel that we are associated with.
	@return A pointer to a ITextModel.
	*/
	virtual ITextModel * QueryTextModel() const = 0;

	/**
	Gets the index within the known set of ITextFrames known to the IFrameList of a ITextFrameColumn specified by its UID.
	@param frameUID UID of ITextFrameColumn within the IFrameList.
	@return index of ITextFrameColumn within the IFrameList, -1 if not found.
	*/
	virtual int32 GetFrameIndex(UID frameUID) const = 0;

	/**
	Gets the index within the known set of ITextFrames known to the IFrameList of a specific ITextFrameColumn.
	@param frame Pointer to ITextFrameColumn within the IFrameList.
	@return index of ITextFrameColumn within the IFrameList, -1 if not found.
	*/
	virtual int32 GetFrameIndex(const ITextFrameColumn* frame) const = 0;

	/**
	Returns the count of ITextFrames known to the IFrameList.
	@return Count of ITextFrames know to the IFrameList.
	*/
	virtual int32 GetFrameCount() const = 0;

	/**
	Accesses a specific ITextFrameColumn within the list held by the IFrameList.
	@param n Index within the IFrameList of the ITextFrameColumn to be returned.
	@return UID of the desired ITextFrameColumn.
	*/
	virtual UID GetNthFrameUID(int32 n) const = 0;

	/**
	Accesses a specific ITextFrameColumn within the list held by the IFrameList.
	@param n Index within the IFrameList of the ITextFrameColumn to be returned.
	@return A pointer to the desired ITextFrameColumn.
	*/
	virtual ITextFrameColumn * QueryNthFrame(int32 n) const = 0;

	/**
	Provides information about what ranges of text are held in what ITextFrames.
	@param frameUID UID of the ITextFrameColumn within the IFrameList.
	@return TextIndex within the primary story thread of the first character composed into the specified ITextFrameColumn.
	*/
	virtual TextIndex GetFrameStart(UID frameUID) const = 0;

	/**
	Provides information about what ranges of text are held in what ITextFrames.
	@param frameUID UID of the ITextFrameColumn within the IFrameList.
	@return Number of characters within the primary story thread composed into the specified ITextFrameColumn.
	*/
	virtual int32 GetFrameSpan(UID frameUID) const = 0;

	/**
	Accesses an ITextFrameColumn specified by the TextIndex of a character composed in it.
	NOTE: This call will cause the text to compose up to at least the specified TextIndex, if it wasn't already composed.
	@param textIndex TextIndex within any ITextStoryThread, not just the primary story thread, in the ITextModel.
	@param frameIndex If non-nil, set to the index of the retunred ITextFrameColumn, or -1 if nil is returned.
	@return The ITextFrameColumn within the IFrameList containing the specified TextIndex.
	*/
	virtual ITextFrameColumn * QueryFrameContaining(TextIndex textIndex, int32 * frameIndex /* = nil*/) const = 0;

	/**
	Accesses the index of the ITextFrameColumn specified by the TextIndex of a character composed in it.
	NOTE: This call will NOT cause the text to compose.
	@param at TextIndex within any ITextStoryThread, not just the primary story thread, in the ITextModel.
	@return The index of the ITextFrameColumn within the IFrameList containing the specified TextIndex.
	*/
	virtual int32 GetFrameIndexContaining(TextIndex at) const = 0;

	/**
	Accesses the indexes of the ITextFrames specified by a text range of characters that are composed in them.
	NOTE: This call will NOT cause the text to compose.
	@param range RangeData within any single ITextStoryThread, not just the primary story thread, in the ITextModel. Lean is ignored.
	@param firstIndex Set to the index of the ITextFrameColumn containing the first character of the specified range, or -1 if the text specified is not in any ITextFrameColumn.
	@param lastIndex Set to the index of the ITextFrameColumn containing the last character (or the last composed character) of the specified range, or -1 if the text specified is not in any ITextFrameColumn.
	*/
	virtual void GetFramesContaining(const RangeData& range, int32* firstIndex, int32* lastIndex) const = 0;

	/**
	The IFrameList is considered overset when, the last time it was composed, some of the composable 
	content did not fit in any of the ITextFrames. This state is persisted by the IFrameList 
	and is updated every time it is recomposed.
	@return kTrue if the persisted overset state is valid.
	*/
	virtual bool16		GetWasOversetValid() const = 0;

	/**
	Returns the last overset state set by the last composition.
	@return The last overset state.
	*/
	virtual bool16		GetWasOverset() const = 0;

	/**
	Sets the new overset state and marks it valid.
	@param ov The new overset state.
	*/
	virtual void		SetWasOverset(bool16 ov) = 0;

	/**
	Adds an ITextFrameColumn to the IFrameList at the end.
	@param frameUID UID of new ITextFrameColumn to add to the IFrameList.
	*/
	virtual void AddFrame(UID frameUID) = 0;

	/**
	Adds an ITextFrameColumn to the IFrameList at a specified index.
	@param frameUID UID of new ITextFrameColumn to add to the IFrameList.
	@param at index within the IFrameList to add the new ITextFrameColumn
	*/
	virtual void AddFrameAt(UID frameUID, int32 at) = 0;

	/**
	AddFrameAt using ProcessCommand.
	@param frameUID UID of new ITextFrameColumn to add to the IFrameList.
	@param at index within the IFrameList to add the new ITextFrameColumn
	*/
	virtual void ProcessAddFrameAt(UID frameUID, int32 at) = 0;

	/**
	Removes an ITextFrameColumn from the IFrameList.
	@param frameUID UID of the ITextFrameColumn to remove from the IFrameList.
	*/
	virtual void RemoveFrame(UID frameUID) = 0;

	/**
	Clears all ITextFrames from the IFrameList.
	*/
	virtual void ClearFrameList() = 0;

	/**
	This method is used by the composition engine to determine
	where to start composing from.  This method can also be
	used to determine whether the entire IFrameList is fully composed.
	@return -1 if the entire IFrameList is undamaged.
	*/
	virtual int32 GetFirstDamagedFrameIndex() const = 0;

	/**
	The "In View" cache is used to eliminate unnecessary recording
	of pending invals during damage recording and recomposition.
	(If a ITextFrameColumn is not in any view, pending invals are unnecessary.)
	These calls are designed for use only during damage recording
	and recomposition. If you need to determine if an ITextFrameColumn is in
	view, you can call ClearInViewCache() followed by IsInView().
	*/
	virtual void ClearInViewCache() = 0;

	/**
	Determines if an ITextFrameColumn within the IFrameList is in view.
	@param frameUID UID of ITextFrameColumn within the IFrameList
	@return kTrue if the specied ITextFrameColumn is in view.
	*/
	virtual bool16 IsInView(UID frameUID) const = 0;

	/**
	Internal Use Only, do not use. Adds an ITextFrameColumn to the in view cache.
	@param frameUID UID of ITextFrameColumn that is to be added to the cache.
	*/
	virtual void AddToInViewCache(UID frameUID) = 0;

	/*
	Normally recomposition and damage recording clear the "in view"
	cache every time they are called, since they have no way of
	knowing if what is in view has changed.  However, recalculating
	the cache is not free and some operations like Change All
	make a lot of separate calls to mark damage (which calls IsInView)
	without the possibility of what is in view changing.  For these cases
	you can (carefully) "freeze" and "unfreeze" the in view cache.
	Freezing the cache clears it and prevents subsequent calls to
	ClearInViewCache from having any effect.  IsInView will populate
	the cache as usual.
	Note: The "frozen" flag is not persistent, so you must maintain
	a reference on the IFrameList for the entire time the cache is frozen.
	@param freezeIt If set to kTrue, the cache is frozen.
	*/
	virtual void FreezeInViewCache(bool16 freezeIt) = 0;

	/**
	The InViewCacheFreezer is just a simple stack-based object to
	help anyone who uses the "cache freezing" feature to remember
	to "thaw the cache."
	*/
	class InViewCacheFreezer
	{
	public:
		InViewCacheFreezer(IFrameList * frameList)
			: fFrameList(frameList)
		{
			if (frameList != nil)
			{
				fFrameList->AddRef();
				fFrameList->FreezeInViewCache(kTrue);
			}
		}

		~InViewCacheFreezer()
		{
			if (fFrameList != nil)
				fFrameList->FreezeInViewCache(kFalse);
		}

	private:
		InterfacePtr<IFrameList> fFrameList;
	};

	/**
	The change counter is persisted value which is incremented (and eventually
	rollover) each time any ITextFrameColumn in the IFrameList goes from undamaged to
	damaged. It is thus a useful indication of when some Text in the IFrameList
	has been damaged and will be re-composed.
	@return The current value of the change counter.
	*/
	virtual uint32 GetChangeCounter() const = 0;

#ifdef DEBUG
	/**
	Internal Use Only, do not use.
	*/
	virtual	void	LockDamaging( bool16 bLock ) = 0;

	/**
	Internal Use Only, do not use.
	*/
	virtual	bool16	IsDamagingLocked() const = 0;
#endif

	/**
	Internal Use Only, do not use. Adds the specified list of ITextFrames to the in view list as not in view.
	@param frameList UIDList of ITextFrames within the IFrameList that should be marked as no in view.
	*/
	virtual void SetNotInViewList(const UIDList& frameList) = 0;

	/**
	Internal Use Only, do not use. Removes the specified list of ITextFrames from the in view list.
	@param frameList UIDList of ITextFrames within the IFrameList that should be removed.
	*/
	virtual void RemoveNotInViewList(const UIDList& frameList) = 0;

};

#endif

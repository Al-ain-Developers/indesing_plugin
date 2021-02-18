//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextParcelListData.h $
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
#ifndef __ITextParcelListData__
#define __ITextParcelListData__

#include "IPMUnknown.h"
#include "ICompositionStyle.h"

#include "PMRect.h"
#include "PMMatrix.h"
#include "TextID.h"
#include "UIDList.h"
#include "CTextEnum.h"
#include "ParcelKey.h"
#include "TextWrapRef.h"

class ITextStoryThread;
class ISpread;


/**
	@ingroup text_layout
*/
class ITextParcelListData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTPARCELLISTDATA };

		//
		// Composed state of the Text Parcel List
		//
		virtual IDataBase *	GetDataBase() const = 0;
		virtual UID			GetTextModelUID() const = 0;
		virtual UID			GetFrameListUID() const = 0;

		virtual ITextStoryThread *	QueryStoryThread() const = 0;

		/**
		A Parcel with TextDamage needs recomposition.
		*/
		virtual bool16		GetParcelIsDamaged(ParcelKey key) const = 0;
		virtual void		SetParcelDamaged(ParcelKey key) = 0;
		virtual void		ClearParcelDamage(ParcelKey key) = 0;

		/**
		Parcels which are marked as needing Wrap check are suspected of having
		new intersecting Wraps available through GetNonInlineWrapsForParcel().
		@param key Parcel to search in.
		@return kTrue if the Parcel needs to check wrap
		*/
		virtual bool16		GetParcelNeedsWrapCheck(ParcelKey key) const = 0;

		/**
		It is the responsibility of the container implementation to mark Parcels
		as needing Wrap check through this method when it knowns that Wraps
		which are not Inline to the Parcel might affect it.

		Typically this means that the implementation has to wait until the
		Parcel has finished its movement to determine the effect - it is not
		necessarily correct to simply mark all moving or resizing Parcels as
		needing Wrap check.

		Furthermore, the implementation is also responsible for determing what
		appropriate "damage" is required in order to trigger evaluation of the
		Wrap. Parcels which are beyond the end of the composed Thread do not
		necessarily have to be composed

		The TextParcelList ONLY calls this method when processing Wraps from
		Inlines via AddParcelInlineWraps().
		@param key Parcel to search in.
		*/
		virtual void		SetParcelNeedsWrapCheck(ParcelKey key) = 0;

		/**
		Clears the wrap check from the specified Parcel. During composition
		the TextParcelList will cause this to be cleared when it processes a
		Parcel following the one currently being composed. It is the
		responsiblity of the implementation to process the Parcel in which
		composition begins.
		@param key Parcel to search in.
		*/
		virtual void		ClearParcelNeedsWrapCheck(ParcelKey key) = 0;

		virtual TextIndex	GetParcelTextStart(ParcelKey key) const = 0;
		virtual int32		GetParcelTextSpan(ParcelKey key) const = 0;
		virtual void		SetParcelTextSpan(ParcelKey key, TextIndex span) = 0;
							// NOT lean left, we want where it really is
		virtual ParcelKey	GetParcelContaining(TextIndex at) const = 0;

		//
		// The Content bounds of the Parcel is measured from the top of the
		// TOFLineHeight() of the first WaxLine to the GetContentBottom() of
		// the last WaxLine in the Content coordinates.
		//
		// Clients which do not cache this information may return a height of
		// 0.0 and TextParcelList::GetContentBounds() will compute it.
		//
		virtual void		GetParcelVContentBounds(ParcelKey key, PMReal* pTop,
												PMReal* pBottom) const = 0;
		virtual void		SetParcelVContentBounds(ParcelKey key, PMReal top,
												PMReal bottom) = 0;

		/**
		The TextParcelList will set this value if the contents of the Parcel,
		including Wax, OwnedItems, WaxAnchoredElements and even Wraps require
		it.
		*/
		virtual bool16		GetParcelHasPositionDependentContent(ParcelKey key) const = 0;
		virtual void		SetParcelHasPositionDependentContent(ParcelKey key, bool16 v) = 0;

		/**
		The TextParcelList will set this value if the contents of the Parcel has any keeps on
		*/
		virtual bool16		GetParcelHasKeepsOn(ParcelKey key) const = 0;
		virtual void		SetParcelHasKeepsOn(ParcelKey key, bool16 v) = 0;

		//
		// Indicates if the Parcel has valid post-processing of VJ using the
		// pre-4.0 style of VJ which did not have a separate Composition
		// YPosition. This will be cleared by the TextParcelList::Recompose()
		// when composition in the Parcel begins.
		//
		virtual bool16		GetParcelHasBeenVJed(ParcelKey key) const = 0;
		virtual void		SetParcelHasBeenVJed(ParcelKey key, bool16 vj) = 0;

		//
		// Indicates if any WaxLines have GridAlignmentMetric other
		// than kGANone.
		//
		virtual bool16		GetParcelHasGridAlignedWax(ParcelKey key) const = 0;
		virtual void		SetParcelHasGridAlignedWax(ParcelKey key, bool16 v) = 0;

		//
		// Indicates if any WaxLines have NeedsYPosPostProcessing() set
		// to kTrue.
		//
		virtual bool16		GetParcelHasNeedsPostProcessWax(ParcelKey key) const = 0;
		virtual void		SetParcelHasNeedsPostProcessWax(ParcelKey key, bool16 v) = 0;

		/**
		Returns the ParcelKey of the Parcel logicaly first. In terms of this
		API, a logical Parcel is one that text can be composed in. Typical
		implementations have these as one-to-one with all the Parcels in the
		IParcelList but implementations such as Table Header and Footer cells
		have only the first Parcel as logically composable and the rest have
		no Text content at all.
		@param pIndex Optional pointer which will be filled in with the index of the returned ParcelKey. If the returned Parcel is invalid then pIndex will be set to -1.
		@return ParcelKey of the first logical Parcel.
		*/
		virtual ParcelKey	GetFirstLogicalParcelKey(int32* pIndex = nil) const = 0;

		/**
		Returns the ParcelKey of the Parcel logically after the specified key.
		If the key is invalid, an invalid key will be returned.
		@param key
		@param pIndex Optional pointer which will be filled in with the index of the returned ParcelKey. If the returned Parcel is invalid then pIndex will be filled in with the count of Parcels in the IParcelList.
		@return ParcelKey of the next logical Parcel.
		*/
		virtual ParcelKey	GetNextLogicalParcelKey(ParcelKey key,
												int32* pIndex = nil) const = 0;

		enum nextParcelType
		{
			npt_box,
			npt_anypage,
			npt_oddpage,
			npt_evenpage
		};

		/**
		Returns the ParcelKey of the specified Parcel Type logically after the
		specified key. If the specified Key is already the type of Parcel
		desired then the key returned will be unchanged. If the key is invalid,
		an invalid key will be returned.
		@param key
		@param pType Type of Parcel the caller wishes to move to. If the
		@param pIndex Optional pointer which will be filled in with the index of the returned ParcelKey. If the returned Parcel is invalid then pIndex will be filled in with the count of Parcels in the IParcelList.
		@return ParcelKey of the next logical Parcel.
		*/
		virtual ParcelKey	GetNextLogicalParcelKeyByType(ParcelKey key,
												nextParcelType pType,
												int32* pIndex = nil) const = 0;

		/**
		Returns the ParcelKey of the Parcel logically previous to the specified
		key. If the key is invalid, an invalid key will be returned.
		@param key
		@param pIndex Optional pointer which will be filled in with the index of the returned ParcelKey. If the returned Parcel is invalid then pIndex will be set to -1.
		@return ParcelKey of the next logical Parcel.
		*/
		virtual ParcelKey	GetPreviousLogicalParcelKey(ParcelKey key,
												int32* pIndex = nil) const = 0;

		/**
		Returns the ParcelKey of the Parcel logicaly last.
		@param pIndex Optional pointer which will be filled in with the index of the returned ParcelKey. If the returned Parcel is invalid then pIndex will be set to the count of Parcels in the IParcelList.
		@return ParcelKey of the last logical Parcel.
		*/
		virtual ParcelKey	GetLastLogicalParcelKey(int32* pIndex = nil) const = 0;

		/**
		This method allows the implementation to control the meaning of overset.
		Implementations which do not support overmatter Parcels will return the
		same value for this method as GetLastLogicalParcelKey(). Those that do
		support overmatter Parcel should return the ParcelKey of the last Parcel
		before the first overmatter Parcel. ITextParcelList::GetIsOverset() will
		use the returned ParcelKey as the measure of overset content.
		@param pIndex Optional pointer which will be filled in with the index of the returned ParcelKey. If the returned Parcel is invalid then pIndex will be filled in with the count of Parcels in the IParcelList.
		@return ParcelKey of last logical non-overset Parcel
		*/
		virtual ParcelKey	GetLastLogicalNonOversetParcelKey(int32* pIndex = nil) const = 0;

		//
		// Text Parcel List Options
		//
		virtual Text::FirstLineOffsetMetric
							GetParcelFirstLineOffsetMetric(ParcelKey key) const = 0;
		virtual PMReal		GetParcelMinFirstLineOffset(ParcelKey key) const = 0;
		virtual bool16		GetIsVertical() const = 0;
		virtual bool16		GetIsRightToLeft() const = 0;

		//
		// To disable Soft Bottom behavior simply return a value smaller or
		// equal to the Parcel height, such as 0.0.
		//
		virtual PMReal		GetParcelMaxSoftBottomHeight(ParcelKey key) const = 0;
		virtual void		SetParcelMaxSoftBottomHeight(ParcelKey key, PMReal maxHeight) = 0;

		virtual bool16		GetParcelIsValidStartBreakLocation(ParcelKey key,
									Text::StartBreakLocation mode) const = 0;
		virtual bool16		GetHasAnyValidStartBreakLocation() const = 0;

		/**
		Returns kFalse if the Parcel does not support Wraps. This is different
		from ignoring in that one can stop ignoring sometime in the future
		whereas one will not suddenly support Wraps. Examples of implementations
		which do not support Wraps are TextOnPath.
		@param key Parcel to search in.
		@return kTrue if the Parcel supports Wraps.
		*/
		virtual bool16		GetParcelSupportsWrap(ParcelKey key) const = 0;

		/**
		Returns kTrue if the Parcel is ignoring the effect of all Wraps. Note
		that the Wraps will still be added to the Parcel, but they will be
		handled as invalid due to ZOrder.
		@param key Parcel to search in.
		@return kTrue if the Parcel is ignoring the effect of all Wraps.
		*/
		virtual bool16		GetParcelIgnoringWrap(ParcelKey key) const = 0;

		/**
		@returns The number of WaxAnchoredElement known to the implementation.
		*/
		virtual int32		GetWaxAnchoredElementCount() const = 0;

		/**
		Returns the index of the specified WaxAnchoredElement.
		@param uid The UID of the desired WaxAnchoredElement boss.
		@returns The index of the specified WaxAnchoredElement or -1 if it is not known to the implementation.
		*/
		virtual int32		GetWaxAnchoredElementIndex(UID uid) const = 0;

		/**
		A new WaxAnchoredElement is inserted into the list.
		@param n An index into the internal list. Must be greater than or equal to zero and less than OR equal to the value returned by GetWaxAnchoredElementCount().
		@param uid The UID of the WaxAnchoredElement. Must not already be known to the implementation.
		*/
		virtual void		InsertNthWaxAnchoredElement(int32 n, UID uid) = 0;

		/**
		The specified WaxAnchoredElement is removed from the list.
		@param n An index into the internal list. Must be greater than or equal to zero and less then the value returned by GetWaxAnchoredElementCount().
		*/
		virtual void		RemoveNthWaxAnchoredElement(int32 n) = 0;

		/**
		Returns the UID of the Nth element.
		@param n An index into the internal list. Must be greater than or equal to zero and less then the value returned by GetWaxAnchoredElementCount().
		@returns The UID
		*/
		virtual UID			GetNthWaxAnchoredElementUID(int32 n) const = 0;

		/**
		Returns the ParcelKey of the Nth element.
		@param n An index into the internal list. Must be greater than or equal to zero and less then the value returned by GetWaxAnchoredElementCount().
		@returns ParcelKey
		*/
		virtual ParcelKey	GetNthWaxAnchoredElementParcelKey(int32 n) const = 0;

		/**
		Sets the ParcelKey of the Nth element.
		@param key ParcelKey.
		*/
		virtual void		SetNthWaxAnchoredElementParcelKey(int32 n,
															ParcelKey Key) = 0;

		/**
		Fills in the specified UIDList with UIDs of the WaxAnchoredElements in
		the specified Parcel.
		@param key Parcel to search in.
		@param list Optional UIDList to append to.
		@returns count of WaxAnchoredElements returned.
		*/
		virtual int32		GetWaxAnchoredElementsIn(ParcelKey key,
												UIDList* list = nil) const = 0;

		/**
		Returns the ParcelKey of the first Parcel in the ParcelList which is
		is damaged. If no Parcel is damaged then an invalid ParcelKey returned.
		Note that this only refers to Parcels which are damaged, NOT those that
		need wrap check.
		@return ParcelKey
		*/
		virtual ParcelKey	GetFirstDamagedParcel() const = 0;

		/**
		This method returns information about the first Parcel which is damaged
		and the first Parcel which needs wrap check.
		@param damagedKeyIndex Reference to int32 which will be filled in with the index of the first Parcel which is damaged, or -1 if none
		@param needWrapCheckKeyIndex Reference to int32 which will be filled in with the index of the first Parcel which needs wrap check, or -1 if none
		*/
		virtual void		GetFirstKeyIndexes(int32& damagedKeyIndex,
										int32& needWrapCheckKeyIndex) const = 0;

		//
		// See ITextParcelList::ShouldFakeTabAlignToChar for more info.
		//
		virtual bool16		ShouldFakeTabAlignToChar() const = 0;

		//
		// Invalidate composed cached state for the Parcel including the ink
		// bounds and pass info. This method will be called whenever the Parcel
		// goes from the damaged state to the undamaged state.
		//
		virtual void		InvalidateParcelComposedState(ParcelKey key) = 0;

		//
		// This method will be called when the TextParcelList is notified that
		// the inkBounds within the specified Parcel have changed outside of
		// composition. The callee should notify the Parent containing Parcel,
		// if any, by calling ITextParcelList::NotifyInkBoundsChanged().
		//
		virtual void		NotifyParcelParentInkBoundsChanged(ParcelKey key) = 0;

		/**
		Returns the list of Parcels that are on the specified ISpread.
		@param spread Pointer to ISpread interface
		@param keyList K2Vector of ParcelKeys to be filled in
		@return count of ParcelKeys added to keyList
		*/
		virtual int32		GetParcelsOnSpread(const ISpread* spread,
									K2Vector<ParcelKey>& keyList) const = 0;

		/**
		Fills in the specfied list with all the non-Inline Wraps which the
		implementation determines are possible overlaps for the specified
		Parcel. Note that this is expected to be the same as or superset of
		the Wraps currently known to the Parcel as returned by GetParcelWraps().
		The TextParcelList will be responsible for adding these Wraps to the
		Parcel in a separate step.
		@param key Parcel to search in.
		@param sodList Reference to TextWrapRefList to be filled in
		@return count of Wraps added to the list
		*/
		virtual int32		GetNonInlineWrapsForParcel(ParcelKey key,
											TextWrapRefList& sodList) const = 0;

		/**
		@param ParcelKey
		@param sodRef TextWrapRef to wrap boss with active IStandOff
		@param isActive kTrue if the Wrap can be tiled against
		@param isNonInline kTrue if the Wrap is not the child of an Inline
		@param isInlineToParcel kTrue if the Wrap is the child of an Inline that is anchored in the Parcel. If kTrue, then sodRef.fX/YOffset are expected to be zero.
		*/
		virtual void		AddParcelWrap(ParcelKey key,
											const TextWrapRef& sodRef,
											bool16 isActive,
											bool16 isNonInline,
											bool16 isInlineToParcel) = 0;

		/**
		Returns the active state of the StandOff relative to the Parcel.
		@param key Parcel to search in.
		@param sodRef TextWrapRef to wrap boss
		*/
		virtual bool16		GetParcelWrapActive(ParcelKey key,
											const TextWrapRef& sodRef) const = 0;

		/**
		@param key Parcel to search in.
		@param sodRef TextWrapRef to wrap boss
		*/
		virtual void		SetParcelWrapActive(ParcelKey,
											const TextWrapRef& sodRef) = 0;

		/**
		@param key Parcel to search in.
		@param sodUID UID of wrap boss with active IStandOffData interface
		*/
		virtual void		ClearParcelWrapActive(ParcelKey key,
											const TextWrapRef& sodRef) = 0;

		/**
		Returns the non-inline state of the StandOff. Wraps which are non-inline
		are NOT children of an Inline - typically they are children of the
		Spread. This state is set when the Wrap is added to the Parcel.
		@param key Parcel to search in.
		@param sodRef TextWrapRef to wrap boss
		*/
		virtual bool16		GetParcelWrapIsNonInline(ParcelKey key,
											const TextWrapRef& sodRef) const = 0;

		/**
		Wraps which are Inline to the Parcel are those that are anchored in
		the Parcel. Wraps that are children of Inlines that are NOt inline to
		the Parcel are anchored at a TextIndex previous to the start of the
		Parcel. This state is set when the Wrap is added to the Parcel.
		@param key Parcel to search in.
		@param sodRef TextWrapRef to wrap boss
		*/
		virtual bool16		GetParcelWrapIsInlineToParcel(ParcelKey key,
											const TextWrapRef& sodRef) const = 0;

		/**
		@param key Parcel to search in.
		@param sodRef TextWrapRef to wrap boss
		*/
		virtual bool16		GetParcelWrapHasOverlappedRange(ParcelKey key,
											const TextWrapRef& sodRef) const = 0;

		/**
		@param key Parcel to search in.
		@param sodRef TextWrapRef to wrap boss
		*/
		virtual void		GetParcelWrapOverlappedRange(ParcelKey key,
												const TextWrapRef& sodRef,
												PMReal& waxYTop,
												PMReal& waxYBottom) const = 0;

		/**
		@param key Parcel to search in.
		@param sodRef TextWrapRef to wrap boss
		*/
		virtual void		SetParcelWrapOverlappedRange(ParcelKey key,
												const TextWrapRef& sodRef,
												const PMReal& waxYTop,
												const PMReal& waxYBottom) = 0;

		/**
		Returns kTrue if the specified Parcel has any Wraps added to it.
		@param key Parcel to search in.
		@return kTrue if the Parcel has any Wraps added to it.
		*/
		virtual bool16		GetParcelHasWraps(ParcelKey key) const = 0;

		/**
		Fills in the specfied list with all the Wraps currently added to
		the Parcel.
		@param key Parcel to search in.
		@param sodList Reference to TextWrapRefList to be filled in
		@return count of Wraps added to the list
		*/
		virtual int32		GetParcelWraps(ParcelKey key,
											TextWrapRefList& sodList) const = 0;

		/**
		Returns kTrue if the specified Parcel has any active Wraps which are
		not a child of an Inline.
		added to it.
		@param key Parcel to search in.
		@return kTrue if the Parcel has any Wraps added to it.
		*/
		virtual bool16		GetParcelHasActiveNonInlineWraps(ParcelKey key) const = 0;

		/**
		Fills in the specfied list with all the Wraps currently added to
		the Parcel which report being active and are not the child of an Inline.
		@param key Parcel to search in.
		@param sodList Reference to TextWrapRefList to be filled in
		@return count of Wraps added to the list
		*/
		virtual int32		GetParcelActiveNonInlineWraps(ParcelKey key,
											TextWrapRefList& sodList) const = 0;

		/**
		Returns kTrue if the specified Parcel has any active Wraps which are a
		child of an Inline.
		@param key Parcel to search in.
		@return kTrue if the Parcel has any Wraps added to it.
		*/
		virtual bool16		GetParcelHasActiveInlineWraps(ParcelKey key) const = 0;

		/**
		Fills in the specfied list with all the Wraps currently added to
		the Parcel which report being active and are a child of an Inline.
		@param key Parcel to search in.
		@param sodList Reference to TextWrapRefList to be filled in
		@return count of Wraps added to the list
		*/
		virtual int32		GetParcelActiveInlineWraps(ParcelKey key,
											TextWrapRefList& sodList) const = 0;

		/**
		@param key Parcel to search in.
		@param sodRef TextWrapRef to wrap boss
		*/
		virtual void		RemoveParcelWrap(ParcelKey key,
											const TextWrapRef& sodRef) = 0;

		/**
		All implementations must support ICompositionStyle::kSingleColumn.
		@param spanType Span type to check
		@return kTrue if the implementation supports the specified span type.
		*/
		virtual bool16		GetSupportsColumnSpanType(ICompositionStyle::SpanColumnsTypeOptions spanType) const = 0;

};

#endif	// __ITextParcelListData__

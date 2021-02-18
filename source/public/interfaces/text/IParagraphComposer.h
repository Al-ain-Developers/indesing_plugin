//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IParagraphComposer.h $
//  
//  Owner: ?
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
#ifndef __IParagraphComposer__
#define __IParagraphComposer__

#include "IPMUnknown.h"
#include "ParcelKey.h"
#include "OwnedItemDataList.h"
#include "CTextEnum.h"
#include "PMRect.h"		// for PMRectCollection
#include "PMMatrix.h"
#include "TextID.h"
#include "AttributeBossList.h"

class IDataBase;
class IParcelList;
class ITextParcelList;
class ITextModel;
class IParcel;
class IComposeScanner;
class IWaxLine;
class IWaxIterator;
class IdleTimer;
class ITextOptions;
class IStoryOptions;
class IPairKernDict;
class IEdgeAlignDict;
class IHyphenationExceptions;
class IHyphenationService;
class ILanguage;

/**
	@ingroup text_comp
*/
class PUBLIC_DECL IParagraphComposer : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPARAGRAPHCOMPOSER };
	enum { kDefaultServiceID = kTextEngineService };

	/**
	*/
	class Tiler
	{
	protected:
		///
		PUBLIC_DECL				Tiler();

	private:
		///
		PUBLIC_DECL				Tiler(const Tiler& copy);
		///
		PUBLIC_DECL Tiler& operator=(const Tiler& copy);

	public:
		///
		virtual					~Tiler() { }

		///
		virtual IParcelList*	GetParcelList() const = 0;

		/**
		In the context of the composing paragraph, returns the ParcelKey of the
		first *logical* parcel.
		Note that the returned value may differ from what the IParcelList would
		have returned.
		*/
		virtual ParcelKey		GetFirstParcelKey() const = 0;

		/**
		In the context of the composing paragraph, returns the ParcelKey of the
		*logical* parcel after the specified Parcel.
		Note that the returned value may differ from what the IParcelList would
		have returned.
		*/
		virtual ParcelKey		GetNextParcelKey(ParcelKey key) const = 0;

		///
		virtual bool16			GetHasAnyValidStartBreakLocation() const = 0;

		///
		virtual bool16			GetParcelIsValidStartBreakLocation(ParcelKey key,
                							Text::StartBreakLocation mode) const = 0;

		/**
		In the context of the composing paragraph, returns the ParcelKey of the
		first *logical* parcel with the specified break attribute with the
		search starting at the specified parcel. If the specified parcel matches
		the specified break location it will be returned. If no parcel can be
		found searching forward which matches the specified break location an
		invalid ParcelKey will be returned.
		Note that the returned value may differ from what the IParcelList would
		have returned.
		*/
		virtual ParcelKey		GetNextParcelKeyByBreak(ParcelKey key,
											Text::StartBreakLocation mode) const = 0;

		/**
		In the context of the composing paragraph, returns the ParcelKey of the
		*logical* parcel before the specified Parcel.
		Note that the returned value may differ from what the IParcelList would
		have returned.
		*/
		virtual ParcelKey		GetPreviousParcelKey(ParcelKey key) const = 0;

		//
		// This method will adjust the specified ParcelKeys and YPosition to
		// the top of the desired break location. If the specified key and
		// position is already at the top of the desired break location then
		// they are unchanged. Returns kTrue if the position changed.
		//
		virtual bool16			MoveToTopNextParcelByBreak(Text::StartBreakLocation mode,
												ParcelKey* pKey,
												PMReal* pYPosition) const = 0;

		///
		virtual PMRect			GetParcelContentBounds(ParcelKey key) const = 0;

		///
		virtual bool16			GetParcelContentIsAnArea(ParcelKey key) const = 0;

		/**
		In the context of the composing paragraph, returns kTrue if the
		specified Parcel has any active TextWraps.
		*/
		virtual bool16			GetHasAnyIntrusionsAt(ParcelKey key) const = 0;

		//
		// The Parcel itself can have a grid or the grid can bleed through
		// from the PageGrid. Either way we return the effective vertical
		// spacing of 0.0 if no grid is active.
		//
		virtual PMReal			GetParcelEffectiveVerticalSpacing(ParcelKey key) const = 0;

		///
		virtual UID				GetParcelFrameUID(ParcelKey key) const = 0;

		///
		virtual PMMatrix		GetParcelContentToFrameMatrix(ParcelKey key) const = 0;

		///
		virtual bool16			GetParcelAppearsMultiplePlaces(ParcelKey key) const = 0;

		/**
		In the context of the composing paragraph returns a tile matching
		the specified criteria. Note that because of straddle heads this
		call may result in the removal and/or addition of Parcels after the
		specified Parcel.
		@param affectedByVerticalJustification Set to kTrue the WaxLine is part of paragraph that would be normally spread by vertical justification. kFalse if affected by a dropcap, paragraph gyudori, etc.
		*/
		
		// Returns
		//	kFalse	Tile is at top of the Parcel but the specified top of Parcel
		//			alignment doesn't match the Parcel's.
		//
		//			pParcelKey		set the Parcel Key
		//			pYOffset		set to the top of the Parcel
		//			pTOPAlignment	set to the Parcel TOP alignment value
		//			pAtTOP			set to kTrue
		//
		//			The caller should simply re-call the method with the same
		//			values returned for ParcelIndex and yPosition but specify
		//			a TOP alignment compatible with the Parcel.
		//
		//	kTrue	A tile was found that fits the desired criteria.
		//
		//			pParcelKey			set to the Parcel Key (invalid if overset)
		//			pYOffset			set to bottom of the returned tile
		//			pTOPAlignment		set to the Parcel TOP alignment value
		//			pAtTOP				set to kTrue if tile is at the top of
		//								the Parcel, kFalse otherwise.
		//			pParcelPositionDependent	set to kTrue if the position of
		//										the tile was dependent on the
		//										position of the Parcel.
		//										Typically indicates that the
		//										tile was aligned to a non-
		//										Parcel relative grid.
		//			pLeftMargin			set to the left margin of the Parcel
		//			pRightMargin		set to the right margin of the Parcel
		//			tiles				has the returned tile(s)
		//
		virtual bool16			GetTiles(PMReal minWidth,
										PMReal height,
										PMReal TOPHeight,
										Text::GridAlignmentMetric gridAlignment,
										PMReal gridAlignmentAdj,
										Text::LeadingModel leadingModel,
										PMReal leading,
										PMReal leadingModelOffset,
										PMReal minHeightLeadingDiff,
										TextIndex nCurrentPosition,
										bool16 affectedByVerticalJustification,
										ParcelKey *pParcelKey,
										PMReal *pYOffset,
										Text::FirstLineOffsetMetric *pTOPHeightMetric,
										PMRectCollection& tiles,
										bool16 *pAtTOP,
										bool16 *pParcelPositionDependent,
										PMReal *pLeftMargin,
										PMReal *pRightMargin) const = 0;

		/// In the context of the composing paragraph
		virtual PMReal			GetParcelGrowableContentBottom(ParcelKey key) const = 0;

		//
		// In the context of the composing paragraph
		//
		// This method will return the Parcel Content Top plus any skipped area
		// due to active TileableTopAdj. Note that Content Top will allready
		// include any EffectiveTopAdj.
		//
		virtual PMReal			GetParcelTileableContentTop(ParcelKey key) const = 0;

		//
		// In the context of the composing paragraph
		//
		// This method will return the GrowableContentBottom minus any skipped
		// ranges.
		//
		// Note: This method may only be called during composition and only by
		// 		 composers that have committed to compose their WaxLine in the
		//		 specified or later Parcel. The internal composition support
		//		 code will consider this call notification that the composing
		//		 WaxLine wishes to do so and will resolve pending composing,
		//		 such as footnotes at the time of this call.
		//
		virtual PMReal			GetParcelTileableContentBottom(ParcelKey key) const = 0;

		/**
		Sometimes the ParcelContainer knows that it is going to be doing
		iterative composition and for performance reasons it does not want
		the new WaxLines to spend time build WaxRuns which may just be tossed
		away.
		Note that this is just an advisory, WaxLines which contain OwnedItems
		typically need to be notified in all cases and the OwnedItem may decide
		to trigger the WaxRuns to be created anyway.
		@param key ParcelKey of the Parcel where the new Wax is created.
		@return kTrue if new WaxLines created by the ParagraphComposer should be Inval()ed, kFalse otherwise.
		*/
		virtual bool16			GetParcelShouldInvalNewWax(ParcelKey key) const = 0;

	};


	class RecomposeHelper : public Tiler
	{
	protected:
		///
		PUBLIC_DECL					RecomposeHelper();

	private:
		///
		PUBLIC_DECL					RecomposeHelper(const RecomposeHelper& copy);
		///
		PUBLIC_DECL RecomposeHelper& operator=(const RecomposeHelper& copy);

	public:
		///
		virtual						~RecomposeHelper() { }

		virtual IDataBase*			GetDataBase() const = 0;

		/// ComposeScanner for the story being composed.
		virtual IComposeScanner*	GetComposeScanner() const = 0;

		/// Return the starting TextIndex of the TextStoryThread being composed.
		virtual TextIndex			GetThreadStart() const = 0;

		/// Return the span of the TextStoryThread being composed.
		virtual int32				GetThreadSpan() const = 0;

		/// Return the ending TextIndex of the TextStoryThread being composed.
		virtual TextIndex			GetThreadEnd() const = 0;

		/// Return the TextIndex of the start of the paragraph.
		virtual TextIndex			GetParagraphStart() const = 0;

		/// Returns the span of the paragraph including the final CR.
		virtual int32				GetParagraphSpan() const = 0;

		/// Return the TextIndex of the end of the paragraph.
		virtual TextIndex			GetParagraphEnd() const = 0;

		/// ITextParcelList for the TextStoryThread being composed.
		virtual const ITextParcelList* 	GetTextParcelList() const = 0;

		virtual bool16				ShouldFakeTabAlignToChar() const = 0;

		///
		virtual const ITextOptions*	GetTextOptions() const = 0;

		///
		virtual const IStoryOptions*	GetStoryOptions() const = 0;

		///
		virtual bool16				GetIsVertical() const = 0;

		///
		virtual IPairKernDict*		GetPairKernDict(ClassID whichAlgorithm) const = 0;

		///
		virtual IEdgeAlignDict*		GetEdgeAlignDict(ClassID whichAlgorithm) const = 0;

		///
		virtual IHyphenationService*	GetSimpleHyphenator() const = 0;

		///
		virtual IHyphenationService*	GetHyphenator(const ILanguage* pLanguage) const = 0;

		///
		virtual IHyphenationExceptions*	GetHyphenationExceptions(bool16 *pCheckUserDictionary) const = 0;

		/**
		Returns optional Idle timer. Implementations are encouraged to
		call this function to see if composition should be interrupted once
		they have made some progress.
		*/
		virtual IdleTimer*			GetIdleTimer() const = 0;

		/**
		Returns a "begin" iterator to a private OwnedItemDataList representing
		the OwnedItems in the span fromthe initial value for
		GetStartingTextIndex() to the end of the current Paragraph.
		@return begin iterator
		*/
		virtual const OwnedItemDataList::const_iterator	GetOwnedItemBeginIter() const = 0;

		/**
		Returns a "begin" iterator to a private OwnedItemDataList representing
		the OwnedItems in the span fromthe initial value for
		GetStartingTextIndex() to the end of the current Paragraph.
		@return end iterator
		*/
		virtual const OwnedItemDataList::const_iterator	GetOwnedItemEndIter() const = 0;

		/**
		Returns kTrue if any OwnedItems in the specified range has a StandOff
		which affects Text composition. It is recommended that clients
		call this method rather than computing this on their own to avoid
		duplication of effort.
		*/
		virtual bool16				GetOwnedItemsHaveStandOffsIn(TextIndex start, TextIndex end) const = 0;

		/**
		Returns the TextIndex of the WaxLine returned by GetWaxLine(). Note
		that as new WaxLines are applied through ApplyComposedLine() the
		value returned by this method will increase by the span of the WaxLine
		applies.
		*/
		virtual TextIndex			GetStartingTextIndex() const = 0;

		/// Returns the ParcelKey of the Parcel where tiling should begin from.
		virtual ParcelKey			GetStartingParcelKey() const = 0;

		/// Returns the YPosition where tiling should begin from.
		virtual PMReal				GetStartingYPosition() const = 0;

		/**
		Returns kTrue if the newly composed WaxLine will be kept with the
		previous WaxLine because of KeepWithNextNLines.
		kFalse if otherwise.
		*/
		virtual bool16				GetKeptWithPrevByNextNLines() const = 0;

		/**
		Returns kTrue if the newly composed WaxLine will be kept with the
		previous WaxLine because of KeepFirstNLines.
		kFalse if otherwise.
		*/
		virtual bool16				GetKeptWithPrevByFirstNLines() const = 0;

		/**
		Returns kTrue if the newly composed WaxLine will be kept with the
		previous WaxLine because of KeepTogether.
		kFalse if otherwise.
		*/
		virtual bool16				GetKeptWithPrevByAllLines() const = 0;

		/**
		Returns kTrue if the WaxLine at the TextIndex returned by
		GetStartingTextIndex() is Content damaged.
		*/
		virtual bool16				GetIsContentDamaged() const = 0;

		/**
		Returns kTrue if the WaxLine at the TextIndex returned by
		GetStartingTextIndex() is Keeps damaged.
		*/
		virtual bool16				GetIsKeepsDamaged() const = 0;

		/**
		Returns kTrue at the start of the Paragraph if the calculated state
		from the ParagraphStrand is invalid. Note that at the time of the
		call the state will have been already been set valid.
		@return kTrue if the state was invalid
		*/
		virtual bool16				GetParagraphCalculatedStateInvalid() const = 0;

		/**
		@return TextIndex of current waxWaxLine.
		*/
		virtual TextIndex 			GetWaxLineTextIndex() const = 0;

		/**
		If GetIsContentDamaged() returns kTrue, then this method will return
		the ParcelKey of the damaged WaxLine, otherwise it will return an
		invalid ParcelKey.
		*/
		virtual ParcelKey			GetWaxLineParcelKey() const = 0;

		/**
		If GetIsContentDamaged() returns kTrue, then this method will return
		the CompositionYPosition of the damaged WaxLine, otherwise it will
		return 0.0.
		*/
		virtual PMReal				GetWaxLineCompositionYPosition() const = 0;

		/**
		If GetIsContentDamaged() returns kTrue, then this method will return
		the LineHeightLeadingDiff of the damaged WaxLine, otherwise it will
		return 0.0.
		*/
		virtual PMReal				GetWaxLineLineHeightLeadingDiff() const = 0;

		/**
		If GetIsContentDamaged() returns kTrue, then this method will return
		the KeepsViolation of the damaged WaxLine, otherwise it will
		return kFalse.
		*/
		virtual bool16				GetWaxLineKeepsViolation() const = 0;

		/**
		Returns the current TextSpan ofthe damaged WaxLine. Note that this span
		may exceed the end of the current Paragraph.
		*/
		virtual int32				GetWaxLineTextSpan() const = 0;

		/**
		Returns a pointer to the (undamaged) WaxLine previous to the one
		returned by GetWaxLine(). Return nil if the current WaxLine is at the
		beginning of the TextStoryThread.
		*/
		virtual const IWaxLine*		GetPreviousWaxLine() const = 0;

		/**
		Returns the starting TextIndex of the previous WaxLine. The span of the
		previous WaxLine can be computed by simply subtracting the TextIndex of
		the current WaxLine from the value returned by this method.
		*/
		virtual TextIndex			GetPreviousWaxLineTextIndex() const = 0;

		/**
		Returns the hyphenation ladder pattern for previous WaxLines in
		the same paragraph and in the same Parcel as returned by a call to
		GetStartingParcelKey(). The LSB bit of the uchar will be 1 in the
		previous WaxLine (as returned by GetPreviousWaxLine()) has a hyphen
		and on in the same way until the MSB bit of the uchar correponding to
		the 8th previous WaxLine.
		*/
		virtual uchar				GetPreviousHyphenLadderPattern() const = 0;

		/**
		@return a ptr to a new WaxIterator so caller can glean information about previously applied WaxLines. See IWaxStrand for more information.
		This is not an InterfacePtr! Should be put into a K2::scoped_ptr<IWaxIterator>.
		*/
		virtual IWaxIterator *		NewWaxIterator(bool16 changeAware = kFalse) const = 0;

		/**
		The implementation is given the opportunity to adjust the starting
		TextIndex of the composition, potentially adjusting the starting
		TextIndex all the way back to the beginning of the paragraph.
		This method and BackupOneLineTowardsParagraphStart() are the only
		approved ways for implementations to change
		the TextIndex that they are asked to compose at.
		Note that this method may not succeed in backing up all the way to
		the paragraph start because of the presence of Keeps damage, soft CRs
		and WaxAnchors, although it may succeeded in changing the starting
		TextIndex part way. Callers should call GetStartingTextIndex() to
		determine the new TextIndex.
		Note that after successfully backing up any amount the callee
		MUST not attempt to apply new WaxLines and should instead return
		kFalse from Recompose() immediately. The ParagraphComposer
		will be called back at a later time with the new starting TextIndex.
		@return kTrue if the position changed.
		*/
		virtual bool16				BackupTowardsParagraphStart() = 0;

		/**
		This method is similar to BackupTowardsPargraphStart() with the
		exception that it always succeeds, as long as the starting TextIndex
		is not already at the beginning of the Paragraph, and is not stopped
		by the presence of soft CRs and WaxAnchors.
		Note that after successfully backing up any amount the callee
		MUST not attempt to apply new WaxLines and should instead return
		kFalse from Recompose() immediately. The ParagraphComposer
		will be called back at a later time with the new starting TextIndex.
		@return kTrue if the position changed.
		*/
		virtual bool16				BackupOneLineTowardsParagraphStart() = 0;

		/**
		All WaxLines in the Paragraph are marked destroyed.
		@return kTrue if the implementation damaged behind the current point of composition.
		*/
		virtual bool16				DestroyAllWaxLinesInParagraph() = 0;

		/**
		This method tells the implementation that one or more OwnedItems have
		been added or removed during composition. It must be called BEFORE
		any new WaxLines are applied or the composer returns.
		*/
		virtual void				OwnedItemsChanged() = 0;

		/// Creates a new IWaxLine suitable for applying into the WaxStrand.
		virtual IWaxLine*			QueryNewWaxLine() const = 0;

		/**
		Apply a WaxLine into the WaxStrand previously created by a call to
		QueryNewWaxLine(). The TextIndex used for the apply will be the current
		value returned by GetStartingTextIndex() which will be advanced by this
		call by the amount of newTextSpan. By default, the next WaxLine in the
		same TextStoryThread will be Geometry damaged, but this can be disabled
		by setting 'applyDamageDisable' to kTrue.
		@param newWaxLine
		@param newTextSpan
		@param applyDamageDisable If set to kTrue, the next WaxLine will NOT be Geometry damaged after the new WaxLine is applied.
		@param disableApplyInval Some composers take responsibility for invalidating sub-portions of the WaxLine being composed and thus do not want the WaxStrand to automatically invalidate the entire WaxLine on apply. This applies to both the invaliation of the target WaxLine AND the new WaxLine.
		@param forceInkCache If kTrue, the WaxLine will be asked for its InkBounds after it has been applied.
		*/
		virtual void				ApplyComposedLine(IWaxLine* newWaxLine,
											int32 newTextSpan,
											bool16 disableApplyDamage = kFalse,
											bool16 disableApplyInval = kFalse,
											bool16 forceInkCache = kFalse) = 0;

		/**
		The current WaxLine returned by GetWaxLine() has its NoShuffle flag
		set to kTrue.
		*/
		virtual void				SetNoShuffle() = 0;

		/**
		Starting with the current WaxLine returned by GetWaxLine(), enough
		WaxLines to cover the specified number of characters will be Content
		damaged. Note that if the WaxLines already have more severe damage, such
		as Geometry or Destroyed, then this method will have no effect.
		*/
		virtual void				MarkContentDamage(int32 nChars) = 0;

		/**
		The current WaxLine returned by GetWaxLine() has its damage reset to
		Content and its NoShuffle flag set to kTrue.

		This method supports certain types of interrupted composition on the
		starting WaxLine by allowing the caller to reset the damage of the
		WaxLine to ContentDamage.
		Most paragraph composers will refuse to be interrupted in the middle of
		their paragraph but some composers, notably the WaxAnchorComposers, take
		too much time to compose and need to leave without having finished the
		composition of their WaxLine.
		However, since they may have done some work towards composition they
		need to be able differentiate between getting new damage and damage
		that they have already seen. This helps them avoid circular composition
		loops.
		*/
		virtual void				ResetDamageToContent() = 0;

		/**
		The WaxLine at the specified TextIndex is content damaged. The
		specified TextIndex must be less than the current value returned by
		GetStartingTextIndex() and be within the same TextStoryThread. Unlike
		the other calls to affect damage, the WaxLines(s) will only be damaged
		when the ParagraphComposer returns from Recompose().
		*/
		virtual void				MarkContentDamagePreviousAt(TextIndex at) = 0;

		/**
		*/
		virtual void				SetDeferredCompositionDueToKeeps() = 0;

		/**
		ADOBE INTERNAL USE ONLY
		*/
		virtual TextIndex			GetNoDamageBackTextIndex() = 0;

		/**
		ADOBE INTERNAL USE ONLY
		*/
		virtual int32 GetShapingEngine() const = 0;

		/**
		ADOBE INTERNAL USE ONLY
		*/
		virtual void SetShapingEngine(int32 shapingEngine) = 0;
	};

	/**
	Build IWaxLines using the specified helper.
	@param helper
	@return kTrue if the composer applied at least one WaxLine into the helper, kFalse if the composer backed up the start of composition.
	*/
	virtual bool16 Recompose(RecomposeHelper* helper) = 0;


	class RebuildHelper
	{
	protected:
		///
		PUBLIC_DECL					RebuildHelper();

	private:
		///
		PUBLIC_DECL					RebuildHelper(const RebuildHelper& copy);
		///
		PUBLIC_DECL RebuildHelper& operator=(const RebuildHelper& copy);

	public:
		///
		virtual						~RebuildHelper() { }

		virtual IDataBase*			GetDataBase() const = 0;

		/// ComposeScanner for the story being composed.
		virtual IComposeScanner*	GetComposeScanner() const = 0;

		/// Return the starting TextIndex of the TextStoryThread being composed.
		virtual TextIndex			GetThreadStart() const = 0;

		/// Return the span of the TextStoryThread being composed.
		virtual int32				GetThreadSpan() const = 0;

		/// Return the ending TextIndex of the TextStoryThread being composed.
		virtual TextIndex			GetThreadEnd() const = 0;

		/// Return the TextIndex of the start of the paragraph.
		virtual TextIndex			GetParagraphStart() const = 0;

		/// Returns the span of the paragraph including the final CR.
		virtual int32				GetParagraphSpan() const = 0;

		/// Return the TextIndex of the end of the paragraph.
		virtual TextIndex			GetParagraphEnd() const = 0;

		/// IParcelList for the TextStoryThread being composed.
		virtual const IParcelList*	GetParcelList() const = 0;

		/// ITextParcelList for the TextStoryThread being composed.
		virtual const ITextParcelList* 	GetTextParcelList() const = 0;

		virtual bool16 ShouldFakeTabAlignToChar() const = 0;

		///
		virtual const ITextOptions*		GetTextOptions() const = 0;

		///
		virtual const IStoryOptions*	GetStoryOptions() const = 0;

		///
		virtual bool16					GetIsVertical() const = 0;

		///
		virtual IPairKernDict*			GetPairKernDict(ClassID whichAlgorithm) const = 0;

		///
		virtual IEdgeAlignDict*			GetEdgeAlignDict(ClassID whichAlgorithm) const = 0;

		///
		virtual IHyphenationService*	GetSimpleHyphenator() const = 0;

		///
		virtual IHyphenationService*	GetHyphenator(const ILanguage* pLanguage) const = 0;

		///
		virtual IHyphenationExceptions*	GetHyphenationExceptions(bool16 *pCheckUserDictionary) const = 0;

		///
		virtual TextIndex			GetTextIndex() const = 0;

		/// Returns a pointer to the WaxLine being rebuilt.
		virtual const IWaxLine*		GetWaxLine() const = 0;

		/**
		Returns a pointer to the (undamaged) WaxLine previous to the one
		returned by GetWaxLine(). Return nil if the current WaxLine is at the
		beginning of the TextStoryThread.
		*/
		virtual const IWaxLine*		GetPreviousWaxLine() const = 0;

		virtual UID GetParcelFrameUID() const = 0;

		virtual PMRect GetParcelContentBounds() const = 0;
		virtual bool16 IsParcelContentAnArea() const = 0;
		virtual PMReal GetParcelEffectiveVerticalSpacing() const = 0;

		/**
		Returns a "begin" iterator to a private OwnedItemDataList representing
		the OwnedItems in the span of the WaxLine.
		@return begin iterator
		*/
		virtual const OwnedItemDataList::const_iterator	GetOwnedItemBeginIter() const = 0;

		/**
		Returns an "end" iterator to a private OwnedItemDataList representing
		the OwnedItems in the span of the WaxLine.
		@return end iterator
		*/
		virtual const OwnedItemDataList::const_iterator	GetOwnedItemEndIter() const = 0;

		/**
		ADOBE INTERNAL USE ONLY
		*/
		virtual int32 GetShapingEngine() const = 0;

		/**
		ADOBE INTERNAL USE ONLY
		*/
		virtual void SetShapingEngine(int32 shapingEngine) = 0;

	};

	/**
	This is used to regenerate composed text data from the minimal data
	stored on disk. It is ok to return kFalse and not do anything.
	@param helper
	*/
	virtual bool16 RebuildLineToFit(RebuildHelper* helper) = 0;

	/**
	This is used to regenerate composed text data with overrides. It is ok to return kFalse and not do anything.
	@param helper
	@param overrides
	@param clearOverrides - set true if overrides need to be cleared and not applied.
	*/
	virtual bool16 RebuildLineWithOverrides(IParagraphComposer::RebuildHelper* helper, const AttributeBossList *overrides, bool16 clearOverrides=kFalse) = 0;

};

#endif

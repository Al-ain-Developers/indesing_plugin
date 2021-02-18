//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextParcelList.h $
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
#ifndef __ITextParcelList__
#define __ITextParcelList__

#include "IPMUnknown.h"
#include "IParcelList.h"
#include "ITextParcelListData.h"

#include "CTextEnum.h"
#include "DrawPassInfo.h"
#include "OwnedItemDataList.h"
#include "PMMatrix.h"
#include "PMRect.h"
#include "TextID.h"
#include "UIDList.h"

class ICallback;
class IComposeScanner;
class IDocumentLayer;
class IFrameList;
class IGraphicsContext;
class IParcelContainer;
class IInlineData;
class IStandOffData;
class ISpread;
class ITextSelectionDrawer;
class ITextStoryThread;
class ITextModel;
class IWaxAnchoredElement;
class IWaxLine;
class IWaxStrand;

class GraphicsData;
class IdleTimer;
class RangeData;
class TabStopTable;
class ContainerComposer;

/**
	@ingroup text_layout
*/
class ITextParcelList : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTPARCELLIST };

		//
		// Composed state of the Text Parcel List
		//
		virtual UIDRef		GetTextModelRef() const = 0;
		virtual UIDRef		GetWaxStrandRef() const = 0;

		virtual ITextStoryThread *	QueryStoryThread() const = 0;
		virtual RangeData	GetThreadRange() const = 0;
		virtual TextIndex	GetThreadStart(int32* pSpan = nil) const = 0;
		virtual int32		GetThreadSpan(TextIndex* pStart = nil) const = 0;

		virtual TextIndex	GetTextStart(ParcelKey key) const = 0;
		virtual int32		GetTextSpan(ParcelKey key) const = 0;
		virtual RangeData	GetTextRange(ParcelKey key) const = 0;
		virtual void		SetTextSpan(ParcelKey key, int32 span) = 0;

		//
		// These methods return the ParcelKey of the Parcel which contains the
		// specified TextIndex (or start of RangeData). If the TextIndex is
		// in overset an invalid ParcelKey will be returned.
		//
		// The LeanLeft variant behaves the same as the other variant except
		// that it treats the first TextIndex in the Parcel as being mapped to
		// the previous Parcel. Most casual users should use the non-LeanLeft
		// variant.
		//
		// NOTE	It is important that the client check for invalid ParcelKeys
		//		before proceeding to use them in the methods of this interface.
		//		The only exception to this is IParcelList::begin(key)/end(key)/
		//		rbegin(key)/rend(key). See that file for more information.
		//
		virtual ParcelKey	GetParcelContaining(TextIndex at) const = 0;
		virtual ParcelKey	GetParcelContainingLeanLeft(TextIndex at) const = 0;
		virtual ParcelKey	GetParcelContaining(const RangeData& location) const = 0;
		virtual void		GetParcelsContaining(const RangeData& r,
											ParcelKey* firstParcel,
											ParcelKey* lastParcel) const = 0;

		/**
		The TextParcelList is considered overset if any content other than the
		last CR in the associated TextStoryThread is not composed in Parcels
		BEFORE the Parcel returned by
		ITextParcelListData::GetLastOversetParcelKey().
		@param pFirstOversetTextIndex Optional pointer that will be filled in the TextIndex of the first overset text.
		@return kTrue if overset, kFalse otherwise.
		*/
		virtual bool16		GetIsOverset(TextIndex* pFirstOversetTextIndex = nil) const = 0;

		/**
		Returns the TextIndex of the first character that is NOT mapped to a
		Parcel BEFORE the Parcel returned by
		ITextParcelListData::GetOversetParcelKey(). If all of the
		TextStoryThread is composed within those Parcel then kInvalidTextIndex
		is returned.
		Note that because of WaxAnchoredElements, this method is not sufficient
		to determine if the TextParcelList is overset, use GetIsOverset().
		@param pThreadLast will be set to the last TextIndex in the TextStoryThread.
		@return TextIndex of the first Text content which is composed beyond the last Logical Parcel.
		*/
		virtual TextIndex	GetFirstOversetTextIndex(TextIndex* pThreadLast = nil) const = 0;

		//
		// These methods help navigate through the ParcelList since some
		// ParcelLists may have Parcels that are not to be composed into, such
		// as in Table Headers/Footers.
		//
		virtual ParcelKey	GetFirstLogicalParcelKey() const = 0;

		virtual ParcelKey	GetNextLogicalParcelKey(ParcelKey key) const = 0;

		virtual ParcelKey	GetLastLogicalParcelKey() const = 0;

		virtual ParcelKey	GetLastLogicalNonOversetParcelKey() const = 0;

		//
		// Iterators
		//
		// It is acceptable to pass in an invalid ParcelKey to begin()/end()/
		// rbegin()/rend(). The resulting iterator will be the same as if the
		// caller had called the end()/rend() methods with no key argument.
		//
		class const_iterator;
		class const_reverse_iterator;
		virtual const_iterator			begin() const = 0;
		virtual const_iterator			begin(ParcelKey key) const = 0;
		virtual const_iterator			end() const = 0;
		virtual const_iterator			end(ParcelKey key) const = 0;
		virtual const_reverse_iterator	rbegin() const = 0;
		virtual const_reverse_iterator	rbegin(ParcelKey key) const = 0;
		virtual const_reverse_iterator	rend() const = 0;
		virtual const_reverse_iterator	rend(ParcelKey key) const = 0;

		//
		// Text Parcel List Properties
		//
		virtual Text::FirstLineOffsetMetric	GetFirstLineOffsetMetric(ParcelKey key) const = 0;
		virtual PMReal		GetMinFirstLineOffset(ParcelKey key) const = 0;
		virtual bool16		GetIsVertical() const = 0;
		virtual bool16		GetIsRightToLeft() const = 0;

		virtual bool16		GetParcelHasBeenVJed(ParcelKey key) const = 0;

		//
		// These methods simply call the ITextTiler methods of the same
		// name. If you already have a Parcel you should call directly rather
		// than using these interfaces.
		//
		virtual PMRect		GetParcelContentBounds(ParcelKey key) const = 0;
		virtual PMMatrix	GetParcelToContentMatrix(ParcelKey key) const = 0;

		//
		// SoftBottom
		//
		// A Parcel which allows Text Tiling to go past the bottom of the
		// Parcel and still be part of the same Parcel (but not visible) is
		// considered to have a SoftBottom. All WaxLines that are tiled off
		// the end of the Parcel but still less than the Max height are
		// considered part of the Parcel but are marked not visible and will
		// not draw.
		//
		virtual PMReal		GetMaxSoftBottomHeight(ParcelKey key) const = 0;

		//
		// Composition is a delicate thing...
		//
		// When an undamaged WaxLine is damaged the InkBound rectangle of the
		// WaxLine (in Parcel coordinates) is given to the SetPendingInval()
		// method and the Parcel is marked damaged through SetDamage().
		//
		// The Recompose() method is eventually called by the owning container
		// (TextFrame, Table, etc).
		//
		// When a WaxLine is applied into a Parcel by the WaxStrand the
		// following occurs:
		//	1) The SetRecomposing() method is called.
		//	2) If the owning container is in view the InkBound rectangle of
		//	   the new WaxLine is given to the SetPendingInval() method.
		//
		// This process then repeats itself until the composition of the
		// original Parcel(s) is complete.
		//
		// Note that starting composition in one Parcel may in fact lead to
		// new WaxLines being applied in other Parcels due to either the
		// ParagraphComposer backing up out of the starting Parcel or simply
		// running off of the starting Parcel into the next one.
		//
		virtual bool16		GetIsDamaged(ParcelKey key) const = 0;
		virtual void		SetDamaged(ParcelKey key) = 0;

		/**
		*/
		virtual ParcelKey	GetFirstDamagedParcel() const = 0;

		/**
		This method returns the ParcelKey of the first Parcel in the ParcelList
		which needs composition. Note because of the subtle iteraction with
		Parcels that needs to check for wrap, this method is not the same as
		simply returning the first damaged or first needs wrap check Parcel. In
		particular, a Parcel needing wrap check which is beyond the Parcel
		containing the end of the story thread is NOT considered to need
		composition.
		@return Invalid ParcelKey if no Parcel needs composition
		*/
		virtual ParcelKey	GetFirstParcelNeedingComposition() const = 0;

		/**
		RecomposeResult
		*/
		enum RecomposeResult
		{
			/**
			The Parcel was either not Wax damaged or after handling wrap check
			damage no wax was damaged as a result. The Parcel remains fully
			composed and without any wax damage.
			*/
			kRR_NothingToCompose,

			/**
			A Parcel in a previous container became damaged.
			*/
			kRR_DamagedBackParcel,

			/**
			Composition was interrupted due to the interruptCheck. This will
			only be returned if and IdleTimer is specified.
			*/
			kRR_Interrupted,

			/**
			The container is now fully composed upto the specified TextIndex.
			This will only be returned if the optional composeUpToTextIndex
			parameter is not kInvalidTextIndex AND after the Column containing
			the TextIndex is fully composed the Container still needs
			composition.
			*/
			kRR_ComposedUpTo,

			/**
			The container is now fully composed.
			*/
			kRR_FullyComposed

		};

		/**
		Recompose Parcels.
		
		WARNING: This method should only be called by the implementors
		of the ITextParcelListData which is the only code with enough
		knowledge of the proper context in which this can be called.
		@param container Pointer to IParcelContainer which will be used to drive the composition on the container.
		@param firstContainerPI The index within the ParcelList of the first Parcel of the container.
		@param noDamageBackPrevContainers If kTrue, composition of the specified container must not result in damage to any Parcels in previous ParcelContainers. This should only be set if the ParcelList being composed is associated with a containing ParcelList (such as the FrameList) otherwise incorrect composition will result.
		@param vj VerticalJustification
		@param vjMaxInterParaSpace
		@param vjBalanceColumns
		@param firstDamagedPI index within the IParcelList of the first Parcel which is damaged. May be set to kInvalidParcelIndex if firstNeedWrapCheckPI is NOT kInvalidParcelIndex.
		@param firstNeedWrapCheckPI index within the IParcelList of the first Parcel which needs wrap check. May be set to kInvalidParcelIndex if firstDamagedPI is NOT kInvalidParcelIndex.
		@param composeUpToTextIndex Optional parameter for TextIndex within the thread which the container will compose 'columns' upto. If the TextIndex is beyond the end of the Container then it has no effect. If it ends within the Container, and the Container and stop composing in the 'column' that it is in, then the method will return early. Otherwise the entire Container will be composed.
		@param interruptCheck Optional pointer to IdleTimer class that will be used in some circumstances to interrupt composition before the container is fully composed.
		@param tilableHeightRemaining Options pointer to PMReal which will be filled in with an estimate of the tileable height remaining in the Container (before VJ was run) if the returned value is kRR_FullyComposed.
		@return RecomposeResult 
		*/
		virtual RecomposeResult	Recompose(IParcelContainer* container,
										int32 firstContainerPI,
										bool16 noDamageBackPrevContainers,
										Text::VerticalJustification vj,
										PMReal vjMaxInterParaSpace,
										bool16 vjBalanceColumns,
										int32 firstDamagedPI,
										int32 firstNeedWrapCheckPI,
										TextIndex composeUpToTextIndex = kInvalidTextIndex,
										IdleTimer* interruptCheck = nil,
										PMReal* tileableHeightRemaining = nil) = 0;

		//
		// The text content can become damaged in various ways other than
		// direct changes to the content.
		//

		/**
		Damage ranges of Text. This method does not damage waxLines, it just
		updates the span state.
		@param at TextIndex for the start of the damage range.
		@param amt Length of damage range, must be > 0, must end before the end of the story thread owning the starting TextIndex.
		@param limitLeanLeftParcelIndex If NOT kInvalidParcelIndex, the index in the controlling ParcelList for which we will not do lean left damage.
		@return kTrue if limitLeanLeftParcelIndex was valid AND it resulted in a limit to leaning left.
		*/
		virtual bool16		MarkDamage(TextIndex at,
										int32 amt,
										int32 limitLeanLeftParcelIndex) = 0;

		/**
		Used only by WaxStrand to maintain consistent text spans in the parcels.
		*/
		virtual void		AdjustSpans(TextIndex at, int32 amt) = 0;

		// These methods provide support for specific common operations that
		// affect the text content. The will compute the span of text that
		// needs to be damaged for that operation.
		//
		// MarkParcelInsertDamage		The parcel list has changed.
		// MarkParcelRemoveDamage		""
		// ComputeResizeDamage			The parcel has changed it's size.
		// ComputeMoveDamage			The parcel has been moved relative to
		//						  		underlying pasteboard. It may or may
		//								not have been moved relative to the
		//								underlying Frame.
		//
		// These methods are provided out of convenience to functions that wish
		// to change the composition environment of the Text such as changing
		// FirstLineOffset, rotating text, etc. It is left upto to the specific
		// function to determine what extent of damage is appropriate.
		//
		// ComputeFirstLineDamage		Compute damage for the first line of
		//								text that COULD compose in the Parcel.
		//								Note this line might not actually be in
		//								the Parcel.
		// ComputeEntireParcelDamage	Compute damage for all text in the
		//								Parcel including the first line of text
		//								in the next Parcel.
		// ComputeFirstLineInNextParcelDamage	Compute damage for the first
		//										line that is in the next Parcel.
		//										This is used to "pull up" lines
		//										into the Parcel.
		//
		// Note: All PMRects are expressed in Parcel coordinates.
		//
		virtual void		MarkParcelInsertDamage(ParcelKey key) = 0;

		virtual void		MarkParcelRemoveDamage(ParcelKey key) = 0;

		virtual void		MarkResizeDamage(ParcelKey key,
						 			const PMRect &boundsBefore,
						 			const PMRect &boundsAfter) = 0;

		virtual void		MarkMoveDamage(ParcelKey key) = 0;

		virtual void		MarkGridDamage(ParcelKey key) = 0;

		/**
		This method will damage a range of Text without causing any back-up damage to a Parcel previous to the one specified.
		The caller specifies the Text range to be damaged but they also must specify the range of the Parcels that may be damaged by this action.
		Only used during composition since for all changes to the TextModel we want to lean-left to previous Parcels and failure to do so will result in ASSERTs by the WaxLineCompositionIter.
		@param limitFirstParcelKey The first Parcel that can become damaged - no damage before this point. If damageStart equals damageEnd, then this Parcel will be marked damaged, otherwise this Parcel will only be damaged if the start of the damage range is containing by this Parcel or we lean-left into it.
		@param threadStart The TextIndex of the start of the Thread managed by this TextParcelList. We could calculate it ourselves but most callers have it anyway.
		@param damageStart TextIndex of the first point of damage - must be within the Parcel specified by 'firstParcelKey'
		@param limitFirstParcelIndex Index within the controlling ParcelList of the Parcel specified by 'limitFirstParcelKey'
		@param damageEnd TextIndex of the end point of damage.
		@param lastParcelIndex Index within the controlling ParcelList of the last Parcel to be damaged. Only used when damageStart equals damageEnd, otherwise the last Parcel damaged will be one containing the last TextIndex of the damage range.
		*/
		virtual void		MarkCompositionDamageNoLean(ParcelKey limitFirstParcelKey,
													TextIndex threadStart,
													TextIndex damageStart,
													int32 limitFirstParcelIndex,
													TextIndex damageEnd,
													int32 lastParcelIndex) = 0;

		virtual void		DamageFirstLine(ParcelKey key) = 0;
		virtual void		DamageEntireParcel(ParcelKey key, int32 limitLeanLeftParcelIndex = kInvalidParcelIndex) = 0;
		virtual void		DamageEntireParcelP1(ParcelKey key,	int32 limitLeanLeftParcelIndex = kInvalidParcelIndex) = 0;
		virtual void		DamageFirstLineInNextParcel(ParcelKey key) = 0;
		virtual void		DamageYRange(ParcelKey key, const PMReal& waxYTop,
									const PMReal& waxYBottom) = 0;
		/*
		This method damages the Wax Anchored Elements(containing foonotes as of now) found in a parcel given that they intersect/lie between with waxYTop & waxYBottom.
		@param key - key of the parcel whose WAE needs to be damaged
		@param waxYTop - top Y position of wax line
		@param waxYBottom - bottom Y position of wax line
		*/
		virtual void		DamageWaxAnchoredElementYRange(ParcelKey key, const PMReal& waxYTop,
									const PMReal& waxYBottom) = 0;

		typedef void		(ITextParcelList::*ComputeMethod1)(ParcelKey,
									TextIndex*, int32*) const;
		typedef void		(ITextParcelList::*ComputeMethod2)(ParcelKey,
									const PMRect&, const PMRect&,
									TextIndex*, int32*) const;

		virtual void		Damage(ComputeMethod1, ParcelKey key, int32 limitLeanLeftParcelIndex = kInvalidParcelIndex) = 0;

		virtual void		Damage(ComputeMethod2, ParcelKey key,
									const PMRect& b1, const PMRect& b2) = 0;

		virtual void		ComputeResizeDamage(ParcelKey key,
								 	const PMRect &boundsBefore,
								 	const PMRect &boundsAfter,
									TextIndex *pStart, int32 *pLen) const = 0;

		virtual void		ComputeFirstLineDamage(ParcelKey key,
									TextIndex *pStart, int32 *pLen) const = 0;
		virtual void		ComputeEntireParcelDamage(ParcelKey key,
									TextIndex *pStart, int32 *pLen) const = 0;
		virtual void		ComputeEntireParcelP1Damage(ParcelKey key,
									TextIndex *pStart, int32 *pLen) const = 0;
		virtual void		ComputeFirstLineInNextParcelDamage(ParcelKey key,
									TextIndex *pStart, int32 *pLen) const = 0;

		//
		// Inval the WaxLines for the specified range.
		//
		virtual void		Inval(TextIndex start, int32 span) const = 0;

		//
		// Not all break values are supported by all implementations. If the
		// implementation does not support the particular break mode for the
		// particular Parcel then it should return kFalse which will ensure
		// that no adjustment to the Paragraph starting position will occur.
		//
		// If the implementation does not support ANY break modes then it
		// should return kFalse for the second method.
		//
		virtual bool16		GetIsValidStartBreakLocation(ParcelKey key,
									Text::StartBreakLocation mode) const = 0;
		virtual bool16		GetHasAnyValidStartBreakLocation() const = 0;

		//
		// Return information needed by IParcelShape.
		//
		virtual void		GetShapeData(ParcelKey key,
										PMRect *inkBounds,	// parcel coord.
										int32 *passCount,
										Text::DrawPassInfo **passList) = 0;

		//
		// Draw a parcel.
		//
		virtual void		DrawParcel(ParcelKey key,
										GraphicsData* gd,
										int32 iShapeFlags,
										const PMRect* areaToDraw,
										const int32 passCount,
										const Text::DrawPassInfo* passList,
										void (*btdFunc)(void *),
										void (*btfdFunc)(void *),
										void* funcPrv,
										bool16* pInkBoundsChanged) = 0;

		//
		// Composed Bounds.
		//
		// The composed bounds represent the smallest amount of space the
		// composed text fit in so it does NOT including any amounts due to
		// Vertical Justification. The bounds are returned in Content
		// coordinates. This information is valuable for computing autogrow.
		//
		// See GetParcelContentBounds() to get the bounds used by the
		// Tiler to tile within the Parcel. Most users will want to use that
		// interface instead of this one.
		//
		virtual PMRect		GetParcelComposedBounds(ParcelKey key) const = 0;

		/**
		Given a point in Pasteboard coordinates, return the TextIndex of
		the closest character/glyph in this Parcel. Only returns TextIndexes
		within this TextStoryThread. The TextParcelList is required
		to be fully composed upto this point. Note that it is not possible to
		hit below the last line in the story thread, the location returned will
		be to the left of the final CR.
		@param key Parcel
		@param pasteboardPt
		@param nextLine The TextIndex of the end of the WaxLine (which is the start of the next WaxLine)
		@returns The TextIndex of the closest character/glyph in this Parcel.
		*/
		virtual PMReal		HitTestParcel(ParcelKey key,
										const PMPoint &pasteboardPt,
										TextIndex *nextLine = nil) = 0;

		/**
		Iterate over every object in a given parcel and call its
		IterateDrawOrder method
		*/
		virtual void		IterateTextParcelListDrawOrder( const PMMatrix *xform,
												ICallback *callbackInfo,
												int32 iShapeFlags,
												ParcelKey key) const = 0;

		/**
		The purpose of this API is for composition/regen code to determine if it should act like there is a tab character as the first
		character of paragraphs in this story thread. This gives table cells the ability to have align to character tab functionality
		without having an actual tab character in the model.
		*/
		virtual bool16		ShouldFakeTabAlignToChar() const = 0;

		/**
		Collects all the OwnedItems and WaxAnchoredElements associated with Parcel. This method supports IVisitorHelper implementations that have Text.
		@param key
		@param list
		*/
		virtual void		CollectParcelChildren(ParcelKey key, UIDList* list) const = 0;

		/**
		@param wae	The WaxAnchoredElement to insert.
		@param atParcel The Parcel that the WaxAnchoredElement will start life in.
		*/
		virtual void		InsertWaxAnchoredElement(IWaxAnchoredElement* wae,
													ParcelKey toKey) = 0;

		/**
		*/
		virtual void		RemoveWaxAnchoredElement(IWaxAnchoredElement*wae) = 0;

		/**
		*/
		virtual void		MoveWaxAnchoredElement(IWaxAnchoredElement* wae,
													ParcelKey toKey) = 0;

		/**
		This method tells the TextParcelList that the WaxLine at the specified
		TextIndex has changed its ink bounds outside of composition. The WaxRun
		and WaxLine containing that TextIndex will have their caches
		invalidated appropriately before NotifyInkBoundsChanged() is called
		internally on the appropriate Parcel.
		@param at TextIndex of the WaxLine that changed.
		@param fromRebuild kTrue if the WaxLine at the specified TextIndex is being rebuilt, kFalse otherwise.
		*/
		virtual void		NotifyInkBoundsChangedAt(TextIndex at,
													bool16 fromRebuild) = 0;

		/**
		This method tells the TextParcelList that some Wax element in the
		specified Parcel has changed its ink bounds outside of composition.
		*/
		virtual void		NotifyParcelInkBoundsChanged(ParcelKey key) = 0;

		/**
		This method tells the TextParcelList that some Wax element in the
		specified Parcel has become position dependent. This call is typically
		made outside of the composition of the Parcel.
		*/
		virtual void		NotifyParcelPositionDependentContentSet(ParcelKey key) = 0;

		/**
		Given a point in Wax coordinates, return the TextIndex of the closest
		character/glyph in this Parcel. The TextParcelList is required
		to be fully composed upto this point. Note that it is not possible to
		hit below the last line in the story thread, the location returned will
		be to the left of the final CR.
		@param key Parcel
		@param waxPt
		@param withinSTOnly If kTrue, then the we will not burrow into Tables or WaxAnchoredElements looking for a better hits.
		@param nextLine The TextIndex of the end of the WaxLine (which is the start of the next WaxLine)
		@returns The TextIndex of the closest character/glyph in this Parcel.
		*/
		virtual PMReal		HitTestParcel(ParcelKey key,
										const PMPoint &waxPt,
										bool16 withinSTOnly,
										TextIndex *nextLine) const = 0;


		/**
		Appends the list of OwnedItems that are associated with the specified
		Parcel. Only those OwnedItems that are actually composed within the
		Parcel are added. Note that because of the presence of WaxAnchorPts and
		WaxAnchoredElements it is not sufficient to use the span of the
		Parcel to compute this.
		@param key
		@param rList The results are appended to the list.
		*/
		virtual void		CollectParcelOwnedItems(ParcelKey key,
										OwnedItemDataList* rList) const = 0;

		/**
		Returns kTrue if the Parcel has no Text span AND no
		WaxAnchoredElemenents with any content.
		@param ParcelKey
		@param optionalIsOnlyLastCR Pointer to bool which will be set to kTrue if the Parcel ONLY contains the final CR of the story thread, kFalse otherwise.
		*/
		virtual bool16		GetParcelIsEmpty(ParcelKey key,
										bool16* optionalIsOnlyLastCR = nil) const = 0;

		/**
		@param ParcelKey
		@param newDocLayer
		*/
		virtual void		NotifyParcelLayerChanged(ParcelKey key,
										const IDocumentLayer* newDocLayer) = 0;

		/**
		@param ParcelKey
		*/
		virtual void		NotifyParcelVisibilityChanged(ParcelKey key) = 0;

		/**
		@param ParcelKey
		*/
		virtual void		NotifyParcelZOrderChanged(ParcelKey key) = 0;

		/**
		@param ParcelKey
		*/
		virtual void		NotifyParcelIgnoreWrapChanged(ParcelKey key) = 0;

		/**
		Adds Wraps during composition that are children of an inlines. Because
		these Wraps are never from MasterPages, the X/YOffset component of the
		Wrap is always zero and so we never pass it in.
		@param key ParcelKey that the inline is registered in
		@param spreadRef UIDRef of ISpread that the key is on
		@param sodList TextWrapRefList of active IStandOffData
		*/
		virtual void		AddParcelInlineWraps(ParcelKey key,
											const IInlineData* id,
											const UIDRef& spreadRef,
											const TextWrapRefList& sodList) = 0;

		/**
		The specified Wrap affecting the specified Parcel has changed in some
		way that is based on ZOrder. This could be ZOrder based on the Wraps
		IHierarchy, the Wraps Layer, the ZOrder of the Wraps Layer, the
		visibility of the Wraps Layer or even Wrap being affected by ZOrder at
		all. The geometry, position and mode of the Wrap remains unchanged.
		This method will re-evaluate the Wrap relative to the effective ZOrder
		of the Parcel if required.
		@param key
		@param sodRef TextWrapRef of the wrap that has been affected.
		@param zOrderBasedWrap
		@param sodLayerVisible
		@param sodLayerIgnoreWhenHidden
		@param sodDocLayer
		*/
		virtual void		NotifyParcelWrapZOrderChanged(ParcelKey key,
											const TextWrapRef& sodRef,
											bool16 zOrderBasedWrap,
											const IDocumentLayer* sodDocLayer) = 0;

		/**
		The specified active Wrap affecting the specified Parcel has changed
		the SkipByLeading option. This method will damage the appropriate text
		within the Parcel as required.
		@param key
		@param sodRef TextWrapRef of the wrap that has been affected.
		*/
		virtual void		NotifyParcelWrapSkipByLeadingChanged(ParcelKey key,
											const TextWrapRef& sodRef) = 0;

		/**
		The specified active Wrap affecting the specified Parcel has changed
		either IStandOff::Mode from one BBox mode to another (such as
		kBoundingBox to kBand) or the IStandOff::Side. These changes do not
		result in a change to the PathGeometry of the Wrap but it will affect
		how Text will compose around the Wrap. This method will damage the
		appropriate text within the Parcel as required.
		@param key
		@param sodRef TextWrapRef of the wrap that has been affected.
		*/
		virtual void		NotifyParcelWrapNonGeometryChanged(ParcelKey key,
											const TextWrapRef& sodRef) = 0;

		/**
		The specified Wrap is removed from the specified Parcel. If the wrap
		is known to the Parcel then this method will damage Text that was
		overlapped by the wrap. The IStandOffParcelUsedList on the same boss
		as the IStandOffData will be called to unregister the Parcel.
		@param key
		@param sod Pointer to IStandOffData interface for the wrap
		@param xOffset XOffset that the specified Parcel knows the StandOff by
		@param yOffset YOffset that the specified Parcel knows the StandOff by
		*/
		virtual void		RemoveParcelWrap(ParcelKey key,
											const TextWrapRef& sodRef) = 0;

		/**
		This method manages the process of asking the IParagraphComposer
		to rebuild the specified WaxLine to fit. This main caller of this
		method is the private method IWaxLine::BuildRuns().
		@param Pointer to ITextStoryThread of the WaxLine
		@param Pointer to IParcelList of this ITextParcelList
		@param waxLine Pointer to IWaxLine that needs WaxRuns to build
		@return kTrue if the WaxLine successfully built it's runs.
		*/
		virtual bool16		RebuildWaxLine(const ITextStoryThread* thread,
											const IParcelList* pl,
											IWaxLine* waxLine) const = 0;

		/**
		Parcels which compose complex content, such as Tables and Footnotes,
		which themselves manage TextStoryThreads in the same TextModel as this
		TextParcelList can be overset without this TextParcelList itself being
		overset.
		@param key
		@return kTrue if the Parcel contains any complex content which is overset.
		*/
		virtual bool16		GetParcelContainsOversetContent(ParcelKey key) const = 0;

		/**
		The story direction (returned by GetIsVertical()) of this StoryThread
		has changed.
		*/
		virtual void		NotifyStoryDirectionChanged() = 0;

		/**
		This method tells callers if the TextParcelList is currently composing
		any Parcels within the list.
		@return ParcelKey of the Parcel being currently composed. Will return an invalid ParcelKey is not composing.
		*/
		virtual ParcelKey	GetParcelComposing() const = 0;

		/**
		*/
		virtual Text::VerticalJustification GetComposingVerticalJustification() const = 0;

		/**
		*/
		virtual bool16 CanBackDamageContainer() const = 0;

		/**
		Iterators.
		*/
		class const_iterator
		{
		public:
			typedef ParcelKey						value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef const ParcelKey*				pointer;
			typedef const ParcelKey&				reference;
			typedef std::bidirectional_iterator_tag	iterator_category;

			friend class TextParcelList;
			friend class const_reverse_iterator;

			const_iterator(const const_iterator& copy)
				{
				ASSERT(copy.fData);
				fData.reset(copy.fData);
				fData->AddRef();
				fKey = copy.fKey;
				fKeyState = copy.fKeyState;
				}

			~const_iterator()
				{ }

			const ParcelKey&		operator*() const
				{ return fKey; }

			const ParcelKey*		operator->() const
				{ return &fKey; }

			const_iterator&			operator=(const const_iterator& rhs)
				{
				if (this != &rhs)
				{
					ASSERT(rhs.fData);
					fData.reset(rhs.fData);
					fData->AddRef();
					fKey = rhs.fKey;
					fKeyState = rhs.fKeyState;
				}
				return *this;
				}

			const_iterator&			operator++()
				{
				if (fKeyState == -1)
				{
					fKey = fData->GetFirstLogicalParcelKey();

					if(!fKey.IsValid())
					{
						fKeyState = 1;
					} else {
						fKeyState = 0;
					}
				}
				else if (fKeyState == 0)
				{
					fKey = fData->GetNextLogicalParcelKey(fKey);

					if(!fKey.IsValid())
					{
						fKeyState = 1;
					}
				}
				else
				{
					ASSERT(fKeyState == 1);
					ASSERT_FAIL("ITextParcelList::const_iterator ++ past end");
				}
				return *this;
				}

			const_iterator			operator++(int)
				{
				const_iterator tmp = *this;
				if (fKeyState == -1)
				{
					fKey = fData->GetFirstLogicalParcelKey();

					if(!fKey.IsValid())
					{
						fKeyState = 1;
					} else {
						fKeyState = 0;
					}
				}
				else if (fKeyState == 0)
				{
					fKey = fData->GetNextLogicalParcelKey(fKey);

					if(!fKey.IsValid())
					{
						fKeyState = 1;
					}
				}
				else
				{
					ASSERT(fKeyState == 1);
					ASSERT_FAIL("ITextParcelList::const_iterator ++ past end");
				}
				return tmp;
				}

			const_iterator&			operator--()
				{
				if (fKeyState == -1)
				{
					ASSERT_FAIL("ITextParcelList::const_iterator -- before begin");
				}
				else if (fKeyState == 0)
				{
					fKey = fData->GetPreviousLogicalParcelKey(fKey);

					if(!fKey.IsValid())
					{
						fKeyState = -1;
					}
				}
				else
				{
					ASSERT(fKeyState == 1);
					fKey = fData->GetLastLogicalParcelKey();

					if(!fKey.IsValid())
					{
						fKeyState = -1;
					} else {
						fKeyState = 0;
					}
				}
				return *this;
				}

			const_iterator			operator--(int)
				{
				const_iterator tmp = *this;
				if (fKeyState == -1)
				{
					ASSERT_FAIL("ITextParcelList::const_iterator -- before begin");
				}
				else if (fKeyState == 0)
				{
					fKey = fData->GetPreviousLogicalParcelKey(fKey);

					if(!fKey.IsValid())
					{
						fKeyState = -1;
					}
				}
				else
				{
					ASSERT(fKeyState == 1);
					fKey = fData->GetLastLogicalParcelKey();

					if(!fKey.IsValid())
					{
						fKeyState = -1;
					} else {
						fKeyState = 0;
					}
				}
				return tmp;
				}

			bool16					operator==(const const_iterator& rhs) const
				{
				return ((fData == rhs.fData) &&
						(fKey == rhs.fKey) &&
						(fKeyState == rhs.fKeyState));
				}

			bool16					operator!=(const const_iterator& rhs) const
				{ return !(*this == rhs); }

		protected:
			const_iterator(const ITextParcelListData* data,
							ParcelKey key,
							int32 keyState) :	// -1 key invalid, before begin
												//  0 key valid, within range
												//  1 key invalid, after end
				fData(data), fKey(key), fKeyState(keyState)
				{
					// Force the ref count to be increased, the initializer
					// is calling the InterfacePtr(IFace*) constructor which
					// doesn't AddRef(). I guess the compiler considers it the
					// best match even though the constness is gone.
					if(fData)
					{
						fData->AddRef();
					}
				ASSERT(((keyState == -1) && (!key.IsValid())) ||
					   ((keyState == 0) && (key.IsValid())) ||
					   ((keyState == 1) && (!key.IsValid())));
				}

			InterfacePtr<const ITextParcelListData>	fData;
			ParcelKey								fKey;
			int32									fKeyState;
		};

		class const_reverse_iterator
		{
		public:
			typedef ParcelKey						value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef const ParcelKey*				pointer;
			typedef const ParcelKey&				reference;
			typedef std::bidirectional_iterator_tag	iterator_category;

			friend class TextParcelList;

			const_reverse_iterator(const const_reverse_iterator& copy) :
				fIter(copy.fIter)
				{ }

			const ParcelKey&		operator*() const
				{ return fIter.operator*(); }

			const ParcelKey*		operator->() const
				{ return fIter.operator->(); }

			const_reverse_iterator&	operator=(const const_reverse_iterator& rhs)
				{ this->fIter = rhs.fIter; return *this; }

			const_reverse_iterator&	operator++()
				{ --fIter; return *this; }

			const_reverse_iterator	operator++(int)
				{
				const_reverse_iterator tmp = *this;
				++fIter;
				return tmp;
				}

			const_reverse_iterator&	operator--()
				{ ++fIter; return *this; }

			const_reverse_iterator	operator--(int)
				{
				const_reverse_iterator tmp = *this;
				--fIter;
				return tmp;
				}

			bool16					operator==(const const_reverse_iterator& rhs) const
				{ return (this->fIter == rhs.fIter); }

			bool16					operator!=(const const_reverse_iterator& rhs)
				{ return !(*this == rhs); }

		protected:
			const_reverse_iterator(const ITextParcelListData* data,
									ParcelKey key, int32 keyState) :
				fIter(data, key, keyState)
				{ }

			const_iterator	fIter;
		};

		virtual ContainerComposer* GetCompositionContext() const = 0;
};

#endif	// __ITextParcelList__


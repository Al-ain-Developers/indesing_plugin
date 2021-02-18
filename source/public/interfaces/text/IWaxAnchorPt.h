//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWaxAnchorPt.h $
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
#ifndef __IWaxAnchorPt__
#define __IWaxAnchorPt__

#include "IPMUnknown.h"
#include "TextID.h"
#include "CTextEnum.h"
#include "IParagraphComposer.h"
#include "PMMatrix.h"
#include "PMPoint.h"
#include "PMRect.h"
#include "DrawPassInfo.h"
#include "PMTextUtils.h"
#include "ParcelKey.h"
#include "OwnedItemDataList.h"

class ICallback;
class IParcel;
class GraphicsData;
class IComposeScanner;
class IWaxLine;


/** 
	@ingroup text_wax
*/
class IWaxAnchorPt : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IWAXANCHORPT };

	///
	enum NextAnchorInfo {
		/// The next WaxLine does NOT contain an Anchor which is related to this Anchor. If the position of this Anchor changes relative to its original location then the next WaxLine will be damaged.
		nai_notcontinued,
		/// The next WaxLine contains an Anchor which is related to this Anchor. The next WaxLine will not be damaged.
		nai_continued
	};

	/**
	The owning UID of the Anchored rectangle is being asked to re-compose
	itself starting in the specified parcel and yPosition.
	@param tpl Pointer to ITextParcelList being composed
	@param tiler Pointer to IParagraphComposer::Tiler managing the geometry
	@param lineStartIndex
	@param anchorPtIndex
	@param tiler
	@param parcelKey
	@param yPosition
	@param waxLineDamage
	@param firstWaxLineInParcel Set to kTrue if the new WaxLine will be the first WaxLine in the specified StartingParcel OR it is part of a keeps/dropcap block that has its top WaxLine as the first in the specified StartingParcel.
	@param waxLinePartOfKeepsBlock Set to kTrue if the new WaxLine is to be kept with a previous WaxLine due to KeepWithNext or KeepWithFirstN or KeepTogether. 
	This can only be kTrue for the first WaxAnchorPt of a multiple WaxAnchorPt set.
	The callee is expected to compute a value for GetTopKeepsContentBottom(). If
	the damage situation is such that the original value is known to be valid
	then it does not have to recompute it.

	If the method returns kTrue then the callee must return ALL the following
	out parameters except for pDamagePreviousWaxLine:
	@param pParcelKey The parcel key of the Anchor rectangle
	@param pBBox The bounding box, in Parcel coordinates. These are not necessarily the inkBounds of the object, just the raw dimensions of the object as if the object was a part of Text. The YPosition of the Anchoring WaxLine will be set to the bottom of the rect, the LineHeight will be set to the height of the rect and the Width will be set to the width of the rect.
	@param pSpaceAfter The BBox. Can be negative. The WaxAnchorComposer will adjust the YPosition of the WaxLine by this amount while maintaining the position of the BBox.
	@param pHasBreak Set to kTrue if some Break (Column, Frame, Page, etc) in effect for this WaxAnchorPt AND this WaxAnchorPt is the ONLY or the FIRST, in the event it is part of a series of related WaxAnchorPts.
	@param pTextSpan The number of Anchor points (span) mapped (>=1).
	@param pDamagePrevousWaxLine Set to kTrue if the previous WaxLine should be damaged after completing processing for this Anchor. Requires that the previous WaxLine be related to this Anchor. This value must always be set.
	@param pNextAnchorInfo Set to nai_notcontinued if no Anchors related to this one follow this Anchor.
	@param pDamageFollowingNthChars Specifies the number of characters after (anchorPtIndex + pTextSpan) that should be content damaged after this Anchor is processed. pNextAnchorInfo must be set to nai_continued and the affected characters must be owned by the Anchor. Only needs to be set if the Anchor composed.
	@param pDeferredCompositionDueToKeeps If waxLinePartOfKeepsBlock is kTrue, then this should be set to kTrue if partial composition was done to faciliate keeps computation, kFalse otherwise.
	@return kTrue if the Anchor composed, kFalse otherwise.
	*/
	enum waxLineDamageType
	{
		kWLDT_Other		= 0,	// other (destroyed, geometry, etc)
		kWLDT_Keeps		= 1,	// "keeps" damaged
		kWLDT_Content	= 2		// "content" damaged
	};

	virtual bool16		Recompose(const ITextParcelList* tpl,
								const IParagraphComposer::Tiler* tiler,
								TextIndex lineStartIndex,
								TextIndex anchorPtIndex,
								ParcelKey parcelKey,
								PMReal yPosition,
								waxLineDamageType waxLineDamage,
								bool16 firstWaxLineInParcel,
								bool16 waxLinePartOfKeepsBlock,
								ParcelKey* pParcelKey,
								PMRect* pBBox,		// in content (Wax) coord.
								PMReal* pSpaceAfter,
								bool16* pHasBreak,
								int32* pTextSpan,
								bool16* pDamagePreviousWaxLine,
								NextAnchorInfo* pNextAnchorInfo,
								int32* pDamageFollowingNChars,
								bool16* pDeferredCompositionDueToKeeps,
								TextIndex noDamageBackTextIndex = -1) = 0;

	/**
	Similar to Recompose() but instead the WaxAnchor is notified that it
	is being moved within the same Parcel. This is used during Vertical
	Justification processing of the Parcel.
	@param anchorPtIndex
	@param tiler
	@param parcelKey
	@param yPosition
	@param yPosDelta
	*/
	virtual void		Move(TextIndex anchorPtIndex,
							IParcelList* pl,
							ParcelKey parcelKey,
							PMReal yPosition,
							PMReal yPosDelta) = 0;


	// GetInkBounds()		Returned bounds are in Wax coordinates.
	// GetDrawPassInfo()

	/**
	Returns the stroke bounding box in Wax coordinates of the Anchor. The value returned should be the same as returned by Recompose().
	@param pBBox 
	*/
	virtual void		GetBBox(PMRect* pBBox) const = 0;

	/**
	Returns the number of characters that are controlled by this Anchor.
	*/
	virtual int32		GetTextSpan() const = 0;

	/**
	Returns the ink bounds in Wax coordinates of the Anchor.
	@param inkBounds 
	*/
	virtual void		GetInkBounds(PMRect* inkBounds) const = 0;

	/**
	Returns the DrawPassInfo for the Anchor.
	@param passList 
	*/
	virtual void		GetDrawPassInfo(Text::DrawPassInfoList *passList) const = 0;

	/**
	IParcelShape calls this method as part of a IShape::IterateDrawOrder()
	sequence.
	@param xform
	@param callbackInfo
	@param iShapeFlags
	*/
	virtual void		IterateWaxAnchorPointDrawOrder(const PMMatrix* xform,
										ICallback* callbackInfo,
										int32 iShapeFlags) = 0;

	/**
	Draw the anchor.
	@param gd
	@param iShapeFlags
	@param pass
	@param xOffset The left edge of the Anchor BBox in drawing container coordintes.
	@param yOffset The bottom edge of the Anchor BBox in drawing container coordintes.
	@param areaToDraw
	@see IWaxRunText
	*/
	virtual void		Draw(GraphicsData* gd, int32 iShapeFlags,
							 	Text::DrawPassInfo::Pass pass,
								const PMReal& xOffset, const PMReal& yOffset,
								const PMRect* areaToDraw) = 0;

	/**
	Returns kTrue if the WaxAnchorPt contains any content which is dependent
	on the position of the Parcel relative to the Pasteboard. WaxAnchorPts must
	return kTrue for this method to guarantee that they will be called via
	MarkMoveDamage() when the containing Parcel is moved.
	*/
	virtual bool16		GetIsParcelPositionDependent() const = 0;

	/**
	Text Keeps has included the bottom edge of this WaxAnchorPt and the top of
	the effective Text Keeps block ends in this WaxAnchorPt without including
	the top edge of this WaxAnchorPt.

	This later criteria is important because this method will not be called if
	the containing Paragraph has keep all lines together as that will, if
	effective, force the entire WaxAnchorPt to be out of the Parcel and that
	will be handled by the Text Keeps processing without calling this method.
	*/
	virtual void		MarkKeepsDamageFromText() = 0;

	/**
	Damage for backup damage the top of the keeps block in this WaxAnchorPt.
	@param paraHasKeepAllLines kTrue if the anchoring Paragraph has Keep All Lines Together set. This will be used by the callee so that it will backup to the very top of the multi-WaxAnchorPt set (topOfKeepsBlockNotTopOfWAPSet will be kFalse, keepBlockAtTopContaining will be kTrue) unless the internal object as an effective text break. 
	@return kTrue if damage was marked, kFalse otherwise.
	*/
	virtual bool16		MarkExtendedDamageFromTextKeeps(bool16 paraHasKeepAllLines) = 0;

	/**
	Given a point in Wax coordinates, return the TextIndex of
	the closest character/glyph in this WaxAnchorPt.
	@param waxPt
	@param nextLine The TextIndex of the end of the WaxLine (which is the st
	art of the next WaxLine
	@return The TextIndex of the closest character/glyph or kInvalidTextIndex if no hit is made.
	*/
	virtual PMReal		HitTest(const PMPoint& waxPt,
								TextIndex* nextLine) const = 0;

	/**
	Returns the list of owned items associated with this WaxAnchorPt. Although
	this list is being collect from a composition component, it is NOT assumed
	that the WaxAnchorPt is fully composed. Those OwnedItems that are known to
	be part of the composition range because they are part of a Parcel that has
	an existing span, regardless of damage state, should be returned. Do not
	return overset.
	@param resultList Append to the list.
	*/
	virtual void		CollectOwnedItems(OwnedItemDataList* rList) const = 0;

	/**
	This method is called during Parcel composition to determine what the
	minimum content bottom for the WaxAnchorPt is. When the WaxAnchorPt is
	part of a keeps block then the previous non-WaxAnchorPt WaxLine wants to
	be kept with the top of whatever minimum sub-divisible part of the
	WaxAnchorPt can be composed. It is the responsibility of the WaxAnchorPt
	to compute this value whenever the components which would affect this value
	change. In addition, when the WaxAnchorPt grows by the inclusion of
	additional components the value returned must not change.
	*/
	virtual PMReal		GetTopKeepsContentBottom(const IWaxLine* waxLine) const = 0;

	/**
	After recomposing the WaxAnchorPt in the context of a deferred keeps
	situation - that is waxLinePartOfKeepsBlock was set to kTrue, this method
	will be called by the Parcel Composer to give the WaxAnchorPt the
	opportunity to damage the WaxAnchorPt appropriately in order to try pull
	up content in a later WaxAnchorPt thay may have been pushed there due to
	the need to compute TopKeepsContentBottom. If the WaxAnchorPt does not have
	multiple composable pieces or it already has composed more than the minimum
	required for keeps it is free to do nothing and return kFalse.
	@return kTrue if the WaxAnchorPt damaged the anchoring WaxLine. Note that
	because this method is called during composition the callee should only
	damage the anchoring WaxLine and should not damage any other WaxLines or
	Parcels.
	*/
	virtual bool16		NotifyComposedPartOfKeepsBlock(IWaxLine* waxLine) = 0;

	/**
	The WaxAnchorPt should mark the appropriate damage internally and on its
	anchoring WaxLine to force recomposition, however this damage should not
	result in damaging a previous WaxAnchorPt (if it is related to the callee)
	or a previous Parcel. Furthermore, the callee is not responsible for
	damaging the containing Parcel.
	@param topYIntersect The YPosition, in Wax coordinate system, that the WaxAnchorPt should damage relative to. This value will be less than equal to the WaxLine YPosition but it may be higher than the Line Height of the WaxLine.
	@return kTrue if the "top" of the WaxAnchorPt was damaged by this call. When this occurs the CompositionIter will mark the WaxLine keeps damaged.
	*/
	virtual bool16		MarkCompositionDamage(IWaxLine* waxLine,
												PMReal topYIntersect) = 0;	

	/**
	Returns kTrue if this WaxAnchorPt could be composed into multiple pieces.
	This method helps the Text Keeps processing system understand if this
	WaxAnchorPt is or could be part of a contiguous multi-piece set.
	@return kTrue if this WaxAnchorPt is divisible
	*/
	virtual bool16		GetIsDivisible() const = 0;

	/**
	Text Keeps processing understands that WaxAnchorPts may represent a single
	conceptual object managed by one or more contiguous WaxAnchorPts. This
	represents a challenge when trying to establish what can be treated as a
	single WaxLine and what cannot.

	This method allows the Text Keeps Processing to know if the keeps flags on
	the WaxLine containing the WaxAnchorPt can used.

	For middle or last WaxAnchorPts of a set those flags can never be used.

	@param pHasTopBreak If method returns kTrue, then this pointer will be set to kTrue if the top of the WaxAnchorPt has an effective text break, kFalse otherwise.
	@return kTrue if this WaxAnchorPt is the only WaxAnchorPt, or is the top/first WaxAnchorPt of a multi-piece set, kFalse otherwise.
	*/
	virtual bool16		GetIsOnlyOrFirstOfASet(bool16* pHasTopBreak) const = 0;

	/**
	This method will be called by the Parcel Composer for the first WaxLine
	composed off the end of the Parcel which contains a WaxAnchorPt.

	The Text Keeps processor will first call GetIsOnlyOrFirstOfASet() and if
	that returns kFalse, then it knows that the keeps flags on the WaxLine
	cannot be relied upon and therefore it will call this method.

	This method should return kTrue if for any reason there is any internal
	keeps relationship between the top of this WaxAnchorPt and the previous
	WaxAnchorPt, which will be in the same set.

	If not, or there is a internal effective keeps break, then this method
	should return kFalse.

	@param paraHasKeepAllLines kTrue if the anchoring Paragraph has Keep All Lines Together set.
	@return kTrue if there is an internal keeps relationship between the top of this Wax WaxAnchorPt and the previous one, which will be in the same set, kFalse otherwise.
	*/
	virtual bool16		GetTextKeepsViolation(bool16 paraHasKeepAllLines) const = 0;

	/**
	This method is used by the Text Keeps processing on a WaxAnchorPt which may
	or may not have been already damaged either internally or by the WaxLine it
	is on.

	When undamaged it will be because it just finished composing the Parcel and
	this is the first non-first WaxAnchorPt of a multi-piece set and it wants
	to get the top of the keeps block.

	Through a previous call to GetTextKeepsViolation() it knows that this
	WaxAnchorPt is not the first part of a multi-piece set and the top edge of
	the WaxAnchorPt wants to be kept with the bottom edge of the WaxAnchorPt
	composed on the previous WaxLine.

	When damaged it will be because we have geometry damaged the WaxLine
	containing this WaxAnchorPt and because we know that it is not the first
	of a set we want to extend the damage through keeps of the WaxAnchorPt
	ABOVE this WaxAnchorPt.

	Either way the callee is asked to start with this keep relationship and
	backup the keeps relationship chain towards the first WaxAnchorPt in the
	set.

	Note that in practice we expect that the returned values will indicate the
	very top, rather than an internal value, of previous WaxAnchorPt because
	the WaxAnchorPt is expected to be responsible for internal keeps and the
	only reason it would create a keeps violation between internal edges is
	if by doing so it was to leave the Parcel empty.

	@param paraHasKeepAllLines kTrue if the anchoring Paragraph has Keep All Lines Together set. This will be used by the callee so that it will backup to the very top of the multi-WaxAnchorPt set (topOfKeepsBlockNotTopOfWAPSet will be kFalse, keepBlockAtTopContaining will be kTrue) unless the internal object as an effective text break. 
	@param topOfKeepsBlockNotTopOfWAPSet Returned kTrue if the object can be considered divisible - that is the top of the keeps block beginning at the bottom of the object ends before the top of the object mapped by one or more WaxAnchorPt, even though the top of the object might be in an earlier WaxAnchorPt. kFalse if the entire object can be considered one whole keeps block, even though the top of the object might be in an earlier WaxAnchorPt. This latter is important because it tells the Text Keeps processing system whether it needs to continue the keeps backup using the WaxLine keeps flags on the top WaxAnchorPt.
	@param keepsBlockAtTopOfContainingWAP Returned kTrue if the top of the keeps block is also the top of the WaxAnchorPt that contains it. If topOfKeepsBlockNotTopOfWAPSet is kFalse, then this value must be kTrue.
	@param keepsBlockHasTopBreak Set to kTrue if the top of the keeps block has an effective text break. This will only be interesting to the Text Keeps processing if the keeps block starts at the top of the WaxAnchorPt (so topOfKeepsBlockNotTopOfWAPSet is set to kFalse, and keepsBlockAtTopOfContaining set to kTrue).
	@param keepsBlockDamaged Set to kTrue if any of the internal abstracted Keeps range between the PREVIOUS multi-piece WaxAnchor and the top of the internal Keeps range has already been damaged. NOTE: The WaxAnchorPt COULD already be damaged and this damage flag does NOT apply to that damage.
	@return The TextIndex of the WaxAnchoredPt which controls the top of the keeps block, which will either be THIS WaxAnchorPt or an ealier one if a multi-piece WaxAnchorPt.
	*/
	virtual TextIndex		BackupToStartOfKeepsFromTop(bool16 paraHasKeepAllLines,
										bool16& topOfKeepsBlockNotTopOfWAPSet,
										bool16& keepsBlockAtTopOfContainingWAP,
										bool16& keepsBlockHasTopBreak,
										bool16& keepsBlockDamaged) const = 0;

	/**
	This method by the Text Keeps processing when it is backing up to the start
	of the Text Keeps block and it encounters a WaxAnchorPt that the next
	WaxLine would like to be kept with.

	By definition this WaxAnchorPt will be the only, or last of a multi-piece
	set.

	The callee needs to indicate how this Text Keep thread flows through the
	WaxAnchorPt - by definition the WaxLine below the WaxAnchorPt is trying to
	keep with the bottom edge but if there is internal keeps relationships that
	stretch from this bottom edge then this is the Keeps block that we are
	interested in.
	
	@param paraHasKeepAllLines kTrue if the anchoring Paragraph has Keep All Lines Together set. This will be used by the callee so that it will backup to the very top of the multi-WaxAnchorPt set (topOfKeepsBlockNotTopOfWAPSet will be kFalse, keepBlockAtTopContaining will be kTrue) unless the internal object as an effective text break. 
	@param topOfKeepsBlockNotTopOfWAPSet Returned kTrue if the object can be considered divisible - that is the top of the keeps block beginning at the bottom of the object ends before the top of the object mapped by one or more WaxAnchorPt, even though the top of the object might be in an earlier WaxAnchorPt. kFalse if the entire object can be considered one whole keeps block, even though the top of the object might be in an earlier WaxAnchorPt. This latter is important because it tells the Text Keeps processing system whether it needs to continue the keeps backup using the WaxLine keeps flags on the top WaxAnchorPt.
	@param keepsBlockAtTopOfContainingWAP Returned kTrue if the top of the keeps block is also the top of the WaxAnchorPt that contains it. If topOfKeepsBlockNotTopOfWAPSet is kFalse, then this value must be kTrue.
	@param keepsBlockHasTopBreak Returned kTrue if the top of the keeps block has an effective text break. This will only be interesting to the Text Keeps processing if the keeps block starts at the top of the WaxAnchorPt (so topOfKeepsBlockNotTopOfWAPSet is set to kFalse, and keepsBlockAtTopOfContaining set to kTrue).
	@param keepsBlockDamaged Returned kTrue if any of the internal abstracted Keeps range between the LAST multi-piece WaxAnchor and the top of the internal Keeps range has already been damaged.
	@return The TextIndex of the WaxAnchoredPt which controls the top of the keeps block, which will either be THIS WaxAnchorPt or an ealier one if a multi-piece WaxAnchorPt.
	*/
	virtual TextIndex		BackupToStartOfKeepsFromBottom(bool16 paraHasKeepAllLines,
										bool16& topOfKeepsBlockNotTopOfWAPSet,
										bool16& keepsBlockAtTopOfContainingWAP,
										bool16& keepsBlockHasTopBreak,
										bool16& keepsBlockDamaged) const = 0;

	/**
	This method is called during composition of the WaxAnchorPt when Tiling
	occurs.
	Returns kTrue if the WaxAnchorPt is composing the "top" of the WaxAnchorPt, False otherwise.
	*/
	virtual bool16		GetIsCompositionExtending() const = 0;

	/**
	The WaxAnchorPt is notified that the Parcel it is composed into has been
	moved. If the WaxAnchorPt manages any StoryThreads then this notification
	must be passed through to any Parcels associated with this IWaxAnchorPt.
	Note that the IWaxLine managed by the IWaxAnchorPt is NOT damaged by the
	caller and that the OwnedItem API of the IWaxAnchorPt is also notified
	via the IOwnedItem::ParcelMoved() method.
	*/
	virtual void		MarkParcelMoveDamage() = 0;

	/**
	The WaxAnchorPt is notified that a Parcel Previous to the Parcel containing
	this WaxAnchorPt has been moved AND the WaxLine containing this WaxAnchorPt
	is the first WaxLine after the Parcel that moved.
	If the composition of this WaxAnchorPt is dependent on the Page position
	of the Parcel then it will need to do the appropriate damage to trigger
	recomposition.
	*/
	virtual void		MarkPreviousParcelMoveDamage() = 0;

	/**
	The WaxAnchorPt is notified that the Parcel it is composed into has been
	damaged because one or more Text Alignment Grids have changed. This
	notification needs to be forwarded to any dependent content which may have
	been aligned to these grids.
	*/
	virtual void		MarkParcelGridDamage() = 0;

	/**
	The WaxAnchorPt is notified that a Parcel Previous to the Parcel it is
	composed into has been damaged because one or more Text Alignment Grids
	have changed. This notification needs to be forwarded to any dependent
	content which may have been aligned to these grids.
	*/
	virtual void		MarkPreviousParcelGridDamage() = 0;
};

#endif

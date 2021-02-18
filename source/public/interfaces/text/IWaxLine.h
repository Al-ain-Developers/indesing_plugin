//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWaxLine.h $
//  
//  Owner: zwilliam
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
#ifndef __IWaxLine__
#define __IWaxLine__

#include "IPMUnknown.h"
#include "TextID.h"
#include "CTextEnum.h"
#include "IDrawingStyle.h"
#include "ParcelKey.h"

class VOS_Object;
class IWaxRun;
class PMRect;
class IFrameList;
class IParcelList;
class IWaxStrand;
class IWaxRunIterator;
class IWaxGlyphIterator;
class PMMatrix;
class ITextStoryThread;
class ITextModel;


/** This interface manages the hierarchy for the wax-line. It also stores the position of the
	line and many other properties such as leading.
	@ingroup text_wax
*/
class IWaxLine : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_IWAXLINE };

		enum LineTightness { kUnknown, kVeryLoose, kLoose, kNormal, kTight, kVeryTight,
							kTooLoose_Obsolete, kTooTight_Obsolete };

		enum { kMaximumTilesPerLine = 32 };		// created by textwrap, warichuu, dropcap

	/** SetVOSWaxObject is for internal initialization only.
	*/
	virtual void SetVOSWaxObject(VOS_Object * vosObject) = 0;
	/** get pointer to vos object that owns this line. Generally internal use only.
	*/
	virtual VOS_Object * GetVOSWaxObject() const = 0;

	/** Hierarchy: this WaxLine is inside the parcel specified: overset == !ParcelKey.IsValid()
	*/
	virtual ParcelKey GetParcelKey() const = 0;
	virtual void SetParcelKey(ParcelKey parcelKey) = 0;

	virtual IWaxRun* QueryRun(int32 index) const = 0;
	virtual int32 GetRunIndex(const IWaxRun * run) const = 0;
	virtual int32 GetRunCount() const = 0;
	/** Are the IWaxRuns for this line already built?
	*/
	virtual bool16 DoWaxRunsExist() const = 0;

	/** Does this IWaxRun start the line?
	*/
	virtual bool16 StartsLine(const IWaxRun* waxRun) const = 0;
	/** Does this IWaxRun end the line?
	*/
	virtual bool16 EndsLine(const IWaxRun* waxRun) const = 0;

	/** QueryWaxGlyphIterator provides iteration through all the glyphs in this waxLine.
		It may not visit every run, since not all runs contain glyphs.
		if includeLine is true, then the Matrix will include the line's transform (thereby converting to parcel coordinates)
	*/
	virtual IWaxGlyphIterator* QueryWaxGlyphIterator(bool16 includeLine = kFalse) const = 0;

	/** QueryWaxRunIterator only iterates the leaf waxRuns - basically it just hides the wax
		hierarchy, providing access to the glyphs (or other "drawn" data).
		if includeLine is true, then the Matrix will include the line's transform (thereby converting to parcel coordinates)
	*/
	virtual IWaxRunIterator* QueryWaxRunIterator(bool16 includeLine = kFalse) const = 0;

	/** QueryRunByTextOffset returns the WaxRun that contains the specified textOffset in the WaxLine.
		pGlyphOffset will be set to the offset within the run to the specified glyph (it can be expensive to generate this).
		NOTE: not all runs have glyphs, so it's possible that *pGlyphOffset will come back invalid (e.g. as -1)
	*/
	virtual IWaxRun * QueryRunByTextOffset(int32 textOffset, int32* pGlyphOffset = nil) const = 0;

	/** sets LISTS of dropcap indents
	*/
	virtual void SetDropCapIndents(int32 howManyIndents, const PMReal* indents, const int32* lineCounts) = 0;
	/** returns number of indents, will copy them if the pointers are non-nil
	*/
	virtual int32 GetDropCapIndents(PMReal* indents = nil, int32* lineCounts = nil) const = 0;
	/** n too big == last one, n too small == 0 --- this allows shortcuts
	*/
	virtual PMReal GetNthDropCapIndent(int32 n) const = 0;
	/** return kTrue if the next line following this one will be affected by a dropcap.
	*/
	virtual bool16 GetNextLineAffectedByDropcap() const = 0;

	/** Returns the database containing this wax
	*/
	virtual IDataBase * GetDataBase() const = 0;

	/** Range of characters in the text model mapped to this wax.
		Note: The wax span and model span differ when the text model
		has been altered but the wax has not been fully recomposed.
	*/
	virtual int32 GetTextSpan() const = 0;

	virtual int32 GetTextSpanInTile(int32 tileNum) const = 0;
	virtual void SetTextSpanInTile(int32 span, int32 tileNum = 0) = 0;

	/**
	Unjustified Text Width is the width of the Text calculated by the composer
	in order to fit within the tile. So the difference between this value and
	the target width of the tile is the amount of space that the composer will
	fill up by justifying the text in the tile.
	If the return value is zero then the composer did not set a value (older
	documents).
	*/
	virtual PMReal GetUnjustifiedTextWidthInTile(int32 tileNum) const = 0;
	virtual void SetUnjustifiedTextWidthInTile(PMReal unJTW, int32 tileNum = 0) = 0;

	/**
	Justified Width is the width to justify the text. In most cases this value is 0
	and should be ignored. In the case of kashida justification the last line can be
	stretched to match the rest of the lines in the paragraph.
	*/
	virtual PMReal GetJustifiedTextWidthInTile(int32 tileNum) const = 0;
	virtual void SetJustifiedTextWidthInTile(PMReal justWidth, int32 tileNum = 0) = 0;

	/** Finds the run within the line and returns it's first TextIndex.
		Passing nil returns the first TextIndex of the line.
	*/
	virtual TextIndex TextOrigin(const IWaxRun * waxRun = nil) const = 0;

	virtual PMReal GetYAdvance() const = 0;

	virtual int32 GetNumberOfTiles() const = 0;
	virtual void SetNumberOfTiles(int32 numTiles) = 0;

	/** x position of each tile. first tile is the line's x position
	*/
	virtual PMReal GetXPosition(int32 tileNum = 0) const = 0;
	virtual void SetXPosition(PMReal xPosition, int32 tileNum = 0) = 0;

	/** y-position of bottom of line height
	*/
	virtual PMReal GetYPosition() const = 0;

	/** The WaxLine exists in its own zero-based coordinate system. These
		matrices will handle the transformations between the various target
		coordinate systems:
		Returns a matrix which will transform a WaxLine relative coordinate to
		the Parcel "content" coordinate system, a.k.a. the "Wax" coordinate
		system, of the Parcel that the WaxLine is in.
	*/
	virtual PMMatrix GetTransform() const = 0;

	/** Returns a matrix which will transform a WaxLine relative coordinate to
		the Parcel coordinate system of the Parcel that the WaxLine is in.
	*/
	virtual PMMatrix GetToParcelMatrix() const = 0;

	/** Returns a matrix which will transform a WaxLine relative coordinate to
		the Frame coordinate system of the Frame that the WaxLine is in.
	*/
	virtual PMMatrix GetToFrameMatrix() const = 0;

	/** Returns a matrix which will transform a WaxLine relative coordinate to
		the Spread coordinate system.
	*/
	virtual PMMatrix GetToSpreadMatrix() const = 0;

	/** Returns a matrix which will transform a WaxLine relative coordinate to
		the Pasteboard coordinate system.
	*/
	virtual PMMatrix GetToPasteboardMatrix() const = 0;

	virtual PMReal GetLineHeight() const = 0;
	virtual void SetLineHeight(PMReal lineHeight) = 0;

	/** The LeadingModel determines how line leading is measured from line to line
		and thereby how lines are placed in the frame
	*/
	virtual Text::LeadingModel GetLeadingModel() const = 0;
	virtual void SetLeadingModel(Text::LeadingModel m) = 0;

	/** This is the difference of the LineHeight and the max Leading value in the line.
	*/
	virtual PMReal GetLineHeightLeadingDiff() const = 0;
	virtual void SetLineHeightLeadingDiff(PMReal lineHeight) = 0;

	/** This is the offset into the LineHeight to the point from which line leading is to be measured
		0.0 means measure leading from the line's yPosition.
	*/
	virtual PMReal GetLeadingModelOffset() const = 0;
	virtual void SetLeadingModelOffset(PMReal offset) = 0;

	/** If ignoreAllTrailing is True the width will not include the width of white
		space or non selectable glyphs. */
	virtual PMReal GetWidth(bool16 ignoreAllTrailing = kFalse) const = 0;
	virtual PMReal GetTargetWidth(int32 tileNum = 0) const = 0;
	virtual void SetTargetWidth(PMReal targetWidth, int32 tileNum = 0) = 0;

	/**	SetJustificationViolationAmt sets the justification violation for a line.
		@param jva specifies the justification violation: 0 = no violation, 100 == complete violation.
	*/
	virtual void SetJustificationViolationAmt(int16 jva) const = 0;
	/**	GetJustificationViolationAmt returns a number from 0 = no violation to 100 == complete violation.
		@return the justification violation amount
	*/
	virtual int16 GetJustificationViolationAmt() const = 0;

	/** SetHyphenationViolation indicates whether a hyphenation violation occurred
		@param violation specifies if an unwanted hyphen had to be used.
	*/
	virtual void SetHyphenationViolation(bool16 violation) = 0;
	/** GetHyphenationViolation indicates whether a hyphenation violation occurred
		@return if an unwanted hyphen had to be used.
	*/
	virtual bool16 GetHyphenationViolation() const = 0;

	/** SetLineTightness indicates a "tightness" of this line which is considered in order to favor justification consistency.
		@param t specifies this line's tightness.
	*/
	virtual void SetLineTightness(IWaxLine::LineTightness t) = 0;
	/** GetLineTightness indicates a "tightness" of this line which is considered in order to favor justification consistency.
		@return this line's tightness rating.
	*/
	virtual IWaxLine::LineTightness GetLineTightness() const = 0;

	virtual void SetKeepsViolation(bool16 onOff) = 0;
	virtual bool16 GetKeepsViolation() const = 0;

	/** SetComposedWithMissingFont indicates whether this line's ending was decided using a missing font.
		When this occurs, we will force this line to recompose when opening the document if the font is back.
		@param missing specifies if a missing font had to be used.
	*/
	virtual void SetComposedWithMissingFont(bool16 missing) = 0;
	/** GetComposedWithMissingFont indicates whether this line's ending was decided using a missing font.
		When this occurs, we will force this line to recompose when opening the document if the font is back.
		@return specifies if a missing font had to be used.
	*/
	virtual bool16 GetComposedWithMissingFont() const = 0;

	virtual void SetHyphenState(bool16 endsWithHyphen) = 0;
	virtual bool16 LineEndsWithHyphen() const = 0;

	/**
	Rebuild the Runs everytime the WaxLine is drawn.
	The composer is allowed to set this value at regen time when it only
	has a const pointer.
	*/
	virtual void SetAlwaysRegenerate(bool16 ) const = 0;
	virtual bool16 GetAlwaysRegenerate() const = 0;

	virtual Text::GridAlignmentMetric GetGridAlignmentMetric() const = 0;

	// offset from bottom of line to grid alignment metric
	virtual PMReal GetGridAlignmentMetricOffset() const = 0;
	virtual void SetGridAlignment(Text::GridAlignmentMetric alignment,
									PMReal metricOffset = 0.0) = 0;

	virtual void SetNoShuffle(bool16 s) = 0;
	virtual bool16 GetNoShuffle() const = 0;

	virtual void SetNoShuffleToParcelBottom(bool16 s) = 0;
	virtual bool16 GetNoShuffleToParcelBottom() const = 0;

	virtual void SetRebuildRunsWhenShuffled(bool16 b) = 0;
	virtual bool16	GetRebuildRunsWhenShuffled() const = 0;

	virtual PMReal GetTOFLineHeight() const = 0;
	virtual Text::FirstLineOffsetMetric GetTOFLineHeightMetric() const = 0;
	virtual void SetTOFLineHeight(PMReal lineHeight,
							Text::FirstLineOffsetMetric lineHeightMetric) = 0;

	virtual void SetAtTOF(bool16 v) = 0;
	virtual bool16 GetAtTOF() const = 0;

	virtual void	SetHasOwnedItem(bool16 v) = 0;
	virtual bool16	GetHasOwnedItem() const = 0;

	/** If the WaxLine needs to be damaged when the Parcel that is composed
		into is moved relative to the pasteboard then this should be set to
		kTrue. Some examples are:
			-	The ITiler will return this information for Tiles that are
				aligned to certain grids.

			-	Certain WaxAnchorPts will set this to kTrue if any of their
				Text content is aligned to grids

			-	WaxLines which contain Inlines will have this set to kTrue by
				the composer.
	*/
	virtual void SetParcelPositionDependent(bool16 v) = 0;
	virtual bool16 GetParcelPositionDependent() const = 0;

	virtual PMReal GetIndentHerePosition() const = 0;
	virtual void SetIndentHerePosition(PMReal r) = 0;

	/** When the WaxLine is applied into the Wax the WaxStrand will update
		the thread information. This information is used to speed the lookup
		of Frame information by getting the ParcelList from the StoryThread
		and using the ParcelIndex to get the appropriate Parcel.
	*/
	virtual void SetStoryThread(ITextStoryThread* thread) = 0;
	virtual ITextStoryThread* QueryStoryThread() const = 0;

	/** Damage recording methods.
	*/
	virtual bool16 IsDamaged() const = 0;
	virtual bool16 IsGeometryDamaged() const = 0;
	virtual bool16 IsKeepsDamaged() const = 0;
	virtual bool16 IsContentDamaged() const = 0;
	virtual bool16 IsDestroyed() const = 0;
	virtual void SetContentDamaged() = 0;
	virtual void SetGeometryDamaged() = 0;
	virtual void SetKeepsDamaged() = 0;
	virtual void SetDestroyed() = 0;
	virtual void ClearDamage() = 0;

	/** if alternateInk is nil, IWaxLineShape::GetInkBounds() will be used.
	*/
	virtual void Inval(IParcelList* pl, const PMRect* alternateInk = nil) const = 0;

	virtual void SetWaxAnchorPt(bool16) = 0;
	virtual bool16 GetIsWaxAnchorPt() const = 0;

	virtual IWaxStrand* QueryWaxStrand() const = 0;
	virtual ITextModel* QueryTextModel() const = 0;

	/** Given a CharacterHang type to get the result for, return a PMReal representing
		the number of points upward the line must be adjusted
	*/
	virtual PMReal GetLineMetricOffset(IDrawingStyle::CharacterHang hangType) const = 0;

	/** Optimization. Will be called by the wax iterator.
	*/
	virtual void SetLineTextOrigin(const TextIndex absoluteTextIndex) = 0;

	/** Returns the effective content bottom of the WaxLine. This value is used
		for fit-frame-to-content and cell autogrow computation. For normal
		lines this is simply the Y Position of the line. For lines containing
		Dropcaps and WaxAnchorPts this computation is slightly different.
		The content Top of the line is still the LineHeight or TOFLineHeight.
	*/
	virtual PMReal	GetContentBottom() const = 0;

	/** When set this flag causes calls to SetGeometryDamage to have the side
		effect of calling all available IListInvalService service providers with
		the line that's being geometry damaged. These services are rarely
		needed, but can be used by text adornments to clear cached data on wax
		runs.
	*/
	virtual void SetRequiresCallToListInvalService(bool16 requiresCall) = 0;
	virtual bool16 GetRequiresCallToListInvalService() const = 0;

	/** Support for keeps on WaxLines. ...External keeps represents the previous
		paragraph having KeepWithNextNLines in effect. ...First keeps represents
		the containing paragraph having KeepTogether or KeepFirstNLines in
		effect. ...Last keeps represents the containing paragraph having
		KeepLastNLines in effect.
	*/

	/**
	External keeps represents the previous paragraph having KeepWithNextNLines
	in effect.
	*/
	virtual void	SetKeepWithPrevExternal(bool16 v) = 0;
	virtual bool16	GetKeepWithPrevExternal() const = 0;

	/**
	Prev Para Last Line represents this paragraph having KeepWithPrev in effect
	which simply means keep the first WaxLine of this Paragraph with the last
	WaxLine of the previous Paragraph.
	*/
	virtual void	SetKeepWithPrevParaLastLine(bool16 v) = 0;
	virtual bool16	GetKeepWithPrevParaLastLine() const = 0;

	/**
	First keeps represents the containing paragraph having KeepTogether or
	KeepFirstNLines in effect.
	*/
	virtual void	SetKeepWithPrevFirst(bool16 v) = 0;
	virtual bool16	GetKeepWithPrevFirst() const = 0;

	/**
	Last keeps represents the containing paragraph having KeepLastNLines
	in effect.
	*/
	virtual void	SetKeepWithPrevLast(bool16 v) = 0;
	virtual bool16	GetKeepWithPrevLast() const = 0;

	/** WaxLines which need post-processing due to paragraph attributes require
		adjustments to the CompositionYPosition with SetYPositionAdj(). Although
		the adjustment mechanism is the same, this not the same as Parcel VJ
		which does not mark the WaxLines.
	*/
	virtual void	SetNeedsPostProcessing(bool16 v) = 0;
	virtual bool16	GetNeedsPostProcessing() const = 0;

	/** WaxLines which were asked to compose with the paragraph composer,
		but were actually composed with the single-line composer because of certain
		restrictions should set this flag to true.
	*/
	virtual void	SetComposerWasSwappedToSingle(bool16 v) = 0;
	virtual bool16	GetComposerWasSwappedToSingle() const = 0;

	/** The CompositionYPosition is what is set by the ParagraphComposer. By
		default there is not YPositionAdj so the value returned by GetYPosition()
		is the same as GetCompositionYPosition(). If post-processing occurs,
		whether it be specified in the WaxLine with SetNeedsPostProcessing() or
		by Parcel VJ, then a YPosition Adj will be set.
	*/
	virtual void	SetCompositionYPosition(PMReal compYPos) = 0; // y-position of bottom of line height
	virtual PMReal	GetCompositionYPosition() const = 0;
	virtual bool16	GetYPositionAdjValid() const = 0;
	virtual void	SetYPositionAdj(PMReal yPosAdj) = 0;
	virtual PMReal	GetYPositionAdj() const = 0;

	/**
		These values refer to the attributes used to compose the WaxLine rather
		their actual composed location.

		If the WaxLine is the first of the Paragraph then GetBreakMode() and
		GetSpaceBefore() may return non-zero values.

		If the WaxLine is the last of the Paragraph then GetGotoNextX(),
		GetSpaceAfter() and GetKeepWithNextNLines() may return non-zero values.
	*/
	virtual void	SetBreakMode(Text::StartBreakLocation bl) = 0;
	virtual Text::StartBreakLocation GetBreakMode() const = 0;
	virtual void	SetGotoNextX(Text::StartBreakLocation nx) = 0;
	virtual Text::StartBreakLocation GetGotoNextX() const = 0;

	virtual void	SetSpaceBefore(PMReal sb) = 0;
	virtual PMReal	GetSpaceBefore() const = 0;
	virtual void	SetSpaceAfter(PMReal sa) = 0;
	virtual PMReal	GetSpaceAfter() const = 0;
    virtual void	SetSameParaSpacing(PMReal sb) = 0;
    virtual PMReal	GetSameParaSpacing() const = 0;

	/** Returns kTrue if space after in line should stay when line is last line in parcel
	*/
	virtual void	SetSpaceAfterIsSticky(bool16 v) = 0;
	virtual bool16	GetSpaceAfterIsSticky() const = 0;

	virtual void	SetKeepWithNextNLines(int32 n) = 0;	// last line of Para
	virtual int32	GetKeepWithNextNLines() const = 0;
	virtual void	SetKeepLastNLines(int32 n) = 0;		// first line of Para
	virtual int32	GetKeepLastNLines() const = 0;

	/** 	The YPositionAdj is only valid when the Parcel the WaxLine has composed
		into has VJ set or the WaxLine needs post-processing and in all other
		cases when the WaxLine is composed SetYPositionAdjIgnored() will be
		called.
	*/
	virtual bool16	GetYPositionAdjIgnored() const = 0;
	virtual void	SetYPositionAdjIgnored() = 0;

	/** 	BulletNumberPosition is only used for lines with text wrap and a bullet/number
		adornment contains a tab character.
	*/
	virtual void	SetBulletNumberOffset(PMReal bnp) = 0;
	virtual PMReal	GetBulletNumberOffset() const = 0;

	/**
	By default, WaxLines compose in a single "column". Paragraph attributes
	exist that allow them to span more than one column OR split a single column
	into two or more sub-columns.
	@return kTrue if the WaxLine is the first WaxLine of the paragraph which is spanning or splitting columns, kFalse otherwise.
	*/
	virtual bool16	GetHasColumnSpanOrSplit() const = 0;

	/**
	Sets the column span to the specified value. Valid values for span are
	greater than or equal to 2 and less than or equal to 40. However, if span
	is set to 255 then it is equivalent to "all".
	@param count
	*/
	virtual void	SetColumnSpan(uchar count) = 0;

	/**
	Gets the current column span value.
	Note that only the first WaxLine of the paragraph can be expected to have
	this value set, all other intra para WaxLines will not.
	@param pCount Optional pointer to value which will be set to the span IF a column span has been previously set.
	@return kTrue if a column span was previously set, kFalse otherwise
	*/
	virtual bool16	GetColumnSpan(uchar* pCount = nil) const = 0;

	/**
	Sets the column split to the specified values. Valid values for count are
	greater than or equal to 2 and less than or equal to 40. insideGutter and
	outsideGutter need to be greater than or equal to 0.0.
	*/
	virtual void	SetColumnSplit(uchar count, PMReal insideGutter,
									PMReal outsideGutter) = 0;

	/**
	Gets the current column split value.
	Note that only the first WaxLine of the paragraph can be expected to have
	this value set, all other intra para WaxLines will not.
	@param pCount Optional pointer to value which will be to the split count IF a column split has been previously set.
	@param pInsideGutter Optional pointer to value which will be to the inside gutter width IF a column split has been previously set.
	@param pOutsideGutter Optional pointer to value which will be to the outside gutter width IF a column split has been previously set.
	@return kTrue if a column split was previously set, kFalse otherwise
	*/
	virtual bool16	GetColumnSplit(uchar* pCount = nil,
									PMReal* pInsideGutter = nil,
									PMReal* pOutsideGutter = nil) const = 0;

	/**
	This method is used to remove all the WaxRuns associated with the WaxLine
	and mark that the Runs were invalidated. This information will be used on
	the next rebuild to re-validate the inkbounds. This method should be used
	whenever the rebuild state of WaxLine is expected to be changed. Examples
	are WaxLines with any type of calculated text.
	*/
	virtual void	InvalidateRuns() = 0;
	virtual bool16	GetRunsWereInvalidated() const = 0;
	virtual void	ClearRunsWereInvalidated() = 0;

	/**
	For Internal Use Only: If a Wax Anchored Element doesn't fit in a parcel, we note down its anchor waxline index.
	This is done so that we can limit backing up otherwise it may cause a forever loop.
	*/
	virtual void SetHasWAENoFitInParcel(bool16, const ParcelKey&) = 0;
	virtual bool16 GetHasWAENoFitInParcel(ParcelKey&) const = 0;

	/**
	For Internal Use Only: If paragraph shading is applied on a waxline, we note here on the waxline about the same.
	*/
	virtual void SetParaShadingOn(bool16 bParaShadingOn) = 0;
	virtual bool16 HasParaShadingOn()const = 0;

	/**
	For Internal Use Only: If paragraph border is applied on a waxline, we note here on the waxline about the same.
	*/
	virtual void SetParaBorderOn(bool16 bParaBorderOn) = 0;
	virtual bool16 HasParaBorderOn() const  = 0;

	/**
	For Internal Use Only: If Paragraph Border Merging is enabled, we note here on the waxline about the same.
	*/
	virtual void SetParaBorderMergingOn(bool16 bParaBorderMergingOn) = 0;
	virtual bool16 HasParaBorderMergingOn() const = 0;
	/**
	For Internal Use Only: for "world ready paragraph /world ready single line composer" If shaping engine happens to be HB store this information at waxline level. // default is lipika 
	below information is utilized only for above mentioned paragraph composer.
	*/
	virtual bool IsHarfBuzzParagraphShapingEngine()const = 0;
	virtual void SetHarfBuzzParagraphShapingEngine(bool shapingEngineType) = 0;


};

#endif

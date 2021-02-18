//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextOptions.h $
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
#ifndef __ITextOptions__
#define __ITextOptions__

#include "IPMUnknown.h"
#include "ICompositionStyle.h"
#include "IReferencePointData.h"
#include "CTextEnum.h"
#include "PMReal.h"
#include "TextID.h"


/**
	@ingroup text_layout
*/
class ITextOptions : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTOPTIONS };

	enum WritingDirection { kHorizontal = 0, kVertical };

	virtual bool16 GetUseTypographersQuotes() const = 0;
	virtual void SetUseTypographersQuotes(bool16 useSmartQuotes) = 0;

	virtual bool16 GetShowHnJViolations() const = 0;
	virtual void SetShowHnJViolations(bool16 showViolations) = 0;

	virtual bool16 GetShowKeepsViolations() const = 0;
	virtual void SetShowKeepsViolations(bool16 showViolations) = 0;

	virtual bool16 GetDisplayParaMark() const = 0;
	virtual void SetDisplayParaMark(bool16 displayParaMark) = 0;

	virtual bool16 GetUseFixedWidthColumns() const = 0;
	virtual void SetUseFixedWidthColumns(bool16 fixedWidthColumns) = 0;

	virtual bool16 GetUseFlexibleWidthColumns() const = 0;
	virtual void SetUseFlexibleWidthColumns(bool16 flexibleWidthColumns) = 0;

	virtual bool16 GetIgnoreTextWrap() const = 0;
	virtual void SetIgnoreTextWrap(bool16 ignoreTextWrap) = 0;

	virtual bool16 GetUseVerticalAlignment() const = 0;
	virtual void SetUseVerticalAlignment(bool16 useVerticalAlignment) = 0;

	virtual bool16 GetShowMissingFonts() const = 0;
	virtual void SetShowMissingFonts(bool16 showFonts) = 0;

	virtual int32 GetNumberOfFrameColumns() const = 0;
	virtual void SetNumberOfFrameColumns(int32 numberOfColumns) = 0;

	virtual PMReal GetSmallCapSize() const = 0;
	virtual void SetSmallCapSize(PMReal SmallCapPercentValue) = 0;

	virtual PMReal GetSuperScriptSize() const = 0;
	virtual void SetSuperScriptSize(PMReal SuperScriptSizePercentValue) = 0;

	virtual PMReal GetSubScriptSize() const = 0;
	virtual void SetSubScriptSize(PMReal SubScriptSizePercentValue) = 0;

	virtual PMReal GetSuperScriptPos() const = 0;
	virtual void SetSuperScriptPos(PMReal SuperScriptPosPercentValue) = 0;

	virtual PMReal GetSubScriptPos() const = 0;
	virtual void SetSubScriptPos(PMReal SubScriptPosPercentValue) = 0;

	virtual PMReal GetTextIncrementSize() const = 0;
	virtual void SetTextIncrementSize(PMReal TextIncrementPointSize) = 0;

	virtual PMReal GetBLShiftIncrementSize() const = 0;
	virtual void SetBLShiftIncrementSize(PMReal blShiftIncrementSize) = 0;

	virtual PMReal GetTrackingIncrementSize() const = 0;
	virtual void SetTrackingIncrementSize(PMReal trackingIncrementSize) = 0;

	virtual PMReal GetFrameGutterWidth() const = 0;
	virtual void SetFrameGutterWidth(PMReal gutterWidth) = 0;

	virtual PMReal GetFixedColumnWidth() const = 0;
	virtual void SetFixedColumnWidth(PMReal columnWidth) = 0;

	virtual PMReal GetFlexibleColumnWidthMax() const = 0;
	virtual void SetFlexibleColumnWidthMax(PMReal maxColumnWidth) = 0;

	virtual void GetFrameInsets(PMReal& left, PMReal& top, PMReal& right, PMReal& bottom) const = 0;
	virtual void SetFrameInsets(PMReal left, PMReal top, PMReal right, PMReal bottom) = 0;

	// get and set the primary writing direction, default is kHorizontal.
	virtual	WritingDirection GetPrimaryWritingDirection() const = 0;
	virtual	void SetPrimaryWritingDirection(WritingDirection nWritingDirection) = 0;

	/**	Set whether this story is primarily right to left (ME - Text)
		@param rtl - Should this story be right-to-left (kTrue) or left-to-right (kFalse)
	*/
	virtual void SetRightToLeft(bool16 rtl) = 0;

	/**	Find out whether this story is right-to-left or not (ME - Text)
		@return - Is this story right-to-left (kTrue) or left-to-right (kFalse)
	*/
	virtual bool16 IsRightToLeft() const = 0;

	virtual bool16 GetMMOpticalSize() const = 0;
	virtual void SetMMOpticalSize(bool16 MMOpticalSize) = 0;

	// get and set the first line offset, default is kAscent.
	virtual	Text::FirstLineOffsetMetric GetFirstLineOffsetMetric() const = 0;
	virtual	void SetFirstLineOffsetMetric(Text::FirstLineOffsetMetric nFirstLineOffset) = 0;

	virtual	PMReal GetMinFirstLineOffset() const = 0;
	virtual	void SetMinFirstLineOffset(PMReal value) = 0;

	virtual	Text::VerticalJustification GetVerticalJustification() const = 0;
	virtual	void SetVerticalJustification(Text::VerticalJustification justify) = 0;
	// get and set the vertical justification, default is kVJTop.

	virtual void SetMaxVJInterParaSpace(PMReal maxInterParaSpace) = 0;
	virtual PMReal GetMaxVJInterParaSpace() const = 0;

	virtual bool16 GetVJBalanceColumns() const = 0;
	virtual void SetVJBalanceColumns(bool16 balance) = 0;

	virtual	Text::AutoSizeDimension GetAutoSizeDimension() const = 0;
	virtual	void SetAutoSizeDimension(Text::AutoSizeDimension asDimension) = 0;

	virtual	IReferencePointData::ReferencePointPosition GetAutoSizeRefPoint() const = 0;
	virtual	void SetAutoSizeRefPoint(IReferencePointData::ReferencePointPosition asRefPoint) = 0;

	virtual	bool16 GetAutoSizeHasMinHeight() const = 0;
	virtual	void SetAutoSizeHasMinHeight(bool16 asHasMinHeight) = 0;

	virtual	PMReal GetAutoSizeMinHeightValue() const = 0;
	virtual	void SetAutoSizeMinHeightValue(PMReal asMinHeightValue) = 0;

	virtual	bool16 GetAutoSizeHasMinWidth() const = 0;
	virtual	void SetAutoSizeHasMinWidth(bool16 asHasMinWidth) = 0;

	virtual	PMReal GetAutoSizeMinWidthValue() const = 0;
	virtual	void SetAutoSizeMinWidthValue(PMReal asMinWidthValue) = 0;

	virtual	bool16 GetAutoSizeNoLineBreak() const = 0;
	virtual	void SetAutoSizeNoLineBreak(bool16 asNoLineBreak) = 0;

	virtual bool16 GetShowKinsoku() const = 0;
	virtual void SetShowKinsoku(bool16 showKinsoku) = 0;

	virtual bool16 GetShowCustomCharWidths() const = 0;
	virtual void SetShowCustomCharWidths(bool16 showCustomCharWidths) = 0;

	virtual bool16 GetShowStylePreviewMode() const = 0;
	virtual void SetShowStylePreviewMode(bool16 showCustomCharWidths) = 0;

	virtual bool16 GetShowGlyphSubstitutions() const = 0;
	virtual void SetShowGlyphSubstitutions(bool16 show) = 0;

	virtual bool16 GetUseParagraphLeading() const = 0;
	virtual void SetUseParagraphLeading(bool16 useParagraphLeading) = 0;

	virtual bool16 GetJustifyTextWrap() const = 0;
	virtual void SetJustifyTextWrap(bool16 justifyTextWrap) = 0;

	/**  GetLinkTextFiles returns whether or not text files should be linked when imported. Doesn't apply to InCopy stories, they are always linked.
		@return kTrue if links should be created on import (place), kFalse if not.
	*/
	virtual bool16 GetLinkTextFiles() const = 0;

	/**  SetLinkTextFiles is used to set whether text files should be linked when imported.
		@param linkTextFiles IN kTrue if a link is created for text files on import (place), kFalse if not.
	*/
	virtual void SetLinkTextFiles(bool16 linkTextFiles) = 0;

	virtual bool16 GetUseNewVerticalScaling() const = 0;
	/**  SetUseNewVerticalScaling is used to set whether scaling Roman text in vertical frames reverses x and y.
		@param useNewVScale IN kTrue if scaling Roman text in vertical frames follows scaling of J upright chars.
	*/
	virtual void SetUseNewVerticalScaling(bool16 useNewVScale) = 0;

	virtual bool16 GetUseCIDMojikumi() const = 0;
	/**  SetUseCIDMojikumi is used to set whether the Japanese composer attempts to use CIDs to determine mojikumi class, tsume, etc, rahter than Unicode.
		@param b IN kTrue if using CID-based mojikumi.
	*/
	virtual void SetUseCIDMojikumi(bool16 b) = 0;

	virtual bool16 GetUseHalfWidthQuotes() const = 0;
	/**  SetUseHalfWidthQuotes is used to set whether the Japanese composer treats quotes ( ) as half width.
			Before CS6 quotes were treated as full width because older fonts had them as full width
			now however in modern fonts they are half width. 
			Affects -
			kTextChar_LeftSingleQuotationMark:		// 0x2018
			kTextChar_RightSingleQuotationMark:	// 0x2019
			kTextChar_LeftDoubleQuotationMark:		// 0x201C
			kTextChar_RightDoubleQuotationMark:	// 0x201D

		@param b IN kTrue if treating quotes as half width.
	*/
	virtual void SetUseHalfWidthQuotes(bool16 b) = 0;


	/** Internal  method used to show HnJ setting. Please do not call!
	*/
	virtual bool16 GetShowHnJViolations_DURING_CONVERSION_ONLY() const = 0;

	/** Internal  method used to convert show keeps setting. Please do not call!
	*/
	virtual bool16 GetShowKeepsViolations_DURING_CONVERSION_ONLY() const = 0;

	/** Internal  method used to convert show para mark setting. Please do not call!
	*/
	virtual bool16 GetDisplayParaMark_DURING_CONVERSION_ONLY() const = 0;

	/** Internal  method used to convert show missing fonts setting. Please do not call!
	*/
	virtual bool16 GetShowMissingFonts_DURING_CONVERSION_ONLY() const = 0;

	/** Internal  method used to convert show kinsoku setting. Please do not call!
	*/
	virtual bool16 GetShowKinsoku_DURING_CONVERSION_ONLY() const = 0;

	/** Internal  method used to convert show custom char widths setting. Please do not call!
	*/
	virtual bool16 GetShowCustomCharWidths_DURING_CONVERSION_ONLY() const = 0;

	/** Internal  method used to convert show glyph subtitutions setting. Please do not call!
	*/
	virtual bool16 GetShowGlyphSubstitutions_DURING_CONVERSION_ONLY() const = 0;

  /** Internal  method used to show glyph subtitutions for opentype context menu. Please do not call!
	*/
	virtual bool16 GetOTHL() const = 0;
	virtual void SetOTHL(bool16 val) = 0;

	// Getter/Setters for vertical rule
	virtual bool16			GetUseVerticalRule() const = 0;
	virtual void			SetUseVerticalRule(bool16 useVerticalRule) = 0;

	virtual PMReal			GetVerticalRuleOffset() const = 0;
	virtual void			SetVerticalRuleOffset(PMReal offset) = 0;

	virtual PMReal			GetVerticalRuleTopInset() const = 0;
	virtual void			SetVerticalRuleTopInset(PMReal inset) = 0;

	virtual bool16			GetVerticalRuleInsetChain() const = 0;
	virtual void			SetVerticalRuleInsetChain(bool16 isChained) = 0;

	virtual PMReal			GetVerticalRuleBottomInset() const = 0;
	virtual void			SetVerticalRuleBottomInset(PMReal inset) = 0;

	virtual PMReal			GetVerticalRuleStrokeWidth() const = 0;
	virtual void			SetVerticalRuleStrokeWidth(PMReal width) = 0;

	virtual UID				GetVerticalRuleStrokeColor() const = 0;
	virtual void			SetVerticalRuleStrokeColor(UID colorUID) = 0;

	virtual ICompositionStyle::StrokeType		GetVerticalRuleStrokeType() const = 0;
	virtual void			SetVerticalRuleStrokeType(ICompositionStyle::StrokeType strokeType) = 0;

	virtual PMReal			GetVerticalRuleTint() const = 0;
	virtual void			SetVerticalRuleTint(PMReal tint) = 0;

	virtual bool16			GetVerticalRuleOverprint()const = 0;
	virtual void			SetVerticalRuleOverprint(bool16 isOverprint) = 0;

	virtual bool16 GetHarfbuzzOverride() const = 0;
	// SetHarfbuzzOverride : if this parameter is set to true, Indic & Latin scripts will be shaped through Harfbuzz instead of Lipika.
	virtual void SetHarfbuzzOverride(bool16 b) = 0;
};

DECLARE_BASE_TYPE(ITextOptions::WritingDirection);
#endif

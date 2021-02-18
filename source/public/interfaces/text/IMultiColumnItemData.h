//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IMultiColumnItemData.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __IMultiColumnItemData__
#define __IMultiColumnItemData__

#include "IPMUnknown.h"
#include "TextID.h"
#include "ICompositionStyle.h"
#include "IBaselineFrameGridData.h"
#include "ITextFrameFootnoteOptions.h"
#include "IReferencePointData.h"
#include "CTextEnum.h"

class ITextColumnSizer;
class ITextFrameOptionsData;
class ITextOptions;
class IVerticalColumnRuleData;

/** 
	@ingroup text_layout
*/
class IMultiColumnItemData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IMULTICOLUMNDATA};

		// Called when you have the doc preferences
		virtual void   SetTextFrameOptionsData(ITextOptions *textOptions) = 0;
		// Called when you have the frame options data from an object style
		virtual void   SetTextFrameOptionsData(ITextFrameOptionsData *textFrameOptionsData) = 0;
		virtual void   SetTextFrameOptionsData(ITextColumnSizer *textColumnSizer) = 0;

		virtual int32  GetNumberOfColumns() = 0;
		virtual PMReal GetGutterWidth() = 0;
		virtual bool16 GetUseFixedColumnSize() = 0;
		virtual PMReal GetFixedColumnWidth() = 0;
		virtual bool16 GetUseFlexibleColumnSize() = 0;
		virtual PMReal GetMaxColumnSize() = 0;
		virtual void   GetFrameInsets(PMReal& left, PMReal& top, PMReal& right, PMReal& bottom) = 0;
		virtual Text::FirstLineOffsetMetric GetFirstLineOffsetMetric() = 0;
		virtual PMReal GetMinFirstLineOffset() const = 0;
		virtual Text::VerticalJustification GetVerticalJustification() = 0;
		virtual PMReal GetMaxVJInterParaSpace() const = 0;
		virtual bool16 GetVJBalanceColumns() const = 0;
		virtual bool16 GetIgnoreTextWrap() const = 0;

		// Called when you have the doc preferences
		virtual void   SetTextFrameAutoSizeOptionsData(ITextOptions *textOptions) = 0;
		// Called when you have the frame options data from an object style
		virtual void   SetTextFrameAutoSizeOptionsData(ITextFrameOptionsData *textFrameOptionsData) = 0;

		virtual Text::AutoSizeDimension GetAutoSizeDimension() const = 0;
		virtual IReferencePointData::ReferencePointPosition GetAutoSizeRefPoint() const = 0;
		virtual bool16 GetAutoSizeHasMinHeight() const = 0;
		virtual PMReal GetAutoSizeMinHeightValue() const = 0;
		virtual bool16 GetAutoSizeHasMinWidth() const = 0;
		virtual PMReal GetAutoSizeMinWidthValue() const = 0;
		virtual bool16 GetAutoSizeNoLineBreak() const = 0;
		
		// Called when you have the doc preferences
		virtual void SetBaselineFrameGridData(IBaselineFrameGridData *baseLineFrameGridData) = 0;
		// Called when you have the frame options data from an object style
		virtual void SetBaselineFrameGridData(ITextFrameOptionsData *textFrameOptionsData) = 0;

		virtual void SetTextFrameFootnoteOptions(ITextFrameFootnoteOptions *textFrameFootnoteOptions) = 0;
		virtual void SetTextFrameFootnoteOptions(ITextFrameOptionsData *textFrameOptionsData) = 0;

		virtual bool16 GetUseCustomBaselineGridFlag() const = 0;
		virtual PMReal GetStartingOffset() const = 0;
		virtual IBaselineFrameGridData::RelativeOption GetRelativeOption() const = 0;
		virtual PMReal GetIncrement() const = 0;
		virtual UID GetBaselineFrameGridColor() const = 0;

		// Used by object styles when converting from a non-text frame to a text frame
		virtual void SetInitialParagraphStyle(UID paraStyle) = 0;
		virtual UID GetInitialParagraphStyle() const = 0;

		// ddarling 6/23/04 -- I wanted to get rid of these, but they are still using these for specific cases, 
		// I added the above calls for SetTextFrameOptionsData because there was about 25+ places which did exactly 
		// those things, but master pages, InCopy, and TOC still want to have greater control so these are hanging around.
		virtual void SetNumberOfColumns(int32 number) = 0;
		virtual void SetGutterWidth(PMReal width) = 0;
		virtual void SetUseFixedColumnSize(bool16 fixedSize) = 0;
		virtual void SetFixedColumnWidth(PMReal columnWidth) = 0;

		// ddarling 6/23/04 -- needed to add this for cases where just the ignore data was being set
		virtual void SetIgnoreTextWrap(bool16 ignore) = 0;
		
		virtual void SetUseFlexibleColumnSize(bool16 flexibleSize) = 0;
		virtual bool16	GetEnableOverrides() const = 0;
		virtual bool16	GetSpanFootnotesAcross() const = 0;
		virtual PMReal	GetMinimumSpacing() const = 0;
		virtual PMReal	GetSpaceBetweenFootnotes() const = 0;

		// Getter for vertical rule
		virtual bool16			GetUseVerticalRule() const = 0;
		virtual PMReal			GetVerticalRuleOffset() const = 0;
		virtual PMReal			GetVerticalRuleTopInset() const = 0;
		virtual bool16			GetVerticalRuleInsetChain() const = 0;
		virtual PMReal			GetVerticalRuleBottomInset() const = 0;
		virtual PMReal			GetVerticalRuleStrokeWidth() const = 0;
		virtual UID				GetVerticalRuleStrokeColor() const = 0;
		virtual ICompositionStyle::StrokeType		GetVerticalRuleStrokeType() const = 0;
		virtual PMReal			GetVerticalRuleTint() const = 0;
		virtual bool16			GetVerticalRuleOverprint()const = 0;
		virtual void			SetVerticalColumnRuleData(IVerticalColumnRuleData *verticalColRuleData) = 0;
		virtual void			SetVerticalColumnRuleData(ITextFrameOptionsData *tfoData) = 0;
};

#endif /* __IMultiColumnItemData__ */

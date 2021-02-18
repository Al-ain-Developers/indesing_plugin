//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFramePrefsCmdData.h $
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
#ifndef __IFramePrefsCmdData__
#define __IFramePrefsCmdData__

#include "IPMUnknown.h"
#include "ICompositionStyle.h"
#include "IReferencePointData.h"
#include "UIDRef.h" 
#include "PMReal.h"
#include "CTextEnum.h"
#include "TextID.h"

class IDataBase;

/** 
	@ingroup text_layout
	Interface used to set up kSetFramePrefsCmdImpl for text frames.
*/
class IFramePrefsCmdData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IFRAMEPREFSCMDDATA };

	/**
		Set the values for the command. Most of the parameters can be retrieved from ITextOptions if custom values aren't desired.
		@param useFixedWidth - if kTrue use fixed column widths
		@param useVerticalAlign - if kTrue frame is vertically aligned
		@param ignoreTextWrap - if kTrue ignore text wrap
		@param numColumns - 1 to n columns in frame (non fixed column sizing)
		@param gutter - what is the gutter width
		@param columnWidth - how wide are the columns (fixed column sizing)
		@param leftInset - value for left inset
		@param topInset - value for top inset
		@param rightInset - value for right inset
		@param bottomInset - value for bottom inset
		@param firstLineOffsetMetric - type of first line offset metric
		@param minFirstLineOffset - minimum value for first line offset (see ITextOptions)
		@param vj - vertical justification type (see ITextOptions)
		@param maxVJInterParaSpace - See ITextOptions
		@param vjBalanceColumns - See ITextOptions
		@param useFlexibleWidth - if kTrue use flexible column widths
		@param maxColumnWidth - maximum column width (flexible column sizing)
		@param auto sizing dimension - dimension of auto sizing - Off, Width, Height, Both or proportionally
		@param auto sizing reference point - reference point from 9 point proxy
		@param auto sizing min height flag - if true use minimum height value
		@param auto sizing min height value - the value of minimum height
		@param auto sizing min width flag - if true use minimum width value
		@param auto sizing min width value - the value of minimum width
		@param auto sizing has line breaks flag - if true then line breaks are not applied
		@param useVerticalRule - if true then vertical column is applied
		@param verticalRuleOffset - offset for vertical column rule
		@param verticalRuleTopInset - inset from top of vertical cloumn rule
		@param verticalRuleInsetChain - inset's chain value of vertical cloumn rule
		@param verticalRuleBottomInset - inset from bottom of vertical column rule
		@param verticalRuleStrokeWidth - width of vertical column rule
		@param verticalRuleStrokeColor - color of vertical column rule
		@param verticalRuleStrokeType - type of vertical column rule
		@param verticalRuleTint - tint of vertical column rule
		@param verticalRuleOverprint - if true then overprint of vertical column is applied
		@return none.
	*/
	virtual void Set(		
						bool16 useFixedWidth,
						bool16 useVerticalAlign,
						bool16 ignoreTextWrap,
						int32 numColumns,
						PMReal gutter,
						PMReal columnWidth,
						PMReal leftInset,
						PMReal topInset,
						PMReal rightInset,
						PMReal bottomInset,
						Text::FirstLineOffsetMetric firstLineOffsetMetric,
						PMReal minFirstLineOffset,
						Text::VerticalJustification vj,
						PMReal maxVJInterParaSpace,
						bool16 vjBalanceColumns,
						bool16 useFlexibleWidth,
						PMReal maxColumnWidth,
						Text::AutoSizeDimension asDimension,
						IReferencePointData::ReferencePointPosition refPoint,
						bool16 useMinHeight,
						PMReal minHeightValue,
						bool16 useMinWidth,
						PMReal minWidthValue,
						bool16 noLineBreak,
						bool16 useVerticalRule,
						PMReal verticalRuleOffset,
						PMReal verticalRuleTopInset,
						bool16 verticalRuleInsetChain,
						PMReal verticalRuleBottomInset,
						PMReal verticalRuleStrokeWidth,
						UID verticalRuleStrokeColor,
						ICompositionStyle::StrokeType verticalRuleStrokeType,
						PMReal verticalRuleTint,
						bool16 verticalRuleOverprint,
						const	UIDRef&	doc			/* which document to affect */
						) = 0;
		
	/**
		Get the value configured in the set method param useFixedWidth.
		@return kTrue using fixed columns.
	*/
	virtual bool16 GetUseFixedWidth() = 0;
		
	/**
		Get the value configured in the set method param useVerticalAlign.
		@return kTrue using vertical alignment.
	*/
	virtual bool16 GetUseVerticalAlignment() = 0;
		
	/**
		Get the value configured in the set method param ignoreTextWrap.
		@return kTrue if ignoring text wrap.
	*/
	virtual bool16 GetIgnoreTextWrap() = 0;
	
	/**
		Get the value configured in the set method param numColumns.
		@return number of columns.
	*/
	virtual int32 GetNumColumns() = 0;

	/**
		Get the value configured in the set method param gutter.
		@return gutter width.
	*/
	virtual PMReal GetGutter() = 0;
		
	/**
		Get the value configured in the set method param columnWidth.
		@return column width.
	*/
	virtual PMReal GetFixedColumnWidth() = 0;
		
	/**
		Get the value configured in the set method inset params.
		@param left - left inset value
		@param top - top inset value
		@param right - right inset value
		@param bottom - bottom inset value
		@return none.
	*/
	virtual const void GetInsets(PMReal& left, PMReal& top, PMReal& right, PMReal& bottom) = 0;

	/**
		Get the value configured in the set method param minFirstLineOffset.
		@return type of first line offset.
	*/
	virtual	Text::FirstLineOffsetMetric GetFirstLineOffsetMetric() = 0;
		
	/**
		Get the value configured in the set method param firstLineOffsetMetric.
		@return minimum first line offset value.
	*/
	virtual	PMReal GetMinFirstLineOffset() = 0;
		
	/**
		Get reference to the document that owns the frame values are being set on.
		@return document reference.
	*/
	virtual const UIDRef& GetDocument() = 0;
	
	/**
		Get the value configured in the set method param vj.
		@return vertical justification setting.
	*/
	virtual Text::VerticalJustification GetVerticalJustification() const = 0;
	
	/**
		Get the value configured in the set method param maxInterParaSpace.
		@return maximum inter-paragraph spacing value.
	*/
	virtual PMReal GetMaxVJInterParaSpace() const = 0;

	/**
		Get the value configured in the set method param vjBalanceColumns.
		@return vj balance columns value.
	*/
	virtual bool16 GetVJBalanceColumns() const = 0;

	/**
		Get the value configured in the set method param useFlexibleWidth.
		@return kTrue using flexible width columns.
	*/
	virtual bool16 GetUseFlexibleWidth() = 0;

	/**
		Get the value configured in the set method param minColumnWidth.
		@return minimum column width.
	*/
	virtual PMReal GetMinColumnWidth() = 0;

	/**
		Get the value configured in the set method param maxColumnWidth.
		@return maximum column width.
	*/
	virtual PMReal GetMaxColumnWidth() = 0;

	/**
		Get the value configured in the set method param asDimension.
		@return auto size dimension.
	*/
	virtual Text::AutoSizeDimension GetAutoSizeDimension() = 0;

	/**
		Get the value configured in the set method param refPoint.
		@return reference point.
	*/
	virtual IReferencePointData::ReferencePointPosition GetAutoSizeRefPoint() = 0;

	/**
		Get the value configured in the set method param useMinHeight.
		@return true if using given min height.
	*/
	virtual bool16 GetAutoSizeHasMinHeight() = 0;

	/**
		Get the value configured in the set method param minHeightValue.
		@returns min height value.
	*/
	virtual PMReal	GetAutoSizeMinHeightValue() = 0;

	/**
		Get the value configured in the set method param useMinWidth.
		@return true if using given min width.
	*/
	virtual bool16 GetAutoSizeHasMinWidth() = 0;

	/**
		Get the value configured in the set method param minWidthValue.
		@returns min width value.
	*/
	virtual PMReal	GetAutoSizeMinWidthValue() = 0;

	/**
		Get the value configured in the set method param useNoLineBreak.
		@return true if has no line breaks.
	*/
	virtual bool16 GetAutoSizeNoLineBreak() = 0;

	/**
		Get the value configured in the set method param useVerticalRule.
		@return true if vertical rule has applied.
	*/
	virtual bool16			GetUseVerticalRule() = 0;

	/**
		Get the value configured in the set method param verticalRuleOffset.
		@return vertical rule offset.
	*/
	virtual PMReal			GetVerticalRuleOffset() = 0;

	/**
		Get the value configured in the set method param verticalRuleTopInset.
		@return vertical rule top inset
	*/
	virtual PMReal			GetVerticalRuleTopInset() = 0;

	/**
		Get the value configured in the set method param verticalRuleInsetChain.
		@return vertical rule inset chain value.
	*/
	virtual bool16			GetVerticalRuleInsetChain() = 0;

	/**
		Get the value configured in the set method param verticalRuleBottomInset.
		@return vertical rule bottom inset
	*/
	virtual PMReal			GetVerticalRuleBottomInset() = 0;

	/**
		Get the value configured in the set method param verticalRuleStrokeWidth.
		@return vertical rule stroke width.
	*/
	virtual PMReal			GetVerticalRuleStrokeWidth() = 0;

	/**
		Get the value configured in the set method param verticalRuleStrokeColor.
		@return vertical rule stroke color.
	*/
	virtual UID				GetVerticalRuleStrokeColor() = 0;

	/**
		Get the value configured in the set method param verticalRuleStrokeColor.
		@return vertical rule stroke type.
	*/
	virtual ICompositionStyle::StrokeType			GetVerticalRuleStrokeType() = 0;

	/**
		Get the value configured in the set method param verticalRuleStrokeColor.
		@return vertical rule stroke tint.
	*/
	virtual PMReal				GetVerticalRuleTint() = 0;

	/**
		Get the value configured in the set method param verticalRuleStrokeColor.
		@return true if vertical rule stroke overprint is applied.
	*/
	virtual bool16				GetVerticalRuleOverprint() = 0;
};

#endif // __IFramePrefsCmdData__

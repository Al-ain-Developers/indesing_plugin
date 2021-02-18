//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IVerticalColumnRuleData.h $
//  
//  Owner: Anurag Singh
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2019 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================


#ifndef _IVerticalColumnRuleData_
#define _IVerticalColumnRuleData_

#define kMinVerticalRuleOffset			-10000
#define kMaxVerticalRuleOffset			10000			
#define kMinVerticalRuleTopInset		-10000	
#define kMaxVerticalRuleTopInset		10000				
#define kMinVerticalRuleBottomInset		-10000		
#define kMaxVerticalRuleBottomInset		10000				
#define kMaxVerticalRuleWidth			10000

#ifndef __ODFRC__ // when used for core resource compilation, provide just the parameter range constants

#include "IPMUnknown.h"
#include "ICompositionStyle.h"

#include "TextID.h"

#include "PMReal.h"
class ITextFrameOptionsData;

class IVerticalColumnRuleData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IVERTICALCOLUMNRULEDATA };

	/**
		VerticalRuleHeightMode defines height mode of vertical rules for different locales.
		For Roman locales: kFlag_VerticalRuleHeightAscToDesc
		For Japanese locales: kFlag_VerticalRuleHeightEmBoxToEmBox
	*/
	enum VerticalRuleHeightMode
	{
		kFlag_VerticalRuleHeightDefault = 0,
		kFlag_VerticalRuleHeightAscToDesc,
		kFlag_VerticalRuleHeightEmBoxToEmBox
	};

	/**
		Get is vertical rule applied on multi column frame flag
		@return bool16
	*/
	virtual bool16			GetUseVerticalRule() const = 0;

	/**
		Set the use vertical rule flag of multi column frame
		@param bool16 to turn on/off vertical rule
	*/
	virtual void			SetUseVerticalRule(bool16 useVerticalRule) = 0;

	/**
		Get the Vertical rule offset of multi column frame
		@return offset value
	*/
	virtual PMReal			GetVerticalRuleOffset() const = 0;

	/**
		Set the vertical rule offset of multi column frame
		@param offset value
	*/
	virtual void			SetVerticalRuleOffset(PMReal offset) = 0;

	/**
		Get the Vertical rule top inset of multi column frame
		@return top inset value
	*/
	virtual PMReal			GetVerticalRuleTopInset() const = 0;

	/**
		Set the vertical rule top inset of multi column frame
		@param top inset value to set
	*/
	virtual void			SetVerticalRuleTopInset(PMReal inset) = 0;

	/**
		Get the vertical rule inset chain of multi column frame
		@return kTrue if inset chain is on otherwise kFalse
	*/
	virtual bool16			GetVerticalRuleInsetChain() const = 0;

	/**
		Set the vertical rule inset chain of multi column frame
		@param offset Value
	*/
	virtual void			SetVerticalRuleInsetChain(bool16 isChained) = 0;

	/**
		Get the vertical rule Bottom inset of multi column frame
		@return PMReal bottom inset
	*/
	virtual PMReal			GetVerticalRuleBottomInset() const = 0;

	/**
		Set the vertical rule Bottom inset of multi column frame
		@param bottom inset value 
	*/
	virtual void			SetVerticalRuleBottomInset(PMReal inset) = 0;

	/**
		Get the vertical rule stroke width of multi column frame
		@return PMReal stroke width value
	*/
	virtual PMReal			GetVerticalRuleStrokeWidth() const = 0;

	/**
		Set the vertical rule stroke width of multi column frame
		@param stroke width value to set
	*/
	virtual void			SetVerticalRuleStrokeWidth(PMReal width) = 0;

	/**
		Get the vertical rule stroke color of multi column frame.
		@return color UID
	*/
	virtual UID				GetVerticalRuleStrokeColor() const = 0;

	/**
		Set the vertical rule stroke color of multi column frame
		@param stroke color UID Value to set
	*/
	virtual void			SetVerticalRuleStrokeColor(UID colorUID) = 0;

	/**
		Get the column rule stroke type of multi column frame.
		@return vertical applied on column rules
	*/
	virtual ICompositionStyle::StrokeType		GetVerticalRuleStrokeType() const = 0;

	/**
		Set the vertical rule stroke type of multi column frame
		@param StrokeType value
	*/
	virtual void			SetVerticalRuleStrokeType(ICompositionStyle::StrokeType strokeType) = 0;

	/**
		Get the vertical rule stroke tint of multi column frame.
		@return PMReal tint value
	*/
	virtual PMReal				GetVerticalRuleTint() const = 0;

	/**
		Set the vertical rule stroke tint of multi column frame
		@param stroke tint Value to set
	*/
	virtual void			SetVerticalRuleTint(PMReal tint) = 0;

	/**
		Get the vertical rule stroke overprint of multi column frame
		@return kTrue if overprint is on otherwise kFalse
	*/
	virtual bool16 				GetVerticalRuleOverprint() const = 0;

	/**
		Set the vertical rule stroke overprint of multi column frame
		@param stroke overprint Value to set
	*/
	virtual void			SetVerticalRuleOverprint(bool16 isOverprint) = 0;

	/**
		Get the Vertical rule height mode of multi column frame
		@return VerticalRuleHeightMode 
	*/
	virtual VerticalRuleHeightMode 				GetVerticalRuleHeightMode() const = 0;

	/** for internal use only */
    /**
		Set the vertical rule height mode of multi column frame
	*/
	virtual void			SetVerticalRuleHeightMode() = 0;

	/**
		CopyFrom copies from the source to this IVerticalColumnRuleData.
		@param source IN The IVerticalColumnRuleData to copy.
	*/
	virtual void CopyFrom(const IVerticalColumnRuleData* verticalColumnRuleData) = 0;

	/** 
		CopyFrom copies from the ITextFrameOptionsData to this IVerticalColumnRuleData.
		@param source IN The ITextFrameOptionsData to copy.
	*/
	virtual void CopyFrom(const ITextFrameOptionsData* tfoData) = 0;
};

#endif	// __odfrc__
#endif	// _IVerticalColumnRuleData_

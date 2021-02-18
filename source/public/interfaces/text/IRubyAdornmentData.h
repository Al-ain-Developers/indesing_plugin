//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IRubyAdornmentData.h $
//  
//  Owner: 
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
#ifndef __IRubyAdornmentData__
#define __IRubyAdornmentData__

#include "IRubyStyle.h"			// for ruby enums
#include "TextAttrID.h"			// for IID_IRUBYADORNMENTDATA
#include "CTextEnum.h"			// for Text::GlyphID
#include "IKRAdornmentData.h"

class PMPoint;
class PMReal;

/** Adornment data interface for Ruby IAdornmentData
	@ingroup text_adorn
	@see Adornments
*/
class IRubyAdornmentData : public IKRAdornmentData
{
public:
	enum { kDefaultIID = IID_IRUBYADORNMENTDATA };

	enum RubyKind {
			kGroup = IRubyStyle::kRubyKind_Group,
			kMono		/* = IRubyStyle::kRubyKind_Mono */
		};

	enum RubyPosition {
			kTopRight = IRubyStyle::kRubyPosition_TopRight,				// Horizontal: Top		Vertical: Right
			kBottomLeft	/* = IRubyStyle::kRubyPosition_BottomLeft */	// Horizontal: Bottom 	Vertical: Left
		};

	enum RubyOverHang {
			kOHNone = IRubyStyle::kRubyOverHang_None,		// None
			kOHOneRuby	/* = IRubyStyle::kRubyOverHang_OneRuby */,		// One width of Ruby character
			kOHHalfRuby	/* = IRubyStyle::kRubyOverHang_HalfRuby */,		// Half width of Ruby character
			kOHOneChar	/* = IRubyStyle::kRubyOverHang_OneChar */,		// One width of base text character
			kOHHalfChar	/* = IRubyStyle::kRubyOverHang_HalfChar */,		// Half width of base text character
			kOHNoLimit	/* = IRubyStyle::kRubyOverHang_NoLimit */
		};

	enum RubyAdjustBaseText {
			kABTAdjustNone = IRubyStyle::kRubyAdjustParent_None,	// None
			kABTBothSide	/* = IRubyStyle::kRubyAdjustParent_BothSide */,	// Add space both side of base text characters.
			kABTMojikumi	/* = IRubyStyle::kRubyAdjustParent_Mojikumi */,	// Add space 1:2:1 in base text characters.
			kABTEqualAki	/* = IRubyStyle::kRubyAdjustParent_EqualAki */,	// Add space 1:1:1 in base text characters.
			kABTJustify	/* = IRubyStyle::kRubyAdjustParent_Justify */	// Full Justify.
		};

	enum RubyAlign {
			kLeft = IRubyStyle::kRubyAlign_Left,						// Left alignment
			kCenter		/* = IRubyStyle::kRubyAlign_Center */,			// Center alignment
			kRight		/* = IRubyStyle::kRubyAlign_Right */,			// Right alignment
			kJustify	/* = IRubyStyle::kRubyAlign_Justify */,			// Full Justify
			kJISRule	/* = IRubyStyle::kRubyAlign_JISRule */,			// 1:2:1
			kEqualSpace	/* = IRubyStyle::kRubyAlign_EqualSpace */,		// 1:1:1
			kEdgeOneRuby /* = IRubyStyle::kRubyAlign_EdgeOneRuby */		// add one width of ruby character. (both side)
		};

	enum RubyPlacementResult {
			kNotPlaced = 0,
			kGreat = 0x8,
			kGood = 0x10,
			kFine = 0x18,
			kOk = 0x20,
			kNotBad = 0x28,
			kKindaBad = 0x30,
			kBad = 0x38,
			kVeryBad = 0x40,
			kPanic = 0x48
		};

	
	/** Set number of base text characters covered by this ruby adornment
	@param length IN number of characters
	*/
	virtual void SetRubyText(int32 length) = 0;

	/** Set font used by Ruby
	@param font IN IPMFont UID
	@param size IN text pt size
	@param style IN face name (non-native) of ruby font
	*/
	virtual void SetRubyFont(UID font, const PMReal& size, PMString style) = 0;

	/** Set ruby placement result. Can be used to give feedback to user similar to H&J violation hilight for ruby.
	@param result IN description of how "good" the ruby layout is
	*/
	virtual void SetRubyPlacementResult(enum RubyPlacementResult result) = 0;

	/** Set base text IWaxRun this adornment is adorning
	@param baseTextWaxRun IN IWaxRun corresponding to base text run ruby is adorning
	*/
	virtual void SetBaseTextRun(IWaxRun* baseTextWaxRun) = 0;

	/** Returns if there is ruby on the base text to adorn
	@return true if there is ruby
	*/
	virtual		  bool16	IsFeatureOn() const = 0;

	/** Returns number of base text characters covered by this ruby adornment
	@return number of base text characters
	*/
	virtual		  int32		GetLength() const = 0;

	/** Get how "good" the ruby placement is
	@return enum RubyPlacementResult
	*/
	virtual enum RubyPlacementResult GetRubyPlacementResult() const = 0;

	/** Custom impl of QueryFont for ruby font
	@param database of current pub
	@return ruby font
	*/
	virtual IPMFont* QueryFont(IDataBase *db) const = 0;

	/** Splits adornment into two at offset
	@param other OUT ptr to split off adornment
	@param offsetInRun IN offset into base text run to split at
	@return true if split occurred
	*/
	virtual bool16 SplitInto(IKRAdornmentData* other, int32 offsetInRun) = 0;
};

#endif

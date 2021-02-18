//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IKentenAdornmentData.h $
//  
//  Owner: Ric Kamicar
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
#ifndef __IKentenAdornmentData__
#define __IKentenAdornmentData__

#include "IPMUnknown.h"
#include "IKentenStyle.h"
#include "ITextAdornmentData.h"
#include "TextAttrID.h"
#include "CTextEnum.h"
#include "IKRAdornmentData.h"

class PMPoint;
class PMReal;

/** Adornment data interface for Kenten (dotted emphasis) IAdornmentData
	@ingroup text_adorn
	@see Adornments
*/
class IKentenAdornmentData : public IKRAdornmentData
{
public:
	enum { kDefaultIID = IID_IKENTENADORNMENTDATA }; 

	enum KentenKind {
			kNoKind = IKentenStyle::Kenten_None,

			kBlackSesameDot		/* = IKentenStyle::Kenten_BlackSesameDot */,
			kWhiteSesameDot		/* = IKentenStyle::Kenten_WhiteSesameDot */,
			kFisheye			/* = IKentenStyle::Kenten_Fisheye */,
			kBlackCircle		/* = IKentenStyle::Kenten_BlackCircle */,
			kSmallBlackCircle	/* = IKentenStyle::Kenten_SmallBlackCircle */,
			kBullseye			/* = IKentenStyle::Kenten_Bullseye */,
			kBlackTriangle		/* = IKentenStyle::Kenten_BlackTriangle */,
			kWhiteTriangle		/* = IKentenStyle::Kenten_WhiteTriangle */,
			kWhiteCircle		/* = IKentenStyle::Kenten_WhiteCircle */,
			kSmallWhiteCircle	/* = IKentenStyle::Kenten_SmallWhiteCircle */,

			kCustomKind			/* = IKentenStyle::Kenten_Custom */
		};

	enum KentenAlignment { kLeft, kCenter, kRight } ;

	/** Set kind of kenten (which dot style)
	@param val IN from enum KentenKind
	@param offsetInRun IN offset in characters into the base text wax run
	@param len IN number of characters to adorn
	*/
	virtual void SetKentenKind(uchar val, int32 offsetInRun, int32 len) = 0;

	/** Adds characters to adorned length in base text wax run
	@param lenToAdd IN number of characters to add
	*/
	virtual void AddLength(int32 lenToAdd) = 0;

	/** Sets font of custom kenten
	@param font IN UID of IPMFont
	@param size IN pt size of font
	@param style IN face of font (non-native)
	*/
	virtual void SetKentenFont(UID font, const PMReal& size, PMString style) = 0;

	/** Attaches this adornment to a base text IWaxRun
	@param baseTextWaxRun IN wax run to attach to
	*/
	virtual void SetBaseTextRun(IWaxRun* baseTextWaxRun) = 0;

	/** Is there kenten on this run?
	@return true if there is kenten
	*/
	virtual bool16 IsFeatureOn() const = 0;

	/** Number of characters in adorned base text run
	@return number of characters
	*/
	virtual int32 GetLength() const = 0;

	/** Custom impl of QueryFont for kenten font
	@param database of current pub
	@return kenten font
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

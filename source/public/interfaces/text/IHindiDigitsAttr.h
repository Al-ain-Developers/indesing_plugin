//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IHindiDigitsAttr.h $
//  
//  Owner: prubini
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
//  
//  Usage rights licenced to Adobe Inc. 1993 - 2007.
//  
//========================================================================================

#ifndef __IDigitsAttr__
#define __IDigitsAttr__

#include "IPMUnknown.h"
#include "WorldReadyID.h"


/**	IDigitsAttr is a simple data interface that is used to hold the
	desired digits used by the world ready composer.
	The simple low-ascii digit values will draw with non-standard glyphs
	if this attribute specifies it.
	@ingroup text_attr
	@see IDrawingStyleME
*/
class IDigitsAttr : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDIGITSATTR };

		enum Digits {	kNativeDigits = -1,
						kDefaultDigits = 0,
						kArabicDigits,
						kHindiDigits,
						kFarsiDigits,
						kFullFarsiDigits,
						kThaiDigits,
						kLaoDigits,
						kDevanagariDigits,
						kBengaliDigits,
						kGurmukhiDigits,
						kGujaratiDigits,
						kOriyaDigits,
						kTamilDigits,
						kTeluguDigits,
						kKannadaDigits,
						kMalayalamDigits,
						kTibetanDigits,
						kKhmerDigits,
						kBurmeseDigits,
						kLastDigitSet };

		typedef IDigitsAttr::Digits		ValueType;

		/** Set the digits used by the world ready composer.
		@param val is the digit type.
		*/
		virtual void Set(ValueType val) = 0;

		/** Get the digits used by the world ready composer.
		@return the digit type.
		*/
		virtual ValueType Get() const = 0;
};

#endif
		// __IIHindiDigitsAttr__

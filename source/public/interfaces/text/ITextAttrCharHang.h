//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrCharHang.h $
//  
//  Owner: ekenning
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
#ifndef __ITextAttrCharHang__
#define __ITextAttrCharHang__

#include "IPMUnknown.h"
#include "IDrawingStyle.h"
#include "TextAttrID.h"

/** Interface for a text attribute whose value is the character hang (the alignment vertically in a horizontal line).
	@see IDrawingStyle::CharacterHang
	@ingroup text_attr
*/
class ITextAttrCharHang : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRCHARHANG };

		typedef IDrawingStyle::CharacterHang		ValueType;

		/** Set() sets the value to type flag
		@param flag [IN] the character hang to be set
		*/
		void Set(ValueType flag) { SetHang(flag); }
		/** Get() gets the current setting for Character Hang
		@return the character hang
		*/
		ValueType Get() const { return GetHang(); }

		/** SetHang() -- same as Set()
		@param cm [IN] character hang to be set
		*/
		virtual void SetHang(IDrawingStyle::CharacterHang cm) = 0;
		/** GetHang() -- same as Get()
		@return character hang setting
		*/
		virtual IDrawingStyle::CharacterHang GetHang() const = 0;
};

#endif
		// __ITextAttrCharHang__

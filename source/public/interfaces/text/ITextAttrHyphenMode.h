//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrHyphenMode.h $
//  
//  Owner: Eric_Menninga
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
#ifndef __ITextAttrHyphenMode__
#define __ITextAttrHyphenMode__

#include "IPMUnknown.h"
#include "IHyphenationStyle.h"
#include "TextAttrID.h"


/**	ITextAttrHyphenMode is a simple data interface that is used to hold the
	desired hyphenation mode: on or off.
	Although the data supports off, manual, dictionary and algorithm, InDesign
	only directly provides access to "manual" and "algorithm"  These correspond
	to "off" (hard & discretionary hyphens only) and "on" (everything including algorithmic hyphenation).
	@ingroup text_attr
	@ingroup text_hyphen
	@see IHyphenationStyle
*/
class ITextAttrHyphenMode : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRHYPHENMODE };

		typedef IHyphenationStyle::HyphenationMethod		ValueType;

		/** Set the value.
			@param flag specifies the hyphenation mode.
		*/
		void Set(ValueType flag)
			{ SetMethod(flag); }
		/** Get the value.
			@return the hyphenation mode.
		*/
		ValueType Get() const
			{ return GetMethod(); }

		/** Set the value.
			@param method specifies the hyphenation mode.
		*/
		virtual void SetMethod(IHyphenationStyle::HyphenationMethod method) = 0;
		/** Get the value.
			@return the hyphenation mode.
		*/
		virtual IHyphenationStyle::HyphenationMethod GetMethod() const = 0;
};

#endif
		// __ITextAttrHyphenMode__


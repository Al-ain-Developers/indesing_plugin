//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ITextAttrRubyOverhang.h $
//  
//  Owner: Shinji Hiramatsu
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
#ifndef __ITextAttrRubyOverhang__
#define __ITextAttrRubyOverhang__

#include "IPMUnknown.h"
#include "IDrawingStyle.h"
#include "IRubyStyle.h"
#include "TextAttrID.h"
#include "CJKID.h"

/** This interface is used to set or retrieve the text attribute for ruby overhang.
	@ingroup text_attr
*/
class ITextAttrRubyOverhang : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRRUBYOVERHANG };

		typedef IRubyStyle::RubyOverHang		ValueType;

		/** Set the attribute.
		@param the attribute.
		*/
		virtual void Set(ValueType flag) = 0;
		/** Get the attribute.
		@return the attribute.
		*/
		virtual ValueType Get() const = 0;
		/** Describe the attribute.
		@param the attribute.
		@return the attribute.
		*/
		virtual ConstCString Describe(ValueType) const = 0;
};

#endif
		// __ITextAttrRubyOverhang__

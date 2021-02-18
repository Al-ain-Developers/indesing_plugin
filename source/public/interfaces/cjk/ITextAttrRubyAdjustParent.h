//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ITextAttrRubyAdjustParent.h $
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
#ifndef __ITextAttrRubyAdjustParent__
#define __ITextAttrRubyAdjustParent__

#include "IPMUnknown.h"
#include "IDrawingStyle.h"
#include "IRubyStyle.h"
#include "CJKID.h"
#include "TextAttrID.h"

/** This interface is used to set or retrieve the text attribute for ruby adjusting parent text.
	@ingroup text_attr
*/
class ITextAttrRubyAdjustParent : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRRUBYADJUSTPARENT };

		typedef IRubyStyle::RubyAdjustParent		ValueType;

		/** Set the attribute.
		@param the attribute.
		*/
		void Set(ValueType flag)
			{ SetRubyAdjustParent(flag); }
		/** Get the attribute.
		@return the attribute.
		*/
		ValueType Get() const
			{ return GetRubyAdjustParent(); }

		/** Set how to adjust the parent text.
		@param the attribute.
		*/
		virtual void SetRubyAdjustParent(IRubyStyle::RubyAdjustParent data) = 0;
		/** Get how to adjust the parent text.
		@return the attribute.
		*/
		virtual IRubyStyle::RubyAdjustParent GetRubyAdjustParent() const = 0;
		/** Describe the attribute.
		@param the attribute.
		@return the attribute.
		*/
		virtual ConstCString Describe(IRubyStyle::RubyAdjustParent) const = 0;
};

#endif
		// __ITextAttrRubyAdjustParent__

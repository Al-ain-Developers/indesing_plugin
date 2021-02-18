//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ITextAttrRubyAlign.h $
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
#ifndef __ITextAttrRubyAlign__
#define __ITextAttrRubyAlign__

#include "IPMUnknown.h"
#include "ICompositionStyle.h"
#include "IRubyStyle.h"
#include "TextAttrID.h"


/** This interface is used to set or retrieve the text attribute for ruby alignment.
	@ingroup text_attr
*/
class ITextAttrRubyAlign : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRRUBYALIGN };

		typedef IRubyStyle::RubyAlign		ValueType;

		/** Get the attribute.
		@return the attribute.
		*/
		ValueType Get() const
			{ return GetRubyAlignment(); }
		/** Set the attribute.
		@param the attribute.
		*/
		void Set(ValueType val)
			{ SetRubyAlignment(val); }

		/** Set how to align the ruby.
		@param the attribute.
		*/
		virtual void SetRubyAlignment(IRubyStyle::RubyAlign dq) = 0;
		/** Get how to align the ruby.
		@return the attribute.
		*/
		virtual IRubyStyle::RubyAlign GetRubyAlignment() const = 0;
};

#endif

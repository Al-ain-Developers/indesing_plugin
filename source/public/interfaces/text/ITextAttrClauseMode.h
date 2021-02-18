//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrClauseMode.h $
//  
//  Owner: Michiko Jessett
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
#ifndef __ITextAttrClauseMode__
#define __ITextAttrClauseMode__

#include "IPMUnknown.h"
#include "IIMEAttrStyle.h"

/** 
	@ingroup text_attr
*/
class ITextAttrClauseMode : public IPMUnknown
{
	public:
//		enum { kDefaultIID = IID_ITEXTATTRBOOLEAN };
		
		typedef IIMEAttrStyle::IMEClauseMode		ValueType;

		void Set(ValueType flag)
			{ SetMode(flag); }
		ValueType Get() const
			{ return GetMode(); }

		virtual void SetMode(IIMEAttrStyle::IMEClauseMode mode) = 0;
		virtual IIMEAttrStyle::IMEClauseMode GetMode() const = 0;
};

#endif
// __ITextAttrClauseMode__

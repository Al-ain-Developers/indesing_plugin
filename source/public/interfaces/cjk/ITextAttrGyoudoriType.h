//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ITextAttrGyoudoriType.h $
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
#ifndef __ITextAttrGyoudoriType__
#define __ITextAttrGyoudoriType__

#include "IPMUnknown.h"
#include "IGridRelatedStyle.h"
#include "TextAttrID.h"
#include "CJKID.h"


/** INTERNAL USE ONLY */
class ITextAttrGyoudoriType : public IPMUnknown	// ##rk: NOT IMPLEMENTED, NOT ACCESSED, NOT USED
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRGYOUDORITYPE};

		typedef IGridRelatedStyle::GyoudoriType		ValueType;

		ValueType Get() const
			{ return GetGyoudoriType(); }
		void Set(ValueType val)
			{ SetGyoudoriType(val); }

		virtual void SetGyoudoriType(IGridRelatedStyle::GyoudoriType dq) = 0;
		virtual IGridRelatedStyle::GyoudoriType GetGyoudoriType() const = 0;
};

#endif	// __ITextAttrGyoudoriType__

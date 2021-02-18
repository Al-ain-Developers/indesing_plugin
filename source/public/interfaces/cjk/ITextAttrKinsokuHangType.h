//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ITextAttrKinsokuHangType.h $
//  
//  Owner: nmccully
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
#ifndef __ITextAttrKinsokuHangType__
#define __ITextAttrKinsokuHangType__

#include "IPMUnknown.h"
#include "ICompositionStyle.h"
#include "IMojikumiStyle.h"
#include "TextAttrID.h"


/** Represents the KinsokuHangType text attribute.
	@see IMojikumiStyle::KinsokuHangType
	@ingroup text_attr
*/
class ITextAttrKinsokuHangType : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IKINSOKUHANGTYPE };

		typedef IMojikumiStyle::KinsokuHangType		ValueType;

		/** */
		ValueType Get() const { return GetKinsokuHangType(); }
		/** */
		void Set(ValueType val) { SetKinsokuHangType(val); }

		/** */
		virtual void SetKinsokuHangType(IMojikumiStyle::KinsokuHangType dq) = 0;
		/** */
		virtual IMojikumiStyle::KinsokuHangType GetKinsokuHangType() const = 0;
};

#endif

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IRangeData.h $
//  
//  Owner: robin briggs
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
#ifndef __IRangeData__
#define __IRangeData__

#include "IPMUnknown.h"
#include "CommandID.h"
#include "RangeData.h"

/** Specifies an integer range.
	@ingroup text_datatype
*/
class IRangeData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IRANGEDATA };

		virtual void Set(int32 startOfRange, int32 endOfRange, RangeData::Lean lean = RangeData::kLeanForward) = 0;
		virtual int32 GetStart(RangeData::Lean* lean = nil) const = 0;
		virtual int32 GetEnd() const = 0;
		virtual int32 GetLength() const = 0;
		virtual RangeData GetRange() const = 0;
		virtual void SetRange( const RangeData& r) = 0;
};

#endif // __IRangeData__

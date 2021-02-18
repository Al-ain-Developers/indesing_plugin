//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ITextAttrGridAlignment.h $
//  
//  Owner: Nat McCully
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
#ifndef __ITextAttrGridAlignment__
#define __ITextAttrGridAlignment__

#include "IPMUnknown.h"
#include "TextAttrID.h"
#include "CJKID.h"
#include "CTextEnum.h"

/** Interface for a text attribute whose value is the GridAlignmentMetric (what part of the tile and grid should be aligned to each other).
	@see Text::GridAlignmentMetric
	@ingroup text_attr
*/
class ITextAttrGridAlignment : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRGRIDALIGNMENT };

		typedef Text::GridAlignmentMetric		ValueType;

		/** */
		void Set(ValueType flag) { SetGridAlignment(flag); }
		/** */
		ValueType Get() const { return GetGridAlignment(); }

		/** */
		virtual void SetGridAlignment(Text::GridAlignmentMetric cm) = 0;
		/** */
		virtual Text::GridAlignmentMetric GetGridAlignment() const = 0;
};

#endif // __ITextAttrGridAlignment__

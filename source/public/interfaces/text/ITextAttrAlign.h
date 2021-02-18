//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrAlign.h $
//  
//  Owner: EricM
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
#ifndef __ITextAttrAlign__
#define __ITextAttrAlign__

#include "IPMUnknown.h"
#include "ICompositionStyle.h"
#include "TextAttrID.h"


/** Interface for a text attribute whose value is the (paragraph's) text alignment/justification.
	@see ICompositionStyle::TextAlignment
	@ingroup text_attr
*/
class ITextAttrAlign : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRALIGN };

		typedef ICompositionStyle::TextAlignment		ValueType;

		/** */
		ValueType Get() const { return GetAlignment(); }
		/** */
		void Set(ValueType val) { SetAlignment(val); }

		/** */
		virtual void SetAlignment(ICompositionStyle::TextAlignment dq) = 0;
		/** */
		virtual ICompositionStyle::TextAlignment GetAlignment() const = 0;
};

#endif

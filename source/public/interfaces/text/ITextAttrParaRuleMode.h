//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrParaRuleMode.h $
//  
//  Owner: ekenning
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
#ifndef __ITextAttrParaRuleMode__
#define __ITextAttrParaRuleMode__

#include "IPMUnknown.h"
#include "ICompositionStyle.h"
#include "TextAttrID.h"


/** 
	A holds the paragraph rules mode value for the paragraph rules text attribute
	@ingroup text_attr
*/

class ITextAttrParaRuleMode : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRPARARULEMODE };
		
		typedef ICompositionStyle::ParagraphRuleMode		ValueType;

		/**
			Sets the paragragh rule mode to the param passed in
			@param flag		ICompositionStyle::ParagraphRuleMode
		*/
		virtual void Set(ValueType dq) = 0;
		/**
			Gets the paragragh rule mode
			@return 	ICompositionStyle::ParagraphRuleMode
		*/
		virtual ValueType Get() const = 0;
};

#endif
		// __ITextAttrParaRuleMode__

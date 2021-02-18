//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrStrokeJoinType.h $
//  
//  Owner: Abhay Sibal
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2017 Adobe 
//  All Rights Reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in 
//  accordance with the terms of the Adobe license agreement accompanying 
//  it. If you have received this file from a source other than Adobe, 
//  then your use, modification, or distribution of it requires the prior 
//  written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __ITextAttrStrokeJoinType__
#define __ITextAttrStrokeJoinType__

#include "IPMUnknown.h"
#include "ICompositionStyle.h"
#include "TextAttrID.h"


/** 
	This holds the value for paragraph stroke join type attribute
	@ingroup text_attr
*/

class ITextAttrStrokeJoinType : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRSTROKEJOINTYPE };
		
		typedef ICompositionStyle::StrokeJoinType		ValueType;

		/**
			Sets the paragragh stroke join type to the param passed in
			@param flag		ICompositionStyle::StrokeJoinType
		*/
		virtual void Set(ValueType dq) = 0;
		/**
			Gets the paragraph stroke join type
			@return 	ICompositionStyle::StrokeJoinType
		*/
		virtual ValueType Get() const = 0;
};

#endif
// __ITextAttrStrokeJoinType__
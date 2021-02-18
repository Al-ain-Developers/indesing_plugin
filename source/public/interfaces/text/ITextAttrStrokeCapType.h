//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrStrokeCapType.h $
//  
//  Owner: Souvik Sinha Deb
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
#ifndef __ITextAttrStrokeCapType__
#define __ITextAttrStrokeCapType__

#include "IPMUnknown.h"
#include "ICompositionStyle.h"
#include "TextAttrID.h"


/**
This holds the value for paragraph stroke cap type attribute
@ingroup text_attr
*/

class ITextAttrStrokeCapType : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTATTRSTROKECAPTYPE };

	typedef ICompositionStyle::StrokeCapType		ValueType;

	/**
	Sets the paragragh stroke cap type to the param passed in
	@param flag		ICompositionStyle::StrokeCapType
	*/
	virtual void Set(ValueType dq) = 0;
	/**
	Gets the paragraph stroke cap type
	@return 	ICompositionStyle::StrokeCapType
	*/
	virtual ValueType Get() const = 0;
};

#endif
// __ITextAttrStrokeCapType__
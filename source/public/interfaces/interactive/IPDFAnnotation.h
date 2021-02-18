//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IPDFAnnotation.h $
//  
//  Owner: Tim Wright
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
#ifndef __IPDFAnnotation_h__
#define __IPDFAnnotation_h__

#include "IPMUnknown.h"
#include "FormFieldID.h"

//=============================================================================

/** Identifies a page item as a pdf annotation.  These objects shouldn't be
    placed within one another, as it poses difficulty for PDF export...
*/
class IPDFAnnotation : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPDFANNOTATION };
};

//=============================================================================

#endif // __IPDFAnnotation_h__

//  IFormField.h.

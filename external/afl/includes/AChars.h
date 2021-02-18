//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/external/afl/includes/AChars.h $
//  
//  Owner: Michael Easter
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
#ifndef __AChars__
#define __AChars__

// Define some of the InDesign text character constants if not already defined
#ifndef __TEXTCHAR__
#include "ATypes.h"

const textchar kTextChar_Null				= 0x0000;
const textchar kTextChar_Space				= 0x0020;
const textchar kTextChar_QuotationMark 		= 0x0022;	// U+0022, QUOTATION MARK, The Unicode Standard 2.0, 7-7
const textchar kTextChar_Asterisk			= 0x002A;
const textchar kTextChar_Period				= 0x002E;
const textchar kTextChar_Solidus			= 0x002F;
const textchar kTextChar_Colon				= 0x003A;
const textchar kTextChar_LessThanSign		= 0x003C;
const textchar kTextChar_GreaterThanSign	= 0x003E;
const textchar kTextChar_QuestionMark		= 0x003F;
const textchar kTextChar_ReverseSolidus		= 0x005C;
const textchar kTextChar_VerticalLine		= 0x007C;

// surrogates
const textchar kTextChar_HighSurrogateStart	= 0xD800;    // includes private use 0xDB80 - 0xDBFF
const textchar kTextChar_HighSurrogateEnd	= 0xDBFF;
const textchar kTextChar_LowSurrogateStart	= 0xDC00;
const textchar kTextChar_LowSurrogateEnd	= 0xDFFF;
#endif	// #ifndef __TEXTCHAR__

#endif	// __AChars__

//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPrintGlyphThresholdPref.h $
//  
//  Owner: DBerggren
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IPrintGlyphThresholdPref__
#define __IPrintGlyphThresholdPref__

#include "IPMUnknown.h"

/**
 An interface to store the value for the print glyph threshold. This value
 is used to determine if a font is downloaded completely, vs. subsetted when
 the font download option is set to Complete in the Print dialog Graphics panel.
 */
class IPrintGlyphThresholdPref : public IPMUnknown
{
public:
	/**
	 Enum of some default values
	 */
	enum {
		kGlyphThresholdMinValue			= 1,
		kGlyphThresholdDefaultValue		= 2000,
		kGlyphThresholdMaxValue			= 999999
	};

	/**
	 Set method for glyph threshold. Valid entries are 1 - 65535

	 @param glyphThreshold	The value of the glyph threshold
	 */
	virtual void SetPrintGlyphThreshold (int32 glyphThreshold) = 0;
	
	/**
	 Returns value of the current setting for the glyph threshold.

	 @return value of the current setting for the glyph threshold
	 */
	virtual int32 GetPrintGlyphThreshold() const = 0;
};


#endif

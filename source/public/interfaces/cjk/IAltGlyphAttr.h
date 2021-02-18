//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IAltGlyphAttr.h $
//  
//  Owner: prubini
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
#ifndef __IAltGlyphAttr__
#define __IAltGlyphAttr__

#include "IPMUnknown.h"
#include "K2Vector.h"
#include "OTFeature.h"
#include "CJKID.h"

/** This interface is obsolete, use ITextAttrGlyphForm instead. This is an attribute for alternate glyphs. 
	@ingroup text_attr
*/
class IAltGlyphAttr : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IALTGLYPHATTR_OBSOLETE };
		enum GlyphForm {kNoForm,
						kTraditionalForm,
						kExpertForm,
						kJIS78Form,
						kJIS83Form,
						kHalfWidthForm,
						kThirdWidthForm,
						kQuarterWidthForm,
                        kNLCForm};
    
		typedef IAltGlyphAttr::GlyphForm		ValueType;

		// Add and Remove 
		virtual void SetAltGlyph(const char* whichSet,int32 choice) = 0;

		virtual void SetGlyphForm(GlyphForm) = 0;
		virtual void Set(ValueType val)
			{ SetGlyphForm(val); }
		virtual GlyphForm GetGlyphForm() const = 0;
		virtual ValueType Get() const
			{ return GetGlyphForm(); }
		
		virtual void SetFeatureList(const OpenTypeFeatureList& featureList) = 0;
		virtual const OpenTypeFeatureList& GetFeatureList() const = 0;
};

 #endif
		// __IAltGlyphAttr__

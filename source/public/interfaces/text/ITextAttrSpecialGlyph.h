//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrSpecialGlyph.h $
//  
//  Owner: emenning
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
#ifndef __ITextAttrSpecialGlyph__
#define __ITextAttrSpecialGlyph__

#include "IPMUnknown.h"
#include "CTextEnum.h"
#include "TextAttrID.h"



/** This is used to set a glyph name or glyph id for a glyph with no unicode value. The unicode value
	kTextChar_SpecialGlyph or kTextChar_NonRomanSpecial is used in the story to indicate that this 
	attribute should be used for the glyph id. When this attribute is constructed glyph name is nil
	and GlyphID is 0. Normally you will only set either the glyph name or the glyph id.
	@ingroup text_attr
*/
class ITextAttrSpecialGlyph : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRSPECIALGLYPH };
		
		typedef const char*		ValueType;
		typedef Text::GlyphID	AlternateValueType;

		/**	Set to glyph name. The name is used first to find a glyph in the fonts. If no
			glyph is found the value set by SetGlyphID will be used. Calling this does not
			reset glyph id. These names are usually obtained from IPMFont::GetGlyphName. Glyph
			names are prefferable to glyph ids because when switching fonts glyph ids may not
			represent the same glyph but glyph names are more likely to represent the same glyph.
			@param flag		glyph name to set
		 */
		virtual void Set(ValueType flag) = 0;

		/**	Gets the glyph name for the attribute. May be nil if only ID is set.
			@return ValueType	glyph name set for a attribute
		 */
		virtual ValueType Get() const = 0;


		/**	Set glyph id for attribute. This will set glyph name to nil. A glyph id is only
			reliable across font changes if the 2 fonts have the same font registry and font
			ordering. 
			@param g	glyph id to set for attribute
		 */
		virtual void SetGlyphID(AlternateValueType g) = 0;

		/**	Get glyph id for attribute.
			@return AlternateValueType	glyph id for attribute. 
		 */
		virtual AlternateValueType GetGlyphID() const = 0;
};

#endif
		// __ITextAttrSpecialGlyph__

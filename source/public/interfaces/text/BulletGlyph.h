//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/BulletGlyph.h $
//  
//  Owner: Anurag Wahi
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

#ifndef __BULLETGLYPH_H__
#define __BULLETGLYPH_H__

#include <vector>

#include "IPMStream.h"
#include "ITextAttrBulletCharacter.h"

struct BulletGlyph
{
	// Enumeration indicating type of glyph - 
	//		Add dialog will always use kGlyphWithFont while reading, and specific value while writing
	//		Main dialog will use bullet character specific value always.
	ITextAttrBulletCharacter::BulletCharacterType		f_BulletCharacterType;

	// Glyph ID or Unicode value, depending on bullet character type
	int32					f_BulletCharacterValue;

	// For bullets that remember their fonts, the font UID, style and MM Axes information.
	// Warning: Giving the wrong fontUID could negatively affect the Bullets feature
	// in certain cases.
	UID						f_FontUID;
	PMString				f_FontFace;
	std::vector<Fixed>		f_Axes;

	BulletGlyph()
		: f_BulletCharacterType(ITextAttrBulletCharacter::kUnicodeWithFont)
		, f_BulletCharacterValue(0)
		, f_FontUID(kInvalidUID)
	{
	}

	BulletGlyph(const ITextAttrBulletCharacter::BulletCharacterType bulletType, 
				const int32 bulletChar,
				const UID fontUID = kInvalidUID,
				const PMString &fontFace = "",
				const std::vector<Fixed> *axes = 0)
	: f_BulletCharacterType(bulletType)
	, f_BulletCharacterValue(bulletChar)
	, f_FontUID(fontUID)
	, f_FontFace(fontFace)
	{
		if (axes)
			f_Axes = *axes;
	}

	bool16 operator==(const BulletGlyph &other) const
	{
		if (f_BulletCharacterType != other.f_BulletCharacterType ||
			f_BulletCharacterValue != other.f_BulletCharacterValue)
			return kFalse;

		if (f_BulletCharacterType == ITextAttrBulletCharacter::kGlyphWithFont ||
			f_BulletCharacterType == ITextAttrBulletCharacter::kUnicodeWithFont)
		{
			if (f_FontUID != other.f_FontUID || 
				!f_FontFace.IsEqual(other.f_FontFace) ||
				f_Axes != other.f_Axes)
				return kFalse;
		}

		return kTrue;
	}

	void ReadWrite(IPMStream *s)
	{
		XFER_ENUM(s, f_BulletCharacterType);
		s->XferInt32(f_BulletCharacterValue);
		s->XferReference(f_FontUID);
		f_FontFace.ReadWrite(s);	
		uchar na = uchar((int8)f_Axes.size());
		int32 numAxes = (int8)s->XferByte(na);

		if (s->IsReading())
			f_Axes.resize(numAxes);

		if (numAxes > 0)
		{
			for (int32 i = 0; i < numAxes; ++i)
				s->XferInt32(f_Axes[i]);
		}
	}
};

typedef std::vector<BulletGlyph> BulletGlyphSet;

#endif // __BULLETGLYPH_H__
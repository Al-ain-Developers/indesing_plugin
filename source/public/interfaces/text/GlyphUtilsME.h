//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/GlyphUtilsME.h $
//  
//  Owner: Pascal Rubini
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
//  Usage rights licenced to Adobe Inc. 1993 - 2007.
//  
//========================================================================================

#pragma once
#ifndef __GlyphUtilsME__
#define __GlyphUtilsME__

#include "IGlyphUtilsME.h"

namespace GlyphUtilsME
{
	inline void	InsertTheCharacter(ISelectionManager *selMgr, IPMFont *font, LanguageID id, GlyphEntry * baseGlyphEntry, GlyphEntry * alternateGlyphEntry, bool16 selectChar = kFalse, bool16 setFont = kFalse)
		{ Utils<IGlyphUtilsME>()->InsertTheCharacter( selMgr, font, id, baseGlyphEntry, alternateGlyphEntry, selectChar, setFont); }
	inline int32	GetSelectionGlyphSet(IPMFont *font, IFontInstance* fontInstance, LanguageID id, const WideString& chars,Text::GlyphID glyph, GlyphSet *glyphSet, GlyphSet::GlyphSortOrder sortOrder = GlyphSet::kNoOrder)
		{ return Utils<IGlyphUtilsME>()->GetSelectionGlyphSet( font,  fontInstance, id, chars, glyph, glyphSet, sortOrder ); }
	inline int32	GetGlyphListGlyphSet(IPMFont *font, IFontInstance* fontInstance, LanguageID id, Text::GlyphID* glyphs, int32 numGlyphs, GlyphSet * glyphSet, GlyphSet::GlyphSortOrder sortOrder = GlyphSet::kNoOrder)
		{ return Utils<IGlyphUtilsME>()->GetGlyphListGlyphSet( font,  fontInstance, id,  glyphs, numGlyphs, glyphSet, sortOrder ); }
	inline bool16	GetGlyphHasAlternate(IPMFont *font, LanguageID id, Text::GlyphID glyph, const char * tag = nil)
		{ return Utils<IGlyphUtilsME>()->GetGlyphHasAlternate( font, id, glyph, tag ); }
	inline int32	GetEntireFont(IPMFont *font, LanguageID id, GlyphSet * glyphSet, GlyphSet::GlyphSortOrder sortOrder = GlyphSet::kNoOrder)
		{ return Utils<IGlyphUtilsME>()->GetEntireFont( font, id,  glyphSet, sortOrder ); }
	inline int32	GetFilteredGlyphs(IPMFont *font, LanguageID id, GlyphSet * glyphSet, GlyphFilterProcList& includeFilterProcList, GlyphFilterProcList& excludeFilterProcList, GlyphSet::GlyphSortOrder sortOrder = GlyphSet::kNoOrder )
		{ return Utils<IGlyphUtilsME>()->GetFilteredGlyphs( font, id,  glyphSet, includeFilterProcList, excludeFilterProcList, sortOrder ); }

	inline int32	GetOTFFeatureGlyphSet(const char * tags, int32 numTags, IPMFont * font, LanguageID id, GlyphSet * glyphSet, GlyphSet::GlyphSortOrder sortOrder = GlyphSet::kNoOrder)
		{ return Utils<IGlyphUtilsME>()->GetOTFFeatureGlyphSet( tags, numTags, font, id,  glyphSet, sortOrder  ); }
	inline bool16	GetOTFFeature(IPMFont * font, IFontInstance * fontInstance, LanguageID id, const GlyphEntry * baseGlyph, const GlyphEntry * alternate, char * tagBuffer/* 4 bytes */, int32 & choice)
		{ return Utils<IGlyphUtilsME>()->GetOTFFeature( font, fontInstance, id, baseGlyph, alternate, tagBuffer, choice  ); }

	inline long		GetGlyphsForFeatureAccessInfo(const char * tags, int32 numTags, IPMFont * font, LanguageID id, GlyphSet * glyphSet)
		{ return Utils<IGlyphUtilsME>()->GetGlyphsForFeatureAccessInfo( tags, numTags, font, id, glyphSet ); }

	inline bool16	TestFeatureSubstitution(IFontInstance * fontInstance, LanguageID id, const WideString& textString, char * tags, int32 * choices, int32 numFeatures, Text::GlyphID testGlyphID)
		{ return Utils<IGlyphUtilsME>()->TestFeatureSubstitution( fontInstance, id, textString, tags, choices, numFeatures, testGlyphID ); }
}


#endif
		// __GlyphUtilsME__
		

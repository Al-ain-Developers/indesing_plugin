//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IGlyphUtilsME.h $
//  
//  Owner: ???
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

#ifndef __IGlyphUtilsME__
#define __IGlyphUtilsME__

#include "IPMUnknown.h"
#include "IPMStream.h"
#include "Utils.h"

#include "K2Vector.h"
#include "CTextEnum.h"
#include "TextID.h"
#include "ITextAttrGlyphForm.h"
#include "UnicodeClass.h"

class IPMFont;
class ISelectionManager;
class IFontInstance;
class GlyphAccessData;
class WideString;
class AttributeBossList;
class GlyphEntry;
class GlyphSet;
class RangeData;

/** Utilities for dealing with glyphs focusing on the complex-script aspects, especially.
	@ingroup text_font
*/
class IGlyphUtilsME : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGLYPHUTILSME };

    /** Inserts a glyph into textmodel. This API is deprecated. Please use InsertTheCharacterAtRange instead.
        @param *setMgr      selection manager
        @param *font        font of glyph.
		@param id			Language id.
        @param *baseGlyphEntry	entry of base glyph
        @param *alternateGlyphEntry	entry of alternate glyph
        @param selectChar	select glyph inserted
        @param setFont		set font of glyph to font passed in. font is restored to previous font after insertion
        @return				unicode character value. 0 if in PUA area and userArea is not nil.
	*/
	virtual void	InsertTheCharacter(ISelectionManager *selMgr, IPMFont *font, LanguageID id, const GlyphEntry * baseGlyphEntry,
		const GlyphEntry * alternateGlyphEntry, bool16 selectChar = kFalse, bool16 setFont = kFalse) = 0;

	/**	Gets alternate glyph values for a given glyph.
		@param font			font to get glyph alternates in
		@param fontInstance	font instance to get glyph alternates in. needs to be an instance of font
		@param id			Language id.
		@param chars		unicode value(s) for glyph. multiple values only if glyph is a combination of unicode
							values like a ligature.
		@param glyph		glyph to get alternates for
		@param glyphSet		OUT set of glyph alternates.
		@param sortOrder how the returned glyph set should be sorted
		@return int32		returns length of glyphset.
	 */
	virtual int32	GetSelectionGlyphSet(IPMFont *font, IFontInstance* fontInstance, LanguageID id, const WideString& chars,
		Text::GlyphID glyph, GlyphSet *glyphSet, GlyphSet::GlyphSortOrder sortOrder = GlyphSet::kNoOrder) = 0;

	/**	Get alternates for glyphs
		@param font			font to get glyph alternates in
		@param fontInstance	font instance to get glyph alternates in. needs to be an instance of font
		@param id			Language id.
		@param glyphs		glyphs to find alternates for
		@param numGlyphs	number of glyphs. must be < 20 (kMaxStrikes).
		@param glyphSet		OUT set of glyph alternates.
		@param sortOrder how the returned glyph set should be sorted
		@return int32		returns length of glyphset. returns 0 if numGlyphs was >=20.
	 */
	virtual int32	GetGlyphListGlyphSet(IPMFont *font, IFontInstance* fontInstance, LanguageID id, Text::GlyphID* glyphs,
		int32 numGlyphs, GlyphSet * glyphSet, GlyphSet::GlyphSortOrder sortOrder = GlyphSet::kNoOrder) = 0;

	/**	Determine if glyph has alternate with a given OpenType feature tag.
		@param font		font to look for alternate glyph in
		@param id			Language id.
		@param glyph	glyph to look for alternate
		@param tag		OpenType feature tag to look for. 'aalt' if set to nil.
		@return bool16	kTrue if there is an alternate with OpenType feature tag.
	 */
	virtual bool16	GetGlyphHasAlternate(IPMFont *font, LanguageID id, Text::GlyphID glyph, const char * tag = nil) = 0;

	/**	Determine how many alternate with a given OpenType feature tag the glyph has.
		@param font		font to look for alternate glyph in
		@param id			Language id.
		@param glyph	glyph to look for alternate
		@param tag		OpenType feature tag to look for. 'aalt' if set to nil.
		@return uint16	the number of alternates with the OpenType feature tag.
	 */
	virtual unsigned	GetGlyphAlternateCount (IPMFont *font, LanguageID id, Text::GlyphID glyph, const char * tag = nil) = 0;

	/**	Get all glyphs in font
		@param font		font to get glyphs in
		@param id			Language id
		@param glyphSet	OUT all glyphs in font
		@param sortOrder how the returned glyph set should be sorted
		@return int32	number of glyphs in glyphSet
	 */
	virtual int32	GetEntireFont(IPMFont *font, LanguageID id, GlyphSet * glyphSet, GlyphSet::GlyphSortOrder sortOrder = GlyphSet::kNoOrder) = 0;

	/**	Get all glyphs in a font that satisfy the given filter function (typically from UnicodeClass).
		@param font		font to get glyphs for
		@param id			Language id
		@param glyphSet	OUT filtered glyphs in font meeting the filter function(s) condition(s).
		@param includeFilterProcList	a list of function pointers to use to filter "in" the glyphs in the font, typically from UnicodeClass.h. GlyphFilterProcList filterArray; filterArray.push_back(&UnicodeClass::IsPunctuationOpen()); filterArray.push_back(&UnicodeClass::IsPunctuationClose());
		@param excludeFilterProcList	a list of function pointers to use to further filter "out" the glyphs in the font captured by the includeFilterProcList, typically from UnicodeClass.h.
		@param sortOrder how the returned glyph set should be sorted
		@return int32	number of glyphs in glyphSet
		@see UnicodeClass.h for type definitions for filter procs.
	 */
	virtual int32	GetFilteredGlyphs(IPMFont *font, LanguageID id, GlyphSet * glyphSet, GlyphFilterProcList& includeFilterProcList, GlyphFilterProcList& excludeFilterProcList, GlyphSet::GlyphSortOrder sortOrder = GlyphSet::kNoOrder ) = 0;

	/**	Get glyphs for a OpenType feature. Also sets global gDesiredTag that is used by GetGlyphAccessInfo for what
		OpenType feature to prefer.
		@param tags		OpenType features to get glyphs for
		@param numTags	number of OpenType features
		@param font		font to get glyphs in
		@param id			Language id.
		@param glyphSet	OUT glyphs with OpenType features
		@param sortOrder how the returned glyph set should be sorted
		@return int32	number of glyphs in glyphSet
	 */
	virtual int32	GetOTFFeatureGlyphSet(const char * tags, int32 numTags, IPMFont * font, LanguageID id, GlyphSet * glyphSet, GlyphSet::GlyphSortOrder sortOrder = GlyphSet::kNoOrder) = 0;


	/**	Try and find an open type feature for the font/glyph combo. Return if a suitable one was found.
		Probably INTERNAL use only.
		@param font		font glyph id is in
		@param fontInstance font instance to get OTF feature for. needs to be an instance of font
		@param id			Language id.
		@param baseGlyph entry of base glyph
		@param alternate entry of alternate glyph
		@param tags OpenType features to get glyphs for
		@param choice OUT return index value of OTF feature chosen from tags array.
		@return bool16 whether the particular feature was found
	 */
	virtual bool16 GetOTFFeature(IPMFont * font, IFontInstance * fontInstance, LanguageID id, const GlyphEntry * baseGlyph, const GlyphEntry * alternate, char * tagBuffer/* 4 bytes */, int32 & choice) = 0;

	/**	Get glyphs for a OpenType feature
		@param tags		OpenType features to get glyphs for
		@param numTags	number of OpenType features
		@param font		font to get glyphs in
		@param id			Language id.
		@param glyphSet	OUT glyphs with OpenType features
		@return int32	1 if has alternates. 0 if no alternates.
	 */
	virtual int32		GetGlyphsForFeatureAccessInfo(const char * tags, int32 numTags, IPMFont * font, LanguageID id,
		GlyphSet * glyphSet) = 0;

	/**	Sets glyphAccessData->fDesiredTag to global gDesiredTag. Calls IPMFont::GetOTGlyphAccess. External code
		should not use this and call IPMFont::GetOTGlyphAccess instead.
		@param glyphID			glyph id to get access for
		@param font				font glyph id is in
		@param id			Language id.
		@param glyphAccessData	access data
		@return int32			0 if success. 1 if failure.
	 */
	virtual int32		GetGlyphAccessInfo(Text::GlyphID glyphID, IPMFont * font, LanguageID id,
		GlyphAccessData * glyphAccessData) = 0;


	/**	
		Sets glyphAccessData->fDesiredTag to global gDesiredTag. Calls IPMFont::GetAllOTGlyphAccess. External code
		should not use this and call IPMFont::GetAllOTGlyphAccess instead.
		@param glyphID			glyph id to get access for
		@param font				font glyph id is in
		@param id			Language id.
		@param glyphAccessData	vector of access data
		@return int32			0 if success. 1 if failure.
	*/
	virtual int32 GetGlyphAllAccessInfo(Text::GlyphID glyphID, IPMFont * font, LanguageID langID, 
			K2Vector<GlyphAccessData*>& glyphAccessDataList) = 0;

	/**	Description
		Probably INTERNAL use only.
		@param fontInstance font instance to test out application of OTF features. needs to be an instance of font
		@param id			Language id.
		@param textString a string of length 1 to apply OTF the feature to
		@param tags		OpenType features array
		@param choices array of choice for features. count is the same as numFeatures.
		@param numFeatures number of features in features variable
		@param testGlyphID
		@return  kTrue if feature can be applied, kFalse if not
		@see IFontInstance.h, ApplyFeatures
	 */
	virtual bool16	TestFeatureSubstitution(IFontInstance * fontInstance, LanguageID id, const WideString& textString, char * tags, int32 * choices, int32 numFeatures, Text::GlyphID testGlyphID) = 0;

	/**	Get an attribute for an open type feature. Return if a suitable one was found.
		@param tags		OpenType feature to get attribute for
		@param choice	value of OTF feature chosen from tags array
		@param attrBossList OUT attribute for the open type feature
		@param featureList OUT
		@param form OUT
		@param fontInstance font instance to get attribute for.
		@param id			Language id.
		@param stringToApply string to get OTF attribute for
		@param g glyphID to get OTF attribute for
	 */
	virtual void	GetOTFAttribute(char * tags, int32 choice, AttributeBossList * attrBossList, OpenTypeFeatureList& featureList, int32& form,
									  IFontInstance *fontInstance, LanguageID id, const WideString& stringToApply, Text::GlyphID g) = 0;

	/** Inserts a glyph into textmodel
	@param *setMgr      selection manager
	@param *font        font of glyph.
	@param id			Language id.
	@param *baseGlyphEntry	entry of base glyph
	@param *alternateGlyphEntry	entry of alternate glyph
	@param selectChar	select glyph inserted
	@param setFont		set font of glyph to font passed in. font is restored to previous font after insertion
	@param start		Text index from where to insert. If this is not provided, then selection is taken as default.
	@param end			Text index till where to insert. If this is not provided, then selection is taken as default.
	@param rangeToSelect	Select this range of text after replacing the character.
	@return				unicode character value. 0 if in PUA area and userArea is not nil.
	*/
	virtual void	InsertTheCharacterAtRange(ISelectionManager *selMgr, IPMFont *font, LanguageID id, const GlyphEntry * baseGlyphEntry,
		const GlyphEntry * alternateGlyphEntry, bool16 selectChar = kFalse, bool16 setFont = kFalse, TextIndex start = kInvalidTextIndex,
		TextIndex end = kInvalidTextIndex, const RangeData* rangeToSelect = nil) = 0;
};


#endif
		// __IGlyphUtilsME__

